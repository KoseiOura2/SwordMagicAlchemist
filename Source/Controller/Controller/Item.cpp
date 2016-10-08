#include "Item.h"
#include "Viewer.h"
#include "Touch.h"
#include "Map.h"
#include "ItemImage.h"

Item::Item( Vector2 pos, NetworkControllerPtr network, MapPtr map, ItemImagePtr item_image ) : Icon( pos ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	_network = network;
	_map = map;
	_item_image = item_image;
	_image = viewer->loadGraph( "work/ctrl_UI/item.png" );
	_window = viewer->loadGraph( "work/ctrl_UI/window/window_item_ver2.png" );
	_window_use = viewer->loadGraph( "work/ctrl_UI/window/window_item_use.png" );
	_open_num = -1;
	_open_page = 1;
	_equipment_weapon = NOT_EQUIPMENT;
	_equipment_accessory = NOT_EQUIPMENT;
	_foot_open = false;

	ITEM_DATA item_teble[ ] = {
	  //ITEM_DATA( type,                   category, rarity, "説明文。" ),
		ITEM_DATA( ITEM_TYPE( HERB1 ),     FOOD,        1,   "☆1　【薬草】食べるとHPが30回復する薬草。" ),
		ITEM_DATA( ITEM_TYPE( HERB2 ),     FOOD,	    3,   "☆3　【上薬草】食べるとHPが60回復する良い薬草。" ),
		ITEM_DATA( ITEM_TYPE( HERB3 ),     FOOD,	    4,   "☆4　【特上薬草】食べるとHPが120回復する凄い薬草。" ),
		ITEM_DATA( ITEM_TYPE( HERB4 ),     FOOD,		3,   "☆3　【見通し草】食べるとフロア全体見通すことが出来る草。" ),
		ITEM_DATA( ITEM_TYPE( HERB5 ),     FOOD,	    3,   "☆3　【なおり草】食べると状態異常を治すことができる薬草。" ),
		ITEM_DATA( ITEM_TYPE( HERB6 ),     FOOD,        3,   "☆3　【ぶっとび草】使用するとフロアのどこかに飛ばされる草。" ),
		ITEM_DATA( ITEM_TYPE( HERB7 ),     FOOD,        2,   "☆2　【毒草】食べると毒状態になってしまう危険な草。" ),
		ITEM_DATA( ITEM_TYPE( HERB8 ),     FOOD,        2,   "☆2　【しびれ草】食べると体が痺れてマヒ状態になってしまう危険な草。" ),
		ITEM_DATA( ITEM_TYPE( HERB9 ),     FOOD,        2,   "☆2　【幻惑草】食べると幻覚に襲われ混乱状態になる危険な草。" ),
		ITEM_DATA( ITEM_TYPE( MEAT1 ),     FOOD,        1,   "☆1　【獣の肉】野生動物の肉。食べるとお腹が10膨れる。" ),
		ITEM_DATA( ITEM_TYPE( MEAT2 ),     FOOD,        2,   "☆2　【大きな肉】大型動物の肉。食べるとお腹が30膨れる。" ),
		ITEM_DATA( ITEM_TYPE( MEAT3 ),     FOOD,        5,   "☆5　【特上スワロース】スワングラーの希少な肉。非常に肉厚で食べるとお腹がいっぱいになる。" ),
		ITEM_DATA( ITEM_TYPE( MEAT4 ),     FOOD,        1,   "☆1　【腐った肉】腐敗した獣の肉。お腹は5膨れるがお腹を壊して毒状態になってしまう。" ),
		ITEM_DATA( ITEM_TYPE( RING1 ),     ACCESSORY,   2,   "☆2　【普通の指輪】宝石が埋められた普通の指輪。装備中、守備力+2。" ),
		ITEM_DATA( ITEM_TYPE( RING2 ),     ACCESSORY,   3,   "☆3　【増命の指輪】生命の加護が宿る宝石が埋められた指輪。装備中、最大HP+10。" ),
		ITEM_DATA( ITEM_TYPE( RING3 ),     ACCESSORY,   3,   "☆3　【加撃の指輪】痛撃の加護が宿る宝石が埋められた指輪。装備中、攻撃力+10。" ),
		ITEM_DATA( ITEM_TYPE( RING4 ),     ACCESSORY,   4,   "☆4　【守りの指輪】剛健の加護が宿る宝石が埋められた指輪。装備中、状態異常にかからない。" ),
		ITEM_DATA( ITEM_TYPE( RING5 ),     ACCESSORY,   5,   "☆5　【創造の指輪】万物の加護が宿る宝石が埋められた指輪。装備中、取得錬金ポイントが2倍になる。" ),
		ITEM_DATA( ITEM_TYPE( RING6 ),     ACCESSORY,   4,   "☆4　【罠除けの指輪】豪運の加護が宿る宝石が埋められた指輪。装備中、罠にかからない。" ),
		ITEM_DATA( ITEM_TYPE( ROD1 ),      WEAPON,	    1,   "☆1　【木の杖】魔力が宿っていないただの木の杖。装備中、攻撃力＋2。" ),
		ITEM_DATA( ITEM_TYPE( ROD2 ),      ROD,	        4,   "☆4　【炎の杖】使うと前方に炎が飛んでいき火炎ダメージを与える杖。" ),
		ITEM_DATA( ITEM_TYPE( ROD3 ),      ROD,		    5,   "☆5　【豪炎の杖】豪炎を宿した杖。使用すると自分のいるフロア全ての敵に火柱攻撃。" ),
		ITEM_DATA( ITEM_TYPE( ROD4 ),      ROD,	        4,   "☆4　【ワープの杖】使用すると直線にいる敵が不思議な力でフロアのどこかにワープする杖。" ),
		ITEM_DATA( ITEM_TYPE( SWORD1 ),    WEAPON,      2,   "☆2　【銅の剣】一般的な剣士が使用している剣。装備中、攻撃力+10。" ),
		ITEM_DATA( ITEM_TYPE( SWORD2 ),    WEAPON,      4,   "☆4　【聖騎士の剣】聖なる騎士が使用している剣。装備中、攻撃力+20。" ),
		ITEM_DATA( ITEM_TYPE( SWORD3 ),    WEAPON,      5,   "☆5　【魔導剣】敵を倒した時に取得できる錬金ポイントが2倍になる魔導士の剣。装備中、攻撃力+40。" ),
		ITEM_DATA( ITEM_TYPE( SWORD4 ),    WEAPON,      5,   "☆5　【トライソード】まれに攻撃時に毒、麻痺、混乱の3種をランダムにかける伝説の剣。" ),
		ITEM_DATA( ITEM_TYPE( STONE1 ),	   STONE,       1,   "☆1　【焼け石】投げると2マス先の敵にダメージを与える高温で焼かれた石。" ),
		ITEM_DATA( ITEM_TYPE( STONE2 ),    CONSUMPTION, 2,   "☆2　【魔導石】使用すると錬金ポイントが50増える魔の力が宿った石。" ),
		ITEM_DATA( ITEM_TYPE( STONE3 ),    STONE,       4,   "☆4　【復活の石】持っていると倒れた時一度だけ復活できる不思議な石。" ),
		ITEM_DATA( ITEM_TYPE( STONE4 ),    CONSUMPTION, 5,   "☆5　【奇跡の石】使用するとレベルが1上がる奇跡の石。" ),
		ITEM_DATA( ITEM_TYPE( STONE5 ),    CONSUMPTION, 3,   "☆3　【罠壊しの石】使用するとフロアのすべての罠が破壊される不思議な石。" ),
		ITEM_DATA( ITEM_TYPE( STONE6 ),    CONSUMPTION, 4,   "☆4　【大魔導石】使用すると錬金ポイントが500増える絶大な魔の力が宿った石。" ),
		ITEM_DATA( ITEM_TYPE( GARBAGE1 ),  STONE,       1,   "☆1　【ゴミ】どこにでも落ちてそうなただのゴミ。" ),
		ITEM_DATA( ITEM_TYPE( GARBAGE2 ),  STONE,       4,   "☆4　【上質なゴミ】珍しく光っているちょっと高級そうなゴミ。" ),	
	};

	for ( int i = 0; i < MAX_ITEM_TYPE; i++ ) {
		_item_table[ i ] = item_teble[ i ];
	}

	COMMAND_DATA command_teble[ ] = {
		COMMAND_DATA( "つかう", Network::ITEM_ACTION::USE,	     USE ),
		COMMAND_DATA( "たべる", Network::ITEM_ACTION::USE,       EAT ),
		COMMAND_DATA( "ふる",   Network::ITEM_ACTION::USE,       SWING ),
		COMMAND_DATA( "なげる", Network::ITEM_ACTION::THROW,	 THROW ),
		COMMAND_DATA( "おく",   Network::ITEM_ACTION::PUT,	     PUT ),
		COMMAND_DATA( "交換",   Network::ITEM_ACTION::EXCHANGE,  EXCHANGE ),
		COMMAND_DATA( "装備"  , Network::ITEM_ACTION::EQUIPMENT, EQUIPMENT ),
		COMMAND_DATA( "はずす", Network::ITEM_ACTION::DISARM,    DISARM ),
		COMMAND_DATA( "とじる", Network::ITEM_ACTION::QUIT,      QUIT ),
		COMMAND_DATA( "拾う",	Network::ITEM_ACTION::PICK_UP,	 PICK_UP ),
	};

	for ( int i = 0; i < MAX_COMMAND_NUM; i++ ) {
		_command_table[ i ] = command_teble[ i ];
	}
	
	//デバッグ用
	/*_item_list.push_back(  _item_table[ 25 ] );
	_item_list.push_back(  _item_table[ 26 ] );
	_item_list.push_back(  _item_table[ 3 ] );
	_item_list.push_back(  _item_table[ 3 ] );
	_item_list.push_back(  _item_table[ 3 ] );
	_item_list.push_back(  _item_table[ 3 ] );
	_item_list.push_back(  _item_table[ 3 ] );
	_item_list.push_back(  _item_table[ 3 ] );*/
	/*_item_list.push_back(  _item_table[ 0 ] );
	_item_list.push_back(  _item_table[ 0 ] );
	_item_list.push_back(  _item_table[ 20 ] );
	_item_list.push_back(  _item_table[ 19 ] );
	_item_list.push_back(  _item_table[ 3 ] );
	_item_list.push_back(  _item_table[ 4 ] );
	_item_list.push_back(  _item_table[ 8 ] );
	_item_list.push_back(  _item_table[ 7 ] );
	_item_list.push_back(  _item_table[ 9 ] );
	_item_list.push_back(  _item_table[ 0 ] );
	_item_list.push_back(  _item_table[ 0 ] );
	_item_list.push_back(  _item_table[ 3 ] );
	_item_list.push_back(  _item_table[ 3 ] );
	_item_list.push_back(  _item_table[ 3 ] );
	_item_list.push_back(  _item_table[ 3 ] );
	_item_list.push_back(  _item_table[ 3 ] );
	_item_list.push_back(  _item_table[ 27 ] );
	_item_list.push_back(  _item_table[ 27 ] );*/
	/*	_foot_item = _item_table[ 20 ];
	_foot_item.type.amount = 6;*/

	//_item_list.push_back(  _item_table[ 3 ] );
	//_item_list.push_back(  _item_table[ 4 ] );
	//_item_list.push_back(  _item_table[ 5 ] );
	//_item_list.push_back(  _item_table[ 6 ] );
	//_item_list.push_back(  _item_table[ 7 ] );
	//_item_list.push_back(  _item_table[ 8 ] );
	//_item_list.push_back(  _item_table[ 9 ] );
	//_item_list.push_back(  _item_table[ 10 ] );
	//_item_list.push_back(  _item_table[ 11 ] );
	//_item_list.push_back(  _item_table[ 12 ] );
	//_item_list.push_back(  _item_table[ 3 ] );
	//_item_list.push_back(  _item_table[ 4 ] );
	//_item_list.push_back(  _item_table[ 5 ] );
	//_item_list.push_back(  _item_table[ 6 ] );
	//_item_list.push_back(  _item_table[ 7 ] );
	//_item_list.push_back(  _item_table[ 8 ] );
	//_item_list.push_back(  _item_table[ 9 ] );
	//_item_list.push_back(  _item_table[ 10 ] );
	//_item_list.push_back(  _item_table[ 11 ] );
	//_item_list.push_back(  _item_table[ 12 ] );
	//_item_list.push_back(  _item_table[ 29 ] );
	//_item_list.push_back(  _item_table[ 29 ] );
	//_item_list.push_back(  _item_table[ 23 ] );
	//_item_list.push_back(  _item_table[ 27 ] );
	//_item_list.push_back(  _item_table[ 26 ] );
	//_item_list.push_back(  _item_table[ 16 ] );
	//_item_list.push_back(  _item_table[ 14 ] );
	//_item_list.push_back(  _item_table[ 8 ] );
	//_item_list.push_back(  _item_table[ 33 ] );
	//_item_list.push_back(  _item_table[ 34 ] );
	//_item_list.push_back(  _item_table[ 24 ] );
	//_item_list.push_back(  _item_table[ 22 ] );
	//_item_list.push_back(  _item_table[ 22 ] );
	//_item_list.push_back(  _item_table[ 22 ] );
	//_item_list.push_back(  _item_table[ 7 ] );
	//_item_list.push_back(  _item_table[ 7 ] );
	//_item_list.push_back(  _item_table[ 7 ] );

	/*for ( int i = 0; i < MAX_ITEM_NUM; i++ ) {
		_item_list.push_back( _item_table[ 0 ] );
	}*/
}

