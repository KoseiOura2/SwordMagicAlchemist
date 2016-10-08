#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include <string>
#include <map>
PTR( Keyboard );

class Keyboard : public Task {
public:
	Keyboard( );
	~Keyboard( );
	void initialize( );
	virtual void finalize( );
	void update( );
	bool isPushKey( std::string key );
	bool isHoldKey( std::string key );
private:
	struct KEYS {
		char buffer[ 256 ];
	};
private:
	KEYS _now_keys;
	KEYS _before_keys;
	std::map< std::string, int > _convert;
};

