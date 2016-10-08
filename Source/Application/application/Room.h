#pragma once

#include "smart_ptr.h"
#include "Vector.h"
#include "Floor.h"
#include <vector>
PTR( Room );

class Room {
public:
	Room( const Floor::FLOOR orijin, const int width, const int height );
	~Room( );
private:
	void createRoom( );
private:
	Floor::FLOOR _orijin_tile;
	int _room_width;
	int _room_height;
	Floor::FLOOR _tile[ 50 / 3 ][ 30 / 2 ]; //•”‰®‚ÌÅ‘å‚Ì‘å‚«‚³‚ğŠm•Û‚µ‚Ä‚¨‚­
};