Item::~Item( ) {
}

// 初期化処理
void Item::init( ) {
	_item_list.clear( );
	_equipment_accessory = NOT_EQUIPMENT;
	_equipment_weapon = NOT_EQUIPMENT;
	close( );
}

void Item::touch( ) {
	FrameworkPtr fw = Framework::getInstance( );
	TouchPtr touch = std::dynamic_pointer_cast< Touch >( fw->getTask( typeid( Touch ).name( ) ) );

	saveEquipmentItem( );
	window( );

	if ( _open_num != -1 ) {	
		openItem( );
	} else if ( _foot_open == true ) {
		openFootItem( );
	}

	if ( touch->isSeparate( ) ) {
		_separate_flag = true;
	}

}

// アイテムを閉じたときにやっておきたいやつ
void Item::close( ) {
	_foot_open = false;
	_open_num = -1;
}

void Item::window( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	TouchPtr touch = std::dynamic_pointer_cast< Touch >( fw->getTask( typeid( Touch ).name( ) ) );

	viewer->drawGraph( WINDOW_POS_X, WINDOW_POS_Y, _window );	// ウィンドウの描画
	
	unsigned int count = 0;		// vectorの参照を得るために使うのでwatnig対策にunsigned型
	for ( int i = 0; i < ITEM_COLUMN; i++ ) {
		for ( int j = 0; j < ITEM_ROW; j++ ) {
			// 手持ちアイテムの描画
			Vector2 item_pos ( WINDOW_POS_X + ITEM_X_SPACE + ( ITEM_X_INTERVAL * j ), WINDOW_POS_Y + ITEM_Y_SPACE + ( ITEM_Y_INTERVAL * i ) );
			if ( count < _item_list.size( ) ) {
				// 選択中アイテム
				if ( count == _open_num ) {
					viewer->drawGraph( ( int )item_pos.x, ( int )item_pos.y, _item_image->getFrameWhite( ) );
				}

				viewer->drawGraph( ( int )item_pos.x, ( int )item_pos.y, _item_image->getOnFrameImage( _item_list.at( count ).type.id ) );
				
				// 装備中アイテム
				if ( _item_list.at( count ).equipment == true ) {
					viewer->drawGraph( ( int )item_pos.x, ( int )item_pos.y, _item_image->getFrameEquipment( ) );
				}	

				// 使用回数の表示
				if ( _item_list.at( count ).category == ROD ) {
					viewer->drawGraph( ( int )item_pos.x, ( int )item_pos.y, _item_image->getFrameAmount( _item_list.at( count ).type.amount - 1 ) );
				}
			} else if ( count == MAX_ITEM_NUM ) {	// 足元アイテムの描画
				if ( _foot_open == true ) {
					viewer->drawGraph( ( int )item_pos.x, ( int )item_pos.y, _item_image->getFrameWhite( ) );
				}
				if ( _foot_item.type.id != ITEM_NONE ) {
					viewer->drawGraph( ( int )item_pos.x, ( int )item_pos.y, _item_image->getOnFrameImage( _foot_item.type.id ) );
				} else {
					viewer->drawGraph( ( int )item_pos.x, ( int )item_pos.y,  _item_image->getFrame( ) );
				}
				viewer->drawGraph( ( int )item_pos.x, ( int )item_pos.y, _item_image->getFrameFoot( ) );

				// 使用回数の表示
				if ( _foot_item.category == ROD ) {
					viewer->drawGraph( ( int )item_pos.x, ( int )item_pos.y, _item_image->getFrameAmount( _foot_item.type.amount - 1 ) );
				}

			} else {
				viewer->drawGraph( ( int )item_pos.x, ( int )item_pos.y, _item_image->getFrame( ) );	// 枠の描画
			}

			// アイテムをタッチした時の処理
			// 足元
			if ( touch->isTouch( item_pos, ITEM_WIDTH, ITEM_HEIGHT ) && count == MAX_ITEM_NUM && _foot_item.type.id != ITEM_NONE ) {
				if ( _foot_open == true && _separate_flag == true ) {
					_foot_open = false;
					_separate_flag = false;
				} else if ( _separate_flag == true ) {
					_foot_open = true;
					_open_num = NOT_OPEN_ITEM;	// 手持ちアイテムは閉じておく
					_separate_flag = false;

				}

			} else if ( touch->isTouch( item_pos, ITEM_WIDTH, ITEM_HEIGHT ) && count < _item_list.size( ) ) {	// 足元以外
				if ( _open_num == count && _separate_flag == true ) {
					_open_num = NOT_OPEN_ITEM;
					_separate_flag = false;
				} else if ( _separate_flag == true ) {
					_open_num = count;
					_foot_open = false;		// 足元アイテムを閉じておく
					_separate_flag = false;

				}
			};

			count++;
		}
	}



	// アイテム数の表示
	/*drawString( Vector2( NUM_ITEM_X, NUM_ITEM_Y ), "%d/%d", _item_list.size( ), MAX_ITEM_NUM );

	// 開けるページの最大数を設定
	int max_page_num = _item_list.size( ) / MAX_PAGE_ITEM + 1;
	if ( max_page_num >= MAX_PAGE - 1 ) {
		max_page_num = MAX_PAGE - 1;
	}
	if ( _item_list.size( ) % MAX_PAGE_ITEM == 0 ) {
		max_page_num = _item_list.size( ) / MAX_PAGE_ITEM;
	}

	int last_page = max_page_num;
	// 足下にアイテムがある場合のみ足下アイテム表示用のページを作る
	if ( _foot_item.type.id != ITEM_ID::ITEM_NONE ) {
		max_page_num++;
	}

	// 開くページの設定
	if ( touch->isTouch( Vector2( NEXT_PAGE_POS_X, NEXT_PAGE_POS_Y ), NEXT_PAGE_WIDTH, NEXT_PAGE_HEIGHT ) && _open_page > 1 && _close_flag == false) {
		_open_page--;
		close( );
		_close_flag = true;
	} else if ( touch->isTouch( Vector2( PREV_PAGE_POS_X, PREV_PAGE_POS_Y ), NEXT_PAGE_WIDTH, NEXT_PAGE_HEIGHT ) && _open_page < max_page_num && _close_flag == false ) {
		_open_page++;
		close( );
		_close_flag = true;
	}

	if ( _open_page > max_page_num ) {
		_open_page = max_page_num;
	}

	// for文の回す回数を決める
	int roop_num = 0;
	if ( _open_page == last_page ) {
		roop_num = _item_list.size( ) % MAX_PAGE_ITEM;
		if ( roop_num == 0 && _item_list.size( ) > 0 ) {
			roop_num = MAX_PAGE_ITEM;
		}
	} else if ( _open_page != last_page && _item_list.size( ) > MAX_PAGE_ITEM ) {
		roop_num = MAX_PAGE_ITEM;
	} else if ( _open_page != last_page && _item_list.size( ) < MAX_PAGE_ITEM ) {
		roop_num = _item_list.size( ) % MAX_PAGE_ITEM;
	}
	// for文の初期値を決める
	int init_num = 0;
	if ( _open_page == MAX_PAGE - 1 ) {
		init_num = 10;
		roop_num += init_num;
	}
	// ページ数表示
	drawString( Vector2( PAGE_NUM_X, PAGE_NUM_Y ), "%d/%d", _open_page, max_page_num );
	
	Vector2 item_pos = Vector2( ITEM_LIST_POS_X, WINDOW_POS_Y + WINDOW_TOP_DISTANCE );

	if ( _open_page == max_page_num && _foot_item.type.id != ITEM_NONE ) {
		// 足下アイテムのみ描画
		item_pos.y += ITEM_DISTANCE;
		drawItemName( item_pos, NULL, true );

		if ( _foot_open ) {
			drawStringColor( item_pos, _foot_item.type.name + "( 足下 )", 0, 180, 255 );
		} else {
			drawString( item_pos, _foot_item.type.name + "( 足下 )" );
		}
		//------------アイテム名をタッチした時の処理------------
	   
	    if ( touch->isTouch( item_pos, WINDOW_WIDTH, FONT_SIZE ) ) {
			// 閉じる
			if ( _foot_open == true && _separate_flag == true ) {
				 _close_flag = true;
				 close( );
				 touch->rejectTouch( );
			} 
			// 開く
			else if ( _close_flag == false ) {
				_separate_flag = false;
				_foot_open = true;
			}
		};
	   
	} else {
		 //------------装備アイテムにE表示を付ける処理------------
		for ( int i = init_num; i < roop_num; i++ ) {
			item_pos.y += ITEM_DISTANCE;
			drawItemName( item_pos, i, false );
			//------------アイテム名をタッチした時の処理------------
		   
		    if ( touch->isTouch( item_pos, WINDOW_WIDTH, FONT_SIZE ) ) {
				// 閉じる
				if ( _open_num == i && _separate_flag == true ) {
					 _close_flag = true;
					 close( );
					 touch->rejectTouch( );
				} 
				// 開く
				else if ( _close_flag == false ) {
					_separate_flag = false;
					_open_num = i;
				}
			};
		    //------------------------------------------------------

		}

	}
	if ( _open_num != -1 ) {	
		openItem( );
	} else if ( _foot_open ) {
		openFootItem( );
	}

	if ( touch->isSeparate( ) ) {
		_separate_flag = true;
		_close_flag = false;
	}*/
}

