#include "Alchemy.h"
#include "Viewer.h"
#include "Touch.h"
#include "Camera.h"
#include "NetworkController.h"
#include "ItemImage.h"
#include "Sound.h"

Alchemy::Alchemy( Vector2 pos, ItemPtr item, NetworkControllerPtr network, CameraPtr camera, ItemImagePtr item_image ) : Icon( pos ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	_item = item;
	_network = network;
	_camera = camera;
	_item_image = item_image;
	_point = 0;
	_item_list = _item->getItemList( );
	_foot_item = _item->getFootItem( );
	_foot_open = false;
	_image = viewer->loadGraph( "work/ctrl_UI/alchemy.png" );
	_alchemy_window = viewer->loadGraph( "work/ctrl_UI/window/window_alchemy.png" );
	_message_window = viewer->loadGraph( "work/ctrl_UI/window/window_message.png" );
	_plus = viewer->loadGraph( "work/ctrl_UI/alchemy/plus.png" );
	_item_set_flag = true;
	_drag = false;
	_remove_area_1 = true;
	_remove_area_2 = true;
	_separate = true;
	_item_drag_num = 0;
	_pot = viewer->loadModel( "work/ctrl_UI/Alchemy/model/pot.mv1" );
	_wait_count = 0;
	_confirmation_window = viewer->loadGraph( "work/ctrl_UI/window/window_message.png" );
	_camera_check = false;
	_create_item = ITEM_ID::ITEM_NONE;
	_anim_flag = false;
	_move_flag = false;
	_start_flag = false;
	_randam_alchemy = false;
	viewer->modelSetPos( _pot, Vector( -4.9, 0, -10 ) );
	viewer->attachAnim( _pot, 0, -1 );
	_pot_anim_total_time = viewer->animTotalTime( _pot, 0 );
	_performance_finish = false;
	_point_window_rank1 = viewer->loadGraph( "work/ctrl_UI/window/point_window_rank1.png" );
	_point_window_close_rank1 = viewer->loadGraph( "work/ctrl_UI/window/point_window_rank1_close.png" );
	_point_window_rank2 = viewer->loadGraph( "work/ctrl_UI/window/point_window_rank2.png" );
	_point_window_close_rank2 = viewer->loadGraph( "work/ctrl_UI/window/point_window_rank2_close.png" );
	_point_window_rank3 = viewer->loadGraph( "work/ctrl_UI/window/point_window_rank3.png" );
	_point_window_close_rank3 = viewer->loadGraph( "work/ctrl_UI/window/point_window_rank3_close.png" );
	
	// デバッグ用
	/*_chosen_item_1.item = _item->getItemStatus( STONE4 );
	_chosen_item_2.item = _item->getItemStatus( STONE4 );*/

}

Alchemy::~Alchemy( ) {

}

void Alchemy::init( ) {
	_point = 0;	// 錬金ポイントを初期化
	close( );
}

void Alchemy::touch( ) {

	FrameworkPtr fw = Framework::getInstance( );
	TouchPtr touch = std::dynamic_pointer_cast< Touch >( fw->getTask( typeid( Touch ).name( ) ) );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	drawAlchemy( );	
	if ( _item_set_flag == true ) {
		setAlchemyItem( );
		
	}
	if ( _start_flag == false ) {
		// アイテムをドラッグしてないときのみスクロールをできるように
		if ( _drag == false ) {
			itemScroll( );
		}
		
		itemSelect( );
		drawItem( );
		// 錬金素材が2つとも選ばれていた時の処理
		if ( _camera_check == true ) {
			if ( _camera->getFinishAlchemy( ) == true ) {
				potAlchemyAnim( );
			} else if ( _performance_finish == true ) {
				createItemObtain( );
			}
		} else if ( _chosen_item_1.item.type.id != ITEM_NONE && _chosen_item_2.item.type.id != ITEM_NONE ) {
			if ( _randam_alchemy == false ) {
				if ( isRecipe( ) == false ) {
					_randam_alchemy = true;
					_separate = false;	// ポイント選択タッチミス防止
				}
			}
			if ( _randam_alchemy == true ) {
				selectAlchemyPoint( );
			}
			//createItem( );
			//_item_set_flag = true;
		}

		if ( _result_flag == true ) {
			result( );
		}
	} else {
		startAnim( );
	}

	
	if ( touch->isSeparate( ) == true ) {
		_separate = true;
	}

}

