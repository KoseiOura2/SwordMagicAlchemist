#pragma once
#include "Character.h"
#include "SkillType.h"
#include "ItemName.h"

PTR ( Player );
PTR ( Floor );
PTR ( MessageLog );
PTR ( NetworkApp );
PTR ( Item );
PTR ( Effect );
PTR ( UIApp );

const int MAX_STAMINA                     = 100;        // �ő�X�^�~�i
const int DECREASE_STAMINA_TURN           = 5;          // �X�^�~�i���P����̂ɂ�����^�[����
const int CONSUMPTION_STAMINA_FOR_SKILL_1 = 5;          // �a���g�p�ɂ��X�^�~�i����
const int CONSUMPTION_STAMINA_FOR_SKILL_2 = 10;         // �a�Ŕg�g�p�ɂ��X�^�~�i����
const int CONSUMPTION_STAMINA_FOR_SKILL_3 = 20;         // �}�e���A�\�[�h�g�p�ɂ��X�^�~�i����
const int CONSUMPTION_STAMINA_FOR_SKILL_4 = 30;         // �����̉���g�p�ɂ��X�^�~�i����

const float DAMAGE_SKILL_1 = 1.4f;       // �a���̃_���[�W�{��
const float DAMAGE_SKILL_2 = 1.2f;       // �a�Ŕg�̃_���[�W�{��
const float DAMAGE_SKILL_3 = 1.3f;       // �}�e���A�\�[�h�̃_���[�W�{��

const int RECOVERLY_POWER_HERB_1         = 30;            // �򑐂̉񕜗�
const int RECOVERLY_POWER_HERB_2         = 60;            // ��򑐂̉񕜗�
const int RECOVERLY_POWER_HERB_3         = 120;           // ����򑐂̉񕜗�
const int RECOVERLY_POWER_MEAT_1         = 20;            // �b�̓��̉񕜗�
const int RECOVERLY_POWER_MEAT_2         = 40;            // �������ȓ��̉񕜗�
const int RECOVERLY_POWER_MEAT_3         = MAX_STAMINA;   // �X�����[�X�̉񕜗�
const int NORMAL_STAMINA_RECOVERLY_POWER = 5;             // �H�ו��̉񕜗�
const int ALCHMY_POINT_STONE_2           = 50;            // �����΂̎��B���|�C���g
const int ALCHMY_POINT_STONE_6           = 500;           // �喂���΂̎��B���|�C���g

const int CAN_EQUIPMENT_NUM = 2;
const int EQUIPMENT_WEAPON  = 0;
const int EQUIPMENT_RING    = 1;

class Player : public Character {
public:
	// �����Z�̃f�[�^
	struct MOVE_SKILL_DATA {
		Vector draw_pos;
		Vector pre_draw_pos;
		Vector2 pos;
		bool hit_enemy;
	};

