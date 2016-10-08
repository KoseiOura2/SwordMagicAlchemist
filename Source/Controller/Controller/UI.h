#pragma once

#include "framework.h"
#include "smart_ptr.h"
#include "mathematics.h"
#include "CharacterStatus.h"
#include < vector >
PTR ( UI );
PTR ( NetworkController );

const int DEFAULT_FONT = 50;	// デフォルトの文字の大きさ
//---------------------------------- ＨＰバー -------------------------------------------------//
const int HP_WIDTH = 450;
const int HP_HEIGHT = 90;
const int HP_POS_X = SCREEN_WIDTH / 2 - HP_WIDTH / 2;
const int HP_POS_Y = HP_HEIGHT / 2;
const int HP_FONT_POS_X = HP_POS_X + HP_WIDTH / 4;
const int HP_FONT_POS_Y = HP_POS_Y + HP_HEIGHT / 4;
const int HP_FONT_SIZE = 30;
//---------------------------------- スタミナバー -------------------------------------------------//
const int STAMINA_WIDTH = 200;
const int STAMINA_HEIGHT = 200;
const int STAMINA_POS_X = SCREEN_WIDTH - STAMINA_WIDTH - 50;
const int STAMINA_POS_Y = ( HP_POS_Y + HP_HEIGHT / 2 ) - ( STAMINA_HEIGHT / 2 ) + 50;	// ＨＰバーと中心を合わせる
const int STAMINA_FONT_POS_X = STAMINA_POS_X - 200;
const int STAMINA_FONT_POS_Y = STAMINA_POS_Y + 50;
const int MAX_STAMINA = 100;
const int STAMINA_FONT_SIZE = 58;
//---------------------------------- 状態異常 -------------------------------------------------//
const int STATE_WIDTH = 200;
const int STATE_HEIGHT = 200;
const int STATE_POS_X = HP_POS_X - STATE_WIDTH - 50;
const int STATE_POS_Y = ( HP_POS_Y + HP_HEIGHT / 2 ) - ( STATE_HEIGHT / 2 ) + 50;
const int STATE_CHANGE_TIME = 20;
const int STATE_ALL_NORMAL = -1;	// どの状態異常にもかかっていない
//---------------------------------- レベル -------------------------------------------------//
const int LEVEL_POS_X = 50;
const int LEVEL_POS_Y = HP_POS_Y;
//---------------------------------- 階層 -------------------------------------------------//
const int FLOOR_POS_X = 50;
const int FLOOR_POS_Y = HP_POS_Y + 100;

const int STATE_TYPE_NUM = 3;	// 同時にかかる状態異常以上の最大数

class UI {
public:
	UI( NetworkControllerPtr network );
	~UI( );
	void update( );
private:
	void draw( );
	void drawLevel( );
	void drawFloorLevel( );
	void drawHPBar( );
	void drawStamina( );
	// 状態異常画像取得
	int getStateImage( );
	int getSpeedImage( );
	int getBuffImage( );
	// 状態異常画像設定
	void setStateImage( );
private:
	int _count;			 // 点滅用のカウント
	NetworkControllerPtr _network;
	int _hp_bar;		 // HPの外枠
	STATUS_DATA _status; // ステータス
	STATUS_DATA _old_status;
	int _stamina;		 // スタミナの現在値
	int _hp_gauge;		 // HPの中身
	int _hp_font;		 // HPの文字
	int _stamina_bar;	 // スタミナの外枠
	int _stamina_gauge;  // スタミナの中身
	int _stamina_font;	 // スタミナの文字
	int _level;			 // 今のレベル
	int _floor_level;	 // 今の階層
	int _default_font;	 // 特に指定がない場合の文字
	bool _state_set;
	// 状態異常画像
	int _poison;         // 毒
	int _paralysis;		 // 麻痺
	int _skill_seal;	 // スキル封印
	int _bind_tile;		 // 移動封印
	int _confuse;		 // 混乱
	// スピード画像
	int _slow;			 // 鈍足
	int _fast;			 // 速足
	// buff画像
	int _buff;			 // バフ(攻撃UP)
	int _debuff;		 // デバフ（攻撃DOWN）
	
	std::vector< int > _image_vector;	// 表示するイメージ
	int _num_image;		 // 表示するイメージ番号
	bool _image_set;	// イメージをセットしなおすかどうか
};

