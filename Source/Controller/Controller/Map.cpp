#include "Map.h"
#include "Framework.h"
#include "Viewer.h"


Map::Map( NetworkControllerPtr network ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	_move_player = false;

	_enemy_reset = true;
	_item_reset = true;
	_mystery_reset = true;

	_network = network;
	_floor = viewer->loadGraph( "work/ctrl_UI/map/floor.png" );
	_player = viewer->loadGraph( "work/ctrl_UI/map/player.png" ); 
	_enemy = viewer->loadGraph( "work/ctrl_UI/map/enemy.png" );
	_item = viewer->loadGraph( "work/ctrl_UI/map/item.png" );
	_stairs = viewer->loadGraph( "work/ctrl_UI/map/stairs.png" );
	_mystery = viewer->loadGraph( "work/ctrl_UI/map/mystery.png" );
	init( );
}
 
 
Map::~Map( ) {
}
 
void Map::update( ) {
 
	/*if ( _network->isEnemyTurnEnd( ) ) {
		 mapChipEnemyTurn( );
	}*/
 
	/*_network->mapRecv( );
	Network::MAP_CHIP_DATA chip = _network->getMapData( );*/
	
	setMapChip( );
	
	if ( _player_pos != _old_player_pos ) {
		// �v���C���[�̈ʒu�ɂ���ă��[�����ʘH�������߂�
		if ( _mapchip[ ( int )_player_pos.x ][ ( int )_player_pos.y ].room != 255 ) {
			openMapRoom( );
		} else {
			openMapChip( ( int )_player_pos.x, ( int )_player_pos.y );
		}
	}
	draw( );
 
	if ( _player_pos == _old_player_pos ) {
		_move_player = false;
	} else {
		_move_player = true;
	}

	//_old_data = chip;
	_old_player_pos = _player_pos;
}
 
// ����������
void Map::init( ) {
	for ( int i = 0; i < MAP_MAX_WIDTH; i++ ) {
		for ( int j = 0; j < MAP_MAX_HEIGHT; j++ ) {
			_mapchip[ i ] [ j ] = MAP_CHIP( );
		}
	}
	_player_pos = Vector2( 0, 0 );
	_stairs_obj = MAP_OBJECT( );
	_item_obj.clear( );
	_enemy_obj.clear( );
	_mystery_obj.clear( );
	_network->resetMapRecv( );
}
void Map::mapChipNextFloor( ) {
	Network::MAP_CHIP_DATA chip;
 
	while ( _network->mapRecv( ) ) {
		chip = _network->getMapData( );
		MAP_OBJECT obj ( chip.pos, false );
		switch( chip.type ) {
		case Network::PLAYER:
			_player_pos = chip.pos;
			break;
		case Network::ENEMY:
			_enemy_obj.push_back( obj );
			break;
		case Network::ITEM:
			_item_obj.push_back( obj );
			break;
		case Network::STAIR:
			_stairs_obj = obj;
			break;
		default:
			_mapchip[ ( int )chip.pos.x ][ ( int )chip.pos.y ] = MAP_CHIP( chip.type, false, chip.room_num );
			break;
		}
	}
}
 
