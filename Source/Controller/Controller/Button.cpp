#include "Button.h"
#include "Framework.h"
#include "Viewer.h"
#include "mathematics.h"
#include "Touch.h"
#include "IconManeger.h"

Button::Button( NetworkControllerPtr network, IconManegerPtr icon_maneger ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	
	//�f�o�b�O�p
	//_phase = Network::CTRL_PHASE::NAVI_PHASE;
	
	_phase = Network::CTRL_PHASE::MOVE_PHASE;
	
	_network = network;
	_icon_maneger = icon_maneger;
	// �摜�̓ǂݍ���
	_lower_left  = viewer->loadGraph( "work/key/lower_left.png" );
	_lower		 = viewer->loadGraph( "work/key/lower.png" );
	_lower_right = viewer->loadGraph( "work/key/lower_right.png" );	
	_left		 = viewer->loadGraph( "work/key/left.png" );
	_wait		 = viewer->loadGraph( "work/key/wait.png" );
	_right		 = viewer->loadGraph( "work/key/right.png" );
	_upper_left  = viewer->loadGraph( "work/key/upper_left.png" );
	_upper		 = viewer->loadGraph( "work/key/upper.png" );
	_upper_right = viewer->loadGraph( "work/key/upper_right.png" );

	// �{�^��������Ԃ̉摜�ǂݍ���
	_lower_left_push  = viewer->loadGraph( "work/key/lower_left_push.png" );
	_lower_push		  = viewer->loadGraph( "work/key/lower_push.png" );
	_lower_right_push = viewer->loadGraph( "work/key/lower_right_push.png" );	
	_left_push		  = viewer->loadGraph( "work/key/left_push.png" );
	_wait_push		  = viewer->loadGraph( "work/key/wait_push.png" );
	_right_push		  = viewer->loadGraph( "work/key/right_push.png" );
	_upper_left_push  = viewer->loadGraph( "work/key/upper_left_push.png" );
	_upper_push		  = viewer->loadGraph( "work/key/upper_push.png" );
	_upper_right_push = viewer->loadGraph( "work/key/upper_right_push.png" );
	
	_separate_flag = false;
	_attack_count = 0;
	// ��ʊO�ɏo���Ƃ�
	reset( );
}

Button::~Button( ) {
}

void Button::update( ) {
	FrameworkPtr fw = Framework::getInstance( );
	TouchPtr touch = std::dynamic_pointer_cast< Touch >( fw->getTask( typeid( Touch ).name( ) ) );
	
	if ( touch->isTouch( Vector2 ( 0, 0 ), SCREEN_WIDTH, SCREEN_HEIGHT - 200 ) ) {
		_touch_flag = true;
		draw( );
		attack( );
		move( );
	} else if ( _touch_flag == true && touch->isTouch( Vector2 ( 0, 0 ), SCREEN_WIDTH, SCREEN_HEIGHT ) ) {
		_touch_flag = true;
		draw( );
		attack( );
		move( );
	} else {
		reset( );
	}
	
	// �ړ��ƌ����ւ��̐؂�ւ�����
	if ( _icon_maneger->isTouchDir( ) == true ) {
		if ( _phase == Network::CTRL_PHASE::MOVE_PHASE ) {
			_phase = Network::CTRL_PHASE::NAVI_PHASE;
			_network->setSendPhase( _phase );
		} else {
			_phase = Network::CTRL_PHASE::MOVE_PHASE;
			_network->setSendPhase( _phase );
		}
	}

	if ( touch->isSeparate( ) ) {
		_separate_flag = true;
	}

	if ( _separate_flag == true ) {
		_attack_count++;
		if ( _attack_count >= ATTACK_DELAY ) {
			_separate_flag = false;
			_attack_count = 0;
		}
	}

}

bool Button::getButtonTouch( ) {
	return _touch_flag;
}

void Button::attack( ) {
	FrameworkPtr fw = Framework::getInstance( );
	TouchPtr touch = std::dynamic_pointer_cast< Touch >( fw->getTask( typeid( Touch ).name( ) ) );

	if ( _separate_flag == true ) {
		_network->setSendAttack( true ); 
	}
}

