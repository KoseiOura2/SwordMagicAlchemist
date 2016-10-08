#pragma once
#include "smart_ptr.h"
#include "mathematics.h"
#include "NetworkController.h"

PTR( Button );
PTR( NetworkController );
PTR( IconManeger );

class Button {
public:
	Button( NetworkControllerPtr network, IconManegerPtr icon_maneger );
	~Button( );
	void update( );
	bool getButtonTouch( );
private:
	const int WIDTH_INTERVAL = 128;
	const int HEIGHT_INTERVAL = 128;
	const int SLIDE_DISTANCE = 120;
	const int SLANT_DISTANCE = 100;	//Å@éŒÇﬂÇÃéûÇÃSLIDE_DISTANCE
	const int PUSH_TIME = 40;
	const int WAIT_DELAY = 12;
	const int ATTACK_DELAY = 5;
	const int IMAGE_SIZE = 128;
	enum DIR {
		NONE,
		LOWER_LEFT,
		LOWER,
		LOWER_RIGHT,
		LEFT,
		WAIT,
		RIGHT,
		UPPER_LEFT,
		UPPER,
		UPPER_RIGHT,	
	};
private:
	void draw( );
	void drawNone( );
	void drawLowerLeft( );
	void drawLower( );
	void drawLowerRight( );
	void drawLeft( );
	void drawWait( );
	void drawRight( );
	void drawUpperLeft( );
	void drawUpper( );
	void drawUpperRight( );
	void attack( );
	void move( );
	void reset( );
private:
	NetworkControllerPtr _network;
	IconManegerPtr _icon_maneger;
	Vector2 _pos;
	Vector2 _slide_pos;
	Vector2 _slide;
	bool _touch_flag;
	bool _wait_flag;
	bool _separate_flag;
	int _wait_count;
	int _attack_count;
	Network::CTRL_PHASE _phase;
	DIR _push_state;
	//âÊëú
	int _lower_left;
	int _lower;
	int _lower_right;
	int _left;
	int _wait;
	int _right;
	int _upper_left;
	int _upper;
	int _upper_right;
	int _lower_left_push;
	int _lower_push;
	int _lower_right_push;
	int _left_push;
	int _wait_push;
	int _right_push;
	int _upper_left_push;
	int _upper_push;
	int _upper_right_push;

};

