#pragma once

#include "framework.h"
#include "smart_ptr.h"
#include "mathematics.h"
#include "CharacterStatus.h"
#include < vector >
PTR ( UI );
PTR ( NetworkController );

const int DEFAULT_FONT = 50;	// �f�t�H���g�̕����̑傫��
//---------------------------------- �g�o�o�[ -------------------------------------------------//
const int HP_WIDTH = 450;
const int HP_HEIGHT = 90;
const int HP_POS_X = SCREEN_WIDTH / 2 - HP_WIDTH / 2;
const int HP_POS_Y = HP_HEIGHT / 2;
const int HP_FONT_POS_X = HP_POS_X + HP_WIDTH / 4;
const int HP_FONT_POS_Y = HP_POS_Y + HP_HEIGHT / 4;
const int HP_FONT_SIZE = 30;
//---------------------------------- �X�^�~�i�o�[ -------------------------------------------------//
const int STAMINA_WIDTH = 200;
const int STAMINA_HEIGHT = 200;
const int STAMINA_POS_X = SCREEN_WIDTH - STAMINA_WIDTH - 50;
const int STAMINA_POS_Y = ( HP_POS_Y + HP_HEIGHT / 2 ) - ( STAMINA_HEIGHT / 2 ) + 50;	// �g�o�o�[�ƒ��S�����킹��
const int STAMINA_FONT_POS_X = STAMINA_POS_X - 200;
const int STAMINA_FONT_POS_Y = STAMINA_POS_Y + 50;
const int MAX_STAMINA = 100;
const int STAMINA_FONT_SIZE = 58;
//---------------------------------- ��Ԉُ� -------------------------------------------------//
const int STATE_WIDTH = 200;
const int STATE_HEIGHT = 200;
const int STATE_POS_X = HP_POS_X - STATE_WIDTH - 50;
const int STATE_POS_Y = ( HP_POS_Y + HP_HEIGHT / 2 ) - ( STATE_HEIGHT / 2 ) + 50;
const int STATE_CHANGE_TIME = 20;
const int STATE_ALL_NORMAL = -1;	// �ǂ̏�Ԉُ�ɂ��������Ă��Ȃ�
//---------------------------------- ���x�� -------------------------------------------------//
const int LEVEL_POS_X = 50;
const int LEVEL_POS_Y = HP_POS_Y;
//---------------------------------- �K�w -------------------------------------------------//
const int FLOOR_POS_X = 50;
const int FLOOR_POS_Y = HP_POS_Y + 100;

const int STATE_TYPE_NUM = 3;	// �����ɂ������Ԉُ�ȏ�̍ő吔

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
	// ��Ԉُ�摜�擾
	int getStateImage( );
	int getSpeedImage( );
	int getBuffImage( );
	// ��Ԉُ�摜�ݒ�
	void setStateImage( );
private:
	int _count;			 // �_�ŗp�̃J�E���g
	NetworkControllerPtr _network;
	int _hp_bar;		 // HP�̊O�g
	STATUS_DATA _status; // �X�e�[�^�X
	STATUS_DATA _old_status;
	int _stamina;		 // �X�^�~�i�̌��ݒl
	int _hp_gauge;		 // HP�̒��g
	int _hp_font;		 // HP�̕���
	int _stamina_bar;	 // �X�^�~�i�̊O�g
	int _stamina_gauge;  // �X�^�~�i�̒��g
	int _stamina_font;	 // �X�^�~�i�̕���
	int _level;			 // ���̃��x��
	int _floor_level;	 // ���̊K�w
	int _default_font;	 // ���Ɏw�肪�Ȃ��ꍇ�̕���
	bool _state_set;
	// ��Ԉُ�摜
	int _poison;         // ��
	int _paralysis;		 // ���
	int _skill_seal;	 // �X�L������
	int _bind_tile;		 // �ړ�����
	int _confuse;		 // ����
	// �X�s�[�h�摜
	int _slow;			 // �ݑ�
	int _fast;			 // ����
	// buff�摜
	int _buff;			 // �o�t(�U��UP)
	int _debuff;		 // �f�o�t�i�U��DOWN�j
	
	std::vector< int > _image_vector;	// �\������C���[�W
	int _num_image;		 // �\������C���[�W�ԍ�
	bool _image_set;	// �C���[�W���Z�b�g���Ȃ������ǂ���
};

