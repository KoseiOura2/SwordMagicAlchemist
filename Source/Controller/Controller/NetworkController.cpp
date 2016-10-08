#include "NetworkController.h"
#include <string>
#include <vector>

NetworkController::NetworkController( ) {
	_phase_change = false;
}


NetworkController::~NetworkController( ) {

}
bool NetworkController::connectNetwork( ) {
/*-----------接続順番------------
　コントローラを挿す
　application側でコントローラーを認識する
-------------------------------*/
	while ( true ) {
		if ( connect( ) == true ) {
			break;
		}
	}
	while ( true ) {
		connectReceive( );
		if ( _success == true ) {
			_success = false;

			break;
		}
	}

	while ( true ) {
		if ( mapConnect( ) == true ) {
			break;
		}
	}
	while ( true ) {
		connectMapReceive( );
		if ( _success == true ) {
			break;
		}
	}
	return true;
}
void NetworkController::closeNetwork( ) {
	CloseNetWork( _handle );
	CloseNetWork( _map_handle );
	_recv.~APP_DATA( );
	_send.~CTRL_DATA( );
}
bool NetworkController::connect( ) {
	static const int IP_LENGTH = 15;

	char ip_str[ IP_LENGTH + 1 ];

	if ( 2 == KeyInputString( 100, 100, IP_LENGTH, ip_str, TRUE ) ) {
		return false;
	}
	std::string str = ip_str;
	str += ".";
	std::vector< int > num;
	int pos = 0;

	while ( true ) {
		int p = str.find( '.', pos );
		std::string tmp = str.substr( pos, ( p - pos ) );
		if ( tmp.empty( ) ) {
			break;
		}

		num.push_back( atoi( tmp.c_str( ) ) );
		pos = p + 1;
	}

	if ( num.size( ) >= 4 ) {
		_partner_ip.d1 = num.at( 0 );
		_partner_ip.d2 = num.at( 1 );
		_partner_ip.d3 = num.at( 2 );
		_partner_ip.d4 = num.at( 3 );
	}

	_handle = ConnectNetWork( _partner_ip, PORT_NUM );
	
	if ( _handle != -1 ) {
		return true;
	} else {
		return false;
	}

}
bool NetworkController::mapConnect( ) {
	_map_handle = ConnectNetWork( _partner_ip, MAP_PORT_NUM );

	if ( _map_handle != -1 ) {
		return true;
	} else {
		return false;
	}

}
void NetworkController::connectReceive( ) {
	if ( GetNetWorkDataLength( _handle ) > 0 ) {
		NetWorkRecv( _handle, &_success, sizeof( _success ) );
	};
}

void NetworkController::connectMapReceive( ) {
	if ( GetNetWorkDataLength( _map_handle ) > 0 ) {
		NetWorkRecv( _map_handle, &_success, sizeof( _success ) );
	};
}

void NetworkController::setSendDir( CTRL_DIR dir, CTRL_PHASE phase ) {
	_send.dir = dir;
	_send.phase = phase;
}

void NetworkController::setSendPhase( CTRL_PHASE phase ) {
	_send.phase = phase;
	_phase_change = true;
}

void NetworkController::setSendItem( ITEM_ACTION action, ITEM_TYPE type ) {
	_send.item_action = action;
	_send.item_type = type;
}

void NetworkController::setSendItemAction( ON_ITEM on_item ) {
	_send.on_item = on_item;
};

void NetworkController::setSendAttack( bool flag ) {
	_send.attack = flag;
}

void NetworkController::setSendUseFootItem( bool flag ) {
	_send.foot_item = flag;
}

void NetworkController::setSendNextFloor( NEXT_FLOOR next_floor ) {
	_send.next_floor = next_floor;
}

void NetworkController::setSendGoGame( bool flag ) {
	_send.go_game = flag;
}

void NetworkController::setSendMagicAttack( bool flag ){
	_send.magic_attack = flag;
}

void NetworkController::setSendSkillId( SKILL_ID id ) {
	_send.skill_id = id;
}

void NetworkController::setSendRevive( REVIVE revive ) {
	_send.revive = revive;
}

void NetworkController::setSendGoTitle( bool flag ) {
	_send.go_title = flag;
}

void NetworkController::setSendFinishApp( bool flag ) {
	_send.finish_app = flag;
}

void NetworkController::setSendReturnTitle( bool flag ) {
	_send.return_title = flag;
}

