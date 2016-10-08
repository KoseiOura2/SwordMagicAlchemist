#pragma once
#include "smart_ptr.h"
#include "Framework.h"
PTR ( Title );

const int TITLE_FONT_NUM = 5;
const int FONT_SIZE_X = 910;
const int FONT_POS_X = SCREEN_WIDTH / 2 - FONT_SIZE_X / 2;
const int FONT_POS_Y = SCREEN_HEIGHT / 2;

const int FONT_CHANGE_TIME = 2;

class Title {
public:
	Title( );
	~Title( );
public:
	void init( );
	void update( );
private:
	void draw( );
	void fontDraw( );
private:
	int _background;
	int _title_font[ TITLE_FONT_NUM ];
	int _font_index;
	int _time;
	bool _flag;
};