void Alchemy::startAnim( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	SoundPtr sound = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );
	
	// 開く音
	if ( _anim_count == 1 ) {
		sound->playSound( Sound::SOUND_TYPE::POT_OPEN );
	}

	if ( _anim_count < ANIM_INIT_TIME ) {
		_anim_count += ANIM_SPEED;
		viewer->setAttachAnimTime( _pot, 0, _anim_count );
		_move_flag = true;
	} else if ( _anim_count >= ANIM_INIT_TIME && _move_flag == true ) {
		_anim_flag = true;
		_move_flag = false;
	}

	if ( _anim_flag == true ) {
		_camera->setCameraMode( Camera::MODE::RETURN );
		_anim_flag = false;
	}
	if ( _camera->getFinishAlchemy( ) == true ) {
		_start_flag = false;
		_camera->setFinishAlchemy( false );	// カメラのほうを初期化しておく
	}
}

void Alchemy::createItemObtain( ) {
	FrameworkPtr fw = Framework::getInstance( );
	SoundPtr sound = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );

	if ( _foot_open == true ) {
		if ( _chosen_item_1.foot == true ) {
		_item->footItemAlchemy(_chosen_item_2.num, _create_item );
		_chosen_item_1 = CHOSEN_ITEM( );
		_chosen_item_2 = CHOSEN_ITEM( );
		_foot_open = false;

		} else if ( _chosen_item_2.foot == true ) {
		_item->footItemAlchemy( _chosen_item_1.num, _create_item );
		_chosen_item_1 = CHOSEN_ITEM( );
		_chosen_item_2 = CHOSEN_ITEM( );
		_foot_open = false;

		}
	} else if ( _create_item != ITEM_NONE ) {
		_item->alchemy( _chosen_item_1.num, _chosen_item_2.num, _create_item );
		_chosen_item_1 = CHOSEN_ITEM( );
		_chosen_item_2 = CHOSEN_ITEM( );
	}
	// 諸々を初期化

	_item_set_flag = true;
	_result_flag = true;
	_camera_check = false;
	_performance_finish = false;

	// 錬金成功音声再生
	sound->playSound( Sound::SOUND_TYPE::ALCHEMY_SUCCESS );
}

void Alchemy::drawAlchemy( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	// 壺の描画
	viewer->drawModel( _pot );

	// 錬金ポイントの描画
	viewer->drawGraph( POINT_POS_X, POINT_POS_Y, _alchemy_window );
	std::string str = "錬金ポイント : %d";
	Vector2 str_pos = Vector2 ( POINT_POS_X + STRING_DIS, POINT_POS_Y + STRING_DIS );
	drawString( Vector2( str_pos.x, str_pos.y ), str, _point );	// 錬金ポイント

	// UIの描画
	/*viewer->drawGraph( ALCHEMY_POS_X, ALCHEMY_POS_Y,_alchemy_window );
	viewer->drawGraph( ALCHEMY_POS_X + WINDOW_DIS, ALCHEMY_POS_Y, _alchemy_window );
	viewer->drawGraph( ALCHEMY_POS_X + ALCHEMY_WIDTH, ALCHEMY_POS_Y, _plus );*/

}
void Alchemy::drawItem( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	// アイテムの描画
	for ( int i = 0; i < MAX_ITEM_NUM; i++ ) {
		// 選択中のアイテムは描画しないようにする
		if ( i == _chosen_item_1.num || i == _chosen_item_2.num ) {
			viewer->drawGraph( ( int )_alchemy_item [ i ].pos.x, ( int )_alchemy_item [ i ].pos.y, _item_image->getBigFrame( ) );

		// ドラッグ中のアイテムは一番前に出せるようにするため描画しない
		} else if ( _drag == true && i == _item_drag_num ) {
			viewer->drawGraph( ( int )_alchemy_item [ i ].pos.x, ( int )_alchemy_item [ i ].pos.y, _item_image->getBigFrame( ) );
		
		} else {
			// アイテム画像の描画
			viewer->drawGraph( ( int )_alchemy_item [ i ].pos.x, ( int )_alchemy_item [ i ].pos.y, _alchemy_item [ i ].image );
			
			// 装備中アイテム
			if (_alchemy_item[ i ].item.equipment == true ) {
				viewer->drawGraph( ( int )_alchemy_item [ i ].pos.x, ( int )_alchemy_item [ i ].pos.y, _item_image->getBigFrameEquipment( ) );
			}	

			// 使用回数の表示
			if ( _alchemy_item[ i ].item.category == Item::CATEGORY::ROD ) {
				viewer->drawGraph( ( int )_alchemy_item [ i ].pos.x, ( int )_alchemy_item [ i ].pos.y, _item_image->getBigFrameAmount( _alchemy_item[ i ].item.type.amount - 1 ) );
			}
		}
	}
	// ドラッグ中のアイテムを描画する
	if ( _drag == true ) {
		viewer->drawGraph( _drag_item.pos.x, _drag_item.pos.y, _drag_item.image );
	}

	// 選択したアイテムを描画する処理
	// 選択されていないときはフレームを表示
	if ( _chosen_item_1.image != 0 ) {
		viewer->drawGraph( CHOICE_AREA_1.x, CHOICE_AREA_1.y, _chosen_item_1.image );
	} else {
		viewer->drawGraph( CHOICE_AREA_1.x, CHOICE_AREA_1.y,  _item_image->getBigFrame( ) );
	}

	if ( _chosen_item_2.image != 0 ) {
		viewer->drawGraph( CHOICE_AREA_2.x, CHOICE_AREA_2.y, _chosen_item_2.image );
	} else {
		viewer->drawGraph( CHOICE_AREA_2.x, CHOICE_AREA_2.y,  _item_image->getBigFrame( ) );
	}
}
void Alchemy::setAlchemyPoint( ) {
	// 錬金ポイント取得処理
	int alchemy_point =_network->getAlchemyPoint( );	// 取得する錬金ポイント

	// 創造の指輪を装備していれば錬金ポイントを倍にする
	if ( _item->isCreateRingEquipment( ) == true ) {
		_point += alchemy_point * 2;
	} else {
		_point += alchemy_point;
	}

	_network->resetAlchemyPoint( );
}

