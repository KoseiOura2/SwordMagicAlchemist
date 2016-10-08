#include "Floor.h"
#include "Framework.h"
#include "Viewer.h"
#include "Keyboard.h"
#include "Sound.h"
#include <vector>

const float STAIR_SCALE = 0.3f;
const float STAIR_ROTATE_Y = 180.0f;

Floor::Floor( NetworkAppPtr network ) {
	_network = network;
	loadGraph( );
}

Floor::~Floor( ) {

}

void Floor::loadGraph( ) {
	FrameworkPtr fw          = Framework::getInstance( );
	ViewerPtr viewer         = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	_stair_model                    = viewer->loadModel( "work/model/stairs/stairs.mv1" );
	_poison_trap_model              = viewer->loadModel( "work/model/trap/trap_01_poison/trap_01.mv1" );
	_paralysis_trap_model           = viewer->loadModel( "work/model/trap/trap_02_paralysis/trap_02.mv1" );
	_skill_seal_trap_model          = viewer->loadModel( "work/model/trap/trap_03_sealed/trap_03.mv1" );
	_slow_trap_model                = viewer->loadModel( "work/model/trap/trap_04_slow/trap_04.mv1" );
	_confuse_trap_model             = viewer->loadModel( "work/model/trap/trap_05_confuse/trap_05.mv1" );
	_alchemy_point_tile_model       = viewer->loadModel( "work/model/trap/trap_06_alchemy_tile/trap_06.mv1" );
	_warp_trap_model                = viewer->loadModel( "work/model/trap/trap_08_warp/trap_08.mv1" );
	_pit_trap_model                 = viewer->loadModel( "work/model/trap/trap_09_return/trap_09.mv1" );
	_damage_trap_model              = viewer->loadModel( "work/model/trap/trap_07_damage/trap_07.mv1" );
	_background                     = viewer->loadGraph( "work/background/dungeon_back.jpg");

	_cave.floor_image               = viewer->loadGraph( "work/tile/2d_map_textuer04.png" );
	_cave.left_side_image           = viewer->loadGraph( "work/tile/2d_map_textuer09.png" );
	_cave.upper_side_image          = viewer->loadGraph( "work/tile/2d_map_textuer08.png" );
	_cave.left_upper_corner_image   = viewer->loadGraph( "work/tile/2d_map_textuer10.png" );
	_cave.wall_image                = viewer->loadGraph( "work/tile/2d_map_textuer12.png" );
	_cave.ceiling_image             = viewer->loadGraph( "work/tile/2d_map_textuer11.png" );

	_jungle.floor_image             = viewer->loadGraph( "work/tile/2d_map_floor_jungle_01.png" );
	_jungle.left_side_image         = viewer->loadGraph( "work/tile/2d_map_floor_jungle_01.png" );
	_jungle.upper_side_image        = viewer->loadGraph( "work/tile/2d_map_floor_jungle_01.png" );
	_jungle.left_upper_corner_image = viewer->loadGraph( "work/tile/2d_map_floor_jungle_01.png" );
	_jungle.wall_image              = viewer->loadGraph( "work/tile/2d_map_wall_jungle.png" );
	_jungle.ceiling_image           = viewer->loadGraph( "work/tile/2d_map_floor_jungle_02.png" );
	
	_water.floor_image              = viewer->loadGraph( "work/tile/3d_map_floor_water_01.png" );
	_water.left_side_image          = viewer->loadGraph( "work/tile/3d_map_floor_water_03.png" );
	_water.upper_side_image         = viewer->loadGraph( "work/tile/3d_map_floor_water_02.png" );
	_water.left_upper_corner_image  = viewer->loadGraph( "work/tile/3d_map_floor_water_04.png" );
	_water.wall_image               = viewer->loadGraph( "work/tile/3d_map_wall_water_02.png" );
	_water.ceiling_image            = viewer->loadGraph( "work/tile/3d_map_wall_water_01.png" );
}

void Floor::deleteGraph( ) {
	FrameworkPtr fw          = Framework::getInstance( );
	ViewerPtr viewer         = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	viewer->deleatModel( _stair_model );
	viewer->deleatModel( _poison_trap_model );
	viewer->deleatModel( _paralysis_trap_model );
	viewer->deleatModel( _skill_seal_trap_model );
	viewer->deleatModel( _slow_trap_model );
	viewer->deleatModel( _confuse_trap_model );
	viewer->deleatModel( _alchemy_point_tile_model );
	viewer->deleatModel( _warp_trap_model );
	viewer->deleatModel( _pit_trap_model );
	viewer->deleatModel( _damage_trap_model );
	viewer->deleatModel( _stair_model );
	viewer->deleteGraph( _background );
	viewer->deleteGraph( _cave.floor_image );           
	viewer->deleteGraph( _cave.left_side_image );       
	viewer->deleteGraph( _cave.upper_side_image );      
	viewer->deleteGraph( _cave.left_upper_corner_image );
	viewer->deleteGraph( _cave.wall_image );        
	viewer->deleteGraph( _cave.ceiling_image );
	viewer->deleteGraph( _jungle.floor_image );           
	viewer->deleteGraph( _jungle.left_side_image );       
	viewer->deleteGraph( _jungle.upper_side_image );      
	viewer->deleteGraph( _jungle.left_upper_corner_image );
	viewer->deleteGraph( _jungle.wall_image );        
	viewer->deleteGraph( _jungle.ceiling_image );
	viewer->deleteGraph( _water.floor_image );           
	viewer->deleteGraph( _water.left_side_image );       
	viewer->deleteGraph( _water.upper_side_image );      
	viewer->deleteGraph( _water.left_upper_corner_image );
	viewer->deleteGraph( _water.wall_image );        
	viewer->deleteGraph( _water.ceiling_image );
	viewer->deleteGraph( _cave.floor_image );           
	viewer->deleteGraph( _cave.left_side_image );       
	viewer->deleteGraph( _cave.upper_side_image );      
	viewer->deleteGraph( _cave.left_upper_corner_image );
	viewer->deleteGraph( _cave.wall_image );        
	viewer->deleteGraph( _cave.ceiling_image );
}

void Floor::init( ) {
	_floor_level = 0;
}

void Floor::reset( ) {
	// mysteryタイルの初期化
	_mystery_tile.erase( _mystery_tile.begin( ), _mystery_tile.end( ) );

	// 全タイルの配置
	for ( int i = 0; i < FLOOR_MAX_WIDTH; i++ ) {
		for ( int j = 0; j < FLOOR_MAX_HEIGHT; j++ ) {
			TILE data;
			data.pos                  = Vector( i * TILE_SIZE, 0, j * TILE_SIZE );
			data.x                    = i;
			data.y                    = j;
			_tile[ i ][ j ]           = data;
		}
	}
	// フロアの内周を設定
	// 横
	for ( int i = 0; i < FLOOR_MAX_WIDTH; i++ ) {
		_tile[ i ][ 0 ].floor_surround = true;
		_tile[ i ][ FLOOR_MAX_HEIGHT - 1 ].floor_surround = true;
	}
	// 縦
	for ( int l = 1; l < FLOOR_MAX_HEIGHT - 1; l++ ) {
		_tile[ 0 ][ l ].floor_surround = true;
		_tile[ FLOOR_MAX_WIDTH - 1 ][ l ].floor_surround = true;
	}
	// roomの初期化
	_room.clear( );
	_room.shrink_to_fit( );

	// 生成するフロアを選択
	selectFloor( );

	// 廊下と接していたらテクスチャーを修正
	for ( int i = 0; i < _max_room_num; i++ ) {
		// 上側
		for ( int j = _room.at( i ).origin.x; j < _room.at( i ).origin.x + _room.at( i ).width - 1; j++ ) {
			if ( _tile[ j ][ _room.at( i ).origin.y - 1 ].type == AISLE ) {
				_tile[ j ][ _room.at( i ).origin.y ].texture_type = ELSE;
			}
		}
		// 左側
		for ( int j = _room.at( i ).origin.y + 1; j < _room.at( i ).origin.y + _room.at( i ).height; j++ ) {
			if ( _tile[ _room.at( i ).origin.x + _room.at( i ).width ][ j ].type == AISLE ) {
				_tile[ _room.at( i ).origin.x + _room.at( i ).width - 1 ][ j ].texture_type = ELSE;
			}
		}
		// 左上角
		if ( _tile[ _room.at( i ).origin.x + _room.at( i ).width ][ _room.at( i ).origin.y ].type == AISLE ) {
			_tile[ _room.at( i ).origin.x + _room.at( i ).width - 1 ][ _room.at( i ).origin.y ].texture_type = UPPER_SIDE;
		}
		if ( _tile[ _room.at( i ).origin.x + _room.at( i ).width - 1 ][ _room.at( i ).origin.y - 1 ].type == AISLE ) {
			_tile[ _room.at( i ).origin.x + _room.at( i ).width - 1 ][ _room.at( i ).origin.y ].texture_type = LEFT_SIDE;
		}
	}

	// 左側のたいるが壁である廊下のテクスチャを設定
	for ( int i = 0; i < FLOOR_MAX_WIDTH - 1; i++ ) {
		for ( int j = 0; j < FLOOR_MAX_HEIGHT; j++ ) {
			if ( _tile[ i ][ j ].type == AISLE &&
				 _tile[ i + 1 ][ j ].type == WALL ) {
				_tile [ i ][ j ].aisle_vertical = true;
			}
		}
	}
	// 階段の生成
	createStair( );

	// 生成する罠を決定
	dicisionMysteryTileForFloor( );

	// 部屋のとなりの廊下を設定
	for ( int i = 0; i < FLOOR_MAX_WIDTH; i++ ) {
		for ( int j = 0; j < FLOOR_MAX_HEIGHT; j++ ) {
			if ( _tile[ i ][ j ].type == AISLE ) {
				for ( int k = -1; k <= 1; k += 2 ) {
					if ( _tile[ i + k ][ j ].type == ROOM ) {
						_tile[ i ][ j ].next_to_room = true;
						_tile[ i ][ j ].room = _tile[ i + k ][ j ].room;
					}
					if ( _tile[ i ][ j + k ].type == ROOM ) {
						_tile[ i ][ j ].next_to_room = true;
						_tile[ i ][ j ].room = _tile[ i ][ j + k ].room;
					}
				}

			}
		}
	}
}

