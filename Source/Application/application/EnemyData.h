#pragma once
#include <string>

// �e���f���̑傫��
const float SWANGLER_SCALE             = 0.4f;
const float OCTO_POT_SCALE             = 0.2f;
const float SPIDER_SCALE               = 0.3f;
const float GOCHIM_SCALE               = 1.5f;
const float SHARK_SCALE                = 0.5f;
const float MINO_SCALE                 = 1.0f;
const float BOSS_SCALE                 = 2.5f;
// �A�j���[�V�����Đ��t���[��
const float STAY_ANIM_FRAME            = 1.0f;
const float WALK_ANIM_FRAME            = 1.5f;
const float DEAD_ANIM_FRAME            = 1.5f;
const float DAMAGE_ANIM_FRAME          = 0.0f;

const float SWANGLER_ATTACK_ANIM_FRAME = 2.5f;
const float OCTO_POT_ATTACK_ANIM_FRAME = 1.0f;
const float SPIDER_ATTACK_ANIM_FRAME   = 1.5f;
const float GOCHIM_ATTACK_ANIM_FRAME   = 1.5f;
const float MINO_ATTACK_ANIM_FRAME     = 1.0f;
const float BOSS_ATTACK_ANIM_FRAME     = 1.5f;

const float SWAN_DEAD_ANIM_FRAME    = 2.5f;
const float SPI_DEAD_ANIM_FRAME     = 1.5f;
const float GOCHIM_DEAD_ANIM_FRAME  = 2.0f;

// �G�l�~�[�̎��
enum ENEMY_TYPE {
	SWANGLER,
	OCTO_POT,
	SPIDER,
	GOCHIMPANZEE,
	SILVER_OCTO_POT,
	MINOTAUR,
	GREAT_SWANGLER,
	GREAT_OCTO_POT,
	GREAT_SPIDER,
	GOLD_OCTO_POT,
	GREAT_MINOTAUR,
	BOSS,
	MAX_ENEMY_NUM
};

// ���O
const std::string ENEMY_NAME[ ] = {
	"�X�����O���[",
	"�I�N�g�|�b�g",
	"�V�F���X�p�C�_�[",
	"�S�`���p��",
	"���^���|�b�g",
	"�^�E���X",
	"�A�C�X�����O���[",
	"�u���[�I�N�g�|�b�g",
	"�V�F���X�p�C�_�[�f",
	"�S�[���f���I�N�g�|�b�g",
	"�~�m�^�E���X",
	"�K�[�f�B�A���E�h���S��",
};

struct ENEMY_DATA {
	std::string name;
	int max_life;
	int attack;
	int deffence;
	int exp;
	int alchemy_point;

	ENEMY_DATA( ) {
		this->name          = "";
		this->max_life      = 0;
		this->attack        = 0;
		this->deffence      = 0;
		this->exp           = 0;
		this->alchemy_point = 0;
	}

	ENEMY_DATA( std::string name, int max_life, int attack, int deffence, int exp, int alchemy_point ) {
		this->name          = name;
		this->max_life      = max_life;
		this->attack        = attack;
		this->deffence      = deffence;
		this->exp           = exp;
		this->alchemy_point = alchemy_point;
	}
};

const ENEMY_DATA ENEMY_DATA_TABLE[ ] = {
		   // ( name,							  max_life, attack, deffence, exp, alchemy_point )
	ENEMY_DATA( ENEMY_NAME[ SWANGLER ],           20,       18,     3,        8,    15 ),
	ENEMY_DATA( ENEMY_NAME[ OCTO_POT ],           13,       15,     5,        7,    10 ),
	ENEMY_DATA( ENEMY_NAME[ SPIDER ],             15,       20,     5,        12,   30 ),
	ENEMY_DATA( ENEMY_NAME[ GOCHIMPANZEE ],       50,       40,     24,       45,   60 ),
	ENEMY_DATA( ENEMY_NAME[ SILVER_OCTO_POT ],    12,       25,     500,      50,   100 ),
	ENEMY_DATA( ENEMY_NAME[ MINOTAUR ],           30,       24,     11,       20,   35 ),
	ENEMY_DATA( ENEMY_NAME[ GREAT_SWANGLER ],     40,       35,     15,       30,   40 ),
	ENEMY_DATA( ENEMY_NAME[ GREAT_OCTO_POT ],     28,       22,     15,       20,   35 ),
	ENEMY_DATA( ENEMY_NAME[ GREAT_SPIDER ],       35,       35,     10,       40,   50 ),
	ENEMY_DATA( ENEMY_NAME[ GOLD_OCTO_POT ],      26,       30,     500,      100,  500 ),
	ENEMY_DATA( ENEMY_NAME[ GREAT_MINOTAUR ],     60,       45,     30,       45,   60 ),
	ENEMY_DATA( ENEMY_NAME[ BOSS ],               500,      60,     35,        0,   0 ),
};

// 1�K�̓K�����x���@�@1(H:45   A:10 D:10)
// 2�K�̓K�����x���@�@3(H:51   A:14 D:12)
// 3�K�̓K�����x���@�@8(H:66   A:24 D:17)
// 4�K�̓K�����x���@ 13(H:81   A:34 D:22)
// 5�K�̓K�����x���@ 15(H:87   A:38 D:34)
