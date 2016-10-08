#include "Touch.h"
#include "Framework.h"


//POINT point;	// タッチ座標の保存用
int count = 0;				// タッチ安定用のカウント
//-----------タッチ取得用-----------
LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam ) {
	
	if ( message != WM_TOUCH ) {
		return 0;
	}
	count = 0;
	bool handled = false;
	int input_count = ( int )LOWORD( wParam );
	PTOUCHINPUT touch_input = new TOUCHINPUT[ input_count ];
	if ( touch_input ) {
		if ( GetTouchInputInfo( ( HTOUCHINPUT )lParam, input_count, touch_input, sizeof( TOUCHINPUT ) ) ) {
			for ( int i = 0; i < input_count; i++ ) {
				POINT point;
				point.x = TOUCH_COORD_TO_PIXEL( touch_input[ i ].x );
				point.y = TOUCH_COORD_TO_PIXEL( touch_input[ i ].y );
				ScreenToClient( hwnd, &point );

				FrameworkPtr fw = Framework::getInstance( );
				TouchPtr touch = std::dynamic_pointer_cast< Touch >( fw->getTask( typeid( Touch ).name( ) ) );
				touch->setTouch( point.x, point.y, i );

			}            
			handled = TRUE;
		}
		delete [] touch_input;
	}
	if ( handled ) {
		// if you handled the message, close the touch input handle and return
		CloseTouchInputHandle( ( HTOUCHINPUT )lParam );
	}

	return 0;
}
//-------------------------------------

Touch::Touch( ) {
	//-----------タッチ取得用-----------
	SetHookWinProc( WndProc ) ;
	SetUseHookWinProcReturnValue( FALSE );
	RegisterTouchWindow( GetMainWindowHandle( ), TWF_WANTPALM );

	_touch_flag = false;
	_reject_flag = false;
	_state = NONE;
	_old_state = NONE;
	_old_pos = Vector2( );
	_slide_num = Vector2( );
	_count = 0;
}

Touch::~Touch( ) {
}

void Touch::initialize( ) {

}

void Touch::finalize( ) {

}

void Touch::setTouch( int x, int y, int num ) {
	/*_array_pos [ num ].x = x;
	_array_pos [ num ].y = y;*/
	if ( _reject_flag == false ) {
		_pos.x = x;
		_pos.y = y;
		_touch_flag = true;
	} else {
		_pos.x = -1;
		_pos.y = -1;
	}
}

void Touch::setClick( ) {
	if ( GetMouseInput( ) == MOUSE_INPUT_LEFT && _reject_flag == false ) {
		int pos_x, pos_y;
		GetMousePoint( &pos_x, &pos_y );
		_pos.x = pos_x;
		_pos.y = pos_y;
		_touch_flag = true;
	}
}

void Touch::update( ) {

	if ( _reject_flag == true ) {
		int hoge = 10;
	}

	_old_state = _state;
	setClick( );
	if ( _touch_flag ) {
		if ( _state == NONE ) {
			 _state = BEGIN;
		} else {
			 _state = MOVE;
		}

		_touch_flag = false;

	} else {
		_state = NONE;
	}
	if ( _count > 0  ) {
		_count--;
	} else if ( _count <= 0 && _reject_flag == true ) {
		_reject_flag = false;
		_count = 0;
	}
	setSlide( );
	_old_pos = _pos;
}
bool Touch::isTouch( ) {

	if ( _state != NONE ) {
		return true;
	}
	return false;
}

bool Touch::isTouch( Vector2 pos, int width, int height ) {
	if ( _state == NONE ) {
		return false;
	}
	for ( int i = 0; i < MAX_TOUCH; i++ ) {
		if ( pos.x <= _pos.x &&
			pos.x + width >= _pos.x && 
			pos.y <= _pos.y &&
			pos.y + height >= _pos.y ) {
			return true;
		}
	}
	return false;
}

bool Touch::isSeparate( ) {
	if ( _old_state == MOVE && _state == NONE ) {
		return true;
	}
	return false;

}

Vector2 Touch::getTouch( ) {
	// 現状シングルのみ
	return _pos;
}

Vector2 Touch::getSlideNum( ) {
	if ( _state == MOVE ) {
		return _slide_num;
	}

	return Vector2( 0, 0 );
}

Touch::TOUCH_STATE Touch::getState( ) {
	return _state;
}

// タッチの認識を一定時間拒否する関数
void Touch::rejectTouch( ) {
	_reject_flag = true;
	_count = REJECT_TIME;
}

void Touch::setSlide( ) {
	if ( _state == MOVE ) {
		_slide_num = _pos - _old_pos;
	}
}