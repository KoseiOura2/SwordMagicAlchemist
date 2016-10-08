#include "ItemImage.h"
#include "Framework.h"
#include "Viewer.h"

ItemImage::ItemImage( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	_frame = viewer->loadGraph( "work/ctrl_UI/item/frame/frame.png" );
	_big_frame = viewer->loadGraph( "work/ctrl_UI/item/frame/big_frame.png" );
	_frame_equipment = viewer->loadGraph( "work/ctrl_UI/item/frame/frame_equipment.png" );
	_big_frame_equipment = viewer->loadGraph( "work/ctrl_UI/item/frame/big_frame_equipment.png" );
	_frame_foot = viewer->loadGraph( "work/ctrl_UI/item/frame/frame_foot.png" );
	_frame_white = viewer->loadGraph( "work/ctrl_UI/item/frame/frame_white.png" );
	

	int frame_amount[ ] = {
		viewer->loadGraph( "work/ctrl_UI/item/frame/frame_amout_1.png" ),
		viewer->loadGraph( "work/ctrl_UI/item/frame/frame_amout_2.png" ),
		viewer->loadGraph( "work/ctrl_UI/item/frame/frame_amout_3.png" ),
		viewer->loadGraph( "work/ctrl_UI/item/frame/frame_amout_4.png" ),
		viewer->loadGraph( "work/ctrl_UI/item/frame/frame_amout_5.png" ),
		viewer->loadGraph( "work/ctrl_UI/item/frame/frame_amout_6.png" ),
		viewer->loadGraph( "work/ctrl_UI/item/frame/frame_amout_7.png" ),
		viewer->loadGraph( "work/ctrl_UI/item/frame/frame_amout_8.png" ),
		viewer->loadGraph( "work/ctrl_UI/item/frame/frame_amout_9.png" ),
	};
	int big_frame_amout[ ] = {
		viewer->loadGraph( "work/ctrl_UI/item/frame/big_frame_amout_1.png" ),
		viewer->loadGraph( "work/ctrl_UI/item/frame/big_frame_amout_2.png" ),
		viewer->loadGraph( "work/ctrl_UI/item/frame/big_frame_amout_3.png" ),
		viewer->loadGraph( "work/ctrl_UI/item/frame/big_frame_amout_4.png" ),
		viewer->loadGraph( "work/ctrl_UI/item/frame/big_frame_amout_5.png" ),
		viewer->loadGraph( "work/ctrl_UI/item/frame/big_frame_amout_6.png" ),
		viewer->loadGraph( "work/ctrl_UI/item/frame/big_frame_amout_7.png" ),
		viewer->loadGraph( "work/ctrl_UI/item/frame/big_frame_amout_8.png" ),
		viewer->loadGraph( "work/ctrl_UI/item/frame/big_frame_amout_9.png" ),
	};

	for ( int i = 0; i < MAX_AMOUNT; i++ ) {
		_frame_amount[ i ] = frame_amount[ i ];
		_big_frame_amount[ i ] = big_frame_amout[ i ];
	}

	ITEM_IMAGE no_frame_image[ ] = {
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/herb01.png" ),    ITEM_ID::HERB1 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/herb02.png" ),    ITEM_ID::HERB2 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/herb03.png" ),    ITEM_ID::HERB3 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/herb04.png" ),    ITEM_ID::HERB4 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/herb05.png" ),    ITEM_ID::HERB5 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/herb06.png" ),    ITEM_ID::HERB6 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/herb07.png" ),    ITEM_ID::HERB7 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/herb08.png" ),    ITEM_ID::HERB8 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/herb09.png" ),    ITEM_ID::HERB9 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/meat01.png" ),    ITEM_ID::MEAT1 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/meat02.png" ),    ITEM_ID::MEAT2 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/meat03.png" ),    ITEM_ID::MEAT3 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/meat04.png" ),    ITEM_ID::MEAT4 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/ring01.png" ),    ITEM_ID::RING1 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/ring02.png" ),    ITEM_ID::RING2 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/ring03.png" ),    ITEM_ID::RING3 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/ring04.png" ),    ITEM_ID::RING4 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/ring05.png" ),    ITEM_ID::RING5 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/ring06.png" ),    ITEM_ID::RING6 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/rod01.png" ),     ITEM_ID::ROD1 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/rod02.png" ),     ITEM_ID::ROD2 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/rod03.png" ),     ITEM_ID::ROD3 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/rod04.png" ),     ITEM_ID::ROD4 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/sword01.png" ),   ITEM_ID::SWORD1 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/sword02.png" ),   ITEM_ID::SWORD2 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/sword03.png" ),   ITEM_ID::SWORD3 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/sword04.png" ),   ITEM_ID::SWORD4 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/stone01.png" ),   ITEM_ID::STONE1 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/stone02.png" ),   ITEM_ID::STONE2 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/stone03.png" ),   ITEM_ID::STONE3 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/stone04.png" ),   ITEM_ID::STONE4 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/stone05.png" ),   ITEM_ID::STONE5 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/stone06.png" ),   ITEM_ID::STONE6 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/garbage01.png" ), ITEM_ID::GARBAGE1 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/no_frame/garbage02.png" ), ITEM_ID::GARBAGE2 ),
	};
	ITEM_IMAGE item_image[ ] = {
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/herb01.png" ),    ITEM_ID::HERB1 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/herb02.png" ),    ITEM_ID::HERB2 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/herb03.png" ),    ITEM_ID::HERB3 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/herb04.png" ),    ITEM_ID::HERB4 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/herb05.png" ),    ITEM_ID::HERB5 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/herb06.png" ),    ITEM_ID::HERB6 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/herb07.png" ),    ITEM_ID::HERB7 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/herb08.png" ),    ITEM_ID::HERB8 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/herb09.png" ),    ITEM_ID::HERB9 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/meat01.png" ),    ITEM_ID::MEAT1 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/meat02.png" ),    ITEM_ID::MEAT2 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/meat03.png" ),    ITEM_ID::MEAT3 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/meat04.png" ),    ITEM_ID::MEAT4 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/ring01.png" ),    ITEM_ID::RING1 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/ring02.png" ),    ITEM_ID::RING2 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/ring03.png" ),    ITEM_ID::RING3 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/ring04.png" ),    ITEM_ID::RING4 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/ring05.png" ),    ITEM_ID::RING5 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/ring06.png" ),    ITEM_ID::RING6 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/rod01.png" ),     ITEM_ID::ROD1 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/rod02.png" ),     ITEM_ID::ROD2 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/rod03.png" ),     ITEM_ID::ROD3 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/rod04.png" ),     ITEM_ID::ROD4 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/sword01.png" ),   ITEM_ID::SWORD1 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/sword02.png" ),   ITEM_ID::SWORD2 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/sword03.png" ),   ITEM_ID::SWORD3 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/sword04.png" ),   ITEM_ID::SWORD4 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/stone01.png" ),   ITEM_ID::STONE1 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/stone02.png" ),   ITEM_ID::STONE2 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/stone03.png" ),   ITEM_ID::STONE3 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/stone04.png" ),   ITEM_ID::STONE4 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/stone05.png" ),   ITEM_ID::STONE5 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/stone06.png" ),   ITEM_ID::STONE6 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/garbage01.png" ), ITEM_ID::GARBAGE1 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/on_frame/garbage02.png" ), ITEM_ID::GARBAGE2 ),
	};

	ITEM_IMAGE big_image[ ] = {
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/herb01.png" ),    ITEM_ID::HERB1 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/herb02.png" ),    ITEM_ID::HERB2 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/herb03.png" ),    ITEM_ID::HERB3 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/herb04.png" ),    ITEM_ID::HERB4 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/herb05.png" ),    ITEM_ID::HERB5 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/herb06.png" ),    ITEM_ID::HERB6 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/herb07.png" ),    ITEM_ID::HERB7 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/herb08.png" ),    ITEM_ID::HERB8 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/herb09.png" ),    ITEM_ID::HERB9 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/meat01.png" ),    ITEM_ID::MEAT1 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/meat02.png" ),    ITEM_ID::MEAT2 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/meat03.png" ),    ITEM_ID::MEAT3 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/meat04.png" ),    ITEM_ID::MEAT4 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/ring01.png" ),    ITEM_ID::RING1 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/ring02.png" ),    ITEM_ID::RING2 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/ring03.png" ),    ITEM_ID::RING3 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/ring04.png" ),    ITEM_ID::RING4 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/ring05.png" ),    ITEM_ID::RING5 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/ring06.png" ),    ITEM_ID::RING6 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/rod01.png" ),     ITEM_ID::ROD1 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/rod02.png" ),     ITEM_ID::ROD2 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/rod03.png" ),     ITEM_ID::ROD3 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/rod04.png" ),     ITEM_ID::ROD4 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/sword01.png" ),   ITEM_ID::SWORD1 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/sword02.png" ),   ITEM_ID::SWORD2 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/sword03.png" ),   ITEM_ID::SWORD3 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/sword04.png" ),   ITEM_ID::SWORD4 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/stone01.png" ),   ITEM_ID::STONE1 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/stone02.png" ),   ITEM_ID::STONE2 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/stone03.png" ),   ITEM_ID::STONE3 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/stone04.png" ),   ITEM_ID::STONE4 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/stone05.png" ),   ITEM_ID::STONE5 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/stone06.png" ),   ITEM_ID::STONE6 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/garbage01.png" ), ITEM_ID::GARBAGE1 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/big_frame/garbage02.png" ), ITEM_ID::GARBAGE2 ),
	};
	
	ITEM_IMAGE grab_image[ ] = {
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/herb01.png" ),    ITEM_ID::HERB1 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/herb02.png" ),    ITEM_ID::HERB2 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/herb03.png" ),    ITEM_ID::HERB3 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/herb04.png" ),    ITEM_ID::HERB4 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/herb05.png" ),    ITEM_ID::HERB5 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/herb06.png" ),    ITEM_ID::HERB6 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/herb07.png" ),    ITEM_ID::HERB7 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/herb08.png" ),    ITEM_ID::HERB8 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/herb09.png" ),    ITEM_ID::HERB9 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/meat01.png" ),    ITEM_ID::MEAT1 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/meat02.png" ),    ITEM_ID::MEAT2 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/meat03.png" ),    ITEM_ID::MEAT3 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/meat04.png" ),    ITEM_ID::MEAT4 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/ring01.png" ),    ITEM_ID::RING1 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/ring02.png" ),    ITEM_ID::RING2 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/ring03.png" ),    ITEM_ID::RING3 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/ring04.png" ),    ITEM_ID::RING4 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/ring05.png" ),    ITEM_ID::RING5 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/ring06.png" ),    ITEM_ID::RING6 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/rod01.png" ),     ITEM_ID::ROD1 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/rod02.png" ),     ITEM_ID::ROD2 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/rod03.png" ),     ITEM_ID::ROD3 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/rod04.png" ),     ITEM_ID::ROD4 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/sword01.png" ),   ITEM_ID::SWORD1 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/sword02.png" ),   ITEM_ID::SWORD2 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/sword03.png" ),   ITEM_ID::SWORD3 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/sword04.png" ),   ITEM_ID::SWORD4 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/stone01.png" ),   ITEM_ID::STONE1 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/stone02.png" ),   ITEM_ID::STONE2 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/stone03.png" ),   ITEM_ID::STONE3 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/stone04.png" ),   ITEM_ID::STONE4 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/stone05.png" ),   ITEM_ID::STONE5 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/stone06.png" ),   ITEM_ID::STONE6 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/garbage01.png" ), ITEM_ID::GARBAGE1 ),
		ITEM_IMAGE ( viewer->loadGraph( "work/ctrl_UI/item/grab_image/garbage02.png" ), ITEM_ID::GARBAGE2 ),
	};

	for ( int i = 0; i < MAX_ITEM_TYPE; i++ ) {
		_no_frame_image[ i ] = no_frame_image[ i ];
		_image[ i ] = item_image[ i ];
		_big_image[ i ] = big_image[ i ];
		_grab_image[ i ] = grab_image[ i ];
	}
}


