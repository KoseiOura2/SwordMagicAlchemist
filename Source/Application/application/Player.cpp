#include "Player.h"
#include "Framework.h"
#include "Keyboard.h"
#include "Floor.h"
#include "Turn.h"
#include "MessageLog.h"
#include "NetworkApp.h"
#include "Effect.h"
#include "Item.h"
#include "UIApp.h"
#include "Sound.h"

const int LIMIT_ZANMETUHA_DIS = 2;
const int BUFF_FOR_SKILL_2    = 20;

const int LEARN_ZANGEKI_LEVEL  = 2;
const int LEARN_ZANMETU_LEVEL  = 6;
const int LEARN_MATERIA_LEVEL  = 15;
const int LEARN_SPEED_UP_LEVEL = 20;

const int HP_UP  = 3;
const int ATK_UP = 2;
const int DEF_UP = 2;

const double NECESSARY_EXP_MAGNIFICATION = 1.2;

Player::Player( FloorPtr floor, TurnPtr turn, MessageLogPtr message, NetworkAppPtr network, ItemPtr item, EffectPtr effect, UIAppPtr ui_app ) : Character ( floor, network, message, effect ) {	
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	_floor   = floor;
	_turn    = turn;
	_message = message;
	_network = network;
	_item    = item;
	_effect  = effect;
	_ui_app  = ui_app;

	_shadow_image = viewer->loadGraph( "work/tile/shadow.png" );

	// モデルのロード
	loadModel( );

	// アニメーションの設定
	_anim_play_time = 0.0f;
	_anim_count = 0;
	_anim_index.stay = viewer->attachAnim( _anim_hundle.model, 0, _anim_hundle.stay );
	_main_anim = _anim_index.stay;
	_anim_state = STAY_ANIM;

	_my_type = MY_TYPE_PLAYER;
	// 初期化
	init( );
}

Player::~Player( ) {

}

void Player::loadModel( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	_model       = viewer->loadModel( "work/model/player_2/model_syujinkou.mv1" );
	_broad_model = viewer->loadModel( "work/model/player_2/model_syujinkou_broad.mv1" );
	_holy_model  = viewer->loadModel( "work/model/player_2/model_syujinkou_holy.mv1" );
	_dark_model  = viewer->loadModel( "work/model/player_2/model_syujinkou_dark.mv1" );
	_tri_model   = viewer->loadModel( "work/model/player_2/model_syujinkou_tri.mv1" );
	
	// モデルの大きさ
	viewer->modelSetScale( _model, 0.05f, 0.05f, 0.05f );
	viewer->modelSetScale( _broad_model, 0.05f, 0.05f, 0.05f );
	viewer->modelSetScale( _holy_model, 0.05f, 0.05f, 0.05f );
	viewer->modelSetScale( _dark_model, 0.05f, 0.05f, 0.05f );
	viewer->modelSetScale( _tri_model, 0.05f, 0.05f, 0.05f );

	_anim_hundle.model  = _model;
	_anim_hundle.attack = viewer->loadModel( "work/model/player_2/motion_syujinkou_attack.mv1" );
	_anim_hundle.stay   = viewer->loadModel( "work/model/player_2/motion_syujinkou_stay.mv1" );
	_anim_hundle.walk   = viewer->loadModel( "work/model/player_2/motion_syujinkou_walk.mv1" );
	_anim_hundle.dead   = viewer->loadModel( "work/model/player_2/motion_syujinkou_dead.mv1" );
	_anim_hundle.damage = viewer->loadModel( "work/model/player_2/motion_syujinkou_damage.mv1" );

	
}

void Player::init( ) {
	
	_walking = false;
	_skill_attack_damage = 0;
	_attacked            = false;
	_attakking           = false;
	_skill_attacked      = false;
	_damaging            = false;
	_dead                = false;
	_zanmetuha.hit_enemy = false;
	_use_zanmetuha       = false;
	_use_materia_sword   = false;
	_no_revive           = false;
	_yes_revive          = false;
	_attacked            = false;
	_skill_attacked      = false;
	_dead                = false;
	// 初期ステータス  
	_status.max_life = 45;
	_pre_max_life   = _status.max_life;
	_status.life     = _status.max_life;
	_status.attack   = 10;
	_pre_attack     = _status.attack;
	_status.defense  = 10;
	_pre_defense    = _status.defense;
	// その他のステータス
	_name = "プレイヤー";
	_stamina            = MAX_STAMINA;
	_exp                = 0;
	_necessary_exp      = 20;
	_level              = 1;
	_action_count       = 0;

	
	_equipment[ EQUIPMENT_RING ].id      = ITEM_ID::ITEM_NONE;
	_equipment[ EQUIPMENT_RING ].life    = 0;
	_equipment[ EQUIPMENT_RING ].attack  = 0;
	_equipment[ EQUIPMENT_RING ].defense = 0;

	_equipment[ EQUIPMENT_WEAPON ].id      = ITEM_ID::ITEM_NONE;
	_equipment[ EQUIPMENT_WEAPON ].life    = 0;
	_equipment[ EQUIPMENT_WEAPON ].attack  = 0;
	_equipment[ EQUIPMENT_WEAPON ].defense = 0;
	
	setModel( );

	// 装備欄の初期化
	for ( int i = 0; i < CAN_EQUIPMENT_NUM; i++ ) {
		_equipment[ i ].id = ITEM_ID::ITEM_NONE;
	}

	_ui_app->setPlayerName( _name );
	_ui_app->setPlayerLevel( _level );
	_ui_app->setPlayerStatus( _status );
	_ui_app->setPlayerStamina( _stamina );
}

void Player::reset( ) {
	// 描画座標
	_draw_pos = _floor->getRandomFloor( ).pos;
	_pre_pos  = _draw_pos;
	// タイル座標
	_pos.x = _draw_pos.x / TILE_SIZE;
	_pos.y = _draw_pos.z / TILE_SIZE;
	_floor->setBondPlayer( ( int )_pos.x, ( int )_pos.y );
	_network->setSendChipData( NetworkApp::MAP_CHIP_TYPE::PLAYER, _pos, 0, false );
	// 向き
	_move_dir   = MOVE_DIR::MOVE_DIR_NONE;
	_status.dir = LOWER;
	// アニメーションの設定
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	viewer->dettachAnim( _anim_hundle.model, _anim_index.stay );
	// アニメーションの設定
	_anim_play_time = 0.0f;
	_anim_count = 0;
	_anim_index.stay = viewer->attachAnim( _anim_hundle.model, 0, _anim_hundle.stay );
	_main_anim = _anim_index.stay;
	_anim_state = STAY_ANIM;
	
	_walking = false;
	_skill_attack_damage = 0;
	_attacked            = false;
	_attakking           = false;
	_skill_attacked      = false;
	_damaging            = false;
	_dead                = false;
	_zanmetuha.hit_enemy = false;
	_use_zanmetuha       = false;
	_use_materia_sword   = false;
	_no_revive           = false;
	_yes_revive          = false;
	_ride_return_trap    = false;
	_return_start        = false;
	_warp                = false;
	_warp_stair          = false;
	_warp_start          = false;
	_warp_move           = false;
	_buff                = false;
	_buff_end            = false;
	_weapon_change       = false;
	
	refreshStateNextFloor( );
	refreshSpeed( );
	refreshBuff( );
}

void Player::bossReset( ) {
	// 描画座標
	_draw_pos = _floor->getBossRoomCharacterPos( Floor::BOSS_ROOM_CHARACTER::BOSS_ROOM_PLAYER ).pos;
	_pre_pos  = _draw_pos;
	// タイル座標
	_pos.x = _draw_pos.x / TILE_SIZE;
	_pos.y = _draw_pos.z / TILE_SIZE;
	_floor->setBondPlayer( ( int )_pos.x, ( int )_pos.y );
	_network->setSendChipData( NetworkApp::MAP_CHIP_TYPE::PLAYER, _pos, 0, false );
	// 向き
	_move_dir   = MOVE_DIR::MOVE_DIR_NONE;
	_status.dir = UPPER;
	// アニメーションの設定
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	viewer->dettachAnim( _anim_hundle.model, _anim_index.stay );
	// アニメーションの設定
	_anim_play_time = 0.0f;
	_anim_count = 0;
	_anim_index.stay = viewer->attachAnim( _anim_hundle.model, 0, _anim_hundle.stay );
	_main_anim = _anim_index.stay;
	_anim_state = STAY_ANIM;
	
	_walking = false;
	_skill_attack_damage = 0;
	_attacked            = false;
	_attakking           = false;
	_skill_attacked      = false;
	_damaging            = false;
	_dead                = false;
	_zanmetuha.hit_enemy = false;
	_use_zanmetuha       = false;
	_use_materia_sword   = false;
	_no_revive           = false;
	_yes_revive          = false;
	_ride_return_trap    = false;
	_return_start        = false;
	_warp                = false;
	_warp_stair          = false;
	_warp_start          = false;
	_warp_move           = false;
	_buff                = false;
	_buff_end            = false;
	_weapon_change       = false;
	
	refreshStateNextFloor( );
	refreshSpeed( );
	refreshBuff( );
}

void Player::update( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	if ( _weapon_change == true ) {
		setModel( );
		_weapon_change = false;
	}

	// アニメーションの再生
	playbackAnim( 1.0f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f );
	_turn_end = false;

	// 自ターンのみの行動
	myTurnAction( );

	// デバッグ
	KeyboardPtr keyboard = std::dynamic_pointer_cast< Keyboard >( fw->getTask( typeid( Keyboard ).name( ) ) );
	if ( keyboard->isPushKey( "ZERO" ) ) {
		_warp_stair = true;
		_warp_start = true;
		_warp_angle = _angle;
		_effect->playEffect( Effect::EFFECT_TYPE::EFFECT_WIND,  _draw_pos + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), EFFECT_PLAYER_NUM );
		_network->setSendChipData( NetworkApp::MAP_CHIP_TYPE::PLAYER, _pos, 0, false );
	}

	// ステータスの更新処理
	updateStatus( );

	// ダメージアニメが終わったかどうか
	finishDamageAnim( );

	// 復活
	if ( _network->isRevive( ) == NetworkApp::REVIVE::YES_REVIVE ) {
		_yes_revive = true;
	} else if ( _network->isRevive( ) == NetworkApp::REVIVE::NO_REVIVE && _dead == true ) {
		_no_revive = true;
	}
	if ( _anim_play_time > _dead_time + 2.0f && _yes_revive == true ) {
		revive( );
		_yes_revive = false;
	}
	// ワープ処理
	if ( _warp == true ) {
		warpPos( );
	}
	if ( _warp_stair == true ) {
		warpStairPos( );
	}
	if ( _warp_move == true ) {
		_floor->setBondPlayer( ( int )_pos.x, ( int )_pos.y );
		_network->setSendChipData( NetworkApp::MAP_CHIP_TYPE::PLAYER, _pos, 0, false );
	}

	// リターン処理
	if ( _return_start == true ) {
		if ( _draw_pos.x == _pos.x * 10 && _draw_pos.z == _pos.y * 10 ) {
			returnTrap( );
		}
	}

	// 描画関連
	updateDraw( );
}

