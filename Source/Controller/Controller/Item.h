#pragma once
#include "Icon.h"
#include < vector >
#include "ItemName.h"
#include "NetworkController.h"
#include "Framework.h"

PTR ( Item )
PTR ( NetworkController );
PTR ( Map );
PTR ( ItemImage );
	
	const int ITEM_WIDTH = 100;
	const int ITEM_HEIGHT = 100;

	const int MAX_ITEM_NUM = 20;
	const int WINDOW_TOP_DISTANCE = 53;
	const int WINDOW_ITEM_HEIGHT = 377;
	const int WINDOW_HEIGHT = 730;
	const int WINDOW_WIDTH = 1226;
	const int WINDOW_POS_X = SCREEN_WIDTH / 2 - WINDOW_WIDTH / 2;
	const int WINDOW_POS_Y = 128;
	const int ITEM_ROW = 7;		// アイテムを横に何個配置するか
	const int ITEM_COLUMN = 3;	// アイテムを縦に何個配置するか
	const int ITEM_X_INTERVAL = WINDOW_WIDTH / ITEM_ROW;	// ウィンドウの幅　/  ( 横のアイテムの数 )
	const int ITEM_Y_INTERVAL = 140;
	const int ITEM_X_SPACE = ( WINDOW_WIDTH - ( ITEM_X_INTERVAL * ( ITEM_ROW - 1 ) + ITEM_WIDTH ) ) / 2;	// ウィンドウとアイテムの間
	const int ITEM_Y_SPACE = 100;

	const int ITEM_LIST_POS_X = WINDOW_POS_X + 37;
	const int STRING_POS_X = WINDOW_POS_X + WINDOW_WIDTH + 30;
	
	const int USE_WINDOW_HEIGHT = 203;
	
	const int NEXT_PAGE_POS_X = WINDOW_POS_X + 291;
	const int NEXT_PAGE_POS_Y = WINDOW_POS_Y + 497;
	const int NEXT_PAGE_WIDTH = 40;
	const int NEXT_PAGE_HEIGHT = 40;
	const int PREV_PAGE_POS_X = NEXT_PAGE_POS_X + 50;
	const int PREV_PAGE_POS_Y = NEXT_PAGE_POS_Y;
	
	const int MAX_PAGE = 3;
	const int MAX_PAGE_ITEM = MAX_ITEM_NUM / ( MAX_PAGE - 1 );
	
	const int ITEM_DISTANCE = WINDOW_ITEM_HEIGHT / MAX_PAGE_ITEM;
	
	const int NUM_ITEM_X = WINDOW_POS_X + 300;
	const int NUM_ITEM_Y = WINDOW_POS_Y + 30;
	const int PAGE_NUM_X = WINDOW_POS_X + 50;
	const int PAGE_NUM_Y = WINDOW_POS_Y + 500;
	const int DESCRIPTION_X = WINDOW_POS_X + 40;
	const int DESCRIPTION_Y = WINDOW_POS_Y + WINDOW_HEIGHT - 120;
	
	const int ITEM_TOUCH_WIDTH = 100;

	const int MAX_COMMAND_NUM = 10;	// noneを抜くため-1
	const int NOT_EQUIPMENT = -1;
	const int NOT_OPEN_ITEM = -1;
class Item : public Icon {
public:

	enum CATEGORY {
		NONE_ITEM,		
		WEAPON,			// 武器
		ACCESSORY,		// 指輪
		FOOD,			// 食べ物
		CONSUMPTION,	// 消費アイテム
		ROD,			// 振るアイテム
		STONE,			// 投げることのみできるアイテム
	};

	enum COMMAND {
		NONE_COMMAND,
		QUIT,		// とじる
		USE,		// つかう
		SWING,		// ふる
		EAT,		// 食べる
		THROW,		// なげる
		PUT,		// おく
		EXCHANGE,	// 交換
		EQUIPMENT,  // 装備
		DISARM,		// はずす
		PICK_UP,	// 拾う
		MAX_COMMAND
	};

	struct COMMAND_DATA {
		std::string name;
		Network::ITEM_ACTION action;
		COMMAND command;

		COMMAND_DATA( ) {
			this->name = "";
			this->action = Network::ITEM_ACTION::QUIT;
			this->command = NONE_COMMAND;
		}

		COMMAND_DATA( std::string name, Network::ITEM_ACTION action, COMMAND command ) {
			this->name = name;
			this->action = action;
			this->command = command;
		}
	};

	struct ITEM_DATA {
		ITEM_TYPE type;				// アイテムの種類
		CATEGORY category;			// アイテムの分類
		int rarity;					// レアリティ
		std::string description;	// 説明文

		bool equipment;				// 装備しているか

		ITEM_DATA( ) {
			this->type.id = ITEM_NONE;
			this->type.name = "";
			this->rarity = 0;
			this->description = "";
			this->category = NONE_ITEM;
			this->equipment = false;
		}

		ITEM_DATA( const ITEM_TYPE type, const CATEGORY category, const int rarity, std::string description ) {
			this->type = type;
			this->category = category;
			this->rarity = rarity;
			this->description = description;
			this->equipment = false;
		}
	};
public:
	Item( Vector2 pos, NetworkControllerPtr network, MapPtr map, ItemImagePtr item_image );
	~Item( );
	void init( );
	void touch( );
	void close( );
	void onItem( );
	std::vector< ITEM_DATA > getItemList( );
	ITEM_DATA getFootItem( );
	ITEM_DATA getItemStatus( ITEM_ID id );
	ITEM_DATA getItemStatus( ITEM_TYPE type );
	void alchemy( int del_item_1, int del_item_2, ITEM_ID new_item );
	void footItemAlchemy( int del_item, ITEM_ID new_item );
	bool isRiviveItem( );
	void openFootItem( );
	bool isCreateRingEquipment( );
	bool isMagicSwordEquipment( );
	void setFootOpen( bool flag );	// 足下ボタンから足下アイテムを開けるように
	void adjustEquipment( );
private:
	void window( );
	void saveEquipmentItem( );
	void openItem( );
	
	void drawDescription( ITEM_DATA item );
	void setCommand( CATEGORY category, bool equipment );
	COMMAND_DATA getCommandStatus( COMMAND command );
	void openCommand( COMMAND_DATA command );	// 選んだコマンドを処理する関数
	
	// 関数ポイントで使う各コマンドの処理
	void commandQuit( );
	void commandUse( );
	void commandPut( );
	void commandExchange( );
	void commandEquipment( );
	void commandDisarm( );
	void commandThrow( );
	void commandPickUp( );
private:
	int _window;
	int _window_use;
	int _open_num;
	int _open_page;
	bool _close_flag;		// 閉じることができるかどうかのフラグ
	bool _separate_flag;	// 一度指を離したかどうかのフラグ
	NetworkControllerPtr _network;
	MapPtr _map;
	ItemImagePtr _item_image;
	ITEM_DATA _item_table[ MAX_ITEM_TYPE ];
	COMMAND_DATA _command_table[ MAX_COMMAND_NUM ];
	std::vector< ITEM_DATA > _item_list;
	std::vector< COMMAND_DATA > _command_list;
	ITEM_DATA _foot_item;
	bool _foot_open;
	int _equipment_weapon;
	int _equipment_accessory;
};

