
#pragma once

#include "Task.h"
#include <string>

PTR( SoundManager );	

class SoundManager : public Task {
public:
	SoundManager( );
	virtual ~SoundManager( );
	virtual void initialize( );
	virtual void finalize( );
	void update( );
public:
	int loadSound( const char *file_path );
	void deleteSound( const int handle ) const;
	void playSound( const int handle, bool loop );
	void backGroundPlaySound( const int handle );
	void stopSound( const int handle );
	void volumeChange( const int handle, int volume );
};