void Alchemy::close( ) {
	_item_set_flag = true;
	_item_drag_num = 0;
	_result_flag = false;
	_drag = false;
	_randam_alchemy = false;
	_anim_count = 0;
	_anim_flag = 0;
	_move_flag = 0;
	_chosen_item_1 = CHOSEN_ITEM( );
	_chosen_item_2 = CHOSEN_ITEM( );
	_camera->cameraReset( );
}

// 錬金画面用のアイテムの一覧を用意する
void Alchemy::setAlchemyItem( ) {
	// アイテムからリストの中身をもらう
	_item_list = _item->getItemList( );
	_foot_item = _item->getFootItem( );

	for ( int i = 0; i < MAX_ITEM_NUM; i++ ) {
		ALCHEMY_ITEM alchemy_item;
		if ( i < _item_list.size( ) ) {
			alchemy_item.item = _item_list.at( i );

			// 画像の設定
			alchemy_item.image = _item_image->getBigFrameImage( _item_list.at( i ).type.id );

			alchemy_item.pos = Vector2 ( i * ITEM_DIS, 700 );
		
			_alchemy_item[ i ] = alchemy_item;

		} else {	
			alchemy_item.image =  _item_image->getBigFrame( );
			alchemy_item.pos = Vector2 ( i * ITEM_DIS, 700 );

			_alchemy_item[ i ] = alchemy_item;
		}
	}
	_item_set_flag = false;
}

void Alchemy::alchemyWindow( ) {
	drawString( Vector2( ALCHEMY_POS_X, ALCHEMY_POS_Y ), _chosen_item_1.item.type.name );
	drawString( Vector2( ALCHEMY_POS_X + WINDOW_DIS, ALCHEMY_POS_Y ), _chosen_item_2.item.type.name );
}

bool Alchemy::isRecipe( ) {

	if ( _chosen_item_1.item.type.id != ITEM_NONE &&  _chosen_item_2.item.type.id != ITEM_NONE ) {
		Item::ITEM_DATA data[ ] = {
			_item->getItemStatus( _chosen_item_1.item.type ),
			_item->getItemStatus( _chosen_item_2.item.type ),
		};

			// 固定錬金
		ITEM_ID recipe[ MAX_RECIPE_NUM ][ RECIPE_MAX_ITEM + 1 ] = {
		 // { 素材1 , 素材2 , 完成品 }
			{ HERB1 , HERB1 , HERB2  },
			{ HERB2 , HERB2 , HERB3  },
			{ RING2 , STONE2, STONE3 },
			{ ROD1  , HERB6 , ROD4 },
			{ ROD1	, STONE2, ROD2   },
			{ ROD2  , STONE6, ROD3 },
			{ RING2 , SWORD1, SWORD2 },
			{ STONE5, RING1 , RING6 },
		};

		for( int i = 0; i < MAX_RECIPE_NUM; i++ ) {
			if ( data[ 0 ].type.id == recipe[ i ][ 0 ] && data[ 1 ].type.id == recipe[ i ][ 1 ] ) {
				_create_item = recipe[ i ][ 2 ];
				_camera_check = true;
				_camera->setCameraMode( Camera::ALCHEMY );
				return true;
			} else if ( data[ 0 ].type.id == recipe[ i ][ 1 ] && data[ 1 ].type.id == recipe[ i ][ 0 ] ) {
				_create_item = recipe[ i ][ 2 ];
				_camera_check = true;
				_camera->setCameraMode( Camera::ALCHEMY );
				return true;
			}
		}
	}

	return false;
}

