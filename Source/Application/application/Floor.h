#pragma once

#include "smart_ptr.h"
#include "mathematics.h"
#include "Player.h"
#include "NetworkApp.h"
#include "Viewer.h"
#include <vector>

PTR( Floor );
PTR( NetworkApp );

const int FLOOR_MAX_WIDTH  = 50;                                // フロアの最大ワイズ
const int FLOOR_MAX_HEIGHT = 30;								// フロアの最大ハイト

const Vector2 BOSS_ROOM_SIZE = Vector2( 15, 15 ); 
const Vector2 BOSS_ROOM_POS  = Vector2( ( FLOOR_MAX_WIDTH - BOSS_ROOM_SIZE.x ) / 2, ( FLOOR_MAX_HEIGHT - BOSS_ROOM_SIZE.y ) / 2 );

class Floor {
public:
	// タイルの種類
	enum TYPE {
		WALL,
		ROOM,
		AISLE,
	};
	// タイルの上に乗っかっているもの
	enum BOND {
		NONE,
		PLAYER,
		ENEMY
	};

	// タイルのテクスチャータイプ
	enum TILE_TEXTURE_TYPE {
		WATER,
		CAVE,
		JUNGLE,
	};
	
	// タイルの影を設定
	enum TILE_SHADOW {
		LEFT_SIDE,
		UPPER_SIDE,
		LEFT_UPPER_CORNER,
		ELSE,
	};

	enum BOSS_ROOM_CHARACTER {
		BOSS_ROOM_PLAYER,
		BOSS_ROOM_BOSS,
	};

	enum MYSTERY_TILE {
		NONE_MISTERY,
		POISON_TRAP,
		PARALYSIS_TRAP,
		SKILL_SEAL_TRAP,
		SLOW_TRAP,
		CONFUSE_TRAP,
		ALCHEMY_POINT,
		WARP_TRAP,
		DAMGE_TRAP,
		RETURN_TRAP,
		MAX_MISTERY_TILE_TYPE
	};

	struct TILE {
		Vector pos;
		TYPE type;
		BOND bond;
		TILE_SHADOW texture_type;
		MYSTERY_TILE myistery_type;
		int x;
		int y;
		int room;
		int mystery_tile_model;
		bool next_to_room;
		bool floor_surround;
		bool room_inside_surround;
		bool aisle_vertical;
		bool item_exist;
		bool stair_exist;
		bool seen_mystery;

		TILE ( ) {
			this->type = WALL;
			this->room = NOT_ROOM;
			this->bond = NONE;
			this->mystery_tile_model   = 0;
			this->next_to_room         = false;
			this->floor_surround       = false;
			this->room_inside_surround = false;
			this->aisle_vertical       = false;
			this->item_exist           = false;
			this->stair_exist          = false;
			this->seen_mystery         = false;
			this->texture_type  = ELSE;
			this->myistery_type = NONE_MISTERY;
		}
	};
	struct ROOM_DATA {
		TILE origin;
		TILE first_conect_point;
		int width;
		int height;
		int longest;
	};

	struct TILE_HANDLE {
		int floor_image;																			
		int left_side_image;																		
		int upper_side_image;																		
		int left_upper_corner_image;																
		int wall_image;																			
		int ceiling_image;		
	};
public:
	Floor( NetworkAppPtr network );
	~Floor( );
	void loadGraph( );
	void deleteGraph( );
	void init( );
	void reset( );
	void bossReset( );
	void update( );
public:
	void setBondPlayer( int x, int y );															// プレイヤータイルの設定
	void setBondNone( int x, int y );															// タイルの上の設定の初期化
	void setBondEnemy( int x, int y );															// エネミータイルの設定
	void setItemExist( int x, int y, bool exist );												// アイテムタイルの設定
	void setStairExist( int x, int y );															// 階段タイルの設定
	void onStair( );																// 階段に乗っかった合図
	void setFloorLelel( int floor_level );														// 現在の階層を設定
	void visibleTrap( int x, int y );
	void breakMysteryTile( int x, int y );
	void allBreakMysteryTile( );
	void sendNetworkMysteryPos( );
	MYSTERY_TILE onMysteryTile( int x, int y );
	TILE getTile( int x, int y ) const;															// 指定のタイルを取得
	TILE getRandomFloor( ) const;																// ランダムタイルを取得
	TILE getRandomStairFloor( ) const;																// ランダムタイルを取得
	TILE getFirstConectPoint( );																// 部屋の接続点を取得
	TILE getPlayerTile( ) const;																// プレイヤータイルを取得
	TILE getStairTile( ) const;
	ROOM_DATA getRoom( int room_num );      													// 指定の部屋を取得
	TILE getBossRoomCharacterPos( BOSS_ROOM_CHARACTER character );
	TILE_TEXTURE_TYPE getTextureType( );
private:																					
	void naviLine( ) const;																		// 升目を描画
	void selectFloor( );                                                                        // 生成するフロアパターンを決める
	void createFloorPattern1( );																// 生成するフロアパターン
	void createFloorPattern2( );
	void createFloorPattern3( );
	void createFloorPattern4( );
	void createFloorPattern5( );
	void createFloorPattern6( );
	void createBossFloor( );
	void createRoom( int num, int max_width, int max_height, int x_origin, int y_origin );		// 部屋の生成
	void createBossRoom( int max_width, int max_height, int x_origin, int y_origin );           // ボス部屋の生成
	void createAislePattern1( );																// 廊下の生成
	void createAislePattern2( );																// 廊下の生成
	void createAislePattern3( );																// 廊下の生成
	void tileConnect( TILE tile_A, TILE tile_B );												// 部屋をつなげる
	void tileConnectDisplaceX( int x, int y, int dir );											// 部屋をつなげるときx方向に修正
	void tileConnectDisplaceY( int x, int y, int dir );											// 部屋をつなげるときｙ方向に修正
	void createStair( );																		// 階段の生成
	void setStairExist( TILE stair_tile );														// 階段タイルに設定
	void createMysteryTile( MYSTERY_TILE type );
	void dicisionMysteryTileForFloor( );
	void setMysteryTile( TILE mystery_tile );
	void drawFloor( ) const;					
	void drawWaterFloor( ) const;	
	void drawJungleFloor( ) const;	
	void drawCaveFloor( ) const;	
	bool isNotNearByAisle( TILE tile );
private:																						
	NetworkAppPtr _network;																		
	TILE _tile[ FLOOR_MAX_WIDTH ][ FLOOR_MAX_HEIGHT ];											
	TILE _player_tile;
	TILE _stair_tile;
	std::vector<TILE> _mystery_tile;
	std::vector< ROOM_DATA > _room;
	TILE_TEXTURE_TYPE _texture;
	int _floor_level;
	int _width_room_num;																			// 生成する部屋の列
	int _height_room_num;																		// 生成する部屋の行
	int _max_room_num;																			// 生成する部屋の最大数		
	int _create_mystery_tile_num;
private:					
	TILE_HANDLE _water;
	TILE_HANDLE _jungle;
	TILE_HANDLE _cave;
	int _stair_model;		
	int _poison_trap_model;
	int _paralysis_trap_model;
	int _skill_seal_trap_model;
	int _slow_trap_model;
	int _confuse_trap_model;
	int _alchemy_point_tile_model;
	int _warp_trap_model;
	int _pit_trap_model;
	int _damage_trap_model;
	int _background;
};

