#pragma once
#include "Framework.h"
#include "mathematics.h"

PTR( NextFloor );
PTR( NetworkController );

class NextFloor {

public:
	NextFloor( NetworkControllerPtr network );
	~NextFloor( );
	void update( );
	void init( );
	void setCheckFlag( bool flag );
	bool getCheckFlag( );
	bool isGoNext( );
private:
	const int WINDOW_WIDTH = 700;
	const int WINDOW_POS_X = SCREEN_WIDTH / 2 - WINDOW_WIDTH / 2;
	const int WINDOW_POS_Y = SCREEN_HEIGHT / 2;
	const int FONT_SIZE = 30;

	const int STRING_POS_X = WINDOW_POS_X + FONT_SIZE;
	const int STRING_POS_Y = WINDOW_POS_Y + FONT_SIZE;
	const int SELECT_POS_X = WINDOW_POS_X + WINDOW_WIDTH - FONT_SIZE * 6;  
	
	const int NONE_CHOICE = -1;
private:
	void draw( );
	int isNextFloor( );
	void drawString( Vector2 pos, const std::string str );
private:
	NetworkControllerPtr _network;
	int _window;
	int _select_window;
	int _font;
	bool _check_flag;
	bool _go_next;
};