void Button::move( ) {
	FrameworkPtr fw = Framework::getInstance( );
	TouchPtr touch = std::dynamic_pointer_cast< Touch >( fw->getTask( typeid( Touch ).name( ) ) );

	if ( touch->getState( ) == Touch::BEGIN ) {
		_pos = touch->getTouch( );
		_slide_pos = Vector2( );

	} else if ( touch->getState( ) == Touch::MOVE ) {
		// �X���C�h�p�̕ϐ��Ƀ^�b�`���W�����鏈��
		_slide_pos = touch->getTouch( );
		_slide = _pos - _slide_pos;		// �ŏ��Ƀ^�b�`�����ꏊ���猻�݂̈ʒu�������č����o��

		// _slide�̒l�����ɕ��������߂�
		if ( _slide.x <= -SLANT_DISTANCE && _slide.y <= -SLANT_DISTANCE ) {
			 _network->setSendDir( Network::CTRL_DIR::LOWER_RIGHT, _phase );
			 _push_state = LOWER_RIGHT;
		} else if ( _slide.x >= SLANT_DISTANCE && _slide.y <= -SLANT_DISTANCE ) {
			 _network->setSendDir( Network::CTRL_DIR::LOWER_LEFT, _phase );
			 _push_state = LOWER_LEFT;
		} else if ( _slide.x <= -SLANT_DISTANCE && _slide.y >= SLANT_DISTANCE ) {
			 _network->setSendDir( Network::CTRL_DIR::UPPER_RIGHT, _phase );
			 _push_state = UPPER_RIGHT;
		} else if ( _slide.x >= SLANT_DISTANCE && _slide.y >= SLANT_DISTANCE ) {
			 _network->setSendDir( Network::CTRL_DIR::UPPER_LEFT, _phase );
			 _push_state = UPPER_LEFT;
		} else if ( _slide.x <= -SLIDE_DISTANCE ) {
			 _network->setSendDir( Network::CTRL_DIR::RIGHT, _phase );
			 _push_state = RIGHT;
		} else if ( _slide.x >= SLIDE_DISTANCE ) {
			 _network->setSendDir( Network::CTRL_DIR::LEFT, _phase );
			 _push_state = LEFT;
		} else if ( _slide.y <= -SLIDE_DISTANCE ) {
			 _network->setSendDir( Network::CTRL_DIR::LOWER, _phase );
			 _push_state = LOWER;
		} else if ( _slide.y >= SLIDE_DISTANCE ) {
			 _network->setSendDir( Network::CTRL_DIR::UPPER, _phase );
			 _push_state = UPPER;
		} else {
			 _wait_count++;	// wait�p�̒������J�E���g�𑝂₷
			 _push_state = WAIT;
		}

		// wait�̏���
		if ( _wait_flag && _wait_count >= WAIT_DELAY ) {	// 2��ڈȍ~��wait����
			 _network->setSendDir( Network::CTRL_DIR::WAIT, _phase );
			 _wait_count = 0;
		} else if ( _wait_count >= PUSH_TIME ) {			// 1��ڂ�wait����
			if ( _wait_flag == false ) { 
				_network->setSendDir( Network::CTRL_DIR::WAIT, _phase );
				_wait_count = 0;
				_wait_flag = true;
			}
		} 
	}
}

void Button::reset( ) {
	_pos = Vector2 ( -1000, -1000 );
	_wait_count = 0;
	_touch_flag = false;
	_wait_flag = false;

	_push_state = NONE;
	_network->setSendDir( Network::CTRL_DIR::NONE, _phase );
}

// �ȉ��{�^���`��p�֐��̂�
void Button::drawNone( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	Vector2 pos = _pos - Vector2( IMAGE_SIZE / 2, IMAGE_SIZE / 2 );

	viewer->drawGraph( ( int )pos.x - WIDTH_INTERVAL, ( int )pos.y + HEIGHT_INTERVAL, _lower_left );
	viewer->drawGraph( ( int )pos.x,				   ( int )pos.y + HEIGHT_INTERVAL, _lower );
	viewer->drawGraph( ( int )pos.x + WIDTH_INTERVAL, ( int )pos.y + HEIGHT_INTERVAL, _lower_right );
	viewer->drawGraph( ( int )pos.x - WIDTH_INTERVAL, ( int )pos.y, _left );
	viewer->drawGraph( ( int )pos.x,				   ( int )pos.y, _wait );
	viewer->drawGraph( ( int )pos.x + WIDTH_INTERVAL, ( int )pos.y, _right );
	viewer->drawGraph( ( int )pos.x - WIDTH_INTERVAL, ( int )pos.y - HEIGHT_INTERVAL, _upper_left );
	viewer->drawGraph( ( int )pos.x,				   ( int )pos.y - HEIGHT_INTERVAL, _upper );
	viewer->drawGraph( ( int )pos.x + WIDTH_INTERVAL, ( int )pos.y - HEIGHT_INTERVAL, _upper_right );
};

