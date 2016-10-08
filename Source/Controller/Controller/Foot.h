#pragma once
#include "icon.h"

PTR( Foot )
PTR( NextFloor )
PTR( NetworkController )
PTR( Item )

class Foot : public Icon {
public:
	Foot( Vector2 pos, NetworkControllerPtr network, NextFloorPtr next_floor, ItemPtr item );
	~Foot( );
	void touch( );
	void close( );
	bool isFootItem( );
private:
	NextFloorPtr _next_floor;
	ItemPtr _item;
	NetworkControllerPtr _network;
	bool _foot_open;
};

