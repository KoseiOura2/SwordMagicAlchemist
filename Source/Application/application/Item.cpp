#include "Item.h"
#include "Framework.h"
#include "Viewer.h"
#include "Floor.h"
#include "Keyboard.h"
#include "MessageLog.h"
#include "Effect.h"
#include "Sound.h"

Item::Item(  FloorPtr floor, NetworkAppPtr network, MessageLogPtr messageLog, EffectPtr effect ) {
	loadModel( );

	ITEM_DATA item_table [ ] = {
	 // ITEM_DATA( ID,       handle,           scale,                         rotate )
		ITEM_DATA( HERB1,    _herb_model_1,    Vector( 1.0f, 1.0f, 1.0f ), Vector( 0.0f, 0.0f, 0.0f ) ),
		ITEM_DATA( HERB2,    _herb_model_2,    Vector( 1.0f, 1.0f, 1.0f ), Vector( 0.0f, 0.0f, 0.0f ) ),
		ITEM_DATA( HERB3,    _herb_model_3,    Vector( 1.0f, 1.0f, 1.0f ), Vector( 0.0f, 0.0f, 0.0f ) ),
		ITEM_DATA( HERB4,    _herb_model_4,    Vector( 1.0f, 1.0f, 1.0f ), Vector( 0.0f, 0.0f, 0.0f ) ),
		ITEM_DATA( HERB5,    _herb_model_5,    Vector( 1.0f, 1.0f, 1.0f ), Vector( 0.0f, 0.0f, 0.0f ) ),
		ITEM_DATA( HERB6,    _herb_model_6,    Vector( 1.0f, 1.0f, 1.0f ), Vector( 0.0f, 0.0f, 0.0f ) ),
		ITEM_DATA( HERB7,    _herb_model_7,    Vector( 1.0f, 1.0f, 1.0f ), Vector( 0.0f, 0.0f, 0.0f ) ),
		ITEM_DATA( HERB8,    _herb_model_8,    Vector( 1.0f, 1.0f, 1.0f ), Vector( 0.0f, 0.0f, 0.0f ) ),
		ITEM_DATA( HERB9,    _herb_model_9,    Vector( 1.0f, 1.0f, 1.0f ), Vector( 0.0f, 0.0f, 0.0f ) ),
		ITEM_DATA( MEAT1,    _meat_model_1,    Vector( 0.2f, 0.2f, 0.2f ), Vector( 0.0f, 0.0f, 0.0f ) ),
		ITEM_DATA( MEAT2,    _meat_model_2,    Vector( 0.5f, 0.5f, 0.5f ), Vector( 0.0f, 0.0f, 0.0f ) ),
		ITEM_DATA( MEAT3,    _meat_model_3,    Vector( 1.0f, 1.0f, 1.0f ), Vector( 0.0f, 0.0f, 0.0f ) ),
		ITEM_DATA( MEAT4,    _meat_model_4,    Vector( 0.2f, 0.2f, 0.2f ), Vector( 0.0f, 0.0f, 0.0f ) ),
		ITEM_DATA( RING1,    _ring_model_1,    Vector( 5.0f, 5.0f, 5.0f ), Vector( -45.0f, 90.0f, 45.0f ) ),
		ITEM_DATA( RING2,    _ring_model_2,    Vector( 5.0f, 5.0f, 5.0f ), Vector( -45.0f, 90.0f, 45.0f ) ),
		ITEM_DATA( RING3,    _ring_model_3,    Vector( 5.0f, 5.0f, 5.0f ), Vector( -45.0f, 90.0f, 45.0f ) ),
		ITEM_DATA( RING4,    _ring_model_4,    Vector( 5.0f, 5.0f, 5.0f ), Vector( -45.0f, 90.0f, 45.0f ) ),
		ITEM_DATA( RING5,    _ring_model_5,    Vector( 5.0f, 5.0f, 5.0f ), Vector( -45.0f, 90.0f, 45.0f ) ),
		ITEM_DATA( RING6,    _ring_model_6,    Vector( 5.0f, 5.0f, 5.0f ), Vector( -45.0f, 90.0f, 45.0f ) ),
		ITEM_DATA( ROD1,     _rod_model_1,     Vector( 0.7f, 0.7f, 0.7f ), Vector( -45.0f, 0.0f, 90.0f ) ),
		ITEM_DATA( ROD2,     _rod_model_2,     Vector( 0.7f, 0.7f, 0.7f ), Vector( -45.0f, 0.0f, 90.0f ) ),
		ITEM_DATA( ROD3,     _rod_model_3,     Vector( 0.7f, 0.7f, 0.7f ), Vector( -45.0f, 0.0f, 90.0f ) ),
		ITEM_DATA( ROD4,     _rod_model_4,     Vector( 0.7f, 0.7f, 0.7f ), Vector( -45.0f, 0.0f, 90.0f ) ),
		ITEM_DATA( SWORD1,   _sword_model_1,   Vector( 0.4f, 0.4f, 0.4f ), Vector( 30.0f, 45.0f, 0.0f ) ),
		ITEM_DATA( SWORD2,   _sword_model_2,   Vector( 0.4f, 0.4f, 0.4f ), Vector( 30.0f, 45.0f, 0.0f ) ),
		ITEM_DATA( SWORD3,   _sword_model_3,   Vector( 0.4f, 0.4f, 0.4f ), Vector( 30.0f, 45.0f, 0.0f ) ),
		ITEM_DATA( SWORD4,   _sword_model_4,   Vector( 0.4f, 0.4f, 0.4f ), Vector( 30.0f, 45.0f, 0.0f ) ),
		ITEM_DATA( STONE1,   _stone_model_1,   Vector( 5.0f, 5.0f, 5.0f ), Vector( 0.0f, 0.0f, 0.0f ) ),
		ITEM_DATA( STONE2,   _stone_model_2,   Vector( 3.0f, 3.0f, 3.0f ), Vector( 0.0f, 0.0f, 0.0f ) ),
		ITEM_DATA( STONE3,   _stone_model_3,   Vector( 5.0f, 5.0f, 5.0f ), Vector( 0.0f, 0.0f, 0.0f ) ),
		ITEM_DATA( STONE4,   _stone_model_4,   Vector( 5.0f, 5.0f, 5.0f ), Vector( 0.0f, 0.0f, 0.0f ) ),
		ITEM_DATA( STONE5,   _stone_model_5,   Vector( 5.0f, 5.0f, 5.0f ), Vector( 0.0f, 0.0f, 0.0f ) ),
		ITEM_DATA( STONE6,   _stone_model_6,   Vector( 7.0f, 7.0f, 7.0f ), Vector( 0.0f, 0.0f, 0.0f ) ),
		ITEM_DATA( GARBAGE1, _garbage_model_1, Vector( 5.0f, 5.0f, 5.0f ), Vector( 0.0f, 0.0f, 0.0f ) ),
		ITEM_DATA( GARBAGE2, _garbage_model_2, Vector( 5.0f, 5.0f, 5.0f ), Vector( 0.0f, 0.0f, 0.0f ) ),
	};
	for ( int i = 0; i < MAX_ITEM_TYPE; i++ ) {
		_item_table[ i ] = item_table[ i ];
	}

	_floor      = floor;
	_network    = network;
	_messageLog = messageLog;
	_effect     = effect;
}

Item::~Item( ) {

}

void Item::loadModel( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	
	_shadow_image       = viewer->loadGraph( "work/tile/shadow.png" );
	_herb_model_1 = viewer->loadModel( "work/model/item/herb/herb1.mv1" );
	_herb_model_2 = viewer->loadModel( "work/model/item/herb/herb2.mv1" );
	_herb_model_3 = viewer->loadModel( "work/model/item/herb/herb3.mv1" );
	_herb_model_4 = viewer->loadModel( "work/model/item/herb/herb4.mv1" );
	_herb_model_5 = viewer->loadModel( "work/model/item/herb/herb5.mv1" );
	_herb_model_6 = viewer->loadModel( "work/model/item/herb/herb6.mv1" );
	_herb_model_7 = viewer->loadModel( "work/model/item/herb/herb7.mv1" );
	_herb_model_8 = viewer->loadModel( "work/model/item/herb/herb8.mv1" );
	_herb_model_9 = viewer->loadModel( "work/model/item/herb/herb9.mv1" );

	_meat_model_1 = viewer->loadModel( "work/model/item/meat/meat1_2_0/meat.mv1" );
	_meat_model_2 = viewer->loadModel( "work/model/item/meat/meat1_2_0/meat.mv1" );
	_meat_model_3 = viewer->loadModel( "work/model/item/meat/meat3_1_0/sourceimages/item_meat03.mv1" );
	_meat_model_4 = viewer->loadModel( "work/model/item/meat/meat2_1_0/item_meat02.mv1" );

	_ring_model_1 = viewer->loadModel( "work/model/item/ring/item_ring1.mv1" );
	_ring_model_2 = viewer->loadModel( "work/model/item/ring/item_ring2.mv1" );
	_ring_model_3 = viewer->loadModel( "work/model/item/ring/item_ring3.mv1" );
	_ring_model_4 = viewer->loadModel( "work/model/item/ring/item_ring4.mv1" );
	_ring_model_5 = viewer->loadModel( "work/model/item/ring/item_ring5.mv1" );
	_ring_model_6 = viewer->loadModel( "work/model/item/ring/item_ring6.mv1" );

	_rod_model_1 = viewer->loadModel( "work/model/item/rod1/rod1.mv1" );
	_rod_model_2 = viewer->loadModel( "work/model/item/rod2/rod2.mv1" );
	_rod_model_3 = viewer->loadModel( "work/model/item/rod3/rod3.mv1" );
	_rod_model_4 = viewer->loadModel( "work/model/item/rod4/scenes/item_rod4.mv1" );

	_sword_model_1 = viewer->loadModel( "work/model/item/sword/sword1.mv1" );
	_sword_model_2 = viewer->loadModel( "work/model/item/sword/sword2.mv1" );
	_sword_model_3 = viewer->loadModel( "work/model/item/sword/sword3.mv1" );
	_sword_model_4 = viewer->loadModel( "work/model/item/sword/sword4.mv1" );

	_stone_model_1 = viewer->loadModel( "work/model/item/item_stone/item_stone1.mv1" );
	_stone_model_2 = viewer->loadModel( "work/model/item/item_stone/item_stone2.mv1" );
	_stone_model_3 = viewer->loadModel( "work/model/item/item_stone/item_stone3.mv1" );
	_stone_model_4 = viewer->loadModel( "work/model/item/item_stone/item_stone4.mv1" );
	_stone_model_5 = viewer->loadModel( "work/model/item/item_stone/item_stone5.mv1" );
	_stone_model_6 = viewer->loadModel( "work/model/item/item_stone/item_stone6.mv1" );
	
	_garbage_model_1 = viewer->loadModel( "work/model/item/gomi/gomi01.mv1" );
	_garbage_model_2 = viewer->loadModel( "work/model/item/gomi/gomi02.mv1" );
}

