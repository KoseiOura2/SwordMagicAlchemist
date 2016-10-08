#include "NetworkApp.h"
#include <string>
#include <vector>
#include "Framework.h"

NetworkApp::NetworkApp( ) {
	Network::Network( );
	PreparationListenNetWork( PORT_NUM );	// 接続待ち状態にする
	_connect_flag = false;
	_handle       = -1;
	_map_handle   = -1;
}

NetworkApp::~NetworkApp( ) {

}

void NetworkApp::update( ) {
	if ( GetNetWorkDataLength( _handle ) <= 0 ) {
		_recv_data.dir          = NONE;
		_recv_data.item_action  = QUIT;
		_recv_data.skill_id     = SKILL_ID::SKILL_NONE;
		_recv_data.next_floor   = NONE_CHOICE;
		_recv_data.on_item      = ON_ITEM::NONE_ITEM;
		_recv_data.revive       = NO_DEAD;
		_recv_data.magic_attack = false;
		_recv_data.attack       = false;
		_recv_data.go_game      = false;
		_recv_data.go_title     = false;
	}
	
	// 接続が絶たれたら接続状態を終了
	FrameworkPtr fw  = Framework::getInstance( );
	int handle = GetLostNetWork( );
	if ( handle != - 1 ) {
		CloseNetWork( _handle );
		CloseNetWork( _map_handle );
		fw->end( );
	}

}

void NetworkApp::connectController( ) {

}

bool NetworkApp::connect( ) {
	// 接続確認
	if ( _connect_flag == false ) {
		drawIpAddress( );
		_handle = GetNewAcceptNetWork( );
		if ( _handle != -1 ) {	// 受信確認
			 StopListenNetWork( );	// 接続待ち状態を終了する
		}

		if ( _handle != -1 ) {
			GetNetWorkIP( _handle, &_partner_ip );	// Controller側のIP取得
			_success = true;

			if ( NetWorkSend( _handle, &_success, sizeof( _success ) ) == -1 ) {
				return false;
			} else {
				_connect_flag = true;
				PreparationListenNetWork( MAP_PORT_NUM );
				return true;
			}
		}
		return false;
	} else {
		return true;
	}
}

bool NetworkApp::mapConnect( ) {
	drawIpAddress( );
	
	_map_handle = GetNewAcceptNetWork( );
	if ( _map_handle != -1 ) {	// 受信確認
		 StopListenNetWork( );	// 接続待ち状態を終了する
	}

	if ( _map_handle != -1 ) {
		_success = true;

		if ( NetWorkSend( _map_handle, &_success, sizeof( _success ) ) == -1 ) {
			return false;
		} else {
			return true;
		}
	}
	return false;
}

void NetworkApp::recv( ) {
	if ( _send.foot == FOOT_NONE ) {
		int hoge = 0;
	}
	int dataLength = GetNetWorkDataLength( _handle );
	if ( GetNetWorkDataLength( _handle ) > 0 ) {
		if ( NetWorkRecv( _handle, &_recv_data, sizeof( _recv_data ) ) == -1 ) {
			int a =10;
		}
	}
}

void NetworkApp::setSendOnItem( ITEM_TYPE item, bool ride ) {
	_send.item_type = item;
	_send.foot      = FOOT_ITEM;
	_send.ride      = ride;
	NetWorkSend( _handle, &_send, sizeof( _send ) );
	// 初期化
	_send = APP_DATA( _send.status, _send.foot, _send.stamina, _send.level, _send.floor_level );
}

void NetworkApp::setSendFoot( FOOT_THING foot, bool ride ) {
	_send.foot = foot;
	_send.ride = ride;
	NetWorkSend( _handle, &_send, sizeof( _send ) );
	// 初期化
	_send = APP_DATA( _send.status, _send.foot, _send.stamina, _send.level, _send.floor_level );
}

void NetworkApp::setSendRide( bool ride ) {
	_send.ride = ride;
}

void NetworkApp::setSendNextFloor( bool in_out_scene ) {
	_send.in_out_scene = in_out_scene;
}

