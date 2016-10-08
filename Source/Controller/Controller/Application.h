#pragma once
#include "Framework.h"
#include "Task.h"
#include "IconManeger.h"
 
PTR( Application )
PTR( NetworkController );
PTR( IconManeger );
PTR( NextFloor );
PTR( Map );
PTR( Title );
PTR( Button );
PTR( Camera );
PTR( UI );

class Application : public Task {
public:
	enum SCENE {
		SCENE_CONNECT,
		SCENE_INIT,
		SCENE_TITLE,
		SCENE_NEXT_FLOOR,
		SCENE_CONTROLLER,
		SCENE_FINISH,
		MAX_SCENE,
	};
public:
	Application( );
	~Application( );
	void update( );
	void setStairsFlag( bool flag );
	virtual void initialize( );
	virtual void finalize( );
private:
	void updateConnect( );
	void updateTitle( );
	void init( );
	void updateNextFloor( );
	void updateController( );
	void updateFinish( );
private:
	SCENE _scene;
	NetworkControllerPtr _network;
	ButtonPtr _button;
	IconManegerPtr _icon_maneger;
	NextFloorPtr _next_floor;
	MapPtr _map;
	TitlePtr _title;
	CameraPtr _camera;
	UIPtr _ui;
	int _back_ctrl;	// îwåi
	bool _stairs_flag;
	bool _separate_flag;
	bool _next_floor_in_out_scene;
	bool _next_floor_tile_finish;
};

