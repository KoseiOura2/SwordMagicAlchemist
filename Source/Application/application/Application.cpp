#include "Application.h"
#include "Framework.h"
#include "Viewer.h"
#include "Floor.h"
#include "Player.h"
#include "Item.h"
#include "EnemyManager.h"
#include "Camera.h"
#include "NetworkApp.h"
#include "Turn.h"
#include "MessageLog.h"
#include "Title.h"
#include "NextFloor.h"
#include "UIApp.h"
#include "Effect.h"
#include "Keyboard.h"
#include "Sound.h"

const int LAST_FLOOR = 4;
const int INCREASE_FADE_OUT_PAL = 5;

Application::Application( ) {
	FrameworkPtr fw = Framework::getInstance( );
	SoundPtr sound = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	_turn         = TurnPtr( new Turn );
	_network      = NetworkAppPtr( new NetworkApp( ) );
	_floor        = FloorPtr( new Floor( _network ) );
	_messageLog   = MessageLogPtr( new MessageLog( ) );
	_effect       = EffectPtr( new Effect( ) );
	_item         = ItemPtr( new Item( _floor, _network, _messageLog, _effect ) );
	_ui_app       = UIAppPtr( new UIApp( ) );
	_player       = PlayerPtr( new Player( _floor, _turn, _messageLog,_network, _item, _effect, _ui_app ) );
	_enemyManager = EnemyManagerPtr( new EnemyManager( _floor, _turn, _player, _messageLog, _item, _network, _effect ) );
	_camera       = CameraPtr( new Camera( _player ) );
	_title        = TitlePtr( new Title( ) );
	_next_floor   = NextFloorPtr( new NextFloor( ) );

	// ������
	_scene = SCENE_TITLE;
	//_scene = SCENE_CONNECT;
	_next_floor_scene_init = false;
	_tile_x_count          = 0;
	_send_tile_finish      = false;
	_fade_out_pal          = 0;

	sound->loadGameSound( );
	_title->loadGraph( );
}

Application::~Application( ) {

}

void Application::initialize( ) {

}

void Application::finalize( ) {

}

void Application::update( ) {
	FrameworkPtr fw = Framework::getInstance( );
	SoundPtr sound  = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );
	
	// �V�[�����Ƃɏ�����؂�ւ���
	switch ( _scene ) {
		case SCENE_CONNECT:
			updateConnect( );
			break;
		case SCENE_TITLE:
			updateTitle( );
			break;
		case SCENE_NEXT_FLOOR:
			updateNextFloor( );
			break;
		case SCENE_GAME:
			updateGame( );
			break;
		case SCENE_BOSS:
			updateBoss( );
			break;
		case SCENE_GAME_CLEAR:
			updateGameClear( );
			break;
		case SCENE_GAME_OVER:
			updateGameOver( );
			break;
	}

	// �R���g���[���[���I�������玩���ŏI������
	if ( _network->isFinishApp( ) == true ) {
		fw->end( );
	}

}

void Application::updateConnect( ) {
	FrameworkPtr fw = Framework::getInstance( );
	SoundPtr sound  = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );
	
	// �R���g���[���[�Ƃ̐ڑ�������������^�C�g���V�[���ց{������
	if ( _network->connect( ) == true ) {
		if ( _network->mapConnect( ) == true ) {
			_scene = SCENE_TITLE;
			_floor->init( );
			_next_floor->init( );
			_floor->init( );
			_player->init( );
			_title->init( );
			_title->loadGraph( );
			sound->loadTitleSound( );
			sound->playSound( Sound::TITLE_BGM, true );
		}
	}
}

void Application::updateTitle( ) {
	FrameworkPtr fw = Framework::getInstance( );
	SoundPtr sound  = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );
	KeyboardPtr keyboard = std::dynamic_pointer_cast< Keyboard >( fw->getTask( typeid( Keyboard ).name( ) ) );

	_title->update( );
	_network->recv( );
	// �Q�[���V�[���ւ̈ڍs������ꂽ��Q�[���V�[���֐؂�ւ��^�C�g����������
	if ( _network->isGoGame( ) == true || keyboard->isPushKey( "SPACE" ) == true ) {
		_scene = SCENE_NEXT_FLOOR;
		_title->init( );
		_fade_out_pal = 0;
		sound->stopSound( Sound::TITLE_BGM );
		sound->playSound( Sound::CAVE_BGM, true );
		sound->deleteTitleSound( );
	}
}

