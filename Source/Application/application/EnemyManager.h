#pragma once
#include "smart_ptr.h"
#include "Floor.h"
#include <vector>
#include "Character.h"
#include "Enemy.h"

PTR ( EnemyManager );
PTR ( Enemy );
PTR ( Floor );
PTR ( Turn );
PTR ( MessageLog );
PTR ( Item );
PTR ( NetworkApp );
PTR ( Effect );

const int ENEMY_TYPE_NUM      = 5;
const int AISLE_FLAME_LOD_DIS = 3;

class EnemyManager {
public:
	EnemyManager( FloorPtr floor, TurnPtr turn, PlayerPtr player, MessageLogPtr message, ItemPtr item, NetworkAppPtr network, EffectPtr effect );
	~EnemyManager( );
public:
	void loadModel( );
	void init( );
	void bossInit( );
	void update( );
	void bossUpdate( );
	void deleteAllEnemy( );    // �G�l�~�[�̑S����
	bool isTurnEnd( );		   // �^�[���̏I���錾
	void setFloorLevel( int floor_level );		
	bool isKnockDownBoss( );
private:								
	void createEnemy( );		 // �G�l�~�[�̍Đ���
	Floor::TILE createPos( );	 // �G�l�~�[�𐶐�����^�C�����W
	void createEnemyFloor1( bool is_recreate );
	void createEnemyFloor2( bool is_recreate );
	void createEnemyFloor3( bool is_recreate );
	void createEnemyFloor4( bool is_recreate );
	void createEnemyBossFloor( );
private:														
	void myTurnAction( );									
	void myTurnActionBossScene( );
	void confuseMove( EnemyPtr enemy );
	void confuseMoveBoss( );
	void dicisionPos( EnemyPtr enemy, Vector2 pre_pos, Vector2 pos, MOVE_DIR dir );
	void dicisionPos( EnemyPtr enemy, Vector2 pre_pos, Vector2 pos, MOVE_DIR dir,  bool* flag );
	void dicisionPosBoss( Vector2 pre_pos, Vector2 pos, MOVE_DIR dir );
	void dicisionPosBoss( Vector2 pre_pos, Vector2 pos, MOVE_DIR dir,  bool* flag );
	void dicisionMovePos( EnemyPtr enemy, int x, int y );			// �ړ�������߂�
	void dicisionMovePosBoss( int x, int y );
	Floor::TILE setRoomTarget( EnemyPtr enemy, int num );		    // �����ɂ��鎞�̃^�[�Q�b�g�n�_�̐ݒ�
	Floor::TILE surroundLookAisle( int x, int y );				    // �L���ɂ��鎞�ɂ܂��̃^�C�����m�F����
	Floor::TILE setAisleTarget( EnemyPtr enemy );				    // �L���ɂ��鎞�̃^�[�Q�b�g�n�_�̐ݒ�
	Floor::TILE checkStraight( EnemyPtr enemy, int x, int y, Enemy::ENEMY_AISLE_DIR dir );
	bool isBranchAisle( Enemy::ENEMY_AISLE_DIR dir, int x, int y );
	void arriveTarget( EnemyPtr enemy, int num );				    // �^�[�Q�b�g�n�_�ɂ����Ƃ��^�[�Q�b�g�n�_���Đݒ�
	void otherEnemy( EnemyPtr enemy, Vector2 *target_pos );	        // �G�l�~�[�ɂԂ������Ƃ��̏���
	bool serchPlayer( EnemyPtr enemy );							    // �v���C���[�̒T��
	bool isRoomSerchRange( EnemyPtr enemy );					    // �����ɂ���Ƃ��̒T���͈�
	bool nearRoomSerch( Floor::TILE tile, int serch_range, int count );
	bool isAisleSerchRange( EnemyPtr enemy );					    // �L���ɂ���Ƃ��̒T���͈�
	ENEMY_DATA getEnemyDataForName( std::string name );
	void setBondBossTile( bool none );
private:						
	void confuseAttack( EnemyPtr enemy );
	void attack( EnemyPtr enemy  );			
	void confuseAttackBoss( );
	void attackBoss( );									  
	void enemyDead( );												   
	void selectDamagedEnemy(  );	
	void damagedBoss( );
	void itemDamage( );												   
	void rodDamage( );			
	void itemDamageBoss( );												   
	void rodDamageBoss( );					
	void triSwordAbnormal( EnemyPtr enemy );
	bool isHitPlayerAttack( int x, int y );		
	bool isHitPlayerAttackBoss( int x, int y );							  
	bool isNextToPlayer( int x, int y );							  
	bool isNextToPlayerBoss( int x, int y );								   
private:															  
	FloorPtr _floor;												
	TurnPtr _turn;													
	PlayerPtr _player;												
	MessageLogPtr _message;											
	ItemPtr _item;				
	NetworkAppPtr _network;
	EffectPtr _effect;
	Character::ANIM_HUNDLE _anim_handle[ ENEMY_TYPE::MAX_ENEMY_NUM ];
	int _tex_handle[ ENEMY_TYPE::MAX_ENEMY_NUM ];
	ENEMY_DATA _enemy_data[ ENEMY_TYPE::MAX_ENEMY_NUM ];
	std::vector< EnemyPtr > _enemy;									
	bool _enemy_dead;												  
	bool _create;													  
	bool _turn_end;		
	bool _knock_down_boss;
	unsigned int _enemy_num;
	unsigned int _enemy_count;	
	int _super_flame_rod_kill_count;
	int _super_flame_rod_killed_count;
	bool _use_flame_rod;
	int _floor_level;
	unsigned int _start_enemy_num;
	unsigned int _max_enemy_num;
	int _shadow_handle;
};

