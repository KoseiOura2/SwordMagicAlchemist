#include "Camera.h"
#include "DxLib.h"
#include "Player.h"

const int CAMERA_DEPTH = 40;            // �J�����̏œ_����
const int ADJUST_CAMERA_ROTATE = 30;    // �J����Z�������̏C���p�x

Camera::Camera( const PlayerPtr player ) {
	// ������
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
	//�@Player�̒��S�𒍎��_�ɂƂ�
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
	// �J�����̃|�W�V�������Z�b�g
	SetCameraPositionAndTarget_UpVecY(
		VGet( ( float )_pos.x, ( float )_pos.y, ( float )_pos.z ), 
		VGet( ( float )_target.x, ( float )_target.y, ( float )_target.z ) );
}