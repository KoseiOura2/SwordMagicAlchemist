#pragma once
#include "smart_ptr.h"
#include "Task.h"

PTR ( Sound );

class Sound : public Task {
public:
	enum SOUND_TYPE {
		TITLE_BGM,
		CAVE_BGM,
		BOSS_BGM,
		CLEAR_BGM,
		GAME_OVER_BGM,
		ZANGEKI,
		SPEED_UP,
		ATTACK,
		PICK_UP_ITEM,
		WARP,
		CURE,
		LEVEL,
		BUFF,
		DEBUFF,
		NEXT_FLOOR,
	};

public:
	Sound( );
	~Sound( );
	void initialize( );
	virtual void finalize( );
	void update( );
public:
	void loadTitleSound( );
	void loadGameSound( );
	void deleteTitleSound( );
	void deleteGameSound( );
	void playSound( SOUND_TYPE type, bool loop );
	void stopSound( SOUND_TYPE type );
	void backgrondPlaySound( SOUND_TYPE type );
private:
	int _title_bgm;
	int _cave_bgm;
	int _boss_bgm;
	int _clear_bgm;
	int _game_over_bgm;
	int _zangeki;
	int _speed_up;
	int _attack;
	int _pick_up_item;
	int _warp;
	int _cure;
	int _level;
	int _buff;
	int _debuff;
	int _next_floor;
};

