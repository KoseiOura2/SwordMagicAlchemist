#include "Framework.h"
#include "Task.h"
#include "Dxlib.h"
#include <typeinfo>

// 唯一のグローバル変数（シングルトン）
FrameworkPtr Framework::_instance;

void Framework::initialize( ) {
	if ( !_instance ) {
		_instance = FrameworkPtr( new Framework );
	}
}

void Framework::finalize( ) {
	if ( _instance ) {
		_instance.reset( );
	}
}

FrameworkPtr Framework::getInstance( ) {
	return _instance;
}

Framework::Framework( ) {
	_end = false;
}

Framework::~Framework( ) {
}

void Framework::run( ) {
	initializeAllTask( );
	loopAllTask( );
	finalizeAllTask( );
}

void Framework::initializeAllTask( ) {
	std::map< std::string, TaskPtr >::iterator it = _task_map.begin( );
	while ( it != _task_map.end( ) ) {
		TaskPtr task = it->second;
		task->initialize( );
		it++;
	}
}

void Framework::finalizeAllTask( ) {
	std::map< std::string, TaskPtr >::iterator it = _task_map.begin( );
	while ( it != _task_map.end( ) ) {
		TaskPtr task = it->second;
		task->finalize( );
		it++;
	}
}

void Framework::loopAllTask( ) {
	while ( true ) {
		if ( ProcessMessage( ) == -1 ) {
			break;
		}
		if ( CheckHitKey( KEY_INPUT_ESCAPE ) ) {
			break;
		}
		//タスクを回す
		std::map< std::string, TaskPtr >::iterator it = _task_map.begin( );
		while ( it != _task_map.end( ) ) {
			TaskPtr task = it->second;
			task->update( );
			it++;
		}
		if ( _end ) {
			break;
		}
	}
}

void Framework::addTask( TaskPtr task ) {
	if ( task ) {
		_task_map[ typeid( *task ).name( ) ] = task;
	}
}

TaskPtr Framework::getTask( std::string type ) {
    if ( _task_map.find( type ) == _task_map.end( ) ) {
        return TaskPtr( );
    }
	return _task_map[ type ];
}

void Framework::end( ) {
	_end = true;
}