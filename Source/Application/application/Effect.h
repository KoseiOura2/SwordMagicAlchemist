#pragma once
#include "smart_ptr.h"
#include "mathematics.h"
#include <vector>

PTR ( Effect );

const int SUPPER_FLAME_EFFECT_TIME = 30;

const int EFFECT_PLAYER_NUM = -1;
const int EFFECT_NONE_NUM   = -2;

class Effect {
public:
	enum EFFECT_TYPE {
		EFFECT_HEAL,
		EFFECT_STAMINA,
		EFFECT_FLAME,
		EFFECT_SKILL1,
		EFFECT_SKILL2,
		EFFECT_SKILL3,
		EFFECT_WIND,
		EFFECT_POISON,
		EFFECT_PARALYSIS,
		EFFECT_CONFUSE,
		EFFECT_BUFF,
		EFFECT_DEBUFF,
		EFFECT_SEALED,
		EFFECT_SPORN,
		EFFECT_BOSS_ATTACK,
	};

	struct EFFECT_DATA {
		EFFECT_TYPE type;
		Vector draw_pos;
		int play_hundle;
		int fllow_num;

	};

public:
	Effect( );
	~Effect( );
public:
	void loadEffect( );
	void deleteEffect( );
	void init( );
	void update( );
	void playEffect( EFFECT_TYPE type, Vector pos, Vector rotate, int fllow_num );
	void rePlayEffect( Vector pos, Vector rotate, int num );
	void moveDrawPos( Vector draw_pos, int fllow_num );
	void drawSupperFlameEffect( );
	void startSupperFlameEffect( );
	int isPlayEndEffect( EFFECT_TYPE type, int fllow_num );
private:
	EffectPtr _effect;
	std::vector<EFFECT_DATA> _play_effect;		
	int _supper_flame_effect_time;
	int _supper_flame_effect_index;
	bool _supper_flame_effect_draw;
private:
	int _heal_handle;
	int _stamina_handle;
	int _flame_handle;
	int _skill_1_handle;
	int _skill_2_handle;
	int _skill_3_handle;
	int _skill_4_handle;
	int _poison_handle;
	int _paralysis_handle;
	int _confuse_handle;
	int _buff_handle;
	int _debuff_handle;
	int _seal_handle;
	int _sporn_handle;
	int _boss_attack_handle;
	int _frame_dummy[ 5 ];
};

