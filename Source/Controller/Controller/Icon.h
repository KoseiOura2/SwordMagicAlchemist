#pragma once
#include "smart_ptr.h"
#include "mathematics.h"
#include "Dxlib.h"
#include <string>

PTR( Icon );

class Icon {
public:
	const int FONT_SIZE = 30;
	const int FONT_SMALL_SIZE = FONT_SIZE - 5;
public:
	Icon( Vector2 pos );
	~Icon( );
	void draw( );
	virtual void touch( );	// �A�C�R�����^�b�`���������܂ŌĂё�������֐�
	virtual void close( );	// �A�C�R���������Ƃ��ɌĂ΂��֐�
protected:
	void drawString( Vector2 pos, const std::string str );
	void drawString( Vector2 pos, char * format, ... );
	void drawString( Vector2 pos, const std::string str, int num );
	void drawString( Vector2 pos, const std::string str, const std::string str_2 );
	void drawStringColor( Vector2 pos, const std::string str, int r, int g, int b );
	void drawStringColor( Vector2 pos, int r, int g, int b, const std::string str, int num );
	void drawStringSmallFont( Vector2 pos, const std::string str );
	int getStringWidth( std::string str );
protected:
	int _image;
	Vector2 _pos;
	int _width;
	int _height;
	int _message_font;
	int _small_font;	// �������ȂǂɎg���������t�H���g
};

