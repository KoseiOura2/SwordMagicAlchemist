#include "MessageLog.h"
#include "Framework.h"
#include "Viewer.h"
#include "DxLib.h"

MessageLog::MessageLog( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	_window_hundle   = viewer->loadGraph( "work/app_UI/window/window_message.png" );
	_message_font    = CreateFontToHandle( "HGP創英角ｺﾞｼｯｸUB", 52, -1, -1 );

	_width  = GAME_SCREEN_WIDTH * 8 / 9;
	_height = GAME_SCREEN_HEIGHT * 5 / 24;
	init( );
}

MessageLog::~MessageLog( ) {

}

void MessageLog::init( ) {
	_time        = 0;
	_window_open = false;
	_line_font.erase( _line_font.begin( ), _line_font.end( ) );
	_num.erase( _num.begin( ), _num.end( ) );
}

void MessageLog::update( ) {
	draw( );
}

void MessageLog::draw( ) {
	openingWindow( );
	if ( _window_open == true ) {
		backgroundDraw( );
		drawMessage( );
	}
}

void MessageLog::backgroundDraw( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	Vector2 pos;
	pos.x = GAME_SCREEN_WIDTH / 27;
	pos.y = GAME_SCREEN_HEIGHT * 3 / 4;
	viewer->drawExtendGraph( pos.x, pos.y, pos.x + _width, pos.y + _height, _window_hundle );
}

void MessageLog::createFont( std::string name, std::string waza, std::string item, int num, MESSAGE_TYPE message_type ) {
	
	_window_open = true;
	_time        = 0;

	switch ( message_type ) {
	case NO_MOVE:
		_line_font.push_back( name + "はうごけない！" );
		_num.push_back( num );
		break;
	case USE_WAZA:
		_line_font.push_back( name + "は " + waza + "をくりだした。" );
		_num.push_back( num );
		break;
	case FAILURE_WAZA:
		_line_font.push_back( waza + "は失敗した。" );
		_num.push_back( num );
		break;
	case LEARN_WAZA:
		_line_font.push_back( name + "は " + waza + "を覚えた。" );
		_num.push_back( num );
		break;
	case SEAL_WAZA:
		_line_font.push_back( "スキルは封印されている！" );
		_num.push_back( num );
		break;
	case HEAL:
		_line_font.push_back( name + "はHPが　%d回復した。" );
		_num.push_back( num );
		break;
	case STAMINA_HEAL:
		_line_font.push_back( name + "はおなかが　%d回復した。" );
		_num.push_back( num );
		break;
	case HALF_STAMINA:
		_line_font.push_back( "おなかがへった。" );
		_num.push_back( num );
		break;
	case HANGER:
		_line_font.push_back( name + "空腹でくらくらしてきた。" );
		_num.push_back( num );
		break;
	case CRISIS_STAMINA:
		_line_font.push_back( name + "何か食べないとまずい！" );
		_num.push_back( num );
		break;
	case DAMAGE:
		_line_font.push_back( name + "に %dのダメージ。" );
		_num.push_back( num );
		break;
	case STATE_ABNORMAL:
		_line_font.push_back( name + "は" + waza + "にかかった。" );
		_num.push_back( num );
		break;
	case CURE_ABNORMAL:
		_line_font.push_back( name + "は状態異常がなおった。" );
		_num.push_back( num );
		break;
	case NO_CHANGE_ABNORMAL:
		_line_font.push_back( name + "はこれ以上悪くならない。" );
		_num.push_back( num );
		break;
	case PROTECT_ABNORMAL:
		_line_font.push_back( name + "は状態異常から身を守った。" );
		_num.push_back( num );
		break;
	case CHANGE_SPEED:
		_line_font.push_back( name + "は" + waza );
		_num.push_back( num );
		break;
	case CURE_SPEED:
		_line_font.push_back( name + "の速さが元に戻った。" );
		_num.push_back( num );
		break;
	case NO_CHANGE_SPEED:
		_line_font.push_back( name + "はこれ以上" + waza );
		_num.push_back( num );
		break;
	case CHANGE_BUFF:
		_line_font.push_back( name + "は" + waza );
		_num.push_back( num );
		break;
	case CURE_BUFF:
		_line_font.push_back( name + "の攻撃力が元に戻った。" );
		_num.push_back( num );
		break;
	case NO_CHANGE_BUFF:
		_line_font.push_back( name + "はこれ以上" + waza );
		_num.push_back( num );
		break;
	case KNOCK_DOWN:
		_line_font.push_back( name + "を倒した。" );
		_num.push_back( num );
		break;
	case PLAYER_DOWN:
		_line_font.push_back( name + "は倒れてしまった。" );
		_num.push_back( num );
		break;
	case PLAYER_REVIVE:
		_line_font.push_back( name + "は復活した。" );
		_num.push_back( num );
		break;
	case GET_EX:
		_line_font.push_back( name + "は %dの経験値を得た。" );
		_num.push_back( num );
		break;
	case LV_UP:
		_line_font.push_back( name + "は Lv.%dにあがった。" );
		_num.push_back( num );
		break;
	case CLEAR:
		_line_font.push_back( "ダンジョンをクリアした。" );
		_num.push_back( num );
		break;
	case USE_ITEM:
		_line_font.push_back( item + "をつかった。" );
		_num.push_back( num );
		break;
	case THROW_ITEM:
		_line_font.push_back( item + "を投げた。" );
		_num.push_back( num );
		break;
	case EQUIPMENT_ITEM:
		_line_font.push_back( item + "を装備した。" );
		_num.push_back( num );
		break;
	case DISARM_ITEM:
		_line_font.push_back( item + "を外した。" );
		_num.push_back( num );
		break;
	case ON_THE_ITEM:
		_line_font.push_back( item + "にのった。" );
		_num.push_back( num );
		break;
	case PICK_ITEM:
		_line_font.push_back( item + "を拾った。" );
		_num.push_back( num );
		break;
	case PUT_ITEM:
		_line_font.push_back( item + "を置いた。" );
		_num.push_back( num );
		break;
	case STEP_MYSTERY:
		_line_font.push_back( name + "をふんだ！" );
		_num.push_back( num );
		break;
	case STEP_ALCKEMY:
		_line_font.push_back( "錬金ポイントが倍になった！" );
		_num.push_back( num );
		break;
	}
	if ( _line_font.size( ) > 3 ) {
		_line_font.erase( _line_font.begin( ) + 0 );
		if ( _num.size( ) > 0 ) {
			_num.erase( _num.begin( ) + 0 );
		}
	}
}

