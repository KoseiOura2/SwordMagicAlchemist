#include "Option.h"
#include "Framework.h"
#include "Viewer.h"

Option::Option( Vector2 pos ) : Icon( pos ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	_image = viewer->loadGraph( "work/ctrl_UI/option.png" );	
}

Option::~Option( ) {
}

void Option::touch( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	viewer->drawGraph( _pos.x, _pos.y - 500, _image );
}