void Floor::bossReset( ) {

	// 全タイル初期化
	for ( int i = 0; i < FLOOR_MAX_WIDTH; i++ ) {
		for ( int j = 0; j < FLOOR_MAX_HEIGHT; j++ ) {
			TILE data;
			data.pos                  = Vector( i * TILE_SIZE, 0, j * TILE_SIZE );
			data.type                 = WALL;
			data.x                    = i;
			data.y                    = j;
			data.room                 = NOT_ROOM;
			data.bond                 = NONE;
			data.next_to_room         = false;
			data.floor_surround       = false;
			data.room_inside_surround = false;
			data.aisle_vertical       = false;
			data.item_exist           = false;
			data.stair_exist          = false;
			data.texture_type         = ELSE;
			_tile[ i ][ j ]           = data;
		}
	}
	// フロアの内周を設定
	// 横
	for ( int i = 0; i < FLOOR_MAX_WIDTH; i++ ) {
		_tile[ i ][ 0 ].floor_surround = true;
		_tile[ i ][ FLOOR_MAX_HEIGHT - 1 ].floor_surround = true;
	}
	// 縦
	for ( int l = 1; l < FLOOR_MAX_HEIGHT - 1; l++ ) {
		_tile[ 0 ][ l ].floor_surround = true;
		_tile[ FLOOR_MAX_WIDTH - 1 ][ l ].floor_surround = true;
	}
	// roomの初期化
	_room.clear( );
	_room.shrink_to_fit( );

	
	_texture = CAVE;
	// 生成するフロアを選択
	createBossFloor( );
}

void Floor::selectFloor( ) {
	FrameworkPtr fw = Framework::getInstance( );
	SoundPtr sound = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );

	int floor_pattern = 5;
	switch( _floor_level ) {
	case 1:
		floor_pattern = 0;
		_texture = WATER;
		break;
	case 2:
		floor_pattern = 1 + rand( ) % 2;
		_texture = JUNGLE;
		break;
	case 3:
		floor_pattern = 3;
		_texture = WATER;
		break;
	case 4:
		floor_pattern = 4 + rand( ) % 2;
		_texture = JUNGLE;
		break;
	}
	//floor_pattern = 4;
	// 階層によって呼び出す関数を変える
	void ( Floor::* funcArray[ ] )( ) = {
		&Floor::createFloorPattern1,
		&Floor::createFloorPattern2,
		&Floor::createFloorPattern3,
		&Floor::createFloorPattern4,
		&Floor::createFloorPattern5,
		&Floor::createFloorPattern6,
	};
	void ( Floor::* func )( ) = funcArray[ floor_pattern ];
	( this->*func )( );
}

void Floor::createFloorPattern1( ) {
	// 部屋数の設定
	_width_room_num  = 7;
	_height_room_num = 7;
	_max_room_num    = 3;
	// 各部屋の原点を求める
	// 部屋の最大サイズ
	int max_width  = FLOOR_MAX_WIDTH / _width_room_num;         // 部屋の横幅 = フロア全体の横幅 / 1行に配置できる最大部屋数
	int max_height = FLOOR_MAX_HEIGHT / _height_room_num;		// 部屋の縦幅 = フロア全体の縦幅 / 1列に配置できる最大部屋数
	// 各部屋の原点
	std::vector< int > x_origin;
	std::vector< int > y_origin;
	// 部屋の原点候補(フロアを６×６当分し、周を除いた真ん中を４つのエリアに区切りまたそのエリアを４つに区切る)
	std::vector< std::vector< Vector2 > > origin_candidate = {
		// 右上のエリア４つ分
		{ 
			//Vector2( max_width, max_height ), 
			Vector2( max_width * 2, max_height ),
		    //Vector2( max_width, max_height * 2 ),
			Vector2( max_width * 2, max_height * 2 )        
		},
		// 左上のエリア４つ分
		{ 
			Vector2( max_width * 4, max_height ), //Vector2( max_width * 5, max_height ),
		    Vector2( max_width * 4, max_height * 2 ), //Vector2( max_width * 5, max_height * 2 )
		},
		// 右下のエリア４つ分
		{ 
			//Vector2( max_width, max_height * 4 ),
			Vector2( max_width * 2, max_height * 4 ),
		    //Vector2( max_width, max_height * 5 ),
			Vector2( max_width * 2, max_height * 5 )
		},
		// 左下のエリア４つ分
		{ 
			Vector2( max_width * 4, max_height * 4 ), //Vector2( max_width * 5, max_height * 4 ),
		    Vector2( max_width * 4, max_height * 5 ), //Vector2( max_width * 5, max_height * 5 ) 
		},
	};

	// 初期化
	for ( int i = 0; i < _max_room_num; i++ ) {
		int num = 0;
		ROOM_DATA room;
		x_origin.push_back( num );
		y_origin.push_back( num );
		_room.push_back( room );
	}

	for ( int i = 0; i < _max_room_num; i++ ) {
		// エリアの選出
		int num   = rand( ) % origin_candidate.size( );
		// エリアのエリアを選出
		int num_2 = rand( ) % origin_candidate.front( ).size( );
		while ( true ) {
			x_origin.at( i ) = rand( ) % 5 + ( int )origin_candidate[ num ][ num_2 ].x;
			y_origin.at( i ) = rand( ) % 5 + ( int )origin_candidate[ num ][ num_2 ].y;
			// 内回りと被らなかったら抜ける
			if ( _tile[ x_origin.at( i ) ][ y_origin.at( i ) ].floor_surround == false ) {
				// 選んだエリアを削除
				origin_candidate.erase( origin_candidate.begin( ) + num );
				break;
			}
		}
		// 部屋の生成
		createRoom( i, max_width, max_height, x_origin.at( i ), y_origin.at( i ) );
	}
	// 通路の生成
	createAislePattern1( );
}

