#include "MessageLog.h"
#include "Framework.h"
#include "Viewer.h"
#include "DxLib.h"

MessageLog::MessageLog( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	_window_hundle   = viewer->loadGraph( "work/app_UI/window/window_message.png" );
	_message_font    = CreateFontToHandle( "HGP�n�p�p�޼��UB", 52, -1, -1 );

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
		_line_font.push_back( name + "�͂������Ȃ��I" );
		_num.push_back( num );
		break;
	case USE_WAZA:
		_line_font.push_back( name + "�� " + waza + "�����肾�����B" );
		_num.push_back( num );
		break;
	case FAILURE_WAZA:
		_line_font.push_back( waza + "�͎��s�����B" );
		_num.push_back( num );
		break;
	case LEARN_WAZA:
		_line_font.push_back( name + "�� " + waza + "���o�����B" );
		_num.push_back( num );
		break;
	case SEAL_WAZA:
		_line_font.push_back( "�X�L���͕��󂳂�Ă���I" );
		_num.push_back( num );
		break;
	case HEAL:
		_line_font.push_back( name + "��HP���@%d�񕜂����B" );
		_num.push_back( num );
		break;
	case STAMINA_HEAL:
		_line_font.push_back( name + "�͂��Ȃ����@%d�񕜂����B" );
		_num.push_back( num );
		break;
	case HALF_STAMINA:
		_line_font.push_back( "���Ȃ����ւ����B" );
		_num.push_back( num );
		break;
	case HANGER:
		_line_font.push_back( name + "�󕠂ł��炭�炵�Ă����B" );
		_num.push_back( num );
		break;
	case CRISIS_STAMINA:
		_line_font.push_back( name + "�����H�ׂȂ��Ƃ܂����I" );
		_num.push_back( num );
		break;
	case DAMAGE:
		_line_font.push_back( name + "�� %d�̃_���[�W�B" );
		_num.push_back( num );
		break;
	case STATE_ABNORMAL:
		_line_font.push_back( name + "��" + waza + "�ɂ��������B" );
		_num.push_back( num );
		break;
	case CURE_ABNORMAL:
		_line_font.push_back( name + "�͏�Ԉُ킪�Ȃ������B" );
		_num.push_back( num );
		break;
	case NO_CHANGE_ABNORMAL:
		_line_font.push_back( name + "�͂���ȏ㈫���Ȃ�Ȃ��B" );
		_num.push_back( num );
		break;
	case PROTECT_ABNORMAL:
		_line_font.push_back( name + "�͏�Ԉُ킩��g��������B" );
		_num.push_back( num );
		break;
	case CHANGE_SPEED:
		_line_font.push_back( name + "��" + waza );
		_num.push_back( num );
		break;
	case CURE_SPEED:
		_line_font.push_back( name + "�̑��������ɖ߂����B" );
		_num.push_back( num );
		break;
	case NO_CHANGE_SPEED:
		_line_font.push_back( name + "�͂���ȏ�" + waza );
		_num.push_back( num );
		break;
	case CHANGE_BUFF:
		_line_font.push_back( name + "��" + waza );
		_num.push_back( num );
		break;
	case CURE_BUFF:
		_line_font.push_back( name + "�̍U���͂����ɖ߂����B" );
		_num.push_back( num );
		break;
	case NO_CHANGE_BUFF:
		_line_font.push_back( name + "�͂���ȏ�" + waza );
		_num.push_back( num );
		break;
	case KNOCK_DOWN:
		_line_font.push_back( name + "��|�����B" );
		_num.push_back( num );
		break;
	case PLAYER_DOWN:
		_line_font.push_back( name + "�͓|��Ă��܂����B" );
		_num.push_back( num );
		break;
	case PLAYER_REVIVE:
		_line_font.push_back( name + "�͕��������B" );
		_num.push_back( num );
		break;
	case GET_EX:
		_line_font.push_back( name + "�� %d�̌o���l�𓾂��B" );
		_num.push_back( num );
		break;
	case LV_UP:
		_line_font.push_back( name + "�� Lv.%d�ɂ��������B" );
		_num.push_back( num );
		break;
	case CLEAR:
		_line_font.push_back( "�_���W�������N���A�����B" );
		_num.push_back( num );
		break;
	case USE_ITEM:
		_line_font.push_back( item + "���������B" );
		_num.push_back( num );
		break;
	case THROW_ITEM:
		_line_font.push_back( item + "�𓊂����B" );
		_num.push_back( num );
		break;
	case EQUIPMENT_ITEM:
		_line_font.push_back( item + "�𑕔������B" );
		_num.push_back( num );
		break;
	case DISARM_ITEM:
		_line_font.push_back( item + "���O�����B" );
		_num.push_back( num );
		break;
	case ON_THE_ITEM:
		_line_font.push_back( item + "�ɂ̂����B" );
		_num.push_back( num );
		break;
	case PICK_ITEM:
		_line_font.push_back( item + "���E�����B" );
		_num.push_back( num );
		break;
	case PUT_ITEM:
		_line_font.push_back( item + "��u�����B" );
		_num.push_back( num );
		break;
	case STEP_MYSTERY:
		_line_font.push_back( name + "���ӂ񂾁I" );
		_num.push_back( num );
		break;
	case STEP_ALCKEMY:
		_line_font.push_back( "�B���|�C���g���{�ɂȂ����I" );
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
