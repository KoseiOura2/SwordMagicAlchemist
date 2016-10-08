#pragma once
#include "smart_ptr.h"
#include "Network.h"

PTR( Network );
PTR( NetworkController );

class NetworkController : public Network {
public:
	NetworkController( );
	 ~NetworkController( );
	bool connectNetwork( );
	void closeNetwork( );
	void send( );
	bool recv( );
	bool mapRecv( );
	void setSendDir( CTRL_DIR dir, CTRL_PHASE phase );
	void setSendPhase( CTRL_PHASE phase );
	void setSendItem( ITEM_ACTION action, ITEM_TYPE type );
	void setSendItemAction( ON_ITEM on_item );
	void setSendAttack( bool flag );
	void setSendUseFootItem( bool flag );
	void setSendNextFloor( NEXT_FLOOR next_floor );
	void setSendRevive( REVIVE revive );
	void setSendGoGame( bool flag );
	void setSendMagicAttack( bool flag );
	void setSendSkillId( SKILL_ID id );
	void setSendGoTitle( bool flag );
	void setSendFinishApp( bool flag );
	void setSendReturnTitle( bool flag );
	void resetRecv( );
	void resetMapRecv( );
	void resetSkillData( );
	void resetAlchemyPoint( );
	void resetDead( );
	void resetRide( );
	bool isInOutScene( );
	ITEM_TYPE getItemType( );
	MAP_CHIP_DATA getMapData( );
	STATUS_DATA getStatusData( );
	int getStamina( );
	int getLevel( );
	int getFloorLevel( );
	void setItemType( ITEM_TYPE item_type );
	int getEnemyNum( );
	int getMaxEnemyNum( );
	bool isFootRecv( );	// FOOTDATA‚ª‘—‚ç‚ê‚Ä‚«‚Ä‚¢‚é‚©‚ðŠm”F
	bool isRecv( );
	bool isEnemyTurnEnd( );
	bool isRide( );
	SKILL_TYPE getSkillType( );
	int getAlchemyPoint( );
	bool isDead( );
	bool isFinish( );
	bool isTileFinish( );
	FOOT_THING getFoot( );
	void setFootThing( FOOT_THING foot_thing );
private:
	bool connect( );
	bool mapConnect( );
	void connectReceive( );
	void connectMapReceive( );
private:
	CTRL_DATA _send;
	APP_DATA _recv;
	MAP_CHIP_DATA _map_recv;
	bool _phase_change;
	FOOT_THING _foot_thing;
};