void MessageLog::drawMessage( ) {
	if ( _line_font.size( ) >= 1 ) {
		if ( _num.size( ) >= 1 ) {
			DrawFormatStringToHandle( FONT_POS_X , ONE_LINE_FONT_POS_Y , GetColor( 255, 255, 255 ),
								_message_font, _line_font.at( 0 ).c_str( ), _num.at( 0 ) );
		}
	}
	if ( _line_font.size( ) >= 2 ) {
		if ( _num.size( ) >= 2 ) {
			DrawFormatStringToHandle( FONT_POS_X , TWO_LINE_FONT_POS_Y , GetColor( 255, 255, 255 ),
								_message_font, _line_font.at( 1 ).c_str( ), _num.at( 1 ) );
		}
	}
	if ( _line_font.size( ) >= 3 ) {
		if ( _num.size( ) >= 3 ) {
			DrawFormatStringToHandle( FONT_POS_X , THREE_LINE_FONT_POS_Y , GetColor( 255, 255, 255 ),
								_message_font, _line_font.at( 2 ).c_str( ), _num.at( 2 ) );
		}
	}
}

void MessageLog::openingWindow( ) {
	if ( _window_open == true ) {
		_time++;
	}
	if ( _time > OPENING_WINDOW_TIME ) {
		_window_open = false;
		_line_font.erase( _line_font.begin( ), _line_font.end( ) );
		_num.erase( _num.begin( ), _num.end( ) );
		_time = 0;
	}
}
