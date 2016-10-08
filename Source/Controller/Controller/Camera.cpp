#include "Camera.h"
#include "DxLib.h"

Camera::Camera( ) {
	// 初期化
	_pos    = ALCHEMY_POS;
	_target = Vector( 0, 0, 0 );
	_objective_pos = _pos;
	_angle = 90;
	_camera_mode = NORMAL;
	_finish_alchemy = false;

	SetCameraPositionAndTarget_UpVecY (
		VGet( ( float )_pos.x, ( float )_pos.y, ( float )_pos.z ), 
		VGet( ( float )_target.x, ( float )_target.y, ( float )_target.z ) );
}


Camera::~Camera( ) {
}

void Camera::initialize( ) {
}

void Camera::finalize( ) {

}

void Camera::update( ) {
	// カメラのスムーズ移動処理
	/*if ( _pos != _objective_pos ) {
		_pos += ( _objective_pos - _pos );
	}*/
	
	switch( _camera_mode ) {
	case ALCHEMY:
		alchemyMode( );
		break;
	case RETURN:
		returnMode( );
		break;
	}

	// カメラの更新
	SetCameraPositionAndTarget_UpVecY(
		VGet( ( float )_pos.x, ( float )_pos.y, ( float )_pos.z ), 
		VGet( ( float )_target.x, ( float )_target.y, ( float )_target.z ) );
}

void Camera::setCameraMode( MODE mode ) {
	_camera_mode = mode;
}

bool Camera::getFinishAlchemy(  ) {
	return _finish_alchemy;
}

void Camera::setFinishAlchemy( bool flag ) {
	_finish_alchemy = flag;
}

// 錬金のカメラワーク
void Camera::alchemyMode( ) {
	if ( _angle < ALCHEMY_ANGLE ) {
		_angle += CAMERA_SPEED;
		Matrix mat = Matrix::makeTransformRotation( Vector( -1, 0, 0 ), _angle );
		_pos = mat.multiply( INIT_POS );
	} else if ( _angle >= ALCHEMY_ANGLE ) {
		// ある程度まで来たらALCHEMY_POS
		_finish_alchemy = true;
		_pos = ALCHEMY_POS;
		_camera_mode = NORMAL;
	}

}

// 錬金終了後のカメラワーク
void Camera::returnMode( ) {
	if ( _angle > 0 ) {
		_angle -= CAMERA_SPEED;
		Matrix mat = Matrix::makeTransformRotation( Vector( -1, 0, 0 ), _angle );
		_pos = mat.multiply( INIT_POS );
	} else if ( _angle >= 0 ) {
		_finish_alchemy = true;
		_pos = INIT_POS;
		_camera_mode = NORMAL;
	}
}

void Camera::cameraReset( ) {
		// 初期化
	_pos    = ALCHEMY_POS;
	_target = Vector( 0, 0, 0 );
	_objective_pos = _pos;
	_angle = 90;
	_camera_mode = NORMAL;
	_finish_alchemy = false;

	SetCameraPositionAndTarget_UpVecY (
		VGet( ( float )_pos.x, ( float )_pos.y, ( float )_pos.z ), 
		VGet( ( float )_target.x, ( float )_target.y, ( float )_target.z ) );
}