void Floor::createFloorPattern2( ) {
	// 部屋数の設定
	_width_room_num  = 7;
	_height_room_num = 7;
	_max_room_num    = 4;
	// 各部屋の原点を求める
	// 部屋の最大サイズ
	int max_width  = FLOOR_MAX_WIDTH / _width_room_num;         // 部屋の横幅 = フロア全体の横幅 / 1行に配置できる最大部屋数
	int max_height = FLOOR_MAX_HEIGHT / _height_room_num;		// 部屋の縦幅 = フロア全体の縦幅 / 1列に配置できる最大部屋数
	// 各部屋の原点
	std::vector< int > x_origin;
	std::vector< int > y_origin;
	// 部屋の原点候補(フロアを６×６当分し、周を除いた真ん中を４つのエリアに区切りまたそのエリアを４つに区切る)
	std::vector< std::vector< Vector2 > > origin_candidate = {
		// 右上のエリア４つ分
		{ 
			Vector2( max_width, max_height ), Vector2( max_width * 2, max_height ),
		    Vector2( max_width, max_height * 2 ), Vector2( max_width * 2, max_height * 2 )        
		},
		// 左上のエリア４つ分
		{ 
			Vector2( max_width * 4, max_height ), Vector2( max_width * 5, max_height ),
		    Vector2( max_width * 4, max_height * 2 ), Vector2( max_width * 5, max_height * 2 )
		},
		// 右下のエリア４つ分
		{ 
			Vector2( max_width, max_height * 4 ), Vector2( max_width * 2, max_height * 4 ),
		    Vector2( max_width, max_height * 5 ), Vector2( max_width * 2, max_height * 5 )
		},
		// 左下のエリア４つ分
		{ 
			Vector2( max_width * 4, max_height * 4 ), Vector2( max_width * 5, max_height * 4 ),
		    Vector2( max_width * 4, max_height * 5 ), Vector2( max_width * 5, max_height * 5 ) 
		},
	};

	// 初期化
	for ( int i = 0; i < _max_room_num; i++ ) {
		int num = 0;
		ROOM_DATA room;
		x_origin.push_back( num );
		y_origin.push_back( num );
		_room.push_back( room );
	}

	for ( int i = 0; i < _max_room_num; i++ ) {
		// エリアの選出
		int num   = rand( ) % origin_candidate.size( );
		// エリアのエリアを選出
		int num_2 = rand( ) % origin_candidate.front( ).size( );
		while ( true ) {
			x_origin.at( i ) = rand( ) % 5 + origin_candidate[ num ][ num_2 ].x;
			y_origin.at( i ) = rand( ) % 5 + origin_candidate[ num ][ num_2 ].y;
			// 内回りと被らなかったら抜ける
			if ( _tile[ x_origin.at( i ) ][ y_origin.at( i ) ].floor_surround == false ) {
				// 選んだエリアを削除
				origin_candidate.erase( origin_candidate.begin( ) + num );
				break;
			}
		}
		// 部屋の生成
		createRoom( i, max_width, max_height, x_origin.at( i ), y_origin.at( i ) );
	}
	// 通路の生成
	createAislePattern1( );
}

void Floor::createFloorPattern3( ) {
	// 部屋数の設定
	_width_room_num  = 10;
	_height_room_num = 7;
	_max_room_num    = 6;
	// 各部屋の原点を求める
	// 部屋の最大サイズ
	int max_width  = FLOOR_MAX_WIDTH / _width_room_num;         // 部屋の横幅 = フロア全体の横幅 / 1行に配置できる最大部屋数
	int max_height = FLOOR_MAX_HEIGHT / _height_room_num;		// 部屋の縦幅 = フロア全体の縦幅 / 1列に配置できる最大部屋数
	// 各部屋の原点
	std::vector< int > x_origin;
	std::vector< int > y_origin;
	// 部屋の原点候補(フロアを４×６当分し、６つのエリアに区切りまたそのエリアを４つに区切る)
	std::vector< std::vector< Vector2 > > origin_candidate = {
		// 右上のエリア４つ分
		{ 
			Vector2( max_width, max_height ), Vector2( max_width * 2, max_height ),
		    Vector2( max_width, max_height * 2 ), Vector2( max_width * 2, max_height * 2 )        
		},
		// 中上のエリア４つ分
		{ 
			Vector2( max_width * 4, max_height ), Vector2( max_width * 5, max_height ),
		    Vector2( max_width * 4, max_height * 2 ), Vector2( max_width * 5, max_height * 2 )  
		},
		// 左上のエリア４つ分
		{ 
			Vector2( max_width * 7, max_height ), Vector2( max_width * 8, max_height ),
		    Vector2( max_width * 7, max_height * 2 ), Vector2( max_width * 8, max_height * 2 )  
		},
		// 右下のエリア４つ分
		{ 
			Vector2( max_width, max_height * 4 ), Vector2( max_width * 2, max_height * 4 ),
		    Vector2( max_width, max_height * 5 ), Vector2( max_width * 2, max_height * 5 )     
		},
		// 中下のエリア４つ分
		{ 
			Vector2( max_width * 4, max_height * 4 ), Vector2( max_width * 5, max_height * 4 ),
		    Vector2( max_width * 4, max_height * 5 ), Vector2( max_width * 5, max_height * 5 )  
		},
		// 左下のエリア４つ分
		{ 
			Vector2( max_width * 7, max_height * 4 ), Vector2( max_width * 8, max_height * 4 ),
		    Vector2( max_width * 7, max_height * 5 ), Vector2( max_width * 8, max_height * 5 )  
		},
	};

	// 初期化
	for ( int i = 0; i < _max_room_num; i++ ) {
		int num = 0;
		ROOM_DATA room;
		x_origin.push_back( num );
		y_origin.push_back( num );
		_room.push_back( room );
	}

	for ( int i = 0; i < _max_room_num; i++ ) {
		// エリアの選出
		int num   = rand( ) % origin_candidate.size( );
		// エリアのエリアを選出
		int num_2 = rand( ) % origin_candidate.front( ).size( );
		while ( true ) {
			x_origin.at( i ) = rand( ) % 5 + origin_candidate[ num ][ num_2 ].x;
			y_origin.at( i ) = rand( ) % 5 + origin_candidate[ num ][ num_2 ].y;
			// 内回りと被らなかったら抜ける
			if ( _tile[ x_origin.at( i ) ][ y_origin.at( i ) ].floor_surround == false ) {
				// 選んだエリアを削除
				origin_candidate.erase( origin_candidate.begin( ) + num );
				break;
			}
		}
		// 部屋の生成
		createRoom( i, max_width, max_height, x_origin.at( i ), y_origin.at( i ) );
	}
	// 通路の生成
	createAislePattern1( );
}

void Floor::createFloorPattern4( ) {
	// 部屋数の設定
	_width_room_num  = 8;
	_height_room_num = 6;
	_max_room_num    = 8;
	// 各部屋の原点を求める
	// 部屋の最大サイズ
	int max_width  = FLOOR_MAX_WIDTH / _width_room_num;         // 部屋の横幅 = フロア全体の横幅 / 1行に配置できる最大部屋数
	int max_height = FLOOR_MAX_HEIGHT / _height_room_num;		// 部屋の縦幅 = フロア全体の縦幅 / 1列に配置できる最大部屋数
	// 各部屋の原点
	std::vector< int > x_origin;
	std::vector< int > y_origin;
	// 初期化
	for ( int i = 0; i < _max_room_num; i++ ) {
		int num = 0;
		ROOM_DATA room;
		x_origin.push_back( num );
		y_origin.push_back( num );
		_room.push_back( room );
	}

	for ( int i = 0; i < _max_room_num; i++ ) {
		// 部屋の原点
		while ( true ) {
			float consttant = 1.9f;
			x_origin.at( i ) = rand( ) % 2 + max_width * ( consttant * ( i % 4 ) + 1 );      // an = 1.9n + 1;
			if ( i < _max_room_num / 2 ) {
				y_origin.at( i ) = rand( ) % 2 + max_height;
			} else{
				y_origin.at( i ) = rand( ) % 2 + max_height * 4;
			}
			
			// 内回りと被らなかったら抜ける
			if ( _tile[ x_origin.at( i ) ][ y_origin.at( i ) ].floor_surround == false ) {
				break;
			}
		}
		// 部屋の生成
		createRoom( i, max_width, max_height, x_origin.at( i ), y_origin.at( i ) );
	}
	// 通路の生成
	createAislePattern2( );
}