void Player::setModel( ) {
	switch( _equipment[ EQUIPMENT_WEAPON ].id ) {
	case SWORD1:
		_anim_hundle.model  = _broad_model;
		break;
	case SWORD2:
		_anim_hundle.model  = _holy_model;
		break;
	case SWORD3:
		_anim_hundle.model  = _dark_model;
		break;
	case SWORD4:
		_anim_hundle.model  = _tri_model;
		break;
	default:
		_anim_hundle.model  = _model;
		break;
	}
	repairAnim( );
}

void Player::repairAnim( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	
	switch( _anim_state ) {
	case STAY_ANIM:
		viewer->dettachAnim( _anim_hundle.model, _anim_index.stay );
		break;
	case WALK_ANIM:
		viewer->dettachAnim( _anim_hundle.model, _anim_index.walk );
		break;
	case ATTACK_ANIM:
		viewer->dettachAnim( _anim_hundle.model, _anim_index.attack );
		break;
	case DAMAGE_ANIM:
		viewer->dettachAnim( _anim_hundle.model, _anim_index.damage );
		break;
	case DEAD_ANIM:
		viewer->dettachAnim( _anim_hundle.model, _anim_index.dead );
		break;
	}
	
	_anim_play_time = 0.0f;
	_anim_count = 0;
	// アニメーションのアタッチ
	_anim_index.stay = viewer->attachAnim( _anim_hundle.model, 0, _anim_hundle.stay );
	_main_anim = _anim_index.stay;
	_anim_state = STAY_ANIM;
	// アニメーションの時間を設定
	_total_time = viewer->animTotalTime( _anim_hundle.model, _main_anim );
	_walking = false;
}

void Player::myTurnAction( ) {
	Turn::STATE turn = _turn->getState( );
	if ( turn == Turn::PLAYER_TURN && _damaging == false ) {
		if ( _dead == false && 
			 _item->isUseSuperFlameRod( ) == false ) {
			// 向きを設定
			if ( _network->getCtrlPhase( ) == NetworkApp::CTRL_PHASE::MOVE_PHASE && _warp == false ) {
				setMoveDir( );
			}
			// 移動先を決定
			if ( _warp == false ) {
				setMovePos( );
			}
			// 攻撃
			attack( );
			// 技
			skillAttack( );
			// アイテムの使用
			itemAction( );
		}
	}
}

void Player::updateStatus( ) {
	// 向きを設定
	if ( _network->getCtrlPhase( ) == NetworkApp::CTRL_PHASE::NAVI_PHASE ) {
		setDir( );
	}
	// モデルの向きを変える
	if ( _warp == true || _warp_stair == true ) {
		rotateByWarp( );
	} else {
		angleChange( );
	}
	// HP超過処理
	if ( _status.life > _status.max_life ) {
		_status.life = _status.max_life;
	}
	// 倒された処理
	dead( );
	// レベルアップ処理
	levelUp( );
	// バフ処理
	statusForBuff( );
	if ( _buff_end == true ) {
		_status.attack = _pre_attack + _equipment[ EQUIPMENT_WEAPON ].attack + _equipment[ EQUIPMENT_RING ].attack;
		_buff_end = false;
	}
}

void Player::updateDraw( ) {
	// エフェクトの描画座標の移動
	_effect->moveDrawPos( _draw_pos + Vector( TILE_SIZE / 2, 0, TILE_SIZE / 2 ), EFFECT_PLAYER_NUM );

	// 描画座標の移動
	move( );

	// UIにデータを送る
	_ui_app->setPlayerStatus( _status );
	_ui_app->setPlayerStamina( _stamina );

	draw( );
	// 斬滅波の描画
	if ( _use_zanmetuha == true ) {
		Vector adjust_pos;
		switch( _status.dir ) {
		case LOWER_LEFT:
			adjust_pos = Vector( TILE_SIZE, 0, TILE_SIZE );
			break;
		case LOWER:
			adjust_pos = Vector( TILE_SIZE / 2, 0, TILE_SIZE );
			break;
		case LOWER_RIGHT:
			adjust_pos = Vector( 0, 0, TILE_SIZE );
			break;
		case LEFT:
			adjust_pos = Vector( TILE_SIZE, 0, TILE_SIZE / 2 );
			break;
		case RIGHT:
			adjust_pos = Vector( 0, 0, TILE_SIZE / 2 );
			break;
		case UPPER_LEFT:
			adjust_pos = Vector( TILE_SIZE, 0, 0 );
			break;
		case UPPER:
			adjust_pos = Vector( TILE_SIZE / 2, 0, 0 );
			break;
		case UPPER_RIGHT:
			adjust_pos = Vector( 0, 0, 0 );
			break;
		}
		_zanmetuha.draw_pos = waveDirMove( _zanmetuha.draw_pos, _zanmetuha.pos, _zanmetuha.pre_draw_pos ) + adjust_pos;
		_effect->moveDrawPos( _zanmetuha.draw_pos, EFFECT_NONE_NUM );
	}
	// effectの更新
	int num = -1;
	switch ( _status.state ) {
		case POISON:
			num = _effect->isPlayEndEffect( Effect::EFFECT_TYPE::EFFECT_POISON, EFFECT_PLAYER_NUM );
			break;
		case PARALYSIS:
			num = _effect->isPlayEndEffect( Effect::EFFECT_TYPE::EFFECT_PARALYSIS, EFFECT_PLAYER_NUM );
			break;
		case SKILL_SEAL:
			num = _effect->isPlayEndEffect( Effect::EFFECT_TYPE::EFFECT_SEALED, EFFECT_PLAYER_NUM );
			break;
		case BIND_TILE:
			num = _effect->isPlayEndEffect( Effect::EFFECT_TYPE::EFFECT_SEALED, EFFECT_PLAYER_NUM );
			break;
		case CONFUSE:
			num = _effect->isPlayEndEffect( Effect::EFFECT_TYPE::EFFECT_CONFUSE, EFFECT_PLAYER_NUM );
			break;
	}
	if ( num != -1 ) {
		_effect->rePlayEffect( _draw_pos + Vector( TILE_SIZE / 2, 0, TILE_SIZE / 2 ), Vector( 0, 0, 0 ), num );
	}

	num = -1;
	switch ( _status.speed ) {
		case SLOW:
			num = _effect->isPlayEndEffect( Effect::EFFECT_TYPE::EFFECT_DEBUFF, EFFECT_PLAYER_NUM );
			break;
		case FAST:
			num = _effect->isPlayEndEffect( Effect::EFFECT_TYPE::EFFECT_BUFF, EFFECT_PLAYER_NUM );
			break;
	}
	if ( num != -1 ) {
		_effect->rePlayEffect( _draw_pos + Vector( TILE_SIZE / 2, 0, TILE_SIZE / 2 ), Vector( 0, 0, 0 ), num );
	}
	
	num = -1;
	switch ( _status.buff ) {
	case DEBUFF:
		num = _effect->isPlayEndEffect( Effect::EFFECT_TYPE::EFFECT_DEBUFF, EFFECT_PLAYER_NUM );
		break;
	case BUFF:
		num = _effect->isPlayEndEffect( Effect::EFFECT_TYPE::EFFECT_BUFF, EFFECT_PLAYER_NUM );
		break;
	}
	if ( num != -1 ) {
		_effect->rePlayEffect( _draw_pos + Vector( TILE_SIZE / 2, 0, TILE_SIZE / 2 ), Vector( 0, 0, 0 ), num );
	}

}

void Player::setMoveDir( ) {
	FrameworkPtr fw = Framework::getInstance( );
	// デバッグ用
	KeyboardPtr keyboard = std::dynamic_pointer_cast< Keyboard >( fw->getTask( typeid( Keyboard ).name( ) ) );
	if ( _status.state == CONFUSE ) {  // 混乱状態
		if ( _network->getInputDir( ) != NetworkApp::CTRL_DIR::NONE || 
			 keyboard->isPushKey( "6" ) || keyboard->isPushKey( "8" ) ||
			 keyboard->isPushKey( "4" ) || keyboard->isPushKey( "2" ) || 
			 keyboard->isPushKey( "7" ) || keyboard->isPushKey( "9" ) || 
			 keyboard->isPushKey( "3" ) || keyboard->isPushKey( "1" ) || 
			 keyboard->isPushKey( "5" ) ) {
			_move_dir = MOVE_DIR( 1 + rand( ) % ( MAX_MOVE_DIR - 1 ) );
		} else {
			_move_dir = MOVE_DIR::MOVE_DIR_NONE;
		}
	} else if ( _status.state == PARALYSIS || _status.state == BIND_TILE ) {  // マヒ状態移動禁止状態のとき
		if ( _network->getInputDir( ) != NetworkApp::CTRL_DIR::NONE || 
			 keyboard->isPushKey( "6" ) || keyboard->isPushKey( "8" ) ||
			 keyboard->isPushKey( "4" ) || keyboard->isPushKey( "2" ) || 
			 keyboard->isPushKey( "7" ) || keyboard->isPushKey( "9" ) || 
			 keyboard->isPushKey( "3" ) || keyboard->isPushKey( "1" ) || 
			 keyboard->isPushKey( "5" ) ) {
			_message->createFont( _name, "", "", 0, MessageLog::MESSAGE_TYPE::NO_MOVE );
			_move_dir = MOVE_DIR::MOVE_DIR_NONE;
			turnEnd( );
		} else {
			_move_dir = MOVE_DIR::MOVE_DIR_NONE;
		}
	} else if ( _speed_abnormal == false && _status.speed == SLOW ) {
		turnEnd( );
	} else {
		if ( ( keyboard->isPushKey( "6" ) || _network->getInputDir( ) == NetworkApp::CTRL_DIR::RIGHT ) ) {
			_move_dir = RIGHT;
		} else if ( ( keyboard->isPushKey( "8" ) || _network->getInputDir( ) == NetworkApp::CTRL_DIR::UPPER ) ) {
			_move_dir = UPPER;
		} else if ( ( keyboard->isPushKey( "4" ) || _network->getInputDir( ) == NetworkApp::CTRL_DIR::LEFT ) ) {
			_move_dir = LEFT;
		} else if ( ( keyboard->isPushKey( "2" ) || _network->getInputDir( ) == NetworkApp::CTRL_DIR::LOWER ) ) {
			_move_dir = LOWER;
		} else if ( ( ( keyboard->isPushKey( "7" ) || _network->getInputDir( ) == NetworkApp::CTRL_DIR::UPPER_LEFT ) ) ) {
			_move_dir = UPPER_LEFT;
		} else if ( ( keyboard->isPushKey( "9" ) || _network->getInputDir( ) == NetworkApp::CTRL_DIR::UPPER_RIGHT ) ) {
			_move_dir = UPPER_RIGHT;
		} else if ( ( keyboard->isPushKey( "3" ) || _network->getInputDir( ) == NetworkApp::CTRL_DIR::LOWER_RIGHT ) ) {
			_move_dir = LOWER_RIGHT;
		} else if ( ( keyboard->isPushKey( "1" ) || _network->getInputDir( ) == NetworkApp::CTRL_DIR::LOWER_LEFT ) ) {
			_move_dir = LOWER_LEFT;
		} else if ( ( keyboard->isPushKey( "5" ) || _network->getInputDir( ) == NetworkApp::CTRL_DIR::WAIT ) ) {
			_move_dir = WAIT;
		} else {
			_move_dir = MOVE_DIR::MOVE_DIR_NONE;
		}
	}
}

