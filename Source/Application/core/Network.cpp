#include "Network.h"
#include "Framework.h"
#include <string>
#include <vector>

Network::Network( ) {
	// _partner_ipÇÃèâä˙âª
	_partner_ip.d1 = 255;
	_partner_ip.d2 = 255;
	_partner_ip.d3 = 255;
	_partner_ip.d4 = 255;
	_font = CreateFontToHandle( "HGPënâpäp∫ﬁºØ∏UB", 52, -1, -1 );

	GetMyIPAddress( &_ip );
}


Network::~Network( ) {
}

void Network::update( ) {

}

void Network::drawIpAddress( ) const {
	int width = GetDrawFormatStringWidthToHandle( _font, "IP : %d.%d.%d.%d", _ip.d1, _ip.d2, _ip.d3, _ip.d4 ) ;
	DrawFormatStringToHandle( SCREEN_WIDTH / 2 - width / 2, SCREEN_HEIGHT / 2, GetColor( 255 , 255, 255 ),
								_font, "IP : %d.%d.%d.%d", _ip.d1, _ip.d2, _ip.d3, _ip.d4 );
}

