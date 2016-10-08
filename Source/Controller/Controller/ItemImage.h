#pragma once

#include "smart_ptr.h"
#include "mathematics.h"
#include "ItemName.h"

const int MAX_AMOUNT = 9;

class ItemImage {
public:
	ItemImage( );
	virtual ~ItemImage( );
	int getNoFrameImage( ITEM_ID id );
	int getOnFrameImage( ITEM_ID id );
	int getBigFrameImage( ITEM_ID id );
	int getGrabImage( ITEM_ID id );
	int getFrame( );
	int getBigFrame( );
	int getFrameEquipment( );
	int getBigFrameEquipment( );
	int getFrameFoot( );
	int getFrameWhite( );
	int getFrameAmount( int num );
	int getBigFrameAmount( int num );
private:
	struct ITEM_IMAGE {
		int image;
		ITEM_ID id;

		ITEM_IMAGE( ) {
			this->image = 0;
			this->id = ITEM_ID::ITEM_NONE;
		}

		ITEM_IMAGE( int image, ITEM_ID id ) {
			this->image = image;
			this->id = id;
		}

	};
private:
	ITEM_IMAGE _no_frame_image[ MAX_ITEM_TYPE ];
	ITEM_IMAGE _image[ MAX_ITEM_TYPE ];
	ITEM_IMAGE _big_image[ MAX_ITEM_TYPE ];
	ITEM_IMAGE _grab_image[ MAX_ITEM_TYPE ];
	int _frame_amount[ MAX_AMOUNT ];
	int _big_frame_amount[ MAX_AMOUNT ];
	int _frame;
	int _big_frame;
	int _frame_equipment;
	int _big_frame_equipment;
	int _frame_foot;
	int _frame_white;
};

