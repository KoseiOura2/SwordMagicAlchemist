#pragma once
#include "NetworkController.h"
#include "Framework.h"
#include <vector>
PTR( Map );

const int MAP_MAX_WIDTH = 50;
const int MAP_MAX_HEIGHT = 30;
const int MAP_CHIP_SIZE = 24;
const int MAP_POS_X = SCREEN_WIDTH / 2 - MAP_MAX_WIDTH * MAP_CHIP_SIZE / 2;
const int MAP_POS_Y = SCREEN_HEIGHT /2 - MAP_MAX_HEIGHT * MAP_CHIP_SIZE / 2 - 50;
const int MAX_ENEMY = 14;

const int MAP_OPEN_NUM = 3;	// �����̎��͂̃}�X���ǂꂾ���J���邩 �R�Ŏ��͂P�}�X
const int MAP_ENEMY_SEARCH = 5;
class Map {
public:
	Map( NetworkControllerPtr network );
	~Map( );
	void init( );
	void mapChipNextFloor( );
	void draw( );
	void update( );
	bool isPlayerMove( );
	void clairvoyance( );	// �痢��
	void mysteryClear( );	// 㩉�
	void mapChipCheck( );
	bool nextFloorFinish( );
private:
	struct MAP_CHIP {
		Network::MAP_CHIP_TYPE type;
		bool visible;
		int room;

		MAP_CHIP( ) {
			this->type = Network::MAP_CHIP_TYPE::WALL;
			this->visible = false;
		}

		MAP_CHIP( Network::MAP_CHIP_TYPE type,  bool visible, int room ) {
			this->type = type;
			this->visible = visible;
			this->room = room;
		}

	};

	struct MAP_OBJECT {
		Vector2 pos;
		bool visible;

		MAP_OBJECT( ) {
			this->pos = Vector2( );
			this->visible = false;
		}

		MAP_OBJECT( Vector2 pos ) {
			this->pos = pos;
			this->visible = false;
		}

		MAP_OBJECT( Vector2 pos, bool visible ){
			this->pos = pos;
			this->visible = visible;
		}

	};
	/*struct MAPCHIP {
		bool wall;
		bool player;
		bool enemy;
		bool stairs;
		bool open;

		MAPCHIP ( ) {
			this->wall = false;
			this->player = false;
			this->enemy = false;
			this->stairs = false;
			this->open = false;
		}
	};*/
private:
//	void setMapChip( Network::MAP_CHIP_DATA chip );
	void setMapChip( );
	void openMapRoom( );
	void openMapChip( int x, int y );
	void openEnemy( int x, int y );
	void openEnemyRoom( );
	void openEnemyAisle( int x, int y );
	bool checkPlayerAround( Vector2 pos );	// pos���v���C���[�̎��肩�ǂ����𔻒f����
private:
	NetworkControllerPtr _network;
	MAP_CHIP _mapchip[ MAP_MAX_WIDTH ][ MAP_MAX_HEIGHT ];
	Vector2 _player_pos;
	Vector2 _old_player_pos;
	std::vector< MAP_OBJECT > _enemy_obj;
	MAP_OBJECT _stairs_obj;
	std::vector< MAP_OBJECT > _item_obj;
	std::vector< MAP_OBJECT > _mystery_obj;
	Network::MAP_CHIP_DATA _old_data;
	bool _move_player;
	bool _next_floor_finish;	// �l�N�X�g�t���A�̂Ńf�[�^��M���I��������ǂ���

	// �}�b�v�`�b�v�̒ʐM�p
	// �eobj�̏������^�C�~���O��ݒ肷��̂Ɏg��
	bool _enemy_reset;
	bool _item_reset;
	bool _mystery_reset;

	// �摜
	int _floor;
	int _player;
	int _enemy;
	int _stairs;
	int _item;
	int _mystery;
};