void Player::setDir( ) {
	FrameworkPtr fw = Framework::getInstance( );
	// デバッグ用
	KeyboardPtr keyboard = std::dynamic_pointer_cast< Keyboard >( fw->getTask( typeid( Keyboard ).name( ) ) );

	if ( _status.state == PARALYSIS || _status.state == BIND_TILE ) {  // マヒ状態移動禁止状態のとき
		if ( _network->getInputDir( ) != NetworkApp::CTRL_DIR::NONE || 
			 keyboard->isPushKey( "6" ) || keyboard->isPushKey( "8" ) ||
			 keyboard->isPushKey( "4" ) || keyboard->isPushKey( "2" ) || 
			 keyboard->isPushKey( "7" ) || keyboard->isPushKey( "9" ) || 
			 keyboard->isPushKey( "3" ) || keyboard->isPushKey( "1" ) || 
			 keyboard->isPushKey( "5" ) ) {
			_message->createFont( _name, "", "", 0, MessageLog::MESSAGE_TYPE::NO_MOVE );
		}
	} else {
		if ( ( keyboard->isPushKey( "6" ) || _network->getInputDir( ) == NetworkApp::CTRL_DIR::RIGHT ) ) {
			_status.dir = MOVE_DIR::RIGHT;
		} else if ( ( keyboard->isPushKey( "8" ) || _network->getInputDir( ) == NetworkApp::CTRL_DIR::UPPER ) ) {
			_status.dir = MOVE_DIR::UPPER;
		} else if ( ( keyboard->isPushKey( "4" ) || _network->getInputDir( ) == NetworkApp::CTRL_DIR::LEFT ) ) {
			_status.dir = MOVE_DIR::LEFT;
		} else if ( ( keyboard->isPushKey( "2" ) || _network->getInputDir( ) == NetworkApp::CTRL_DIR::LOWER ) ) {
			_status.dir = MOVE_DIR::LOWER;
		} else if ( ( ( keyboard->isPushKey( "7" ) || _network->getInputDir( ) == NetworkApp::CTRL_DIR::UPPER_LEFT ) ) ) {
			_status.dir = MOVE_DIR::UPPER_LEFT;
		} else if ( ( keyboard->isPushKey( "9" ) || _network->getInputDir( ) == NetworkApp::CTRL_DIR::UPPER_RIGHT ) ) {
			_status.dir = MOVE_DIR::UPPER_RIGHT;
		} else if ( ( keyboard->isPushKey( "3" ) || _network->getInputDir( ) == NetworkApp::CTRL_DIR::LOWER_RIGHT ) ) {
			_status.dir = MOVE_DIR::LOWER_RIGHT;
		} else if ( ( keyboard->isPushKey( "1" ) || _network->getInputDir( ) == NetworkApp::CTRL_DIR::LOWER_LEFT ) ) {
			_status.dir = MOVE_DIR::LOWER_LEFT;
		}
	}
}

void Player::setMovePos( ) {
	if ( _attakking == false && isWalking( ) == false ) {
		if ( _move_dir == RIGHT ) {
			_status.dir = RIGHT;
			// 移動先をチェック
			if ( okMove( _pos.x - 1, _pos.y ) == true ) {
				_floor->setBondNone( _pos.x, _pos.y );
				_pos.x--;
				settingForWalk( );
			}
		} else if ( _move_dir == UPPER ) {
			_status.dir = UPPER;
			// 移動先をチェック
			if ( okMove( _pos.x, _pos.y - 1 ) == true ) {
				_floor->setBondNone( _pos.x, _pos.y );
				_pos.y--;
				settingForWalk( );
			}
		} else if ( _move_dir == LEFT ) {
			_status.dir = LEFT;
			// 移動先をチェック
			if ( okMove( _pos.x + 1, _pos.y ) == true ) {
				_floor->setBondNone( _pos.x, _pos.y );
				_pos.x++;
				settingForWalk( );
			}
		} else if ( _move_dir == LOWER ) {
			_status.dir = LOWER;
			// 移動先をチェック
			if ( okMove( _pos.x, _pos.y + 1 ) == true ) {
				_floor->setBondNone( _pos.x, _pos.y );
				_pos.y++;
				settingForWalk( );
			}
		} else if ( _move_dir == UPPER_LEFT ) {
			_status.dir = UPPER_LEFT;
			// 移動先をチェック
			if ( okMove( _pos.x + 1, _pos.y - 1 ) == true && isNotCornerWall( _pos ) == true ) {
				_floor->setBondNone( _pos.x, _pos.y );
				_pos.x++;
				_pos.y--;
				settingForWalk( );
			}
		} else if ( _move_dir == UPPER_RIGHT ) {
			_status.dir = UPPER_RIGHT;
			// 移動先をチェック
			if ( okMove( _pos.x - 1, _pos.y - 1 ) == true && isNotCornerWall( _pos ) == true ) {
				_floor->setBondNone( _pos.x, _pos.y );
				_pos.x--;
				_pos.y--;
				settingForWalk( );
			}
		} else if ( _move_dir == LOWER_RIGHT ) {
			_status.dir = LOWER_RIGHT;
			// 移動先をチェック
			if ( okMove( _pos.x - 1, _pos.y + 1 ) == true && isNotCornerWall( _pos ) == true ) {
				_floor->setBondNone( _pos.x, _pos.y );
				_pos.x--;
				_pos.y++;
				settingForWalk( );
			}
		} else if ( _move_dir == LOWER_LEFT ) {
			_status.dir = LOWER_LEFT;
			// 移動先をチェック
			if ( okMove( _pos.x + 1, _pos.y + 1 ) == true && isNotCornerWall( _pos ) == true ) {
				_floor->setBondNone( _pos.x, _pos.y );
				_pos.x++;
				_pos.y++;
				settingForWalk( );
			}
		}
		else if ( _move_dir == WAIT ) {
			_move_dir = MOVE_DIR_NONE;
			hunger( );
			fluctuationHPForStamina( );
			turnEnd( );
		}
	}
}

bool Player::okMove( int x, int y ) {
	if ( _floor->getTile( x, y ).type != Floor::TYPE::WALL &&
		 _floor->getTile( x, y ).bond != Floor::BOND::ENEMY ) {
		return true;
	}
	return false;
}

void Player::settingForWalk( ) {
	NetworkApp::FOOT_THING foot = NetworkApp::FOOT_THING::FOOT_NONE;

	// アニメーション
	walkAnim( );
	// 移動先をネットワークに送る
	_network->setSendChipData( NetworkApp::MAP_CHIP_TYPE::PLAYER, _pos, 0, false );
	// 移動先のタイルをプレイヤーのタイルに指定
	_floor->setBondPlayer( _pos.x, _pos.y );
	// おなかの処理
	hunger( );
	// 落ちているアイテムに対してのアクションを行ったか
	if ( _floor->getTile( _pos.x, _pos.y ).item_exist == true ) {
		foot = NetworkApp::FOOT_THING::FOOT_ITEM;
		_item->abovePlayer( _pos.x, _pos.y );
	}
	// 階段があるかどうか
	else if ( _floor->getTile( _pos.x, _pos.y ).stair_exist == true ) {
		foot = NetworkApp::FOOT_THING::FOOT_STAIR;
		_floor->onStair( );
		_ui_app->setStairWindow( true );
	}
	// 罠があるかどうか
	else if ( _floor->getTile( _pos.x, _pos.y ).myistery_type != Floor::MYSTERY_TILE::NONE_MISTERY ) {
		_floor->visibleTrap( _pos.x, _pos.y );
		stepMysteryTile( );
		foot = NetworkApp::FOOT_THING::FOOT_TRAP;
		_network->setSendFoot( foot, true );
	} else {
		_network->setSendFoot( foot, false );
	}
	if ( _floor->getTile( _pos.x, _pos.y ).myistery_type != Floor::MYSTERY_TILE::WARP_TRAP ) {
		// ターン終了
		turnEnd( );
	}

	
}

void Player::walkAnim( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	_walking = true;
	fluctuationHPForStamina( );
	// 元いたタイルを初期化
	_floor->setBondNone( _pos.x, _pos.y );
	// 元いた座標を記憶
	_pre_pos = _draw_pos;
	// アニメーションの初期化
	viewer->dettachAnim( _anim_hundle.model, _anim_index.stay );
	_anim_play_time = 0.0f;
	_anim_count = 0;
	_anim_index.walk = viewer->attachAnim( _anim_hundle.model, 0, _anim_hundle.walk );
	_main_anim = _anim_index.walk;
	_anim_state = WALK_ANIM;
}