void Item::openItem( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	TouchPtr touch = std::dynamic_pointer_cast< Touch >( fw->getTask( typeid( Touch ).name( ) ) );

	viewer->drawGraph( WINDOW_POS_X + WINDOW_WIDTH, WINDOW_POS_Y, _window_use );	// ウィンドウの描画
	int use_dis = USE_WINDOW_HEIGHT / 6;	// ウィンドウの高さ / コマンドの数 + 2

	Vector2 string_pos [ 4 ] = { Vector2( STRING_POS_X, WINDOW_POS_Y + use_dis ),
								 Vector2( STRING_POS_X, WINDOW_POS_Y + use_dis * 2 ),
								 Vector2( STRING_POS_X, WINDOW_POS_Y + use_dis * 3 ),
								 Vector2( STRING_POS_X, WINDOW_POS_Y + use_dis * 4 ) };

	drawDescription( _item_list.at( _open_num ) );

	setCommand( _item_list.at( _open_num ).category, _item_list.at( _open_num ).equipment );
	for ( unsigned int i = 0; i < _command_list.size( ); i++ ) {
		if ( touch->isTouch( string_pos[ i ], ITEM_TOUCH_WIDTH, FONT_SIZE ) ) {
			openCommand( _command_list.at( i ) );
		}
		drawString( string_pos[ i ], _command_list.at( i ).name );
	}

}

