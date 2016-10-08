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
	bool isTouchDir( );	// �����{�^�����^�b�`�������ǂ���
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
	void close( ICON icon );	// �����Ŏw�肳�ꂽ���̈ȊO���ׂĕ���
	void revive( );	// ���S�ɕ����̐΂������Ă��邩
	void touchReturn( ); // �߂�{�^�����^�b�`������
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
	bool _separate_flag;		// ��x�w��b�������ǂ����̃t���O
	bool _close_flag;			// ���邱�Ƃ��ł��邩�ǂ����̃t���O
	Touch::TOUCH_STATE _old_state;	// �O��̃^�b�`��Ԃ�ۑ����Ă����ϐ�
	int _return;	// �߂�{�^��
	Vector2 _return_pos;
	int _direction;		// �����{�^��
	Vector2 _direction_pos;
	bool _button_touch;
};

