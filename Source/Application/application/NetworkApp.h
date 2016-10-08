#pragma once
#include "smart_ptr.h"
#include "Network.h"

PTR( NetworkApp );

class NetworkApp : public Network {
public:
	NetworkApp( );
	~NetworkApp( );
	void update( );
	bool connect( );
	bool mapConnect( );
	void connectController( );
	CTRL_DIR getInputDir( );
	CTRL_PHASE getCtrlPhase( );
	ITEM_ACTION getItemAction( );
	ITEM_TYPE getItemType( );
	ON_ITEM isOnItem( );
	SKILL_ID getSkillID( );
	NEXT_FLOOR isNextFloor( );
	bool isMagicAttack( );
	bool isAttack( );
	bool isFootItem( );
	REVIVE isRevive( );
	bool isGoGame( );
	bool isGoTitle( );
	bool isFinishApp( );
	bool isReturnTitle( );

	void recv( );
	void send( );
	void tileSend( );
	void setSendOnItem( ITEM_TYPE item, bool ride );
	void setSendFoot( FOOT_THING foot, bool ride );
	void setSendRide( bool ride );
	void setSendNextFloor( bool next_floor );
	void setSendChipData( MAP_CHIP_TYPE chip, Vector2 pos, int room_num, bool zero );
	void setSendSkillData( SKILL_ID id );
	void setSendEnemyNum( int enemy_num );
	void setSendMaxEnemyNum( int max_enemy_num );
	void setSendPlayerDead( bool dead );
	void setSendAlchemyPoint( int alchemy_point );
	void setSendTileFinish( int send_tile_finish );
	void sendStatus( STATUS_DATA status, int stamina, int level );
	void sendFloorLevel( int floor_level );
	void setSendGameFinish( bool game_finish );
private:
	bool _connect_flag;
	APP_DATA _send;
	CTRL_DATA _recv_data;
	MAP_CHIP_DATA _map_data;
};