void Item::openFootItem( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	TouchPtr touch = std::dynamic_pointer_cast< Touch >( fw->getTask( typeid( Touch ).name( ) ) );

	viewer->drawGraph( WINDOW_POS_X + WINDOW_WIDTH, WINDOW_POS_Y, _window_use );	// ウィンドウの描画
	int use_dis = USE_WINDOW_HEIGHT / 5;	// ウィンドウの高さ / コマンドの数 + 2

	Vector2 string_pos [ 3 ] = { Vector2( STRING_POS_X, WINDOW_POS_Y + use_dis ),
								 Vector2( STRING_POS_X, WINDOW_POS_Y + use_dis * 2 ),
								 Vector2( STRING_POS_X, WINDOW_POS_Y + use_dis * 3 ) };

	drawDescription( _foot_item );

	setCommand( _foot_item.category, false );
	for ( unsigned int i = 0; i < _command_list.size( ); i++ ) {
		if ( touch->isTouch( string_pos[ i ], ITEM_TOUCH_WIDTH, FONT_SIZE ) ) {
			openCommand( _command_list.at( i ) );
		}
		drawString( string_pos[ i ], _command_list.at( i ).name );
	}

}

void Item::saveEquipmentItem( ) {
	bool weapon_flag = false;		// 武器を装備しているか
	bool accessory_flag = false;	// アクセサリーを装備しているか

	for ( int i = 0; i < _item_list.size( ); i++ ) {
		if ( _item_list.at( i ).equipment == true ) {
			switch( _item_list.at( i ).category ) {
			case WEAPON:
				weapon_flag = true;
				_equipment_weapon = i;
				break;
			case ACCESSORY:
				accessory_flag = true;
				_equipment_accessory = i;
				break;
			}
		}
	}
	
	// アイテムを装備していないとき
	if ( weapon_flag == false ) {
		_equipment_weapon = NOT_EQUIPMENT;
	}

	if ( accessory_flag == false ) {
		_equipment_accessory = NOT_EQUIPMENT;
	}

}

