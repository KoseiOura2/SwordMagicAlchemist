#include "Sound.h"
#include "Framework.h"
#include "SoundManager.h"


Sound::Sound( ) {
}


Sound::~Sound( ) {

}

void Sound::initialize( ) {

}

void Sound::finalize( ) {

}

void Sound::update( ) {

}

void Sound::loadTitleSound( ) {
	FrameworkPtr fw = Framework::getInstance( );
	SoundManagerPtr sound_manager = std::dynamic_pointer_cast< SoundManager >( fw->getTask( typeid( SoundManager ).name( ) ) );
	
	_title_bgm = sound_manager->loadSound( "work/sound/BGM/op.MP3" );

	//sound_manager->volumeChange( _cave_bgm, 150 );
}

void Sound::loadGameSound( ) {
	FrameworkPtr fw = Framework::getInstance( );
	SoundManagerPtr sound_manager = std::dynamic_pointer_cast< SoundManager >( fw->getTask( typeid( SoundManager ).name( ) ) );
	
	_cave_bgm      = sound_manager->loadSound( "work/sound/BGM/game_bgm_1.mp3" );
	_boss_bgm      = sound_manager->loadSound( "work/sound/BGM/boss.mp3" );
	_clear_bgm     = sound_manager->loadSound( "work/sound/BGM/clear.mp3" );
	_game_over_bgm = sound_manager->loadSound( "work/sound/SE/dead.mp3" );
	
	_attack          = sound_manager->loadSound( "work/sound/SE/enemy_attack.mp3" );
	_zangeki         = sound_manager->loadSound( "work/sound/SE/skill_attack.mp3" );
	_speed_up        = sound_manager->loadSound( "work/sound/SE/wind_protection.mp3" );
	_pick_up_item    = sound_manager->loadSound( "work/sound/SE/pick_up_item.mp3" );
	_warp            = sound_manager->loadSound( "work/sound/SE/warp.mp3" );
	_cure            = sound_manager->loadSound( "work/sound/SE/cure.mp3" );
	_level           = sound_manager->loadSound( "work/sound/SE/level.mp3" );
	_buff            = sound_manager->loadSound( "work/sound/SE/buff.mp3" );
	_debuff          = sound_manager->loadSound( "work/sound/SE/debuff.mp3" );
	_next_floor      = sound_manager->loadSound( "work/sound/SE/kaidan.mp3" );

	sound_manager->volumeChange( _cave_bgm, 200 );
}


void Sound::deleteTitleSound( ) {
	FrameworkPtr fw = Framework::getInstance( );
	SoundManagerPtr sound_manager = std::dynamic_pointer_cast< SoundManager >( fw->getTask( typeid( SoundManager ).name( ) ) );

	sound_manager->deleteSound( _title_bgm );
}

void Sound::deleteGameSound( ) {
	FrameworkPtr fw = Framework::getInstance( );
	SoundManagerPtr sound_manager = std::dynamic_pointer_cast< SoundManager >( fw->getTask( typeid( SoundManager ).name( ) ) );
	
	sound_manager->deleteSound( _cave_bgm );
	sound_manager->deleteSound( _boss_bgm );
	sound_manager->deleteSound( _clear_bgm );
	sound_manager->deleteSound( _game_over_bgm );
	
	sound_manager->deleteSound( _attack );
	sound_manager->deleteSound( _zangeki );
	sound_manager->deleteSound( _speed_up );
	sound_manager->deleteSound( _pick_up_item );
	sound_manager->deleteSound( _warp );
	sound_manager->deleteSound( _cure );
	sound_manager->deleteSound( _level );
	sound_manager->deleteSound( _buff );
	sound_manager->deleteSound( _debuff );
}

