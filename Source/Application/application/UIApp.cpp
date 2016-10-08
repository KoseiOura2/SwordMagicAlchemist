#include "UIApp.h"
#include "Viewer.h"
#include "Player.h"
#include "Dxlib.h"

UIApp::UIApp( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	_floor_font               = CreateFontToHandle( "HGP�n�p�p�޼��UB", 100, -1, -1 );
	_player_font              = CreateFontToHandle( "HGP�n�p�p�޼��UB", 58, -1, -1 );
	_hp_bar_handle            = viewer->loadGraph( "work/app_UI/ui_pc_hpbar/ui_pc_hpbar.png" );
	_hp_bar_gauge_handle      = viewer->loadGraph( "work/app_UI/ui_pc_hpbar/ui_pc_hpbar_gauge.png" );
	_hp_font                  = CreateFontToHandle( "HGP�n�p�p�޼��UB", 30, -1, DX_FONTTYPE_EDGE );
	_hp_back_font             = CreateFontToHandle( "HGP�n�p�p�޼��UB", 32, -1, -1 );
	_stamina_bar_handle       = viewer->loadGraph( "work/UI/stamina/ui_pc_hunger_meter_1.png" );
	_stamina_bar_gauge_handle = viewer->loadGraph( "work/UI/stamina/ui_pc_hunger_meter_2.png" );
	_stamina_font             = CreateFontToHandle( "HGP�n�p�p�޼��UB", 58, -1, -1 );
	_stair_window_handle      = viewer->loadGraph( "work/app_UI/window/window_message.png" );
	_stair_window_font        = CreateFontToHandle( "HGP�n�p�p�޼��UB", 50, -1, -1 );

	_player_name         = "";
	_player_level        = 0;
	_player_status       = STATUS_DATA( );
	_player_stamina      = 0;
	_fluctuation_stamina = false;
	_stair_window        = false;
	init( );
}


void UIApp::init( ) {
	_stamina_bar_time    = 0;
	_stamina_flag        = true;
	_visible_time        = 0;
	_visible_stamina_bar = false;
	_fluctuation_stamina = false;
	_stair_window        = false;
}

UIApp::~UIApp( ) {

}

void UIApp::update( ) {
	draw( );
}

void UIApp::draw( ) {
	// �K�w�\��
	drawFloorLevel( );
	// �v���C���[�̖��O�\��
	drawPlayerName( );
	// �v���C���[�̃��x���\��
	drawPlayerLevel( );
	// �g�o�o�[�\��
	drawHpBar( );
	// �X�^�~�i�o�[�\��
	drawStaminaBar( );
	// �K�i�ړ��E�B���h�E�\��
	drawStairWindow( );
}

void UIApp::drawFloorLevel( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	_floor_chara = "B%dF";
	DrawFormatStringToHandle( FLOOR_LEVEL_X , FLOOR_LEVEL_Y , GetColor( 255, 255, 255 ),
							_floor_font, _floor_chara.c_str( ), _floor_level );
}

void UIApp::drawPlayerName( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	_player_name_chara = _player_name;
	DrawFormatStringToHandle( PLAYER_NAME_X , PLAYER_Y , GetColor( 255, 140, 0 ),
							_player_font, _player_name_chara.c_str( ) );
}

void UIApp::drawPlayerLevel( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	_player_level_chara = "Lv %d";
	DrawFormatStringToHandle( PLAYER_LEVEL_X , PLAYER_Y , GetColor( 255, 255, 255 ),
							_player_font, _player_level_chara.c_str( ), _player_level );
}

void UIApp::drawHpBar( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	int right_bar_gauge_pos = ( HP_BAR_GAUGE_RIGHT - HP_BAR_GAUGE_LEFT ) * _player_status.life / _player_status.max_life;
	viewer->drawRectGraph( HP_BAR_GAUGE_LEFT, HP_BAR_GAUGE_UPPER, 0, 0, right_bar_gauge_pos, HP_BAR_GAUGE_LOWER - HP_BAR_GAUGE_UPPER, _hp_bar_gauge_handle );
	viewer->drawGraph( HP_BAR_LEFT, HP_BAR_UPPER, _hp_bar_handle );
	_hp_chara = "HP  %d / %d";
	DrawFormatStringToHandle( HP_CHARA_POS_X , HP_CHARA_POS_Y , GetColor( 255, 255, 255 ),
							_hp_font, _hp_chara.c_str( ), _player_status.life, _player_status.max_life );
}

