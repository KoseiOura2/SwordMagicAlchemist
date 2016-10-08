#include "Enemy.h"
#include "EnemyManager.h"
#include "Player.h"
#include "Framework.h"
#include "Viewer.h"
#include "Turn.h"
#include "Effect.h"
#include "NetworkApp.h"

Enemy::Enemy( FloorPtr floor, NetworkAppPtr network, MessageLogPtr message, EffectPtr effect ,ENEMY_TYPE enemy_type, ANIM_HUNDLE anim_handle,
		      float scale, ENEMY_DATA data ) : Character ( floor, network, message, effect ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	_network = network;

	_action = MOVE_LOITERING;
	_effect = effect;
	// エネミータイプを設定
	_enemy_type = enemy_type;
	// アニメーションハンドルの設定
	_anim_hundle.model  = viewer->duplicateModel( anim_handle.model );
	_anim_hundle.stay   = viewer->duplicateModel( anim_handle.stay );
	_anim_hundle.walk   = viewer->duplicateModel( anim_handle.walk );
	_anim_hundle.attack = viewer->duplicateModel( anim_handle.attack );
	_anim_hundle.dead   = viewer->duplicateModel( anim_handle.dead );

	_my_type = MY_TYPE_ENEMY;
	// 初期化
	init( scale, data );
}

Enemy::~Enemy( ) {

}

void Enemy::init( float scale, ENEMY_DATA data ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	_dead            = false;
	_find_player     = false;
	_buff            = false;
	_buff_end        = false;
	_target          = _pos;
	_aisle_dir       = DIR_NONE;
	viewer->modelSetScale( _anim_hundle.model, scale, scale, scale );
	_name = data.name;
	// 初期ステータスの設定
	_status.max_life = data.max_life;
	_status.life     = _status.max_life;
	_status.attack   = data.attack;
	_pre_attack      = data.attack;
	_status.defense  = data.deffence;
	_exp             = data.exp;
	_alchemy_point   = data.alchemy_point;
	// アニメーションの設定
	_anim_play_time = 0.0f;
	_anim_count = 0;
	_anim_index.stay = viewer->attachAnim( _anim_hundle.model, 0, _anim_hundle.stay );
	_main_anim = _anim_index.stay;
	_anim_state = STAY_ANIM;

}

void Enemy::init( int my_number, Floor::TILE my_tile ) {
	// 自身の番号を登録
	_my_number = my_number;
	// 描画座標
	_draw_pos = my_tile.pos;
	_pre_pos = _draw_pos;
	// タイル座標
	_pos.x = _draw_pos.x / TILE_SIZE;
	_pos.y = _draw_pos.z / TILE_SIZE;
}

