#pragma once
#include "smart_ptr.h"

PTR ( NextFloor );

class NextFloor {
public:
	NextFloor( );
	~NextFloor( );
public:
	void init( );
	void update( );
	void countFloorLevel( bool next );
	int getFloorLevel( );
private:
	void draw( );
private:
	int _floor_level;
	int _font;
};