void UIApp::drawStaminaBar( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	// ���Ȃ���50��25�ɂȂ�����\��
	if ( _player_stamina == 50 || _player_stamina == 25 || _fluctuation_stamina == true ) {
		_stamina_flag = true;
		_fluctuation_stamina = false;
	}
	// ��莞�ԓ��X�^�~�i�o�[��\��
	if ( _stamina_flag ) {
		_stamina_bar_time++;
	}
	// ��莞�Ԃ𒴂�����t�h������
	if ( _stamina_bar_time > STAMINA_RESET_TIME ) {
		_stamina_bar_time = 0;
		_stamina_flag = false;
	}
	// ���Ȃ����O�ɂȂ�����_�ŊJ�n
	if ( _player_stamina == 0 ) {
		_visible_time++;
	}
	// �����遨�����
	if ( _visible_time == VISIBLE_TIME ) {
		_visible_time = 0;
		if ( _visible_stamina_bar == true ) {
			_visible_stamina_bar = false;
		} else {
			_visible_stamina_bar = true;
		}
	}

	// �X�^�~�i�o�[�\��
	if ( _stamina_bar_time > 0 || ( _player_stamina < 10 && _player_stamina != 0 ) || _visible_stamina_bar == true ) {
		int gauge_size = ( STAMINA_BAR_SIZE ) * _player_stamina / MAX_STAMINA;
		viewer->drawRectGraph( STAMINA_BAR_LEFT, STAMINA_BAR_UPPER + ( STAMINA_BAR_SIZE - gauge_size ), 0, 0, STAMINA_BAR_RIGHT - STAMINA_BAR_LEFT, gauge_size, _stamina_bar_gauge_handle );
		//viewer->drawExtendGraph( STAMINA_BAR_LEFT, STAMINA_BAR_LOWER - upper_bar_gauge_pos, STAMINA_BAR_RIGHT, STAMINA_BAR_LOWER - 3, _stamina_bar_gauge_handle );
		viewer->drawGraph( STAMINA_BAR_LEFT, STAMINA_BAR_UPPER, _stamina_bar_handle );

		_stamina_chara = "���Ȃ�";
		DrawFormatStringToHandle( STAMINA_CHARA_POS_X_1 , STAMINA_CHARA_POS_Y_1 , GetColor( 255, 255, 255 ),
								_stamina_font, _stamina_chara.c_str( ) );
		_stamina_chara = "%d";
		int length = GetDrawFormatStringWidthToHandle( _stamina_font, _stamina_chara.c_str( ), _player_stamina ) ;
		int left = STAMINA_BAR_RIGHT - ( ( STAMINA_BAR_RIGHT - STAMINA_BAR_LEFT ) / 2 ) - length / 2;
		DrawFormatStringToHandle( left , STAMINA_CHARA_POS_Y_2 , GetColor( 255, 255, 255 ),
								_stamina_font, _stamina_chara.c_str( ), _player_stamina );
	}
}

void UIApp::drawStairWindow( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	if ( _stair_window == true ) {
		viewer->drawGraph( STAIR_WINDOW_X, STAIR_WINDOW_Y, _stair_window_handle );
		_stair_window_font_chara = "�K�w�ړ����܂����H\n �I��ł�������";
		DrawFormatStringToHandle( STAIR_WINDOW_X + 500, STAIR_WINDOW_Y + 30, GetColor( 255,255, 255 ),
							_stair_window_font, _stair_window_font_chara.c_str( ) );
	}
}

void UIApp::setFloorLevel( int floor_level ) {
	_floor_level = floor_level;
}

void UIApp::setPlayerName( std::string name ) {
	_player_name = name;
}

void UIApp::setPlayerLevel( int level ) {
	_player_level = level;
}

void UIApp::setPlayerStatus( STATUS_DATA status ) {
	_player_status = status;
}
void UIApp::setPlayerStamina( int stamina ) {
	_player_stamina = stamina;
}
void UIApp::setFluctuationStamina( bool fluctuation ) {
	_fluctuation_stamina = fluctuation;
}
void UIApp::setStairWindow( bool window ) {
	_stair_window = window;
}
