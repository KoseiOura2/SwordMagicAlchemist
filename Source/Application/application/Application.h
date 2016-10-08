#pragma once
#include "Task.h"
#include "smart_ptr.h"

PTR ( Application );
PTR ( Title );
PTR ( NextFloor );
PTR ( Player );
PTR ( Floor );
PTR ( Camera );
PTR ( NetworkApp );
PTR ( EnemyManager );
PTR ( Item );
PTR ( Turn );
PTR ( MessageLog );
PTR ( UIApp );
PTR ( Effect );

class Application : public Task {
private:								 
	enum SCENE{							  
		SCENE_CONNECT,
		SCENE_TITLE,				  
		SCENE_GAME,						  
		SCENE_NEXT_FLOOR,
		SCENE_BOSS,
		SCENE_GAME_CLEAR,
		SCENE_GAME_OVER
	};		
public:
	Application( );                      
	~Application( );					 
public:									 
	void initialize( );					 
	void finalize( );					 
	void update( );						 
private:								 
	void updateConnect( );				 // Controller側との接続シーンの更新処理
	void updateTitle( );			     // タイトルシーンの更新処理
	void updateGame( );					 // MainGameシーンの更新処理
	void updateNextFloor( );			 // 階層移動シーンの更新処理	
	void updatePreFloor( );			 // 階層移動シーンの更新処理	
	void updateBoss( );		        	 // ボスシーンの更新処理		
	void updateGameClear( );		     // クリアシーンの更新処理		
	void updateGameOver( );		         // ゲームオーバーシーンの更新処理							  
private:								  
	SCENE _scene;						  
	FloorPtr _floor;
	TitlePtr _title;
	TurnPtr _turn;						  
	PlayerPtr _player;					 
	CameraPtr _camera;					 
	EnemyManagerPtr _enemyManager;		 
	ItemPtr _item;						 
	NetworkAppPtr _network;				 
	MessageLogPtr _messageLog;			 
	NextFloorPtr _next_floor;			 
	UIAppPtr _ui_app;			
	EffectPtr _effect;
	bool _next_floor_scene_init;		 // 初期化フラグ
	int _tile_x_count;					 // コントローラーに送るマップチップのカウント数
	bool _send_tile_finish;				 // コントローラーにマップチップを送り終わったかどうか
	int _fade_out_pal;					 // フェードアウトのカウント数
};