void Item::init( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	_item_damage     = 0;

	_foot                    = false;
	_throw_item_toward_enemy = false;
	_throw                   = false;
	_end_throw               = false;
	_hit_enemy               = false;
	_use_flame_rod           = false;
	_use_super_flame_rod     = false;
	_use_warp_rod            = false;
	_turn_end                = false;
	

	// �K�w�ɂ���ďo������A�C�e����ς���
	void ( Item::* funcArray[ ] )( ) = {
		&Item::createFloor1,
		&Item::createFloor2,
		&Item::createFloor3,
		&Item::createFloor4,
	};
	void ( Item::* func )( ) = funcArray[ _floor_level - 1 ];
	( this->*func )( );

	/*
	// �f�o�b�O
	_start_item_num = 10;
	for ( int i = 0; i < _start_item_num; i++ ) {
		
		ITEM_DATA herb = getItemDataForID( SWORD4 );
		_items.push_back( herb );
	}
	*/
	
	for ( unsigned int i = 0; i < _items.size( ); i++ ) {
		// ���f���̐ݒ�
		viewer->modelSetScale( _items.at( i ).model_hundle, _items.at( i ).scale.x, _items.at( i ).scale.y, _items.at( i ).scale.z );
		viewer->modelSetRotation( _items.at( i ).model_hundle, _items.at( i ).rotate.x, _items.at( i ).rotate.y, _items.at( i ).rotate.z );
		// ���W�̐ݒ�
		_items.at( i ).draw_pos = getInitPos( );
		_items.at( i ).pre_pos = _items.at( i ).draw_pos;
		_items.at( i ).pos.x = _items.at( i ).draw_pos.x / TILE_SIZE;
		_items.at( i ).pos.y = _items.at( i ).draw_pos.z / TILE_SIZE;
		_network->setSendChipData( NetworkApp::MAP_CHIP_TYPE::ITEM, _items.at( i ).pos, 0, false );
	}
}

void Item::createFloor1( ) {
	// �o�������
	_start_item_num = 5 + rand( ) % 3;       // 5 �` 7��:3����/4����
	// �o��������
	ITEM_DATA herb1  = getItemDataForID( HERB1 );
	ITEM_DATA herb7  = getItemDataForID( HERB7 );
	ITEM_DATA herb9  = getItemDataForID( HERB9 );
	ITEM_DATA meat1  = getItemDataForID( MEAT1 );
	ITEM_DATA meat4  = getItemDataForID( MEAT4 );
	ITEM_DATA ring1  = getItemDataForID( RING1 );
	ITEM_DATA rod1   = getItemDataForID( ROD1 );
	ITEM_DATA sword1 = getItemDataForID( SWORD1 );
	ITEM_DATA stone1 = getItemDataForID( STONE1 );
	ITEM_DATA stone2 = getItemDataForID( STONE2 );
	ITEM_DATA gomi1  = getItemDataForID( GARBAGE1 );

	// �A�C�e���̊m��
	int probability[ ] = { 1500, 3000, 4300, 5300, 6300, 6600, 7600, 8600, 8900, 9900 };
	for ( int i = 0; i < _start_item_num; i++ ) {
		// �o������m��
		int num = rand( ) % 10000;
		// �򑐁F15��
		if ( num < probability[ 0 ] ) {
			_items.push_back( herb1 );
		} 
		// �b�̓��F15��
		else if ( num < probability[ 1 ] ) {
			_items.push_back( meat1 );
		}   
		// �Ă��΁F13��
		else if ( num < probability[ 2 ] ) {
			_items.push_back( stone1 );
		}  
		// �ő��F10��
		else if ( num < probability[ 3 ] ) {
			_items.push_back( herb7 );
		}   
		// ���f���F10��
		else if ( num < probability[ 4 ] ) {
			_items.push_back( herb9 );
		} 
		// ���������F3��
		else if ( num < probability[ 5 ] ) {
			_items.push_back( meat4 );
		}  
		// ���ʂ̎w�ցF10��
		else if ( num < probability[ 6 ] ) {
			_items.push_back( ring1 );
		}  
		// �؂̏�F10��
		else if ( num < probability[ 7 ] ) {
			_items.push_back( rod1 );
		} 
		// ���̌��F3��
		else if ( num < probability[ 8 ] ) {
			_items.push_back( sword1 );
		}  
		// �����΁F10��
		else if ( num < probability[ 9 ] ) {
			_items.push_back( stone2 );
		} 
		// ���݁F1��
		else {
			_items.push_back( gomi1 );
		}  
	}
}

void Item::createFloor2( ) {
	// �o�������
	_start_item_num = 7 + rand( ) % 4;       // 7 �` 10��:4����/6����
	// �o��������
	ITEM_DATA herb1  = getItemDataForID( HERB1 );
	ITEM_DATA herb2  = getItemDataForID( HERB2 );
	ITEM_DATA herb5  = getItemDataForID( HERB5 );
	ITEM_DATA herb6  = getItemDataForID( HERB6 );
	ITEM_DATA herb8  = getItemDataForID( HERB8 );
	ITEM_DATA meat1  = getItemDataForID( MEAT1 );
	ITEM_DATA meat4  = getItemDataForID( MEAT4 );
	ITEM_DATA ring1  = getItemDataForID( RING1 );
	ITEM_DATA ring2  = getItemDataForID( RING2 );
	ITEM_DATA ring3  = getItemDataForID( RING3 );
	ITEM_DATA ring4  = getItemDataForID( RING4 );
	ITEM_DATA rod1   = getItemDataForID( ROD1 );
	ITEM_DATA sword1 = getItemDataForID( SWORD1 );
	ITEM_DATA stone1 = getItemDataForID( STONE1 );
	ITEM_DATA stone2 = getItemDataForID( STONE2 );
	ITEM_DATA stone3 = getItemDataForID( STONE3 );
	ITEM_DATA gomi1  = getItemDataForID( GARBAGE1 );
	
	// �A�C�e���̊m��
	int probability[ ] = { 1700, 3200, 4200, 4500, 4800, 5300, 6300, 7300, 8000, 9000, 9100, 9200, 9300, 9500, 9600, 9900  };
	for ( int i = 0; i < _start_item_num; i++ ) {
		// �o������m��
		int num = rand( ) % 10000;
		// �򑐁F17��
		if ( num < probability[ 0 ] ) {
			_items.push_back( herb1 );
		} 
		// �b�̓��F15��
		else if ( num < probability[ 1 ] ) {
			_items.push_back( meat1 );
		}   
		// �Ă��΁F10��
		else if ( num < probability[ 2 ] ) {
			_items.push_back( stone1 );
		}  
		// �Ȃ��葐�F3��
		else if ( num < probability[ 3 ] ) {
			_items.push_back( herb5 );
		}   
		// �Ԃ��Ƃё��F3��
		else if ( num < probability[ 4 ] ) {
			_items.push_back( herb6 );
		} 
		// ���тꑐ�F5��
		else if ( num < probability[ 5 ] ) {
			_items.push_back( herb8 );
		}  
		// ���ʂ̎w�ցF10��
		else if ( num < probability[ 6 ] ) {
			_items.push_back( ring1 );
		}  
		// �؂̏�F10��
		else if ( num < probability[ 7 ] ) {
			_items.push_back( rod1 );
		} 
		// ���̌��F7��
		else if ( num < probability[ 8 ] ) {
			_items.push_back( sword1 );
		}  
		// �����΁F10��
		else if ( num < probability[ 9 ] ) {
			_items.push_back( stone2 );
		}   
		// �����̎w�ցF1��
		else if ( num < probability[ 10 ] ) {
			_items.push_back( ring2 );
		}  
		// �����̎w�ցF1��
		else if ( num < probability[ 11 ] ) {
			_items.push_back( ring3 );
		}  
		// ���̎w�ցF1��
		else if ( num < probability[ 12 ] ) {
			_items.push_back( ring4 );
		}  
		// �����̐΁F2��
		else if ( num < probability[ 13 ] ) {
			_items.push_back( stone3 );
		}  
		// ���������F1��
		else if ( num < probability[ 14 ] ) {
			_items.push_back( meat4 );
		}
		// ��򑐁F3��
		else if ( num < probability[ 15 ] ) {
			_items.push_back( herb2 );
		}  
		// ���݁F1��
		else {
			_items.push_back( gomi1 );
		}  
	}
}

