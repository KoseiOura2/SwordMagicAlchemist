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
	  //ITEM_DATA( type,                   category, rarity, "�������B" ),
		ITEM_DATA( ITEM_TYPE( HERB1 ),     FOOD,        1,   "��1�@�y�򑐁z�H�ׂ��HP��30�񕜂���򑐁B" ),
		ITEM_DATA( ITEM_TYPE( HERB2 ),     FOOD,	    3,   "��3�@�y��򑐁z�H�ׂ��HP��60�񕜂���ǂ��򑐁B" ),
		ITEM_DATA( ITEM_TYPE( HERB3 ),     FOOD,	    4,   "��4�@�y����򑐁z�H�ׂ��HP��120�񕜂��鐦���򑐁B" ),
		ITEM_DATA( ITEM_TYPE( HERB4 ),     FOOD,		3,   "��3�@�y���ʂ����z�H�ׂ�ƃt���A�S�̌��ʂ����Ƃ��o���鑐�B" ),
		ITEM_DATA( ITEM_TYPE( HERB5 ),     FOOD,	    3,   "��3�@�y�Ȃ��葐�z�H�ׂ�Ə�Ԉُ���������Ƃ��ł���򑐁B" ),
		ITEM_DATA( ITEM_TYPE( HERB6 ),     FOOD,        3,   "��3�@�y�Ԃ��Ƃё��z�g�p����ƃt���A�̂ǂ����ɔ�΂���鑐�B" ),
		ITEM_DATA( ITEM_TYPE( HERB7 ),     FOOD,        2,   "��2�@�y�ő��z�H�ׂ�Ɠŏ�ԂɂȂ��Ă��܂��댯�ȑ��B" ),
		ITEM_DATA( ITEM_TYPE( HERB8 ),     FOOD,        2,   "��2�@�y���тꑐ�z�H�ׂ�Ƒ̂�Ⴢ�ă}�q��ԂɂȂ��Ă��܂��댯�ȑ��B" ),
		ITEM_DATA( ITEM_TYPE( HERB9 ),     FOOD,        2,   "��2�@�y���f���z�H�ׂ�ƌ��o�ɏP��ꍬ����ԂɂȂ�댯�ȑ��B" ),
		ITEM_DATA( ITEM_TYPE( MEAT1 ),     FOOD,        1,   "��1�@�y�b�̓��z�쐶�����̓��B�H�ׂ�Ƃ�����10�c���B" ),
		ITEM_DATA( ITEM_TYPE( MEAT2 ),     FOOD,        2,   "��2�@�y�傫�ȓ��z��^�����̓��B�H�ׂ�Ƃ�����30�c���B" ),
		ITEM_DATA( ITEM_TYPE( MEAT3 ),     FOOD,        5,   "��5�@�y����X�����[�X�z�X�����O���[�̊󏭂ȓ��B���ɓ����ŐH�ׂ�Ƃ����������ς��ɂȂ�B" ),
		ITEM_DATA( ITEM_TYPE( MEAT4 ),     FOOD,        1,   "��1�@�y���������z���s�����b�̓��B������5�c��邪�������󂵂ēŏ�ԂɂȂ��Ă��܂��B" ),
		ITEM_DATA( ITEM_TYPE( RING1 ),     ACCESSORY,   2,   "��2�@�y���ʂ̎w�ցz��΂����߂�ꂽ���ʂ̎w�ցB�������A�����+2�B" ),
		ITEM_DATA( ITEM_TYPE( RING2 ),     ACCESSORY,   3,   "��3�@�y�����̎w�ցz�����̉��삪�h���΂����߂�ꂽ�w�ցB�������A�ő�HP+10�B" ),
		ITEM_DATA( ITEM_TYPE( RING3 ),     ACCESSORY,   3,   "��3�@�y�����̎w�ցz�Ɍ��̉��삪�h���΂����߂�ꂽ�w�ցB�������A�U����+10�B" ),
		ITEM_DATA( ITEM_TYPE( RING4 ),     ACCESSORY,   4,   "��4�@�y���̎w�ցz�����̉��삪�h���΂����߂�ꂽ�w�ցB�������A��Ԉُ�ɂ�����Ȃ��B" ),
		ITEM_DATA( ITEM_TYPE( RING5 ),     ACCESSORY,   5,   "��5�@�y�n���̎w�ցz�����̉��삪�h���΂����߂�ꂽ�w�ցB�������A�擾�B���|�C���g��2�{�ɂȂ�B" ),
		ITEM_DATA( ITEM_TYPE( RING6 ),     ACCESSORY,   4,   "��4�@�y㩏����̎w�ցz���^�̉��삪�h���΂����߂�ꂽ�w�ցB�������A㩂ɂ�����Ȃ��B" ),
		ITEM_DATA( ITEM_TYPE( ROD1 ),      WEAPON,	    1,   "��1�@�y�؂̏�z���͂��h���Ă��Ȃ������̖؂̏�B�������A�U���́{2�B" ),
		ITEM_DATA( ITEM_TYPE( ROD2 ),      ROD,	        4,   "��4�@�y���̏�z�g���ƑO���ɉ������ł����Ή��_���[�W��^�����B" ),
		ITEM_DATA( ITEM_TYPE( ROD3 ),      ROD,		    5,   "��5�@�y�����̏�z�������h������B�g�p����Ǝ����̂���t���A�S�Ă̓G�ɉΒ��U���B" ),
		ITEM_DATA( ITEM_TYPE( ROD4 ),      ROD,	        4,   "��4�@�y���[�v�̏�z�g�p����ƒ����ɂ���G���s�v�c�ȗ͂Ńt���A�̂ǂ����Ƀ��[�v�����B" ),
		ITEM_DATA( ITEM_TYPE( SWORD1 ),    WEAPON,      2,   "��2�@�y���̌��z��ʓI�Ȍ��m���g�p���Ă��錕�B�������A�U����+10�B" ),
		ITEM_DATA( ITEM_TYPE( SWORD2 ),    WEAPON,      4,   "��4�@�y���R�m�̌��z���Ȃ�R�m���g�p���Ă��錕�B�������A�U����+20�B" ),
		ITEM_DATA( ITEM_TYPE( SWORD3 ),    WEAPON,      5,   "��5�@�y�������z�G��|�������Ɏ擾�ł���B���|�C���g��2�{�ɂȂ閂���m�̌��B�������A�U����+40�B" ),
		ITEM_DATA( ITEM_TYPE( SWORD4 ),    WEAPON,      5,   "��5�@�y�g���C�\�[�h�z�܂�ɍU�����ɓŁA��ჁA������3��������_���ɂ�����`���̌��B" ),
		ITEM_DATA( ITEM_TYPE( STONE1 ),	   STONE,       1,   "��1�@�y�Ă��΁z�������2�}�X��̓G�Ƀ_���[�W��^���鍂���ŏĂ��ꂽ�΁B" ),
		ITEM_DATA( ITEM_TYPE( STONE2 ),    CONSUMPTION, 2,   "��2�@�y�����΁z�g�p����ƘB���|�C���g��50�����閂�̗͂��h�����΁B" ),
		ITEM_DATA( ITEM_TYPE( STONE3 ),    STONE,       4,   "��4�@�y�����̐΁z�����Ă���Ɠ|�ꂽ����x���������ł���s�v�c�Ȑ΁B" ),
		ITEM_DATA( ITEM_TYPE( STONE4 ),    CONSUMPTION, 5,   "��5�@�y��Ղ̐΁z�g�p����ƃ��x����1�オ���Ղ̐΁B" ),
		ITEM_DATA( ITEM_TYPE( STONE5 ),    CONSUMPTION, 3,   "��3�@�y㩉󂵂̐΁z�g�p����ƃt���A�̂��ׂĂ�㩂��j�󂳂��s�v�c�Ȑ΁B" ),
		ITEM_DATA( ITEM_TYPE( STONE6 ),    CONSUMPTION, 4,   "��4�@�y�喂���΁z�g�p����ƘB���|�C���g��500��������Ȗ��̗͂��h�����΁B" ),
		ITEM_DATA( ITEM_TYPE( GARBAGE1 ),  STONE,       1,   "��1�@�y�S�~�z�ǂ��ɂł������Ă����Ȃ����̃S�~�B" ),
		ITEM_DATA( ITEM_TYPE( GARBAGE2 ),  STONE,       4,   "��4�@�y�㎿�ȃS�~�z�����������Ă��邿����ƍ��������ȃS�~�B" ),	
	};

	for ( int i = 0; i < MAX_ITEM_TYPE; i++ ) {
		_item_table[ i ] = item_teble[ i ];
	}

	COMMAND_DATA command_teble[ ] = {
		COMMAND_DATA( "����", Network::ITEM_ACTION::USE,	     USE ),
		COMMAND_DATA( "���ׂ�", Network::ITEM_ACTION::USE,       EAT ),
		COMMAND_DATA( "�ӂ�",   Network::ITEM_ACTION::USE,       SWING ),
		COMMAND_DATA( "�Ȃ���", Network::ITEM_ACTION::THROW,	 THROW ),
		COMMAND_DATA( "����",   Network::ITEM_ACTION::PUT,	     PUT ),
		COMMAND_DATA( "����",   Network::ITEM_ACTION::EXCHANGE,  EXCHANGE ),
		COMMAND_DATA( "����"  , Network::ITEM_ACTION::EQUIPMENT, EQUIPMENT ),
		COMMAND_DATA( "�͂���", Network::ITEM_ACTION::DISARM,    DISARM ),
		COMMAND_DATA( "�Ƃ���", Network::ITEM_ACTION::QUIT,      QUIT ),
		COMMAND_DATA( "�E��",	Network::ITEM_ACTION::PICK_UP,	 PICK_UP ),
	};

	for ( int i = 0; i < MAX_COMMAND_NUM; i++ ) {
		_command_table[ i ] = command_teble[ i ];
	}
	
	//�f�o�b�O�p
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