void Floor::createFloorPattern5( ) {
	// 部屋数の設定
	_width_room_num  = 8;
	_height_room_num = 4;
	_max_room_num    = 10;
	// 各部屋の原点を求める
	// 部屋の最大サイズ
	int max_width  = FLOOR_MAX_WIDTH / _width_room_num;         // 部屋の横幅 = フロア全体の横幅 / 1行に配置できる最大部屋数
	int max_height = FLOOR_MAX_HEIGHT / _height_room_num;		// 部屋の縦幅 = フロア全体の縦幅 / 1列に配置できる最大部屋数
	// 各部屋の原点
	std::vector< int > x_origin;
	std::vector< int > y_origin;

	// 初期化
	for ( int i = 0; i < _max_room_num; i++ ) {
		int num = 0;
		ROOM_DATA room;
		x_origin.push_back( num );
		y_origin.push_back( num );
		_room.push_back( room );
	}

	for ( int i = 0; i < _max_room_num; i++ ) {
		while ( true ) {
			// 座標　＝　乱数　＋　部屋番号によって位置を変える
			x_origin.at( i ) = rand( ) % 3 - 1 + ( max_width * ( i % 5 ) ) + ( ( i % 5 ) + 1 ) * ( max_width / 2 );
			y_origin.at( i ) = rand( ) % 3 - 1 + ( max_height * ( i % 2 ) ) + ( ( i % 2 == 0 ) ? max_width / 2 : ( max_width / 2 * 3 ) );
			// 内回りと被らなかったら抜ける
			if ( _tile[ x_origin.at( i ) ][ y_origin.at( i ) ].floor_surround == false ) {
				break;
			}
		}
		// 部屋の生成
		createRoom( i, max_width, max_height, x_origin.at( i ), y_origin.at( i ) );
	}
	// 通路の生成
	createAislePattern1( );
}

void Floor::createFloorPattern6( ) {
	// 部屋数の設定
	_width_room_num  = 10;
	_height_room_num = 7;
	_max_room_num    = 10;
	// 各部屋の原点を求める
	// 部屋の最大サイズ
	int max_width  = FLOOR_MAX_WIDTH / _width_room_num;         // 部屋の横幅 = フロア全体の横幅 / 1行に配置できる最大部屋数
	int max_height = FLOOR_MAX_HEIGHT / _height_room_num;		// 部屋の縦幅 = フロア全体の縦幅 / 1列に配置できる最大部屋数
	// 各部屋の原点
	std::vector< int > x_origin;
	std::vector< int > y_origin;
	// 初期化
	for ( int i = 0; i < _max_room_num; i++ ) {
		int num = 0;
		ROOM_DATA room;
		x_origin.push_back( num );
		y_origin.push_back( num );
		_room.push_back( room );
	}
	// 上下
	for ( int i = 0; i < 6; i++ ) {
		// 部屋の原点
		while ( true ) {
			x_origin.at( i ) = max_width * ( 2 * ( i % 3 ) + 3 ); 
			y_origin.at( i ) = max_height * ( 4 * ( i % 2 ) + 1 );
			// 内回りと被らなかったら抜ける
			if ( _tile[ x_origin.at( i ) ][ y_origin.at( i ) ].floor_surround == false ) {
				break;
			}
		}
		// 部屋の生成
		createRoom( i, max_width, max_height, x_origin.at( i ), y_origin.at( i ) );
	}
	// 左右
	for ( int i = 6; i < _max_room_num; i++ ) {
		// 部屋の原点
		while ( true ) {
			x_origin.at( i ) = max_width * ( 8 * ( i % 2 ) + 1 );      // an = 8n + 1;
			if ( i < 8 ) {
				y_origin.at( i ) = rand( ) % 3 + max_height * 2;
			} else{
				y_origin.at( i ) = rand( ) % 3 + max_height * 4;
			}
			// 内回りと被らなかったら抜ける
			if ( _tile[ x_origin.at( i ) ][ y_origin.at( i ) ].floor_surround == false ) {
				break;
			}
		}
		// 部屋の生成
		createRoom( i, max_width, max_height, x_origin.at( i ), y_origin.at( i ) );
	}
	// 通路の生成
	createAislePattern3( );
}

void Floor::createBossFloor( ) {
	FrameworkPtr fw = Framework::getInstance( );
	SoundPtr sound = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );

	_texture = CAVE;
	// 部屋数の設定
	_width_room_num  = 1;
	_height_room_num = 1;
	_max_room_num    = 1;
	ROOM_DATA room;
	_room.push_back( room );
	// 各部屋の原点を求める
	// 部屋の最大サイズ
	int max_width  = ( int )BOSS_ROOM_SIZE.x;
	int max_height = ( int )BOSS_ROOM_SIZE.y;
	// 各部屋の原点
	int x_origin = ( int )BOSS_ROOM_POS.x;
	int y_origin = ( int )BOSS_ROOM_POS.y;
	// 部屋の生成
	createBossRoom( max_width, max_height, x_origin, y_origin );
}

void Floor::createRoom( int num, int max_width, int max_height, int x_origin, int y_origin ) {
	// 各部屋のサイズ
	int width  = 0;
	int height = 0;
	
	// サイズがフロアの内周に届かないようにする
	while( 1 ) {
		width = 1 + rand( ) % max_width;
		if ( width >= 4 && width <= 8 ) {
			if ( _tile[ x_origin + width - 1 ][ y_origin ].floor_surround == false ) { 
				break;
			}
		}
	}
	while( 1 ) {
		height = 1 + rand( ) % max_height;
		if ( height >= 4 && height <= 8 ) {
			if ( _tile[ x_origin ][ y_origin + height - 1 ].floor_surround == false ) { 
				break;
			}
		}
	}
	// フロアの内周以外の該当箇所を部屋に指定
	for ( int i = x_origin; i < width + x_origin; i++ ) {
		for ( int j = y_origin; j < height + y_origin; j++ ) {
			_tile[ i ][ j ].type = ROOM;
			// 部屋番号を設定
			_tile[ i ][ j ].room = num;
		}
	}
	// 部屋の内周であることを設定
	std::vector< TILE > surround;
	// 横
	for ( int i = x_origin; i < width + x_origin; i++ ) {
		_tile[ i ][ y_origin ].room_inside_surround = true;
		surround.push_back( _tile[ i ][ y_origin ] );
		_tile[ i ][ y_origin + height - 1 ].room_inside_surround = true;
		surround.push_back( _tile[ i ][ y_origin + height - 1 ] );
	}
	// 縦
	for ( int i = y_origin + 1; i < height + y_origin - 1; i++ ) {
		_tile[ x_origin ][ i ].room_inside_surround = true;
		surround.push_back( _tile[ x_origin ][ i ] );
		_tile[ x_origin + width - 1 ][ i ].room_inside_surround = true;
		surround.push_back( _tile[ x_origin + width - 1 ][ i ] );
	}
	// 部屋のテクスチャーを決める
	// 部屋の上側
	for ( int i = x_origin; i < x_origin + width - 1; i++ ) {
		_tile[ i ][ y_origin ].texture_type = UPPER_SIDE;
	}
	// 部屋の左側
	for ( int i = y_origin + 1; i < y_origin + height; i++ ) {
		_tile[ x_origin + width - 1 ][ i ].texture_type = LEFT_SIDE;
	}
	// 部屋の左上角
	_tile[ x_origin + width - 1 ][ y_origin ].texture_type = LEFT_UPPER_CORNER;

	// 部屋の設定
	// 原点
	_room[ num ].origin = _tile[ x_origin ][ y_origin ];
	// 他の部屋とつながる最初のタイル
	_room[ num ].first_conect_point = surround.at( rand ( ) % surround.size( ) );
	// 横幅
	_room[ num ].width  = width;
	// 縦幅
	_room[ num ].height = height;
	// 幅の長いほうを取得
	if ( width < height ) {
		_room[ num ].longest = height;
	} else {
		_room[ num ].longest = width;
	}
}

void Floor::createBossRoom( int max_width, int max_height, int x_origin, int y_origin ) {
	// 各部屋のサイズ
	int width  = max_width;
	int height = max_height;

	// フロアの内周以外の該当箇所を部屋に指定
	for ( int i = x_origin; i < width + x_origin; i++ ) {
		for ( int j = y_origin; j < height + y_origin; j++ ) {
			_tile[ i ][ j ].type = ROOM;
			// 部屋番号を設定
			_tile[ i ][ j ].room = 0;
		}
	}
	// 部屋の内周であることを設定
	std::vector< TILE > surround;
	// 横
	for ( int i = x_origin; i < width + x_origin; i++ ) {
		_tile[ i ][ y_origin ].room_inside_surround = true;
		surround.push_back( _tile[ i ][ y_origin ] );
		_tile[ i ][ y_origin + height - 1 ].room_inside_surround = true;
		surround.push_back( _tile[ i ][ y_origin + height - 1 ] );
	}
	// 縦
	for ( int i = y_origin + 1; i < height + y_origin - 1; i++ ) {
		_tile[ x_origin ][ i ].room_inside_surround = true;
		surround.push_back( _tile[ x_origin ][ i ] );
		_tile[ x_origin + width - 1 ][ i ].room_inside_surround = true;
		surround.push_back( _tile[ x_origin + width - 1 ][ i ] );
	}
	// 部屋のテクスチャーを決める
	// 部屋の上側
	for ( int i = x_origin; i < x_origin + width - 1; i++ ) {
		_tile[ i ][ y_origin ].texture_type = UPPER_SIDE;
	}
	// 部屋の左側
	for ( int i = y_origin + 1; i < y_origin + height; i++ ) {
		_tile[ x_origin + width - 1 ][ i ].texture_type = LEFT_SIDE;
	}
	// 部屋の左上角
	_tile[ x_origin + width - 1 ][ y_origin ].texture_type = LEFT_UPPER_CORNER;

	// 部屋の設定
	// 原点
	_room[ 0 ].origin = _tile[ x_origin ][ y_origin ];
	// 他の部屋とつながる最初のタイル
	_room[ 0 ].first_conect_point = surround.at( rand ( ) % surround.size( ) );
	// 横幅
	_room[ 0 ].width  = width;
	// 縦幅
	_room[ 0 ].height = height;
	// 幅の長いほうを取得
	if ( width < height ) {
		_room[ 0 ].longest = height;
	} else {
		_room[ 0 ].longest = width;
	}
}

