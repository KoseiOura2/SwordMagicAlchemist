#include "Skill.h"
#include "Framework.h"
#include "Viewer.h"
#include "Touch.h"
#include "ItemImage.h"

Skill::Skill( Vector2 pos, NetworkControllerPtr network, ItemImagePtr item_image ) : Icon( pos ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	_image = viewer->loadGraph( "work/ctrl_UI/skill.png" );
	_window = viewer->loadGraph( "work/ctrl_UI/window/window_skill.png" );
	_window_use = viewer->loadGraph( "work/ctrl_UI/window/window_item_use.png" );
	_network = network;
	_item_image = item_image;
	_open_num = -1;
	SKILL_DATA teble[ ] = {
		SKILL_DATA( ZANGEKI, "斬撃", "【斬撃】研ぎ澄まされた剣撃が目の前の敵を貫く。お腹消費5" ),
		SKILL_DATA( ZANMETUHA, "斬滅破", "【斬滅破】斬撃による衝撃波が2マス先までの敵を襲う。お腹消費10" ),
		SKILL_DATA( MATERIASWORD, "マテリアソード", "【マテリアソード】魔力により敵から体力を吸い取る斬撃。与えたダメージ分HPが回復する。お腹消費20" ),
		SKILL_DATA( SPEED_UP, "疾風の加護", "【疾風の加護】風の力を身にまとい疾風怒濤の速さを手に入れる。数ターンの間2回行動ができる。お腹消費30" ),
	};
	for ( int i = 0; i < MAX_SKILL_NUM; i++ ) {
		_skill_table [ i ] = teble[ i ];
	}

	_zangeki = viewer->loadGraph( "work/ctrl_UI/skill/zangeki.png" );
	_zanmetuha = viewer->loadGraph( "work/ctrl_UI/skill/zanmetuha.png" );
	_materiasword = viewer->loadGraph( "work/ctrl_UI/skill/materiasword.png" );
	_speed_up = viewer->loadGraph( "work/ctrl_UI/skill/speed_up.png" );

	_zangeki_seal = viewer->loadGraph( "work/ctrl_UI/skill/zangeki_seal.png" );
	_zanmetuha_seal = viewer->loadGraph( "work/ctrl_UI/skill/zanmetuha_seal.png" );
	_materiasword_seal = viewer->loadGraph( "work/ctrl_UI/skill/materiasword_seal.png" );
	_speed_up_seal = viewer->loadGraph( "work/ctrl_UI/skill/speed_up_seal.png" );
	//デバッグ用
	/*_skill_list.push_back( _skill_table[ 0 ] );
	_skill_list.push_back( _skill_table[ 1 ] );
	_skill_list.push_back( _skill_table[ 2 ] );
	_skill_list.push_back( _skill_table[ 3 ] );*/
}

Skill::~Skill( ) {
}

void Skill::init( ) {
	_skill_list.clear( );
	close( );
}

void Skill::close( ) {
	_open_num = -1;
}

void Skill::touch( ) {
	FrameworkPtr fw = Framework::getInstance( );
	TouchPtr touch = std::dynamic_pointer_cast< Touch >( fw->getTask( typeid( Touch ).name( ) ) );

	drawWindow( );
	if ( _open_num != -1 ) {
		openSkill( _open_num );
	}
	if ( touch->isSeparate( ) ) {
		_separate_flag = true;
		_close_flag = false;
	}
}

void Skill::drawWindow( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	TouchPtr touch = std::dynamic_pointer_cast< Touch >( fw->getTask( typeid( Touch ).name( ) ) );

	// ウィンドウの描画
	viewer->drawGraph( SKILL_WINDOW_X, SKILL_WINDOW_Y, _window );

	unsigned int count = 0;		// vectorの参照を得るために使うのでwatning対策にunsigned型
	for ( int i = 0; i < SKILL_COLUMN; i++ ) {
		for ( int j = 0; j <= SKILL_ROW; j++ ) {
			// 描画位置を設定
			Vector2 skill_pos ( SKILL_WINDOW_X + SKILL_X_SPACE + ( SKILL_X_INTERVAL * j ), SKILL_WINDOW_Y + SKILL_Y_SPACE + ( SKILL_Y_INTERVAL * i ) );
			
			// アイコンを描画
			if ( count < _skill_list.size( ) ) { 
				// 選択中のアイテム
				if ( count == _open_num ) {
					viewer->drawGraph( ( int )skill_pos.x, ( int )skill_pos.y, _item_image->getFrameWhite( ) );
				}

				// スキル封印処理
				if ( _network->getStatusData( ).state == STATE::SKILL_SEAL ) {
					drawSkillSeal( );
					viewer->drawGraph ( ( int )skill_pos.x, ( int )skill_pos.y, getSkillSealImage( _skill_list.at( count ).type.id ) );
				} else {	
					viewer->drawGraph ( ( int )skill_pos.x, ( int )skill_pos.y, getSkillImage( _skill_list.at( count ).type.id ) );
					// スキルをタッチした時の処理
					if ( touch->isTouch( skill_pos, SKILL_IMAGE_WIDTH, SKILL_IMAGE_HEIGHT ) ) {
						if ( _open_num == count && _separate_flag == true ) {
							_open_num = NOT_OEPN_SKILL;
							_separate_flag = false;
						} else if ( _separate_flag == true ) {
							_open_num = count;
							_separate_flag = false;

						}
					}
				}
			}
			count++;
		}
	}

	// 文字の描画
	/*Vector2 string_pos = Vector2( SKILL_LIST_POS_X, SKILL_LIST_POS_Y );
	for ( int i = 0; i < _skill_list.size( ); i++ ) {	
		if ( i == _open_num ) {
			drawStringColor( string_pos, _skill_list.at( i ).type.name, 0, 180, 255 );
		} else {
			drawString( string_pos, _skill_list.at( i ).type.name );
		}
		
		if ( touch->isTouch( string_pos, string_pos.x + SKILL_NAME_WIDTH, FONT_SIZE  ) ) {
			// 閉じる
			if ( _open_num == i && _separate_flag == true ) {
				 _close_flag = true;
				 close( );
				 touch->rejectTouch( );
			} 
			// 開く
			else if ( _close_flag == false ) {
				_separate_flag = false;
				_open_num = i;
			}
		}
		string_pos.y += SKILL_DISTANCE;
	}*/

}