void Item::createFloor3( ) {
	// �o�������
	_start_item_num = 10 + rand( ) % 3;       // 10 �` 12��:8����
	// �o��������
	ITEM_DATA herb1  = getItemDataForID( HERB1 );
	ITEM_DATA herb2  = getItemDataForID( HERB2 );
	ITEM_DATA herb5  = getItemDataForID( HERB5 );
	ITEM_DATA herb6  = getItemDataForID( HERB6 );
	ITEM_DATA herb7  = getItemDataForID( HERB7 );
	ITEM_DATA meat1  = getItemDataForID( MEAT1 );
	ITEM_DATA meat2  = getItemDataForID( MEAT2 );
	ITEM_DATA meat4  = getItemDataForID( MEAT4 );
	ITEM_DATA ring1  = getItemDataForID( RING1 );
	ITEM_DATA ring2  = getItemDataForID( RING2 );
	ITEM_DATA ring3  = getItemDataForID( RING3 );
	ITEM_DATA ring4  = getItemDataForID( RING4 );
	ITEM_DATA rod1   = getItemDataForID( ROD1 );
	ITEM_DATA rod2   = getItemDataForID( ROD2 );
	ITEM_DATA rod4   = getItemDataForID( ROD4 );
	ITEM_DATA sword1 = getItemDataForID( SWORD1 );
	ITEM_DATA sword2 = getItemDataForID( SWORD2 );
	ITEM_DATA stone1 = getItemDataForID( STONE1 );
	ITEM_DATA stone2 = getItemDataForID( STONE2 );
	ITEM_DATA stone3 = getItemDataForID( STONE3 );
	ITEM_DATA gomi1  = getItemDataForID( GARBAGE1 );
	ITEM_DATA gomi2  = getItemDataForID( GARBAGE2 );
	
	// �A�C�e���̊m��
	int probability[ ] = { 1700, 2700, 3700, 4000, 4300, 4900,
						   5900, 6900, 7600, 8600, 8610, 8620,
						   8630, 8930, 9030, 9330, 9630, 9730,
						   9830, 9880, 9980  };
	for ( int i = 0; i < _start_item_num; i++ ) {
		// �o������m��
		int num = rand( ) % 10000;
		// �򑐁F17��
		if ( num < probability[ 0 ] ) {
			_items.push_back( herb1 );
		} 
		// �b�̓��F10��
		else if ( num < probability[ 1 ] ) {
			_items.push_back( meat1 );
		}   
		// �Ă��΁F10��
		else if ( num < probability[ 2 ] ) {
			_items.push_back( stone1 );
		}  
		// �Ȃ��葐�F3��
		else if ( num < probability[ 3 ] ) {
			_items.push_back( herb5 );
		}   
		// �Ԃ��Ƃё��F3��
		else if ( num < probability[ 4 ] ) {
			_items.push_back( herb6 );
		} 
		// �ő��F6��
		else if ( num < probability[ 5 ] ) {
			_items.push_back( herb7 );
		}  
		// ���ʂ̎w�ցF10��
		else if ( num < probability[ 6 ] ) {
			_items.push_back( ring1 );
		}  
		// �؂̏�F10��
		else if ( num < probability[ 7 ] ) {
			_items.push_back( rod1 );
		} 
		// ���̌��F7��
		else if ( num < probability[ 8 ] ) {
			_items.push_back( sword1 );
		}  
		// �����΁F10��
		else if ( num < probability[ 9 ] ) {
			_items.push_back( stone2 );
		}   
		// �����̎w�ցF0.1��
		else if ( num < probability[ 10 ] ) {
			_items.push_back( ring2 );
		}  
		// �����̎w�ցF0.1��
		else if ( num < probability[ 11 ] ) {
			_items.push_back( ring3 );
		}  
		// ���̎w�ցF0.1��
		else if ( num < probability[ 12 ] ) {
			_items.push_back( ring4 );
		}  
		// �����̐΁F3��
		else if ( num < probability[ 13 ] ) {
			_items.push_back( stone3 );
		}  
		// ���������F1��
		else if ( num < probability[ 14 ] ) {
			_items.push_back( meat4 );
		}
		// ��򑐁F3��
		else if ( num < probability[ 15 ] ) {
			_items.push_back( herb2 );
		}
		// �傫�ȓ��F3��
		else if ( num < probability[ 16 ] ) {
			_items.push_back( meat2 );
		}
		// ���̏�F1��
		else if ( num < probability[ 17 ] ) {
			_items.push_back( rod2 );
		}
		// ���[�v�̏�F1��
		else if ( num < probability[ 18 ] ) {
			_items.push_back( rod4 );
		}
		// �����̌��F0.5��
		else if ( num < probability[ 19 ] ) {
			_items.push_back( sword2 );
		}
		// ���݁F1��
		else if ( num < probability[ 20 ] ) {
			_items.push_back( gomi1 );
		}  
		// �㎿�Ȃ��݁F0.2��
		else {
			_items.push_back( gomi2 );
		}  
	}
}

void Item::createFloor4( ) {
	// �o�������
	_start_item_num = 10 + rand( ) % 6;       // 10 �` 15��:10����
	// �o��������
	ITEM_DATA herb1  = getItemDataForID( HERB1 );
	ITEM_DATA herb2  = getItemDataForID( HERB2 );
	ITEM_DATA herb3  = getItemDataForID( HERB3 );
	ITEM_DATA herb5  = getItemDataForID( HERB5 );
	ITEM_DATA herb8  = getItemDataForID( HERB8 );
	ITEM_DATA herb9  = getItemDataForID( HERB9 );
	ITEM_DATA meat1  = getItemDataForID( MEAT1 );
	ITEM_DATA meat2  = getItemDataForID( MEAT2 );
	ITEM_DATA meat3  = getItemDataForID( MEAT3 );
	ITEM_DATA meat4  = getItemDataForID( MEAT4 );
	ITEM_DATA ring5  = getItemDataForID( RING5 );
	ITEM_DATA rod2   = getItemDataForID( ROD2 );
	ITEM_DATA rod3   = getItemDataForID( ROD3 );
	ITEM_DATA rod4   = getItemDataForID( ROD4 );
	ITEM_DATA sword2 = getItemDataForID( SWORD2 );
	ITEM_DATA sword3 = getItemDataForID( SWORD3 );
	ITEM_DATA sword4 = getItemDataForID( SWORD4 );
	ITEM_DATA stone1 = getItemDataForID( STONE1 );
	ITEM_DATA stone2 = getItemDataForID( STONE2 );
	ITEM_DATA stone3 = getItemDataForID( STONE3 );
	ITEM_DATA stone6 = getItemDataForID( STONE6 );
	ITEM_DATA gomi1  = getItemDataForID( GARBAGE1 );
	ITEM_DATA gomi2  = getItemDataForID( GARBAGE2 );
	
	// �A�C�e���̊m��
	int probability[ ] = { 1500, 3000, 3300, 4800, 5450, 6250,
						   7250, 7550, 7650, 7950, 8250, 8350,
						   8450, 9450, 9550, 9749, 9948, 9958,
						   9968, 9978, 9979, 9980  };
	for ( int i = 0; i < _start_item_num; i++ ) {
		// �o������m��
		int num = rand( ) % 10000;
		// �򑐁F15��
		if ( num < probability[ 0 ] ) {
			_items.push_back( herb1 );
		} 
		// �b�̓��F15��
		else if ( num < probability[ 1 ] ) {
			_items.push_back( meat1 );
		}   
		// �Ă��΁F3��
		else if ( num < probability[ 2 ] ) {
			_items.push_back( stone1 );
		}  
		// �Ȃ��葐�F15��
		else if ( num < probability[ 3 ] ) {
			_items.push_back( herb5 );
		}   
		// ���тꑐ�F6.5��
		else if ( num < probability[ 4 ] ) {
			_items.push_back( herb8 );
		} 
		// ���f���F8��
		else if ( num < probability[ 5 ] ) {
			_items.push_back( herb9 );
		} 
		// �����΁F10��
		else if ( num < probability[ 9 ] ) {
			_items.push_back( stone2 );
		}
		// �����̐΁F3��
		else if ( num < probability[ 10 ] ) {
			_items.push_back( stone3 );
		}  
		// ���������F1��
		else if ( num < probability[ 11 ] ) {
			_items.push_back( meat4 );
		}
		// ��򑐁F3��
		else if ( num < probability[ 12 ] ) {
			_items.push_back( herb2 );
		}
		// �傫�ȓ��F3��
		else if ( num < probability[ 13 ] ) {
			_items.push_back( meat2 );
		}
		// ���̏�F1��
		else if ( num < probability[ 14 ] ) {
			_items.push_back( rod2 );
		}
		// ���[�v�̏�F1��
		else if ( num < probability[ 15 ] ) {
			_items.push_back( rod4 );
		}
		// �����̌��F10��
		else if ( num < probability[ 16 ] ) {
			_items.push_back( sword2 );
		}
		// ���݁F1��
		else if ( num < probability[ 17 ] ) {
			_items.push_back( gomi1 );
		}  
		// ����򑐁F1.99��
		else if ( num < probability[ 17 ] ) {
			_items.push_back( herb3 );
		}  
		// ����X�����[�X�F1.99��
		else if ( num < probability[ 17 ] ) {
			_items.push_back( meat3 );
		}  
		// �n���̎w�ցF0.1��
		else if ( num < probability[ 17 ] ) {
			_items.push_back( ring5 );
		}  
		// �������F0.1��
		else if ( num < probability[ 17 ] ) {
			_items.push_back( sword3 );
		}  
		// �喂���΁F0.1��
		else if ( num < probability[ 17 ] ) {
			_items.push_back( stone6 );
		}  
		// �g���C�\�[�h�F0.01��
		else if ( num < probability[ 17 ] ) {
			_items.push_back( sword4 );
		}  
		// �����̏�F0.01��
		else if ( num < probability[ 17 ] ) {
			_items.push_back( rod3 );
		}  
		// �㎿�Ȃ��݁F0.2��
		else {
			_items.push_back( gomi2 );
		}  
	}
}

