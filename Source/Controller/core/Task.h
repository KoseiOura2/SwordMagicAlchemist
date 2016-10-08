#pragma once

#include "smart_ptr.h"

PTR( Task );

class Task {
public:
	Task( );
	virtual ~Task( );
	virtual void update( ) = 0;
	virtual void initialize( ) = 0;
	virtual void finalize( ) = 0;
};

