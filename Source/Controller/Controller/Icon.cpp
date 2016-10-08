#include "Icon.h"
#include "Framework.h"
#include "Viewer.h"

Icon::Icon( Vector2 pos ) {
	_pos = pos;
	_message_font = CreateFontToHandle( "HGPënâpäp∫ﬁºØ∏UB", FONT_SIZE, 0, -1 );
	_small_font = CreateFontToHandle( "HGPënâpäp∫ﬁºØ∏UB", FONT_SMALL_SIZE, 0, -1 );
}


Icon::~Icon( ) {
}

void Icon::draw( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	viewer->drawGraph( _pos.x, _pos.y, _image );
}

void Icon::touch( ) {
}

void Icon::close( ) {
}

void Icon::drawString( Vector2 pos , const std::string str ) {
	unsigned int color = GetColor( 255, 255, 255 ) ;
	DrawFormatStringToHandle( ( int )pos.x, ( int )pos.y, color, _message_font, str.c_str( ) );
}

void Icon::drawString( Vector2 pos, char * format, ... ) {
	va_list args;
	char buffer[ 1024 ];
	va_start( args, format );
	vsprintf_s( buffer, 1024, format, args );

	unsigned int color = GetColor( 255, 255, 255 );
	DrawStringToHandle( ( int )pos.x, ( int )pos.y, buffer, color, _message_font );
}

void Icon::drawString( Vector2 pos, const std::string str, int num ) {
	unsigned int color = GetColor( 255, 255, 255 );
	DrawFormatStringToHandle( ( int )pos.x, ( int )pos.y, color, _message_font, str.c_str( ), num );
}

void Icon::drawString( Vector2 pos, const std::string str, const std::string str_2 ) {
	unsigned int color = GetColor( 255, 255, 255 );
	DrawFormatStringToHandle( ( int )pos.x, ( int )pos.y, color, _message_font, str.c_str( ), str_2.c_str( ) );
}

void Icon::drawStringColor( Vector2 pos, const std::string str, int r, int g, int b ) {
	unsigned int color = GetColor( r, g, b );
	DrawFormatStringToHandle( ( int )pos.x, ( int )pos.y, color, _message_font, str.c_str( ) );
}

void Icon::drawStringColor( Vector2 pos, int r, int g, int b, const std::string str, int num ) {
	unsigned int color = GetColor( r, g, b );
	DrawFormatStringToHandle( ( int )pos.x, ( int )pos.y, color, _message_font, str.c_str( ), num );
}

void Icon::drawStringSmallFont( Vector2 pos, const std::string str ) {
	unsigned int color = GetColor( 255, 255, 255 ) ;
	DrawFormatStringToHandle( ( int )pos.x, ( int )pos.y, color, _small_font, str.c_str( ) );
}

int Icon::getStringWidth( std::string str ) {
	int length = strlen( str.c_str( ) );
	return GetDrawStringWidth( str.c_str( ), length );
}