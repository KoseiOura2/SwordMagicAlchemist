#include "Button.h"
#include "Framework.h"
#include "Viewer.h"
#include "mathematics.h"
#include "Touch.h"
#include "IconManeger.h"

Button::Button( NetworkControllerPtr network, IconManegerPtr icon_maneger ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	
	//デバッグ用
	//_phase = Network::CTRL_PHASE::NAVI_PHASE;
	
	_phase = Network::CTRL_PHASE::MOVE_PHASE;
	
	_network = network;
	_icon_maneger = icon_maneger;
	// 画像の読み込み
	_lower_left  = viewer->loadGraph( "work/key/lower_left.png" );
	_lower		 = viewer->loadGraph( "work/key/lower.png" );
	_lower_right = viewer->loadGraph( "work/key/lower_right.png" );	
	_left		 = viewer->loadGraph( "work/key/left.png" );
	_wait		 = viewer->loadGraph( "work/key/wait.png" );
	_right		 = viewer->loadGraph( "work/key/right.png" );
	_upper_left  = viewer->loadGraph( "work/key/upper_left.png" );
	_upper		 = viewer->loadGraph( "work/key/upper.png" );
	_upper_right = viewer->loadGraph( "work/key/upper_right.png" );

	// ボタン押し状態の画像読み込み
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
	// 画面外に出しとく
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
	
	// 移動と向き替えの切り替え処理
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
		// スライド用の変数にタッチ座標を入れる処理
		_slide_pos = touch->getTouch( );
		_slide = _pos - _slide_pos;		// 最初にタッチした場所から現在の位置を引いて差を出す

		// _slideの値を元に方向を決める
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
			 _wait_count++;	// wait用の長押しカウントを増やす
			 _push_state = WAIT;
		}

		// waitの処理
		if ( _wait_flag && _wait_count >= WAIT_DELAY ) {	// 2回目以降のwait処理
			 _network->setSendDir( Network::CTRL_DIR::WAIT, _phase );
			 _wait_count = 0;
		} else if ( _wait_count >= PUSH_TIME ) {			// 1回目のwait処理
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

// 以下ボタン描画用関数のみ
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

	// 関数ポインタの配列
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