	struct EQUIPMENT_DATA {
		ITEM_ID id;
		int life;
		int attack;
		int defense;
	};

public:
	Player( FloorPtr floor, TurnPtr turn, MessageLogPtr message, NetworkAppPtr network, ItemPtr item, EffectPtr effect, UIAppPtr ui_app );
	~Player( );
public:
	void loadModel( );
	void init( ); 
	void reset( );        // �K�w�ړ��̍ۂ̃��Z�b�g
	void bossReset( );
	void update( );
	void myTurnAction( );
	void updateStatus( );
	void updateDraw( );
	void randDirForConfuse( );
	void increaseExp( int exp );
	void materiaAbsorption( int absorption_damage );    // HP�z���Z���g�����ۂ�HP��������
	void alchemyPointManage( int point );
	bool pushSpace( );
	bool isTurnEnd( );
public:
	void setDamage( int enemy_power );
	void setTrapDamage( int damage );
	void setZanmetuHitEnemy( bool hit_enemy );
	void setUseMateria( bool use_materia );
	Vector2 getHitEnemyPos( );		
	MOVE_DIR getMoveDir( );
	int getStamina( );
	int getSkillAttackDamage( );
	int getLevel( );
	EQUIPMENT_DATA getEquipment( int equipment_num );
	bool isAttack( );
	bool isSkillAttack( );
	bool isUseZanmetuha( );
	bool isZanmetuHitEnemy( );
	bool isUseMateriaSword( );
	bool isDead( );
	bool isRevive( );
	bool isRideReturnTrap( );
	bool isEquipmentAttackItem( );
	bool isEquipmentSword4( );
	bool isEquipmentRing4( );
	void turnEnd( );
private:
	void setModel( );
	void repairAnim( );
	void setMoveDir( );          // �ړ��������
	void setDir( );              // ����������
	void setMovePos( );
	void settingForWalk( );  // �ړ��ɂ�鏔�X�̐ݒ�
	void walkAnim( );
	void stepMysteryTile( );
	void attack( );
	void skillAttack( );
	void setSkillPosAndRotate( Vector* pos, Vector* rotate );
	void settingForUseSkill( int consumption_stamina, float damage_magnification );  // �X�L���g�p�ɂ�鏔�X�̐ݒ�
	void itemAction( );
	void useItem( );
	void equipmentItem( );
	void disArmItem( );
	void dead( );
	void revive( );		
	void finishDamageAnim( );
	void recoverlyForItem( int recoverly_power, bool is_hp );
	void fluctuationHPForStamina( );       // �X�^�~�i�ɂ����HP�𑝌�������
	void hunger( );     // ������
	void equipmentWeapon( ITEM_ID id );
	void equipmentRing( ITEM_ID id );
	void levelUp( );
	void itemLevelUP( );
	void learnSkillForLevel( );
	void visibleMysteryForDir( );
	void returnTrap( );
	bool okMove( int x, int y );          // �ړ���̃`�F�b�N
private:
	// �v���C���[�̌����ɂ���ĉ������Z�̕�����ς���
	void waveDirNone( MOVE_SKILL_DATA *skill );									    
	void waveDirLowerLeft( MOVE_SKILL_DATA *skill );								    
	void waveDirLower( MOVE_SKILL_DATA *skill );									    
	void waveDirLowerRight( MOVE_SKILL_DATA *skill );							    
	void waveDirLeft( MOVE_SKILL_DATA *skill );									    
	void waveDirWait( MOVE_SKILL_DATA *skill );									    
	void waveDirRight( MOVE_SKILL_DATA *skill );									    
	void waveDirUpperLeft( MOVE_SKILL_DATA *skill );								    
	void waveDirUpper( MOVE_SKILL_DATA *skill );									    
	void waveDirUpperRight( MOVE_SKILL_DATA *skill );	
	Vector waveDirMove( Vector draw_pos, Vector2 pos, Vector pre_pos );	   // �`����W���ړ�
private:
	FloorPtr _floor;
	TurnPtr _turn;
	NetworkAppPtr _network;
	MessageLogPtr _message;
	ItemPtr _item;
	EffectPtr _effect;
	UIAppPtr _ui_app;
private:
	MOVE_DIR _move_dir;
	MOVE_SKILL_DATA _zanmetuha;
	Vector2 _hit_enemy_pos;
	EQUIPMENT_DATA _equipment[ CAN_EQUIPMENT_NUM ];
	int _stamina;
	int _skill_attack_damage;
	int _exp;
	int _necessary_exp;
	int _level;
	int _action_count;
	int _damage;
	int _pre_max_life;
	int _pre_defense;
	bool _attacked;
	bool _attakking;
	bool _skill_attacked;
	bool _damaging;
	bool _dead;
	bool _use_zanmetuha;
	bool _use_materia_sword;
	bool _turn_end;
	bool _no_revive;
	bool _yes_revive;
	bool _weapon_change;
private:
	int _model;
	int _broad_model;
	int _holy_model;
	int _dark_model;
	int _tri_model;
};
