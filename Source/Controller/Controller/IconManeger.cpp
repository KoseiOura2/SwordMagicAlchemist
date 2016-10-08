#include "IconManeger.h"
#include "Framework.h"
#include "Viewer.h"
#include "Item.h"
#include "Skill.h"
#include "Alchemy.h"
#include "HInt.h"
#include "Option.h"
#include "Foot.h"
#include "Touch.h"
#include "Camera.h"
#include "ItemImage.h"

IconManeger::IconManeger( NetworkControllerPtr network, MapPtr map, CameraPtr camera, NextFloorPtr next_floor ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	// �A�C�R���̉��ɕ~���摜
	_underlay = viewer->loadGraph( "work/ctrl_UI/underlay.png" );
	_underlay_pos = Vector2 ( ( SCREEN_WIDTH - UNDELAY_WIDTH ) / 2, SCREEN_HEIGHT - UNDELAY_HEIGHT );

	// �߂�{�^��
	_return = viewer->loadGraph( "work/ctrl_UI/return.png" );
	_return_pos = Vector2( 0, SCREEN_HEIGHT - RETURN_HEIGHT );

	// �����{�^��
	_direction = viewer->loadGraph( "work/ctrl_UI/direction.png" );
	_direction_pos = Vector2( SCREEN_WIDTH - DIRECTION_WIDTH, SCREEN_HEIGHT - DIRECTION_HEIGHT );

	_separate_flag = false;
	_close_flag = false;
	//-------------���W�w��----------------------
	Vector2 pos[ ICON_NUM ];
	for ( int i = 0; i < ICON_NUM; i++ ) {
		pos[ i ].x = _underlay_pos.x + ( ( UNDELAY_WIDTH - 350 ) / ICON_NUM * i ) + 100;
		pos[ i ].y = SCREEN_HEIGHT - UNDELAY_HEIGHT;

		switch ( i ) {
		case 0:
			_skill_pos = pos[ i ];
			break;
		case 1:
			_item_pos = pos[ i ];
			break;
		case 2:
			_alchemy_pos = pos[ i ];
			break;
		case 3:
			_hint_pos = pos[ i ];
			break;
		case 4:
			_foot_pos = pos[ i ];
			break;
		}
	}
	//-------------------------------------------
	_network = network;

	_item_image = ItemImagePtr( new ItemImage( ) );
	_skill = SkillPtr( new Skill( _skill_pos, _network, _item_image ) );
	_item = ItemPtr( new Item( _item_pos, _network, map, _item_image ) );
	_alchemy = AlchemyPtr( new Alchemy( _alchemy_pos, _item, _network, camera, _item_image ) );
	_hint = HintPtr( new Hint( _hint_pos ) );
	_foot = FootPtr( new Foot( _foot_pos, _network, next_floor, _item ) );

	_button_touch = false;
}


IconManeger::~IconManeger( ) {
}

void IconManeger::update( ) {
	FrameworkPtr fw = Framework::getInstance( );
	TouchPtr touch = std::dynamic_pointer_cast< Touch >( fw->getTask( typeid( Touch ).name( ) ) );

	if ( _old_open != _open_icon ) {
		close( _old_open );
	}

	touchReturn( );

	draw( );
	_item->onItem( );
	_skill->skillGet( );
	_alchemy->setAlchemyPoint( );	// �B���|�C���g�擾�����̓^�b�`���ĂȂ���Ԃł����s����
	_alchemy->AlchemyTile( );
	// �v���C���[�̎��S���ɕ����̐΂������Ă��邩
	if ( _network->isDead( ) == true ) {
		revive( );
	}

	// ��x�w�𗣂��Ă��邩�ǂ������擾
	if ( touch->isSeparate( ) ) {
		_separate_flag = true;
		_close_flag = false;
	}

	_old_open = _open_icon;
}

void IconManeger::init( ) {
	_item->init( );
	_skill->init( );
	_alchemy->init( );
}

