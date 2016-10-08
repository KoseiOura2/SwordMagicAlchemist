#include "UI.h"
#include "viewer.h"
#include "NetworkController.h"
#include "Dxlib.h"

UI::UI( NetworkControllerPtr network ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	_count = 0;
	_state_set = false;

	_hp_bar = viewer->loadGraph( "work/ctrl_UI/hp_bar/hp_bar.png" );
	_hp_gauge = viewer->loadGraph( "work/ctrl_UI/hp_bar/hp_gauge.png" );
	_hp_font = CreateFontToHandle( "HGPënâpäp∫ﬁºØ∏UB", HP_FONT_SIZE, -1, DX_FONTTYPE_EDGE );

	_stamina_bar = viewer->loadGraph( "work/ctrl_UI/stamina/ui_pc_hunger_meter_1.png" );
	_stamina_gauge = viewer->loadGraph( "work/ctrl_UI/stamina/ui_pc_hunger_meter_2.png" );
	_stamina_font = CreateFontToHandle( "HGPënâpäp∫ﬁºØ∏UB", STAMINA_FONT_SIZE, -1, -1 );

	_default_font = CreateFontToHandle( "HGPënâpäp∫ﬁºØ∏UB", DEFAULT_FONT, -1, -1 );

	_poison = viewer->loadGraph( "work/ctrl_UI/status/poison.png" );    
	_paralysis = viewer->loadGraph( "work/ctrl_UI/status/paralysis.png" );	
	_skill_seal = viewer->loadGraph( "work/ctrl_UI/status/skill_seal.png" );
	_bind_tile = viewer->loadGraph( "work/ctrl_UI/status/work_seal.png" );	
	_confuse = viewer->loadGraph( "work/ctrl_UI/status/confuse.png" );;	

	_slow = viewer->loadGraph( "work/ctrl_UI/status/slow.png" );		
	_fast = viewer->loadGraph( "work/ctrl_UI/status/fast.png" );

	_buff = viewer->loadGraph( "work/ctrl_UI/status/buff.png" );
	_debuff = viewer->loadGraph( "work/ctrl_UI/status/debuff.png" );

	_network = network;

	_num_image = 0;
	_image_set = false;
}


UI::~UI( ) {
}

void UI::update( ) {
	// UIï\é¶ópÇÃÉXÉeÅ[É^ÉXÉfÅ[É^Çï€ë∂
	_status = _network->getStatusData( );
	_stamina = _network->getStamina( );
	_level = _network->getLevel( );
	_floor_level = _network->getFloorLevel( );
	
	// ÉfÉoÉbÉOóp
	/*_stamina = 100;
	
	STATUS_DATA status;
	status.life = 200;
	status.max_life = 300;
	status.state = STATE::NORMAL_STATE;
	status.speed = SPEED::FAST;
	status.buff = BUFF_STATE::BUFF;

	_status = status;

	_level = 10;
	_floor_level = 10;*/
	
	

	//setStateImage

	if ( _status.state != _old_status.state ||
		 _status.speed != _old_status.speed ||
		 _status.buff != _old_status.buff )	{
		_image_vector.clear( );
		setStateImage( );
		_num_image = 0;
	} 
	if ( _status.state == STATE::NORMAL_STATE &&
		 _status.speed == SPEED::NORMAL_SPEED &&
		 _status.buff == BUFF_STATE::NO_BUFF )	{
		_num_image = STATE_ALL_NORMAL;
		_image_vector.clear( );
	}

	_count++;

	draw( );

	if ( _count == STATE_CHANGE_TIME ) {
		_count = 0;
		_num_image++;
		if ( _num_image >= _image_vector.size( ) ) {
			_num_image = 0;
		}
	}

	_old_status = _status;
}

void UI::setStateImage( ) {
	if ( _status.state != STATE::NORMAL_STATE ) {
		_image_vector.push_back( getStateImage( ) );
	}
	if ( _status.speed != SPEED::NORMAL_SPEED ) {
		_image_vector.push_back( getSpeedImage( ) );
	}
	if ( _status.buff != BUFF_STATE::NO_BUFF ) {
		_image_vector.push_back( getBuffImage( ) );
	}
}

