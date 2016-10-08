#pragma once
#include "smart_ptr.h"
#include "mathematics.h"
#include <string>
#include <vector>

PTR ( MessageLog );
// å„Ç≈GlobalïœêîÇ…
const int GAME_SCREEN_WIDTH = 1920;
const int GAME_SCREEN_HEIGHT = 1080;
const int OPENING_WINDOW_TIME = 300;
const int FONT_POS_X = GAME_SCREEN_WIDTH / 18;
const int ONE_LINE_FONT_POS_Y = GAME_SCREEN_HEIGHT * 74 / 96;
const int TWO_LINE_FONT_POS_Y = GAME_SCREEN_HEIGHT * 80 / 96;
const int THREE_LINE_FONT_POS_Y = GAME_SCREEN_HEIGHT * 86 / 96;

class MessageLog {
public:
	enum MESSAGE_TYPE {
		NO_MOVE,
		USE_WAZA,
		FAILURE_WAZA,
		LEARN_WAZA,
		SEAL_WAZA,
		HEAL,
		STAMINA_HEAL,
		HALF_STAMINA,
		HANGER,
		CRISIS_STAMINA,
		NO_STAMINA,
		DAMAGE,
		STATE_ABNORMAL,
		CURE_ABNORMAL,
		NO_CHANGE_ABNORMAL,
		PROTECT_ABNORMAL,
		CHANGE_SPEED,
		CURE_SPEED,
		NO_CHANGE_SPEED,
		CHANGE_BUFF,
		CURE_BUFF,
		NO_CHANGE_BUFF,
		KNOCK_DOWN,
		PLAYER_DOWN,
		PLAYER_REVIVE,
		GET_EX,
		LV_UP,
		CLEAR,
		USE_ITEM,
		THROW_ITEM,
		EQUIPMENT_ITEM,
		DISARM_ITEM,
		ON_THE_ITEM,
		PICK_ITEM,
		PUT_ITEM,
		STEP_MYSTERY,
		STEP_ALCKEMY,
	};

	struct FONT_COLOR {
		int r;
		int g;
		int b;
	};
public:
	MessageLog( );
	~MessageLog( );
public:
	void init( );
	void update( );
	void createFont( std::string name, std::string waza, std::string item, int num, MESSAGE_TYPE message_type );
private:
	void draw( );
	void backgroundDraw( );
	void drawMessage( );
	void openingWindow( );
private:
	int _window_hundle;
	int _message_font;
	int _width;
	int _height;
	int _time;
	bool _window_open;
	std::vector<std::string> _line_font;

	std::vector<int> _num;
};

