#include "Foot.h"
#include "Framework.h"
#include "Viewer.h"
#include "NextFloor.h"
#include "NetworkController.h"
#include "Item.h"

Foot::Foot( Vector2 pos, NetworkControllerPtr network, NextFloorPtr next_floor, ItemPtr item ) : Icon( pos ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	_image = viewer->loadGraph( "work/ctrl_UI/foot.png" );	
	_next_floor = next_floor;
	_network = network;
	_item = item;

	_foot_open = false;
}


Foot::~Foot( ) {
}

void Foot::close( ) {
	_foot_open = false;
}

void Foot::touch( ) {
	if ( _network->getFoot( ) == Network::FOOT_THING::FOOT_STAIR ) {
		_next_floor->setCheckFlag( true );
	} else if ( _network->getFoot( ) == Network::FOOT_THING::FOOT_ITEM && _item->getFootItem( ).type.id != ITEM_NONE ) {
		_foot_open = true;
	}
}

bool Foot::isFootItem( ) {
	return _foot_open;
}