void NetworkController::send( ) {

	if ( _send.dir != NONE || 
		 _send.item_action != QUIT ||
		 _send.on_item != NONE_ITEM ||
		 _send.attack != false ||
		 _send.foot_item != false ||
		 _send.next_floor != false ||
		 _send.go_game != false ||
		 _send.go_title != false ||
		 _send.finish_app != false ||
		 _send.skill_id != SKILL_NONE ||
		 _send.revive != NO_DEAD ||
		 _phase_change != false ||
		 _send.return_title != false ) {

		NetWorkSend( _handle, &_send, sizeof( _send ) );
		_send = CTRL_DATA( _send.phase );
		_phase_change = false;
	}
}

bool NetworkController::recv( ) {
	if ( GetNetWorkDataLength( _handle ) == 0 ) {
		return false;
	}

	if ( _handle <= 0 ) {
		return false;
	}

	NetWorkRecv( _handle, &_recv, sizeof( _recv ) ) ;

	if ( _recv.foot == FOOT_ITEM ) {
		int hoger= 20;
	}
	
	if ( _recv.in_out_scene == true ) {
		int hoger= 20;
	}

	return true;
}

bool NetworkController::mapRecv( ) {
	if ( GetNetWorkDataLength( _map_handle ) == 0 ) {
		return false;
	}

	if ( _map_handle <= 0 ) {
		return false;
	}

	NetWorkRecv( _map_handle, &_map_recv, sizeof( _map_recv ) ) ;

	return true;
}

void NetworkController::setItemType( ITEM_TYPE item_type ) {
	_recv.item_type = item_type;
}

void NetworkController::resetRecv( ) {
	_recv = APP_DATA( _recv.status, _recv.foot, _recv.stamina, _recv.level, _recv.floor_level );
}

void NetworkController::resetMapRecv( ) {
	_map_recv = MAP_CHIP_DATA( );
}

ITEM_TYPE NetworkController::getItemType( ) {
	return _recv.item_type;
}

bool NetworkController::isInOutScene( ) {
	return _recv.in_out_scene;
}

Network::MAP_CHIP_DATA NetworkController::getMapData( ) {
	return _map_recv;
}

int NetworkController::getEnemyNum( ) {
	return _recv.enemy_num;
}

int NetworkController::getMaxEnemyNum( ) {
	return _recv.max_enemy_num;
}

SKILL_TYPE NetworkController::getSkillType( ) {
	return _recv.skill_type;
}

bool NetworkController::isRecv( ) {
	if ( GetNetWorkDataLength( _handle ) == 0 ) {
		return false;
	};
	return true;
}

bool NetworkController::isEnemyTurnEnd( ) {
	return _recv.enemy_turn_end;
}

int NetworkController::getAlchemyPoint( ) {
	return _recv.alchemy_point;
}

bool NetworkController::isDead( ) {
	return _recv.dead;
}
bool NetworkController::isFinish( ) {
	return _recv.game_finish;
}

Network::FOOT_THING NetworkController::getFoot( ) {
	return _recv.foot;
}

STATUS_DATA NetworkController::getStatusData( ) {
	return _recv.status;
}

int NetworkController::getStamina( ) {
	return _recv.stamina;
}

int NetworkController::getLevel( ) {
	return _recv.level;
}

int NetworkController::getFloorLevel( ) {
	return _recv.floor_level;
}

void NetworkController::resetSkillData( ) {
	_recv.skill_type = APP_DATA( ).skill_type;
}
void NetworkController::resetAlchemyPoint( ) {
	_recv.alchemy_point = APP_DATA( ).alchemy_point;
}

void NetworkController::resetDead( ) {
	_recv.dead = APP_DATA( ).dead;
}

void NetworkController::resetRide( ) {
	_recv.ride = APP_DATA( ).ride;
}

bool NetworkController::isFootRecv( ) {
	if ( GetNetWorkDataLength( _handle ) == 0 ) {
		return false;
	};
	APP_DATA recv;
	//NetWorkRecvToPeek( _handle, &recv, sizeof( recv ) ) ;

	if ( recv.foot != FOOT_THING::FOOT_NONE ) {
		return true;
	}
	return false;
}

bool NetworkController::isRide( ) {
	return _recv.ride;
}

bool NetworkController::isTileFinish( ) {
	return _recv.send_tile_finish;
}

void NetworkController::setFootThing( FOOT_THING foot_thing ) {
	_recv.foot = foot_thing;
}