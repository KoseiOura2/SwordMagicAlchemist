#pragma once
#include "smart_ptr.h"
#include "mathematics.h"
#include "Touch.h"

PTR ( IconManeger );
PTR ( Alchemy );
PTR ( Item );
PTR ( Skill );
PTR ( Hint );
PTR ( Option );
PTR ( NetworkController );
PTR ( Map );
PTR ( Camera );
PTR ( Foot );
PTR ( NextFloor );
PTR ( ItemImage );

const int UNDELAY_WIDTH = 1350;
const int UNDELAY_HEIGHT = 200;
const int ICON_NUM = 5;
const int ICON_WIDTH = 250;
const int ICON_HEIGHT = 170;

const int RETURN_WIDTH = 250;
const int RETURN_HEIGHT = 250;

const int DIRECTION_WIDTH = 250;
const int DIRECTION_HEIGHT = 250;

class IconManeger {
public:
	IconManeger( NetworkControllerPtr network, MapPtr map, CameraPtr camera, NextFloorPtr next_floor );
	~IconManeger( );
	void update( );
	void touch( );
	bool isOpenIcon( );
	bool isTouchDir( );	// 方向ボタンをタッチしたかどうか
	void setButtonTouch( bool flag );
	void init( );
private:
	enum ICON {
		NONE,
		SKILL,
		ITEM,
		ALCHEMY,
		HINT,
		OPTION,
		FOOT,
	};
private:
	void draw( );
	void close( ICON icon );	// 引数で指定されたもの以外すべて閉じる
	void revive( );	// 死亡に復活の石を持っているか
	void touchReturn( ); // 戻るボタンをタッチした時
private:
	AlchemyPtr _alchemy;
	Vector2 _alchemy_pos;
	ItemPtr _item;
	Vector2 _item_pos;
	SkillPtr _skill;
	Vector2 _skill_pos;
	HintPtr _hint;
	Vector2 _hint_pos;
	FootPtr	_foot;
	Vector2 _foot_pos;
	int _underlay;
	Vector2 _underlay_pos;
	NetworkControllerPtr _network;
	ItemImagePtr _item_image;
	ICON _open_icon;
	ICON _old_open;
	bool _separate_flag;		// 一度指を話したかどうかのフラグ
	bool _close_flag;			// 閉じることができるかどうかのフラグ
	Touch::TOUCH_STATE _old_state;	// 前回のタッチ状態を保存しておく変数
	int _return;	// 戻るボタン
	Vector2 _return_pos;
	int _direction;		// 方向ボタン
	Vector2 _direction_pos;
	bool _button_touch;
};

