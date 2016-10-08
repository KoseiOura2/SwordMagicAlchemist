#pragma once
#include "Task.h"
#include "smart_ptr.h"

PTR ( Application );
PTR ( Title );
PTR ( NextFloor );
PTR ( Player );
PTR ( Floor );
PTR ( Camera );
PTR ( NetworkApp );
PTR ( EnemyManager );
PTR ( Item );
PTR ( Turn );
PTR ( MessageLog );
PTR ( UIApp );
PTR ( Effect );

class Application : public Task {
private:								 
	enum SCENE{							  
		SCENE_CONNECT,
		SCENE_TITLE,				  
		SCENE_GAME,						  
		SCENE_NEXT_FLOOR,
		SCENE_BOSS,
		SCENE_GAME_CLEAR,
		SCENE_GAME_OVER
	};		
public:
	Application( );                      
	~Application( );					 
public:									 
	void initialize( );					 
	void finalize( );					 
	void update( );						 
private:								 
	void updateConnect( );				 // Controller���Ƃ̐ڑ��V�[���̍X�V����
	void updateTitle( );			     // �^�C�g���V�[���̍X�V����
	void updateGame( );					 // MainGame�V�[���̍X�V����
	void updateNextFloor( );			 // �K�w�ړ��V�[���̍X�V����	
	void updatePreFloor( );			 // �K�w�ړ��V�[���̍X�V����	
	void updateBoss( );		        	 // �{�X�V�[���̍X�V����		
	void updateGameClear( );		     // �N���A�V�[���̍X�V����		
	void updateGameOver( );		         // �Q�[���I�[�o�[�V�[���̍X�V����							  
private:								  
	SCENE _scene;						  
	FloorPtr _floor;
	TitlePtr _title;
	TurnPtr _turn;						  
	PlayerPtr _player;					 
	CameraPtr _camera;					 
	EnemyManagerPtr _enemyManager;		 
	ItemPtr _item;						 
	NetworkAppPtr _network;				 
	MessageLogPtr _messageLog;			 
	NextFloorPtr _next_floor;			 
	UIAppPtr _ui_app;			
	EffectPtr _effect;
	bool _next_floor_scene_init;		 // �������t���O
	int _tile_x_count;					 // �R���g���[���[�ɑ���}�b�v�`�b�v�̃J�E���g��
	bool _send_tile_finish;				 // �R���g���[���[�Ƀ}�b�v�`�b�v�𑗂�I��������ǂ���
	int _fade_out_pal;					 // �t�F�[�h�A�E�g�̃J�E���g��
};