// ����������
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

// �A�C�e��������Ƃ��ɂ���Ă����������
void Item::close( ) {
	_foot_open = false;
	_open_num = -1;
}

void Item::window( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	TouchPtr touch = std::dynamic_pointer_cast< Touch >( fw->getTask( typeid( Touch ).name( ) ) );

	viewer->drawGraph( WINDOW_POS_X, WINDOW_POS_Y, _window );	// �E�B���h�E�̕`��
	
	unsigned int count = 0;		// vector�̎Q�Ƃ𓾂邽�߂Ɏg���̂�watnig�΍��unsigned�^
	for ( int i = 0; i < ITEM_COLUMN; i++ ) {
		for ( int j = 0; j < ITEM_ROW; j++ ) {
			// �莝���A�C�e���̕`��
			Vector2 item_pos ( WINDOW_POS_X + ITEM_X_SPACE + ( ITEM_X_INTERVAL * j ), WINDOW_POS_Y + ITEM_Y_SPACE + ( ITEM_Y_INTERVAL * i ) );
			if ( count < _item_list.size( ) ) {
				// �I�𒆃A�C�e��
				if ( count == _open_num ) {
					viewer->drawGraph( ( int )item_pos.x, ( int )item_pos.y, _item_image->getFrameWhite( ) );
				}

				viewer->drawGraph( ( int )item_pos.x, ( int )item_pos.y, _item_image->getOnFrameImage( _item_list.at( count ).type.id ) );
				
				// �������A�C�e��
				if ( _item_list.at( count ).equipment == true ) {
					viewer->drawGraph( ( int )item_pos.x, ( int )item_pos.y, _item_image->getFrameEquipment( ) );
				}	

				// �g�p�񐔂̕\��
				if ( _item_list.at( count ).category == ROD ) {
					viewer->drawGraph( ( int )item_pos.x, ( int )item_pos.y, _item_image->getFrameAmount( _item_list.at( count ).type.amount - 1 ) );
				}
			} else if ( count == MAX_ITEM_NUM ) {	// �����A�C�e���̕`��
				if ( _foot_open == true ) {
					viewer->drawGraph( ( int )item_pos.x, ( int )item_pos.y, _item_image->getFrameWhite( ) );
				}
				if ( _foot_item.type.id != ITEM_NONE ) {
					viewer->drawGraph( ( int )item_pos.x, ( int )item_pos.y, _item_image->getOnFrameImage( _foot_item.type.id ) );
				} else {
					viewer->drawGraph( ( int )item_pos.x, ( int )item_pos.y,  _item_image->getFrame( ) );
				}
				viewer->drawGraph( ( int )item_pos.x, ( int )item_pos.y, _item_image->getFrameFoot( ) );

				// �g�p�񐔂̕\��
				if ( _foot_item.category == ROD ) {
					viewer->drawGraph( ( int )item_pos.x, ( int )item_pos.y, _item_image->getFrameAmount( _foot_item.type.amount - 1 ) );
				}

			} else {
				viewer->drawGraph( ( int )item_pos.x, ( int )item_pos.y, _item_image->getFrame( ) );	// �g�̕`��
			}

			// �A�C�e�����^�b�`�������̏���
			// ����
			if ( touch->isTouch( item_pos, ITEM_WIDTH, ITEM_HEIGHT ) && count == MAX_ITEM_NUM && _foot_item.type.id != ITEM_NONE ) {
				if ( _foot_open == true && _separate_flag == true ) {
					_foot_open = false;
					_separate_flag = false;
				} else if ( _separate_flag == true ) {
					_foot_open = true;
					_open_num = NOT_OPEN_ITEM;	// �莝���A�C�e���͕��Ă���
					_separate_flag = false;

				}

			} else if ( touch->isTouch( item_pos, ITEM_WIDTH, ITEM_HEIGHT ) && count < _item_list.size( ) ) {	// �����ȊO
				if ( _open_num == count && _separate_flag == true ) {
					_open_num = NOT_OPEN_ITEM;
					_separate_flag = false;
				} else if ( _separate_flag == true ) {
					_open_num = count;
					_foot_open = false;		// �����A�C�e������Ă���
					_separate_flag = false;

				}
			};

			count++;
		}
	}



	// �A�C�e�����̕\��
	/*drawString( Vector2( NUM_ITEM_X, NUM_ITEM_Y ), "%d/%d", _item_list.size( ), MAX_ITEM_NUM );

	// �J����y�[�W�̍ő吔��ݒ�
	int max_page_num = _item_list.size( ) / MAX_PAGE_ITEM + 1;
	if ( max_page_num >= MAX_PAGE - 1 ) {
		max_page_num = MAX_PAGE - 1;
	}
	if ( _item_list.size( ) % MAX_PAGE_ITEM == 0 ) {
		max_page_num = _item_list.size( ) / MAX_PAGE_ITEM;
	}

	int last_page = max_page_num;
	// �����ɃA�C�e��������ꍇ�̂ݑ����A�C�e���\���p�̃y�[�W�����
	if ( _foot_item.type.id != ITEM_ID::ITEM_NONE ) {
		max_page_num++;
	}

	// �J���y�[�W�̐ݒ�
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

	// for���̉񂷉񐔂����߂�
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
	// for���̏����l�����߂�
	int init_num = 0;
	if ( _open_page == MAX_PAGE - 1 ) {
		init_num = 10;
		roop_num += init_num;
	}
	// �y�[�W���\��
	drawString( Vector2( PAGE_NUM_X, PAGE_NUM_Y ), "%d/%d", _open_page, max_page_num );
	
	Vector2 item_pos = Vector2( ITEM_LIST_POS_X, WINDOW_POS_Y + WINDOW_TOP_DISTANCE );

	if ( _open_page == max_page_num && _foot_item.type.id != ITEM_NONE ) {
		// �����A�C�e���̂ݕ`��
		item_pos.y += ITEM_DISTANCE;
		drawItemName( item_pos, NULL, true );

		if ( _foot_open ) {
			drawStringColor( item_pos, _foot_item.type.name + "( ���� )", 0, 180, 255 );
		} else {
			drawString( item_pos, _foot_item.type.name + "( ���� )" );
		}
		//------------�A�C�e�������^�b�`�������̏���------------
	   
	    if ( touch->isTouch( item_pos, WINDOW_WIDTH, FONT_SIZE ) ) {
			// ����
			if ( _foot_open == true && _separate_flag == true ) {
				 _close_flag = true;
				 close( );
				 touch->rejectTouch( );
			} 
			// �J��
			else if ( _close_flag == false ) {
				_separate_flag = false;
				_foot_open = true;
			}
		};
	   
	} else {
		 //------------�����A�C�e����E�\����t���鏈��------------
		for ( int i = init_num; i < roop_num; i++ ) {
			item_pos.y += ITEM_DISTANCE;
			drawItemName( item_pos, i, false );
			//------------�A�C�e�������^�b�`�������̏���------------
		   
		    if ( touch->isTouch( item_pos, WINDOW_WIDTH, FONT_SIZE ) ) {
				// ����
				if ( _open_num == i && _separate_flag == true ) {
					 _close_flag = true;
					 close( );
					 touch->rejectTouch( );
				} 
				// �J��
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

	viewer->drawGraph( WINDOW_POS_X + WINDOW_WIDTH, WINDOW_POS_Y, _window_use );	// �E�B���h�E�̕`��
	int use_dis = USE_WINDOW_HEIGHT / 6;	// �E�B���h�E�̍��� / �R�}���h�̐� + 2

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

	viewer->drawGraph( WINDOW_POS_X + WINDOW_WIDTH, WINDOW_POS_Y, _window_use );	// �E�B���h�E�̕`��
	int use_dis = USE_WINDOW_HEIGHT / 5;	// �E�B���h�E�̍��� / �R�}���h�̐� + 2

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
	bool weapon_flag = false;		// ����𑕔����Ă��邩
	bool accessory_flag = false;	// �A�N�Z�T���[�𑕔����Ă��邩

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
	
	// �A�C�e���𑕔����Ă��Ȃ��Ƃ�
	if ( weapon_flag == false ) {
		_equipment_weapon = NOT_EQUIPMENT;
	}

	if ( accessory_flag == false ) {
		_equipment_accessory = NOT_EQUIPMENT;
	}

}

// �Ƃ���R�}���h�̏���
void Item::commandQuit( ) {
	// �e�R�}���h���ʏ����݂̂Ȃ̂œ��ɂȂ�
	return;
}

// �����R�}���h�̏���
void Item::commandPut( ) {
	_network->setSendItem( Network::ITEM_ACTION::PUT, _item_list.at( _open_num ).type );
	_foot_item = _item_list.at( _open_num );
	_item_list.erase( _item_list.begin( ) + _open_num );	// �g�����A�C�e���̍폜
	adjustEquipment( );
}
// �����R�}���h�̏���
void Item::commandExchange( ) {
	ITEM_DATA temp;
	temp = _item_list.at( _open_num );
	_network->setSendItem( Network::ITEM_ACTION::EXCHANGE, _item_list.at( _open_num ).type );
	_item_list.at( _open_num ) = _foot_item;	// �A�C�e���𑫉��̃A�C�e���ƌ���
	_foot_item = temp;
}

// �����A���ׂ铙�̂����A�N�V�����̎��̏���
void Item::commandUse( ) {
	// �����A�C�e�����𔻕ʂ��ď�����؂�ւ���
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
	// ���ʂ�������
	if ( _item_list.at( _open_num ).type.id == HERB4 ) {
		// �}�b�v�̌��ʂ����̊֐����Ă�
		_map->clairvoyance( );
	}
	if ( _item_list.at( _open_num ).type.id == STONE5 ) {
		_map->mysteryClear( );
	}

	_item_list.at( _open_num ).type.amount--;	// �g�p�񐔂���񌸂炷
	if ( _item_list.at( _open_num ).type.amount <= 0 && _item_list.at( _open_num ).category == ROD ) {
		_item_list.at( _open_num ) = _item_table[ ROD1 - 1 ];	// �g���I�������͖؂̏�ɂ���

	} else if ( _item_list.at( _open_num ).type.amount <= 0 ) {
		_item_list.erase( _item_list.begin( ) + _open_num );	// �g�����A�C�e���̍폜
		adjustEquipment( );
	}
}

// �Ȃ���R�}���h�̏���
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
	_item_list.erase( _item_list.begin( ) + _open_num );	// �Ȃ����A�C�e���̍폜
	adjustEquipment( );
}

// �����R�}���h�̏���
void Item::commandEquipment( ) {
	// ���ɑ������Ă������̂��O������
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

// �͂����R�}���h�̏���
void Item::commandDisarm( ) {
	_network->setSendItem( Network::ITEM_ACTION::DISARM, _item_list.at( _open_num ).type );
	_item_list.at( _open_num ).equipment = false;
}

// �E���R�}���h�̏���
void Item::commandPickUp( ) {
	_network->setSendItem( Network::ITEM_ACTION::PICK_UP, _foot_item.type );
	
	if ( _item_list.size( ) >= MAX_ITEM_NUM ) { // �A�C�e���������ς��̂Ƃ�
		return;
	}

	// �����A�C�e�����莝���ɒǉ�����
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

// �A�C�e�����J�����ۂ̃R�}���h��ݒ肷��֐�
void Item::setCommand( CATEGORY category, bool equipment ) {
	_command_list.clear( );

	COMMAND_DATA data;
	// �g���H�ׂ铙
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

	// footitem�̂ݏE��
	if ( _foot_open == true ) {
		data = getCommandStatus( PICK_UP );
		_command_list.push_back( data );
	}

	// �Ȃ���
	_command_list.push_back( getCommandStatus( THROW ) );

	// ����or����
	// �����A�C�e���ł͂Ȃ��A�����ɊK�i���Ȃ��Ƃ��̂�
	if ( _foot_open == false && _network->getFoot( ) != Network::FOOT_STAIR ) {
		if ( _foot_item.type.id != ITEM_NONE ) {
			_command_list.push_back( getCommandStatus( EXCHANGE ) );
		} else {
			_command_list.push_back( getCommandStatus( PUT ) );
		}
	}

	// �Ƃ���
	_command_list.push_back( getCommandStatus( QUIT ) );


}

// �R�}���h�̃X�e�[�^�X���擾����֐�
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

// �A�C�e�������̕`��
void Item::drawDescription( ITEM_DATA item ) {
	int line = 0;
	line = item.description.find( "�z" );
	if ( line == std::string::npos ) {
		line = item.description.find( "�B" );
	}
	line += 2;
	std::string tmp = item.description.substr( 0, line );	// �B�܂ł̈ʒu����s�ڂƂ���
	drawStringSmallFont( Vector2 ( DESCRIPTION_X, DESCRIPTION_Y ), tmp );
	tmp = item.description.substr( line );					// �B�ȍ~�̕�����2�s�ڂɂ���
	drawStringSmallFont( Vector2 ( DESCRIPTION_X, DESCRIPTION_Y + FONT_SMALL_SIZE ), tmp );
}

void Item::onItem( ) {
	ITEM_DATA temp;
	temp.type =_network->getItemType( );
	temp = getItemStatus( temp.type );

	if ( _network->getFoot( ) == Network::FOOT_THING::FOOT_ITEM && temp.type.id != ITEM_ID::ITEM_NONE && _network->isRide( ) == true ) {

		if ( _item_list.size( ) < MAX_ITEM_NUM && _foot_item.type.id == ITEM_NONE ) {

			// �A�C�e���ɋ󂫂�����_foot_item��o�^���Ă��Ȃ��Ƃ�
			_item_list.push_back( temp );
			_network->setFootThing( Network::FOOT_THING::FOOT_NONE );
			_network->setSendItemAction( Network::ON_ITEM::NO );

		} else if ( _item_list.size( ) >= MAX_ITEM_NUM && _foot_item.type.id == ITEM_NONE ) {

			// �A�C�e���������ς���_foot_item��o�^���ĂȂ��Ƃ�
			_foot_item = temp;
			_network->setSendItemAction( Network::ON_ITEM::YES );
		} else if ( _item_list.size( ) >= MAX_ITEM_NUM && _foot_item.type.id != ITEM_NONE ) {

			// �A�C�e���������ς���_foot_item��o�^���Ă��Ƃ�
			_network->setSendItemAction( Network::ON_ITEM::YES );
		}
		//_network->resetRide( );
	} else if ( _network->getFoot( ) == Network::FOOT_THING::FOOT_ITEM && temp.type.id != ITEM_ID::ITEM_NONE && _network->isRide( ) == false ) {
		_foot_item = temp;
		
	} else if ( _network->getFoot( ) != Network::FOOT_THING::FOOT_ITEM && _network->isRide( ) == false ) {
		_foot_item = ITEM_DATA( ); // �v���C���[���������������̃f�[�^������
	}
}

std::vector< Item::ITEM_DATA > Item::getItemList( ) {
	return _item_list;
}

Item::ITEM_DATA Item::getFootItem( ) {
	return _foot_item;
}
// �A�C�e����id���琫�\���擾����֐�
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
// �A�C�e����type���琫�\���擾���A�g�p�񐔂Ȃǂ�type�͕ێ����Ă����֐�
Item::ITEM_DATA Item::getItemStatus( ITEM_TYPE item ) {
	ITEM_DATA result;

	for ( int i = 0; i < MAX_ITEM_TYPE; i++ ) {
		if ( _item_table[ i ].type.id == item.id ) {
			result = _item_table[ i ];
			break;
		}
	}
	result.type = item;	//�@�g�p�񐔂��������ꍇ����������Ȃ��悤��

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
	// �B���ō�����A�C�e�����񂾂����Ƃ��g�p�񐔂�ݒ�
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

// ���S���ɕ����̐΂������Ă��邩��Ԃ��A�����Ă����ꍇ�͕����̐΂��g�p���ĕ�������
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