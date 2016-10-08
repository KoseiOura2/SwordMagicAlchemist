#pragma once
#include "smart_ptr.h"

PTR ( Title );

const int TITLE_FONT_NUM = 5;

class Title {
public:
	Title( );
	~Title( );
public:
	void loadGraph( );
	void deleteGraph( );
	void init( );
	void update( );
	void clearDraw( );
	void gameOverDraw( );
private:
	void draw( );
	void fontDraw( );
private:
	int _title_logo;
	int _clear;
	int _background;
	int _game_over;
	int _title_font[ TITLE_FONT_NUM ];
	int _font_index;
	int _time;
	bool _flag;
};