void Floor::createAislePattern1( ) {
	std::vector< bool > used_first_points;
	std::vector<TILE > first_points;
	for ( int i = 0; i < _max_room_num; i++ ) {
		TILE tile;
		used_first_points.push_back( false );
		first_points.push_back( tile );
	}

	for ( int i = 0; i < _max_room_num; i++ ) {
		int n = rand( ) % _max_room_num;
		while ( true ) {
			if ( used_first_points.at( n ) == false ) {
				first_points.at( i ) = _room.at( n ).first_conect_point;
				used_first_points.at( n ) = true;
				break;
			} else {
				n = rand( ) % _max_room_num;
			}
		}
	}

	if ( _max_room_num % 2 == 0 ) {
		for ( int i = 0; i < _max_room_num; i += 2 ) {
			tileConnect( first_points.at( i ), first_points.at( i + 1 ) );
		}
		for ( int i = 1; i < _max_room_num - 2; i += 2 ) {
			tileConnect( first_points.at( i ), first_points.at( i + 1 ) );
		}
	} else { 
		for ( int i = 0; i < _max_room_num - 1; i += 2 ) {
			tileConnect( first_points.at( i ), first_points.at( i + 1 ) );
		}
		for ( int i = 1; i < _max_room_num - 1; i += 2 ) {
			tileConnect( first_points.at( i ), first_points.at( i + 1 ) );
		}
		tileConnect( first_points.at( 0 ), first_points.at( first_points.size( ) - 1 ) );
	}
}

void Floor::createAislePattern2( ) {
	// 周りの廊下
	// 横
	for ( int i = 2; i < FLOOR_MAX_WIDTH - 2; i++ ) {
		_tile[ i ][ 2 ].type = AISLE;
		_tile[ i ][ FLOOR_MAX_HEIGHT - 3 ].type = AISLE;
	}
	// 縦
	for ( int l = 3; l < FLOOR_MAX_HEIGHT - 3; l++ ) {
		_tile[ 2 ][ l ].type = AISLE;
		_tile[ FLOOR_MAX_WIDTH - 3 ][ l ].type = AISLE;
	}
	
	int aisle_connect_num = 3 + rand( ) % 3;
	std::vector< bool > used_first_points;
	std::vector< TILE > first_points;
	// 初期化
	for ( int i = 0; i < _max_room_num; i++ ) {
		TILE tile;
		used_first_points.push_back( false );
		first_points.push_back( tile );
	}
	// 廊下と繋ぐ部屋を選出
	for ( int i = 0; i < aisle_connect_num; i++ ) {
		while ( true ) {
			int n = rand( ) % _max_room_num;
			if ( used_first_points.at( n ) == false ) {
				first_points.at( i ) = _room.at( n ).first_conect_point;
				used_first_points.at( n ) = true;
				break;
			}
		}
	}
	// 廊下と繋ぐ以外の部屋
	for ( int i = aisle_connect_num; i < _max_room_num; i++ ) {
		while ( true ) {
			int n = rand( ) % _max_room_num;
			if ( used_first_points.at( n ) == false ) {
				first_points.at( i ) = _room.at( n ).first_conect_point;
				used_first_points.at( n ) = true;
				break;
			}
		}
	}
	// 廊下と繋ぐ
	enum DIR {
		UP,
		DOWN,
		RIGHT,
		LEFT,
	};
	for ( int i = 0; i < aisle_connect_num; i++ ) {
		int dir = rand( ) % 4;
		int count = 1;
		switch( dir ) {
		case UP:
			while ( true ) {
				if ( _tile[ first_points.at( i ).x ][ first_points.at( i ).y + count ].type == AISLE ) {
					break;
				}
				count--;
			}
			tileConnect( first_points.at( i ), _tile[ first_points.at( i ).x ][ first_points.at( i ).y + count ] );
			break;
		case DOWN:
			while ( true ) {
				if ( _tile[ first_points.at( i ).x ][ first_points.at( i ).y + count ].type == AISLE ) {
					break;
				}
				count++;
			}
			tileConnect( first_points.at( i ), _tile[ first_points.at( i ).x ][ first_points.at( i ).y + count ] );
			break;
		case RIGHT:
			while ( true ) {
				if ( _tile[ first_points.at( i ).x + count ][ first_points.at( i ).y ].type == AISLE ) {
					break;
				}
				count--;
			}
			tileConnect( first_points.at( i ), _tile[ first_points.at( i ).x + count ][ first_points.at( i ).y ] );
			break;
		case LEFT:
			while ( true ) {
				if ( _tile[ first_points.at( i ).x + count ][ first_points.at( i ).y ].type == AISLE ) {
					break;
				}
				count--;
			}
			tileConnect( first_points.at( i ), _tile[ first_points.at( i ).x + count ][ first_points.at( i ).y ] );
			break;
		}
	}
	// 残りの部屋
	// 廊下とつながる部屋が過半数より少ない場合
	if ( aisle_connect_num < _max_room_num / 2 ) {
		for ( int i = 0; i < aisle_connect_num; i++ ) {
			tileConnect( first_points.at( i ), first_points.at( i + aisle_connect_num ) );
		}
		for ( int i = 0; i < aisle_connect_num; i++ ) {
			tileConnect( first_points.at( i ), first_points.at( _max_room_num - i - 1 ) );
		}
	}
	// 廊下とつながる部屋が過半数以上の場合
	else { 
		for ( int i = aisle_connect_num; i < _max_room_num; i++ ) {
			tileConnect( first_points.at( i ), first_points.at( i - aisle_connect_num ) );
		}
	}
}

void Floor::createAislePattern3( ) {
	std::vector< bool > used_first_points;
	std::vector<TILE > first_points;
	for ( int i = 0; i < _max_room_num; i++ ) {
		TILE tile;
		used_first_points.push_back( false );
		first_points.push_back( _room.at( i ).first_conect_point );
	}

	for ( int i = 0; i < _max_room_num; i += 2 ) {
		tileConnect( first_points.at( i ), first_points.at( i + 1 ) );
	}
	int num = 3 + rand( ) % 3;
	for ( int i = 0; i < num; i++ ) {
		while ( true ) {
			int n = rand( ) % _max_room_num;
			if ( used_first_points.at( n ) == false ) {
				first_points.at( i ) = _room.at( n ).first_conect_point;
				used_first_points.at( n ) = true;
				break;
			}
		}
	}
	for ( int i = num; i < _max_room_num; i++ ) {
		while ( true ) {
			int n = rand( ) % _max_room_num;
			if ( used_first_points.at( n ) == false ) {
				first_points.at( i ) = _room.at( n ).first_conect_point;
				used_first_points.at( n ) = true;
				break;
			}
		}
	}

	for ( int i = 0; i < num; i++ ) {
		if ( num <= _max_room_num / 2 ) {
			tileConnect( first_points.at( i ), first_points.at( i + num ) );
		} else {
			int num2 = rand( ) % _max_room_num;
			tileConnect( first_points.at( i ), first_points.at( num2 ) );
		}
	}
}

