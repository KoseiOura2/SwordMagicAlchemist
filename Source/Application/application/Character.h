#pragma once
#include "smart_ptr.h"
#include "mathematics.h"
#include "CharacterStatus.h"
#include <String>

PTR ( Character );
PTR ( Floor );
PTR ( Turn );
PTR ( NetworkApp );
PTR ( MessageLog );
PTR ( Effect );

const int WALK_ANIM_TIME = 15;  // �ړ��A�j���[�V�������Đ����鎞��
const double WARP_LIMIT_Y = 50;
																	
class Character {													
public:
	enum MY_TYPE {
		MY_TYPE_PLAYER,
		MY_TYPE_ENEMY,
	};
	// �A�j���[�V�����̎��
	enum ANIM_STATE {												
		STAY_ANIM,													
		WALK_ANIM,													
		ATTACK_ANIM,												
		DEAD_ANIM,													
		DAMAGE_ANIM,
		REVIVE_ANIM,
	};
	// �A�j���[�V�������A�^�b�`���锠
	struct ANIM_INDEX {												
		int stay;													
		int walk;													
		int attack;													
		int damage;													
		int dead;													
	};
	// �A�j���[�V�����f�[�^�̃n���h��
	struct ANIM_HUNDLE {											
		int model;													
		int stay;													
		int walk;													
		int attack;													
		int damage;													
		int dead;													
	};																
public:																
	Character( FloorPtr floor, NetworkAppPtr network, MessageLogPtr message, EffectPtr effect );													
	~Character( );		
public:
	virtual void update( ) = 0;
	void loadShadow( int shadow_image );
	void refreshState( );	
	void refreshStateNextFloor( );
	void becomeAbnormalState( STATE state, int effect_num );
	void elapsedAbnormalTurn( );
	void refreshSpeed( );
	void changeSpeedState( SPEED speed, int effect_num );
	void elapsedSpeedTurn( );
	void refreshBuff( );
	void changeBuffState( BUFF_STATE buff, int effect_num );
	void elapsedBuffTurn( );
	void statusForBuff( );
	void warpPos( );
	void warpStairPos( );
	bool warpProduction( bool up );
	bool pitProduction( );
	void warpStart( int num );
	void warpStairStart( int num );
	bool isWarp( );
	bool isWarpMove( );
public:
	void setDir( MOVE_DIR dir );
	Vector getDrawPos( );
	Vector getPreDrawPos( );
	Vector2 getPos( );
	STATUS_DATA getStatus( );	
	std::string getName( );		
	float getAngle( );
	ANIM_HUNDLE getAnimHundle( );
	ANIM_INDEX getAnimIndex( );
	int getMainAnim( );
	ANIM_STATE getAnimState( );
	int getAnimCount( );
	float getAnimTime( );
	float getTotalAnimTime( );
	float getAttackAnimTime( );
	float getDamageAnimTime( );
	float getDeadAnimTime( );
	bool isWalking( );
	bool isSpeedAbnormal( );
	bool isNotCornerWall( Vector2 pos );         // �p������h������
protected:			
	void angleChange( );
	void rotateByWarp( );
	void draw( );					
	void move( );
	void playbackAnim( float stay_anim_time, float walk_anim_time,		  // �A�j���[�V�����̍Đ�
		            float attack_anim_time, float dead_anim_time,	  
					float damage_time, float revive_time );
	void decreaseHPForPoison( );
protected:																  
	FloorPtr _floor;
	NetworkAppPtr _network;
	MessageLogPtr _message;
	EffectPtr _effect;
	Vector _draw_pos;													  // �`����W
	Vector2 _pos; 														  // �^�C�����W
	Vector _pre_pos;													  // ���W�ړ��̍ۂ̌��̕`����W
	MY_TYPE _my_type;
	STATUS_DATA _status;		                                          // �X�e�[�^�X
	int _pre_attack;
	std::string _name;					                                  // ���O	  
	float _angle;														  // ���f���̌���
	float _warp_angle;													  // ���f���̌���
	ANIM_HUNDLE _anim_hundle;											  
	ANIM_INDEX _anim_index;												  
	int _main_anim;													      // �A�^�b�`����A�j���[�V�����̔�
	ANIM_STATE _anim_state;				
	int _anim_count;													  // �ړ��A�j���[�V�����̍ۂ̌o�ߎ���
	float _anim_play_time;												  // �A�j���[�V�����Đ�����
	float _total_time;													  // �A�j���[�V������������鎞��
	float _attack_time;													  // �U���A�j���[�V�����ɂ����鎞��
	float _damage_time;													  // �_���[�W�A�j���[�V�����ɂ����鎞��
	float _dead_time;													  // ���S�A�j���[�V�����ɂ����鎞��
	bool _walking;														  // �ړ��A�j���[�V���������ǂ���
	int _state_change_turn;                                               // ��Ԉُ�������̂ɕK�v�ȃ^�[��
	int _elapsed_time;                                                    // ��Ԉُ�ɂ������Ă���̌o�ߎ���
	int _speed_change_turn;
	int _speed_elapsed_time;
	int _buff_change_turn;
	int _buff_elapsed_time;
	bool _speed_abnormal;
	bool _buff;
	bool _buff_end;
	bool _warp;
	bool _warp_stair;
	bool _warp_start;
	bool _warp_move;
	bool _ride_return_trap;
	bool _return_start;
	int _shadow_image;
};

