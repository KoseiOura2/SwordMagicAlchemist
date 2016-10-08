#include "Camera.h"
#include "DxLib.h"
#include "Player.h"

const int CAMERA_DEPTH = 40;            // カメラの焦点距離
const int ADJUST_CAMERA_ROTATE = 30;    // カメラZ軸方向の修正角度

Camera::Camera( const PlayerPtr player ) {
	// 初期化
	_pos    = Vector( 30, CAMERA_DEPTH, -30 );
	_target = Vector( 0, 0, 0 );
	_player = player;
	SetCameraPositionAndTarget_UpVecY(
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
	//　Playerの中心を注視点にとる
	if ( _player->isWarp( ) == false ) {
		_target = _player->getDrawPos( ) + Vector( 5, 0, 5 );
		_pos.x  = _target.x;
		_pos.z  = _target.z + ADJUST_CAMERA_ROTATE;
	} else if ( _player->isWarpMove( ) == true ) {
		_player->turnEnd( );
		_target = _player->getDrawPos( ) + Vector( 5, 0, 5 );
		_target.y = 0;
		_pos.x  = _target.x;
		_pos.z  = _target.z + ADJUST_CAMERA_ROTATE;
	}
	// カメラのポジションをセット
	SetCameraPositionAndTarget_UpVecY(
		VGet( ( float )_pos.x, ( float )_pos.y, ( float )_pos.z ), 
		VGet( ( float )_target.x, ( float )_target.y, ( float )_target.z ) );
}