void Floor::tileConnect( TILE tile_A, TILE tile_B ) {
	int x  = tile_A.x;
	int x2 = tile_B.x;
	int y  = tile_A.y;
	int y2 = tile_B.y;
	// x軸が同じ場合
	if ( x == x2 ) {
		// タイルAのｙが小さい場合
		if ( y < y2 ) {
			for ( int i = y; i < y2; i++ ) {
				tileConnectDisplaceX( x, i, 1 );
			}
		}
		// タイルAのｙが小さい場合
		else if ( y > y2 ) { 
			for ( int i = y2; i < y; i++ ) {
				tileConnectDisplaceX( x, i , 1);
			}
		} else {
			return;
		}
	}
	// タイルAのxが小さい場合
	else if ( x < x2 ) {
		for ( int i = x; i < x2; i++ ) {
			tileConnectDisplaceY( i, y, 1 );
		}
		// タイルAのｙが小さい場合
		if ( y < y2 ) {
			for ( int i = y2; i > y; i-- ) {
				tileConnectDisplaceX( x2, i, -1 );
			}
		} 
		// タイルAのｙが大きい場合
		else if ( y > y2 ) { 
			for ( int i = y2; i < y; i++ ) {
				tileConnectDisplaceX( x2, i, 1 );
			}
		} else {
			return;
		}
	}
	// タイルAのxが大きい場合
	else if ( x > x2 ) {
		for ( int i = x; i > x2; i-- ) {
			tileConnectDisplaceY( i, y, -1 );
		}
		// タイルAのｙが小さい場合
		if ( y < y2 ) {
			for ( int i = y2; i > y; i-- ) {
				tileConnectDisplaceX( x2, i, -1 );
			}
		}
		// タイルAのｙが大きい場合
		else if ( y > y2 ) { 
			for ( int i = y2; i < y; i++ ) {
				tileConnectDisplaceX( x2, i, 1 );
			}
		} else {
			return;
		}
	}
}

void Floor::tileConnectDisplaceX( int x, int i, int dir ) {
	// となりに廊下がある場合はずらす
	if ( _tile[ x ][ i + dir ].type == WALL ) {
		// 一歩先と今のタイルの左右が壁でなかったら
		if ( ( _tile[ x - 1 ][ i + dir ].type != WALL &&
			 _tile[ x - 1 ][ i ].type != WALL ) ||
			 ( _tile[ x + 1 ][ i + dir ].type != WALL &&
				  _tile[ x + 1 ][ i ].type != WALL ) ) {
			return;
		}
		// 一歩先のタイルの右側が壁で今のタイルの右側が壁でなかったら
		else if ( _tile[ x - 1 ][ i + dir ].type == WALL &&
				  _tile[ x - 1 ][ i ].type != WALL ) {
			_tile[ x ][ i ].type = AISLE;
			_tile[ x ][ i + dir ].type = AISLE;
		}
		// 一歩先のタイルの左側が壁で今のタイルの左側が壁でなかったら
		else if ( _tile[ x + 1 ][ i + dir ].type == WALL &&
				  _tile[ x + 1 ][ i ].type != WALL ) {
			_tile[ x ][ i ].type = AISLE;
			_tile[ x ][ i + dir ].type = AISLE;
		}
		// 通常時
		else {
			_tile[ x ][ i + dir ].type = AISLE;
		}
	}
}

void Floor::tileConnectDisplaceY( int i, int y, int dir ) {
	// となりに廊下がある場合はずらす
	if (  _tile[ i + dir ][ y ].type == WALL ){
		// 一歩先と今のタイルの上下が壁でなかったら
		if ( ( _tile[ i + dir ][ y - 1 ].type != WALL &&
			 _tile[ i ][ y - 1 ].type != WALL ) ||
			 ( _tile[ i + dir ][ y + 1 ].type != WALL &&
				  _tile[ i ][ y + 1 ].type != WALL ) ) {
			return;
		}
		// 一歩先のタイルの上側が壁で今のタイルの上側が壁でなかったら
		else if ( _tile[ i + dir ][ y - 1 ].type == WALL &&
				  _tile[ i ][ y - 1 ].type != WALL ) {
			_tile[ i ][ y ].type = AISLE;
			_tile[ i + dir ][ y ].type = AISLE;
		}
		// 一歩先のタイルの下側が壁で今のタイルの下側が壁でなかったら
		else if ( _tile[ i + dir ][ y + 1 ].type == WALL &&
				  _tile[ i ][ y + 1 ].type != WALL ) {
			_tile[ i ][ y ].type = AISLE;
			_tile[ i + dir ][ y ].type = AISLE;
		}
		// 通常時
		else {
			_tile[ i + dir ][ y ].type = AISLE;
		}
	}
}

void Floor::createStair( ) {
	// どこかの部屋のタイルに生成
	TILE stair_tile;
	while ( true ) {
		stair_tile = getRandomFloor( );
		if ( isNotNearByAisle( stair_tile ) == true ) {
			break;
		}
	}
	_stair_tile = stair_tile;
	setStairExist( stair_tile );
	Vector2 pos;
	pos.x = stair_tile.x;
	pos.y = stair_tile.y;
	_network->setSendChipData( NetworkApp::MAP_CHIP_TYPE::STAIR, pos, 0, false );
}

void Floor::setStairExist( TILE stair_tile ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	_tile[ stair_tile.x ][ stair_tile.y ].stair_exist = true;
	// モデルの設定
	viewer->modelSetScale( _stair_model, STAIR_SCALE, STAIR_SCALE, STAIR_SCALE );
	viewer->modelSetRotation( _stair_model, 0.0f, STAIR_ROTATE_Y, 0.0f );
	viewer->modelSetPos( _stair_model, stair_tile.pos );
}

void Floor::dicisionMysteryTileForFloor( ) {
	
	std::vector< MYSTERY_TILE > dicision_type;
	switch( _floor_level ) {
	case 1:
		_create_mystery_tile_num = 0;
		break;
	case 2:
		_create_mystery_tile_num = 2 + rand ( ) % 2;
		dicision_type.push_back( ALCHEMY_POINT );
		dicision_type.push_back( DAMGE_TRAP );
		dicision_type.push_back( POISON_TRAP );
		dicision_type.push_back( CONFUSE_TRAP );
		dicision_type.push_back( WARP_TRAP );
		dicision_type.push_back( SLOW_TRAP );
		dicision_type.push_back( RETURN_TRAP );
		break;
	case 3:
		_create_mystery_tile_num = 5 + rand ( ) % 2;
		dicision_type.push_back( DAMGE_TRAP );
		dicision_type.push_back( POISON_TRAP );
		dicision_type.push_back( PARALYSIS_TRAP );
		dicision_type.push_back( SKILL_SEAL_TRAP );
		dicision_type.push_back( SLOW_TRAP );
		dicision_type.push_back( WARP_TRAP );
		break;
	case 4:
		_create_mystery_tile_num = 8 + rand ( ) % 2;
		dicision_type.push_back( ALCHEMY_POINT );
		dicision_type.push_back( DAMGE_TRAP );
		dicision_type.push_back( POISON_TRAP );
		dicision_type.push_back( PARALYSIS_TRAP );
		dicision_type.push_back( CONFUSE_TRAP );
		dicision_type.push_back( WARP_TRAP );
		dicision_type.push_back( RETURN_TRAP );
		dicision_type.push_back( SLOW_TRAP );
		break;
	}

	
	for ( int i = 0; i < _create_mystery_tile_num; i++ ) {
		int num = rand( ) % dicision_type.size( );
		MYSTERY_TILE type = dicision_type.at( num );
		//MYSTERY_TILE type = RETURN_TRAP;
		// 不思議な床の生成
		createMysteryTile( type );
	}
	

	
	//////////// デバッグ用 ////////////////////////
	/*
	MYSTERY_TILE type = POISON_TRAP;
	// 不思議な床の生成
	createMysteryTile( type );
	*/
}

void Floor::createMysteryTile( Floor::MYSTERY_TILE type ) {
	
	
	// どこかの部屋のタイルに生成
	TILE mystery_tile;
	while ( true ) {
		mystery_tile = getRandomFloor( );
		if ( mystery_tile.stair_exist == false && isNotNearByAisle( mystery_tile ) == true ) {
			break;
		}
	}
	mystery_tile.myistery_type = type;
	setMysteryTile( mystery_tile );
	_mystery_tile.push_back( _tile[ mystery_tile.x ][ mystery_tile.y ] );
	
	
	/////////////////////////// デバッグ用 ////////////////////////////////////////
	/*
	TILE stair_tile;
	for ( int i = 0; i < FLOOR_MAX_WIDTH; i++ ) {
		for ( int j = 0; j < FLOOR_MAX_HEIGHT; j++ ) {
			if ( _tile[ i ][ j ].stair_exist == true ) {
				stair_tile = _tile[ i ][ j ];
			}
		}
	}

	for ( int i = -1; i <= 1; i += 2 ) {
		for ( int j = -1; j <= 1; j += 2 ) {
			TILE mystery_tile = _tile[ stair_tile.x + i ][ stair_tile.y + j ];
			mystery_tile.myistery_type = type;
			setMysteryTile( mystery_tile );
			_mystery_tile.push_back( _tile[ mystery_tile.x ][ mystery_tile.y ] );
		}
	}
	*/
	
}

