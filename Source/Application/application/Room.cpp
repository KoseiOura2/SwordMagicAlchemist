#include "Room.h"


Room::Room( Floor::TILE orijin, int width, int height ) {
	_orijin_tile = orijin;
	_room_width = width;
	_room_height = height;
	createRoom( );
}


Room::~Room( ) {
}

void Room::createRoom( ) {
	
}
