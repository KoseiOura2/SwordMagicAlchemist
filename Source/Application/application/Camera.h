#pragma once

#include "smart_ptr.h"
#include "mathematics.h"

PTR( Camera );
PTR( Player );

class Camera {
public:
	Camera( const PlayerPtr player );
	~Camera( );
	virtual void initialize( );
	virtual void finalize( );
	void update( ); 
private:									
	Vector _pos;							// 3D���W
	Vector _target;							// �����_�̍��W
	PlayerPtr _player;					
};