void Button::drawLowerLeft( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	Vector2 pos = _pos - Vector2( IMAGE_SIZE / 2, IMAGE_SIZE / 2 );

	viewer->drawGraph( ( int )pos.x - WIDTH_INTERVAL, ( int )pos.y + HEIGHT_INTERVAL, _lower_left_push );
	viewer->drawGraph( ( int )pos.x,				   ( int )pos.y + HEIGHT_INTERVAL, _lower );
	viewer->drawGraph( ( int )pos.x + WIDTH_INTERVAL, ( int )pos.y + HEIGHT_INTERVAL, _lower_right );
	viewer->drawGraph( ( int )pos.x - WIDTH_INTERVAL, ( int )pos.y, _left );
	viewer->drawGraph( ( int )pos.x,				   ( int )pos.y, _wait );
	viewer->drawGraph( ( int )pos.x + WIDTH_INTERVAL, ( int )pos.y, _right );
	viewer->drawGraph( ( int )pos.x - WIDTH_INTERVAL, ( int )pos.y - HEIGHT_INTERVAL, _upper_left );
	viewer->drawGraph( ( int )pos.x,				   ( int )pos.y - HEIGHT_INTERVAL, _upper );
	viewer->drawGraph( ( int )pos.x + WIDTH_INTERVAL, ( int )pos.y - HEIGHT_INTERVAL, _upper_right );
};

void Button::drawLower( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	Vector2 pos = _pos - Vector2( IMAGE_SIZE / 2, IMAGE_SIZE / 2 );

	viewer->drawGraph( ( int )pos.x - WIDTH_INTERVAL, ( int )pos.y + HEIGHT_INTERVAL, _lower_left );
	viewer->drawGraph( ( int )pos.x,				   ( int )pos.y + HEIGHT_INTERVAL, _lower_push );
	viewer->drawGraph( ( int )pos.x + WIDTH_INTERVAL, ( int )pos.y + HEIGHT_INTERVAL, _lower_right );
	viewer->drawGraph( ( int )pos.x - WIDTH_INTERVAL, ( int )pos.y, _left );
	viewer->drawGraph( ( int )pos.x,				   ( int )pos.y, _wait );
	viewer->drawGraph( ( int )pos.x + WIDTH_INTERVAL, ( int )pos.y, _right );
	viewer->drawGraph( ( int )pos.x - WIDTH_INTERVAL, ( int )pos.y - HEIGHT_INTERVAL, _upper_left );
	viewer->drawGraph( ( int )pos.x,				   ( int )pos.y - HEIGHT_INTERVAL, _upper );
	viewer->drawGraph( ( int )pos.x + WIDTH_INTERVAL, ( int )pos.y - HEIGHT_INTERVAL, _upper_right );
};

void Button::drawLowerRight( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	Vector2 pos = _pos - Vector2( IMAGE_SIZE / 2, IMAGE_SIZE / 2 );

	viewer->drawGraph( ( int )pos.x - WIDTH_INTERVAL, ( int )pos.y + HEIGHT_INTERVAL, _lower_left );
	viewer->drawGraph( ( int )pos.x,				   ( int )pos.y + HEIGHT_INTERVAL, _lower );
	viewer->drawGraph( ( int )pos.x + WIDTH_INTERVAL, ( int )pos.y + HEIGHT_INTERVAL, _lower_right_push );
	viewer->drawGraph( ( int )pos.x - WIDTH_INTERVAL, ( int )pos.y, _left );
	viewer->drawGraph( ( int )pos.x,				   ( int )pos.y, _wait );
	viewer->drawGraph( ( int )pos.x + WIDTH_INTERVAL, ( int )pos.y, _right );
	viewer->drawGraph( ( int )pos.x - WIDTH_INTERVAL, ( int )pos.y - HEIGHT_INTERVAL, _upper_left );
	viewer->drawGraph( ( int )pos.x,				   ( int )pos.y - HEIGHT_INTERVAL, _upper );
	viewer->drawGraph( ( int )pos.x + WIDTH_INTERVAL, ( int )pos.y - HEIGHT_INTERVAL, _upper_right );
};