ItemImage::~ItemImage( ) {

}

int ItemImage::getNoFrameImage( ITEM_ID id ) {
	int result = 0;

	for ( int i = 0; i < MAX_ITEM_TYPE; i++ ) {
		if ( _no_frame_image[ i ].id == id ) {
			result = _no_frame_image[ i ].image;
			break;
		}
	}
	return result;
}

int ItemImage::getOnFrameImage( ITEM_ID id ) {
	int result = 0;

	for ( int i = 0; i < MAX_ITEM_TYPE; i++ ) {
		if ( _image[ i ].id == id ) {
			result = _image[ i ].image;
			break;
		}
	}
	return result;
}

int ItemImage::getBigFrameImage( ITEM_ID id ) {
	int result = 0;

	for ( int i = 0; i < MAX_ITEM_TYPE; i++ ) {
		if ( _image[ i ].id == id ) {
			result = _big_image[ i ].image;
			break;
		}
	}
	return result;
}

int ItemImage::getGrabImage( ITEM_ID id ) {
	int result = 0;

	for ( int i = 0; i < MAX_ITEM_TYPE; i++ ) {
		if ( _image[ i ].id == id ) {
			result = _grab_image[ i ].image;
			break;
		}
	}
	return result;
}

int ItemImage::getFrameAmount( int num ) {
	return _frame_amount[ num ];
}

int ItemImage::getBigFrameAmount( int num ) {
	return _big_frame_amount[ num ];
}

int ItemImage::getFrame( ) {
	return _frame;
}

int ItemImage::getBigFrame( ) {
	return _big_frame;
}

int ItemImage::getFrameEquipment( ) {
	return _frame_equipment;
}

int ItemImage::getBigFrameEquipment( ) {
	return _big_frame_equipment;
}

int ItemImage::getFrameFoot( ) {
	return _frame_foot;
}

int ItemImage::getFrameWhite( ) {
	return _frame_white;
}