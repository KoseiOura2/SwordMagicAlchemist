#pragma once
#include "Icon.h"
#include "SkillType.h"
#include "NetworkController.h"
#include <vector>
#include "Framework.h"

PTR( Skill );
PTR( ItemImage );

	const int SKILL_IMAGE_WIDTH = 100;
	const int SKILL_IMAGE_HEIGHT = 100;
	const int SKILL_WINDOW_WIDTH	 = 1226;
	const int SKILL_WINDOW_HEIGHT	 = 730;
	const int SKILL_WINDOW_X = SCREEN_WIDTH / 2 - SKILL_WINDOW_WIDTH / 2;;
	const int SKILL_WINDOW_Y = 128;
	/*const int SKILL_DISTANCE = SKILL_HEIGHT / 10;
	const int SKILL_LIST_POS_X = SKILL_WINDOW_X + 30;
	const int SKILL_LIST_POS_Y = SKILL_WINDOW_Y + 64;*/
	const int SKILL_USE_WIDTH = 100;
	const int SKILL_USE_STRING_X = SKILL_WINDOW_X + SKILL_WINDOW_WIDTH + 30;
	const int SKILL_USE_HEIGHT = 203;
	const int SKILL_DESCRIPTION_X = SKILL_WINDOW_X + 40;
	const int SKILL_DESCRIPTION_Y = SKILL_WINDOW_Y + SKILL_WINDOW_HEIGHT - 120;

	const int SKILL_ROW = 7;
	const int SKILL_COLUMN = 3;
	const int SKILL_X_INTERVAL = SKILL_WINDOW_WIDTH / SKILL_ROW;
	const int SKILL_Y_INTERVAL = 140;
	const int SKILL_X_SPACE = ( SKILL_WINDOW_WIDTH - ( SKILL_X_INTERVAL * ( SKILL_ROW - 1 ) + SKILL_IMAGE_WIDTH ) ) / 2;
	const int SKILL_Y_SPACE = 100;

	const int NOT_OEPN_SKILL = -1;
class Skill : public Icon {
public:
	struct SKILL_DATA {
		SKILL_TYPE type;
		std::string description;

		SKILL_DATA( ) {
			this->type = SKILL_TYPE( );
			this->description = "";
		}

		SKILL_DATA( const SKILL_ID id, const std::string name, const std::string description ) {
			this->type.id = id;
			this->type.name = name;
			this->description = description;
		}

	};
public:	
	Skill( Vector2 pos, NetworkControllerPtr network, ItemImagePtr item_Image );
	~Skill( );
	void init( );
	void touch( );
	void skillGet( );
	void close( );
private:
	void drawWindow( );
	void openSkill( int num );
	void drawDescription( SKILL_DATA skill );
	SKILL_DATA getSkillData( SKILL_ID id );	// スキルIDからスキルを取得する関数
	int getSkillImage( SKILL_ID id );
	int getSkillSealImage( SKILL_ID id );
	void drawSkillSeal( );
private:
	NetworkControllerPtr _network;
	ItemImagePtr _item_image;
	SKILL_DATA _skill_table[ MAX_SKILL_NUM ];
	std::vector< SKILL_DATA > _skill_list;
	bool _close_flag;		// 閉じることができるかどうかのフラグ
	bool _separate_flag;	// 一度指を離したかどうかのフラグ
	int _open_num;
	int _window;
	int _window_use;
	// スキル用画像
	int _zangeki;
	int _zanmetuha;
	int _materiasword;
	int _speed_up;
	int _zangeki_seal;
	int _zanmetuha_seal;
	int _materiasword_seal;
	int _speed_up_seal;
};