void Button::drawLeft( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	Vector2 pos = _pos - Vector2( IMAGE_SIZE / 2, IMAGE_SIZE / 2 );

	viewer->drawGraph( ( int )pos.x - WIDTH_INTERVAL, ( int )pos.y + HEIGHT_INTERVAL, _lower_left );
	viewer->drawGraph( ( int )pos.x,				   ( int )pos.y + HEIGHT_INTERVAL, _lower );
	viewer->drawGraph( ( int )pos.x + WIDTH_INTERVAL, ( int )pos.y + HEIGHT_INTERVAL, _lower_right );
	viewer->drawGraph( ( int )pos.x - WIDTH_INTERVAL, ( int )pos.y, _left_push );
	viewer->drawGraph( ( int )pos.x,				   ( int )pos.y, _wait );
	viewer->drawGraph( ( int )pos.x + WIDTH_INTERVAL, ( int )pos.y, _right );
	viewer->drawGraph( ( int )pos.x - WIDTH_INTERVAL, ( int )pos.y - HEIGHT_INTERVAL, _upper_left );
	viewer->drawGraph( ( int )pos.x,				   ( int )pos.y - HEIGHT_INTERVAL, _upper );
	viewer->drawGraph( ( int )pos.x + WIDTH_INTERVAL, ( int )pos.y - HEIGHT_INTERVAL, _upper_right );
};

void Button::drawWait( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	Vector2 pos = _pos - Vector2( IMAGE_SIZE / 2, IMAGE_SIZE / 2 );

	viewer->drawGraph( ( int )pos.x - WIDTH_INTERVAL, ( int )pos.y + HEIGHT_INTERVAL, _lower_left );
	viewer->drawGraph( ( int )pos.x,				   ( int )pos.y + HEIGHT_INTERVAL, _lower );
	viewer->drawGraph( ( int )pos.x + WIDTH_INTERVAL, ( int )pos.y + HEIGHT_INTERVAL, _lower_right );
	viewer->drawGraph( ( int )pos.x - WIDTH_INTERVAL, ( int )pos.y, _left );
	viewer->drawGraph( ( int )pos.x,				   ( int )pos.y, _wait );
	viewer->drawGraph( ( int )pos.x + WIDTH_INTERVAL, ( int )pos.y, _right );
	viewer->drawGraph( ( int )pos.x - WIDTH_INTERVAL, ( int )pos.y - HEIGHT_INTERVAL, _upper_left );
	viewer->drawGraph( ( int )pos.x,				   ( int )pos.y - HEIGHT_INTERVAL, _upper );
	viewer->drawGraph( ( int )pos.x + WIDTH_INTERVAL, ( int )pos.y - HEIGHT_INTERVAL, _upper_right );
};

void Button::drawRight( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	Vector2 pos = _pos - Vector2( IMAGE_SIZE / 2, IMAGE_SIZE / 2 );

	viewer->drawGraph( ( int )pos.x - WIDTH_INTERVAL, ( int )pos.y + HEIGHT_INTERVAL, _lower_left );
	viewer->drawGraph( ( int )pos.x,				   ( int )pos.y + HEIGHT_INTERVAL, _lower );
	viewer->drawGraph( ( int )pos.x + WIDTH_INTERVAL, ( int )pos.y + HEIGHT_INTERVAL, _lower_right );
	viewer->drawGraph( ( int )pos.x - WIDTH_INTERVAL, ( int )pos.y, _left );
	viewer->drawGraph( ( int )pos.x,				   ( int )pos.y, _wait );
	viewer->drawGraph( ( int )pos.x + WIDTH_INTERVAL, ( int )pos.y, _right_push );
	viewer->drawGraph( ( int )pos.x - WIDTH_INTERVAL, ( int )pos.y - HEIGHT_INTERVAL, _upper_left );
	viewer->drawGraph( ( int )pos.x,				   ( int )pos.y - HEIGHT_INTERVAL, _upper );
	viewer->drawGraph( ( int )pos.x + WIDTH_INTERVAL, ( int )pos.y - HEIGHT_INTERVAL, _upper_right );
};

