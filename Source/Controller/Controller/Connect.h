#pragma once
#include "DxLib.h"
#include "smart_ptr.h"

PTR( Connect );

class Connect {
public:
	Connect( );
	~Connect( );
	void update( );
	void init( );
private:
	IPDATA _ip;
};