void Player::stepMysteryTile( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	SoundPtr sound   = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );

	if ( _equipment[ EQUIPMENT_RING ].id != ITEM_ID::RING6 ) {
		switch ( _floor->getTile( _pos.x, _pos.y ).myistery_type ) {
		case Floor::MYSTERY_TILE::POISON_TRAP:
			_message->createFont ( "どくの罠", "", "", 0, MessageLog::STEP_MYSTERY );
			if ( isEquipmentRing4( ) == false ) {
				becomeAbnormalState( STATE::POISON, EFFECT_PLAYER_NUM );
			} else {
				_message->createFont ( _name, "", "", 0, MessageLog::PROTECT_ABNORMAL );
			}
			break;
		case Floor::MYSTERY_TILE::PARALYSIS_TRAP:
			_message->createFont ( "まひの罠", "", "", 0, MessageLog::STEP_MYSTERY );
			if ( isEquipmentRing4( ) == false ) {
				becomeAbnormalState( PARALYSIS, EFFECT_PLAYER_NUM );
			} else {
				_message->createFont ( _name, "", "", 0, MessageLog::PROTECT_ABNORMAL );
			}
			break;
		case Floor::MYSTERY_TILE::SKILL_SEAL_TRAP:
			_message->createFont ( "わざ封印の罠", "", "", 0, MessageLog::STEP_MYSTERY );
			if ( isEquipmentRing4( ) == false ) {
				becomeAbnormalState( SKILL_SEAL, EFFECT_PLAYER_NUM );
			} else {
				_message->createFont ( _name, "", "", 0, MessageLog::PROTECT_ABNORMAL );
			}
			break;
		case Floor::MYSTERY_TILE::SLOW_TRAP:
			_message->createFont ( "どんそくの罠", "", "", 0, MessageLog::STEP_MYSTERY );
			changeSpeedState( SLOW, EFFECT_PLAYER_NUM );
			break;
		case Floor::MYSTERY_TILE::CONFUSE_TRAP:
			_message->createFont ( "こんらんの罠", "", "", 0, MessageLog::STEP_MYSTERY );
			if ( isEquipmentRing4( ) == false ) {
				becomeAbnormalState( CONFUSE, EFFECT_PLAYER_NUM );
			} else {
				_message->createFont ( _name, "", "", 0, MessageLog::PROTECT_ABNORMAL );
			}
			break;
		case Floor::MYSTERY_TILE::WARP_TRAP:
			_message->createFont ( "ワープの罠", "", "", 0, MessageLog::STEP_MYSTERY );
			warpStart( EFFECT_PLAYER_NUM );
			break;
		case Floor::MYSTERY_TILE::RETURN_TRAP:
			_message->createFont ( "落とし穴の罠", "", "", 0, MessageLog::STEP_MYSTERY );
			_return_start = true;
			break;
		case Floor::MYSTERY_TILE::DAMGE_TRAP:
			{
				_message->createFont ( "まきびしの罠", "", "", 0, MessageLog::STEP_MYSTERY );
				int damage = _status.max_life / 8;
				setTrapDamage( damage );
			}
				break;
		}
		sound->playSound( Sound::ATTACK, false );
	} 

	switch ( _floor->getTile( _pos.x, _pos.y ).myistery_type ) {
	case Floor::MYSTERY_TILE::ALCHEMY_POINT:
		_message->createFont ( "錬金ポイントタイル", "", "", 0, MessageLog::STEP_MYSTERY );
		_message->createFont ( "", "", "", 0, MessageLog::STEP_ALCKEMY );
		_network->setSendFoot( NetworkApp::FOOT_THING::FOOT_ALCHEMY, true );
		_floor->breakMysteryTile( ( int )_pos.x, ( int )_pos.y );
		_network->setSendFoot( NetworkApp::FOOT_THING::FOOT_NONE, false );
		break;
	}
}

void Player::attack( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	SoundPtr sound = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );

	if ( ( _network->isAttack( ) || pushSpace( ) ) && _attakking == false ) {
		// マヒ状態のとき
		if ( _status.state == PARALYSIS ) {
			turnEnd( );
		} else {
			sound->backgrondPlaySound( Sound::ATTACK );
			// 罠の発見
			visibleMysteryForDir( );
			// 混乱時自身の方向をランダムにする
			randDirForConfuse( );
			// アニメーションの初期化
			viewer->dettachAnim( _anim_hundle.model, _anim_index.stay );
			_anim_play_time = 0.0f;
			_anim_count = 0;
			// アニメーションのアタッチ
			_anim_index.attack = viewer->attachAnim( _anim_hundle.model, 0, _anim_hundle.attack );
			_main_anim = _anim_index.attack;
			_anim_state = ATTACK_ANIM;
			_total_time = viewer->animTotalTime( _anim_hundle.model, _main_anim );
			_attack_time = _total_time;
			// おなかの処理
			hunger( );
			// 歩き状態を解除
			_walking = false;
			// 攻撃状態を設定
			_attakking = true;
			if ( isNotCornerWall( _pos ) == true ) {
				_attacked = true;
			}
		}
	}
	// ターン終了
	if ( _anim_play_time >= _attack_time && _attakking == true ) {
		turnEnd( );
		_attakking = false;
	}
}

void Player::visibleMysteryForDir( ) {
	switch( _status.dir ) {
	case LOWER_LEFT:
		_floor->visibleTrap( ( int )_pos.x + 1, ( int )_pos.y + 1 );
		break;
	case LOWER:
		_floor->visibleTrap( ( int )_pos.x, ( int )_pos.y + 1 );
		break;
	case LOWER_RIGHT:
		_floor->visibleTrap( ( int )_pos.x - 1, ( int )_pos.y + 1 );
		break;
	case LEFT:
		_floor->visibleTrap( ( int )_pos.x + 1, ( int )_pos.y );
		break;
	case RIGHT:
		_floor->visibleTrap( ( int )_pos.x - 1, ( int )_pos.y );
		break;
	case UPPER_LEFT:
		_floor->visibleTrap( ( int )_pos.x + 1, ( int )_pos.y - 1 );
		break;
	case UPPER:
		_floor->visibleTrap( ( int )_pos.x, ( int )_pos.y - 1 );
		break;
	case UPPER_RIGHT:
		_floor->visibleTrap( ( int )_pos.x - 1, ( int )_pos.y - 1 );
		break;
	}
}

void Player::skillAttack( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	KeyboardPtr keyboard = std::dynamic_pointer_cast< Keyboard >( fw->getTask( typeid( Keyboard ).name( ) ) );   // デバッグ用
	SoundPtr sound = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );

	if ( ( _network->isMagicAttack( ) || keyboard->isPushKey( "W" ) ) && _attakking == false ) {
		// マヒ状態のとき
		if ( _status.state == PARALYSIS ) {
			turnEnd( );
		} else if ( _status.state == SKILL_SEAL ) {  // スキル封印
			_message->createFont( "", "", "", 0, MessageLog::SEAL_WAZA );
		} else {
			// 混乱時自身の方向をランダムにする
			randDirForConfuse( );
			// アニメーションの初期化
			viewer->dettachAnim( _anim_hundle.model, _anim_index.stay );
			_anim_play_time = 0.0f;
			_anim_count = 0;
			// アニメーションのアタッチ
			_anim_index.attack = viewer->attachAnim( _anim_hundle.model, 0, _anim_hundle.attack );
			_main_anim = _anim_index.attack;
			_anim_state = ATTACK_ANIM;
			// アニメーションの時間を設定
			_total_time = viewer->animTotalTime( _anim_hundle.model, _main_anim );
			_attack_time = _total_time;
			hunger( );
			// 歩き状態を解除
			_walking = false;
		
			Vector adjust_pos;
			Vector rotate;
			if ( _network->getSkillID( ) == SKILL_ID::ZANGEKI || keyboard->isPushKey( "ONE" ) ) {
				if ( _stamina > CONSUMPTION_STAMINA_FOR_SKILL_1 && isNotCornerWall( _pos ) == true ) {
					_zanmetuha.hit_enemy = false;
					setSkillPosAndRotate( &adjust_pos, &rotate );
					_effect->playEffect( Effect::EFFECT_TYPE::EFFECT_SKILL1, _draw_pos + adjust_pos, rotate, EFFECT_PLAYER_NUM );
					settingForUseSkill( CONSUMPTION_STAMINA_FOR_SKILL_1, DAMAGE_SKILL_1 );
					_skill_attacked = true;
					sound->backgrondPlaySound( Sound::ZANGEKI );
					_message->createFont( _name, "斬撃", "", 0, MessageLog::MESSAGE_TYPE::USE_WAZA );
				} else {
					_message->createFont( "", "斬撃", "", 0, MessageLog::MESSAGE_TYPE::FAILURE_WAZA );
				}
				_use_zanmetuha     = false;
				_use_materia_sword = false;
				// ターン終了
				turnEnd( );
			} else if ( _network->getSkillID( ) == SKILL_ID::ZANMETUHA || keyboard->isPushKey( "TWO" ) ) {
				if ( _stamina > CONSUMPTION_STAMINA_FOR_SKILL_2 ) {
					setSkillPosAndRotate( &adjust_pos, &rotate );
					_effect->playEffect( Effect::EFFECT_TYPE::EFFECT_SKILL2, _draw_pos + adjust_pos, rotate, EFFECT_NONE_NUM );
					settingForUseSkill( CONSUMPTION_STAMINA_FOR_SKILL_2, DAMAGE_SKILL_2 );
					// 斬滅波の描画位置をセット
					_zanmetuha.draw_pos = _draw_pos;
					_zanmetuha.pre_draw_pos = _zanmetuha.draw_pos;
					_zanmetuha.pos = _pos;
					// プレイヤーの向きによって飛ばす方向を変える
					void ( Player::* funcArray[ ] )( MOVE_SKILL_DATA * ) = {
						&Player::waveDirNone,
						&Player::waveDirLowerLeft,
						&Player::waveDirLower,
						&Player::waveDirLowerRight,
						&Player::waveDirLeft,
						&Player::waveDirWait,
						&Player::waveDirRight,
						&Player::waveDirUpperLeft,
						&Player::waveDirUpper,
						&Player::waveDirUpperRight,
					};
					void ( Player::* func )( MOVE_SKILL_DATA* ) = funcArray[ _status.dir ];
					( this->*func )( &_zanmetuha );
					_use_zanmetuha     = true;
					_use_materia_sword = false;
					_message->createFont( _name, "斬滅波", "", 0, MessageLog::MESSAGE_TYPE::USE_WAZA );
					sound->backgrondPlaySound( Sound::ZANGEKI );
				} else {
					_message->createFont( "", "斬滅波", "", 0, MessageLog::MESSAGE_TYPE::FAILURE_WAZA );
				}
			}
			else if ( _network->getSkillID( ) == SKILL_ID::MATERIASWORD || keyboard->isPushKey( "THREE" ) ) {
				if ( _stamina > CONSUMPTION_STAMINA_FOR_SKILL_3 && isNotCornerWall( _pos ) == true ) {
					settingForUseSkill( CONSUMPTION_STAMINA_FOR_SKILL_3, DAMAGE_SKILL_3 );
					_zanmetuha.hit_enemy = false;
					_skill_attacked = true;
					_message->createFont( _name, "マテリアソード", "", 0, MessageLog::MESSAGE_TYPE::USE_WAZA );
					sound->backgrondPlaySound( Sound::ZANGEKI );
					_use_materia_sword = true;
					_use_zanmetuha     = false;
				}  else {
					_message->createFont( "", "マテリアソード", "", 0, MessageLog::MESSAGE_TYPE::FAILURE_WAZA );
				}
				// ターン終了
				turnEnd( );
			}
			else if ( _network->getSkillID( ) == SKILL_ID::SPEED_UP || keyboard->isPushKey( "FOUR" ) )  {
				if ( _stamina > CONSUMPTION_STAMINA_FOR_SKILL_4 && isNotCornerWall( _pos ) == true ) {
					_effect->playEffect( Effect::EFFECT_TYPE::EFFECT_WIND,  _draw_pos + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), EFFECT_PLAYER_NUM );
					settingForUseSkill( CONSUMPTION_STAMINA_FOR_SKILL_4, 0 );
					_zanmetuha.hit_enemy = false;
					_skill_attacked = false;
					_message->createFont( _name, "疾風の加護", "", 0, MessageLog::MESSAGE_TYPE::USE_WAZA );
					sound->backgrondPlaySound( Sound::SPEED_UP );
					_use_materia_sword = false;
					_use_zanmetuha     = false;
					changeSpeedState( FAST, EFFECT_PLAYER_NUM );
				}  else {
					_message->createFont( "", "疾風の加護", "", 0, MessageLog::MESSAGE_TYPE::FAILURE_WAZA );
				}
				// ターン終了
				turnEnd( );
			}
		}
	}
}