void Alchemy::createItem( int alchemy_point ) {

	if ( _chosen_item_1.item.type.id != ITEM_NONE &&  _chosen_item_2.item.type.id != ITEM_NONE ) {
		Item::ITEM_DATA data[ ] = {
			_item->getItemStatus( _chosen_item_1.item.type ),
			_item->getItemStatus( _chosen_item_2.item.type ),
		};

		//ランダム錬金
		if ( _create_item == ITEM_NONE ) {
			int sum_rarity = data[ 0 ].rarity + data[ 1 ].rarity;
			_create_item = randamAlchemy( sum_rarity, alchemy_point );
		}

		_camera_check = true;

	}
}
ITEM_ID Alchemy::randamAlchemy( int sum_rarity, int alchemy_point ) {
	ITEM_ID create_item = ITEM_NONE;
	if ( alchemy_point == POINT_ZERO ) {
		switch ( sum_rarity ) {
			case 2: {
				// 万分率
				int num [ ] = { 2900, 7000, 100, 0, 0 };
				create_item = itemLottery( num );
				break;
			}
			case 3: {
				int num [ ] = { 2000, 3000, 5000, 0, 0 };
				create_item = itemLottery( num );
				break;
			}
			case 4: {
				int num [ ] = { 0, 3000, 7000, 0, 0 };
				create_item = itemLottery( num );
				break;
			}
			case 5: {
				int num [ ] = { 0, 2000, 7900, 100, 0 };
				create_item = itemLottery( num );
				break;
			}
			case 6: {
				int num [ ] = { 0, 100, 8900, 1000, 0 };
				create_item = itemLottery( num );
				break;
			}
			case 7: {
				int num [ ] = { 0, 0, 4000, 6000, 0 };
				create_item = itemLottery( num );
				break;
			}
			case 8: {
				int num [ ] = { 0, 0, 1000, 9000, 0 };
				create_item = itemLottery( num );
				break;
			}
			case 9: {
				int num [ ] = { 0, 0, 0, 8000, 2000 };
				create_item = itemLottery( num );
				break;
			}
			case 10: {
				int num [ ] = { 100, 0, 0, 900, 9000 };
				create_item = itemLottery( num );
				break;
			}
		}
	} else if ( alchemy_point == POINT_ONE ) {
		switch ( sum_rarity ) {
			case 2: {
				// 万分率
				int num [ ] = { 0, 9800, 200, 0, 0 };
				create_item = itemLottery( num );
				break;
			}
			case 3: {
				int num [ ] = { 0, 3000, 7000, 0, 0 };
				create_item = itemLottery( num );
				break;
			}
			case 4: {
				int num [ ] = { 0, 0, 10000, 0, 0 };
				create_item = itemLottery( num );
				break;
			}
			case 5: {
				int num [ ] = { 0, 400, 9500, 100, 0 };
				create_item = itemLottery( num );
				break;
			}
			case 6: {
				int num [ ] = { 0, 0, 7000, 3000, 0 };
				create_item = itemLottery( num );
				break;
			}
			case 7: {
				int num [ ] = { 0, 0, 3000, 7000, 0 };
				create_item = itemLottery( num );
				break;
			}
			case 8: {
				int num [ ] = { 0, 0, 0, 9900, 100 };
				create_item = itemLottery( num );
				break;
			}
			case 9: {
				int num [ ] = { 0, 0, 0, 5000, 5000 };
				create_item = itemLottery( num );
				break;
			}
			case 10: {
				int num [ ] = { 0, 0, 0, 0, 10000 };
				create_item = itemLottery( num );
				break;
			}
		}
	}  else if ( alchemy_point == POINT_TWO ) {
		switch ( sum_rarity ) {
			case 2: {
				// 万分率
				int num [ ] = { 0, 1000, 9000, 0, 0 };
				create_item = itemLottery( num );
				break;
			}
			case 3: {
				int num [ ] = { 0, 0, 10000, 0, 0 };
				create_item = itemLottery( num );
				break;
			}
			case 4: {
				int num [ ] = { 0, 0, 9900, 100, 0 };
				create_item = itemLottery( num );
				break;
			}
			case 5: {
				int num [ ] = { 0, 0, 7000, 3000, 0 };
				create_item = itemLottery( num );
				break;
			}
			case 6: {
				int num [ ] = { 0, 0, 90, 9900, 10 };
				create_item = itemLottery( num );
				break;
			}
			case 7: {
				int num [ ] = { 0, 0, 0, 9000, 1000 };
				create_item = itemLottery( num );
				break;
			}
			case 8: {
				int num [ ] = { 0, 0, 0, 3000, 7000 };
				create_item = itemLottery( num );
				break;
			}
			case 9: {
				int num [ ] = { 0, 0, 0, 500, 9500 };
				create_item = itemLottery( num );
				break;
			}
			case 10: {
				int num [ ] = { 0, 0, 0, 0, 10000 };
				create_item = itemLottery( num );
				break;
			}
		}
	}
	 return create_item;
}
ITEM_ID Alchemy::itemLottery( int num [ MAX_RARITY ] ) {
	int rand_num = rand( ) % 10000 + 1;

	int create_rerity = 0;
	int sum = 0;
	/*int probability [ MAX_RARITY ];

	// 錬金ポイントによる確立の変動
	//alchemyPointChance( num, probability );
	/*int calculation = _point;
	probability [ 0 ] = num [ 0 ] - calculation;
	
	calculation += _point;
	calculation -= num[ 0 ]; 

	if ( probability [ 0 ] < 0 ) {
		probability [ 0 ] = 0;
		probability [ 1 ] = num [ 1 ] - calculation;
	} else {
		probability [ 1 ] = num [ 1 ] - calculation;
	}

	if ( probability [ 1 ] < 0 ) {
		probability [ 1 ] = 0;
		calculation -= num[ 1 ]; 
		probability [ 2 ] = num [ 2 ] - calculation;
	} else {
		probability [ 2 ] = num [ 2 ];
	}

	if ( probability [ 2 ] < 0 ) {
		probability [ 2 ] = 0;
		calculation -= num[ 2 ]; 
		probability [ 3 ] = num [ 3 ] + _point - calculation;
	} else {
		probability [ 3 ] = num [ 3 ] + _point;
	}

	if ( probability [ 3 ] < 0 ) {
		probability [ 3 ] = 0;
		calculation -= num[ 3 ]	+ _point; 
		probability [ 4 ] = num [ 4 ] + _point - calculation;
	} else {
		probability [ 4 ] = num [ 4 ] + _point;
	}*/
	

	// 作るアイテムのレアリティを決める処理
	for( int i = 0; i < MAX_RARITY; i++ ) {
		sum += num [ i ];
		if ( rand_num <= sum ) {
			create_rerity = i + 1;
			break;
		}
	}
	
	switch( create_rerity ) {
		case 1: {
			rand_num = rand( ) % RARITY_ONE_MAX;
			ITEM_ID id [ ] = { HERB1, ROD1, MEAT1, MEAT4, STONE1, GARBAGE1 };
			return id [ rand_num ];
			break;
		}
		case 2:	{
			rand_num = rand( ) % RARITY_TWO_MAX;
			ITEM_ID id [ ] = { HERB7, HERB8, HERB9, MEAT2, SWORD1, RING1, STONE2 };
			return id [ rand_num ];
			break;
		}
		case 3:	{
			rand_num = rand( ) % RARITY_THREE_MAX;
			ITEM_ID id [ ] = { HERB2, HERB4, HERB5, HERB6, RING2, RING3, STONE5 };
			return id [ rand_num ];
			break;
		}
		case 4:	{
			rand_num = rand( ) % RARITY_FOUR_MAX;
			ITEM_ID id [ ] = { HERB3, ROD2, ROD4, SWORD2, STONE3, STONE6, GARBAGE2, RING4, RING6 };
			return id [ rand_num ];
			break;
		}
		case 5:	{
			rand_num = rand( ) % RARITY_ONE_MAX;
			ITEM_ID id [ ] = { STONE4, RING5, ROD3, SWORD3, SWORD4, MEAT3 };
			return id [ rand_num ];
			break;
		}
	}

	return ITEM_NONE;

}