void Item::update( ) {
	draw( );
	pickUPItem( );
	if ( _foot == true ) {
		for ( unsigned  int i = 0; i < _items.size( ); i++ ) {
			if ( _floor->getPlayerTile( ).x == _items.at( i ).pos.x && _floor->getPlayerTile( ).y == _items.at( i ).pos.y ) {
				_network->setSendOnItem( _items.at( i ).type, false );
				_foot = false;
			}
		}
	}
	// �`����W�̈ړ�
	if ( _throw == true ) {
		_items.at( _throw_num ).draw_pos = throwMove( _items.at( _throw_num ).draw_pos, _items.at( _throw_num ).pos, _items.at( _throw_num ).pre_pos );
	}

	if ( isEndThrow( ) == true ) {
		// �G�l�~�[�Ɍ������ăA�C�e���𓊂������ǂ���
		if ( _throw_item_toward_enemy == true ) {
			itemHitEnemy( );
		}
		_turn_end = true;
	}
}

void Item::draw( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	for ( unsigned int i = 0; i < _items.size( ); i++ ) {
		viewer->drawPolygonFloor( _items.at( i ).draw_pos, _shadow_image );
		viewer->drawModel( _items.at( i ).model_hundle );
		if ( _items.at( i ).type.id == ITEM_ID::ROD1 ||
			 _items.at( i ).type.id == ITEM_ID::ROD2 ||
			 _items.at( i ).type.id == ITEM_ID::ROD3 ||
			 _items.at( i ).type.id == ITEM_ID::ROD4 ) {
			viewer->modelSetPos( _items.at( i ).model_hundle, _items.at( i ).draw_pos + Vector( TILE_SIZE / 2, 0.0f, TILE_SIZE / 2 ) );
		} else {
			viewer->modelSetPos( _items.at( i ).model_hundle, _items.at( i ).draw_pos );
		}
	}
}

Vector Item::getInitPos( ) {
	Floor::TILE tile;
	// �����_���ȃ^�C�����擾
	while ( true ) {
		tile = _floor->getRandomFloor( );
		if ( tile.item_exist == false && tile.stair_exist == false && tile.myistery_type == Floor::MYSTERY_TILE::NONE_MISTERY ) {
			break;
		} 
	}
	_floor->setItemExist( tile.x, tile.y, true );
	return tile.pos;
}

void Item::abovePlayer( int x, int y ) {
	// �A�C�e���ɏ�����������Ƃ�Controller���ɑ���
	for ( unsigned  int i = 0; i < _items.size( ); i++ ) {
		if ( x == _items.at( i ).pos.x && y == _items.at( i ).pos.y ) {
			_network->setSendOnItem( _items.at( i ).type, true );
		}
	}
}

void Item::itemAction( MOVE_DIR move_dir ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	SoundPtr sound = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );
	// ����
	if ( _network->getItemAction( ) == NetworkApp::ITEM_ACTION::EXCHANGE ) {
		for ( unsigned  int i = 0; i < _items.size( ); i++ ) {
			if ( _floor->getPlayerTile( ).x == _items.at( i ).pos.x && _floor->getPlayerTile( ).y == _items.at( i ).pos.y ) {
				// �󂯎�����A�C�e���𐶐�
				ITEM_DATA change_item = getItemDataForID( _network->getItemType( ).id );
				change_item.type = _network->getItemType( );
				change_item.draw_pos = _items.at( i ).draw_pos;
				change_item.pre_pos = change_item.draw_pos;
				change_item.pos = _items.at( i ).pos;
				viewer->modelSetScale( _items.at( i ).model_hundle, _items.at( i ).scale.x, _items.at( i ).scale.y, _items.at( i ).scale.z );
				viewer->modelSetRotation( _items.at( i ).model_hundle, _items.at( i ).rotate.x, _items.at( i ).rotate.y, _items.at( i ).rotate.z );
				_items.at( _items.size( ) - 1 ) = change_item;
			}
		}
	}
	// �u��
	else if ( _network->getItemAction( ) == NetworkApp::ITEM_ACTION::PUT ) {
		_foot = true;
		// �󂯎�����A�C�e���𐶐�
		ITEM_DATA change_item = getItemDataForID( _network->getItemType( ).id );
		change_item.draw_pos = _floor->getPlayerTile( ).pos;
		change_item.pre_pos = change_item.draw_pos;
		change_item.pos.x = _floor->getPlayerTile( ).x;
		change_item.pos.y = _floor->getPlayerTile( ).y;
		viewer->modelSetScale( change_item.model_hundle, change_item.scale.x, change_item.scale.y, change_item.scale.z );
		viewer->modelSetRotation( change_item.model_hundle, change_item.rotate.x, change_item.rotate.y, change_item.rotate.z );
		_items.push_back( change_item );
		_messageLog->createFont( "", "",  change_item.type.name, 0, MessageLog::PUT_ITEM );
		_floor->setItemExist( change_item.pos.x, change_item.pos.y, true );
		for ( unsigned  int i = 0; i < _items.size( ); i++ ) {
			_network->setSendChipData( NetworkApp::MAP_CHIP_TYPE::ITEM, _items.at( i ).pos, 0, false );
		}
	}
	// �g��
	else if ( _network->getItemAction( ) == NetworkApp::ITEM_ACTION::USE ) {
		// �󂯎�����A�C�e���������̂��������ꍇ
		if ( _network->getItemType( ).id == ITEM_ID::ROD3 ) {
			sound->backgrondPlaySound( Sound::ATTACK );
			_item_damage = 100;
			_use_super_flame_rod = true;
			_effect->startSupperFlameEffect( );
			// �����Ă�����̂��g��
			if ( _network->isFootItem( ) ) {
				for ( unsigned  int i = 0; i < _items.size( ); i++ ) {
					if ( _floor->getPlayerTile( ).x == _items.at( i ).pos.x && _floor->getPlayerTile( ).y == _items.at( i ).pos.y ) {
						if ( _items.at( i ).type.amount < 1 ) {
							_floor->setItemExist( _items.at( i ).pos.x, _items.at( i ).pos.y, false );
							_items.erase( _items.begin( ) + i );
						}
						_items.at( i ).type.amount -= 1;
					}
				}
				_items.shrink_to_fit( );
			}
		}
		// �󂯎�����A�C�e�������̂��������ꍇ
		if ( _network->getItemType( ).id == ITEM_ID::ROD2 ) {
			sound->backgrondPlaySound( Sound::ATTACK );
			_item_damage = 25;
			_use_flame_rod = true;
			// �����Ă�����̂��g��
			if ( _network->isFootItem( ) ) {
				for ( unsigned  int i = 0; i < _items.size( ); i++ ) {
					if ( _floor->getPlayerTile( ).x == _items.at( i ).pos.x && _floor->getPlayerTile( ).y == _items.at( i ).pos.y ) {
						if ( _items.at( i ).type.amount < 1 ) {
							_floor->setItemExist( _items.at( i ).pos.x, _items.at( i ).pos.y, false );
							_items.erase( _items.begin( ) + i );
						}
						_items.at( i ).type.amount -= 1;
					}
				}
				_items.shrink_to_fit( );
			}
			void ( Item::* funcArray[ ] )( ) = {
				&Item::swingNone,
				&Item::swingLowerLeft,
				&Item::swingLower,
				&Item::swingLowerRight,
				&Item::swingLeft,
				&Item::swingWait,
				&Item::swingRight,
				&Item::swingUpperLeft,
				&Item::swingUpper,
				&Item::swingUpperRight,
			};
			void ( Item::* func )( ) = funcArray[ move_dir ];
			( this->*func )( );
		}
		// �󂯎�����A�C�e�������[�v�̂��������ꍇ
		if ( _network->getItemType( ).id == ITEM_ID::ROD4 ) {
			_item_damage = 0;
			_use_warp_rod = true;
			// �����Ă�����̂��g��
			if ( _network->isFootItem( ) ) {
				for ( unsigned  int i = 0; i < _items.size( ); i++ ) {
					if ( _floor->getPlayerTile( ).x == _items.at( i ).pos.x && _floor->getPlayerTile( ).y == _items.at( i ).pos.y ) {
						if ( _items.at( i ).type.amount < 1 ) {
							_floor->setItemExist( _items.at( i ).pos.x, _items.at( i ).pos.y, false );
							_items.erase( _items.begin( ) + i );
						}
						_items.at( i ).type.amount -= 1;
					}
				}
				_items.shrink_to_fit( );
			}
			void ( Item::* funcArray[ ] )( ) = {
				&Item::swingNone,
				&Item::swingLowerLeft,
				&Item::swingLower,
				&Item::swingLowerRight,
				&Item::swingLeft,
				&Item::swingWait,
				&Item::swingRight,
				&Item::swingUpperLeft,
				&Item::swingUpper,
				&Item::swingUpperRight,
			};
			void ( Item::* func )( ) = funcArray[ move_dir ];
			( this->*func )( );
		}
		// �����̃A�C�e�����g���ꍇ
		if ( _network->isFootItem( ) == true ) {
			for ( unsigned  int i = 0; i < _items.size( ); i++ ) {
				if ( _floor->getPlayerTile( ).x == _items.at( i ).pos.x && _floor->getPlayerTile( ).y == _items.at( i ).pos.y ) {
					_floor->setItemExist( _items.at( i ).pos.x, _items.at( i ).pos.y, false );
					_items.erase( _items.begin( ) + i );
				}
			}
			_items.shrink_to_fit( );
		}
		for ( unsigned  int i = 0; i < _items.size( ); i++ ) {
			_network->setSendChipData( NetworkApp::MAP_CHIP_TYPE::ITEM, _items.at( i ).pos, 0, false );
		}
	}
	// ����
	else if ( _network->getItemAction( ) == NetworkApp::ITEM_ACTION::EQUIPMENT ) {
		// �����̃A�C�e�����g���ꍇ
		if ( _network->isFootItem( ) == true ) {
			for ( unsigned  int i = 0; i < _items.size( ); i++ ) {
				if ( _floor->getPlayerTile( ).x == _items.at( i ).pos.x && _floor->getPlayerTile( ).y == _items.at( i ).pos.y ) {
					_floor->setItemExist( _items.at( i ).pos.x, _items.at( i ).pos.y, false );
					_items.erase( _items.begin( ) + i );
				}
				_network->setSendChipData( NetworkApp::MAP_CHIP_TYPE::ITEM, _items.at( i ).pos, 0, false );
			}
			_items.shrink_to_fit( );
		}
	}
}