void Player::setSkillPosAndRotate( Vector* pos, Vector* rotate ) {
	switch( _status.dir ) {
	case LOWER_LEFT:
		*pos    = Vector( TILE_SIZE, TILE_SIZE / 2, TILE_SIZE );
		*rotate = Vector( 0, 45, 0 );
		break;
	case LOWER:
		*pos    = Vector( TILE_SIZE / 2, TILE_SIZE / 2, TILE_SIZE );
		*rotate = Vector( 0, 0, 0 );
		break;
	case LOWER_RIGHT:
		*pos    = Vector( 0, TILE_SIZE / 2, TILE_SIZE );
		*rotate = Vector( 0, -45, 0 );
		break;
	case LEFT:
		*pos    = Vector( TILE_SIZE, TILE_SIZE / 2, TILE_SIZE / 2 );
		*rotate = Vector( 0, 90, 0 );
		break;
	case RIGHT:
		*pos    = Vector( 0, TILE_SIZE / 2, TILE_SIZE / 2 );
		*rotate = Vector( 0, -90, 0 );
		break;
	case UPPER_LEFT:
		*pos    = Vector( TILE_SIZE, TILE_SIZE / 2, 0 );
		*rotate = Vector( 0, 135, 0 );
		break;
	case UPPER:
		*pos    = Vector( TILE_SIZE / 2, TILE_SIZE / 2, 0 );
		*rotate = Vector( 0, 180, 0 );
		break;
	case UPPER_RIGHT:
		*pos    = Vector( 0, TILE_SIZE / 2, 0 );
		*rotate = Vector( 0, -135, 0 );
		break;
	}
}

void Player::settingForUseSkill( int consumption_stamina, float damage_magnification ) {
	_ui_app->setFluctuationStamina( true );
	_skill_attack_damage = ( int )( _status.attack * damage_magnification );
	_stamina -= consumption_stamina;
}

void Player::waveDirNone( Player::MOVE_SKILL_DATA *skill ) {
	return;
}

void Player::waveDirLowerLeft( Player::MOVE_SKILL_DATA *skill ) {
	MOVE_SKILL_DATA provisional_skill = *skill;
	int x = ( int )_pos.x;
	int y = ( int )_pos.y;
	int pre_x = x;
	int pre_y = y;

	while ( true ) {
		x++;
		y++;
		// 投げる距離が限界に達したとき
		if ( x - pre_x > LIMIT_ZANMETUHA_DIS ) {
			provisional_skill.pos.x = x - 1;
			provisional_skill.pos.y = y - 1;
			break;
		}
		// エネミーにぶつかった場合
		if ( _floor->getTile( x, y ).bond == Floor::BOND::ENEMY ) {
			provisional_skill.pos.x = x;
			provisional_skill.pos.y = y;
			break;
		}
		// 壁にぶつかった場合
		if ( _floor->getTile( x, y ).type == Floor::TYPE::WALL ) {
			provisional_skill.pos.x = x - 1;
			provisional_skill.pos.y = y - 1;
			break;
		}
	}
	*skill = provisional_skill;
}

void Player::waveDirLower( Player::MOVE_SKILL_DATA *skill ) {
	MOVE_SKILL_DATA provisional_skill = *skill;
	int x = ( int )_pos.x;
	int y = ( int )_pos.y;
	int pre_y = y;

	while ( true ) {
		y++;
		// 投げる距離が限界に達したとき
		if ( y - pre_y > LIMIT_ZANMETUHA_DIS ) {
			provisional_skill.pos.y = y - 1;
			break;
		}
		// エネミーにぶつかった場合
		if ( _floor->getTile( x, y ).bond == Floor::BOND::ENEMY ) {
			provisional_skill.pos.y = y;
			break;
		}
		// 壁にぶつかった場合
		if ( _floor->getTile( x, y ).type == Floor::TYPE::WALL ) {
			provisional_skill.pos.y = y - 1;
			break;
		}
	}
	*skill = provisional_skill;
}

void Player::waveDirLowerRight( Player::MOVE_SKILL_DATA *skill ) {
	MOVE_SKILL_DATA provisional_skill = *skill;
	int x = ( int )_pos.x;
	int y = ( int )_pos.y;
	int pre_x = x;
	int pre_y = y;

	while ( true ) {
		x--;
		y++;
		// 投げる距離が限界に達したとき
		if ( pre_x - x > LIMIT_ZANMETUHA_DIS ) {
			provisional_skill.pos.x = x + 1;
			provisional_skill.pos.y = y - 1;
			break;
		}
		// エネミーにぶつかった場合
		if ( _floor->getTile( x, y ).bond == Floor::BOND::ENEMY ) {
			provisional_skill.pos.x = x;
			provisional_skill.pos.y = y;
			break;
		}
		// 壁にぶつかった場合
		if ( _floor->getTile( x, y ).type == Floor::TYPE::WALL ) {
			provisional_skill.pos.x = x + 1;
			provisional_skill.pos.y = y - 1;
			break;
		}
	}
	*skill = provisional_skill;
}

void Player::waveDirLeft( Player::MOVE_SKILL_DATA *skill ) {
	MOVE_SKILL_DATA provisional_skill = *skill;
	int x = ( int )_pos.x;
	int y = ( int )_pos.y;
	int pre_x = x;

	while ( true ) {
		x++;
		// 投げる距離が限界に達したとき
		if ( x - pre_x > LIMIT_ZANMETUHA_DIS ) {
			provisional_skill.pos.x = x - 1;
			break;
		}
		// エネミーにぶつかった場合
		if ( _floor->getTile( x, y ).bond == Floor::BOND::ENEMY ) {
			provisional_skill.pos.x = x;
			break;
		}
		// 壁にぶつかった場合
		if ( _floor->getTile( x, y ).type == Floor::TYPE::WALL ) {
			provisional_skill.pos.x = x - 1;
			break;
		}
	}
	*skill = provisional_skill;
}

void Player::waveDirWait( Player::MOVE_SKILL_DATA *skill ) {
	return;
}

void Player::waveDirRight( Player::MOVE_SKILL_DATA *skill ) {
	MOVE_SKILL_DATA provisional_skill = *skill;
	int x = ( int )_pos.x;
	int y = ( int )_pos.y;
	int pre_x = x;

	while ( true ) {
		x--;
		// 投げる距離が限界に達したとき
		if ( pre_x - x > LIMIT_ZANMETUHA_DIS ) {
			provisional_skill.pos.x = x + 1;
			break;
		}
		// エネミーにぶつかった場合
		if ( _floor->getTile( x, y ).bond == Floor::BOND::ENEMY ) {
			provisional_skill.pos.x = x;
			break;
		}
		// 壁にぶつかった場合
		if ( _floor->getTile( x, y ).type == Floor::TYPE::WALL ) {
			provisional_skill.pos.x = x + 1;
			break;
		}
	}
	*skill = provisional_skill;
}

void Player::waveDirUpperLeft( Player::MOVE_SKILL_DATA *skill ) {
	MOVE_SKILL_DATA provisional_skill = *skill;
	int x = ( int )_pos.x;
	int y = ( int )_pos.y;
	int pre_x = x;
	int pre_y = y;

	while ( true ) {
		x++;
		y--;
		// 投げる距離が限界に達したとき
		if ( x - pre_x > LIMIT_ZANMETUHA_DIS ) {
			provisional_skill.pos.x = x - 1;
			provisional_skill.pos.y = y + 1;
			break;
		}
		// エネミーにぶつかった場合
		if ( _floor->getTile( x, y ).bond == Floor::BOND::ENEMY ) {
			provisional_skill.pos.x = x;
			provisional_skill.pos.y = y;
			break;
		}
		// 壁にぶつかった場合
		if ( _floor->getTile( x, y ).type == Floor::TYPE::WALL ) {
			provisional_skill.pos.x = x - 1;
			provisional_skill.pos.y = y + 1;
			break;
		}
	}
	*skill = provisional_skill;
}

void Player::waveDirUpper( Player::MOVE_SKILL_DATA *skill ) {
	MOVE_SKILL_DATA provisional_skill = *skill;
	int x = ( int )_pos.x;
	int y = ( int )_pos.y;
	int pre_y = y;

	while ( true ) {
		y--;
		// 投げる距離が限界に達したとき
		if ( pre_y - y > LIMIT_ZANMETUHA_DIS ) {
			provisional_skill.pos.y = y + 1;
			break;
		}
		// エネミーにぶつかった場合
		if ( _floor->getTile( x, y ).bond == Floor::BOND::ENEMY ) {
			provisional_skill.pos.y = y;
			break;
		}
		// 壁にぶつかった場合
		if ( _floor->getTile( x, y ).type == Floor::TYPE::WALL ) {
			provisional_skill.pos.y = y + 1;
			break;
		}
	}
	*skill = provisional_skill;
}

void Player::waveDirUpperRight( Player::MOVE_SKILL_DATA *skill ) {
	MOVE_SKILL_DATA provisional_skill = *skill;
	int x = ( int )_pos.x;
	int y = ( int )_pos.y;
	int pre_x = x;
	int pre_y = y;

	while ( true ) {
		x--;
		y--;
		// 投げる距離が限界に達したとき
		if ( pre_x - x > LIMIT_ZANMETUHA_DIS ) {
			provisional_skill.pos.x = x + 1;
			provisional_skill.pos.y = y + 1;
			break;
		}
		// エネミーにぶつかった場合
		if ( _floor->getTile( x, y ).bond == Floor::BOND::ENEMY ) {
			provisional_skill.pos.x = x;
			provisional_skill.pos.y = y;
			break;
		} 
		// 壁にぶつかった場合
		if ( _floor->getTile( x, y ).type == Floor::TYPE::WALL ) {
			provisional_skill.pos.x = x + 1;
			provisional_skill.pos.y = y + 1;
			break;
		}
	}
	*skill = provisional_skill;
}