void Map::setMapChip( ) {
	Network::MAP_CHIP_DATA data;
	bool enemy_check = false;	// visible��������邩�ǂ���
	bool item_check = false;	
	bool mystery_check = false;

	while( _network->mapRecv( ) ) {	// ��M�����@�f�[�^���Ȃ��Ȃ�܂ő�����
		data = _network->getMapData( );	// �f�[�^���擾
		switch( data.type ) {	// �擾�����f�[�^�̃^�C�v���ƂɐU�蕪����
		case Network::PLAYER: 
			_player_pos = data.pos;
			break;
		case Network::ENEMY:
			if ( data.zero == true ) {
				_enemy_obj.clear( );
			}
			if ( _enemy_reset == true ) {	//�@�ŏ��̃f�[�^�������ۂɏ���������
				_enemy_obj.clear( );
				enemy_check = true;
				_enemy_reset = false;
			}
			_enemy_obj.push_back( MAP_OBJECT ( data.pos ) );	// obj�Ƀf�[�^��ۑ�
			break;
		case Network::ITEM:
			if ( data.zero == true ) {
				_item_obj.clear( );
			}
			if ( _item_reset == true ) {
				_item_obj.clear( );
				item_check = true;
				_item_reset = false;
			}
			_item_obj.push_back( MAP_OBJECT ( data.pos ) );
			break;
		case Network::MYSTERY:
						if ( data.zero == true ) {
				_mystery_obj.clear( );
			}
			if ( _mystery_reset == true ) {
				_mystery_obj.clear( ) ;
				mystery_check = true;
				_mystery_reset = false;
			}
			_mystery_obj.push_back( MAP_OBJECT ( data.pos ) );
			break;
		}
	}

	_enemy_reset = true;
	_item_reset = true;
	_mystery_reset = true;

	if ( enemy_check == true ) {
		if ( _mapchip[ ( int )_player_pos.x ][ ( int )_player_pos.y ].room != 255 ) {
			openEnemyRoom( );
		} else {
			openEnemyAisle( ( int )_player_pos.x, ( int )_player_pos.y );
		}
	}

	if ( item_check == true ) {
		for ( int i = 0; i < _item_obj.size( ); i++ ) {
			if ( _mapchip[ ( int )_item_obj.at( i ).pos.x ][ ( int )_item_obj.at( i ).pos.y ].visible == true ) {	// ���ɊJ���Ă���chip�̎��͕\������悤�ɂ���
				_item_obj.at( i ).visible = true;
			} else {
				_item_obj.at( i ).visible = false;
			}
		}
	}

	if ( mystery_check == true ) {
		for ( int i = 0; i < _mystery_obj.size( ); i++ ) {
			if ( _mapchip[ ( int )_mystery_obj.at( i ).pos.x ][ ( int )_mystery_obj.at( i ).pos.y ].visible == true ) {	// ���ɊJ���Ă���chip�̎��͕\������悤�ɂ���
				_mystery_obj.at( i ).visible = true;
			} else {
				_mystery_obj.at( i ).visible = false;
			}
		}
	}

	/*if ( chip.type == Network::PLAYER ) {
		_player_pos = chip.pos;
	}
	
	if ( chip.type == Network::ENEMY ) {
		_enemy_obj.clear( );
		MAP_OBJECT enemy = MAP_OBJECT( chip.pos, false );
		_enemy_obj.push_back( enemy );
		while ( _network->mapRecv( ) == true ) {
			Network::MAP_CHIP_DATA enemy_chip = _network->getMapData( );
			if ( enemy_chip.type == Network::ENEMY ) {
				enemy.pos = enemy_chip.pos;
				_enemy_obj.push_back( enemy );
			} else {
				break;
			}
		}
		// �G�l�~�[��\��������悤�ɂ��鏈��
		if ( _mapchip[ ( int )_player_pos.x ][ ( int )_player_pos.y ].room != 255 ) {
			openEnemyRoom( );
		} else {
			openEnemy( ( int )_player_pos.x, ( int )_player_pos.y );
		}

		//_network->resetMapRecv( );
	}
 
	if ( chip.type == Network::ITEM && _old_data.type != Network::ITEM ) {
		_item_obj.clear( );
		MAP_OBJECT item;
		if ( _mapchip[ ( int )chip.pos.x ][ ( int )chip.pos.y ].visible == true ) {
			item = MAP_OBJECT ( chip.pos, true );
		} else {
			item = MAP_OBJECT ( chip.pos, false );
		}
		_item_obj.push_back( item );
 
		while ( _network->mapRecv( ) ) {
			Network::MAP_CHIP_DATA item_chip = _network->getMapData( );
			if ( item_chip.type == Network::ITEM ) {
				if ( _mapchip[ ( int )item_chip.pos.x ][ ( int )item_chip.pos.y ].visible == true ) {	// ���ɊJ���Ă���chip�̎��͕\������悤�ɂ���
					item = MAP_OBJECT ( item_chip.pos, true );
				} else {
					item = MAP_OBJECT ( item_chip.pos, false );
				}
				_item_obj.push_back( item );
			} else {
				break;
			}
		}
	}
	
	if ( chip.type == Network::MYSTERY && _old_data.type != Network::MYSTERY ) {
		_mystery_obj.clear( );
		MAP_OBJECT mystery;
		if ( _mapchip[ ( int )chip.pos.x ][ ( int )chip.pos.y ].visible == true ) {
			mystery = MAP_OBJECT ( chip.pos, true );
		} else {
			mystery = MAP_OBJECT ( chip.pos, false );
		}
		_mystery_obj.push_back( mystery );
		
		while( _network->mapRecv( ) ) {
			Network::MAP_CHIP_DATA mystery_chip = _network->getMapData( );
			if ( mystery_chip.type == Network::MYSTERY ) {
				if ( _mapchip[ ( int )mystery_chip.pos.x ][ ( int )mystery_chip.pos.y ].visible == true ) {
					mystery = MAP_OBJECT ( mystery_chip.pos, true );
				} else {
					mystery = MAP_OBJECT ( mystery_chip.pos, false );
				}
				_mystery_obj.push_back( mystery );
			} else {
				break;
			}
		}
	}

	if ( _player_pos == _old_player_pos ) {
		_move_player = false;
	} else {
		_move_player = true;
	}*/
}
void Map::openMapRoom( ) {
 
	for ( int i = 0; i < MAP_MAX_WIDTH; i++ ) {
		for ( int j = 0; j < MAP_MAX_HEIGHT; j++ ) {
			if ( _mapchip[ i ][ j ].room == _mapchip[ ( int )_player_pos.x ][ ( int )_player_pos.y ].room ) {
				openMapChip( i, j );
			}
		}
	}
}