void Item::pickUPItem( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	SoundPtr sound = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );
	//  �����Ă���A�C�e�����E��
	for ( unsigned  int i = 0; i < _items.size( ); i++ ) {
		if ( _floor->getPlayerTile( ).x == _items.at( i ).pos.x && _floor->getPlayerTile( ).y == _items.at( i ).pos.y ) {	
			if ( _network->isOnItem( ) == NetworkApp::ON_ITEM::NO ||  _network->getItemAction( ) == NetworkApp::ITEM_ACTION::PICK_UP ) {
				_messageLog->createFont( "", "",  _items.at( i ).type.name, 0, MessageLog::PICK_ITEM );
				sound->backgrondPlaySound( Sound::PICK_UP_ITEM );
				_floor->setItemExist( _items.at( i ).pos.x, _items.at( i ).pos.y, false );
				_items.erase( _items.begin( ) + i );
				if ( _items.size( ) > 0 ) {
					for ( unsigned int j = 0; j < _items.size( ); j++ ) {
						_network->setSendChipData( NetworkApp::MAP_CHIP_TYPE::ITEM, _items.at( j ).pos, 0, false );
					}
				} else {
					_network->setSendChipData( NetworkApp::MAP_CHIP_TYPE::ITEM, Vector2( 0, 0 ), 0, true );
				}
			} else if ( _network->isOnItem( ) == NetworkApp::ON_ITEM::YES ) {
				_messageLog->createFont( "", "",  _items.at( i ).type.name, 0, MessageLog::ON_THE_ITEM );
			}
		}
	}
	_items.shrink_to_fit( );
}

void Item::throwItem( MOVE_DIR move_dir ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	// �����Ă�����̂𓊂���
	if ( _network->isFootItem( ) ) {
		// �v���C���[�̌����ɂ���ē����������ς���
		void ( Item::* funcArray[ ] )( ITEM_DATA* ) = {
			&Item::throwNone,
			&Item::throwLowerLeft,
			&Item::throwLower,
			&Item::throwLowerRight,
			&Item::throwLeft,
			&Item::throwWait,
			&Item::throwRight,
			&Item::throwUpperLeft,
			&Item::throwUpper,
			&Item::throwUpperRight,
		};
		for ( unsigned  int i = 0; i < _items.size( ); i++ ) {
			if ( _floor->getPlayerTile( ).x == _items.at( i ).pos.x && _floor->getPlayerTile( ).y == _items.at( i ).pos.y ) {
				_floor->setItemExist( _items.at( i ).pos.x, _items.at( i ).pos.y, false );
				void ( Item::* func )( ITEM_DATA* ) = funcArray[ move_dir ];
				( this->*func )( &_items.at( i ) );
				_throw_num = i;
			}
			if ( _floor->getPlayerTile( ).x == _items.at( i ).pos.x && _floor->getPlayerTile( ).y == _items.at( i ).pos.y ) {
				_foot = true;
			}
			_network->setSendChipData( NetworkApp::MAP_CHIP_TYPE::ITEM, _items.at( i ).pos, 0, false );
		}
		_throw = true;
	}
	// Controller����󂯎�����A�C�e���𓊂���
	else {
		ITEM_DATA change_item = getItemDataForID( _network->getItemType( ).id );
		change_item.draw_pos = _floor->getPlayerTile( ).pos;
		change_item.pre_pos = change_item.draw_pos;
		change_item.pos.x = _floor->getPlayerTile( ).x;
		change_item.pos.y = _floor->getPlayerTile( ).y;
		viewer->modelSetScale( change_item.model_hundle, change_item.scale.x, change_item.scale.y, change_item.scale.z );
		viewer->modelSetRotation( change_item.model_hundle, change_item.rotate.x, change_item.rotate.y, change_item.rotate.z );
		// �v���C���[�̌����ɂ���ē����������ς���
		void ( Item::* funcArray[ ] )( ITEM_DATA* ) = {
			&Item::throwNone,
			&Item::throwLowerLeft,
			&Item::throwLower,
			&Item::throwLowerRight,
			&Item::throwLeft,
			&Item::throwWait,
			&Item::throwRight,
			&Item::throwUpperLeft,
			&Item::throwUpper,
			&Item::throwUpperRight,
		};
		void ( Item::* func )( ITEM_DATA* ) = funcArray[ move_dir ];
		( this->*func )( &change_item );
		_items.push_back( change_item );
		_throw = true;
		_throw_num = _items.size( ) - 1;
		for ( unsigned  int i = 0; i < _items.size( ); i++ ) {
			if ( _floor->getPlayerTile( ).x == _items.at( i ).pos.x && _floor->getPlayerTile( ).y == _items.at( i ).pos.y ) {
				_foot = true;
			}
			_network->setSendChipData( NetworkApp::MAP_CHIP_TYPE::ITEM, _items.at( i ).pos, 0, false );
		}
	}
}

void Item::throwNone( Item::ITEM_DATA *item ) {
	return;
}

void Item::throwLowerLeft( Item::ITEM_DATA *item ) {
	ITEM_DATA provisional_item = *item;
	int x = _floor->getPlayerTile(  ).x;
	int y = _floor->getPlayerTile(  ).y;
	int pre_x = x;
	int pre_y = y;

	while ( true ) {
		x++;
		y++;
		// �Ă��΂��������ꍇ
		if ( provisional_item.type.id == STONE1 ) {
			// �G�l�~�[�ɂԂ������ꍇ
			if ( _floor->getTile( x, y ).bond == Floor::ENEMY ) {
				provisional_item.pos.x = x - pre_x;
				provisional_item.pos.y = y - pre_y;
				_throw_item_toward_enemy = true;
				_hit_enemy_item = provisional_item.type.id;
				break;
			}
			// �ǂɂԂ������ꍇ
			if ( _floor->getTile( x, y ).type == Floor::WALL ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x - 1, y - 1 ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x - 1 , y - 1 );
					provisional_item.pos.x = pos.x;
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.x = x - 1;
					provisional_item.pos.y = y - 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
			// �����鋗�������E�ɒB�����Ƃ�
			if ( x - pre_x > FLAME_STONE_DISTANCE ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x - 1, y - 1 ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x - 1 , y - 1 );
					provisional_item.pos.x = pos.x;
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.x = x - 1;
					provisional_item.pos.y = y - 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
		} else {
			// �ǂɂԂ������ꍇ
			if ( _floor->getTile( x, y ).type == Floor::WALL ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x - 1, y - 1 ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x - 1 , y - 1 );
					provisional_item.pos.x = pos.x;
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.x = x - 1;
					provisional_item.pos.y = y - 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
			// �����鋗�������E�ɒB�����Ƃ�
			if ( x - pre_x > LIMIT_THROW_DISTANCE ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x - 1, y - 1 ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x - 1 , y - 1 );
					provisional_item.pos.x = pos.x;
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.x = x - 1;
					provisional_item.pos.y = y - 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
			// �G�l�~�[�ɂԂ������ꍇ
			if ( _floor->getTile( x, y ).bond == Floor::ENEMY ) {
				provisional_item.pos.x = x;
				provisional_item.pos.y = y;
				_throw_item_toward_enemy = true;
				_hit_enemy_item = provisional_item.type.id;
				break;
			}
		}
	}
	*item = provisional_item;
}