Vector Player::waveDirMove( Vector draw_pos, Vector2 pos, Vector pre_pos ) {
	// 移動先のベクトル
	int move_x = ( pos.x * TILE_SIZE - _pre_pos.x ) / WALK_ANIM_TIME * 2;
	int move_z = ( pos.y * TILE_SIZE - _pre_pos.z ) / WALK_ANIM_TIME * 2;
	if ( move_x > 0 ) {  // 左
		// 徐々に動かす
		draw_pos.x += move_x;
		// 目的地を過ぎたら目的地に座標をセット
		if ( draw_pos.x > pos.x * TILE_SIZE ) {
			draw_pos.x = pos.x * TILE_SIZE;
			pre_pos.x  = pos.x * TILE_SIZE;
		}
	} else if ( move_x < 0 ) {   // 右
		// 徐々に動かす
		draw_pos.x += move_x;
		// 目的地を過ぎたら目的地に座標をセット
		if ( draw_pos.x < pos.x * TILE_SIZE ) {
			draw_pos.x = pos.x * TILE_SIZE;
			pre_pos.x  = pos.x * TILE_SIZE;
		}
	} else {   // 同座標軸の場合
		draw_pos.x = pos.x * TILE_SIZE;
		pre_pos.x  = pos.x * TILE_SIZE;
	}
	
	if ( move_z > 0 ) {  // 上
		// 徐々に動かす
		draw_pos.z += move_z;
		// 目的地を過ぎたら目的地に座標をセット
		if ( draw_pos.z > pos.y * TILE_SIZE ) {
			draw_pos.z = pos.y * TILE_SIZE;
			pre_pos.z  = pos.y * TILE_SIZE;
		}
	} else if ( move_z < 0 ) {  // 下
		// 徐々に動かす
		draw_pos.z += move_z;
		// 目的地を過ぎたら目的地に座標をセット
		if ( draw_pos.z < pos.y * TILE_SIZE ) {
			draw_pos.z = pos.y * TILE_SIZE;
			pre_pos.z  = pos.y * TILE_SIZE;
		}
	} else {  // 同座標軸の場合
		draw_pos.z = pos.y * TILE_SIZE;
		pre_pos.z  = pos.y * TILE_SIZE;
	}
	// 目的地に着いたら諸々の設定
	if ( draw_pos.x == pos.x * TILE_SIZE && draw_pos.z == pos.y * TILE_SIZE ) {
		_use_zanmetuha   = false;
		_skill_attacked  = true;
		_hit_enemy_pos.x = pos.x;
		_hit_enemy_pos.y = pos.y;
		if ( _floor->getTile( ( int )pos.x, ( int )pos.y ).bond == Floor::ENEMY ) {
			_zanmetuha.hit_enemy = true;
			int num = rand( ) % 100;

			if ( num < BUFF_FOR_SKILL_2 ) {
				changeBuffState( BUFF, EFFECT_PLAYER_NUM );
			}
		}
		// ターン終了
		turnEnd( );
	}
	
	return draw_pos;
}

void Player::itemAction( ) {
	_item->itemAction( _status.dir );
	// 使う
	if ( _network->getItemAction( ) == NetworkApp::ITEM_ACTION::USE ) {
		useItem( );
	}
	// 置く
	else if ( _network->getItemAction( ) == NetworkApp::ITEM_ACTION::PUT ) {
		turnEnd( );
	}
	// 装備
	else if ( _network->getItemAction( ) == NetworkApp::ITEM_ACTION::EQUIPMENT ) {
		equipmentItem( );
		_weapon_change = true;
		turnEnd( );
	}
	// 装備を外す
	else if ( _network->getItemAction( ) == NetworkApp::ITEM_ACTION::DISARM ) {
		disArmItem( );
		turnEnd( );
	}
	// 投げる
	else if ( _network->getItemAction( ) == NetworkApp::ITEM_ACTION::THROW ) {
		// 混乱時自身の方向をランダムにする
		randDirForConfuse( );

		_item->throwItem( _status.dir );
		_message->createFont( "", "", _network->getItemType( ).name, 0, MessageLog::MESSAGE_TYPE::THROW_ITEM );
	}
	if ( _item->isTurnEnd( ) ) {
		turnEnd( );
		_item->setTurnEnd( false );
	}
}

void Player::useItem( ) {
	// メッセージ
	_message->createFont( "", "", _network->getItemType( ).name, 0, MessageLog::MESSAGE_TYPE::USE_ITEM );
	if ( _network->getItemType( ).id == ITEM_ID::HERB1 ) {  // 薬草
		_effect->playEffect( Effect::EFFECT_TYPE::EFFECT_HEAL, _draw_pos + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), EFFECT_PLAYER_NUM );
		recoverlyForItem( RECOVERLY_POWER_HERB_1, true );
		recoverlyForItem( NORMAL_STAMINA_RECOVERLY_POWER, false );
		_ui_app->setFluctuationStamina( true );
		turnEnd( );
	} 
	else if ( _network->getItemType( ).id == HERB2 ) {  // 上薬草
		_effect->playEffect( Effect::EFFECT_TYPE::EFFECT_HEAL, _draw_pos + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), EFFECT_PLAYER_NUM );
		recoverlyForItem( RECOVERLY_POWER_HERB_2, true );
		recoverlyForItem( NORMAL_STAMINA_RECOVERLY_POWER, false );
		_ui_app->setFluctuationStamina( true );
		turnEnd( );
	} 
	else if ( _network->getItemType( ).id == HERB3 ) {  // 特上薬草
		_effect->playEffect( Effect::EFFECT_TYPE::EFFECT_HEAL, _draw_pos + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), EFFECT_PLAYER_NUM );
		recoverlyForItem( RECOVERLY_POWER_HERB_3, true );
		recoverlyForItem( NORMAL_STAMINA_RECOVERLY_POWER, false );
		_ui_app->setFluctuationStamina( true );
		turnEnd( );
	}  
	else if ( _network->getItemType( ).id == HERB5 ) {  // なおり草
		_effect->playEffect( Effect::EFFECT_TYPE::EFFECT_HEAL, _draw_pos + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), EFFECT_PLAYER_NUM );
		refreshState( );
		recoverlyForItem( NORMAL_STAMINA_RECOVERLY_POWER, false );
		_ui_app->setFluctuationStamina( true );
		turnEnd( );
	}  
	else if ( _network->getItemType( ).id == HERB6 ) {  // ぶっとび草
		warpStart( EFFECT_PLAYER_NUM );
		recoverlyForItem( NORMAL_STAMINA_RECOVERLY_POWER, false );
		_ui_app->setFluctuationStamina( true );
		turnEnd( );
	} 
	else if ( _network->getItemType( ).id == HERB7 ) {  // 毒草
		if ( isEquipmentRing4( ) == false ) {
			becomeAbnormalState( STATE::POISON, EFFECT_PLAYER_NUM );
		} else {
			_message->createFont ( _name, "", "", 0, MessageLog::PROTECT_ABNORMAL );
		}
		recoverlyForItem( NORMAL_STAMINA_RECOVERLY_POWER, false );
		_ui_app->setFluctuationStamina( true );
		turnEnd( );
	} 
	else if ( _network->getItemType( ).id == HERB8 ) {  // しびれ草
		if ( isEquipmentRing4( ) == false ) {
			becomeAbnormalState( STATE::PARALYSIS, EFFECT_PLAYER_NUM );
		} else {
			_message->createFont ( _name, "", "", 0, MessageLog::PROTECT_ABNORMAL );
		}
		recoverlyForItem( NORMAL_STAMINA_RECOVERLY_POWER, false );
		_ui_app->setFluctuationStamina( true );
		turnEnd( );
	} 
	else if ( _network->getItemType( ).id == HERB9 ) {  // 幻惑草
		if ( isEquipmentRing4( ) == false ) {
			becomeAbnormalState( STATE::CONFUSE, EFFECT_PLAYER_NUM );
		} else {
			_message->createFont ( _name, "", "", 0, MessageLog::PROTECT_ABNORMAL );
		}
		recoverlyForItem( NORMAL_STAMINA_RECOVERLY_POWER, false );
		_ui_app->setFluctuationStamina( true );
		turnEnd( );
	}
	else if ( _network->getItemType( ).id == MEAT1 ) {  // 獣の肉
		_effect->playEffect( Effect::EFFECT_TYPE::EFFECT_STAMINA, _draw_pos + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), EFFECT_PLAYER_NUM );
		recoverlyForItem( RECOVERLY_POWER_MEAT_1, false );
		_ui_app->setFluctuationStamina( true );
		turnEnd( );
	} 
	else if ( _network->getItemType( ).id == MEAT2 ) {  // 大きな肉
		_effect->playEffect( Effect::EFFECT_TYPE::EFFECT_STAMINA, _draw_pos + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), EFFECT_PLAYER_NUM );
		recoverlyForItem( RECOVERLY_POWER_MEAT_2, false );
		_ui_app->setFluctuationStamina( true );
		turnEnd( );
	}
	else if ( _network->getItemType( ).id == MEAT3 ) {  // スワロース
		_effect->playEffect( Effect::EFFECT_TYPE::EFFECT_STAMINA, _draw_pos + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), EFFECT_PLAYER_NUM );
		recoverlyForItem( RECOVERLY_POWER_MEAT_3, false );
		_ui_app->setFluctuationStamina( true );
		turnEnd( );
	} 
	else if ( _network->getItemType( ).id == MEAT4 ) {  // 腐った肉
		if ( isEquipmentRing4( ) == false ) {
			becomeAbnormalState( STATE::POISON, EFFECT_PLAYER_NUM );
		} else {
			_message->createFont ( _name, "", "", 0, MessageLog::PROTECT_ABNORMAL );
		}
		_effect->playEffect( Effect::EFFECT_TYPE::EFFECT_STAMINA, _draw_pos + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), EFFECT_PLAYER_NUM );
		recoverlyForItem( NORMAL_STAMINA_RECOVERLY_POWER, false );
		_ui_app->setFluctuationStamina( true );
		turnEnd( );
	}
	else if ( _network->getItemType( ).id == ITEM_ID::STONE2 ) {   // 魔導石
		alchemyPointManage( ALCHMY_POINT_STONE_2 );
		turnEnd( );
	} 
	else if ( _network->getItemType( ).id == ITEM_ID::STONE4 ) {   // 奇跡の石
		itemLevelUP( );
		turnEnd( );
	}
	else if ( _network->getItemType( ).id == ITEM_ID::STONE5 ) {   // 罠壊しの石
		_floor->allBreakMysteryTile( );
		turnEnd( );
	}
	else if ( _network->getItemType( ).id == ITEM_ID::STONE6 ) {   // 大魔導石
		alchemyPointManage( ALCHMY_POINT_STONE_6 );
		turnEnd( );
	}
}