void Map::openMapChip( int x, int y ) {
	// �L���̎��̏���
	for ( int i = 0; i < MAP_OPEN_NUM; i++ ) {
		for ( int j = 0; j < MAP_OPEN_NUM; j++ ) {
			// �����̎��͂̃}�X��n�}�ɋL��
			Vector2 open_pos( x + i - MAP_OPEN_NUM / 2, y + j - MAP_OPEN_NUM / 2 );
			_mapchip[ ( int )open_pos.x ][ ( int )open_pos.y ].visible = true; 
			
			// �K�i�̕\��
			if ( _stairs_obj.pos == open_pos ) {
				_stairs_obj.visible = true;
			}
			// �A�C�e���̕\��
			for ( int k = 0; k < _item_obj.size( ); k++ ) {
				if ( _item_obj.at( k ).pos == open_pos ) {
					_item_obj.at( k ).visible = true;
				}
			}

			// �����̎��͂ɂ���G�̂ݕ\������悤�ɂ���
			for ( int k = 0; k < _enemy_obj.size( ); k++ ) {
				if ( _enemy_obj.at( k ).pos == open_pos ) {
					_enemy_obj.at( k ).visible = true;
				}
			}

		}
	}
}

void Map::openEnemyRoom( ) {
 
	for ( int i = 0; i < MAP_MAX_WIDTH; i++ ) {
		for ( int j = 0; j < MAP_MAX_HEIGHT; j++ ) {
			if ( _mapchip[ i ][ j ].room == _mapchip[ ( int )_player_pos.x ][ ( int )_player_pos.y ].room ) {
				openEnemy( i, j );
			}
		}
	}
}

void Map::openEnemy( int x, int y ) {
	for ( int i = 0; i < MAP_OPEN_NUM; i++ ) {
		for ( int j = 0; j < MAP_OPEN_NUM; j++ ) {
			Vector2 open_pos( x + i - 1, y + j - 1 );

			// �����̎��͂ɂ���G�̂ݕ\������悤�ɂ���
			for ( int k = 0; k < _enemy_obj.size( ); k++ ) {
				// �J�����Ƃ��Ă���n�_�ɓG�����邩�@&&�@�J�����Ƃ��Ă���}�b�v�����łɊJ���Ă��邩
				if ( _enemy_obj.at( k ).pos == open_pos && _mapchip[ ( int )_enemy_obj.at( k ).pos.x ][ ( int )_enemy_obj.at( k ).pos.y ].visible == true ) {
					_enemy_obj.at( k ).visible = true;
				}
			}
		}
	}
}

void Map::openEnemyAisle( int x, int y ) {
	// �L���̎��̏���
	for ( int i = 0; i < MAP_ENEMY_SEARCH; i++ ) {
		for ( int j = 0; j < MAP_ENEMY_SEARCH; j++ ) {
			Vector2 open_pos( x + i - MAP_ENEMY_SEARCH / 2, y + j - MAP_ENEMY_SEARCH / 2 );

			// �����̎��͂ɂ���G�̂ݕ\������悤�ɂ���
			for ( int k = 0; k < _enemy_obj.size( ); k++ ) {
				if ( _enemy_obj.at( k ).pos == open_pos && _mapchip[ ( int )_enemy_obj.at( k ).pos.x ][ ( int )_enemy_obj.at( k ).pos.y ].visible == true ) {
					_enemy_obj.at( k ).visible = true;
				}
			}
		}
	}
}

