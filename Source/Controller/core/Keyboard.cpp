#include "Keyboard.h"
#include "DxLib.h"

Keyboard::Keyboard( ) {
	
}


Keyboard::~Keyboard( ) {
}

void Keyboard::initialize( ) {
	_convert[ "LEFT" ]  = KEY_INPUT_LEFT;
	_convert[ "UP"]     = KEY_INPUT_UP;
	_convert[ "RIGHT" ] = KEY_INPUT_RIGHT;
	_convert[ "DOWN" ]  = KEY_INPUT_DOWN;
	_convert[ "W" ]  = KEY_INPUT_W;
	_convert[ "SPACE" ]  = KEY_INPUT_SPACE;
	_convert[ "9" ]  = KEY_INPUT_NUMPAD9;
	_convert[ "8" ]  = KEY_INPUT_NUMPAD8;
	_convert[ "7" ]  = KEY_INPUT_NUMPAD7;
	_convert[ "6" ]  = KEY_INPUT_NUMPAD6;
	_convert[ "5" ]  = KEY_INPUT_NUMPAD5;
	_convert[ "4" ]  = KEY_INPUT_NUMPAD4;
	_convert[ "3" ]  = KEY_INPUT_NUMPAD3;
	_convert[ "2" ]  = KEY_INPUT_NUMPAD2;
	_convert[ "1" ]  = KEY_INPUT_NUMPAD1; 
	
	_convert[ "ONE" ]  = KEY_INPUT_1; 
	_convert[ "TWO" ]  = KEY_INPUT_2; 
	_convert[ "THREE" ]  = KEY_INPUT_3;
	_convert[ "DEL" ] = KEY_INPUT_DELETE;
	_convert[ "ENTER" ] = KEY_INPUT_RETURN;
}

void Keyboard::finalize( ) {

}

void Keyboard::update( ) {
	_before_keys = _now_keys;
	GetHitKeyStateAll( _now_keys.buffer );
}

bool Keyboard::isHoldKey( std::string key ) {
	int dxkey = _convert[ key ];
	return _now_keys.buffer[ dxkey ] == 1;
}

bool Keyboard::isPushKey( std::string key ) {
	int dxkey = _convert[ key ];
	return ( _now_keys.buffer[ dxkey ] == 1 ) && ( _before_keys.buffer[ dxkey ] == 0 );
}