void Skill::openSkill( int num ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	TouchPtr touch = std::dynamic_pointer_cast< Touch >( fw->getTask( typeid( Touch ).name( ) ) );

	viewer->drawGraph( SKILL_WINDOW_X + SKILL_WINDOW_WIDTH, SKILL_WINDOW_Y, _window_use );	// ウィンドウの描画
	drawDescription( _skill_list.at( num ) );

	int use_dis = SKILL_USE_HEIGHT / 4; // ウィンドウの高さ / コマンドの数 + 2
	Vector2 string_pos[  ] = { Vector2 ( SKILL_USE_STRING_X, SKILL_WINDOW_Y + use_dis ),
							   Vector2 ( SKILL_USE_STRING_X, SKILL_WINDOW_Y + use_dis * 2 ) };
	drawString( string_pos[ 0 ], "つかう" );
	drawString( string_pos[ 1 ], "とじる" );

	// つかうコマンドの処理
	if ( touch->isTouch( string_pos[ 0 ], SKILL_USE_WIDTH, FONT_SIZE ) ) {
		_network->setSendMagicAttack( true );
		_network->setSendSkillId( _skill_list.at( num ).type.id );
		touch->rejectTouch( );
		close( );
	// とじるコマンド
	} else if ( touch->isTouch( string_pos[ 1 ], SKILL_USE_WIDTH, FONT_SIZE ) ) {
		close( );
		touch->rejectTouch( );
	}
}

void Skill::drawDescription( SKILL_DATA skill ) {
	int line = 0;
	line = skill.description.find( "】" );
	if ( line == std::string::npos ) {
		line = skill.description.find( "。" );
	}
	line += 2;
	std::string tmp = skill.description.substr( 0, line );	// 。までの位置を一行目とする
	drawStringSmallFont( Vector2 ( SKILL_DESCRIPTION_X, SKILL_DESCRIPTION_Y ), tmp );
	tmp = skill.description.substr( line );					// 。以降の文字を2行目にする
	drawStringSmallFont( Vector2 ( SKILL_DESCRIPTION_X, SKILL_DESCRIPTION_Y + FONT_SIZE ), tmp );
}

void Skill::skillGet( ) {
	SKILL_ID id = _network->getSkillType( ).id;
	if ( id != SKILL_NONE ) {
		_skill_list.push_back( getSkillData( id ) );
		_network->resetSkillData( );
	}
}

Skill::SKILL_DATA Skill::getSkillData( SKILL_ID id ) {
	SKILL_DATA result;

	for ( int i = 0; i < MAX_SKILL_NUM; i++ ) {
		if ( _skill_table[ i ].type.id == id ) {
			result = _skill_table[ i ];
			break;
		}
	}

	return result;
}

int Skill::getSkillImage( SKILL_ID id ) {
	int image = 0;
	
	switch ( id ) {
		case SKILL_ID::ZANGEKI : {
			image = _zangeki;
			break;
		}
		case SKILL_ID::ZANMETUHA : {
			image = _zanmetuha;
			break;
		}
		case SKILL_ID::MATERIASWORD : {
			image = _materiasword;
			break;
		}
		case SKILL_ID::SPEED_UP : {
			image = _speed_up;
			break;
		}
	}

	return image;

}

int Skill::getSkillSealImage( SKILL_ID id ) {
	int image = 0;
	
	switch ( id ) {
		case SKILL_ID::ZANGEKI : {
			image = _zangeki_seal;
			break;
		}
		case SKILL_ID::ZANMETUHA : {
			image = _zanmetuha_seal;
			break;
		}
		case SKILL_ID::MATERIASWORD : {
			image = _materiasword_seal;
			break;
		}
		case SKILL_ID::SPEED_UP : {
			image = _speed_up_seal;
			break;
		}
	}

	return image;

}

void Skill::drawSkillSeal( ) {
	std::string str = "スキルは封印されている！";
	drawString( Vector2 ( SKILL_DESCRIPTION_X, SKILL_DESCRIPTION_Y ), str );
}