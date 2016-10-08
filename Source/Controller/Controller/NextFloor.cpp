#include "NextFloor.h"
#include "Viewer.h"
#include "Touch.h"
#include "Dxlib.h"
#include "NetworkController.h"

NextFloor::NextFloor( NetworkControllerPtr network ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	_check_flag = false;
	_network = network;
	_window = viewer->loadGraph( "work/ctrl_UI/window/window_message.png" );
	_font = CreateFontToHandle( "HGPënâpäp∫ﬁºØ∏U", FONT_SIZE, -1, -1 ) ;
	_go_next = false;
}


NextFloor::~NextFloor( ) {
}

void NextFloor::update( ) {

	if ( _check_flag == true ) {
		if ( isNextFloor( ) != NONE_CHOICE ) { 
			_check_flag = false;
		}
	}
}

void NextFloor::init( ) {
	_go_next = false;
}

void NextFloor::draw( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	viewer->drawGraph( WINDOW_POS_X, WINDOW_POS_Y, _window );

	drawString( Vector2( STRING_POS_X, STRING_POS_Y ), "äKíiÇ™Ç†ÇÈÅBÅ@Å@ç~ÇËÇÈÅH" );
	drawString( Vector2( SELECT_POS_X, STRING_POS_Y ), "ÇÕÇ¢" );
	drawString( Vector2( SELECT_POS_X, STRING_POS_Y + FONT_SIZE * 2 ), "Ç¢Ç¢Ç¶" );

}

void NextFloor::drawString( Vector2 pos , const std::string str ) {
	unsigned int color = GetColor( 255, 255, 255 ) ;
	DrawFormatStringToHandle( ( int )pos.x, ( int )pos.y, color, _font, str.c_str( ) );
}

int NextFloor::isNextFloor( ) {
	FrameworkPtr fw = Framework::getInstance( );
	TouchPtr touch = std::dynamic_pointer_cast< Touch >( fw->getTask( typeid( Touch ).name( ) ) );
	int result = NONE_CHOICE;

	draw( );

	if ( touch->isTouch ( Vector2( SELECT_POS_X, STRING_POS_Y ), 100, FONT_SIZE ) ) {
		_network->setSendNextFloor( Network::NEXT_FLOOR::GO_NEXT );
		result = true;
		_go_next = true;
		touch->rejectTouch( );
	} else if ( touch->isTouch( Vector2( SELECT_POS_X, STRING_POS_Y + FONT_SIZE * 2 ), 100, FONT_SIZE )) {
		_network->setSendNextFloor( Network::NEXT_FLOOR::NOT_NEXT );
		result = false;
		touch->rejectTouch( );
	}
	 return result;
}

void NextFloor::setCheckFlag( bool flag ) {
	_check_flag = flag;
}

bool NextFloor::getCheckFlag( ) {
	return _check_flag;
}

bool NextFloor::isGoNext( ) {
	return _go_next;
}