// とじるコマンドの処理
void Item::commandQuit( ) {
	// 各コマンド共通処理のみなので特になし
	return;
}

// おくコマンドの処理
void Item::commandPut( ) {
	_network->setSendItem( Network::ITEM_ACTION::PUT, _item_list.at( _open_num ).type );
	_foot_item = _item_list.at( _open_num );
	_item_list.erase( _item_list.begin( ) + _open_num );	// 使ったアイテムの削除
	adjustEquipment( );
}
// 交換コマンドの処理
void Item::commandExchange( ) {
	ITEM_DATA temp;
	temp = _item_list.at( _open_num );
	_network->setSendItem( Network::ITEM_ACTION::EXCHANGE, _item_list.at( _open_num ).type );
	_item_list.at( _open_num ) = _foot_item;	// アイテムを足下のアイテムと交換
	_foot_item = temp;
}

// つかう、たべる等のつかうアクションの時の処理
void Item::commandUse( ) {
	// 足下アイテムかを判別して処理を切り替える
	if ( _foot_open == true ) {
		_network->setSendItem( Network::ITEM_ACTION::USE, _foot_item.type );
		_network->setSendUseFootItem( true );
		 
		_foot_item.type.amount--;
		if ( _foot_item.type.amount <= 0 ) {
			_foot_item = ITEM_DATA( );
			_foot_open = false;
			_open_page--;
		}
		return;
	}

	_network->setSendItem( Network::ITEM_ACTION::USE, _item_list.at( _open_num ).type );
	// 見通し草処理
	if ( _item_list.at( _open_num ).type.id == HERB4 ) {
		// マップの見通し草の関数を呼ぶ
		_map->clairvoyance( );
	}
	if ( _item_list.at( _open_num ).type.id == STONE5 ) {
		_map->mysteryClear( );
	}

	_item_list.at( _open_num ).type.amount--;	// 使用回数を一回減らす
	if ( _item_list.at( _open_num ).type.amount <= 0 && _item_list.at( _open_num ).category == ROD ) {
		_item_list.at( _open_num ) = _item_table[ ROD1 - 1 ];	// 使い終わった杖は木の杖にする

	} else if ( _item_list.at( _open_num ).type.amount <= 0 ) {
		_item_list.erase( _item_list.begin( ) + _open_num );	// 使ったアイテムの削除
		adjustEquipment( );
	}
}

