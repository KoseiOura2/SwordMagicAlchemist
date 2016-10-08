#include "Application.h"
#include "NetworkController.h"
#include "IconManeger.h"
#include "Viewer.h"
#include "NextFloor.h"
#include "Map.h"
#include "Title.h"
#include "Button.h"
#include "Camera.h"
#include "Keyboard.h"
#include "UI.h"

Application::Application( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	_back_ctrl = viewer->loadGraph( "work/background/ctrl_back.jpg" );
	_stairs_flag = false;
	_separate_flag = false;
	_next_floor_in_out_scene = false;
	_next_floor_tile_finish = false;
	_scene = SCENE_CONTROLLER;
	//_scene = SCENE_CONNECT;
	//_scene = SCENE_NEXT_FLOOR;
	_camera = CameraPtr( new Camera( ) );
	_network = NetworkControllerPtr( new NetworkController( ) );
	_next_floor = NextFloorPtr( new NextFloor( _network ) );
	_map = MapPtr( new Map( _network ) );
	_icon_maneger = IconManegerPtr( new IconManeger( _network, _map, _camera, _next_floor ) );
	_button = ButtonPtr( new Button( _network, _icon_maneger ) );
	_title = TitlePtr( new Title( ) );
	_ui = UIPtr( new UI( _network ) );
}

Application::~Application( ) {
}

void Application::initialize( ) {

}

void Application::finalize( ) {

}

void Application::update( ) {
	FrameworkPtr fw = Framework::getInstance( );
	TouchPtr touch = std::dynamic_pointer_cast< Touch >( fw->getTask( typeid( Touch ).name( ) ) );
	KeyboardPtr keyboard = std::dynamic_pointer_cast< Keyboard >( fw->getTask( typeid( Keyboard ).name( ) ) );
	switch ( _scene ) {
	case SCENE_CONNECT:
		updateConnect( );
		break;
	case SCENE_INIT:
		init( );
		break;
	case SCENE_TITLE:
		updateTitle( );
		break;
	case SCENE_NEXT_FLOOR:
		updateNextFloor( );
		break;
	case SCENE_CONTROLLER:
		updateController( );
		break;
	case SCENE_FINISH:
		updateFinish( );
		break;
	}

	// I—¹ˆ—
	if ( keyboard->isPushKey( "DEL" ) ) {
		_network->setSendFinishApp( true );
		_network->send( );
		fw->end( );
	}

	// ‰Šú‰»ˆ—
	if ( keyboard->isPushKey( "ENTER" ) ) {
		_network->setSendReturnTitle( true );
		_network->send( );
		_scene = SCENE_INIT;
	}
}

void Application::updateConnect( ) {
	_network->connectNetwork( );
	_scene = SCENE_TITLE;
}

void Application::init( ) {
	_map->init( );
	_icon_maneger->init( );
	_next_floor->init( );
	_scene = SCENE_TITLE;
}

void Application::updateTitle( ) {
	FrameworkPtr fw = Framework::getInstance( );
	TouchPtr touch = std::dynamic_pointer_cast< Touch >( fw->getTask( typeid( Touch ).name( ) ) );

	_title->update( );

	if( touch->isTouch( ) == true ) {
		_network->setSendGoGame( true );
		_scene = SCENE_NEXT_FLOOR;
		_network->send( );
		
	}
}
void Application::updateNextFloor( ) {

	_map->mapChipNextFloor( );
	_network->send( );	
	_network->recv( );
	if ( _network->isInOutScene( ) == true ) {
		_next_floor_in_out_scene = true;
	}
	if ( _network->isTileFinish( ) == true ) {
		_next_floor_tile_finish = true;
	}
	if ( _next_floor_in_out_scene == true && _next_floor_tile_finish == true ) {
		_scene = SCENE_CONTROLLER;
		_network->resetRecv( );
		_next_floor_in_out_scene = false;
		_next_floor_tile_finish = false;
		_next_floor->init( );
	}
}

void Application::updateController( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	viewer->drawGraph( 0, 0, _back_ctrl );

	_network->recv( );
	_ui->update( );
	// ƒQ[ƒ€I—¹Žž‚Ìˆ—
	if ( _network->isFinish( ) == true ) {
		_scene = SCENE_FINISH;
	}
	
	if ( _network->isInOutScene( ) == true ) {
		_scene = SCENE_NEXT_FLOOR;
		_stairs_flag = false;
		_map->init( );
		_network->resetRecv( ); 
	} else if ( _next_floor->isGoNext( ) == false ) {
		_map->update( );
	}

	_camera->update( );
	_icon_maneger->update( );

	if ( _icon_maneger->isOpenIcon( ) == false && _next_floor->getCheckFlag( ) == false ) {
		_button->update( );
	}
	if ( _button->getButtonTouch( ) == false ) {
		_icon_maneger->touch( );
	}
	//-----------ŠK’iˆÚ“®ˆ—------------
	if ( _network->getFoot( ) == Network::FOOT_STAIR && _network->isRide( ) == true ) {
		_next_floor->setCheckFlag( true );
		_network->resetRide( );
	}

	_next_floor->update( );

	//-------ŠK’iˆÚ“®ˆ—‚±‚±‚Ü‚Å--------

	_network->send( );	
	
}

void Application::updateFinish( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	TouchPtr touch = std::dynamic_pointer_cast< Touch >( fw->getTask( typeid( Touch ).name( ) ) );

	viewer->drawGraph( 0, 0, _back_ctrl );

	_network->recv( );

	if ( touch->isSeparate( ) == true ) {
		_network->setSendGoTitle( true );
		_scene = SCENE_INIT;
	}

	_network->send( );	
}