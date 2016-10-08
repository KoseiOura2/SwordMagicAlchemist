#include "NextFloor.h"
#include "DxLib.h"
#include <string>

const int SCREEN_WIDTH = 1920 / 2;
const int SCREEN_HEIGHT = 1080 / 2;

NextFloor::NextFloor( ) {
	_font = CreateFontToHandle( "HGPënâpäp∫ﬁºØ∏UB", 100, -1, -1 ) ;
	init( );
}


NextFloor::~NextFloor( ) {

}

void NextFloor::init( ) {
	_floor_level = 0;
}

void NextFloor::update( ) {
	draw( );
}

void NextFloor::draw( ) {
	std::string font = "B%dF";
	DrawFormatStringToHandle( SCREEN_WIDTH * 9 / 10, SCREEN_HEIGHT * 4 / 5 , GetColor( 255, 255, 255 ),
							_font, font.c_str( ), _floor_level );
}

void NextFloor::countFloorLevel( bool next ) {
	if ( next == true ) {
		_floor_level++;
	} else {
		_floor_level--;
	}
}

int NextFloor::getFloorLevel( ) {
	return _floor_level;
}
