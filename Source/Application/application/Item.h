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

const int LIMIT_THROW_DISTANCE = 10;  // アイテムを投げる限界距離
const int FLAME_STONE_DISTANCE = 2;   // 焼け石を投げる限界距離

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
	void abovePlayer( int x, int y );                                      // アイテムの上にエネミーがいる処理
	void itemAction( MOVE_DIR move_dir );						           // アイテムに対する行動
	void throwItem( MOVE_DIR move_dir );						           // アイテムを投げる
	void setFloorLevel( int floor_level );							       // 現在の階層を設定                     
	void deleteAllItem( );												   // アイテム全消去 
public:
	void setInitHitEnemyPos( );
	Vector2 getHitEnemyPos( );											   // アイテムが当たったエネミーを取得
	ITEM_ID getHitEnemyType( );										       // エネミーにあたったアイテムタイプを取得
	bool isEndThrow( );
	int getItemDamage( );												   // アイテムダメージを取得
	bool isHitEnemy( );													   // エネミーに当たったかどうか
	void setHitEnemy( bool hit_enemy );									   
	bool isUseFlameRod( );											       // ワープの杖を使ったかどうか
	void setUseWarpRod( bool use_rod );							   
	bool isUseWarpRod( );											       // 炎の杖を使ったかどうか
	void setUseFlameRod( bool use_rod );							   
	bool isUseSuperFlameRod( );											   // 豪炎の杖を使ったかどうか
	void setUseSuperFlameRod( bool use_rod );							   
	bool isTurnEnd( );													   
	void setTurnEnd( bool turn_end );	
private:
	void loadModel( );
private:																   
	Vector getInitPos( );												   // 初期配置する座標を取得
	Vector2 displaceItemPos( int x, int y );							   // アイテムが被ったらずらす
	Vector throwMove( Vector draw_pos, Vector2 pos, Vector pre_pos );	   // 描画座標を移動
	ITEM_DATA getItemDataForID( ITEM_ID id );							   // IDによってアイテムのデータを取得
	void pickUPItem( );													   // アイテムを拾う						    
	void itemHitEnemy( );		
private:
	// プレイヤーのむきによって投げる方向を変える
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
	// プレイヤーのむきによって杖をフル方向を変える
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
	// 以下モデルハンドル	
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

