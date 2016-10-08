#pragma once

#include "smart_ptr.h"
#include "Task.h"

PTR ( Sound );

class Sound : public Task {
public:
	enum SOUND_TYPE {
		DECISION,	// ����
		RETURN,		// �߂�
		POT_OPEN,	// �q���J������
		POT_CLOSE,	// �q�������
		ALCHEMY_SUCCESS,	// �B��������
	};
public:
	Sound( );
	~Sound( );
	void initialize( );
	virtual void finalize( );
	void update( );
	void playSound( SOUND_TYPE type );
private:
	int _decision;
	int _return;
	int _pot_open;
	int _pot_close;
	int _alchemy_success;
};

