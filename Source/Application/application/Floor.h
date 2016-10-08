#pragma once

#include "smart_ptr.h"
#include "mathematics.h"
#include "Player.h"
#include "NetworkApp.h"
#include "Viewer.h"
#include <vector>

PTR( Floor );
PTR( NetworkApp );

const int FLOOR_MAX_WIDTH  = 50;                                // �t���A�̍ő像�C�Y
const int FLOOR_MAX_HEIGHT = 30;								// �t���A�̍ő�n�C�g

const Vector2 BOSS_ROOM_SIZE = Vector2( 15, 15 ); 
const Vector2 BOSS_ROOM_POS  = Vector2( ( FLOOR_MAX_WIDTH - BOSS_ROOM_SIZE.x ) / 2, ( FLOOR_MAX_HEIGHT - BOSS_ROOM_SIZE.y ) / 2 );

class Floor {
public:
	// �^�C���̎��
	enum TYPE {
		WALL,
		ROOM,
		AISLE,
	};
	// �^�C���̏�ɏ�������Ă������
	enum BOND {
		NONE,
		PLAYER,
		ENEMY
	};

	// �^�C���̃e�N�X�`���[�^�C�v
	enum TILE_TEXTURE_TYPE {
		WATER,
		CAVE,
		JUNGLE,
	};
	
	// �^�C���̉e��ݒ�
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
	void setBondPlayer( int x, int y );															// �v���C���[�^�C���̐ݒ�
	void setBondNone( int x, int y );															// �^�C���̏�̐ݒ�̏�����
	void setBondEnemy( int x, int y );															// �G�l�~�[�^�C���̐ݒ�
	void setItemExist( int x, int y, bool exist );												// �A�C�e���^�C���̐ݒ�
	void setStairExist( int x, int y );															// �K�i�^�C���̐ݒ�
	void onStair( );																// �K�i�ɏ�����������}
	void setFloorLelel( int floor_level );														// ���݂̊K�w��ݒ�
	void visibleTrap( int x, int y );
	void breakMysteryTile( int x, int y );
	void allBreakMysteryTile( );
	void sendNetworkMysteryPos( );
	MYSTERY_TILE onMysteryTile( int x, int y );
	TILE getTile( int x, int y ) const;															// �w��̃^�C�����擾
	TILE getRandomFloor( ) const;																// �����_���^�C�����擾
	TILE getRandomStairFloor( ) const;																// �����_���^�C�����擾
	TILE getFirstConectPoint( );																// �����̐ڑ��_���擾
	TILE getPlayerTile( ) const;																// �v���C���[�^�C�����擾
	TILE getStairTile( ) const;
	ROOM_DATA getRoom( int room_num );      													// �w��̕������擾
	TILE getBossRoomCharacterPos( BOSS_ROOM_CHARACTER character );
	TILE_TEXTURE_TYPE getTextureType( );
private:																					
	void naviLine( ) const;																		// ���ڂ�`��
	void selectFloor( );                                                                        // ��������t���A�p�^�[�������߂�
	void createFloorPattern1( );																// ��������t���A�p�^�[��
	void createFloorPattern2( );
	void createFloorPattern3( );
	void createFloorPattern4( );
	void createFloorPattern5( );
	void createFloorPattern6( );
	void createBossFloor( );
	void createRoom( int num, int max_width, int max_height, int x_origin, int y_origin );		// �����̐���
	void createBossRoom( int max_width, int max_height, int x_origin, int y_origin );           // �{�X�����̐���
	void createAislePattern1( );																// �L���̐���
	void createAislePattern2( );																// �L���̐���
	void createAislePattern3( );																// �L���̐���
	void tileConnect( TILE tile_A, TILE tile_B );												// �������Ȃ���
	void tileConnectDisplaceX( int x, int y, int dir );											// �������Ȃ���Ƃ�x�����ɏC��
	void tileConnectDisplaceY( int x, int y, int dir );											// �������Ȃ���Ƃ��������ɏC��
	void createStair( );																		// �K�i�̐���
	void setStairExist( TILE stair_tile );														// �K�i�^�C���ɐݒ�
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
	int _width_room_num;																			// �������镔���̗�
	int _height_room_num;																		// �������镔���̍s
	int _max_room_num;																			// �������镔���̍ő吔		
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