void Item::throwLower( Item::ITEM_DATA *item ) {
	ITEM_DATA provisional_item = *item;
	int x = _floor->getPlayerTile(  ).x;
	int y = _floor->getPlayerTile(  ).y;
	int pre_y = y;

	while ( true ) {
		y++;
		// �Ă��΂��������ꍇ
		if ( provisional_item.type.id == STONE1 ) {
			// �G�l�~�[�ɂԂ������ꍇ
			if ( _floor->getTile( x, y ).bond == Floor::ENEMY ) {
				provisional_item.pos.y = y;
				_throw_item_toward_enemy = true;
				_hit_enemy_item = provisional_item.type.id;
				break;
			}
			// �ǂɂԂ������ꍇ
			if ( _floor->getTile( x, y ).type == Floor::WALL ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x, y - 1 ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x , y - 1 );
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.y = y - 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
			// �����鋗�������E�ɒB�����Ƃ�
			if ( y - pre_y > FLAME_STONE_DISTANCE ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x, y - 1 ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x , y - 1 );
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.y = y - 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
		} else {
			// �ǂɂԂ������ꍇ
			if ( _floor->getTile( x, y ).type == Floor::WALL ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x, y - 1 ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x , y - 1 );
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.y = y - 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
			// �����鋗�������E�ɒB�����Ƃ�
			if ( y - pre_y > LIMIT_THROW_DISTANCE ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x, y - 1 ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x , y - 1 );
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.y = y - 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
			// �G�l�~�[�ɂԂ������ꍇ
			if ( _floor->getTile( x, y ).bond == Floor::ENEMY ) {
				provisional_item.pos.y = y;
				_throw_item_toward_enemy = true;
				_hit_enemy_item = provisional_item.type.id;
				break;
			}
		}
	}
	*item = provisional_item;
}

void Item::throwLowerRight( Item::ITEM_DATA *item ) {
	ITEM_DATA provisional_item = *item;
	int x = _floor->getPlayerTile(  ).x;
	int y = _floor->getPlayerTile(  ).y;
	int pre_x = x;
	int pre_y = y;

	while ( true ) {
		x--;
		y++;
		// �Ă��΂��������ꍇ
		if ( provisional_item.type.id == STONE1 ) {
			// �G�l�~�[�ɂԂ������ꍇ
			if ( _floor->getTile( x, y ).bond == Floor::ENEMY ) {
				provisional_item.pos.x = x;
				provisional_item.pos.y = y;
				_throw_item_toward_enemy = true;
				_hit_enemy_item = provisional_item.type.id;
				break;
			}
			// �ǂɂԂ������ꍇ
			if ( _floor->getTile( x, y ).type == Floor::WALL ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x + 1, y - 1 ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x + 1, y - 1 );
					provisional_item.pos.x = pos.x;
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.x = x + 1;
					provisional_item.pos.y = y - 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
			// �����鋗�������E�ɒB�����Ƃ�
			if ( pre_x - x > FLAME_STONE_DISTANCE ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x + 1, y - 1 ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x + 1, y - 1 );
					provisional_item.pos.x = pos.x;
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.x = x + 1;
					provisional_item.pos.y = y - 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
		} else {
			// �ǂɂԂ������ꍇ
			if ( _floor->getTile( x, y ).type == Floor::WALL ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x + 1, y - 1 ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x + 1, y - 1 );
					provisional_item.pos.x = pos.x;
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.x = x + 1;
					provisional_item.pos.y = y - 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
			// �����鋗�������E�ɒB�����Ƃ�
			if ( pre_x - x > LIMIT_THROW_DISTANCE ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x + 1, y - 1 ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x + 1, y - 1 );
					provisional_item.pos.x = pos.x;
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.x = x + 1;
					provisional_item.pos.y = y - 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
			// �G�l�~�[�ɂԂ������ꍇ
			if ( _floor->getTile( x, y ).bond == Floor::ENEMY ) {
				provisional_item.pos.x = x;
				provisional_item.pos.y = y;
				_throw_item_toward_enemy = true;
				_hit_enemy_item = provisional_item.type.id;
				break;
			}
		}
	}
	*item = provisional_item;
}

void Item::throwLeft( Item::ITEM_DATA *item ) {
	ITEM_DATA provisional_item = *item;
	int x = _floor->getPlayerTile(  ).x;
	int y = _floor->getPlayerTile(  ).y;
	int pre_x = x;

	while ( true ) {
		x++;
		// �Ă��΂��������ꍇ
		if ( provisional_item.type.id == STONE1 ) {
			// �G�l�~�[�ɂԂ������ꍇ
			if ( _floor->getTile( x, y ).bond == Floor::ENEMY ) {
				provisional_item.pos.x = x;
				_throw_item_toward_enemy = true;
				_hit_enemy_item = provisional_item.type.id;
				break;
			}
			// �ǂɂԂ������ꍇ
			if ( _floor->getTile( x, y ).type == Floor::WALL ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x - 1, y ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x - 1, y );
					provisional_item.pos.x = pos.x;
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.x = x - 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
			// �����鋗�������E�ɒB�����Ƃ�
			if ( x - pre_x > FLAME_STONE_DISTANCE ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x - 1, y ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x - 1, y );
					provisional_item.pos.x = pos.x;
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.x = x - 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
		} else {
			// �ǂɂԂ������ꍇ
			if ( _floor->getTile( x, y ).type == Floor::WALL ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x - 1, y ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x - 1, y );
					provisional_item.pos.x = pos.x;
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.x = x - 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
			// �����鋗�������E�ɒB�����Ƃ�
			if ( x - pre_x > LIMIT_THROW_DISTANCE ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x - 1, y ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x - 1, y );
					provisional_item.pos.x = pos.x;
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.x = x - 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
			// �G�l�~�[�ɂԂ������ꍇ
			if ( _floor->getTile( x, y ).bond == Floor::ENEMY ) {
				provisional_item.pos.x = x;
				_throw_item_toward_enemy = true;
				_hit_enemy_item = provisional_item.type.id;
				break;
			}
		}
	}
	*item = provisional_item;
}

void Item::throwWait( Item::ITEM_DATA *item ) {
	// �������Ȃ�
	return;
}

void Item::throwRight( Item::ITEM_DATA *item ) {
	ITEM_DATA provisional_item = *item;
	int x = _floor->getPlayerTile(  ).x;
	int y = _floor->getPlayerTile(  ).y;
	int pre_x = x;

	while ( true ) {
		x--;
		// �Ă��΂��������ꍇ
		if ( provisional_item.type.id == STONE1 ) {
			// �G�l�~�[�ɂԂ������ꍇ
			if ( _floor->getTile( x, y ).bond == Floor::ENEMY ) {
				provisional_item.pos.x = x;
				_throw_item_toward_enemy = true;
				_hit_enemy_item = provisional_item.type.id;
				break;
			}
			// �ǂɂԂ������ꍇ
			if ( _floor->getTile( x, y ).type == Floor::WALL ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x + 1, y ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x + 1, y );
					provisional_item.pos.x = pos.x;
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.x = x + 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
			// �����鋗�������E�ɒB�����Ƃ�
			if ( pre_x - x > FLAME_STONE_DISTANCE ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x + 1, y ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x + 1, y );
					provisional_item.pos.x = pos.x;
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.x = x + 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
		} else {
			// �G�l�~�[�ɂԂ������ꍇ
			if ( _floor->getTile( x, y ).bond == Floor::ENEMY ) {
				provisional_item.pos.x = x;
				_throw_item_toward_enemy = true;
				_hit_enemy_item = provisional_item.type.id;
				break;
			}
			// �ǂɂԂ������ꍇ
			if ( _floor->getTile( x, y ).type == Floor::WALL ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x + 1, y ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x + 1, y );
					provisional_item.pos.x = pos.x;
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.x = x + 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
			// �����鋗�������E�ɒB�����Ƃ�
			if ( pre_x - x > LIMIT_THROW_DISTANCE ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x + 1, y ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x + 1, y );
					provisional_item.pos.x = pos.x;
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.x = x + 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
		}
	}
	*item = provisional_item;
}

