#pragma once
#include "smart_ptr.h"

PTR ( Turn );

class Turn {
public:
	enum STATE {
		PLAYER_TURN,
		ENEMY_TURN,
	};
public:
	Turn( );
	~Turn( );
public:
	void init( );
	void changeTurn( );
	STATE getState( );
	int getTurnCount( );
private:
private:
	int _count;
	STATE _state;
};