void Player::equipmentItem( ) {
	// idの取得
	ITEM_ID id = _network->getItemType( ).id;

	// idの登録
	switch ( id ) {
	case ITEM_ID::RING1:
	case ITEM_ID::RING2:
	case ITEM_ID::RING3:
	case ITEM_ID::RING4:
	case ITEM_ID::RING5:
	case ITEM_ID::RING6:
		_equipment[ EQUIPMENT_RING ].id = id;
		equipmentRing( id );
		break;
	case ITEM_ID::ROD1:
	case ITEM_ID::SWORD1:
	case ITEM_ID::SWORD2:
	case ITEM_ID::SWORD3:
	case ITEM_ID::SWORD4:
		_equipment[ EQUIPMENT_WEAPON ].id = id;
		equipmentWeapon( id );
		break;
	}

	// メッセージ
	_message->createFont( "", "", _network->getItemType( ).name, 0, MessageLog::MESSAGE_TYPE::EQUIPMENT_ITEM );
}

void Player::disArmItem( ) {
	// idの取得
	ITEM_ID id = _network->getItemType( ).id;

	// 初期化
	switch ( id ) {
	case ITEM_ID::RING1:
	case ITEM_ID::RING2:
	case ITEM_ID::RING3:
	case ITEM_ID::RING4:
	case ITEM_ID::RING5:
	case ITEM_ID::RING6:
		_equipment[ EQUIPMENT_RING ].id      = ITEM_ID::ITEM_NONE;
		_equipment[ EQUIPMENT_RING ].attack  = 0;
		_equipment[ EQUIPMENT_RING ].life    = 0;
		_equipment[ EQUIPMENT_RING ].defense = 0;
		break;
	case ITEM_ID::ROD1:
	case ITEM_ID::SWORD1:
	case ITEM_ID::SWORD2:
	case ITEM_ID::SWORD3:
	case ITEM_ID::SWORD4:
		_equipment[ EQUIPMENT_WEAPON ].id      = ITEM_ID::ITEM_NONE;
		_equipment[ EQUIPMENT_WEAPON ].attack  = 0;
		_equipment[ EQUIPMENT_WEAPON ].life    = 0;
		_equipment[ EQUIPMENT_WEAPON ].defense = 0;
		break;
	}
	// ステータス変動
	_status.max_life = _pre_max_life + _equipment[ EQUIPMENT_WEAPON ].life + _equipment[ EQUIPMENT_RING ].life;
	_status.attack   = _pre_attack + _equipment[ EQUIPMENT_WEAPON ].attack + _equipment[ EQUIPMENT_RING ].attack;
	_status.defense  = _pre_defense + _equipment[ EQUIPMENT_WEAPON ].defense + _equipment[ EQUIPMENT_RING ].defense;

	// メッセージ
	_message->createFont( "", "", _network->getItemType( ).name, 0, MessageLog::MESSAGE_TYPE::DISARM_ITEM );
}

void Player::dead( ) {
	// アニメーション
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	if ( _status.life <= 0 && _dead == false ) {
		// アニメーションの初期化
		viewer->dettachAnim( _anim_hundle.model, _anim_index.stay );
		_anim_play_time = 0.0f;
		_anim_count = 0;
		// アニメーションのアタッチ
		_anim_index.dead = viewer->attachAnim( _anim_hundle.model, 0, _anim_hundle.dead );
		_main_anim = _anim_index.dead;
		_anim_state = DEAD_ANIM;
		// アニメーションの時間を設定
		_total_time = viewer->animTotalTime( _anim_hundle.model, _main_anim );
		_dead_time = _total_time;
		_walking = false;

		// 倒されたかどうか
		_dead = true;
		_message->createFont( _name, "", "", 0, MessageLog::MESSAGE_TYPE::PLAYER_DOWN );
		_network->setSendPlayerDead( true );
	}
}

void Player::revive( ) {
	// アニメーション
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	_message->createFont( _name, "", "", 0, MessageLog::MESSAGE_TYPE::PLAYER_REVIVE );
	// アニメーションの初期化
	_anim_play_time = _dead_time;
	_anim_count = 0;
	_anim_state = REVIVE_ANIM;

	_dead = false;
	// ステータスを初期化
	_status.life    = _status.max_life;
	_status.attack  = _pre_attack;
	_status.defense = _pre_defense;

	_stamina = MAX_STAMINA;
	_status.state = STATE::NORMAL_STATE;
	refreshState( );
}

void Player::setDamage( int enemy_power ) {
	if ( _status.state == CONFUSE ) {
		refreshState( );
	}
	if ( _dead == false ) {
		FrameworkPtr fw  = Framework::getInstance( );
		ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
		// アニメーションの初期化
		viewer->dettachAnim( _anim_hundle.model, _anim_index.stay );
		_anim_play_time = 0.0f;
		_anim_count = 0;
		// アニメーションのアタッチ
		_anim_index.damage = viewer->attachAnim( _anim_hundle.model, 0, _anim_hundle.damage );
		_main_anim = _anim_index.damage;
		_anim_state = DAMAGE_ANIM;
		// アニメーションの時間を設定
		_total_time = viewer->animTotalTime( _anim_hundle.model, _main_anim );
		_damage_time = _total_time;
		_walking = false;
		_damaging = true;
	}
	// ダメージ計算
	// 敵の攻撃力が上回った場合
	if ( _status.defense + 3 < enemy_power ) {
		// 攻撃力引く防御力
		_damage = enemy_power - _status.defense;
		_status.life = _status.life - _damage;
		if ( _status.life <= 0 ) {
			_status.life = 0;
		}
	} else {  // 敵の攻撃力が下回った場合
		_damage = rand( ) % 3 + 1;  // １～３ダメージ与える
		_status.life = _status.life - _damage;
		if ( _status.life <= 0 ) {
			_status.life = 0;
		}
	}
	// メッセージ
	_message->createFont( _name, "", "", _damage, MessageLog::MESSAGE_TYPE::DAMAGE );
}

void Player::setTrapDamage( int damage ) {
	if ( _status.state == CONFUSE ) {
		refreshState( );
	}
	if ( _dead == false ) {
		FrameworkPtr fw  = Framework::getInstance( );
		ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
		// アニメーションの初期化
		viewer->dettachAnim( _anim_hundle.model, _anim_index.stay );
		_anim_play_time = 0.0f;
		_anim_count = 0;
		// アニメーションのアタッチ
		_anim_index.damage = viewer->attachAnim( _anim_hundle.model, 0, _anim_hundle.damage );
		_main_anim = _anim_index.damage;
		_anim_state = DAMAGE_ANIM;
		// アニメーションの時間を設定
		_total_time = viewer->animTotalTime( _anim_hundle.model, _main_anim );
		_damage_time = _total_time;
		_walking = false;
		_damaging = true;
	}
	// ダメージ計算
	_damage = damage;
	_status.life = _status.life - _damage;
	if ( _status.life <= 0 ) {
		_status.life = 0;
	}
	// メッセージ
	_message->createFont( _name, "", "", _damage, MessageLog::MESSAGE_TYPE::DAMAGE );
}

void Player::finishDamageAnim( ) {
	if ( _damaging == true && _anim_play_time > _damage_time ) {
		_damaging = false;
	}
}

void Player::randDirForConfuse( ) {
	if ( _status.state == CONFUSE ) {
		_status.dir = MOVE_DIR( 1 + rand( ) % ( MOVE_DIR::MAX_MOVE_DIR - 1 ) );
	}
}

void Player::recoverlyForItem( int recoverly_power, bool is_hp ) {
	FrameworkPtr fw = Framework::getInstance( );
	SoundPtr sound = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );

	sound->backgrondPlaySound( Sound::CURE );
	if ( is_hp == true ) {
		if ( _status.life + recoverly_power > _status.max_life ) {
			_status.life = _status.max_life;
			_message->createFont( _name, "", "", _status.life + recoverly_power - _status.max_life, MessageLog::HEAL );
		} else {
			_status.life += recoverly_power;
			_message->createFont( _name, "", "", recoverly_power, MessageLog::HEAL );
		}
	} else {
		if ( _stamina + recoverly_power > MAX_STAMINA ) {
			_stamina = MAX_STAMINA;
			_message->createFont( _name, "", "", _stamina + recoverly_power - MAX_STAMINA, MessageLog::STAMINA_HEAL );
		} else {
			_stamina += recoverly_power;
			_message->createFont( _name, "", "", recoverly_power, MessageLog::STAMINA_HEAL );
		}
	}
}

void Player::materiaAbsorption( int absorption_damage ) {
	FrameworkPtr fw = Framework::getInstance( );
	SoundPtr sound = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );

	sound->backgrondPlaySound( Sound::CURE );
	_effect->playEffect( Effect::EFFECT_TYPE::EFFECT_HEAL, _draw_pos + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), EFFECT_PLAYER_NUM );
	// マックスライフを超える場合、ライフをマックスライフに設定
	if ( _status.life + absorption_damage > _status.max_life ) {
		_status.life = _status.max_life;
		_message->createFont( _name, "", "", _status.life + absorption_damage - _status.max_life, MessageLog::HEAL );
	} else {
		_status.life += absorption_damage;
		_message->createFont( _name, "", "", absorption_damage, MessageLog::HEAL );
	}
}

void Player::fluctuationHPForStamina( ) {
	// 腹減り時以外移動で回復
	if ( _status.life < _status.max_life && _stamina > 0 && _status.state != POISON ) {
		_status.life++;
	}
	// おなかが０なら行動の度にHPを１削る
	if ( _stamina <= 0 ) {
		_status.life--;;
	}
}

void Player::hunger( ) {
	_action_count++;
	// 一定ターン歩くとおなかを１消費
	if ( _action_count >= DECREASE_STAMINA_TURN && _stamina > 0 ) {
		_stamina--;
		_action_count = 0;
		if ( _stamina == 50 ) {
			_message->createFont( "", "", "", 0, MessageLog::HALF_STAMINA );
		} else if ( _stamina == 25 ) {
			_message->createFont( "", "", "", 0, MessageLog::HANGER );
		} else if ( _stamina == 10 || _stamina == 5 || _stamina == 0 ) {
			_message->createFont( "", "", "", 0, MessageLog::CRISIS_STAMINA );
		}
	}
}

