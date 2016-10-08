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
	Vector _pos;							// 3DÀ•W
	Vector _target;							// ’‹“_‚ÌÀ•W
	PlayerPtr _player;					
};