void Floor::setMysteryTile( TILE mystery_tile ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	_tile[ mystery_tile.x ][ mystery_tile.y ].myistery_type = mystery_tile.myistery_type;
	
	switch ( mystery_tile.myistery_type ) {
	case POISON_TRAP:
		_tile[ mystery_tile.x ][ mystery_tile.y ].mystery_tile_model = viewer->duplicateModel( _poison_trap_model );
		break;
	case PARALYSIS_TRAP:
		_tile[ mystery_tile.x ][ mystery_tile.y ].mystery_tile_model = viewer->duplicateModel( _paralysis_trap_model );
		break;
	case SKILL_SEAL_TRAP:
		_tile[ mystery_tile.x ][ mystery_tile.y ].mystery_tile_model = viewer->duplicateModel( _skill_seal_trap_model );
		break;
	case SLOW_TRAP:
		_tile[ mystery_tile.x ][ mystery_tile.y ].mystery_tile_model = viewer->duplicateModel( _slow_trap_model );
		break;
	case CONFUSE_TRAP:
		_tile[ mystery_tile.x ][ mystery_tile.y ].mystery_tile_model = viewer->duplicateModel( _confuse_trap_model );
		break;
	case WARP_TRAP:
		_tile[ mystery_tile.x ][ mystery_tile.y ].mystery_tile_model = viewer->duplicateModel( _warp_trap_model );
		break;
	case RETURN_TRAP:
		_tile[ mystery_tile.x ][ mystery_tile.y ].mystery_tile_model = viewer->duplicateModel( _pit_trap_model );
		break;
	case DAMGE_TRAP:
		_tile[ mystery_tile.x ][ mystery_tile.y ].mystery_tile_model = viewer->duplicateModel( _damage_trap_model );
		break;
	case ALCHEMY_POINT:
		_tile[ mystery_tile.x ][ mystery_tile.y ].mystery_tile_model = viewer->duplicateModel( _alchemy_point_tile_model );
		_tile[ mystery_tile.x ][ mystery_tile.y ].seen_mystery = true;
		_network->setSendChipData( NetworkApp::MAP_CHIP_TYPE::MYSTERY, Vector2( mystery_tile.x, mystery_tile.y ), 0, false );
		break;
	}
	// モデルの設定
	viewer->modelSetScale( _tile[ mystery_tile.x ][ mystery_tile.y ].mystery_tile_model, STAIR_SCALE * 30, STAIR_SCALE * 30, STAIR_SCALE * 30 );
	viewer->modelSetRotation( _tile[ mystery_tile.x ][ mystery_tile.y ].mystery_tile_model, 0.0f, STAIR_ROTATE_Y, 0.0f );
	viewer->modelSetPos( _tile[ mystery_tile.x ][ mystery_tile.y ].mystery_tile_model, _tile[ mystery_tile.x ][ mystery_tile.y ].pos + Vector( - TILE_SIZE / 2 + 1.4, 0, TILE_SIZE / 2 ) );
}

void Floor::update( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	// 背景の描画
	viewer->drawGraph( 0, 0, _background );
	drawFloor( );
	if ( _network->getCtrlPhase( ) == NetworkApp::CTRL_PHASE::NAVI_PHASE ) {
		naviLine( );
	}
}

void Floor::drawFloor( ) const {
	switch ( _texture ) {
	case WATER:
		drawWaterFloor( );
		break;
	case JUNGLE:
		drawJungleFloor( );
		break;
	case CAVE:
		drawCaveFloor( );
		break;
	}
}

void Floor::drawWaterFloor( ) const {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	for ( int i = 0; i < FLOOR_MAX_WIDTH; i++ ) {
		for ( int j = 0; j < FLOOR_MAX_HEIGHT; j++ ) {
			switch ( _tile[ i ][ j ].type ) {
				// 壁
				case WALL:
					viewer->drawPolygonWall( _tile[ i ][ j ].pos, _water.ceiling_image, _water.wall_image );
					break;
				// 部屋
				case ROOM:
					if ( _tile[ i ][ j ].texture_type == ELSE ) {
						viewer->drawPolygonFloor( _tile[ i ][ j ].pos, _water.floor_image );
					}
					if ( _tile[ i ][ j ].texture_type == UPPER_SIDE ) {
						viewer->drawPolygonFloor( _tile[ i ][ j ].pos, _water.upper_side_image );
					}
					if ( _tile[ i ][ j ].texture_type == LEFT_SIDE ) {
						viewer->drawPolygonFloor( _tile[ i ][ j ].pos, _water.left_side_image );
					}
					if ( _tile[ i ][ j ].texture_type == LEFT_UPPER_CORNER ) {
						viewer->drawPolygonFloor( _tile[ i ][ j ].pos, _water.left_upper_corner_image );
					}
					break;
				// 廊下
				case AISLE:
					if ( _tile[ i ][ j ].aisle_vertical == true ) {
						viewer->drawPolygonFloor( _tile[ i ][ j ].pos, _water.left_side_image );
					} else {
						viewer->drawPolygonFloor( _tile[ i ][ j ].pos, _water.floor_image );
					}
					break;
			}
			// 階段
			if ( _tile[ i ][ j ].stair_exist == true ) {
				viewer->drawModel( _stair_model );
			}
			// 罠
			if ( _tile[ i ][ j ].mystery_tile_model != 0 && _tile[ i ][ j ].seen_mystery == true ) {
				viewer->drawModel( _tile[ i ][ j ].mystery_tile_model );
			}
		}
	}
}

void Floor::drawJungleFloor( ) const {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	for ( int i = 0; i < FLOOR_MAX_WIDTH; i++ ) {
		for ( int j = 0; j < FLOOR_MAX_HEIGHT; j++ ) {
			switch ( _tile[ i ][ j ].type ) {
				// 壁
				case WALL:
					viewer->drawPolygonWall( _tile[ i ][ j ].pos, _jungle.ceiling_image, _jungle.wall_image );
					break;
				// 部屋
				case ROOM:
					if ( _tile[ i ][ j ].texture_type == ELSE ) {
						viewer->drawPolygonFloor( _tile[ i ][ j ].pos, _jungle.floor_image );
					}
					if ( _tile[ i ][ j ].texture_type == UPPER_SIDE ) {
						viewer->drawPolygonFloor( _tile[ i ][ j ].pos, _jungle.upper_side_image );
					}
					if ( _tile[ i ][ j ].texture_type == LEFT_SIDE ) {
						viewer->drawPolygonFloor( _tile[ i ][ j ].pos, _jungle.left_side_image );
					}
					if ( _tile[ i ][ j ].texture_type == LEFT_UPPER_CORNER ) {
						viewer->drawPolygonFloor( _tile[ i ][ j ].pos, _jungle.left_upper_corner_image );
					}
					break;
				// 廊下
				case AISLE:
					if ( _tile[ i ][ j ].aisle_vertical == true ) {
						viewer->drawPolygonFloor( _tile[ i ][ j ].pos, _jungle.left_side_image );
					} else {
						viewer->drawPolygonFloor( _tile[ i ][ j ].pos, _jungle.floor_image );
					}
					break;
			}
			// 階段
			if ( _tile[ i ][ j ].stair_exist == true ) {
				viewer->drawModel( _stair_model );
			}
			// 罠
			if ( _tile[ i ][ j ].mystery_tile_model != 0 && _tile[ i ][ j ].seen_mystery == true ) {
				viewer->drawModel( _tile[ i ][ j ].mystery_tile_model );
			}
		}
	}
}