// なげるコマンドの処理
void Item::commandThrow( ) {
	if ( _foot_open ) {
		_network->setSendItem( Network::ITEM_ACTION::THROW, _foot_item.type );
		_network->setSendUseFootItem( true );
		_foot_item = ITEM_DATA( );
		_foot_open = false;
		_open_page--;
		return;
	}
	_network->setSendItem( Network::ITEM_ACTION::THROW, _item_list.at( _open_num ).type );
	_item_list.erase( _item_list.begin( ) + _open_num );	// なげたアイテムの削除
	adjustEquipment( );
}

// 装備コマンドの処理
void Item::commandEquipment( ) {
	// 既に装備していたものを外す処理
	if ( _item_list.at( _open_num ).category == WEAPON ) {
		 if( _equipment_weapon != NOT_EQUIPMENT ) {
			 _item_list.at( _equipment_weapon ).equipment = false;
		 }
	} else if ( _item_list.at( _open_num ).category == ACCESSORY ) {
		 if( _equipment_accessory != NOT_EQUIPMENT ) {
			 _item_list.at( _equipment_accessory ).equipment = false;
		 }
	}

	_network->setSendItem( Network::ITEM_ACTION::EQUIPMENT, _item_list.at( _open_num ).type );
	_item_list.at( _open_num ).equipment = true;
}