void Item::throwUpperLeft( Item::ITEM_DATA *item ) {
	ITEM_DATA provisional_item = *item;
	int x = _floor->getPlayerTile(  ).x;
	int y = _floor->getPlayerTile(  ).y;
	int pre_x = x;
	int pre_y = y;

	while ( true ) {
		x++;
		y--;
		// �Ă��΂��������ꍇ
		if ( provisional_item.type.id == STONE1 ) {
			// �G�l�~�[�ɂԂ������ꍇ
			if ( _floor->getTile( x, y ).bond == Floor::ENEMY ) {
				provisional_item.pos.x = x;
				provisional_item.pos.y = y;
				_throw_item_toward_enemy = true;
				_hit_enemy_item = provisional_item.type.id;
				break;
			}
			// �ǂɂԂ������ꍇ
			if ( _floor->getTile( x, y ).type == Floor::WALL ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x - 1, y + 1 ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x - 1, y + 1 );
					provisional_item.pos.x = pos.x;
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.x = x - 1;
					provisional_item.pos.y = y + 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
			// �����鋗�������E�ɒB�����Ƃ�
			if ( x - pre_x > FLAME_STONE_DISTANCE ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x - 1, y + 1 ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x - 1, y + 1 );
					provisional_item.pos.x = pos.x;
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.x = x - 1;
					provisional_item.pos.y = y + 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
		} else {
			// �G�l�~�[�ɂԂ������ꍇ
			if ( _floor->getTile( x, y ).bond == Floor::ENEMY ) {
				provisional_item.pos.x = x;
				provisional_item.pos.y = y;
				_throw_item_toward_enemy = true;
				_hit_enemy_item = provisional_item.type.id;
				break;
			}
			// �ǂɂԂ������ꍇ
			if ( _floor->getTile( x, y ).type == Floor::WALL ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x - 1, y + 1 ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x - 1, y + 1 );
					provisional_item.pos.x = pos.x;
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.x = x - 1;
					provisional_item.pos.y = y + 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
			// �����鋗�������E�ɒB�����Ƃ�
			if ( x - pre_x > LIMIT_THROW_DISTANCE ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x - 1, y + 1 ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x - 1, y + 1 );
					provisional_item.pos.x = pos.x;
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.x = x - 1;
					provisional_item.pos.y = y + 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
		}
	}
	*item = provisional_item;
}

void Item::throwUpper( Item::ITEM_DATA *item ) {
	ITEM_DATA provisional_item = *item;
	int x = _floor->getPlayerTile(  ).x;
	int y = _floor->getPlayerTile(  ).y;
	int pre_y = y;

	while ( true ) {
		y--;
		// �Ă��΂��������ꍇ
		if ( provisional_item.type.id == STONE1 ) {
			// �G�l�~�[�ɂԂ������ꍇ
			if ( _floor->getTile( x, y ).bond == Floor::ENEMY ) {
				provisional_item.pos.y = y;
				_throw_item_toward_enemy = true;
				_hit_enemy_item = provisional_item.type.id;
				break;
			}
			// �ǂɂԂ������ꍇ
			if ( _floor->getTile( x, y ).type == Floor::WALL ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x, y + 1 ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x, y + 1 );
					provisional_item.pos.x = pos.x;
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.y = y + 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
			// �����鋗�������E�ɒB�����Ƃ�
			if ( pre_y - y > FLAME_STONE_DISTANCE ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x, y + 1 ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x, y + 1 );
					provisional_item.pos.x = pos.x;
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.y = y + 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
		} else {
			// �G�l�~�[�ɂԂ������ꍇ
			if ( _floor->getTile( x, y ).bond == Floor::ENEMY ) {
				provisional_item.pos.y = y;
				_throw_item_toward_enemy = true;
				_hit_enemy_item = provisional_item.type.id;
				break;
			}
			// �ǂɂԂ������ꍇ
			if ( _floor->getTile( x, y ).type == Floor::WALL ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x, y + 1 ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x, y + 1 );
					provisional_item.pos.x = pos.x;
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.y = y + 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
			// �����鋗�������E�ɒB�����Ƃ�
			if ( pre_y - y > LIMIT_THROW_DISTANCE ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x, y + 1 ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x, y + 1 );
					provisional_item.pos.x = pos.x;
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.y = y + 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
		}
	}
	*item = provisional_item;
}

void Item::throwUpperRight( Item::ITEM_DATA *item ) {
	ITEM_DATA provisional_item = *item;
	int x = _floor->getPlayerTile(  ).x;
	int y = _floor->getPlayerTile(  ).y;
	int pre_x = x;
	int pre_y = y;

	while ( true ) {
		x--;
		y--;
		// �Ă��΂��������ꍇ
		if ( provisional_item.type.id == STONE1 ) {
			// �G�l�~�[�ɂԂ������ꍇ
			if ( _floor->getTile( x, y ).bond == Floor::ENEMY ) {
				provisional_item.pos.x = x;
				provisional_item.pos.y = y;
				_throw_item_toward_enemy = true;
				_hit_enemy_item = provisional_item.type.id;
				break;
			} 
			// �ǂɂԂ������ꍇ
			if ( _floor->getTile( x, y ).type == Floor::WALL ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x + 1, y + 1 ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x + 1, y + 1 );
					provisional_item.pos.x = pos.x;
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.x = x + 1;
					provisional_item.pos.y = y + 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
			// �����鋗�������E�ɒB�����Ƃ�
			if ( pre_x - x > FLAME_STONE_DISTANCE ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x + 1, y + 1 ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x + 1, y + 1 );
					provisional_item.pos.x = pos.x;
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.x = x + 1;
					provisional_item.pos.y = y + 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
		} else {
			// �G�l�~�[�ɂԂ������ꍇ
			if ( _floor->getTile( x, y ).bond == Floor::ENEMY ) {
				provisional_item.pos.x = x;
				provisional_item.pos.y = y;
				_throw_item_toward_enemy = true;
				_hit_enemy_item = provisional_item.type.id;
				break;
			} 
			// �ǂɂԂ������ꍇ
			if ( _floor->getTile( x, y ).type == Floor::WALL ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x + 1, y + 1 ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x + 1, y + 1 );
					provisional_item.pos.x = pos.x;
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.x = x + 1;
					provisional_item.pos.y = y + 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
			// �����鋗�������E�ɒB�����Ƃ�
			if ( pre_x - x > LIMIT_THROW_DISTANCE ) {
				// �A�C�e���ɂԂ������ꍇ
				if ( _floor->getTile( x + 1, y + 1 ).item_exist == true ) {
					Vector2 pos = displaceItemPos( x + 1, y + 1 );
					provisional_item.pos.x = pos.x;
					provisional_item.pos.y = pos.y;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				} else {
					provisional_item.pos.x = x + 1;
					provisional_item.pos.y = y + 1;
					_floor->setItemExist( provisional_item.pos.x, provisional_item.pos.y, true );
					break;
				}
			}
		}
	}
	*item = provisional_item;
}

Vector2 Item::displaceItemPos( int x, int y ) {
	Vector2 pos;
	int count = 1;
	while ( true ) {
		// �㉺
		for( int i = -count; i <= count; i += ( count * 2 ) ) {
			for( int j = -count; j <= count; j++ ) {
				if ( _floor->getTile( x + i, y + j ).item_exist == false &&
					 _floor->getTile( x + i, y + j ).type != Floor::WALL &&
					 _floor->getTile( x + i, y + j ).stair_exist == false &&
					 _floor->getTile( x + i, y + j ).bond != Floor::PLAYER ) {
					pos.x = x + i;
					pos.y = y + j;
					return pos;
				}
			}
		}
		// ���E
		for( int i = -count; i <= count; i++ ) {
			for( int j = -count; j <= count; j += ( count * 2 ) ) {
				if ( _floor->getTile( x + i, y + j ).item_exist == false &&
					 _floor->getTile( x + i, y + j ).type != Floor::WALL &&
					 _floor->getTile( x + i, y + j ).stair_exist == false &&
					 _floor->getTile( x + i, y + j ).bond != Floor::PLAYER ) {
					pos.x = x + i;
					pos.y = y + j;
					return pos;
				}
			}
		}
		count++;
	}
}

Vector Item::throwMove( Vector draw_pos, Vector2 pos, Vector pre_pos ) {
	// �ړ���̃x�N�g��
	int move_x = ( pos.x * TILE_SIZE - pre_pos.x ) / WALK_ANIM_TIME * 2;
	int move_z = ( pos.y * TILE_SIZE - pre_pos.z ) / WALK_ANIM_TIME * 2;
	// ��
	if ( move_x > 0 ) {
		// ���X�ɓ�����
		draw_pos.x += move_x;
		// �ړI�n���߂�����ړI�n�ɍ��W���Z�b�g
		if ( draw_pos.x > pos.x * TILE_SIZE ) {
			draw_pos.x = pos.x * TILE_SIZE;
			pre_pos.x  = pos.x * TILE_SIZE;
			move_x = 0;
		}
	}
	// �E
	else if ( move_x < 0 ) {
		// ���X�ɓ�����
		draw_pos.x += move_x;
		// �ړI�n���߂�����ړI�n�ɍ��W���Z�b�g
		if ( draw_pos.x < pos.x * TILE_SIZE ) {
			draw_pos.x = pos.x * TILE_SIZE;
			pre_pos.x  = pos.x * TILE_SIZE;
			move_x = 0;
		}
	}
	// �����W���̏ꍇ
	else {
		draw_pos.x = pos.x * TILE_SIZE;
		pre_pos.x  = pos.x * TILE_SIZE;
		move_x = 0;
	}
	// ��
	if ( move_z > 0 ) {
		// ���X�ɓ�����
		draw_pos.z += move_z;
		// �ړI�n���߂�����ړI�n�ɍ��W���Z�b�g
		if ( draw_pos.z > pos.y * TILE_SIZE ) {
			draw_pos.z = pos.y * TILE_SIZE;
			pre_pos.z  = pos.y * TILE_SIZE;
			move_z = 0;
		}
	}
	// ��
	else if ( move_z < 0 ) {
		// ���X�ɓ�����
		draw_pos.z += move_z;
		// �ړI�n���߂�����ړI�n�ɍ��W���Z�b�g
		if ( draw_pos.z < pos.y * TILE_SIZE ) {
			draw_pos.z = pos.y * TILE_SIZE;
			pre_pos.z  = pos.y * TILE_SIZE;
			move_z = 0;
		}
	}
	// �����W���̏ꍇ
	else {
		draw_pos.z = pos.y * TILE_SIZE;
		pre_pos.z  = pos.y * TILE_SIZE;
		move_z = 0;
	}

	if ( move_x == 0 && move_z == 0 && _throw == true ) {
		_throw     = false;
		_end_throw = true;
	}
	return draw_pos;
}