// アイテムのスクロールを行う関数
void Alchemy::itemScroll( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	TouchPtr touch = std::dynamic_pointer_cast< Touch >( fw->getTask( typeid( Touch ).name( ) ) );
	
	// スライド量を受けとる
	int slide = touch->getSlideNum( ).x;
	
	// 現状の両端のアイテムを保存しておく変数を用意
	int right_item = 0;
	int right_pos_x = 0;
	int left_item = 0;
	int left_pos_x = SCREEN_WIDTH;
	
	for ( int i = 0; i < MAX_ITEM_NUM; i++ ) {
		_alchemy_item [ i ].pos.x += slide;	// 全てのアイテムをスライド分だけ移動させる
	
		// 両端のアイテムを取得する処理
		if ( _alchemy_item [ i ].pos.x < left_pos_x ) {
			 left_pos_x = _alchemy_item [ i ].pos.x;
			 left_item = i;
		}
		if ( _alchemy_item [ i ].pos.x > right_pos_x ) {
			 right_pos_x = _alchemy_item [ i ].pos.x;
			 right_item = i;
		}
	}
	
	// 端にあるアイテムが画面内に収まった時、反対の端のアイテムを持ってくる
	if ( left_pos_x >= 0 ) {
		_alchemy_item [ right_item ].pos.x = -ITEM_DIS + left_pos_x;
	} else if ( right_pos_x <= SCREEN_WIDTH ) {
		_alchemy_item [ left_item ].pos.x = SCREEN_WIDTH + ITEM_DIS - ( SCREEN_WIDTH - right_pos_x );
	}
	
}

