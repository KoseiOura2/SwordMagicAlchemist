#pragma once

#include "smart_ptr.h"
#include "mathematics.h"

PTR( Camera );

const int ALCHEMY_ANGLE = 90;
const Vector INIT_POS = Vector ( 0, 30, 1 );
const Vector ALCHEMY_POS = Vector( 0, -INIT_POS.z, INIT_POS.y );
const int CAMERA_SPEED = 3;
class Camera {
public:
	enum MODE {
		NORMAL,
		ALCHEMY,
		RETURN
	};
public:
	Camera( );
	~Camera( );
	virtual void initialize( );
	virtual void finalize( );
	void update( );
	void setCameraMode( MODE mode );
	bool getFinishAlchemy( );
	void setFinishAlchemy( bool flag );
	void cameraReset( );
private:
	void alchemyMode( );
	void returnMode( );
private:									
	Vector _pos;							// 3D座標
	Vector _target;							// 注視点の座標			
	Vector _objective_pos;					// 移動する際の目標地点
	MODE _camera_mode;
	double _angle;
	bool _finish_alchemy;
};