void Sound::playSound( SOUND_TYPE type, bool loop ) {
	FrameworkPtr fw = Framework::getInstance( );
	SoundManagerPtr sound_manager = std::dynamic_pointer_cast< SoundManager >( fw->getTask( typeid( SoundManager ).name( ) ) );

	switch ( type ) {
		case TITLE_BGM:
			sound_manager->playSound( _title_bgm, loop );
			break;
		case CAVE_BGM:
			sound_manager->playSound( _cave_bgm, loop );
			break;
		case BOSS_BGM:
			sound_manager->playSound( _boss_bgm, loop );
			break;
		case CLEAR_BGM:
			sound_manager->playSound( _clear_bgm, loop );
			break;
		case GAME_OVER_BGM:
			sound_manager->playSound( _game_over_bgm, loop );
			break;
		case ATTACK:
			sound_manager->playSound( _attack, loop );
			break;
		case ZANGEKI:
			sound_manager->playSound( _zangeki, loop );
			break;
		case SPEED_UP:
			sound_manager->playSound( _speed_up, loop );
			break;
		case PICK_UP_ITEM:
			sound_manager->playSound( _pick_up_item, loop );
			break;
		case WARP:
			sound_manager->playSound( _warp, loop );
			break;
		case CURE:
			sound_manager->playSound( _cure, loop );
			break;
		case LEVEL:
			sound_manager->playSound( _level, loop );
			break;
		case BUFF:
			sound_manager->playSound( _buff, loop );
			break;
		case DEBUFF:
			sound_manager->playSound( _debuff, loop );
			break;
		case NEXT_FLOOR:
			sound_manager->playSound( _next_floor, loop );
			break;
	}
}

void Sound::stopSound( SOUND_TYPE type ) {
	FrameworkPtr fw = Framework::getInstance( );
	SoundManagerPtr sound_manager = std::dynamic_pointer_cast< SoundManager >( fw->getTask( typeid( SoundManager ).name( ) ) );

	switch ( type ) {
		case TITLE_BGM:
			sound_manager->stopSound( _title_bgm );
			break;
		case CAVE_BGM:
			sound_manager->stopSound( _cave_bgm );
			break;
		case BOSS_BGM:
			sound_manager->stopSound( _boss_bgm );
			break;
		case CLEAR_BGM:
			sound_manager->stopSound( _clear_bgm );
			break;
		case GAME_OVER_BGM:
			sound_manager->stopSound( _game_over_bgm );
			break;
		case ATTACK:
			sound_manager->stopSound( _attack );
			break;
		case ZANGEKI:
			sound_manager->stopSound( _zangeki );
			break;
		case SPEED_UP:
			sound_manager->stopSound( _speed_up );
			break;
		case PICK_UP_ITEM:
			sound_manager->stopSound( _pick_up_item );
			break;
		case WARP:
			sound_manager->stopSound( _warp );
			break;
		case CURE:
			sound_manager->stopSound( _cure );
			break;
		case LEVEL:
			sound_manager->stopSound( _level );
			break;
		case BUFF:
			sound_manager->stopSound( _buff );
			break;
		case DEBUFF:
			sound_manager->stopSound( _debuff );
			break;
		case NEXT_FLOOR:
			sound_manager->stopSound( _next_floor );
			break;
	}
}

void Sound::backgrondPlaySound( SOUND_TYPE type ) {
	FrameworkPtr fw = Framework::getInstance( );
	SoundManagerPtr sound_manager = std::dynamic_pointer_cast< SoundManager >( fw->getTask( typeid( SoundManager ).name( ) ) );

	switch ( type ) {
		case TITLE_BGM:
			sound_manager->backGroundPlaySound( _title_bgm );
			break;
		case CAVE_BGM:
			sound_manager->backGroundPlaySound( _cave_bgm );
			break;
		case BOSS_BGM:
			sound_manager->backGroundPlaySound( _boss_bgm );
			break;
		case CLEAR_BGM:
			sound_manager->backGroundPlaySound( _clear_bgm );
			break;
		case GAME_OVER_BGM:
			sound_manager->backGroundPlaySound( _game_over_bgm );
			break;
		case ATTACK:
			sound_manager->backGroundPlaySound( _attack );
			break;
		case ZANGEKI:
			sound_manager->backGroundPlaySound( _zangeki );
			break;
		case SPEED_UP:
			sound_manager->backGroundPlaySound( _speed_up );
			break;
		case PICK_UP_ITEM:
			sound_manager->backGroundPlaySound( _pick_up_item );
			break;
		case WARP:
			sound_manager->backGroundPlaySound( _warp );
			break;
		case CURE:
			sound_manager->backGroundPlaySound( _cure );
			break;
		case LEVEL:
			sound_manager->backGroundPlaySound( _level );
			break;
		case BUFF:
			sound_manager->backGroundPlaySound( _buff );
			break;
		case DEBUFF:
			sound_manager->backGroundPlaySound( _debuff );
			break;
		case NEXT_FLOOR:
			sound_manager->backGroundPlaySound( _next_floor );
			break;
	}
}