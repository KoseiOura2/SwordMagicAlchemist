#pragma once
#include "Character.h"
#include "Floor.h"
#include "EnemyData.h"
#include <String>

PTR ( Enemy );
PTR ( Floor );
PTR ( MessageLog );
PTR ( Effect );
PTR ( NetworkApp );

const int AISLE_DIS      = 3; // �L���ɂ���Ƃ��̒T���͈�
const int FIND_AISLE_DIS = 5; // �L���ɂ���Ƃ��@AND�@���������̒T���͈�

class Enemy : public Character {
public:
	// �s���p�^�[��
	enum ACTION {
		MOVE_CHASE,
		MOVE_LOITERING,
		ATTACK,
	};
	// �L�����̌���	
	enum ENEMY_AISLE_DIR {
		DIR_NONE,
		DIR_RIGHT,
		DIR_LEFT,
		DIR_UPPER,
		DIR_LOWER,
		MAX_AISLE_DIR,
	};
public:
	Enemy( FloorPtr floor, NetworkAppPtr network, MessageLogPtr message, EffectPtr effect, ENEMY_TYPE enemytype, ANIM_HUNDLE anim_handle,
		   float scale, ENEMY_DATA data );
	~Enemy( );
public:												  
	void init( float scale, ENEMY_DATA data );
	void init( int my_number, Floor::TILE my_tile );
	void update( );
	void moveAnim( Vector2 pos );			
	void attackAnim( );							
	void deadAnim( );							  
	void dead( );								
	void damage( int player_power, bool use_waza, bool equip_item, bool zangeki );		// �v���C���[����̃_���[�W�v�Z
	void itemDamage( int item_damage );					// �A�C�e���̃_���[�W�v�Z											
	void deleatModel( );
public:
	void setAction( ACTION action );                  // �s���p�^�[����ݒ�
	void setAisleDir( ENEMY_AISLE_DIR aisle_dir );	  // �L�����̌�����ݒ�
	void setTargetPos( int x, int y );				  // �^�[�Q�b�g�n�_�̃^�C�����W��ݒ�
	void setFindPlayer( bool find );				  // �v���C���[�����������ǂ�����ݒ�
	void setRoomNum( int room_num );
	ENEMY_TYPE getType( );
	ACTION getAction( );			   // �s���p�^�[�����擾
	ENEMY_AISLE_DIR getAisleDir( );	   // �L�����̌������擾
	Vector2 getTargetPos( );		   // �^�[�Q�b�g�n�_�̃^�C�����W�̎擾	  
	unsigned int getNumber( );
	int getRoomNum( );											
	int getDamage( );																						  
	int getExp( );				
	int getAlchemyPoint( );					
	bool isEndMoveAnim( );											
	bool isEndAttackAnim( );										
	bool isEndDeadAnim( );			
	bool isFindPlayer( );
	bool isDead( );													  // ���S�������ǂ���							  
private:															   
	NetworkAppPtr _network;
	ACTION _action;													  
	Vector2 _target;												  // ���Ɉړ�����^�[�Q�b�g�n�_
	ENEMY_TYPE _enemy_type;											  
	ENEMY_AISLE_DIR _aisle_dir;			
	unsigned int _my_number;
	int _damage;													  
	int _exp;			
	int _alchemy_point;
	int _room_num;
	bool _find_player;											  
	bool _dead;														  
};																	  