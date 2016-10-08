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

const int AISLE_DIS      = 3; // 廊下にいるときの探索範囲
const int FIND_AISLE_DIS = 5; // 廊下にいるとき　AND　見つけた時の探索範囲

class Enemy : public Character {
public:
	// 行動パターン
	enum ACTION {
		MOVE_CHASE,
		MOVE_LOITERING,
		ATTACK,
	};
	// 廊下時の向き	
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
	void damage( int player_power, bool use_waza, bool equip_item, bool zangeki );		// プレイヤーからのダメージ計算
	void itemDamage( int item_damage );					// アイテムのダメージ計算											
	void deleatModel( );
public:
	void setAction( ACTION action );                  // 行動パターンを設定
	void setAisleDir( ENEMY_AISLE_DIR aisle_dir );	  // 廊下時の向きを設定
	void setTargetPos( int x, int y );				  // ターゲット地点のタイル座標を設定
	void setFindPlayer( bool find );				  // プレイヤーを見つけたかどうかを設定
	void setRoomNum( int room_num );
	ENEMY_TYPE getType( );
	ACTION getAction( );			   // 行動パターンを取得
	ENEMY_AISLE_DIR getAisleDir( );	   // 廊下時の向きを取得
	Vector2 getTargetPos( );		   // ターゲット地点のタイル座標の取得	  
	unsigned int getNumber( );
	int getRoomNum( );											
	int getDamage( );																						  
	int getExp( );				
	int getAlchemyPoint( );					
	bool isEndMoveAnim( );											
	bool isEndAttackAnim( );										
	bool isEndDeadAnim( );			
	bool isFindPlayer( );
	bool isDead( );													  // 死亡したかどうか							  
private:															   
	NetworkAppPtr _network;
	ACTION _action;													  
	Vector2 _target;												  // 次に移動するターゲット地点
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