// アイテム一覧からアイテムを選ぶ処理
void Alchemy::itemSelect( ) {
	FrameworkPtr fw = Framework::getInstance( );
	TouchPtr touch = std::dynamic_pointer_cast< Touch >( fw->getTask( typeid( Touch ).name( ) ) );

	// ドラッグのためにアイテムをタッチしているかどうかを判別する
	if ( _drag == false ) {
		for ( int i = 0; i < MAX_ITEM_NUM; i++ ) {
			if ( touch->isTouch( _alchemy_item [ i ].pos, BIG_ITEM_WIDTH, BIG_ITEM_HEIGHT ) == true && _alchemy_item[ i ].item.type.id != ITEM_NONE && i != _chosen_item_1.num && i != _chosen_item_2.num ) {
				_wait_count++;
				_item_drag_num = i;
			}
		}
	}
	// 選択中のアイテムをドラッグして外そうとしたとき
	if ( touch->isTouch( CHOICE_AREA_1, BIG_ITEM_WIDTH, BIG_ITEM_HEIGHT ) == true && _drag == false && _chosen_item_1.item.type.id != ITEM_NONE && _separate == true ) {
		_wait_count++;
		_item_drag_num = _chosen_item_1.num;
	} else if ( touch->isTouch( CHOICE_AREA_2, BIG_ITEM_WIDTH, BIG_ITEM_HEIGHT ) == true && _drag == false && _chosen_item_2.item.type.id != ITEM_NONE && _separate == true ) {
		_wait_count++;
		_item_drag_num = _chosen_item_2.num;
	} 

	// アイテムを長押しした時の処理
	if ( _wait_count > GLAB_COUNT && _drag == false ) {
		if ( touch->isTouch( CHOICE_AREA_1, BIG_ITEM_WIDTH, BIG_ITEM_HEIGHT ) == true ) {
			_drag_item = _alchemy_item[ _chosen_item_1.num ];
			_drag_item.image = _item_image->getGrabImage( _alchemy_item[ _chosen_item_1.num ].item.type.id );
			_chosen_item_1 = CHOSEN_ITEM( );
			_drag = true;
			_remove_area_1 = false;
		} else if ( touch->isTouch( CHOICE_AREA_2, BIG_ITEM_WIDTH, BIG_ITEM_HEIGHT ) == true ) {
			_drag_item = _alchemy_item[ _chosen_item_2.num ];
			_drag_item.image = _item_image->getGrabImage( _alchemy_item[ _chosen_item_2.num ].item.type.id );
			_chosen_item_2 = CHOSEN_ITEM( );
			_drag = true;
			_remove_area_2 = false;
		} else {
			_drag_item = _alchemy_item[ _item_drag_num ];
			_drag_item.image = _item_image->getGrabImage( _alchemy_item[ _item_drag_num ].item.type.id );	// 選択したアイテムの枠をなくす
			_drag = true;
		}
	}

	// 選択したアイテムをドラッグして範囲外に出たときの処理
	if ( touch->isTouch( CHOICE_AREA_1, BIG_ITEM_WIDTH, BIG_ITEM_HEIGHT ) == false ) {
		_remove_area_1 = true;
	}
	if ( touch->isTouch( CHOICE_AREA_2, BIG_ITEM_WIDTH, BIG_ITEM_HEIGHT ) == false ) {
		_remove_area_2 = true;
	}

	// アイテムをドラッグ中のタッチ位置へと移動させる処理　( 中心へとずらす処理含む )
	if ( _drag == true ) {
		_drag_item.pos = touch->getTouch( ) - Vector2( GLAB_ITEM_WIDTH / 2, GLAB_ITEM_HEIGHT / 2 );
	}

	// アイテムをドラッグして選択エリアに入れ、決定させる
	if ( touch->isTouch( CHOICE_AREA_1, BIG_ITEM_WIDTH, BIG_ITEM_HEIGHT ) == true && _drag == true && _remove_area_1 == true ) {
		_drag_item = ALCHEMY_ITEM( );
		_chosen_item_1.item = _alchemy_item[ _item_drag_num ].item;
		_chosen_item_1.image = _alchemy_item[ _item_drag_num ].image;
		_chosen_item_1.num = _item_drag_num;
		_item_drag_num = 0;
		_drag = false;
		_wait_count = 0;
		_remove_area_1 = false;
		_separate = false;
	}

	if ( touch->isTouch( CHOICE_AREA_2, BIG_ITEM_WIDTH, BIG_ITEM_HEIGHT ) == true && _drag == true && _remove_area_2 == true ) {
		_drag_item = ALCHEMY_ITEM( );
		_chosen_item_2.item = _alchemy_item[ _item_drag_num ].item;
		_chosen_item_2.image = _alchemy_item[ _item_drag_num ].image;
		_chosen_item_2.num = _item_drag_num;
		_item_drag_num = 0;
		_drag = false;
		_wait_count = 0;
		_remove_area_2 = false;
		_separate = false;
	}

	// 指を離したとき元の位置に戻す
	if ( _drag == true && touch->isSeparate( ) == true ) {
		_drag_item = ALCHEMY_ITEM( );
		_item_drag_num = 0;
		_drag = false;
		_wait_count = 0;
	}

}

