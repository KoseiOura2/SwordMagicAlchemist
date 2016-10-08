#pragma once
#include "Task.h"
#include "DxLib.h"
#include "mathematics.h"

PTR( Touch );

const int MAX_TOUCH = 3;	// マルチタップの最高認識数
const int BUFFER_COUNT = 5; // この数字分タッチされていなかったらポイントを初期化
const int REJECT_TIME = 3;
class Touch : public Task {
public:
	enum TOUCH_STATE {
		NONE,
		BEGIN,
		MOVE
	};

public:
	Touch( );
	virtual ~Touch( );
	void update( );
	Vector2 getTouch( );
	bool isTouch( );
	bool isTouch( Vector2 pos, int width, int height );
	bool isSeparate( );
	void setTouch( int x, int y, int num );
	TOUCH_STATE getState( );
	Vector2 getSlideNum( );
	virtual void initialize( );
	virtual void finalize( );
	void rejectTouch( );
private:
	void setClick( );
	void setSlide( );
private:
	TOUCH_STATE _state;
	TOUCH_STATE _old_state;
	Vector2 _pos;
	Vector2 _old_pos;
	Vector2 _array_pos[ MAX_TOUCH ];
	bool _mouse_flag;
	bool _touch_flag;
	bool _reject_flag;
	int _max_touch;
	int _count;
	Vector2 _slide_num;
};

