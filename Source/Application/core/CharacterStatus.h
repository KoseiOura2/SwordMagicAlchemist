#pragma once


// ƒvƒŒƒCƒ„[‚ÌŒü‚«
enum MOVE_DIR {
	MOVE_DIR_NONE,
	LOWER_LEFT,
	LOWER,
	LOWER_RIGHT,
	LEFT,
	WAIT,
	RIGHT,
	UPPER_LEFT,
	UPPER,
	UPPER_RIGHT,
	MAX_MOVE_DIR,
};

enum STATE {
	NORMAL_STATE,
	POISON,
	PARALYSIS,
	SKILL_SEAL,
	BIND_TILE,
	CONFUSE,
};

enum SPEED {
	NORMAL_SPEED,
	SLOW,
	FAST,
};

enum BUFF_STATE {
	NO_BUFF,
	BUFF,
	DEBUFF,
};

struct STATUS_DATA {
	int max_life;
	int life;
	int attack;
	int defense;
	STATE state;
	SPEED speed;
	BUFF_STATE buff;
	MOVE_DIR dir;

	STATUS_DATA( ) {
		this->state = NORMAL_STATE;
		this->speed = NORMAL_SPEED;
		this->buff  = NO_BUFF;
		this->dir   = LOWER;
	}

	virtual ~STATUS_DATA( ) {
	
	}
};