void Alchemy::createConfirmationWindow( ) {
	/*FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	TouchPtr touch = std::dynamic_pointer_cast< Touch >( fw->getTask( typeid( Touch ).name( ) ) );

	viewer->drawGraph( CONFIRMATION_POS.x, CONFIRMATION_POS.y, _confirmation_window );
	drawString( CONFIRMATION_POS + Vector2 ( 100, 100 ), "錬金しますか？" );
	drawString( CONFIRMATION_POS + Vector2 ( 350, 100 ), "はい" );
	drawString( CONFIRMATION_POS + Vector2 ( 350, 150 ), "いいえ" );

	// 錬金する
	if ( touch->isTouch( CONFIRMATION_POS + Vector2 ( 350, 100 ), 100, 50 ) ) {
		_camera->setAlchemyFlag( Camera::ALCHEMY );
		createItem( );
		_item_set_flag = true;
	// 連勤しない
	} else if ( touch->isTouch( CONFIRMATION_POS + Vector2 ( 350, 150 ), 100, 100 ) ) {
		cancelAlchemy( );
	}*/

}

void Alchemy::cancelAlchemy( ) {
	_chosen_item_1 = CHOSEN_ITEM( );
	_chosen_item_2 = CHOSEN_ITEM( );
	
}

void Alchemy::selectAlchemyPoint( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	TouchPtr touch = std::dynamic_pointer_cast< Touch >( fw->getTask( typeid( Touch ).name( ) ) );

	// メッセージ
	viewer->drawGraph( POINT_MESSAGE_POS_X, POINT_MESSAGE_POS_Y, _message_window );
	std::string str = "使う錬金ポイントを選んでください。";
	Vector2 str_pos = Vector2 ( POINT_MESSAGE_POS_X + STRING_DIS, POINT_MESSAGE_POS_Y + STRING_DIS );
	drawString( Vector2( str_pos.x, str_pos.y ), str, _point );	// 錬金ポイント

	int touch_num = POINT_NOT_TOUCH;

	for ( int i = 0; i < POINT_SELECT_NUM; i++ ) {
		// タッチしたウィンドウを保存
		Vector2 window_pos ( POINT_WINDOW_SPACE + ( POINT_WINDOW_INTERVAL * i ), POINT_WINDOW_POS_Y );
			
		switch ( i ) {
			case 0: {
				if ( _point >= POINT_ZERO ) {
					viewer->drawGraph( ( int )window_pos.x, ( int )window_pos.y, _point_window_rank1 );
					if ( touch->isTouch( window_pos, POINT_WINDOW_WIDTH, POINT_WINDOW_HEIGHT ) == true && _separate == true ) {
						touch_num = i;
					}
					break;
				}
				viewer->drawGraph( ( int )window_pos.x, ( int )window_pos.y, _point_window_close_rank1 );
				break;
			}
			case 1: {
				if ( _point >= POINT_ONE ) {
					viewer->drawGraph( ( int )window_pos.x, ( int )window_pos.y, _point_window_rank2 );
					if ( touch->isTouch( window_pos, POINT_WINDOW_WIDTH, POINT_WINDOW_HEIGHT ) == true && _separate == true ) {
						touch_num = i;
					}
					break;
				}
				viewer->drawGraph( ( int )window_pos.x, ( int )window_pos.y, _point_window_close_rank2 );
				break;
			}
			case 2: {
				if ( _point >= POINT_TWO ) {
					viewer->drawGraph( ( int )window_pos.x, ( int )window_pos.y, _point_window_rank3 );
					if ( touch->isTouch( window_pos, POINT_WINDOW_WIDTH, POINT_WINDOW_HEIGHT ) == true && _separate == true ) {
						touch_num = i;
					}
					break;
				}
				viewer->drawGraph( ( int )window_pos.x, ( int )window_pos.y, _point_window_close_rank3 );
				break;
			}
		}
	}

	// 錬金をする
	switch ( touch_num ) {
		case 0: {
			_point -= POINT_ZERO;
			_camera->setCameraMode( Camera::ALCHEMY );
			createItem( POINT_ZERO );
			break;
		}

		case 1: {
			_point -= POINT_ONE;
			_camera->setCameraMode( Camera::ALCHEMY );
			createItem( POINT_ONE );
			break;
		}
		
		case 2: {
			_point -= POINT_TWO;
			_camera->setCameraMode( Camera::ALCHEMY );
			createItem( POINT_TWO );
			break;
		}
	}

}