// はずすコマンドの処理
void Item::commandDisarm( ) {
	_network->setSendItem( Network::ITEM_ACTION::DISARM, _item_list.at( _open_num ).type );
	_item_list.at( _open_num ).equipment = false;
}

// 拾うコマンドの処理
void Item::commandPickUp( ) {
	_network->setSendItem( Network::ITEM_ACTION::PICK_UP, _foot_item.type );
	
	if ( _item_list.size( ) >= MAX_ITEM_NUM ) { // アイテムがいっぱいのとき
		return;
	}

	// 足下アイテムを手持ちに追加する
	_item_list.push_back( _foot_item );
	_foot_item = ITEM_DATA( );

}

void Item::openCommand( COMMAND_DATA command ) {
	FrameworkPtr fw = Framework::getInstance( );
	TouchPtr touch = std::dynamic_pointer_cast< Touch >( fw->getTask( typeid( Touch ).name( ) ) );

	void ( Item::* funcArray[ ] )( void ) = {
		&Item::commandQuit,
		&Item::commandPut,
		&Item::commandExchange,
		&Item::commandUse,
		&Item::commandThrow,
		&Item::commandEquipment,
		&Item::commandDisarm,
		&Item::commandPickUp,
	};
	void ( Item::*func )( void ) = funcArray[ command.action ];
	( this->*func )( );

	close( );
	touch->rejectTouch( );
}

// アイテムを開いた際のコマンドを設定する関数
void Item::setCommand( CATEGORY category, bool equipment ) {
	_command_list.clear( );

	COMMAND_DATA data;
	// 使う食べる等
	switch( category ) {
	case WEAPON:
	case ACCESSORY:
		if ( _foot_open == false ) {
			if ( equipment && _foot_open == false ) {
				data = getCommandStatus( DISARM );
			} else {
				data = getCommandStatus( EQUIPMENT );
			}
			_command_list.push_back( data );
		}
		break;
	case CONSUMPTION:
		data = getCommandStatus( USE );
		_command_list.push_back( data );
		break;
	case FOOD:
		data = getCommandStatus( EAT );
		_command_list.push_back( data );
		break;
	case ROD:
		data = getCommandStatus( SWING );
		_command_list.push_back( data );
		break;
	case STONE:
		break;
	}

	// footitemのみ拾う
	if ( _foot_open == true ) {
		data = getCommandStatus( PICK_UP );
		_command_list.push_back( data );
	}

	// なげる
	_command_list.push_back( getCommandStatus( THROW ) );

	// おくor交換
	// 足下アイテムではなく、足下に階段がないときのみ
	if ( _foot_open == false && _network->getFoot( ) != Network::FOOT_STAIR ) {
		if ( _foot_item.type.id != ITEM_NONE ) {
			_command_list.push_back( getCommandStatus( EXCHANGE ) );
		} else {
			_command_list.push_back( getCommandStatus( PUT ) );
		}
	}

	// とじる
	_command_list.push_back( getCommandStatus( QUIT ) );


}

// コマンドのステータスを取得する関数
Item::COMMAND_DATA Item::getCommandStatus( COMMAND command ) {
	COMMAND_DATA result;

	for ( int i = 0; i < MAX_COMMAND_NUM; i++ ) {
		if ( _command_table[ i ].command == command ) {
			result = _command_table[ i ];
			break;
		}
	}
	return result;
}

// アイテム説明の描画
void Item::drawDescription( ITEM_DATA item ) {
	int line = 0;
	line = item.description.find( "】" );
	if ( line == std::string::npos ) {
		line = item.description.find( "。" );
	}
	line += 2;
	std::string tmp = item.description.substr( 0, line );	// 。までの位置を一行目とする
	drawStringSmallFont( Vector2 ( DESCRIPTION_X, DESCRIPTION_Y ), tmp );
	tmp = item.description.substr( line );					// 。以降の文字を2行目にする
	drawStringSmallFont( Vector2 ( DESCRIPTION_X, DESCRIPTION_Y + FONT_SMALL_SIZE ), tmp );
}

