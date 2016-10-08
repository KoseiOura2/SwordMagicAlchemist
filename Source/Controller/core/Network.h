#pragma once
#include "smart_ptr.h"
#include "DxLib.h"
#include "CharacterStatus.h"
#include "ItemName.h"
#include "mathematics.h"
#include "SkillType.h"

PTR( Network );

const int NOT_ROOM = 255;			// 部屋でない場合の部屋ナンバー

class Network {
public:
	Network( );
	~Network( );
public:
	enum CTRL_DIR {
		NONE,
		LOWER_LEFT,
		LOWER,
		LOWER_RIGHT,
		LEFT,
		WAIT,
		RIGHT,
		UPPER_LEFT,
		UPPER,
		UPPER_RIGHT,		
	};
	enum CTRL_PHASE {
		MOVE_PHASE,
		NAVI_PHASE,
	};
	enum ITEM_ACTION {
		QUIT,
		PUT,
		EXCHANGE,
		USE,
		THROW,
		EQUIPMENT,
		DISARM,
		PICK_UP,
	};
	enum ON_ITEM {
		NONE_ITEM,
		YES,
		NO,
	};
	enum REVIVE {
		NO_DEAD,
		YES_REVIVE,
		NO_REVIVE,
	};
	enum NEXT_FLOOR {
		NONE_CHOICE,
		GO_NEXT,
		NOT_NEXT,
	};
	enum FOOT_THING {
		FOOT_NONE,
		FOOT_ITEM,
		FOOT_STAIR,
		FOOT_TRAP,
		FOOT_ALCHEMY,
	};
	enum MAP_CHIP_TYPE {
		WALL,
		FLOOR,
		STAIR,
		PLAYER,
		ENEMY,
		ITEM,
		MYSTERY,
	};
	struct MAP_CHIP_DATA {
		MAP_CHIP_TYPE type;
		Vector2 pos;
		int room_num;
		bool zero;
	};
	struct APP_DATA {
		STATUS_DATA status;
		ITEM_TYPE item_type;
		SKILL_TYPE skill_type;
		FOOT_THING foot;
		int floor_level;
		int stamina;
		int level;
		int enemy_num;
		int max_enemy_num;
		int alchemy_point;
		bool ride;
		bool dead;
		bool enemy_turn_end;
		bool in_out_scene;
		bool game_finish;
		bool send_tile_finish;

		// 初期化
		APP_DATA( ) {
			this->foot             = FOOT_NONE;
			this->alchemy_point    = 0;
			this->ride             = false;
			this->dead             = false;
			this->enemy_turn_end   = false;
			this->in_out_scene     = false;
			this->game_finish      = false;
			this->send_tile_finish = false;
		}

		APP_DATA( STATUS_DATA status, FOOT_THING foot, int stamina, int level, int floor_level ) {
			this->foot             = foot;
			this->alchemy_point    = 0;
			this->status           = status;
			this->stamina          = stamina;
			this->level			   = level;
			this->floor_level	   = floor_level;
			this->in_out_scene     = false;
			this->dead             = false;
			this->enemy_turn_end   = false;
			this->game_finish      = false;
			this->send_tile_finish = false;
		}

		virtual ~APP_DATA( ) {
			this->status.~STATUS_DATA( );
			this->item_type.~ITEM_TYPE( );
			this->skill_type.~SKILL_TYPE( );
		}
	};
	struct CTRL_DATA {
		CTRL_DIR dir;
		CTRL_PHASE phase;
		ITEM_TYPE item_type;
		ITEM_ACTION item_action;
		ON_ITEM on_item;
		REVIVE revive;
		SKILL_ID skill_id;
		NEXT_FLOOR next_floor;
		bool attack;
		bool magic_attack;
		bool foot_item;
		bool go_game;
		bool go_title;
		bool finish_app;
		bool return_title;

		// 初期化
		CTRL_DATA( ) {
			this->dir          = NONE;
			this->phase        = MOVE_PHASE;
			this->item_type.id = ITEM_ID::ITEM_NONE;
			this->item_action  = QUIT;
			this->on_item      = NONE_ITEM;
			this->revive	   = NO_DEAD;
			this->skill_id     = SKILL_ID::SKILL_NONE;
			this->next_floor   = NONE_CHOICE;
			this->attack       = false;
			this->magic_attack = false;
			this->foot_item    = false;
			this->go_game      = false;
			this->go_title     = false;
			this->finish_app   = false;
			this->return_title = false;
		}

		CTRL_DATA( CTRL_PHASE phase ) {
			this->dir          = NONE;
			this->phase        = phase;
			this->item_type.id = ITEM_ID::ITEM_NONE;
			this->item_action  = QUIT;
			this->on_item      = NONE_ITEM;
			this->revive	   = NO_DEAD;
			this->skill_id     = SKILL_ID::SKILL_NONE;
			this->next_floor   = NONE_CHOICE;
			this->attack       = false;
			this->magic_attack = false;
			this->foot_item    = false;
			this->go_game      = false;
			this->go_title     = false;
			this->finish_app   = false;
			this->return_title = false;
		}

		virtual ~CTRL_DATA( ) {
			this->item_type.~ITEM_TYPE( );
		}
	};
protected:
	const int PORT_NUM = 9800;
	const int MAP_PORT_NUM = 9850;
protected:
	void drawIpAddress( ) const;
	void update( );
protected:
	IPDATA _ip;
	IPDATA _partner_ip;
	bool _success;	// 初期接続用	
	int _handle;
	int _map_handle;
	int _font;
};