void Button::drawUpperLeft( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	Vector2 pos = _pos - Vector2( IMAGE_SIZE / 2, IMAGE_SIZE / 2 );

	viewer->drawGraph( ( int )pos.x - WIDTH_INTERVAL, ( int )pos.y + HEIGHT_INTERVAL, _lower_left );
	viewer->drawGraph( ( int )pos.x,				   ( int )pos.y + HEIGHT_INTERVAL, _lower );
	viewer->drawGraph( ( int )pos.x + WIDTH_INTERVAL, ( int )pos.y + HEIGHT_INTERVAL, _lower_right );
	viewer->drawGraph( ( int )pos.x - WIDTH_INTERVAL, ( int )pos.y, _left );
	viewer->drawGraph( ( int )pos.x,				   ( int )pos.y, _wait );
	viewer->drawGraph( ( int )pos.x + WIDTH_INTERVAL, ( int )pos.y, _right );
	viewer->drawGraph( ( int )pos.x - WIDTH_INTERVAL, ( int )pos.y - HEIGHT_INTERVAL, _upper_left_push );
	viewer->drawGraph( ( int )pos.x,				   ( int )pos.y - HEIGHT_INTERVAL, _upper );
	viewer->drawGraph( ( int )pos.x + WIDTH_INTERVAL, ( int )pos.y - HEIGHT_INTERVAL, _upper_right );
};

void Button::drawUpper( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	Vector2 pos = _pos - Vector2( IMAGE_SIZE / 2, IMAGE_SIZE / 2 );

	viewer->drawGraph( ( int )pos.x - WIDTH_INTERVAL, ( int )pos.y + HEIGHT_INTERVAL, _lower_left );
	viewer->drawGraph( ( int )pos.x,				   ( int )pos.y + HEIGHT_INTERVAL, _lower );
	viewer->drawGraph( ( int )pos.x + WIDTH_INTERVAL, ( int )pos.y + HEIGHT_INTERVAL, _lower_right );
	viewer->drawGraph( ( int )pos.x - WIDTH_INTERVAL, ( int )pos.y, _left );
	viewer->drawGraph( ( int )pos.x,				   ( int )pos.y, _wait );
	viewer->drawGraph( ( int )pos.x + WIDTH_INTERVAL, ( int )pos.y, _right );
	viewer->drawGraph( ( int )pos.x - WIDTH_INTERVAL, ( int )pos.y - HEIGHT_INTERVAL, _upper_left );
	viewer->drawGraph( ( int )pos.x,				   ( int )pos.y - HEIGHT_INTERVAL, _upper_push );
	viewer->drawGraph( ( int )pos.x + WIDTH_INTERVAL, ( int )pos.y - HEIGHT_INTERVAL, _upper_right );
};

void Button::drawUpperRight( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	Vector2 pos = _pos - Vector2( IMAGE_SIZE / 2, IMAGE_SIZE / 2 );

	viewer->drawGraph( ( int )pos.x - WIDTH_INTERVAL, ( int )pos.y + HEIGHT_INTERVAL, _lower_left );
	viewer->drawGraph( ( int )pos.x,				   ( int )pos.y + HEIGHT_INTERVAL, _lower );
	viewer->drawGraph( ( int )pos.x + WIDTH_INTERVAL, ( int )pos.y + HEIGHT_INTERVAL, _lower_right );
	viewer->drawGraph( ( int )pos.x - WIDTH_INTERVAL, ( int )pos.y, _left );
	viewer->drawGraph( ( int )pos.x,				   ( int )pos.y, _wait );
	viewer->drawGraph( ( int )pos.x + WIDTH_INTERVAL, ( int )pos.y, _right );
	viewer->drawGraph( ( int )pos.x - WIDTH_INTERVAL, ( int )pos.y - HEIGHT_INTERVAL, _upper_left );
	viewer->drawGraph( ( int )pos.x,				   ( int )pos.y - HEIGHT_INTERVAL, _upper );
	viewer->drawGraph( ( int )pos.x + WIDTH_INTERVAL, ( int )pos.y - HEIGHT_INTERVAL, _upper_right_push );
};

void Button::draw( ) {

	// �֐��|�C���^�̔z��
	void ( Button::* funcArray[ ] )( void ) = {
		&Button::drawNone,
		&Button::drawLowerLeft,
		&Button::drawLower,
		&Button::drawLowerRight,
		&Button::drawLeft,
		&Button::drawWait,
		&Button::drawRight,
		&Button::drawUpperLeft,
		&Button::drawUpper,
		&Button::drawUpperRight,
	};
	void ( Button::*func )( void ) = funcArray[ _push_state ];
	( this->*func )( );

}