void Item::swingNone( ) {
	return;
}

void Item::swingLowerLeft( ) {
	int x = _floor->getPlayerTile(  ).x;
	int y = _floor->getPlayerTile(  ).y;

	while ( true ) {
		x++;
		y++;
		// �G�l�~�[�ɂԂ������ꍇ
		if ( _floor->getTile( x, y ).bond == Floor::ENEMY ) {
			_hit_enemy_pos.x = x;
			_hit_enemy_pos.y = y;
			break;
		}
		// �ǂɂԂ������ꍇ
		if ( _floor->getTile( x, y ).type == Floor::WALL ) {
			break;
		}
	}
}

void Item::swingLower( ) {
	int x = _floor->getPlayerTile(  ).x;
	int y = _floor->getPlayerTile(  ).y;

	while ( true ) {
		y++;
		// �G�l�~�[�ɂԂ������ꍇ
		if ( _floor->getTile( x, y ).bond == Floor::ENEMY ) {
			_hit_enemy_pos.x = x;
			_hit_enemy_pos.y = y;
			break;
		}
		// �ǂɂԂ������ꍇ
		if ( _floor->getTile( x, y ).type == Floor::WALL ) {
			break;
		}
	}
}

void Item::swingLowerRight( ) {
	int x = _floor->getPlayerTile(  ).x;
	int y = _floor->getPlayerTile(  ).y;

	while ( true ) {
		x--;
		y++;
		// �G�l�~�[�ɂԂ������ꍇ
		if ( _floor->getTile( x, y ).bond == Floor::ENEMY ) {
			_hit_enemy_pos.x = x;
			_hit_enemy_pos.y = y;
			break;
		}
		// �ǂɂԂ������ꍇ
		if ( _floor->getTile( x, y ).type == Floor::WALL ) {
			break;
		}
	}
}

void Item::swingLeft( ) {
	int x = _floor->getPlayerTile(  ).x;
	int y = _floor->getPlayerTile(  ).y;

	while ( true ) {
		x++;
		// �G�l�~�[�ɂԂ������ꍇ
		if ( _floor->getTile( x, y ).bond == Floor::ENEMY ) {
			_hit_enemy_pos.x = x;
			_hit_enemy_pos.y = y;
			break;
		}
		// �ǂɂԂ������ꍇ
		if ( _floor->getTile( x, y ).type == Floor::WALL ) {
			break;
		}
	}
}

void Item::swingWait( ) {
	// �������Ȃ�
	return;
}

void Item::swingRight( ) {
	int x = _floor->getPlayerTile(  ).x;
	int y = _floor->getPlayerTile(  ).y;

	while ( true ) {
		x--;
		// �G�l�~�[�ɂԂ������ꍇ
		if ( _floor->getTile( x, y ).bond == Floor::ENEMY ) {
			_hit_enemy_pos.x = x;
			_hit_enemy_pos.y = y;
			break;
		}
		// �ǂɂԂ������ꍇ
		if ( _floor->getTile( x, y ).type == Floor::WALL ) {
			break;
		}
	}
}

void Item::swingUpperLeft( ) {
	int x = _floor->getPlayerTile(  ).x;
	int y = _floor->getPlayerTile(  ).y;

	while ( true ) {
		x++;
		y--;
		// �G�l�~�[�ɂԂ������ꍇ
		if ( _floor->getTile( x, y ).bond == Floor::ENEMY ) {
			_hit_enemy_pos.x = x;
			_hit_enemy_pos.y = y;
			break;
		}
		// �ǂɂԂ������ꍇ
		if ( _floor->getTile( x, y ).type == Floor::WALL ) {
			break;
		}
	}
}

void Item::swingUpper( ) {
	int x = _floor->getPlayerTile(  ).x;
	int y = _floor->getPlayerTile(  ).y;

	while ( true ) {
		y--;
		// �G�l�~�[�ɂԂ������ꍇ
		if ( _floor->getTile( x, y ).bond == Floor::ENEMY ) {
			_hit_enemy_pos.x = x;
			_hit_enemy_pos.y = y;
			break;
		}
		// �ǂɂԂ������ꍇ
		if ( _floor->getTile( x, y ).type == Floor::WALL ) {
			break;
		}
	}
}

void Item::swingUpperRight( ) {
	int x = _floor->getPlayerTile(  ).x;
	int y = _floor->getPlayerTile(  ).y;

	while ( true ) {
		x--;
		y--;
		// �G�l�~�[�ɂԂ������ꍇ
		if ( _floor->getTile( x, y ).bond == Floor::ENEMY ) {
			_hit_enemy_pos.x = x;
			_hit_enemy_pos.y = y;
			break;
		}
		// �ǂɂԂ������ꍇ
		if ( _floor->getTile( x, y ).type == Floor::WALL ) {
			break;
		}
	}
}

void Item::itemHitEnemy( ) {
	// �A�C�e���ɂԂ������G�l�~�[��I�o
	for ( unsigned  int i = 0; i < _items.size( ); i++ ) {
		if ( _floor->getTile( _items.at( i ).pos.x, _items.at( i ).pos.y ).bond == Floor::ENEMY &&
			 _floor->getTile( _items.at( i ).pos.x, _items.at( i ).pos.y ).pos.x == _items.at( i ).draw_pos.x &&
			 _floor->getTile( _items.at( i ).pos.x, _items.at( i ).pos.y ).pos.z == _items.at( i ).draw_pos.z &&
			 _hit_enemy_item == _items.at( i ).type.id ) {
			// �A�C�e���ɂ���ă_���[�W��ς���
			if ( _items.at( i ).type.id == STONE1 ) {
				_item_damage = 10;
			} else if ( _items.at( i ).type.id == HERB1 ) {
				_item_damage -= 30;
			} else if ( _items.at( i ).type.id == HERB2 ) {
				_item_damage -= 60;
			} else if ( _items.at( i ).type.id == HERB3 ) {
				_item_damage -= 120;
			} else {
				_item_damage = 5;
			}  
			_hit_enemy_pos.x = _items.at( i ).pos.x;
			_hit_enemy_pos.y = _items.at( i ).pos.y;
			_hit_enemy = true;
			_items.erase( _items.begin( ) + i );
			for ( unsigned  int i = 0; i < _items.size( ); i++ ) {
				_network->setSendChipData( NetworkApp::MAP_CHIP_TYPE::ITEM, _items.at( i ).pos, 0, false );
			}
			_throw_item_toward_enemy = false;
			break;
		}
	}
	_items.shrink_to_fit( );
}

bool Item::isEndThrow( ) {
	if ( _end_throw == true ) {
		_end_throw = false;
		return true;
	}
	return false;
}

Vector2 Item::getHitEnemyPos( ) {
	return _hit_enemy_pos;
}

void Item::setInitHitEnemyPos( ) {
	_hit_enemy_pos = Vector2( 0, 0 );
}

ITEM_ID Item::getHitEnemyType( ) {
	return _hit_enemy_item;
}

int Item::getItemDamage( ) {
	return _item_damage;
}

bool Item::isHitEnemy( ) {
	return _hit_enemy;
}

void Item::setHitEnemy( bool hit_enemy ) {
	_hit_enemy = hit_enemy;
}

bool Item::isUseFlameRod( ) {
	return _use_flame_rod;
}

void Item::setUseFlameRod( bool use_rod ) {
	_use_flame_rod = use_rod;
}

bool Item::isUseWarpRod( ) {
	return _use_warp_rod;
}

void Item::setUseWarpRod( bool use_rod ) {
	_use_warp_rod = use_rod;
}

bool Item::isUseSuperFlameRod( ) {
	return _use_super_flame_rod;
}

void Item::setUseSuperFlameRod( bool use_rod ) {
	_use_super_flame_rod = use_rod;
}

bool Item::isTurnEnd( ) {
	return _turn_end;
}

void Item::setTurnEnd( bool turn_end ) {
	_turn_end = turn_end;
}

void Item::deleteAllItem( ) {
	_items.erase( _items.begin( ), _items.end( ) );
	_items.shrink_to_fit( );
}

void Item::setFloorLevel( int floor_level ) {
	_floor_level = floor_level;
}

Item::ITEM_DATA Item::getItemDataForID( ITEM_ID id ) {
	// id�ɂ���ăf�[�^���擾
	ITEM_DATA result;
	for ( int i = 0; i < MAX_ITEM_TYPE; i++ ) {
		if ( _item_table[ i ].type.id == id ) {
			result = _item_table[ i ];
			break;
		}
	}
	
	return result;
}