void Enemy::update( ) {
	// タイプによってアニメーション再生時間を設定
	switch ( _enemy_type ) {
	case SWANGLER:
	case GREAT_SWANGLER:
		playbackAnim( STAY_ANIM_FRAME, WALK_ANIM_FRAME, SWANGLER_ATTACK_ANIM_FRAME, SWAN_DEAD_ANIM_FRAME, DAMAGE_ANIM_FRAME, 0.0f );
		break;
	case OCTO_POT:
	case GREAT_OCTO_POT:
	case SILVER_OCTO_POT:
	case GOLD_OCTO_POT:
		playbackAnim( STAY_ANIM_FRAME, WALK_ANIM_FRAME, OCTO_POT_ATTACK_ANIM_FRAME, DEAD_ANIM_FRAME, DAMAGE_ANIM_FRAME, 0.0f );
		break;
	case SPIDER:
	case GREAT_SPIDER:
		playbackAnim( STAY_ANIM_FRAME, WALK_ANIM_FRAME, SPIDER_ATTACK_ANIM_FRAME, SPI_DEAD_ANIM_FRAME, DAMAGE_ANIM_FRAME, 0.0f );
		break;
	case GOCHIMPANZEE:
		playbackAnim( STAY_ANIM_FRAME, WALK_ANIM_FRAME, GOCHIM_ATTACK_ANIM_FRAME, GOCHIM_DEAD_ANIM_FRAME, DAMAGE_ANIM_FRAME, 0.0f );
		break;
	case MINOTAUR:
	case GREAT_MINOTAUR:
		playbackAnim( STAY_ANIM_FRAME, WALK_ANIM_FRAME, MINO_ATTACK_ANIM_FRAME, DEAD_ANIM_FRAME, DAMAGE_ANIM_FRAME, 0.0f );
		break;
	case BOSS:
		playbackAnim( STAY_ANIM_FRAME, WALK_ANIM_FRAME, BOSS_ATTACK_ANIM_FRAME, DEAD_ANIM_FRAME, DAMAGE_ANIM_FRAME, 0.0f );
		break;
	}
	move( );	
	// モデルの向きを変える
	if ( _warp == true || _warp_stair == true ) {
		rotateByWarp( );
	} else {
		angleChange( );
	}
	// ワープ処理
	if ( _warp == true ) {
		warpPos( );
	}
	if ( _warp_stair == true ) {
		warpStairPos( );
	}
	if ( _warp_move == true ) {
		if ( _enemy_type == ENEMY_TYPE::BOSS ) {
			for ( int i = - 1; i <= 1; i++ ) {
				for ( int j = - 1; j <= 1; j++ ) {
					_floor->setBondEnemy( ( int )_pos.x + i, ( int )_pos.y + j );
				}
			}
		} else {
			_floor->setBondEnemy( ( int )_pos.x, ( int )_pos.y );
		}
	}
	// バフ処理
	statusForBuff( );
	if ( _buff_end == true ) {
		_status.attack = _pre_attack;
		_buff_end = false;
	}

	draw( );

	
	// エフェクトの描画座標の移動
	_effect->moveDrawPos( _draw_pos + Vector( TILE_SIZE / 2, 0, TILE_SIZE / 2 ), _my_number );
	// effectの更新
	int num = -1;
	switch ( _status.state ) {
	case POISON:
		num = _effect->isPlayEndEffect( Effect::EFFECT_TYPE::EFFECT_POISON, _my_number );
		break;
	case PARALYSIS:
		num = _effect->isPlayEndEffect( Effect::EFFECT_TYPE::EFFECT_PARALYSIS, _my_number );
		break;
	case SKILL_SEAL:
		num = _effect->isPlayEndEffect( Effect::EFFECT_TYPE::EFFECT_SEALED, _my_number );
		break;
	case BIND_TILE:
		num = _effect->isPlayEndEffect( Effect::EFFECT_TYPE::EFFECT_SEALED, _my_number );
		break;
	case CONFUSE:
		num = _effect->isPlayEndEffect( Effect::EFFECT_TYPE::EFFECT_CONFUSE, _my_number );
		break;
	}

	num = -1;
	switch ( _status.speed ) {
	case SLOW:
		num = _effect->isPlayEndEffect( Effect::EFFECT_TYPE::EFFECT_DEBUFF, _my_number );
		break;
	case FAST:
		num = _effect->isPlayEndEffect( Effect::EFFECT_TYPE::EFFECT_BUFF, _my_number );
		break;
	}
	
	num = -1;
	switch ( _status.buff ) {
	case DEBUFF:
		num = _effect->isPlayEndEffect( Effect::EFFECT_TYPE::EFFECT_DEBUFF, _my_number );
		break;
	case BUFF:
		num = _effect->isPlayEndEffect( Effect::EFFECT_TYPE::EFFECT_BUFF, _my_number );
		break;
	}

	if ( num != -1 ) {
		_effect->rePlayEffect( _draw_pos + Vector( TILE_SIZE / 2, 0, TILE_SIZE / 2 ), Vector( 0, 0, 0 ), num );
	}
}

void Enemy::moveAnim( Vector2 pos ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	viewer->dettachAnim( _anim_hundle.model, _anim_index.stay );
	// アニメーションのアタッチ
	_anim_play_time = 0.0f;
	_anim_count = 0;
	_anim_index.walk = viewer->attachAnim( _anim_hundle.model, 0, _anim_hundle.walk );
	_main_anim = _anim_index.stay;
	_anim_state = WALK_ANIM;
	// 移動先を設定
	_pre_pos = _draw_pos;
	_pos = pos;
}

bool Enemy::isEndMoveAnim( ) {
	if ( _anim_state == WALK_ANIM && _anim_count > WALK_ANIM_TIME ) {
		return true;
	}
	return false;
}

void Enemy::attackAnim( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	// アニメーションの初期化
	viewer->dettachAnim( _anim_hundle.model, _anim_index.stay );
	_anim_play_time = 0.0f;
	_anim_count = 0;
	// アニメーションのアタッチ
	_anim_index.attack = viewer->attachAnim( _anim_hundle.model, 0, _anim_hundle.attack );
	_main_anim  = _anim_index.attack;
	_anim_state = ATTACK_ANIM;
	// アニメーションの時間を設定
	_total_time  = viewer->animTotalTime( _anim_hundle.model, _main_anim );
	_attack_time = _total_time;
}

