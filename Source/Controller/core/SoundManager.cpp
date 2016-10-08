#include "SoundManager.h"
#include "DxLib.h"


SoundManager::SoundManager( ) {

}

SoundManager::~SoundManager( ) {

}

void SoundManager::initialize( ) {

}

void SoundManager::finalize( ) {

}

void SoundManager::update( ) {

}

int SoundManager::loadSound( const char* file_path ) {
	return LoadSoundMem( file_path );
}

void SoundManager::playSound( const int handle, bool loop ) {
	if ( loop == true ) {
		PlaySoundMem( handle, DX_PLAYTYPE_LOOP, FALSE );
	} else {
		PlaySoundMem( handle, DX_PLAYTYPE_NORMAL, FALSE );
	}
}

void SoundManager::backGroundPlaySound( const int handle ) {
	PlaySoundMem( handle, DX_PLAYTYPE_BACK, FALSE );
}

void SoundManager::stopSound( const int handle ) {
	StopSoundMem( handle );
}