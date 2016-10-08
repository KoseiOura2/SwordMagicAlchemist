#include "Turn.h"

Turn::Turn( ) {
	init( );
}


Turn::~Turn( ) {
}

void Turn::init( ) {
	_count = 0;
	_state = PLAYER_TURN;
}

void Turn::changeTurn( ) {
	switch ( _state ) {
		case PLAYER_TURN :
			_state = ENEMY_TURN;
			break;
		case ENEMY_TURN  :
			_state = PLAYER_TURN;
			_count++;
			break;
	}
}

Turn::STATE Turn::getState( ) {
	return _state;
}

int Turn::getTurnCount( ) {
	return _count;
}