void Map::draw( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
 
	// ���̕`��
	for ( int i = 0; i < MAP_MAX_WIDTH; i++ ) {
		for ( int j = 0; j < MAP_MAX_HEIGHT; j++ ) {
			if ( _mapchip[ i ][ j ].type == Network::FLOOR && _mapchip[ i ][ j ].visible == true ) {
				viewer->drawGraph( ( MAP_MAX_WIDTH - i - 1 ) * MAP_CHIP_SIZE + MAP_POS_X, j * MAP_CHIP_SIZE + MAP_POS_Y, _floor );
			} 
		}
	}
 
	// �K�i�̕`��
	if ( _stairs_obj.visible == true ) {
		viewer->drawGraph( ( MAP_MAX_WIDTH - 1 - _stairs_obj.pos.x ) * MAP_CHIP_SIZE + MAP_POS_X, _stairs_obj.pos.y * MAP_CHIP_SIZE + MAP_POS_Y, _stairs );
	}
	// �A�C�e���̕`��
	for ( int i = 0; i < _item_obj.size( ); i++ ) {
		if ( _item_obj.at( i ).visible == true ) {
			viewer->drawGraph( ( MAP_MAX_WIDTH - 1 - _item_obj.at( i ).pos.x ) * MAP_CHIP_SIZE + MAP_POS_X, _item_obj.at( i ).pos.y * MAP_CHIP_SIZE + MAP_POS_Y, _item );
		}
	}
	
	// 㩂̕`��
	for ( int i = 0; i < _mystery_obj.size( ); i++ ) {
		if ( _mystery_obj.at( i ).visible == true ) {
			viewer->drawGraph( ( MAP_MAX_WIDTH - 1 - _mystery_obj.at( i ).pos.x ) * MAP_CHIP_SIZE + MAP_POS_X, _mystery_obj.at( i ).pos.y * MAP_CHIP_SIZE + MAP_POS_Y, _mystery );
		}
	}

	// �G�̕`��
	for ( int i = 0; i < _enemy_obj.size( ); i++ ) {
		if ( _enemy_obj.at( i ).visible == true ) {
			viewer->drawGraph( ( MAP_MAX_WIDTH - 1 - _enemy_obj.at( i ).pos.x ) * MAP_CHIP_SIZE + MAP_POS_X, _enemy_obj.at( i ).pos.y * MAP_CHIP_SIZE + MAP_POS_Y, _enemy );
		}
	}
 
	// �v���C���[�̕`��
	viewer->drawGraph( ( MAP_MAX_WIDTH - 1 - _player_pos.x ) * MAP_CHIP_SIZE + MAP_POS_X, _player_pos.y * MAP_CHIP_SIZE + MAP_POS_Y, _player );
 
}
 
void Map::clairvoyance( ) {	// ���ʂ����g�p��
	for ( int i = 0; i < MAP_MAX_WIDTH; i++ ) {
		for ( int j = 0; j < MAP_MAX_HEIGHT; j++ ) {
			_mapchip[ i ][ j ].visible = true;
		}
	}
 
	// �K�i�̕`��
	_stairs_obj.visible = true;
 
	// �A�C�e���̕`��
	for ( int i = 0; i < _item_obj.size( ); i++ ) {
		_item_obj.at( i ).visible = true;
	}
 
}
 
bool Map::checkPlayerAround( Vector2 pos ) {
 
	// �v���C���[�̈ʒu�ɂ���ă��[���S�̂��v���C���[�̎��͂������߂�
	if ( _mapchip[ ( int )_player_pos.x ][ ( int )_player_pos.y ].room != 255 ) {
		if ( _mapchip[ ( int )_player_pos.x ][ ( int )_player_pos.y ].room == _mapchip[ ( int )pos.x ][ ( int )pos.y ].room ) {
			return true;
		}

	} else {
		for ( int i = 0; i < MAP_OPEN_NUM; i++ ) {
			for ( int j = 0; j < MAP_OPEN_NUM; j++ ) {
				Vector2 open_pos( ( int )_player_pos.x + i - 1, ( int )_player_pos.y + j - 1 );
				if ( open_pos == pos ) {
					return true;
				}
			}
		}
	}
	return false;
}
 
bool Map::isPlayerMove( ) {
	return _move_player;
}

void Map::mysteryClear( ) {
	_mystery_obj.clear( );
}
