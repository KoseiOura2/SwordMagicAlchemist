#include "Hint.h"
#include "Framework.h"
#include "Viewer.h"

Hint::Hint( Vector2 pos ) : Icon( pos ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	_image = viewer->loadGraph( "work/ctrl_UI/hint.png" );
	_window = viewer->loadGraph( "work/ctrl_UI/hint/hint.png" );
}

Hint::~Hint( ) {
}

void Hint::touch( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	viewer->drawGraph( HINT_WINDOW_POS_X, HINT_WINDOW_POS_Y, _window );	
}