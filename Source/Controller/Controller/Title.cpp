#include "Title.h"
#include "Framework.h"
#include "Viewer.h"



Title::Title( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	_background = viewer->loadGraph( "work/background/ctrl_back.jpg" );
	_title_font[ 0 ] = viewer->loadGraph( "work/ctrl_UI/title_font_animation/title_font_1.png" );
	_title_font[ 1 ] = viewer->loadGraph( "work/ctrl_UI/title_font_animation/title_font_2.png" );
	_title_font[ 2 ] = viewer->loadGraph( "work/ctrl_UI/title_font_animation/title_font_3.png" );
	_title_font[ 3 ] = viewer->loadGraph( "work/ctrl_UI/title_font_animation/title_font_4.png" );
	_title_font[ 4 ] = viewer->loadGraph( "work/ctrl_UI/title_font_animation/title_font_5.png" );

	init( );
}


Title::~Title( ) {

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
	viewer->drawGraph( 0, 0, _background );
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