void Application::updateNextFloor( ) {
	FrameworkPtr fw = Framework::getInstance( );
	SoundPtr sound  = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );
	KeyboardPtr keyboard = std::dynamic_pointer_cast< Keyboard >( fw->getTask( typeid( Keyboard ).name( ) ) );
	
	// �K�w���J��グ��
	if ( _next_floor_scene_init == false ) {
		_next_floor->countFloorLevel( true );
	}

	_next_floor->update( );
	// �K�w�ړ����ɏ�����
	if ( _next_floor_scene_init == false ) {
		// ���݂̊K�w��ݒ�
		_ui_app->setFloorLevel( _next_floor->getFloorLevel( ) );
		_enemyManager->setFloorLevel( _next_floor->getFloorLevel( ) );
		_item->setFloorLevel( _next_floor->getFloorLevel( ) );
		// ������
		_enemyManager->deleteAllEnemy( );
		_item->deleteAllItem( );
		_floor->setFloorLelel( _next_floor->getFloorLevel( ) );
		// �{�X�K�w���ǂ����ŏ�����
		if ( _next_floor->getFloorLevel( ) > LAST_FLOOR ) {
			_floor->bossReset( );
			_player->bossReset( );
			_enemyManager->bossInit( );
		} else {
			_floor->reset( );
			_item->init( );
			_player->reset( );
			_enemyManager->init( );
		}
		_messageLog->init( );
		_effect->init( );
		_ui_app->init( );
		_next_floor_scene_init = true;
		_network->sendFloorLevel( _next_floor->getFloorLevel( ) );
		_network->sendStatus( _player->getStatus( ), _player->getStamina( ), _player->getLevel( ) );
		if ( _next_floor->getFloorLevel( ) > LAST_FLOOR ) {
			sound->stopSound( Sound::CAVE_BGM );
			sound->playSound( Sound::BOSS_BGM, true );
		}
	}
	// �t���A�̏���1�t���[����1��Controller���ɑ���
	if ( _send_tile_finish == false ) {
		for ( int i = 0; i < FLOOR_MAX_HEIGHT; i++ ) {
			Vector2 pos;
			pos.x = _tile_x_count;
			pos.y = i;
			if ( _floor->getTile( pos.x, pos.y ).type != Floor::TYPE::WALL ) {
				_network->setSendChipData( NetworkApp::MAP_CHIP_TYPE::FLOOR, pos,
										   _floor->getTile( ( int )pos.x, ( int )pos.y ).room, false );
			}
		}
		_tile_x_count++;
	}
	// �^�C����X���W���}�b�N�X�܂ł�������I��
	if ( _tile_x_count >= FLOOR_MAX_WIDTH ) {
		_tile_x_count = 0;
		_send_tile_finish = true;
		_network->setSendTileFinish( true );
	}
	// �R���g���[���[�Ƀ}�b�v�`�b�v�𑗂�I�������Q�[���V�[����
	if ( _send_tile_finish == true ||
		 ( keyboard->isPushKey( "SPACE" ) == true && _send_tile_finish == true ) ) {
		_next_floor_scene_init = false;
		_network->sendStatus( _player->getStatus( ), _player->getStamina( ), _player->getLevel( ) );
		if ( _next_floor->getFloorLevel( ) > LAST_FLOOR ) {
   			_scene = SCENE_BOSS;
		} else {
			_scene = SCENE_GAME;
		}
		_network->setSendNextFloor( true );
		_network->send( );
		_send_tile_finish = false;
	}
}

void Application::updateGame( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	SoundPtr sound   = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );

	viewer->setNormalBlend( );
	
	_network->recv( );
	// �^�[�����肩��
	if ( _player->isTurnEnd( ) == true ) {
		int alchemy_point = 1;
		_player->alchemyPointManage( alchemy_point );
		_turn->changeTurn( );
	}
	if ( _enemyManager->isTurnEnd( ) == true ) {
		_turn->changeTurn( );
	}

	// �X�V����
	_floor->update( );
	_item->update( );
	_enemyManager->update( );
	_messageLog->update( );
	_player->update( );
	_camera->update( ); 
	_ui_app->update( );
	// �G�t�F�N�g�͍Ō�ɂ��Ȃ��Ə�����
	_effect->update( );
	// �K�w�ړ������Ă悢�Ǝ���Ƃ�����K�w�ړ����J�n�i �f�o�b�O�F�K�i�̂���^�C���ŃX�y�[�X������ �j
	if ( ( _network->isNextFloor( ) == NetworkApp::NEXT_FLOOR::GO_NEXT && _player->isDead( ) == false ) ||
		 ( _floor->getTile( _player->getPos( ).x, _player->getPos( ).y ).stair_exist == true &&
		   _player->pushSpace( ) == true && _player->isDead( ) == false ) ||
		   _player->isRideReturnTrap( ) == true ) {
		int alchemy_point = 10;
		_player->alchemyPointManage( alchemy_point );
		_scene = SCENE_NEXT_FLOOR;
		_network->setSendNextFloor( true );
		sound->playSound( Sound::NEXT_FLOOR, false );
	} else if ( _network->isNextFloor( ) == NetworkApp::NEXT_FLOOR::NOT_NEXT ) {
		_ui_app->setStairWindow( false );
	}
	
	
	// GameOver����
	if ( _player->isRevive( ) == true ) {
		_fade_out_pal += INCREASE_FADE_OUT_PAL;
		if ( _fade_out_pal > 255 ) {
			_fade_out_pal = 255;
			_scene = SCENE_GAME_OVER;
			_network->setSendGameFinish( true );
			sound->stopSound( Sound::CAVE_BGM );
			sound->playSound( Sound::GAME_OVER_BGM, true );
		}
		viewer->setAlpha( _fade_out_pal );
		viewer->drawBox( SCREEN_WIDTH, SCREEN_HEIGHT, Vector2( 0, 0 ), 0, 0, 0, true );
	}
	// �^�C�g���ɖ߂邪�����Ă����Ƃ�
	if ( _network->isReturnTitle( ) == true ) {
		_fade_out_pal += INCREASE_FADE_OUT_PAL;
		if ( _fade_out_pal > 255 ) {
			_next_floor->init( );
			_floor->init( );
			_player->init( );
			_fade_out_pal = 255;
			_scene = SCENE_TITLE;
			_network->setSendGameFinish( true );
			sound->loadTitleSound( );
			sound->stopSound( Sound::CAVE_BGM );
			sound->playSound( Sound::TITLE_BGM, true );
		}
		viewer->setAlpha( _fade_out_pal );
		viewer->drawBox( SCREEN_WIDTH, SCREEN_HEIGHT, Vector2( 0, 0 ), 0, 0, 0, true );
	}

	_network->send( );
	_network->update( );
}