bool Enemy::isEndAttackAnim( ) {
	if ( _anim_state == ATTACK_ANIM && _anim_count > _attack_time ) {
		return true;
	}
	return false;
}

void Enemy::deadAnim( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	// アニメーションの初期化
	viewer->dettachAnim( _anim_hundle.model, _anim_index.stay );
	_anim_play_time = 0.0f;
	_anim_count = 0;
	// アニメーションのアタッチ
	_anim_index.dead = viewer->attachAnim( _anim_hundle.model, 0, _anim_hundle.dead );
	_main_anim  = _anim_index.dead;
	_anim_state = DEAD_ANIM;
	// アニメーションの時間を設定
	_total_time = viewer->animTotalTime( _anim_hundle.model, _main_anim );
	_dead_time  = _total_time;
}

void Enemy::dead( ) {
	_dead = true;
}

bool Enemy::isEndDeadAnim( ) {
	if ( _anim_state == DEAD_ANIM && _anim_play_time > _dead_time ) {
		//deleatModel( );
		return true;
	}
	return false;
}

void Enemy::damage( int player_power, bool use_waza, bool equip_item, bool zangeki ) {
	if ( use_waza == true ) {
		if ( zangeki == true ) {
			_damage = player_power;
			_status.life -= _damage;
		} else {
		// Playerの攻撃力が上回っていた場合
			if ( player_power > _status.defense + 3 ) {
				_damage = ( player_power - _status.defense );
				_status.life -= _damage;
			}
			// Playerの攻撃力が下回っていた場合１～３ダメージ
			else {
				_damage = ( rand( ) % 3 + 1 );
				_status.life -= _damage;
			}
		}
	} else {
		if ( _enemy_type == ENEMY_TYPE::SILVER_OCTO_POT || _enemy_type == ENEMY_TYPE::GOLD_OCTO_POT ) {
			_damage = 3;
			_status.life -= _damage;
		} else {
			if ( equip_item == true ) {
				// Playerの攻撃力が上回っていた場合
				if ( player_power > _status.defense + 3 ) {
					_damage = ( player_power - _status.defense );
					_status.life -= _damage;
				}
				// Playerの攻撃力が下回っていた場合１～３ダメージ
				else {
					_damage = ( rand( ) % 3 + 1 );
					_status.life -= _damage;
				}
			} else {
				_damage = 5;
				_status.life -= _damage;
			}
		}
	}
}

void Enemy::itemDamage( int item_damage ) {
	_damage = item_damage;
	// 回復アイテムの場合HPを回復
	if ( item_damage < 0 ) {
		if ( _status.max_life < _status.life - item_damage ) {
			_status.life = _status.max_life;
		} else {
			_status.life -= item_damage;
		}
	} else {
		_status.life -= item_damage;
	}
}

void Enemy::deleatModel( ) {
	// 使わなくなったモデルを削除
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	viewer->deleatModel( _anim_hundle.model );
	viewer->deleatModel( _anim_hundle.stay );
	viewer->deleatModel( _anim_hundle.walk );
	viewer->deleatModel( _anim_hundle.attack );
	viewer->deleatModel( _anim_hundle.dead );
}

void Enemy::setAction( ACTION action ) {
	_action = action;
}

void Enemy::setAisleDir( ENEMY_AISLE_DIR aisle_dir ) {
	_aisle_dir = aisle_dir;
}

void Enemy::setTargetPos( int x, int y ) {
	_target.x = x;
	_target.y = y;
}

void Enemy::setFindPlayer( bool find ) {
	_find_player = find;
}

void Enemy::setRoomNum( int room_num ) {
	_room_num = room_num;
}

ENEMY_TYPE Enemy::getType( ) {
	return _enemy_type;
} 

Enemy::ACTION Enemy::getAction( ) {
	return _action;
}

Enemy::ENEMY_AISLE_DIR Enemy::getAisleDir( ) {
	return _aisle_dir;
}

Vector2 Enemy::getTargetPos( ) {
	return _target;
}

unsigned int Enemy::getNumber( ) {
	return _my_number;
}

int Enemy::getRoomNum( ) {
	return _room_num;
}

int Enemy::getDamage( ) {
	return _damage;
}

int Enemy::getExp( ) {
	return _exp;
}

int Enemy::getAlchemyPoint( ) {
	return _alchemy_point;
}

bool Enemy::isFindPlayer( ) {
	return _find_player;
}

bool Enemy::isDead( ) {
	return _dead;
}