void Floor::drawCaveFloor( ) const {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	for ( int i = 0; i < FLOOR_MAX_WIDTH; i++ ) {
		for ( int j = 0; j < FLOOR_MAX_HEIGHT; j++ ) {
			switch ( _tile[ i ][ j ].type ) {
				// 壁
				case WALL:
					viewer->drawPolygonWall( _tile[ i ][ j ].pos, _cave.ceiling_image, _cave.wall_image );
					break;
				// 部屋
				case ROOM:
					if ( _tile[ i ][ j ].texture_type == ELSE ) {
						viewer->drawPolygonFloor( _tile[ i ][ j ].pos, _cave.floor_image );
					}
					if ( _tile[ i ][ j ].texture_type == UPPER_SIDE ) {
						viewer->drawPolygonFloor( _tile[ i ][ j ].pos, _cave.upper_side_image );
					}
					if ( _tile[ i ][ j ].texture_type == LEFT_SIDE ) {
						viewer->drawPolygonFloor( _tile[ i ][ j ].pos, _cave.left_side_image );
					}
					if ( _tile[ i ][ j ].texture_type == LEFT_UPPER_CORNER ) {
						viewer->drawPolygonFloor( _tile[ i ][ j ].pos, _cave.left_upper_corner_image );
					}
					break;
				// 廊下
				case AISLE:
					if ( _tile[ i ][ j ].aisle_vertical == true ) {
						viewer->drawPolygonFloor( _tile[ i ][ j ].pos, _cave.left_side_image );
					} else {
						viewer->drawPolygonFloor( _tile[ i ][ j ].pos, _cave.floor_image );
					}
					break;
			}
			// 階段
			if ( _tile[ i ][ j ].stair_exist == true ) {
				viewer->drawModel( _stair_model );
			}
			// 罠
			if ( _tile[ i ][ j ].mystery_tile_model != 0 && _tile[ i ][ j ].seen_mystery == true ) {
				viewer->drawModel( _tile[ i ][ j ].mystery_tile_model );
			}
		}
	}
}

void Floor::naviLine( ) const {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	
	int x = 0;
	int z = 0;
	for ( int i = 0; i < FLOOR_MAX_WIDTH + 1; i++ ) {
		Vector pos = Vector( x, 0, 0 );
		x += TILE_SIZE;
		viewer->line( pos, Vector( pos.x, pos.y, FLOOR_MAX_HEIGHT * TILE_SIZE ), 255, 255, 255 );
	}

	for ( int i = 0; i < FLOOR_MAX_HEIGHT + 1; i++ ) {
		
		Vector pos = Vector( 0, 0, z );
		z += TILE_SIZE;
		viewer->line( pos, Vector( FLOOR_MAX_WIDTH * TILE_SIZE, pos.y, pos.z ), 255, 255, 255 );
	}
	
}

Floor::TILE Floor::getTile( int x, int y ) const {
	if ( x > 0 && x < FLOOR_MAX_WIDTH &&
		 y > 0 && y < FLOOR_MAX_HEIGHT ) {
		return _tile[ x ][ y ];
	}
	return _tile[ 0 ][ 0 ];
}

Floor::TILE Floor::getPlayerTile( ) const {
	return _player_tile;
}

Floor::TILE Floor::getStairTile( ) const {
	return _stair_tile;
}

Floor::ROOM_DATA Floor::getRoom( int room_num ) {
	return _room[ room_num ];
}

Floor::TILE Floor::getRandomFloor( ) const {
	TILE tile;
	while( true ) {
		// ランダムに部屋を取得
		int num = rand( ) % _max_room_num;
		// 部屋内のランダムなタイルを返す
		int width  = rand( ) % _room[ num ].width;
		int height = rand( ) % _room[ num ].height;
		if ( _tile[ width + _room[ num ].origin.x ][ height + _room[ num ].origin.y ].type != WALL ) {
			tile = _tile[ width + _room[ num ].origin.x ][ height + _room[ num ].origin.y ];
			break;
		}
	}
	return tile;
}

Floor::TILE Floor::getRandomStairFloor( ) const {
	TILE tile;
	while( true ) {
		// ランダムに部屋を取得
		int num = _stair_tile.room;
		// 部屋内のランダムなタイルを返す
		int width  = rand( ) % _room[ num ].width;
		int height = rand( ) % _room[ num ].height;
		if ( _tile[ width + _room[ num ].origin.x ][ height + _room[ num ].origin.y ].type != WALL ) {
			tile = _tile[ width + _room[ num ].origin.x ][ height + _room[ num ].origin.y ];
			break;
		}
	}
	return tile;
}

Floor::TILE Floor::getBossRoomCharacterPos( Floor::BOSS_ROOM_CHARACTER character ) {
	int x;
	int y;
	switch ( character ) {
	case BOSS_ROOM_PLAYER:
		x = ( int )( BOSS_ROOM_POS.x + BOSS_ROOM_SIZE.x / 2 - 1 );
		y = ( int )( BOSS_ROOM_POS.y + BOSS_ROOM_SIZE.y / 2 + 1 );
		break;
	case BOSS_ROOM_BOSS:
		x = ( int )( BOSS_ROOM_POS.x + BOSS_ROOM_SIZE.x / 2 - 1 );
		y = ( int )( BOSS_ROOM_POS.y + BOSS_ROOM_SIZE.y / 2 - 2 );
		break;
	}
	return _tile[ x ][ y ];
}

void Floor::setBondNone( int x, int y ) {
	_tile[ x ][ y ].bond = NONE;
}

void Floor::setBondPlayer( int x, int y ) {
	// プレイヤーのいるタイルを登録
	_tile[ x ][ y ].bond = PLAYER;
	_player_tile         = _tile[ x ][ y ];
}

void Floor::setBondEnemy( int x, int y ) {
	_tile[ x ][ y ].bond = ENEMY;
}

void Floor::setItemExist( int x, int y, bool exist ) {
	_tile[ x ][ y ].item_exist = exist;
}

void Floor::setStairExist( int x, int y ) {
	_tile[ x ][ y ].stair_exist = true;
}

void Floor::onStair( ) {
	_network->setSendFoot( NetworkApp::FOOT_THING::FOOT_STAIR, true );
}

void Floor::setFloorLelel( int floor_level ) {
	_floor_level = floor_level;
}

void Floor::visibleTrap( int x, int y ) {
	if ( _tile[ x ][ y ].seen_mystery == false ) {
		_tile[ x ][ y ].seen_mystery = true;
		for ( int i = 0; i < _mystery_tile.size( ); i++ ) {
			if ( _mystery_tile.at( i ).x == x && _mystery_tile.at( i ).y == y ) {
				_mystery_tile.at( i ).seen_mystery = true;
			}
		}
	}
}

void Floor::breakMysteryTile( int x, int y ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	_tile[ x ][ y ].myistery_type = NONE_MISTERY;
	viewer->deleatModel( _tile[ x ][ y ].mystery_tile_model );
	for ( int i = 0; i < _mystery_tile.size( ); i++ ) {
		if ( _mystery_tile.at( i ).x == x && _mystery_tile.at( i ).y == y ) {
			_mystery_tile.erase( _mystery_tile.begin( ) + i );
		}
	}
}

void Floor::allBreakMysteryTile( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	for ( int i = 0; i < FLOOR_MAX_WIDTH; i++ ) {
		for ( int j = 0; j < FLOOR_MAX_HEIGHT; j++ ) {
			if ( _tile[ i ][ j ].myistery_type != NONE_MISTERY ) {
				_tile[ i ][ j ].myistery_type = NONE_MISTERY;
				viewer->deleatModel( _tile[ i ][ j ].mystery_tile_model );
			}
		}
	}
	_mystery_tile.erase( _mystery_tile.begin( ), _mystery_tile.end( ) );
}

void Floor::sendNetworkMysteryPos( ) {
	for ( int i = 0; i < _mystery_tile.size( ); i++ ) {
		if ( _mystery_tile.at( i ).seen_mystery == true ) {
			_network->setSendChipData( NetworkApp::MAP_CHIP_TYPE::MYSTERY, Vector2( _mystery_tile.at( i ).x, _mystery_tile.at( i ).y ), 0, false );
		}
	}
	if ( _mystery_tile.size( ) <= 0 ) {
		_network->setSendChipData( NetworkApp::MAP_CHIP_TYPE::MYSTERY, Vector2( 0, 0 ), 0, true );
	}
}

Floor::TILE Floor::getFirstConectPoint( ) {
	int target_room_num = rand( ) % _max_room_num;
	TILE targetPos      = _room[ target_room_num ].first_conect_point;
	return targetPos;
}

bool Floor::isNotNearByAisle( TILE tile ) {
	if ( _tile[ tile.x + 1 ][ tile.y ].type != AISLE &&
		 _tile[ tile.x - 1 ][ tile.y ].type != AISLE &&
		 _tile[ tile.x ][ tile.y + 1 ].type != AISLE &&
		 _tile[ tile.x ][ tile.y - 1 ].type != AISLE ) {
		return true;
	}
	return false;
}

Floor::TILE_TEXTURE_TYPE Floor::getTextureType( ) {
	return _texture;
}