void Application::updateBoss( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	SoundPtr sound   = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );

	viewer->setNormalBlend( );

	_network->recv( );
	// �^�[�����肩��
	if ( _player->isTurnEnd( ) == true ) {
		int alchemy_point = 1;
		_player->alchemyPointManage( alchemy_point );
		_turn->changeTurn( );
	}
	if ( _enemyManager->isTurnEnd( ) == true ) {
		_turn->changeTurn( );
	}
	
	// �X�V����
	_floor->update( );
	_item->update( );
	_enemyManager->bossUpdate( );
	_messageLog->update( );
	_player->update( );
	_camera->update( ); 
	_ui_app->update( );
	// �G�t�F�N�g�͍Ō�ɂ��Ȃ��Ə�����
	_effect->update( );
	
	// GameClear����
	if ( _enemyManager->isKnockDownBoss( ) ) {
		_fade_out_pal += INCREASE_FADE_OUT_PAL;
		if ( _fade_out_pal > 255 ) {
			_fade_out_pal = 255;
			_scene = SCENE_GAME_CLEAR;
			_network->setSendGameFinish( true );
			sound->stopSound( Sound::BOSS_BGM );
			sound->playSound( Sound::CLEAR_BGM, true );
		}
		viewer->setAlpha( _fade_out_pal );
		viewer->drawBox( SCREEN_WIDTH, SCREEN_HEIGHT, Vector2( 0, 0 ), 0, 0, 0, true );
	}
	
	// GameOver����
	if ( _player->isRevive( ) == true ) {
		_fade_out_pal += INCREASE_FADE_OUT_PAL;
		if ( _fade_out_pal > 255 ) {
			_fade_out_pal = 255;
			_scene = SCENE_GAME_OVER;
			_network->setSendGameFinish( true );
			sound->stopSound( Sound::BOSS_BGM );
			sound->playSound( Sound::GAME_OVER_BGM, true );
		}
		viewer->setAlpha( _fade_out_pal );
		viewer->drawBox( SCREEN_WIDTH, SCREEN_HEIGHT, Vector2( 0, 0 ), 0, 0, 0, true );
	}

	
	// �^�C�g���ɖ߂邪�����Ă����Ƃ�
	if ( _network->isReturnTitle( ) == true ) {
		_fade_out_pal += INCREASE_FADE_OUT_PAL;
		if ( _fade_out_pal > 255 ) {
			_next_floor->init( );
			_floor->init( );
			_player->init( );
			_fade_out_pal = 255;
			_scene = SCENE_TITLE;
			_network->setSendGameFinish( true );
			sound->loadTitleSound( );
			sound->stopSound( Sound::BOSS_BGM );
			sound->playSound( Sound::TITLE_BGM, true );
		}
		viewer->setAlpha( _fade_out_pal );
		viewer->drawBox( SCREEN_WIDTH, SCREEN_HEIGHT, Vector2( 0, 0 ), 0, 0, 0, true );
	}
	_network->send( );
	_network->update( );
}

void Application::updateGameClear( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	SoundPtr sound = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );

	_network->recv( );

	viewer->setNormalBlend( );
	_title->clearDraw( );
	if ( _player->pushSpace( ) == true || _network->isGoTitle( ) == true || _network->isReturnTitle( ) == true ) {
		_next_floor->init( );
		_floor->init( );
		_player->init( );
		_scene = SCENE_TITLE;
		sound->loadTitleSound( );
		sound->stopSound( Sound::CLEAR_BGM );
		sound->playSound( Sound::TITLE_BGM, true );
	}
}

void Application::updateGameOver( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	SoundPtr sound = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );

	_network->recv( );

	viewer->setNormalBlend( );
	_title->gameOverDraw( );
	if ( _player->pushSpace( ) == true || _network->isGoTitle( ) == true || _network->isReturnTitle( ) == true ) {
		_next_floor->init( );
		_floor->init( );
		_player->init( );
		_scene = SCENE_TITLE;
		sound->loadTitleSound( );
		sound->stopSound( Sound::GAME_OVER_BGM );
		sound->playSound( Sound::TITLE_BGM, true );
	}
}