void Alchemy::result( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	TouchPtr touch = std::dynamic_pointer_cast< Touch >( fw->getTask( typeid( Touch ).name( ) ) );

	// ウィンドウ
	viewer->drawGraph( POINT_MESSAGE_POS_X, POINT_MESSAGE_POS_Y, _message_window );
	// 作られたアイテム
	viewer->drawGraph( RESULT_ITEM_POS_X, RESULT_ITEM_POS_Y, _item_image->getNoFrameImage( _create_item ) );
	std::string str = "%sができました。";
	Vector2 str_pos = Vector2 ( POINT_MESSAGE_POS_X + STRING_DIS, POINT_MESSAGE_POS_Y + STRING_DIS );
	drawString( Vector2( str_pos.x, str_pos.y ), str, _item->getItemStatus( _create_item ).type.name );	// 錬金ポイント

	if ( touch->isTouch( ) == true ) {
		_create_item = ITEM_NONE;
		_result_flag = false;
	}

}

void Alchemy::setStartFlag( bool flag ) {
	_start_flag = flag;
}

void Alchemy::potAlchemyAnim( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	SoundPtr sound = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );
	
	// 閉まる音
	if ( _anim_count == 24 ) {
		sound->playSound( Sound::SOUND_TYPE::POT_CLOSE );
	}

	// 開く音
	if ( _anim_count == 51 ) {
		sound->playSound( Sound::SOUND_TYPE::POT_OPEN );
	}

	if ( _anim_count < _pot_anim_total_time ) {
		_anim_count += ANIM_SPEED;
		_performance_finish = false;
	} else {
		_anim_count = ANIM_INIT_TIME;
		_performance_finish = true;
		_camera->setCameraMode( Camera::RETURN );
		_camera->setFinishAlchemy( false );
	}
	viewer->setAttachAnimTime( _pot, 0, _anim_count );
}

void Alchemy::AlchemyTile( ) {
	if ( _network->getFoot( ) == Network::FOOT_THING::FOOT_ALCHEMY ) {
		_point *= 2;
	};
}