#pragma once
#include "smart_ptr.h"
#include "mathematics.h"
#include "Framework.h"
#include "CharacterStatus.h"
#include <string>

PTR ( UIApp );
PTR ( Player );

//---------------------------------- ＨＰバー表示位置 -------------------------------------------------//
const int HP_BAR_LEFT             = SCREEN_WIDTH / 2;
const int HP_BAR_RIGHT            = HP_BAR_LEFT + 450;
const int HP_BAR_UPPER            = SCREEN_HEIGHT / 15;
const int HP_BAR_LOWER            = HP_BAR_UPPER + 90;
const int HP_BAR_GAUGE_RIGHT      = HP_BAR_RIGHT - 1;
const int HP_BAR_GAUGE_LEFT       = HP_BAR_LEFT + 1;
const int HP_BAR_GAUGE_UPPER      = HP_BAR_UPPER + 1;
const int HP_BAR_GAUGE_LOWER      = HP_BAR_LOWER - 1;
const int HP_CHARA_POS_X          = HP_BAR_GAUGE_LEFT + 100;
const int HP_CHARA_POS_Y          = HP_BAR_GAUGE_UPPER + 30;
//---------------------------------- スタミナバー表示位置 ---------------------------------------------//
const int STAMINA_BAR_SIZE        = 256;
const int STAMINA_BAR_LEFT        = SCREEN_WIDTH * 10 / 13;
const int STAMINA_BAR_RIGHT       = STAMINA_BAR_LEFT + STAMINA_BAR_SIZE;
const int STAMINA_BAR_UPPER       = SCREEN_HEIGHT * 2 / 11;
const int STAMINA_BAR_LOWER       = STAMINA_BAR_UPPER + STAMINA_BAR_SIZE;
const int STAMINA_CHARA_POS_X_1   = STAMINA_BAR_LEFT - 200;
const int STAMINA_CHARA_POS_Y_1   = STAMINA_BAR_UPPER + 50;
const int STAMINA_CHARA_POS_Y_2   = STAMINA_BAR_UPPER + 50;
//---------------------------------- 階層表示位置 -------------------------------------------------//
const int FLOOR_LEVEL_X           = SCREEN_WIDTH / 20;
const int FLOOR_LEVEL_Y           = HP_BAR_GAUGE_UPPER + 40;
//---------------------------------- プレイヤーの名前表示位置 -------------------------------------------------//
const int PLAYER_NAME_X           = SCREEN_WIDTH * 2 / 9;
const int PLAYER_Y                = HP_BAR_GAUGE_UPPER + 40;
//---------------------------------- プレイヤーのレベル表示位置 -------------------------------------------------//
const int PLAYER_LEVEL_X          = SCREEN_WIDTH * 2 / 5;
//---------------------------------- 階段移動ウィンドウ表示位置 -------------------------------------------------//
const int STAIR_WINDOW_X          = SCREEN_WIDTH / 7;
const int STAIR_WINDOW_Y          = SCREEN_HEIGHT / 3;

const int STAMINA_RESET_TIME      = 180;
const int VISIBLE_TIME            = 30;

class UIApp {
public:
	UIApp( );
	~UIApp( );
public:
	void init( );
	void update( );
	void setFloorLevel( int floor_level );
	void setPlayerName( std::string name );
	void setPlayerLevel( int level );
	void setPlayerStatus( STATUS_DATA status );
	void setPlayerStamina( int stamina );
	void setFluctuationStamina( bool fluctuation );
	void setStairWindow( bool window );
private:
	void draw( );
	void drawFloorLevel( );
	void drawPlayerName( );
	void drawPlayerLevel( );
	void drawHpBar( );
	void drawStaminaBar( );
	void drawStairWindow( );
private:
	int _floor_font;
	int _player_font;
	int _hp_font;
	int _hp_back_font;
	int _stamina_font;
	int _stair_window_font;
	std::string _floor_chara;
	std::string _player_name_chara;
	std::string _player_level_chara;
	std::string _hp_chara;
	std::string _stamina_chara;
	std::string _stair_window_font_chara;
	int _hp_bar_handle;
	int _hp_bar_gauge_handle;
	int _stamina_bar_handle;
	int _stamina_bar_gauge_handle;
	int _stair_window_handle;
private:
	int _stamina_bar_time;
	bool _stamina_flag;
	int _visible_count;
	int _visible_time;
	bool _visible_stamina_bar;
private:
	int _floor_level;
	std::string _player_name;
	int _player_level;
	STATUS_DATA _player_status;
	int _player_stamina;
	bool _fluctuation_stamina;
	bool _stair_window;
};