void UI::draw( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	
	drawLevel( );
	drawFloorLevel( );
	drawHPBar( );
	drawStamina( );

	bool state_flag = false;
	bool speed_flag = false;
	bool buff_flag = false;
	int add = 0;

	if ( _num_image != STATE_ALL_NORMAL ) {
		viewer->drawGraph( STATE_POS_X, STATE_POS_Y, _image_vector.at( _num_image ) );
	}
	// éÌóﬁÇ™ÇPÇ¬ÇÃéû
	/*if ( add == 1 ) {
		if ( state_flag == true ) {
			drawState( );
		} else if ( speed_flag == true ) {
			drawSpeed( );
		} else if ( buff_flag == true ) {
			drawBuff( );
		}
	} else if ( add == 2 ) {
		if ( state_flag == true ) {
			drawState( );
		} 
		if ( speed_flag == true ) {
			drawSpeed( );
		} 
		if ( buff_flag == true ) {
			drawBuff( );
		}
	} else if ( add == 3 ) {

		drawState( );
		drawSpeed( );
		drawBuff( );
	}*/
}
void UI::drawLevel( ) {
	std::string level_str = "LV %d";
	DrawFormatStringToHandle( LEVEL_POS_X, LEVEL_POS_Y, GetColor( 255, 255, 255 ), _default_font, level_str.c_str( ), _level );
}

void UI::drawFloorLevel( ) {
	std::string floor_str = "B%dF";
	DrawFormatStringToHandle( FLOOR_POS_X, FLOOR_POS_Y, GetColor( 255, 255, 255 ), _default_font, floor_str.c_str( ), _floor_level );
}

void UI::drawHPBar( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	int hp_gauge_pos = HP_WIDTH * _status.life / _status.max_life;

	viewer->drawRectGraph( HP_POS_X, HP_POS_Y, 0, 0, hp_gauge_pos, HP_HEIGHT, _hp_gauge );
	viewer->drawGraph( HP_POS_X, HP_POS_Y, _hp_bar );
	
	// fontê›íË
	std::string hp_str = "HP %d/%d";
	DrawFormatStringToHandle( HP_FONT_POS_X, HP_FONT_POS_Y, GetColor( 255, 255, 255 ), _hp_font, hp_str.c_str( ), _status.life, _status.max_life );
}

void UI::drawStamina( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	int stamina_gauge_pos = STAMINA_HEIGHT * _stamina / MAX_STAMINA;
	viewer->drawRectGraph( STAMINA_POS_X, STAMINA_POS_Y + ( STAMINA_HEIGHT - stamina_gauge_pos ), 0, 0, STAMINA_WIDTH, stamina_gauge_pos, _stamina_gauge );
	viewer->drawGraph( STAMINA_POS_X, STAMINA_POS_Y, _stamina_bar );

	// fontê›íË
	std::string stamina_str = "Ç®Ç»Ç©    %d";
	DrawFormatStringToHandle( STAMINA_FONT_POS_X, STAMINA_FONT_POS_Y, GetColor( 255, 255, 255 ), _stamina_font, stamina_str.c_str( ), _stamina );
}

int UI::getStateImage( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	int image = 0;
	switch ( _status.state ) {
	case STATE::POISON:
		image = _poison;
		break;
	case STATE::PARALYSIS:
		image = _paralysis;
		break;
	case STATE::SKILL_SEAL:
		image = _skill_seal;
		break;
	case STATE::BIND_TILE:
		image = _bind_tile;
		break;
	case STATE::CONFUSE:
		image = _confuse;
		break;
	}
	return image;
}
int UI::getSpeedImage( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	int image = 0;
	switch ( _status.speed ) {
		case SPEED::SLOW: {
			image = _slow;
			break;
		}
		case SPEED::FAST: {
			image = _fast;
			break;
		}
	}
	return image;
}
int UI::getBuffImage( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	int image = 0;
	switch ( _status.buff ) {
		case BUFF_STATE::BUFF: {
			image = _buff;
			break;
		}
		case BUFF_STATE::DEBUFF: {
			image = _debuff;
			break;
		}
	}
	return image;
}
