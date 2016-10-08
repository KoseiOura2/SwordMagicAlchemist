#pragma once

#include <string>
#include <map>
#include "smart_ptr.h"

PTR( Framework );
PTR( Task );

const int SCREEN_HEIGHT = 1080;
const int SCREEN_WIDTH = 1920;

class Framework {
public:
	static FrameworkPtr getInstance( );
	static void initialize( );
	static void finalize( );
	virtual ~Framework( );
	void run( );
	void addTask( TaskPtr task );
	TaskPtr getTask( std::string type );
	void end( );
private:
	Framework( );
	void initializeAllTask( );
	void loopAllTask( );
	void finalizeAllTask( );
private:
	static FrameworkPtr _instance;
	std::map< std::string, TaskPtr > _task_map;
	bool _end;
};