void Player::equipmentWeapon( ITEM_ID id ) {
	// ステータスを一度元に戻す
	_status.max_life = _pre_max_life + _equipment[ EQUIPMENT_RING ].life;
	_status.attack   = _pre_attack + _equipment[ EQUIPMENT_RING ].attack;
	_status.defense  = _pre_defense + _equipment[ EQUIPMENT_RING ].defense;

	switch ( id ) {
	case ITEM_ID::ROD1:
		_equipment[ EQUIPMENT_WEAPON ].attack = 2;
		break;
	case ITEM_ID::SWORD1:
		_equipment[ EQUIPMENT_WEAPON ].attack = 5;
		break;
	case ITEM_ID::SWORD2:
		_equipment[ EQUIPMENT_WEAPON ].attack = 20;
		break;
	case ITEM_ID::SWORD3:
		_equipment[ EQUIPMENT_WEAPON ].attack = 40;
		break;
	case ITEM_ID::SWORD4:
		_equipment[ EQUIPMENT_WEAPON ].attack = 50;
		break;
	}

	// ステータス変動
	_status.max_life += _equipment[ EQUIPMENT_WEAPON ].life;
	_status.attack   += _equipment[ EQUIPMENT_WEAPON ].attack;
	_status.defense  += _equipment[ EQUIPMENT_WEAPON ].defense;
}

void Player::equipmentRing( ITEM_ID id ) {
	// ステータスを一度元に戻す
	_status.max_life = _pre_max_life + _equipment[ EQUIPMENT_WEAPON ].life;
	_status.attack   = _pre_attack + _equipment[ EQUIPMENT_WEAPON ].attack;
	_status.defense  = _pre_defense + _equipment[ EQUIPMENT_WEAPON ].defense;

	switch ( id ) {
	case ITEM_ID::RING1:
		_equipment[ EQUIPMENT_RING ].life    = 0;
		_equipment[ EQUIPMENT_RING ].attack  = 0;
		_equipment[ EQUIPMENT_RING ].defense = 2;
		break;
	case ITEM_ID::RING2:
		_equipment[ EQUIPMENT_RING ].life    = 10;
		_equipment[ EQUIPMENT_RING ].attack  = 0;
		_equipment[ EQUIPMENT_RING ].defense = 0;
		break;
	case ITEM_ID::RING3:
		_equipment[ EQUIPMENT_RING ].life    = 0;
		_equipment[ EQUIPMENT_RING ].attack  = 10;
		_equipment[ EQUIPMENT_RING ].defense = 0;
		break;
	case ITEM_ID::RING4:
		_equipment[ EQUIPMENT_RING ].life    = 0;
		_equipment[ EQUIPMENT_RING ].attack  = 0;
		_equipment[ EQUIPMENT_RING ].defense = 0;
		break;
	case ITEM_ID::RING5:
		_equipment[ EQUIPMENT_RING ].life    = 0;
		_equipment[ EQUIPMENT_RING ].attack  = 0;
		_equipment[ EQUIPMENT_RING ].defense = 0;
		break;
	case ITEM_ID::RING6:
		_equipment[ EQUIPMENT_RING ].life    = 0;
		_equipment[ EQUIPMENT_RING ].attack  = 0;
		_equipment[ EQUIPMENT_RING ].defense = 0;
		break;
	}
	
	// ステータス変動
	_status.max_life += _equipment[ EQUIPMENT_RING ].life;
	_status.attack   += _equipment[ EQUIPMENT_RING ].attack;
	_status.defense  += _equipment[ EQUIPMENT_RING ].defense;
}

void Player::increaseExp( int exp ) {
	_exp += exp;
	_message->createFont( _name, "", "", exp, MessageLog::MESSAGE_TYPE::GET_EX );
}

void Player::levelUp( ) {
	FrameworkPtr fw = Framework::getInstance( );
	SoundPtr sound = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );

	if ( _exp >= _necessary_exp ) {
		_level++;
		sound->backgrondPlaySound( Sound::LEVEL );
		// マックスライフ
		_pre_max_life += HP_UP; 
		_status.max_life = _pre_max_life + _equipment[ EQUIPMENT_WEAPON ].life + _equipment[ EQUIPMENT_RING ].life;
		_status.life += HP_UP;
		// 攻撃
		_pre_attack += ATK_UP;
		_status.attack = _pre_attack + _equipment[ EQUIPMENT_WEAPON ].attack + _equipment[ EQUIPMENT_RING ].attack;
		// 防御
		_pre_defense += DEF_UP;
		_status.defense = _pre_defense + _equipment[ EQUIPMENT_WEAPON ].defense + _equipment[ EQUIPMENT_RING ].defense;
		// 経験値
		int extra_exp = _exp - _necessary_exp;
		_exp = extra_exp;
		_necessary_exp = ( int )( _necessary_exp * NECESSARY_EXP_MAGNIFICATION );
		// メッセージ
		_message->createFont( _name, "", "", _level, MessageLog::MESSAGE_TYPE::LV_UP );
		learnSkillForLevel( );
		
		_ui_app->setPlayerLevel( _level );
	}
}

void Player::itemLevelUP( ) {
	FrameworkPtr fw = Framework::getInstance( );
	SoundPtr sound = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );

	_level++;
	sound->backgrondPlaySound( Sound::LEVEL );
	// マックスライフ
	_pre_max_life += HP_UP; 
	_status.max_life = _pre_max_life + _equipment[ EQUIPMENT_WEAPON ].life + _equipment[ EQUIPMENT_RING ].life;
	_status.life += HP_UP;
	// 攻撃
	_pre_attack += ATK_UP;
	_status.attack = _pre_attack + _equipment[ EQUIPMENT_WEAPON ].attack + _equipment[ EQUIPMENT_RING ].attack;
	// 防御
	_pre_defense += DEF_UP;
	_status.defense = _pre_defense + _equipment[ EQUIPMENT_WEAPON ].defense + _equipment[ EQUIPMENT_RING ].defense;
	_message->createFont( _name, "", "", _level, MessageLog::MESSAGE_TYPE::LV_UP );
	_exp = 0;
	_necessary_exp = ( int )( _necessary_exp * NECESSARY_EXP_MAGNIFICATION );
	learnSkillForLevel( );
	
	_ui_app->setPlayerLevel( _level );
}

void Player::learnSkillForLevel( ) {
	if ( _level == LEARN_ZANGEKI_LEVEL ) {
		_network->setSendSkillData( SKILL_ID::ZANGEKI );
		_message->createFont( _name, "斬撃", "", 0, MessageLog::MESSAGE_TYPE::LEARN_WAZA );
	}
	if ( _level == LEARN_ZANMETU_LEVEL ) {
		_network->setSendSkillData( SKILL_ID::ZANMETUHA );
		_message->createFont( _name, "斬滅波", "", 0, MessageLog::MESSAGE_TYPE::LEARN_WAZA );
	}
	if ( _level == LEARN_MATERIA_LEVEL ) {
		_network->setSendSkillData( SKILL_ID::MATERIASWORD );
		_message->createFont( _name, "マテリアソード", "", 0, MessageLog::MESSAGE_TYPE::LEARN_WAZA );
	}
	if ( _level == LEARN_SPEED_UP_LEVEL ) {
		_network->setSendSkillData( SKILL_ID::SPEED_UP );
		_message->createFont( _name, "疾風の加護", "", 0, MessageLog::MESSAGE_TYPE::LEARN_WAZA );
	}
}

void Player::returnTrap( ) {
	if ( pitProduction( ) == true ) {
		_ride_return_trap = true;
		_return_start     = false;
	}
}

void Player::turnEnd( ){
	// 状態異常ターン経過の更新
	elapsedAbnormalTurn( );
	elapsedSpeedTurn( );
	elapsedBuffTurn( );
	// ステータスを送る
	_network->sendStatus( _status, _stamina, _level );
	// はやあし状態で動いていないならターンエンドしない
	if ( !( _speed_abnormal == true && _status.speed == FAST ) ) {
		_turn_end = true;
	}
	// 見えている罠の場所を送る
	_floor->sendNetworkMysteryPos( );
}

void Player::alchemyPointManage( int point ) {
	_network->setSendAlchemyPoint( point );
}

MOVE_DIR Player::getMoveDir( ) {
	return _move_dir;
}

int Player::getStamina( ) {
	return _stamina;
}

int Player::getSkillAttackDamage( ) {
	return _skill_attack_damage;
}

int Player::getLevel( ) {
	return _level;
}

bool Player::isAttack( ) {
	if ( _attacked == true ) {
		_attacked = false;
		return true;
	}
	return false;
}

bool Player::isSkillAttack( ) {
	if ( _skill_attacked == true ) {
		_skill_attacked = false;
		return true;
	}
	return false;
}

bool Player::isUseZanmetuha( ) {
	return _use_zanmetuha;
}

Vector2 Player::getHitEnemyPos( ) {
	return _hit_enemy_pos;
}

void Player::setZanmetuHitEnemy( bool hit_enemy ) {
	_zanmetuha.hit_enemy = hit_enemy;
}

bool Player::isZanmetuHitEnemy( ) {
	return _zanmetuha.hit_enemy;
}

void Player::setUseMateria( bool use_materia_sword ) {
	_use_materia_sword = use_materia_sword;
}

bool Player::isUseMateriaSword( ) {
	return _use_materia_sword;
}

bool Player::isDead( ) {
	return _dead;
}

bool Player::isRevive( ) {
	return _no_revive;
}


bool Player::isRideReturnTrap( ) {
	if ( _ride_return_trap == true ) {
		_ride_return_trap = false;
		return true;
	}
	return false;
}

bool Player::isEquipmentAttackItem( ) {
	if ( _equipment[ EQUIPMENT_RING ].id == ITEM_ID::RING3 || _equipment[ EQUIPMENT_WEAPON ].id != ITEM_ID::ITEM_NONE ) {
		return true;
	}
	return false;
}

bool Player::isEquipmentSword4( ) {
	if ( _equipment[ EQUIPMENT_WEAPON ].id == ITEM_ID::SWORD4 ) {
		return true;
	}
	return false;
}

bool Player::isEquipmentRing4( ) {
	if ( _equipment[ EQUIPMENT_RING ].id == ITEM_ID::RING4 ) {
		return true;
	}
	return false;
}

bool Player::pushSpace( ) {
	FrameworkPtr fw = Framework::getInstance( );
	KeyboardPtr keyboard = std::dynamic_pointer_cast< Keyboard >( fw->getTask( typeid( Keyboard ).name( ) ) );
	// スペースを押したら行動
	if ( keyboard->isPushKey( "SPACE" ) ) {
		return true;
	} else {
		return false;
	}
}

bool Player::isTurnEnd( ) {
	return _turn_end;
}

Player::EQUIPMENT_DATA Player::getEquipment( int equipment_num ) {
	return _equipment[ equipment_num ];
}
