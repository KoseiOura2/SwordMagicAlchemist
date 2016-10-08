#include "Sound.h"
#include "Framework.h"
#include "SoundManager.h"


Sound::Sound( ) {
	FrameworkPtr fw = Framework::getInstance( );
	SoundManagerPtr sound_manager = std::dynamic_pointer_cast< SoundManager >( fw->getTask( typeid( SoundManager ).name( ) ) );
	_decision = sound_manager->loadSound( "work/sound/SE/decision.mp3" );
	_return = sound_manager->loadSound( "work/sound/SE/cancel.mp3" );
	_pot_open = sound_manager->loadSound( "work/sound/SE/pot_open.mp3" );
	//_pot_open = sound_manager->loadSound( "work/sound/BGM/boss.mp3" );
	_pot_close = sound_manager->loadSound( "work/sound/SE/pot_close.mp3" );
	_alchemy_success = sound_manager->loadSound( "work/sound/SE/alchemy_success.mp3" );
}


Sound::~Sound( ) {

}

void Sound::initialize( ) {

}

void Sound::finalize( ) {

}

void Sound::update( ) {

}

void Sound::playSound( SOUND_TYPE type ) {
	FrameworkPtr fw = Framework::getInstance( );
	SoundManagerPtr sound_manager = std::dynamic_pointer_cast< SoundManager >( fw->getTask( typeid( SoundManager ).name( ) ) );

	int sound = 0;
	switch( type ) {
		case DECISION : {
			sound = _decision;
			break;
		}
		case RETURN : {
			sound = _return;
			break;
		}
		case POT_OPEN : {
			sound = _pot_open;
			break;
		}
		case POT_CLOSE : {
			sound = _pot_close;
			break;
		}
		case ALCHEMY_SUCCESS : {
			sound = _alchemy_success;
			break;
		}
	}

	sound_manager->backGroundPlaySound( sound );

}