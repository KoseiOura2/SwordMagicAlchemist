#pragma once
#include "smart_ptr.h"
#include "mathematics.h"
#include "mathematics.h"
#include <vector>
#include <string>
#include "ItemName.h"
#include "NetworkApp.h"
#include "Player.h"

PTR ( Item );
PTR ( Floor );
PTR ( NetworkApp );
PTR ( MessageLog );
PTR ( Effect );

const int LIMIT_THROW_DISTANCE = 10;  // �A�C�e���𓊂�����E����
const int FLAME_STONE_DISTANCE = 2;   // �Ă��΂𓊂�����E����

class Item {
public:
	struct ITEM_DATA {
		Vector draw_pos;
		Vector2 pos;
		Vector pre_pos;
		ITEM_TYPE type;
		int model_hundle;
		Vector scale;
		Vector rotate;
		ITEM_DATA ( ) {
			this->type = ITEM_TYPE( );
		}
		ITEM_DATA ( const ITEM_ID id, int model_hundle,
					const Vector scale, const Vector rotate ) {
			this->type         = ITEM_TYPE( id );
			this->model_hundle = model_hundle;
			this->scale        = scale;
			this->rotate       = rotate;
		}
	};
public:
	Item( FloorPtr floor, NetworkAppPtr network, MessageLogPtr messageLog, EffectPtr effect );
	~Item( );
public:
	void update( );
	void draw( );
	void init( );
	void createFloor1( );
	void createFloor2( );
	void createFloor3( );
	void createFloor4( );
	void abovePlayer( int x, int y );                                      // �A�C�e���̏�ɃG�l�~�[�����鏈��
	void itemAction( MOVE_DIR move_dir );						           // �A�C�e���ɑ΂���s��
	void throwItem( MOVE_DIR move_dir );						           // �A�C�e���𓊂���
	void setFloorLevel( int floor_level );							       // ���݂̊K�w��ݒ�                     
	void deleteAllItem( );												   // �A�C�e���S���� 
public:
	void setInitHitEnemyPos( );
	Vector2 getHitEnemyPos( );											   // �A�C�e�������������G�l�~�[���擾
	ITEM_ID getHitEnemyType( );										       // �G�l�~�[�ɂ��������A�C�e���^�C�v���擾
	bool isEndThrow( );
	int getItemDamage( );												   // �A�C�e���_���[�W���擾
	bool isHitEnemy( );													   // �G�l�~�[�ɓ����������ǂ���
	void setHitEnemy( bool hit_enemy );									   
	bool isUseFlameRod( );											       // ���[�v�̏���g�������ǂ���
	void setUseWarpRod( bool use_rod );							   
	bool isUseWarpRod( );											       // ���̏���g�������ǂ���
	void setUseFlameRod( bool use_rod );							   
	bool isUseSuperFlameRod( );											   // �����̏���g�������ǂ���
	void setUseSuperFlameRod( bool use_rod );							   
	bool isTurnEnd( );													   
	void setTurnEnd( bool turn_end );	
private:
	void loadModel( );
private:																   
	Vector getInitPos( );												   // �����z�u������W���擾
	Vector2 displaceItemPos( int x, int y );							   // �A�C�e����������炸�炷
	Vector throwMove( Vector draw_pos, Vector2 pos, Vector pre_pos );	   // �`����W���ړ�
	ITEM_DATA getItemDataForID( ITEM_ID id );							   // ID�ɂ���ăA�C�e���̃f�[�^���擾
	void pickUPItem( );													   // �A�C�e�����E��						    
	void itemHitEnemy( );		
private:
	// �v���C���[�̂ނ��ɂ���ē����������ς���
	void throwNone( ITEM_DATA *item );									   
	void throwLowerLeft( ITEM_DATA *item );								    
	void throwLower( ITEM_DATA *item );									    
	void throwLowerRight( ITEM_DATA *item );							    
	void throwLeft( ITEM_DATA *item );									    
	void throwWait( ITEM_DATA *item );									    
	void throwRight( ITEM_DATA *item );									    
	void throwUpperLeft( ITEM_DATA *item );								    
	void throwUpper( ITEM_DATA *item );									    
	void throwUpperRight( ITEM_DATA *item );	
private:
	// �v���C���[�̂ނ��ɂ���ď���t��������ς���
	void swingNone( );									   
	void swingLowerLeft( );								    
	void swingLower( );									    
	void swingLowerRight( );							    
	void swingLeft( );									    
	void swingWait( );									    
	void swingRight( );									    
	void swingUpperLeft( );								    
	void swingUpper( );									    
	void swingUpperRight( );	
private:																   
	FloorPtr _floor;													   
	NetworkAppPtr _network;												   
	MessageLogPtr _messageLog;	
	EffectPtr _effect;
	ITEM_DATA _item_table[ MAX_ITEM_TYPE ];								 
	std::vector< ITEM_DATA > _items;									 
	Vector2 _hit_enemy_pos;		
	ITEM_ID _hit_enemy_item;
	int _item_damage;	
	int _floor_level;											 
	int _start_item_num;		
	int _throw_num;
	bool _foot;
	bool _throw_item_toward_enemy;										 
	bool _hit_enemy;	
	bool _throw;
	bool _end_throw;
	bool _use_flame_rod;	
	bool _use_super_flame_rod;	
	bool _use_warp_rod;
	bool _turn_end;	
private:
	// �ȉ����f���n���h��	
	int _herb_model_1;
	int _herb_model_2;
	int _herb_model_3;
	int _herb_model_4;
	int _herb_model_5;
	int _herb_model_6;
	int _herb_model_7;
	int _herb_model_8;
	int _herb_model_9;
	int _meat_model_1;	
	int _meat_model_2;	
	int _meat_model_3;	
	int _meat_model_4;													   
	int _ring_model_1;													   
	int _ring_model_2;													   
	int _ring_model_3;													   
	int _ring_model_4;														   
	int _ring_model_5;													   
	int _ring_model_6;												   
	int _rod_model_1;													   
	int _rod_model_2;													   
	int _rod_model_3;													   
	int _rod_model_4;												   
	int _sword_model_1;													   
	int _sword_model_2;													   
	int _sword_model_3;													   
	int _sword_model_4;													   
	int _stone_model_1;													   
	int _stone_model_2;													   
	int _stone_model_3;													   
	int _stone_model_4;													   
	int _stone_model_5;													   
	int _stone_model_6;													   
	int _garbage_model_1;												   
	int _garbage_model_2;	
	int _shadow_image;
};																		 

