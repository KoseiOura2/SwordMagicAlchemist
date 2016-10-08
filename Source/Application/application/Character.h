#pragma once
#include "smart_ptr.h"
#include "mathematics.h"
#include "CharacterStatus.h"
#include <String>

PTR ( Character );
PTR ( Floor );
PTR ( Turn );
PTR ( NetworkApp );
PTR ( MessageLog );
PTR ( Effect );

const int WALK_ANIM_TIME = 15;  // 移動アニメーションを再生する時間
const double WARP_LIMIT_Y = 50;
																	
class Character {													
public:
	enum MY_TYPE {
		MY_TYPE_PLAYER,
		MY_TYPE_ENEMY,
	};
	// アニメーションの種類
	enum ANIM_STATE {												
		STAY_ANIM,													
		WALK_ANIM,													
		ATTACK_ANIM,												
		DEAD_ANIM,													
		DAMAGE_ANIM,
		REVIVE_ANIM,
	};
	// アニメーションをアタッチする箱
	struct ANIM_INDEX {												
		int stay;													
		int walk;													
		int attack;													
		int damage;													
		int dead;													
	};
	// アニメーションデータのハンドル
	struct ANIM_HUNDLE {											
		int model;													
		int stay;													
		int walk;													
		int attack;													
		int damage;													
		int dead;													
	};																
public:																
	Character( FloorPtr floor, NetworkAppPtr network, MessageLogPtr message, EffectPtr effect );													
	~Character( );		
public:
	virtual void update( ) = 0;
	void loadShadow( int shadow_image );
	void refreshState( );	
	void refreshStateNextFloor( );
	void becomeAbnormalState( STATE state, int effect_num );
	void elapsedAbnormalTurn( );
	void refreshSpeed( );
	void changeSpeedState( SPEED speed, int effect_num );
	void elapsedSpeedTurn( );
	void refreshBuff( );
	void changeBuffState( BUFF_STATE buff, int effect_num );
	void elapsedBuffTurn( );
	void statusForBuff( );
	void warpPos( );
	void warpStairPos( );
	bool warpProduction( bool up );
	bool pitProduction( );
	void warpStart( int num );
	void warpStairStart( int num );
	bool isWarp( );
	bool isWarpMove( );
public:
	void setDir( MOVE_DIR dir );
	Vector getDrawPos( );
	Vector getPreDrawPos( );
	Vector2 getPos( );
	STATUS_DATA getStatus( );	
	std::string getName( );		
	float getAngle( );
	ANIM_HUNDLE getAnimHundle( );
	ANIM_INDEX getAnimIndex( );
	int getMainAnim( );
	ANIM_STATE getAnimState( );
	int getAnimCount( );
	float getAnimTime( );
	float getTotalAnimTime( );
	float getAttackAnimTime( );
	float getDamageAnimTime( );
	float getDeadAnimTime( );
	bool isWalking( );
	bool isSpeedAbnormal( );
	bool isNotCornerWall( Vector2 pos );         // 角抜けを防ぐ処理
protected:			
	void angleChange( );
	void rotateByWarp( );
	void draw( );					
	void move( );
	void playbackAnim( float stay_anim_time, float walk_anim_time,		  // アニメーションの再生
		            float attack_anim_time, float dead_anim_time,	  
					float damage_time, float revive_time );
	void decreaseHPForPoison( );
protected:																  
	FloorPtr _floor;
	NetworkAppPtr _network;
	MessageLogPtr _message;
	EffectPtr _effect;
	Vector _draw_pos;													  // 描画座標
	Vector2 _pos; 														  // タイル座標
	Vector _pre_pos;													  // 座標移動の際の元の描画座標
	MY_TYPE _my_type;
	STATUS_DATA _status;		                                          // ステータス
	int _pre_attack;
	std::string _name;					                                  // 名前	  
	float _angle;														  // モデルの向き
	float _warp_angle;													  // モデルの向き
	ANIM_HUNDLE _anim_hundle;											  
	ANIM_INDEX _anim_index;												  
	int _main_anim;													      // アタッチするアニメーションの箱
	ANIM_STATE _anim_state;				
	int _anim_count;													  // 移動アニメーションの際の経過時間
	float _anim_play_time;												  // アニメーション再生時間
	float _total_time;													  // アニメーションが一周する時間
	float _attack_time;													  // 攻撃アニメーションにかかる時間
	float _damage_time;													  // ダメージアニメーションにかかる時間
	float _dead_time;													  // 死亡アニメーションにかかる時間
	bool _walking;														  // 移動アニメーション中かどうか
	int _state_change_turn;                                               // 状態異常を治すのに必要なターン
	int _elapsed_time;                                                    // 状態異常にかかってからの経過時間
	int _speed_change_turn;
	int _speed_elapsed_time;
	int _buff_change_turn;
	int _buff_elapsed_time;
	bool _speed_abnormal;
	bool _buff;
	bool _buff_end;
	bool _warp;
	bool _warp_stair;
	bool _warp_start;
	bool _warp_move;
	bool _ride_return_trap;
	bool _return_start;
	int _shadow_image;
};