void Item::onItem( ) {
	ITEM_DATA temp;
	temp.type =_network->getItemType( );
	temp = getItemStatus( temp.type );

	if ( _network->getFoot( ) == Network::FOOT_THING::FOOT_ITEM && temp.type.id != ITEM_ID::ITEM_NONE && _network->isRide( ) == true ) {

		if ( _item_list.size( ) < MAX_ITEM_NUM && _foot_item.type.id == ITEM_NONE ) {

			// アイテムに空きがあり_foot_itemを登録していないとき
			_item_list.push_back( temp );
			_network->setFootThing( Network::FOOT_THING::FOOT_NONE );
			_network->setSendItemAction( Network::ON_ITEM::NO );

		} else if ( _item_list.size( ) >= MAX_ITEM_NUM && _foot_item.type.id == ITEM_NONE ) {

			// アイテムがいっぱいで_foot_itemを登録してないとき
			_foot_item = temp;
			_network->setSendItemAction( Network::ON_ITEM::YES );
		} else if ( _item_list.size( ) >= MAX_ITEM_NUM && _foot_item.type.id != ITEM_NONE ) {

			// アイテムがいっぱいで_foot_itemを登録してたとき
			_network->setSendItemAction( Network::ON_ITEM::YES );
		}
		//_network->resetRide( );
	} else if ( _network->getFoot( ) == Network::FOOT_THING::FOOT_ITEM && temp.type.id != ITEM_ID::ITEM_NONE && _network->isRide( ) == false ) {
		_foot_item = temp;
		
	} else if ( _network->getFoot( ) != Network::FOOT_THING::FOOT_ITEM && _network->isRide( ) == false ) {
		_foot_item = ITEM_DATA( ); // プレイヤーが歩いた時足下のデータを消す
	}
}

std::vector< Item::ITEM_DATA > Item::getItemList( ) {
	return _item_list;
}

Item::ITEM_DATA Item::getFootItem( ) {
	return _foot_item;
}
// アイテムのidから性能を取得する関数
Item::ITEM_DATA Item::getItemStatus( ITEM_ID id ) {
	ITEM_DATA result;

	for ( int i = 0; i < MAX_ITEM_TYPE; i++ ) {
		if ( _item_table[ i ].type.id == id ) {
			result = _item_table[ i ];
			break;
		}
	}
	return result;
}
// アイテムのtypeから性能を取得し、使用回数などのtypeは保持しておく関数
Item::ITEM_DATA Item::getItemStatus( ITEM_TYPE item ) {
	ITEM_DATA result;

	for ( int i = 0; i < MAX_ITEM_TYPE; i++ ) {
		if ( _item_table[ i ].type.id == item.id ) {
			result = _item_table[ i ];
			break;
		}
	}
	result.type = item;	//　使用回数があった場合それを消さないように

	return result;
}

void Item::alchemy( int del_item_1, int del_item_2, ITEM_ID new_item ) {
	int first_del = del_item_1;
	int second_del = del_item_2;
	if ( del_item_2 > del_item_1 ) {
		first_del = del_item_2;
		second_del = del_item_1;
	}
	ITEM_DATA new_item_data = getItemStatus( new_item );
	// 錬金で作ったアイテムが杖だったとき使用回数を設定
	if ( new_item_data.category == ROD ) {
		new_item_data.type.amount = 5 + rand( ) % 3;
	}
	_item_list.erase( _item_list.begin( ) + first_del );
	_item_list.erase( _item_list.begin( ) + second_del );
	adjustEquipment( );
	_item_list.push_back( new_item_data );
}

void Item::footItemAlchemy( int del_item, ITEM_ID new_item ) {
	_item_list.erase( _item_list.begin( ) + del_item );
	adjustEquipment( );
	_network->setSendUseFootItem( true );
	_item_list.push_back( getItemStatus( new_item ) );
	_foot_item = ITEM_DATA( );
}

// 死亡時に復活の石を持っているかを返し、持っていた場合は復活の石を使用して復活する
bool Item::isRiviveItem( ) {
	for ( int i = 0; i < _item_list.size( ); i++ ) {
		if ( _item_list.at( i ).type.id == STONE3 ) {
			_item_list.erase( _item_list.begin( ) + i );
			adjustEquipment( );
			return true;
		}
	}
	return false;
}
bool Item::isCreateRingEquipment( ) {
	if( _equipment_accessory == NOT_EQUIPMENT ) {
		return false;
	}

	if ( _item_list.at( _equipment_accessory ).type.id == RING5 ) {
		return true;
	}
	return false;
}

bool Item::isMagicSwordEquipment( ) {
	if( _equipment_weapon == NOT_EQUIPMENT ) {
		return false;
	}

	if ( _item_list.at( _equipment_weapon ).type.id == SWORD3 ) {
		return true;
	}
	return false;
}

void Item::setFootOpen( bool flag ) {
	_foot_open = flag;
}

void Item::adjustEquipment( ) {
	for ( int i = 0; i < _item_list.size( ); i ++ ) {
		if ( _item_list.at( i ).equipment == true ) {
			switch ( _item_list.at( i ).category ) {
				case WEAPON: {
					_equipment_weapon = i;
					break;
				}
				case ACCESSORY: {
					_equipment_accessory = i;
					break;
				}
			}
		}

	}
}