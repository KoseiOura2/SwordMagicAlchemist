#include "Title.h"
#include "Framework.h"
#include "Viewer.h"

const int LOGO_POS_X = 0;
const int LOGO_POS_Y = 0;

const int FONT_SIZE_X = 910;
const int FONT_POS_X = SCREEN_WIDTH / 2 - FONT_SIZE_X / 2;
const int FONT_POS_Y = SCREEN_HEIGHT * 4 / 5;

const int FONT_CHANGE_TIME = 2;

Title::Title( ) {

}


Title::~Title( ) {

}

void Title::loadGraph( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	_title_logo      = viewer->loadGraph( "work/title_logo/title_logo.png" );
	_clear           = viewer->loadGraph( "work/app_UI/text_ui/gameclear02.png" );
	_game_over       = viewer->loadGraph( "work/app_UI/text_ui/gameover.png" );
	_background      = viewer->loadGraph( "work/title_logo/2d_haikei_tb.jpg" );
	_title_font[ 0 ] = viewer->loadGraph( "work/app_UI/title_font_animation_tb/title_font_tb_1.png" );
	_title_font[ 1 ] = viewer->loadGraph( "work/app_UI/title_font_animation_tb/title_font_tb_2.png" );
	_title_font[ 2 ] = viewer->loadGraph( "work/app_UI/title_font_animation_tb/title_font_tb_3.png" );
	_title_font[ 3 ] = viewer->loadGraph( "work/app_UI/title_font_animation_tb/title_font_tb_4.png" );
	_title_font[ 4 ] = viewer->loadGraph( "work/app_UI/title_font_animation_tb/title_font_tb_5.png" );
}

void Title::deleteGraph( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	viewer->deleteGraph( _title_logo );
	viewer->deleteGraph( _background );
	viewer->deleteGraph( _title_font[ 0 ] );
	viewer->deleteGraph( _title_font[ 1 ] );
	viewer->deleteGraph( _title_font[ 2 ] );
	viewer->deleteGraph( _title_font[ 3 ] );
	viewer->deleteGraph( _title_font[ 4 ] );
}

void Title::init( ) {
	_font_index = 0;
	_time = 0;
	_flag = false;
}

void Title::update( ) {
	draw( );
}

void Title::draw( ) {
	FrameworkPtr fw     = Framework::getInstance( );
	ViewerPtr viewer    = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	viewer->drawGraph( LOGO_POS_X, LOGO_POS_Y, _background );
	viewer->drawGraph( LOGO_POS_X, LOGO_POS_Y, _title_logo );
	fontDraw( );
}

void Title::clearDraw( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	viewer->drawGraph( LOGO_POS_X, LOGO_POS_Y, _background );
	viewer->drawGraph( SCREEN_WIDTH / 2 - 600, SCREEN_HEIGHT / 2 -80 , _clear );
	fontDraw( );
}

void Title::gameOverDraw( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	viewer->drawGraph( LOGO_POS_X, LOGO_POS_Y, _background );
	viewer->drawGraph( SCREEN_WIDTH / 2 - 565, SCREEN_HEIGHT / 2 -80 , _game_over );
	fontDraw( );
}

void Title::fontDraw( ) {
	FrameworkPtr fw     = Framework::getInstance( );
	ViewerPtr viewer    = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	_time++;
	if ( _time > FONT_CHANGE_TIME && _flag == false ) {
		_font_index++;
		_time = 0;
	}
	if ( _time > FONT_CHANGE_TIME && _flag == true ) {
		_font_index--;
		_time = 0;
	}
	if ( _font_index > 4 ) {
		_font_index = 4;
		_flag = true;
	}
	if ( _font_index < 0 ) {
		_font_index = 0;
		_flag = false;
	}
	viewer->drawGraph( FONT_POS_X, FONT_POS_Y, _title_font[ _font_index ] );
}