void NetworkApp::setSendChipData( MAP_CHIP_TYPE chip, Vector2 pos, int room_num, bool zero ) {
	_map_data.type = chip;
	_map_data.pos = pos;
	_map_data.room_num = room_num;
	_map_data.zero     = zero;
	//_send.enemy_turn_end = turn_end;
	NetWorkSend( _map_handle, &_map_data, sizeof( _map_data ) );
	//_send.enemy_turn_end = false;
}

void NetworkApp::setSendSkillData( SKILL_ID id ) {
	_send.skill_type.id = id;
}

void NetworkApp::setSendEnemyNum( int enemy_num ) {
	_send.enemy_num = enemy_num;
}

void NetworkApp::setSendMaxEnemyNum( int max_enemy_num ) {
	_send.max_enemy_num = max_enemy_num;
}

void NetworkApp::setSendPlayerDead( bool dead ) {
	_send.dead = dead;
}

void NetworkApp::setSendAlchemyPoint( int alchemy_point ) {
	_send.alchemy_point = alchemy_point;
}

void NetworkApp::sendStatus( STATUS_DATA status, int stamina, int level ) {
	_send.status  = status;
	_send.stamina = stamina;
	_send.level   = level;
	NetWorkSend( _handle, &_send, sizeof( _send ) );
	// 初期化
	_send = APP_DATA( _send.status, _send.foot, _send.stamina, _send.level, _send.floor_level );
}

void NetworkApp::sendFloorLevel( int floor_level ) {
	_send.floor_level = floor_level;
	NetWorkSend( _handle, &_send, sizeof( _send ) );
	// 初期化
	_send = APP_DATA( _send.status, _send.foot, _send.stamina, _send.level, _send.floor_level );
}

void NetworkApp::setSendGameFinish( bool game_finish ) {
	_send.game_finish = game_finish;
}

void NetworkApp::setSendTileFinish( int send_tile_finish ) {
	_send.send_tile_finish = send_tile_finish;
}

void NetworkApp::send( ) {
	// 何かに乗っかったかどうか
	// ネクストフロアシーンに入ったかどうか
	// 死んだかどうか
	// 錬金ポイントが追加されたかどうか
	if ( _send.ride == true ||
		 _send.in_out_scene == true ||
		 _send.dead == true ||
		 _send.alchemy_point != 0 ||
		 _send.game_finish == true ) {
		NetWorkSend( _handle, &_send, sizeof( _send ) );
		// 初期化
		_send = APP_DATA( _send.status, _send.foot, _send.stamina, _send.level, _send.floor_level );
	}
}

Network::CTRL_DIR NetworkApp::getInputDir( ) {
	return _recv_data.dir;
}

Network::CTRL_PHASE NetworkApp::getCtrlPhase( ) {
	return _recv_data.phase;
}

Network::ITEM_ACTION NetworkApp::getItemAction( ) {
	return _recv_data.item_action;
}

ITEM_TYPE NetworkApp::getItemType( ) {
	return _recv_data.item_type;
}

Network::ON_ITEM NetworkApp::isOnItem( ) {
	return _recv_data.on_item;
}

SKILL_ID NetworkApp::getSkillID( ) {
	return _recv_data.skill_id;
}

Network::NEXT_FLOOR NetworkApp::isNextFloor( ) {
	return _recv_data.next_floor;
}

bool NetworkApp::isMagicAttack( ) {
	return _recv_data.magic_attack;
}


bool NetworkApp::isAttack( ) {
	return _recv_data.attack;
}

bool NetworkApp::isFootItem( ) {
	return _recv_data.foot_item;
}

Network::REVIVE NetworkApp::isRevive( ) {
	return _recv_data.revive;
}

bool NetworkApp::isGoGame( ) {
	return _recv_data.go_game;
}

bool NetworkApp::isGoTitle( ) {
	return _recv_data.go_title;
}

bool NetworkApp::isFinishApp( ) {
	return _recv_data.finish_app;
}

bool NetworkApp::isReturnTitle( ) {
	return _recv_data.return_title;
}