void IconManeger::touch( ) {
	FrameworkPtr fw = Framework::getInstance( );
	TouchPtr touch = std::dynamic_pointer_cast< Touch >( fw->getTask( typeid( Touch ).name( ) ) );

	//-------------------�J���A�C�R���̐ݒ�------------------------
	// �킴
	if ( touch->isTouch( _skill_pos, ICON_WIDTH, ICON_HEIGHT ) ) {
		if ( _open_icon == SKILL && _separate_flag == true ) {
			_open_icon = NONE;
			_close_flag = true;
		} else if ( _close_flag == false ) {
			_separate_flag = false;
			_open_icon = SKILL;
		}
	}

	// �A�C�e��
	if ( touch->isTouch( _item_pos, ICON_WIDTH, ICON_HEIGHT ) ) {
		if ( _open_icon == ITEM && _separate_flag == true ) {
			_open_icon = NONE;
			_close_flag = true;
		} else if ( _close_flag == false ) {
			_separate_flag = false;
			_open_icon = ITEM;
		}
	}

	// ��񂹂�
	if ( touch->isTouch( _alchemy_pos, ICON_WIDTH, ICON_HEIGHT ) ) {
		if ( _open_icon == ALCHEMY && _separate_flag == true ) {
			_open_icon = NONE;
			_close_flag = true;
		} else if ( _close_flag == false ) {
			_alchemy->setStartFlag( true );	// ����N���̐ݒ�
			_separate_flag = false;
			_open_icon = ALCHEMY;
		}
	}

	// �q���g
	if ( touch->isTouch( _hint_pos, ICON_WIDTH, ICON_HEIGHT ) ) {
		if ( _open_icon == HINT && _separate_flag == true ) {
			_open_icon = NONE;
			_close_flag = true;
		} else if ( _close_flag == false ) {
			_separate_flag = false;
			_open_icon = HINT;
		}
	}

	// ����
	if ( touch->isTouch( _foot_pos, ICON_WIDTH, ICON_HEIGHT ) ) {
		if ( _open_icon == FOOT && _separate_flag == true ) {
			_open_icon = NONE;
			_close_flag = true;
		} else if ( _close_flag == false ) {
			_separate_flag = false;
			_open_icon = FOOT;
		}
	}
	//----------------------------------------------------------------------


	// �e�A�C�R���̃^�b�`���Ăԏ���
	switch ( _open_icon ) {
		case SKILL: {
			_skill->touch( );
			break;
		}
		case ITEM: {
			_item->touch( );
			break;
		}
		case ALCHEMY: {
			_alchemy->touch( );
			break;
		}
		case HINT: {
			_hint->touch( );
			break;
		}
		case FOOT: {
			_foot->touch( );
			if ( _foot->isFootItem( ) == true ) {
				_open_icon = ITEM;
				_item->setFootOpen( true );
			} else {
				_open_icon = NONE;
			}
			_foot->close( );
			_close_flag = true;
			break;
		}
	}

}

void IconManeger::close( ICON icon ) {
	switch( icon ) {
		case SKILL:
			_skill->close( );
			break;
		case ITEM: 
			_item->close( );
			break;
		case ALCHEMY:
			_alchemy->close( );
			break;
		case HINT:
			_hint->close( );
			break;
	}
}

void IconManeger::draw( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	viewer->drawGraph( _underlay_pos.x, _underlay_pos.y, _underlay ); // ���~���̕`��
	viewer->drawGraph( _return_pos.x, _return_pos.y, _return ); // �߂�{�^��
	viewer->drawGraph( _direction_pos.x, _direction_pos.y, _direction  );	// �����{�^��
		 
	_alchemy->draw( );
	_item->draw( );
	_skill->draw( );
	_hint->draw( );
	_foot->draw( );
}

void IconManeger::revive( ) {
	if ( _item->isRiviveItem( ) == true ) {
		_network->setSendRevive( Network::YES_REVIVE );
		_network->resetDead( );
	} else {
		_network->setSendRevive( Network::NO_REVIVE );
		_network->resetDead( );
	}
}

bool IconManeger::isOpenIcon( ) {
	if ( _open_icon == NONE ) {
		return false;
	}
	return true;
}

// �߂�{�^���̏���
void IconManeger::touchReturn( ) {
	FrameworkPtr fw = Framework::getInstance( );
	TouchPtr touch = std::dynamic_pointer_cast< Touch >( fw->getTask( typeid( Touch ).name( ) ) );

	if ( touch->isTouch( _return_pos, RETURN_WIDTH, RETURN_HEIGHT ) ) {
		close( _old_open );
		_open_icon = NONE;
		_close_flag = true;
	}
}

// �����{�^�����^�b�`�������ǂ���	
// button����Ăяo���Ďg��

bool IconManeger::isTouchDir( ) {
	FrameworkPtr fw = Framework::getInstance( );
	TouchPtr touch = std::dynamic_pointer_cast< Touch >( fw->getTask( typeid( Touch ).name( ) ) );

	if ( _separate_flag == false ) {
		return false;
	}

	if ( touch->isTouch( _direction_pos, DIRECTION_WIDTH, DIRECTION_HEIGHT ) ) {
		_separate_flag = false;
		return true;
	}
	return false;
}

void IconManeger::setButtonTouch( bool flag ) {
	_button_touch = flag;
}