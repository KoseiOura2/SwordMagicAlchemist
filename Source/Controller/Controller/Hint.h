#pragma once
#include "Icon.h"
#include "Framework.h"

PTR ( Hint )

	const int HINT_WINDOW_HEIGHT = 730;
	const int HINT_WINDOW_WIDTH = 1226;
	const int HINT_WINDOW_POS_X = SCREEN_WIDTH / 2 - HINT_WINDOW_WIDTH / 2;
	const int HINT_WINDOW_POS_Y = 128;

class Hint : public Icon {
public:
	Hint( Vector2 pos );
	~Hint( );
	void touch( );
private:
	int _window;	// 表示するウィンドウ
};

