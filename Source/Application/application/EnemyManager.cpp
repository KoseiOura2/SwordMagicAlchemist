#include "EnemyManager.h"
#include "Framework.h"
#include "Turn.h"
#include "MessageLog.h"
#include "Item.h"
#include "NetworkApp.h"
#include "Effect.h"
#include "Sound.h"

const int CREATE_ENEMY_TURN = 5;

EnemyManager::EnemyManager( FloorPtr floor, TurnPtr turn, PlayerPtr player, MessageLogPtr message, ItemPtr item, NetworkAppPtr network, EffectPtr effect ) {
	_floor   = floor;
	_turn    = turn;
	_player  = player;
	_message = message;
	_item    = item;
	_network = network;
	_effect  = effect;


	for ( int i = 0; i < ENEMY_TYPE::MAX_ENEMY_NUM; i++ ) {
		_enemy_data[ i ] = ENEMY_DATA_TABLE[ i ];
	}

	loadModel( );
}

EnemyManager::~EnemyManager( ) {

}

void EnemyManager::loadModel( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	
	_shadow_handle = viewer->loadGraph( "work/tile/shadow.png" );;

	_anim_handle[ OCTO_POT ].model  = viewer->loadModel( "work/model/enemy/octpot/model_enemy5.mv1" );
	_anim_handle[ OCTO_POT ].stay   = viewer->loadModel( "work/model/enemy/octpot/motion_stay_enemy5.mv1" );
	_anim_handle[ OCTO_POT ].walk   = viewer->loadModel( "work/model/enemy/octpot/motion_walk_enemy5.mv1" );
	_anim_handle[ OCTO_POT ].attack = viewer->loadModel( "work/model/enemy/octpot/motion_attack_enemy5.mv1" );
	_anim_handle[ OCTO_POT ].dead   = viewer->loadModel( "work/model/enemy/octpot/motion_dead_enemy5.mv1" );
	
	_anim_handle[ SPIDER ].model  = viewer->loadModel( "work/model/enemy/spider2.0/scenes/spider.mv1" );
	_anim_handle[ SPIDER ].stay   = viewer->loadModel( "work/model/enemy/spider2.0/scenes/spider_stay.mv1" );
	_anim_handle[ SPIDER ].walk   = viewer->loadModel( "work/model/enemy/spider2.0/scenes/spider_walk.mv1" );
	_anim_handle[ SPIDER ].attack = viewer->loadModel( "work/model/enemy/spider2.0/scenes/spider_attack.mv1" );
	_anim_handle[ SPIDER ].dead   = viewer->loadModel( "work/model/enemy/spider2.0/scenes/spider_dead.mv1" );
	
	_anim_handle[ SWANGLER ].model  = viewer->loadModel( "work/model/enemy/swangler/swangler.mv1" );
	_anim_handle[ SWANGLER ].stay   = viewer->loadModel( "work/model/enemy/swangler/swangler_wait.mv1" );
	_anim_handle[ SWANGLER ].walk   = viewer->loadModel( "work/model/enemy/swangler/swangler_walk.mv1" );
	_anim_handle[ SWANGLER ].attack = viewer->loadModel( "work/model/enemy/swangler/swangler_attack.mv1" );
	_anim_handle[ SWANGLER ].dead   = viewer->loadModel( "work/model/enemy/swangler/swangler_dead.mv1" );
	
	_anim_handle[ GREAT_OCTO_POT ].model  = viewer->loadModel( "work/model/enemy/octpot/model_enemy5_02.mv1" );
	_anim_handle[ GREAT_OCTO_POT ].stay   = _anim_handle[ OCTO_POT ].stay; 
	_anim_handle[ GREAT_OCTO_POT ].walk   = _anim_handle[ OCTO_POT ].walk;  
	_anim_handle[ GREAT_OCTO_POT ].attack = _anim_handle[ OCTO_POT ].attack;
	_anim_handle[ GREAT_OCTO_POT ].dead   = _anim_handle[ OCTO_POT ].dead; 
	
	_anim_handle[ SILVER_OCTO_POT ].model  = viewer->loadModel( "work/model/enemy/octpot/model_enemy5_03.mv1" );
	_anim_handle[ SILVER_OCTO_POT ].stay   = _anim_handle[ OCTO_POT ].stay;  
	_anim_handle[ SILVER_OCTO_POT ].walk   = _anim_handle[ OCTO_POT ].walk;  
	_anim_handle[ SILVER_OCTO_POT ].attack = _anim_handle[ OCTO_POT ].attack;;
	_anim_handle[ SILVER_OCTO_POT ].dead   = _anim_handle[ OCTO_POT ].dead;  
	
	_anim_handle[ MINOTAUR ].model  = viewer->loadModel( "work/model/enemy/minotaur/scenes/minotaur.mv1" );
	_anim_handle[ MINOTAUR ].stay   = viewer->loadModel( "work/model/enemy/minotaur/scenes/minotaur_stay.mv1" );
	_anim_handle[ MINOTAUR ].walk   = viewer->loadModel( "work/model/enemy/minotaur/scenes/minotaur_walk.mv1" );
	_anim_handle[ MINOTAUR ].attack = viewer->loadModel( "work/model/enemy/minotaur/scenes/minotaur_attack.mv1" );
	_anim_handle[ MINOTAUR ].dead   = viewer->loadModel( "work/model/enemy/minotaur/scenes/minotaur_dead.mv1" );
	
	_anim_handle[ GOCHIMPANZEE ].model  = viewer->loadModel( "work/model/enemy/gochimpanzee/model_enemy10_Tpose.mv1" );
	_anim_handle[ GOCHIMPANZEE ].stay   = viewer->loadModel( "work/model/enemy/gochimpanzee/model_enemy10_wait.mv1" );
	_anim_handle[ GOCHIMPANZEE ].walk   = viewer->loadModel( "work/model/enemy/gochimpanzee/model_enemy10_walk.mv1" );
	_anim_handle[ GOCHIMPANZEE ].attack = viewer->loadModel( "work/model/enemy/gochimpanzee/model_enemy10_attack.mv1" );
	_anim_handle[ GOCHIMPANZEE ].dead   = viewer->loadModel( "work/model/enemy/gochimpanzee/model_enemy10_death.mv1" );
	
	_anim_handle[ GREAT_SWANGLER ].model  = viewer->loadModel( "work/model/enemy/swangler/swangler_2.mv1" );
	_anim_handle[ GREAT_SWANGLER ].stay   = _anim_handle[ SWANGLER ].stay;  
	_anim_handle[ GREAT_SWANGLER ].walk   = _anim_handle[ SWANGLER ].walk;  
	_anim_handle[ GREAT_SWANGLER ].attack = _anim_handle[ SWANGLER ].attack;
	_anim_handle[ GREAT_SWANGLER ].dead   = _anim_handle[ SWANGLER ].dead;  
	
	_anim_handle[ GOLD_OCTO_POT ].model  = viewer->loadModel( "work/model/enemy/octpot/model_enemy5_04.mv1" );
	_anim_handle[ GOLD_OCTO_POT ].stay   = _anim_handle[ OCTO_POT ].stay;  
	_anim_handle[ GOLD_OCTO_POT ].walk   = _anim_handle[ OCTO_POT ].walk;  
	_anim_handle[ GOLD_OCTO_POT ].attack = _anim_handle[ OCTO_POT ].attack;
	_anim_handle[ GOLD_OCTO_POT ].dead   = _anim_handle[ OCTO_POT ].dead;  
	
	_anim_handle[ GREAT_SPIDER ].model  = viewer->loadModel( "work/model/enemy/spider2.0/scenes/great_spider.mv1" );
	_anim_handle[ GREAT_SPIDER ].stay   = _anim_handle[ SPIDER ].stay;  
	_anim_handle[ GREAT_SPIDER ].walk   = _anim_handle[ SPIDER ].walk;  
	_anim_handle[ GREAT_SPIDER ].attack = _anim_handle[ SPIDER ].attack;
	_anim_handle[ GREAT_SPIDER ].dead   = _anim_handle[ SPIDER ].dead;  
	
	_anim_handle[ GREAT_MINOTAUR ].model  = viewer->loadModel( "work/model/enemy/minotaur/scenes/great_minotaur.mv1" );
	_anim_handle[ GREAT_MINOTAUR ].stay   = _anim_handle[ MINOTAUR ].stay;  
	_anim_handle[ GREAT_MINOTAUR ].walk   = _anim_handle[ MINOTAUR ].walk;  
	_anim_handle[ GREAT_MINOTAUR ].attack = _anim_handle[ MINOTAUR ].attack;
	_anim_handle[ GREAT_MINOTAUR ].dead   = _anim_handle[ MINOTAUR ].dead;  
	
	_anim_handle[ BOSS ].model  = viewer->loadModel( "work/model/enemy/boss/scenes1/model_boss.mv1" );
	_anim_handle[ BOSS ].stay   = viewer->loadModel( "work/model/enemy/boss/scenes1/model_boss_stay.mv1" );
	_anim_handle[ BOSS ].walk   = viewer->loadModel( "work/model/enemy/boss/scenes1/model_boss_walk.mv1" );
	_anim_handle[ BOSS ].attack = viewer->loadModel( "work/model/enemy/boss/scenes1/model_boss_atk.mv1" );
	_anim_handle[ BOSS ].dead   = viewer->loadModel( "work/model/enemy/boss/scenes1/model_boss_dead.mv1" );
}

void EnemyManager::init( ) {
	_super_flame_rod_kill_count   = 0;
	_super_flame_rod_killed_count = 0;
	_enemy_dead      = false;
	_create          = false;
	_use_flame_rod   = false;
	_knock_down_boss = false;
	_enemy_num = 0;
	_enemy_count = 0;
	void ( EnemyManager::* funcArray[ ] )( bool ) = {
		&EnemyManager::createEnemyFloor1,
		&EnemyManager::createEnemyFloor2,
		&EnemyManager::createEnemyFloor3,
		&EnemyManager::createEnemyFloor4,
	};

	void ( EnemyManager::* func )( bool ) = funcArray[ _floor_level - 1 ];
	//void ( EnemyManager::* func )( bool ) = funcArray[ 0 ];	// �f�o�b�O�p
	( this->*func )( false );
}

void EnemyManager::bossInit( ) {
	_super_flame_rod_kill_count   = 0;
	_super_flame_rod_killed_count = 0;
	_enemy_dead      = false;
	_create          = false;
	_use_flame_rod   = false;
	_knock_down_boss = false;
	_enemy_num = 0;
	_enemy_count = 0;
	createEnemyBossFloor( );
}

void EnemyManager::update( ) {
	_turn_end  = false;
	// �_���[�W���󂯂��G�l�~�[��I�o
	selectDamagedEnemy( );
	itemDamage( );
	rodDamage( );
	
	// �|�ꂽ�G�l�~�[��I�o
	enemyDead( );
	// �SEnemy�̏������I�������^�[���I��
	if ( _enemy_count >= _enemy.size( ) ) {
		_enemy_count = 0;
		_turn_end = true;
		_create = false;
		// Enemy�̍Đ���
		createEnemy( );
		// �ړ�����l�b�g���[�N�ɑ���
		for ( unsigned int i = 0; i < _enemy.size( ); i++ ) {
			_network->setSendChipData( NetworkApp::MAP_CHIP_TYPE::ENEMY, _enemy.at( i )->getPos( ), 0, false );
		}
	}
	// �^�[�Q�b�g�n�_�ɓ������Ă���ꍇ�V�����ݒ�
	if ( _enemy.size( ) > 0 ) {
		if ( _enemy.at( _enemy_count )->getTargetPos( ).x == _enemy.at( _enemy_count )->getPos( ).x &&
			 _enemy.at( _enemy_count )->getTargetPos( ).y == _enemy.at( _enemy_count )->getPos( ).y &&
			 _enemy.at( _enemy_count )->getStatus( ).state != CONFUSE ) {
			arriveTarget( _enemy.at( _enemy_count ), _enemy_count );
		}
	}
	// Enemy�^�[���̂ݍs��
	myTurnAction( );
	// �SEnemy�̍X�V����
	for ( unsigned int i = 0; i < _enemy.size( ); i++ ) {
		_enemy.at( i )->update( );
	}
}

void EnemyManager::myTurnAction( ) {
	Turn::STATE turn = _turn->getState( );
	if ( turn == Turn::ENEMY_TURN && _player->isUseZanmetuha( ) == false ) {
		if ( _enemy.size( ) > 0 ) {
			// Player�T�m�͈͓��ł̍s���p�^�[���؂�ւ�
			if ( serchPlayer( _enemy.at( _enemy_count ) ) == true ) {
				// Player�ׂ̗ɂ���ꍇ
				if ( isNextToPlayer( ( int )_enemy.at( _enemy_count )->getPos( ).x, ( int )_enemy.at( _enemy_count )->getPos( ).y ) == true ) {
					_enemy.at( _enemy_count )->setAction( Enemy::ATTACK );
				} else {
					_enemy.at( _enemy_count )->setAction( Enemy::MOVE_CHASE );
				}
			}
			// Player�T�m�͈͊O
			else {
				_enemy.at( _enemy_count )->setAction( Enemy::MOVE_LOITERING );
			}
			// �s���p�^�[���ɂ���ď�����ς���
			if ( _enemy.at( _enemy_count )->getStatus( ).state == CONFUSE ) {  // �������
				if ( ( _enemy.at( _enemy_count )->getAction( ) == Enemy::MOVE_LOITERING || _enemy.at( _enemy_count )->getAction( ) == Enemy::MOVE_CHASE ) 
					 && _enemy.at( _enemy_count )->isDead( ) == false ) {
					confuseMove( _enemy.at( _enemy_count ) );
				} else if ( _enemy.at( _enemy_count )->getAction( ) == Enemy::ATTACK && _enemy.at( _enemy_count )->isDead( ) == false ) {
					confuseAttack( _enemy.at( _enemy_count ) );
				}
			} else if ( _enemy.at( _enemy_count )->getStatus( ).state != PARALYSIS &&
				        !( _enemy.at( _enemy_count )->getStatus( ).state == SLOW && _enemy.at( _enemy_count )->isSpeedAbnormal( ) == true ) ) {  // �}�q�E�ݑ��ȊO
				if ( _enemy.at( _enemy_count )->getStatus( ).state == BIND_TILE ) {  // �ړ��֎~���
					if ( _enemy.at( _enemy_count )->getAction( ) == Enemy::ATTACK && _enemy.at( _enemy_count )->isDead( ) == false ) {
						attack( _enemy.at( _enemy_count ) );
					}
				} else {
					if ( _enemy.at( _enemy_count )->getAction( ) == Enemy::MOVE_LOITERING && _enemy.at( _enemy_count )->isDead( ) == false ) {
						dicisionMovePos( _enemy.at( _enemy_count ), ( int )_enemy.at( _enemy_count )->getTargetPos( ).x, ( int )_enemy.at( _enemy_count )->getTargetPos( ).y );
					} else if ( _enemy.at( _enemy_count )->getAction( ) == Enemy::MOVE_CHASE && _enemy.at( _enemy_count )->isDead( ) == false ) {
						dicisionMovePos( _enemy.at( _enemy_count ), _floor->getPlayerTile( ).x, _floor->getPlayerTile( ).y );
					} else if ( _enemy.at( _enemy_count )->getAction( ) == Enemy::ATTACK && _enemy.at( _enemy_count )->isDead( ) == false && _enemy.at( _enemy_count )->isWarp( ) == false ) {
						attack( _enemy.at( _enemy_count ) );
					}
				}
			}

			// �t���A��Enemy�̂���ʒu�𑗂�
			_floor->setBondEnemy( ( int )_enemy.at( _enemy_count )->getPos( ).x, ( int )_enemy.at( _enemy_count )->getPos( ).y );
			_enemy.at( _enemy_count )->setRoomNum( _floor->getTile( ( int )_enemy.at( _enemy_count )->getPos( ).x, ( int )_enemy.at( _enemy_count )->getPos( ).y ).room );

			// �G�l�~�[�̏�Ԉُ�Ȃǂ̌o�߃^�[����i�߂�
			_enemy.at( _enemy_count )->elapsedAbnormalTurn( );
			_enemy.at( _enemy_count )->elapsedSpeedTurn( );
			_enemy.at( _enemy_count )->elapsedBuffTurn( );
			if ( !( _enemy.at( _enemy_count )->isSpeedAbnormal( ) == true && _enemy.at( _enemy_count )->getStatus( ).state == FAST ) ) {   // �͂₠���ȊO�̎�
				_enemy_count++;
			}

			// �SEnemy�̏������I�������^�[���I��
			if ( _enemy_count >= _enemy.size( ) ) {
				_enemy_count = 0;
				_turn_end = true;
				_create = false;
				// Enemy�̍Đ���
				createEnemy( );
				// �ړ�����l�b�g���[�N�ɑ���
				for ( unsigned int i = 0; i < _enemy.size( ); i++ ) {
					_network->setSendChipData( NetworkApp::MAP_CHIP_TYPE::ENEMY, _enemy.at( i )->getPos( ), 0, false );
				}
				_network->sendStatus( _player->getStatus( ), _player->getStamina( ), _player->getLevel( ) );
			}
		}
		if ( _enemy.size( ) == 0 ) {
			// Enemy�̍Đ���
			createEnemy( );
			// �ړ�����l�b�g���[�N�ɑ���
			for ( unsigned int i = 0; i < _enemy.size( ); i++ ) {
				_network->setSendChipData( NetworkApp::MAP_CHIP_TYPE::ENEMY, _enemy.at( i )->getPos( ), 0, false );
			}
			_turn_end = true;
		}
	}
}

void EnemyManager::bossUpdate( ) {
	_turn_end  = false;
	damagedBoss( );
	itemDamageBoss( );
	rodDamageBoss( );
	// ���S
	if ( _enemy.size( ) > 0 ) {
		if ( _enemy.at( 0 )->getStatus( ).life < 0 ) {
			if ( _enemy_dead == false ) {
				_enemy.at( 0 )->deadAnim( );
				_enemy.at( 0 )->dead( );
				setBondBossTile( true );
				_enemy_dead = true;
				_super_flame_rod_kill_count++;
			}
			// �A�j���[�V�������I��������폜����
			if ( _enemy.at( 0 )->isEndDeadAnim( ) == true ) {
				setBondBossTile( true );
				_message->createFont( _enemy.at( 0 )->getName( ), "", "", 0, MessageLog::KNOCK_DOWN );
				_enemy.erase( _enemy.begin( ) );
				_enemy.shrink_to_fit( );
				_knock_down_boss = true;
				_enemy_dead = false;
				_super_flame_rod_killed_count++;
			}
		}
	}
	// Enemy�^�[���̂ݍs��
	myTurnActionBossScene( );
	// �SEnemy�̍X�V����
	for ( unsigned int i = 0; i < _enemy.size( ); i++ ) {
		_enemy.at( i )->update( );
	}
}

void EnemyManager::myTurnActionBossScene( ) {
	Turn::STATE turn = _turn->getState( );
	if ( turn == Turn::ENEMY_TURN && _player->isUseZanmetuha( ) == false ) {
		if ( _enemy.size( ) > 0 ) {
			// Player�T�m�͈͓��ł̍s���p�^�[���؂�ւ�
			if ( isNextToPlayerBoss( ( int )_enemy.at( 0 )->getPos( ).x, ( int )_enemy.at( 0 )->getPos( ).y ) == true ) {
				_enemy.at( 0 )->setAction( Enemy::ATTACK );
			} else {
				_enemy.at( 0 )->setAction( Enemy::MOVE_CHASE );
			}
			// �s���p�^�[���ɂ���ď�����ς���
			if ( _enemy.at( 0 )->getStatus( ).state == CONFUSE ) {  // �������
				if ( ( _enemy.at( 0 )->getAction( ) == Enemy::MOVE_CHASE ) && _enemy.at( 0 )->isDead( ) == false ) {
					confuseMoveBoss( );
				} else if ( _enemy.at( 0 )->getAction( ) == Enemy::ATTACK && _enemy.at( 0 )->isDead( ) == false ) {
					confuseAttackBoss( );
				}
			} else if ( _enemy.at( 0 )->getStatus( ).state != PARALYSIS &&
				        !( _enemy.at( 0 )->getStatus( ).state == SLOW && _enemy.at( 0 )->isSpeedAbnormal( ) == true ) ) {  // �}�q�E�ݑ��ȊO
				if ( _enemy.at( 0 )->getStatus( ).state == BIND_TILE ) {  // �ړ��֎~���
					if ( _enemy.at( 0 )->getAction( ) == Enemy::ATTACK && _enemy.at( 0 )->isDead( ) == false ) {
						attackBoss( );
					}
				} else {
					if ( _enemy.at( 0 )->getAction( ) == Enemy::MOVE_CHASE && _enemy.at( 0 )->isDead( ) == false ) {
						dicisionMovePosBoss( _floor->getPlayerTile( ).x, _floor->getPlayerTile( ).y );
					} else if ( _enemy.at( 0 )->getAction( ) == Enemy::ATTACK && _enemy.at( 0 )->isDead( ) == false ) {
						attackBoss( );
					}
				}
			}
			// �t���A��Enemy�̂���ʒu�𑗂�
			setBondBossTile( false );
			_enemy.at( 0 )->setRoomNum( _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x, ( int )_enemy.at( 0 )->getPos( ).y ).room );
			_enemy.at( 0 )->elapsedAbnormalTurn( );
			_enemy.at( 0 )->elapsedSpeedTurn( );
			_enemy.at( 0 )->elapsedBuffTurn( );
			if ( !( _enemy.at( 0 )->isSpeedAbnormal( ) == true && _enemy.at( _enemy_count )->getStatus( ).state == FAST ) ) {   // �͂₠���ȊO�̎�
				_turn_end = true;
				// �ړ�����l�b�g���[�N�ɑ���
				for ( unsigned int i = 0; i < _enemy.size( ); i++ ) {
					_network->setSendChipData( NetworkApp::MAP_CHIP_TYPE::ENEMY, _enemy.at( i )->getPos( ), 0, false );
				}
				_network->sendStatus( _player->getStatus( ), _player->getStamina( ), _player->getLevel( ) );
			}
		}
	}
}

void EnemyManager::createEnemyFloor1( bool is_recreate ) {
	// �o��������
	ENEMY_DATA octo_data   = getEnemyDataForName( ENEMY_NAME[ OCTO_POT ] );
	ENEMY_DATA swan_data   = getEnemyDataForName( ENEMY_NAME[ SWANGLER ] );
	ENEMY_DATA s_octo_data = getEnemyDataForName( ENEMY_NAME[ SILVER_OCTO_POT ] );

	// �����z�u�G�l�~�[��
	_start_enemy_num = 1;
	// �ő�G�l�~�[��
	_max_enemy_num = 3;
	// �Ă��̊m��
	int probability[ ] = { 9000, 9900 };
	if ( is_recreate == false ) {
		// �����z�u����Enemy
		for ( unsigned int i  = 0; i < _start_enemy_num; i++ ) {
			EnemyPtr enemy;
			_enemy_num++;
			int num = rand( ) % 10000;
			if ( num < probability[ 0 ] ) {
				// �����_���ɂǂ����̕����̃^�C���ɐ���
				enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, OCTO_POT, _anim_handle[ OCTO_POT ], OCTO_POT_SCALE, octo_data ) );
			} else if ( num < probability[ 1 ] ) {
				// �����_���ɂǂ����̕����̃^�C���ɐ���
				enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, SWANGLER, _anim_handle[ SWANGLER ], SWANGLER_SCALE, swan_data ) );
			} else {
				// �����_���ɂǂ����̕����̃^�C���ɐ���
				enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, SILVER_OCTO_POT, _anim_handle[ SILVER_OCTO_POT ], OCTO_POT_SCALE, s_octo_data ) );
			}
			enemy->loadShadow( _shadow_handle );
			enemy->init( _enemy_num, createPos( ) );
			_enemy.push_back( enemy );
			_effect->playEffect( Effect::EFFECT_SPORN, _enemy.at( i )->getDrawPos( ) + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), EFFECT_NONE_NUM );
		}
		for ( unsigned int i = 0; i < _enemy.size( ); i++ ) {
			// pos���l�b�g���[�N�ɑ���
			_network->setSendChipData( NetworkApp::MAP_CHIP_TYPE::ENEMY, _enemy.at( i )->getPos( ), 0, false );
			// �G�l�~�[�̃^�C���ݒ�
			_floor->setBondEnemy( ( int )_enemy.at( i )->getPos( ).x, ( int )_enemy.at( i )->getPos( ).y );
			_enemy.at( i )->setRoomNum( _floor->getTile( ( int )_enemy.at( i )->getPos( ).x, ( int )_enemy.at( i )->getPos( ).y ).room );
			// �L���Ƃ̐ڑ��n�_���^�[�Q�b�g�n�_�ɐݒ�
			Floor::TILE target = setRoomTarget( _enemy.at( i ), i );
			_enemy.at( i )->setTargetPos( target.x, target.y );
		}
	} else {
		EnemyPtr enemy;
		_enemy_num++;
		int num = rand( ) % 10000;
		if ( num < probability[ 0 ] ) {
			// �����_���ɂǂ����̕����̃^�C���ɐ���
			enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, OCTO_POT, _anim_handle[ OCTO_POT ], OCTO_POT_SCALE, octo_data ) );
		} else if ( num < probability[ 1 ] ) {
			// �����_���ɂǂ����̕����̃^�C���ɐ���
			enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, SWANGLER, _anim_handle[ SWANGLER ], SWANGLER_SCALE, swan_data ) );
		} else {
			// �����_���ɂǂ����̕����̃^�C���ɐ���
			enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, SILVER_OCTO_POT, _anim_handle[ SILVER_OCTO_POT ], OCTO_POT_SCALE, s_octo_data ) );
		}
		enemy->loadShadow( _shadow_handle );
		enemy->init( _enemy_num, createPos( ) );
		// �G�l�~�[�̃^�C���ݒ�
		_floor->setBondEnemy( ( int )enemy->getPos( ).x, ( int )enemy->getPos( ).y );
		enemy->setRoomNum( _floor->getTile( ( int )enemy->getPos( ).x, ( int )enemy->getPos( ).y ).room );
		// �L���Ƃ̐ڑ��n�_���^�[�Q�b�g�n�_�ɐݒ�
		Floor::TILE target = setRoomTarget( enemy, _enemy.size( ) );
		enemy->setTargetPos( target.x, target.y );
		_enemy.push_back( enemy );
		_effect->playEffect( Effect::EFFECT_SPORN, enemy->getDrawPos( ) + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), EFFECT_NONE_NUM );
	}
}

void EnemyManager::createEnemyFloor2( bool is_recreate ) {
	// �o��������
	ENEMY_DATA octo_data   = getEnemyDataForName( ENEMY_NAME[ OCTO_POT ] );			// 20%
	ENEMY_DATA swan_data   = getEnemyDataForName( ENEMY_NAME[ SWANGLER ] );			// 30%
	ENEMY_DATA spi_data    = getEnemyDataForName( ENEMY_NAME[ SPIDER ] );			// 35%
	ENEMY_DATA mino_data   = getEnemyDataForName( ENEMY_NAME[ MINOTAUR ] );			// 5%
	ENEMY_DATA g_octo_data = getEnemyDataForName( ENEMY_NAME[ GREAT_OCTO_POT ] );	// 5%
	ENEMY_DATA s_octo_data = getEnemyDataForName( ENEMY_NAME[ SILVER_OCTO_POT ] );	// 5%

	// �����z�u�G�l�~�[��
	_start_enemy_num = 2;
	// �ő�G�l�~�[��
	_max_enemy_num = 6;
	// �Ă��̊m��
	int probability[ ] = { 2000, 5000, 8500, 9000, 9500 };
	if ( is_recreate == false ) {
		// �����z�u����Enemy
		for ( unsigned int i  = 0; i < _start_enemy_num; i++ ) {
			EnemyPtr enemy;
			_enemy_num++;
			int num = rand( ) % 10000;
			if ( num < probability[ 0 ] ) {
				// �����_���ɂǂ����̕����̃^�C���ɐ���
				enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, OCTO_POT, _anim_handle[ OCTO_POT ], OCTO_POT_SCALE, octo_data ) );
			} else if ( num < probability[ 1 ] ) {
				// �����_���ɂǂ����̕����̃^�C���ɐ���
				enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, SWANGLER, _anim_handle[ SWANGLER ], SWANGLER_SCALE, swan_data ) );
			} else if ( num < probability[ 2 ] ) {
				// �����_���ɂǂ����̕����̃^�C���ɐ���
				enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, SPIDER, _anim_handle[ SPIDER ], SPIDER_SCALE, spi_data ) );
			} else if ( num < probability[ 3 ] ) {
				// �����_���ɂǂ����̕����̃^�C���ɐ���
				enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, MINOTAUR, _anim_handle[ MINOTAUR ], MINO_SCALE, mino_data ) );
			}  else if ( num < probability[ 4 ] ) {
				// �����_���ɂǂ����̕����̃^�C���ɐ���
				enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, GREAT_OCTO_POT, _anim_handle[ GREAT_OCTO_POT ], OCTO_POT_SCALE, g_octo_data ) );
			} else {
				// �����_���ɂǂ����̕����̃^�C���ɐ���
				enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, SILVER_OCTO_POT, _anim_handle[ SILVER_OCTO_POT ], OCTO_POT_SCALE, s_octo_data ) );
			}
			enemy->loadShadow( _shadow_handle );
			enemy->init( _enemy_num, createPos( ) );
			_enemy.push_back( enemy );
			_effect->playEffect( Effect::EFFECT_SPORN, _enemy.at( i )->getDrawPos( ) + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), EFFECT_NONE_NUM );
		}
		for ( unsigned int i = 0; i < _enemy.size( ); i++ ) {
			// pos���l�b�g���[�N�ɑ���
			_network->setSendChipData( NetworkApp::MAP_CHIP_TYPE::ENEMY, _enemy.at( i )->getPos( ), 0, false );
			// �G�l�~�[�̃^�C���ݒ�
			_floor->setBondEnemy( ( int )_enemy.at( i )->getPos( ).x, ( int )_enemy.at( i )->getPos( ).y );
			_enemy.at( i )->setRoomNum( _floor->getTile( ( int )_enemy.at( i )->getPos( ).x, ( int )_enemy.at( i )->getPos( ).y ).room );
			// �L���Ƃ̐ڑ��n�_���^�[�Q�b�g�n�_�ɐݒ�
			Floor::TILE target = setRoomTarget( _enemy.at( i ), i );
			_enemy.at( i )->setTargetPos( target.x, target.y );
		}
	} else {
		EnemyPtr enemy;
		_enemy_num++;
		int num = rand( ) % 10000;
		if ( num < probability[ 0 ] ) {
			// �����_���ɂǂ����̕����̃^�C���ɐ���
			enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, OCTO_POT, _anim_handle[ OCTO_POT ], OCTO_POT_SCALE, octo_data ) );
		} else if ( num < probability[ 1 ] ) {
			// �����_���ɂǂ����̕����̃^�C���ɐ���
			enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, SWANGLER, _anim_handle[ SWANGLER ], SWANGLER_SCALE, swan_data ) );
		} else if ( num < probability[ 2 ] ) {
			// �����_���ɂǂ����̕����̃^�C���ɐ���
			enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, SPIDER, _anim_handle[ SPIDER ], SPIDER_SCALE, spi_data ) );
		} else if ( num < probability[ 3 ] ) {
			// �����_���ɂǂ����̕����̃^�C���ɐ���
			enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, MINOTAUR, _anim_handle[ MINOTAUR ], MINO_SCALE, mino_data ) );
		}  else if ( num < probability[ 4 ] ) {
			// �����_���ɂǂ����̕����̃^�C���ɐ���
			enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, GREAT_OCTO_POT, _anim_handle[ GREAT_OCTO_POT ], OCTO_POT_SCALE, g_octo_data ) );
		} else {
			// �����_���ɂǂ����̕����̃^�C���ɐ���
			enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, SILVER_OCTO_POT, _anim_handle[ SILVER_OCTO_POT ], OCTO_POT_SCALE, s_octo_data ) );
		}
		enemy->loadShadow( _shadow_handle );
		enemy->init( _enemy_num, createPos( ) );
		// �G�l�~�[�̃^�C���ݒ�
		_floor->setBondEnemy( ( int )enemy->getPos( ).x, ( int )enemy->getPos( ).y );
		enemy->setRoomNum( _floor->getTile( ( int )enemy->getPos( ).x, ( int )enemy->getPos( ).y ).room );
		// �L���Ƃ̐ڑ��n�_���^�[�Q�b�g�n�_�ɐݒ�
		Floor::TILE target = setRoomTarget( enemy, _enemy.size( ) );
		enemy->setTargetPos( target.x, target.y );
		_enemy.push_back( enemy );
		_effect->playEffect( Effect::EFFECT_SPORN, enemy->getDrawPos( ) + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), EFFECT_NONE_NUM );
	}
}

void EnemyManager::createEnemyFloor3( bool is_recreate ) {
	// �o��������
	ENEMY_DATA swan_data    = getEnemyDataForName( ENEMY_NAME[ GREAT_SWANGLER ] );	// 25%
	ENEMY_DATA mino_data    = getEnemyDataForName( ENEMY_NAME[ MINOTAUR ] );		// 40%
	ENEMY_DATA g_octo_data  = getEnemyDataForName( ENEMY_NAME[ GREAT_OCTO_POT ] );	// 29.5%
	ENEMY_DATA s_octo_data  = getEnemyDataForName( ENEMY_NAME[ SILVER_OCTO_POT ] );	// 5%
	ENEMY_DATA go_octo_data = getEnemyDataForName( ENEMY_NAME[ GOLD_OCTO_POT ] );	// 0.5%

	// �����z�u�G�l�~�[��
	_start_enemy_num = 5;
	// �ő�G�l�~�[��
	_max_enemy_num = 8;
	// �Ă��̊m��
	int probability[ ] = { 2500, 6500, 9450, 9950 };
	if ( is_recreate == false ) {
		// �����z�u����Enemy
		for ( unsigned int i  = 0; i < _start_enemy_num; i++ ) {
			EnemyPtr enemy;
			_enemy_num++;
			int num = rand( ) % 10000;
			if ( num < probability[ 0 ] ) {
				// �����_���ɂǂ����̕����̃^�C���ɐ���
				enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, GREAT_SWANGLER, _anim_handle[ GREAT_SWANGLER ], SWANGLER_SCALE, swan_data ) );
			} else if ( num < probability[ 1 ] ) {
				// �����_���ɂǂ����̕����̃^�C���ɐ���
				enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, MINOTAUR, _anim_handle[ MINOTAUR ], MINO_SCALE, mino_data ) );
			} else if ( num < probability[ 2 ] ) {
				// �����_���ɂǂ����̕����̃^�C���ɐ���
				enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, GREAT_OCTO_POT, _anim_handle[ GREAT_OCTO_POT ], OCTO_POT_SCALE, g_octo_data ) );
			} else if ( num < probability[ 3 ] ) {
				// �����_���ɂǂ����̕����̃^�C���ɐ���
				enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, SILVER_OCTO_POT, _anim_handle[ SILVER_OCTO_POT ], OCTO_POT_SCALE, s_octo_data ) );
			} else {
				// �����_���ɂǂ����̕����̃^�C���ɐ���
				enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, GOLD_OCTO_POT, _anim_handle[ GOLD_OCTO_POT ], OCTO_POT_SCALE, go_octo_data ) );
			}
			enemy->loadShadow( _shadow_handle );
			enemy->init( _enemy_num, createPos( ) );
			_enemy.push_back( enemy );
			_effect->playEffect( Effect::EFFECT_SPORN, _enemy.at( i )->getDrawPos( ) + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), EFFECT_NONE_NUM );
		}
		for ( unsigned int i = 0; i < _enemy.size( ); i++ ) {
			// pos���l�b�g���[�N�ɑ���
			_network->setSendChipData( NetworkApp::MAP_CHIP_TYPE::ENEMY, _enemy.at( i )->getPos( ), 0, false );
			// �G�l�~�[�̃^�C���ݒ�
			_floor->setBondEnemy( ( int )_enemy.at( i )->getPos( ).x, ( int )_enemy.at( i )->getPos( ).y );
			_enemy.at( i )->setRoomNum( _floor->getTile( ( int )_enemy.at( i )->getPos( ).x, ( int )_enemy.at( i )->getPos( ).y ).room );
			// �L���Ƃ̐ڑ��n�_���^�[�Q�b�g�n�_�ɐݒ�
			Floor::TILE target = setRoomTarget( _enemy.at( i ), i );
			_enemy.at( i )->setTargetPos( target.x, target.y );
		}
	} else {
		EnemyPtr enemy;
		_enemy_num++;
		int num = rand( ) % 10000;
		if ( num < probability[ 0 ] ) {
			// �����_���ɂǂ����̕����̃^�C���ɐ���
			enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, GREAT_SWANGLER, _anim_handle[ GREAT_SWANGLER ], SWANGLER_SCALE, swan_data ) );
		} else if ( num < probability[ 1 ] ) {
			// �����_���ɂǂ����̕����̃^�C���ɐ���
			enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, MINOTAUR, _anim_handle[ MINOTAUR ], MINO_SCALE, mino_data ) );
		} else if ( num < probability[ 2 ] ) {
			// �����_���ɂǂ����̕����̃^�C���ɐ���
			enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, GREAT_OCTO_POT, _anim_handle[ GREAT_OCTO_POT ], OCTO_POT_SCALE, g_octo_data ) );
		} else if ( num < probability[ 3 ] ) {
			// �����_���ɂǂ����̕����̃^�C���ɐ���
			enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, SILVER_OCTO_POT, _anim_handle[ SILVER_OCTO_POT ], OCTO_POT_SCALE, s_octo_data ) );
		} else {
			// �����_���ɂǂ����̕����̃^�C���ɐ���
			enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, GOLD_OCTO_POT, _anim_handle[ GOLD_OCTO_POT ], OCTO_POT_SCALE, go_octo_data ) );
		}
		enemy->loadShadow( _shadow_handle );
		enemy->init( _enemy_num, createPos( ) );
		// �G�l�~�[�̃^�C���ݒ�
		_floor->setBondEnemy( ( int )enemy->getPos( ).x, ( int )enemy->getPos( ).y );
		enemy->setRoomNum( _floor->getTile( ( int )enemy->getPos( ).x, ( int )enemy->getPos( ).y ).room );
		// �L���Ƃ̐ڑ��n�_���^�[�Q�b�g�n�_�ɐݒ�
		Floor::TILE target = setRoomTarget( enemy, _enemy.size( ) );
		enemy->setTargetPos( target.x, target.y );
		_enemy.push_back( enemy );
		_effect->playEffect( Effect::EFFECT_SPORN, enemy->getDrawPos( ) + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), EFFECT_NONE_NUM );
	}
}

void EnemyManager::createEnemyFloor4( bool is_recreate ) {
	// �o��������
	ENEMY_DATA swan_data    = getEnemyDataForName( ENEMY_NAME[ GREAT_SWANGLER ] );	// 30%
	ENEMY_DATA spi_data     = getEnemyDataForName( ENEMY_NAME[ GREAT_SPIDER ] );	// 35%
	ENEMY_DATA gochim_data  = getEnemyDataForName( ENEMY_NAME[ GOCHIMPANZEE ] );	// 15%
	ENEMY_DATA g_mino_data  = getEnemyDataForName( ENEMY_NAME[ GREAT_MINOTAUR ] );	// 14.5%
	ENEMY_DATA s_octo_data  = getEnemyDataForName( ENEMY_NAME[ SILVER_OCTO_POT ] );	// 5%
	ENEMY_DATA go_octo_data = getEnemyDataForName( ENEMY_NAME[ GOLD_OCTO_POT ] );	// 0.5%

	// �����z�u�G�l�~�[��
	_start_enemy_num = 8;
	// �ő�G�l�~�[��
	_max_enemy_num = 10;
	// �Ă��̊m��
	int probability[ ] = { 3000, 6500, 8000, 9450, 9950 };
	if ( is_recreate == false ) {
		// �����z�u����Enemy
		for ( unsigned int i  = 0; i < _start_enemy_num; i++ ) {
			EnemyPtr enemy;
			_enemy_num++;
			int num = rand( ) % 10000;
			if ( num < probability[ 0 ] ) {
				// �����_���ɂǂ����̕����̃^�C���ɐ���
				enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, GREAT_SWANGLER, _anim_handle[ GREAT_SWANGLER ], SWANGLER_SCALE, swan_data ) );
			} else if ( num < probability[ 1 ] ) {
				// �����_���ɂǂ����̕����̃^�C���ɐ���
				enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, GREAT_SPIDER, _anim_handle[ GREAT_SPIDER ], SPIDER_SCALE, spi_data ) );
			} else if ( num < probability[ 2 ] ) {
				// �����_���ɂǂ����̕����̃^�C���ɐ���
				enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, GOCHIMPANZEE, _anim_handle[ GOCHIMPANZEE ], GOCHIM_SCALE, gochim_data ) );
			} else if ( num < probability[ 3 ] ) {
				// �����_���ɂǂ����̕����̃^�C���ɐ���
				enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, GREAT_MINOTAUR, _anim_handle[ GREAT_MINOTAUR ], MINO_SCALE, g_mino_data ) );
			} else if ( num < probability[ 4 ] ) {
				// �����_���ɂǂ����̕����̃^�C���ɐ���
				enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, SILVER_OCTO_POT, _anim_handle[ SILVER_OCTO_POT ], OCTO_POT_SCALE, s_octo_data ) );
			} else {
				// �����_���ɂǂ����̕����̃^�C���ɐ���
				enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, GOLD_OCTO_POT, _anim_handle[ GOLD_OCTO_POT ], OCTO_POT_SCALE, go_octo_data ) );
			}
			enemy->loadShadow( _shadow_handle );
			enemy->init( _enemy_num, createPos( ) );
			_enemy.push_back( enemy );
			_effect->playEffect( Effect::EFFECT_SPORN, _enemy.at( i )->getDrawPos( ) + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), EFFECT_NONE_NUM );
		}
		for ( unsigned int i = 0; i < _enemy.size( ); i++ ) {
			// pos���l�b�g���[�N�ɑ���
			_network->setSendChipData( NetworkApp::MAP_CHIP_TYPE::ENEMY, _enemy.at( i )->getPos( ), 0, false );
			// �G�l�~�[�̃^�C���ݒ�
			_floor->setBondEnemy( ( int )_enemy.at( i )->getPos( ).x, ( int )_enemy.at( i )->getPos( ).y );
			_enemy.at( i )->setRoomNum( _floor->getTile( ( int )_enemy.at( i )->getPos( ).x, ( int )_enemy.at( i )->getPos( ).y ).room );
			// �L���Ƃ̐ڑ��n�_���^�[�Q�b�g�n�_�ɐݒ�
			Floor::TILE target = setRoomTarget( _enemy.at( i ), i );
			_enemy.at( i )->setTargetPos( target.x, target.y );
		}
	} else {
		EnemyPtr enemy;
		_enemy_num++;
		int num = rand( ) % 10000;
		if ( num < probability[ 0 ] ) {
			// �����_���ɂǂ����̕����̃^�C���ɐ���
			enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, GREAT_SWANGLER, _anim_handle[ GREAT_SWANGLER ], SWANGLER_SCALE, swan_data ) );
		} else if ( num < probability[ 1 ] ) {
			// �����_���ɂǂ����̕����̃^�C���ɐ���
			enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, GREAT_SPIDER, _anim_handle[ GREAT_SPIDER ], SPIDER_SCALE, spi_data ) );
		} else if ( num < probability[ 2 ] ) {
			// �����_���ɂǂ����̕����̃^�C���ɐ���
			enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, GOCHIMPANZEE, _anim_handle[ GOCHIMPANZEE ], GOCHIM_SCALE, gochim_data ) );
		} else if ( num < probability[ 3 ] ) {
			// �����_���ɂǂ����̕����̃^�C���ɐ���
			enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, GREAT_MINOTAUR, _anim_handle[ GREAT_MINOTAUR ], MINO_SCALE, g_mino_data ) );
		} else if ( num < probability[ 4 ] ) {
			// �����_���ɂǂ����̕����̃^�C���ɐ���
			enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, SILVER_OCTO_POT, _anim_handle[ SILVER_OCTO_POT ], OCTO_POT_SCALE, s_octo_data ) );
		} else {
			// �����_���ɂǂ����̕����̃^�C���ɐ���
			enemy = EnemyPtr( new Enemy( _floor, _network, _message, _effect, GOLD_OCTO_POT, _anim_handle[ GOLD_OCTO_POT ], OCTO_POT_SCALE, go_octo_data ) );
		}
		enemy->loadShadow( _shadow_handle );
		enemy->init( _enemy_num, createPos( ) );
		// �G�l�~�[�̃^�C���ݒ�
		_floor->setBondEnemy( ( int )enemy->getPos( ).x, ( int )enemy->getPos( ).y );
		enemy->setRoomNum( _floor->getTile( ( int )enemy->getPos( ).x, ( int )enemy->getPos( ).y ).room );
		// �L���Ƃ̐ڑ��n�_���^�[�Q�b�g�n�_�ɐݒ�
		Floor::TILE target = setRoomTarget( enemy, _enemy.size( ) );
		enemy->setTargetPos( target.x, target.y );
		_enemy.push_back( enemy );
		_effect->playEffect( Effect::EFFECT_SPORN, enemy->getDrawPos( ) + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), EFFECT_NONE_NUM );
	}
}

Floor::TILE EnemyManager::createPos( ) {
	Floor::TILE tile;
	while ( true ) {
		tile = _floor->getRandomFloor( );
		// �^�[�Q�b�g�n�_�Ƀv���C���[���G�l�~�[������ꍇ�Đݒ肷��
		if ( tile.bond != Floor::PLAYER && tile.bond != Floor::ENEMY ) {
			break;
		}
	}
	return tile;
}

void EnemyManager::createEnemyBossFloor( ) {
	// �����z�u�G�l�~�[��
	_start_enemy_num = 1;
	// �ő�G�l�~�[��
	_max_enemy_num = 1;
	// Boss�̐���
	_enemy_num++;
	ENEMY_DATA boss_data  = getEnemyDataForName( ENEMY_NAME[ BOSS ] );
	EnemyPtr boss = EnemyPtr( new Enemy( _floor, _network, _message, _effect, BOSS, _anim_handle[ BOSS ], BOSS_SCALE, boss_data ) );
	boss->loadShadow( _shadow_handle );
	_enemy.push_back( boss );
	_effect->playEffect( Effect::EFFECT_SPORN, boss->getDrawPos( ) + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), EFFECT_NONE_NUM );
	_enemy.at( 0 )->init( _enemy_num, _floor->getBossRoomCharacterPos( Floor::BOSS_ROOM_BOSS ) );
	for ( unsigned int i = 0; i < _enemy.size( ); i++ ) {
		// pos���l�b�g���[�N�ɑ���
		_network->setSendChipData( NetworkApp::MAP_CHIP_TYPE::ENEMY, _enemy.at( i )->getPos( ), 0, false );
		// �G�l�~�[�̃^�C���ݒ�
		setBondBossTile( false );
		_enemy.at( i )->setRoomNum( _floor->getTile( ( int )_enemy.at( i )->getPos( ).x, ( int )_enemy.at( i )->getPos( ).y ).room );
	}
}

void EnemyManager::createEnemy( ) {
	if ( _enemy.size( ) < _max_enemy_num ) {
		// �T�^�[���Ɉ�̐���
		if ( _turn->getTurnCount( ) % CREATE_ENEMY_TURN == 0 && _turn->getTurnCount( ) > 0 && _create == false ) {
			void ( EnemyManager::* funcArray[ ] )( bool ) = {
				&EnemyManager::createEnemyFloor1,
				&EnemyManager::createEnemyFloor2,
				&EnemyManager::createEnemyFloor3,
				&EnemyManager::createEnemyFloor4,
			};

			void ( EnemyManager::* func )( bool ) = funcArray[ _floor_level - 1 ];
			//void ( EnemyManager::* func )( bool ) = funcArray[ 0 ];
			( this->*func )( true );

			_create = true;
		}
	}
}

bool EnemyManager::serchPlayer( EnemyPtr enemy ) {
	// Enemy�̍��W�擾
	int enemy_x = ( int )enemy->getPos( ).x;
	int enemy_y = ( int )enemy->getPos( ).y;

	// Enemy��Room�ɂ���܂��͕����ׂ̗̘L���ɂ���ꍇ
	if ( _floor->getTile( enemy_x, enemy_y ).type == Floor::ROOM ||
		 _floor->getTile( enemy_x, enemy_y ).next_to_room == true ) {
		if ( isRoomSerchRange( enemy ) == true ) {
			// �v���C���[�𔭌�
			enemy->setFindPlayer( true );
			return true;
		}
	}
	// Enemy���L���ɂ���ꍇ
	else if ( _floor->getTile( enemy_x, enemy_y ).type == Floor::AISLE ) {
		if ( isAisleSerchRange( enemy ) == true ) {
			// �v���C���[�𔭌�
			enemy->setFindPlayer( true );
			return true;
		}
	}
	// �v���C���[�𔭌�����
	enemy->setFindPlayer( false );
	return false;
}

bool EnemyManager::isRoomSerchRange( EnemyPtr enemy ) {
	int serch_dis;
	// �v���C���[�𔭌����Ă��邩�ǂ����ŒT���͈͂�ς���
	if ( enemy->isFindPlayer( ) == true ) {
		serch_dis = FIND_AISLE_DIS;
	} else {
		serch_dis = AISLE_DIS;
	}

	// Player�̍��W�擾
	int player_x = _floor->getPlayerTile( ).x;
	int player_y = _floor->getPlayerTile( ).y;
	// ���݂���Room�̑傫�����擾
	int room_num = _floor->getTile( ( int )enemy->getPos( ).x, ( int )enemy->getPos( ).y ).room;
	Floor::ROOM_DATA enemy_room = _floor->getRoom( room_num );
	int origin_x = enemy_room.origin.x;
	int origin_y = enemy_room.origin.y;
	int width    = enemy_room.width;
	int height   = enemy_room.height;
	// �͈͓��ɂ����true��Ԃ�
	// ������
	if ( player_x < origin_x + width && player_x >= origin_x &&
		 player_y < origin_y + height && player_y >= origin_y ) {
		return true;
	}
	// ��������͈͓̔�
	// �㉺
	for ( int i = 0; i <= width; i++ ) {
		if ( nearRoomSerch( _floor->getTile( origin_x + i, origin_y - 1 ), serch_dis, 0 ) == true ) {
			return true;
		}
		if ( nearRoomSerch( _floor->getTile( origin_x + i, origin_y + height + 1 ), serch_dis, 0 ) == true ) {
			return true;
		}
	}
	// ���E
	for ( int i = 0; i <= height; i++ ) {
		if ( nearRoomSerch( _floor->getTile( origin_x - 1, origin_y + i ), serch_dis, 0 ) == true ) {
			return true;
		}
		if ( nearRoomSerch( _floor->getTile( origin_x + width + 1, origin_y + i ), serch_dis, 0 ) == true ) {
			return true;
		}
	}
	return false;
}

bool EnemyManager::nearRoomSerch( Floor::TILE tile, int serch_range, int count ) {
	if ( tile.type == Floor::WALL ) {
		return false;
	} else {
		// �v���C���[��������true
		if ( tile.bond == Floor::PLAYER ) {
			return true;
		}
		count++;
		// �͈͂𒴂�����false
		if ( count > serch_range ) {
			return false;
		}
		// �J��Ԃ�����
		for ( int i = -1; i <= 1; i += 2 ) {
			if ( nearRoomSerch( _floor->getTile( tile.x + i, tile.y ), serch_range, count ) == true ) {
				return true;
			}
			if ( nearRoomSerch( _floor->getTile( tile.x, tile.y + i ), serch_range, count ) == true ) {
				return true;
			}
		}
	}
	return false;
}

bool EnemyManager::isAisleSerchRange( EnemyPtr enemy ) {
	// �T���͈�
	int serch_dis;
	// Player�̍��W�擾
	int player_x = _floor->getPlayerTile( ).x;
	int player_y = _floor->getPlayerTile( ).y;
	// Enemy�̍��W�擾
	int enemy_x = ( int )enemy->getPos( ).x;
	int enemy_y = ( int )enemy->getPos( ).y;

	// �v���C���[�𔭌����Ă��邩�ǂ����ŒT���͈͂�ς���
	if ( enemy->isFindPlayer( ) == true ) {
		serch_dis = FIND_AISLE_DIS;
	} else {
		serch_dis = AISLE_DIS;
	}

	// Player�𔭌����Ă���Ƃ�
	if ( enemy->isFindPlayer( ) == true ) {
		// �͈͓��ɂ����true��Ԃ�
		if ( player_x < enemy_x + serch_dis && player_x > enemy_x - serch_dis &&
			 player_y < enemy_y + serch_dis && player_y > enemy_y - serch_dis ) {
			return true;
		}
	}
	// Player�𔭌����Ă��Ȃ��Ƃ�
	else {
		// �r���ŕǂɂԂ������疢����
		// ��
		for ( int i = 0; i < serch_dis; i++  ) {
			if ( _floor->getTile( enemy_x + i, enemy_y ).type == Floor::WALL ) {
				break;
			}
			if ( enemy_x + i == player_x && player_y == enemy_y ) {
				return true;
			}
		}
		// �E
		for ( int i = 0; i < serch_dis; i++  ) {
			if ( _floor->getTile( enemy_x - i, enemy_y ).type == Floor::WALL ) {
				break;
			}
			if ( enemy_x - i == player_x && player_y == enemy_y ) {
				return true;
			}
		}
		// ��
		for ( int i = 0; i < serch_dis; i++  ) {
			if ( _floor->getTile( enemy_x, enemy_y - i ).type == Floor::WALL ) {
				break;
			}
			if ( enemy_y - i == player_y && player_x == enemy_x ) {
				return true;
			}
		}
		// ��
		for ( int i = 0; i < serch_dis; i++  ) {
			if ( _floor->getTile( enemy_x, enemy_y + i ).type == Floor::WALL ) {
				break;
			}
			if ( enemy_y + i == player_y && player_x == enemy_x ) {
				return true;
			}
		}
	}
	return false;
}

void EnemyManager::arriveTarget( EnemyPtr enemy, int num ) {
	// �����n�_�������̏ꍇ
	if ( _floor->getTile( ( int )enemy->getPos( ).x, ( int )enemy->getPos( ).y ).type == Floor::ROOM ) {
		Floor::TILE target = setRoomTarget( enemy, num );
		enemy->setTargetPos( target.x, target.y );
	}
	// �����n�_���L���̏ꍇ
	else if ( _floor->getTile( ( int )enemy->getPos( ).x, ( int )enemy->getPos( ).y ).type == Floor::AISLE ) {
		Floor::TILE target = setAisleTarget( enemy );
		enemy->setTargetPos( target.x, target.y );
	}
}

Floor::TILE EnemyManager::setRoomTarget( EnemyPtr enemy, int num ) {
	int x = ( int )enemy->getPos( ).x;
	int y = ( int )enemy->getPos( ).y;
	Floor::TILE target_tile;
	std::vector<Floor::TILE> target_candidate;
	int room_length =  _floor->getRoom( _floor->getTile( x, y ).room ).longest;

	// �q�����Ă����ԋ߂��L����T��
	for ( int i = room_length; i >= 2; i-- ) {
		// �c
		for( int j = -i; j <= i; j += ( i * 2 ) ) {
			for( int k = -i; k <= i; k++ ) {
				if ( _floor->getTile( x + j, y + k ).type == Floor::AISLE &&
					 _floor->getTile( x + j, y + k ).next_to_room == true &&
					 _floor->getTile( x + j, y + k ).room == _floor->getTile( x, y ).room ) {
					// �������^�[�Q�b�g�����ɒǉ�
					target_candidate.push_back( _floor->getTile( x + j, y + k ) );
				}
			}
		}
		// ��
		for( int j = -i; j <= i; j++ ) {
			for( int k = -i; k <= i; k += ( i * 2 ) ) {
				if ( _floor->getTile( x + j, y + k ).type == Floor::AISLE &&
					 _floor->getTile( x + j, y + k ).next_to_room == true &&
					 _floor->getTile( x + j, y + k ).room == _floor->getTile( x, y ).room ) {
					// �������^�[�Q�b�g�����ɒǉ�
					target_candidate.push_back( _floor->getTile( x + j, y + k ) );
				}
			}
		}
	}
	// ��₩�烉���_���Ń^�[�Q�b�g��I��
	if ( target_candidate.size( ) > 0 ) {
		int num = rand( ) % target_candidate.size( );
		target_tile = target_candidate.at( num );
		return target_tile;
	}
	// �q�����Ă���L������{�̏ꍇ
	target_tile = surroundLookAisle( x, y );
	return target_tile;
}

Floor::TILE EnemyManager::surroundLookAisle( int x, int y ) {
	Floor::TILE target;
	// ���E
	for( int i = -1; i <= 1; i += 2 ) {
		if ( _floor->getTile( x + i, y ).type == Floor::AISLE &&
			 _floor->getTile( x + i, y ).next_to_room == true ) {
			target = _floor->getTile( x + i, y );
			return target;
		}
	}
	// �㉺
	for( int i = -1; i <= 1; i += 2 ) {
		if ( _floor->getTile( x, y + i ).type == Floor::AISLE &&
			 _floor->getTile( x, y + i ).next_to_room == true ) {
			target = _floor->getTile( x, y + i );
			return target;
		}
	}
	// �p
	for( int i = -1; i <= 1; i += 2 ) {
		for( int j = -1; j <= 1; j += 2 ) {
			if ( _floor->getTile( x + i, y + j ).type == Floor::AISLE &&
				 _floor->getTile( x + i, y + j ).next_to_room == true ) {
				// �������L���ׂ̗�Room�^�C�����w��
				target = _floor->getTile( x + i, y + j );
				return target;
			}
		}
	}
	target = _floor->getTile( 0, 0 );
	return target;
}

Floor::TILE EnemyManager::setAisleTarget( EnemyPtr enemy ) {
	int x = ( int )enemy->getPos( ).x;
	int y = ( int )enemy->getPos( ).y;
	Floor::TILE target_tile;
	std::vector< Enemy::ENEMY_AISLE_DIR > dirs;

	// �������ȊO�i�߂Ȃ��Ƃ�
	if ( _floor->getTile( x - 1, y ).type == Floor::WALL &&
		 _floor->getTile( x, y + 1 ).type == Floor::WALL &&
		 _floor->getTile( x, y - 1 ).type == Floor::WALL ) {
		target_tile = checkStraight( enemy, x, y, Enemy::DIR_LEFT );
		return target_tile;
	}
	// �E�����ȊO�i�߂Ȃ��Ƃ�
	if ( _floor->getTile( x + 1, y ).type == Floor::WALL &&
		 _floor->getTile( x, y + 1 ).type == Floor::WALL &&
		 _floor->getTile( x, y - 1 ).type == Floor::WALL ) {
		target_tile = checkStraight( enemy, x, y, Enemy::DIR_RIGHT );
		return target_tile;
	}
	// �������ȊO�i�߂Ȃ��Ƃ�
	if ( _floor->getTile( x + 1, y ).type == Floor::WALL &&
		 _floor->getTile( x - 1, y ).type == Floor::WALL &&
		 _floor->getTile( x, y - 1 ).type == Floor::WALL ) {
		target_tile = checkStraight( enemy, x, y, Enemy::DIR_LOWER );
		return target_tile;
	}
	// ������ȊO�i�߂Ȃ��Ƃ�
	if ( _floor->getTile( x + 1, y ).type == Floor::WALL &&
		 _floor->getTile( x - 1, y ).type == Floor::WALL &&
		 _floor->getTile( x, y + 1 ).type == Floor::WALL ) {
		target_tile = checkStraight( enemy, x, y, Enemy::DIR_UPPER );
		return target_tile;
	}

	// �ړ��\�ȕ�����o�^
	// ������
	if ( _floor->getTile( x + 1, y ).type != Floor::WALL &&
		 enemy->getAisleDir( ) != Enemy::DIR_RIGHT ) {
		dirs.push_back( Enemy::DIR_LEFT );
	}
	// �E����
	if ( _floor->getTile( x - 1, y ).type != Floor::WALL &&
		 enemy->getAisleDir( ) != Enemy::DIR_LEFT ) {
		dirs.push_back( Enemy::DIR_RIGHT );
	}
	// ������
	if ( _floor->getTile( x, y + 1 ).type != Floor::WALL &&
		 enemy->getAisleDir( ) != Enemy::DIR_UPPER ) {
		dirs.push_back( Enemy::DIR_LOWER );
	}
	// �����
	if ( _floor->getTile( x, y - 1 ).type != Floor::WALL &&
		 enemy->getAisleDir( ) != Enemy::DIR_LOWER ) {
		dirs.push_back( Enemy::DIR_UPPER );
	}

	// �o�^�����������烉���_���őI��
	int num = rand( ) % dirs.size( );
	target_tile = checkStraight( enemy, x, y, dirs.at( num ) );

	return target_tile;
}

Floor::TILE EnemyManager::checkStraight( EnemyPtr enemy, int x, int y, Enemy::ENEMY_AISLE_DIR dir ) {
	Floor::TILE target_tile;
	int count = 2;
	Vector2 pos;
	int adjust_x;
	int adjust_y;

	while ( true ) {
		switch ( dir ) {
		case Enemy::DIR_LEFT:
			pos = Vector2 ( x + count, y );
			adjust_x = -1;
			adjust_y = 0;
			break;
		case Enemy::DIR_RIGHT:
			pos = Vector2 ( x - count, y );
			adjust_x = 1;
			adjust_y = 0;
			break;
		case Enemy::DIR_UPPER:
			pos = Vector2 ( x, y - count );
			adjust_x = 0;
			adjust_y = 1;
			break;
		case Enemy::DIR_LOWER:
			pos = Vector2 ( x, y + count );
			adjust_x = 0;
			adjust_y = -1;
			break;
		}

		// �L�������򂵂��ꍇ
		if ( _floor->getTile( ( int )pos.x, ( int )pos.y ).type == Floor::AISLE &&
			 isBranchAisle( dir, ( int )pos.x, ( int )pos.y ) == true ) {
			target_tile = _floor->getTile( ( int )pos.x, ( int )pos.y );
			enemy->setAisleDir( dir );
			return target_tile;
		}
		// �ǂɂԂ������ꍇ
		else if ( _floor->getTile( ( int )pos.x, ( int )pos.y ).type == Floor::WALL ) {
			target_tile = _floor->getTile( ( int )pos.x + adjust_x, ( int )pos.y + adjust_y );
			enemy->setAisleDir( dir );
			return target_tile;
		}
		// �����ɓ�������ꍇ
		else if ( _floor->getTile( ( int )pos.x, ( int )pos.y ).type == Floor::ROOM ) {
			target_tile = _floor->getTile( ( int )pos.x, ( int )pos.y );
			enemy->setAisleDir( Enemy::DIR_NONE );
			return target_tile;
		}
		count++;
	}
}

bool EnemyManager::isBranchAisle( Enemy::ENEMY_AISLE_DIR dir, int x, int y ) {
	switch ( dir ) {
	case Enemy::DIR_LEFT:
	case Enemy::DIR_RIGHT:
		if ( _floor->getTile( x, y - 1 ).type == Floor::AISLE ||
			 _floor->getTile( x, y + 1 ).type == Floor::AISLE ) {
			return true;
		}
		break;
	case Enemy::DIR_UPPER:
	case Enemy::DIR_LOWER:
		if ( _floor->getTile( x - 1, y ).type == Floor::AISLE ||
			 _floor->getTile( x + 1, y ).type == Floor::AISLE ) {
			return true;
		}
		break;
	}
	return false;
}

void EnemyManager::confuseMove( EnemyPtr enemy ) {
	Vector2 enemy_pos = enemy->getPos( );
	MOVE_DIR dir;
	bool flag = false;
	while ( flag != true ) {
		dir = MOVE_DIR( 1 + rand( ) % ( MAX_MOVE_DIR - 1 ) );
		switch( dir ) {
		case MOVE_DIR::LOWER_LEFT:
			if ( enemy->isNotCornerWall( enemy_pos ) == true ) {
				dicisionPos( enemy, enemy_pos, Vector2( enemy_pos.x + 1, enemy_pos.y + 1 ), dir, &flag );
			}
			break;
		case MOVE_DIR::LOWER:
			dicisionPos( enemy, enemy_pos, Vector2( enemy_pos.x, enemy_pos.y + 1 ), dir, &flag );
			break;
		case MOVE_DIR::LOWER_RIGHT:
			if ( enemy->isNotCornerWall( enemy_pos ) == true ) {
				dicisionPos( enemy, enemy_pos, Vector2( enemy_pos.x - 1, enemy_pos.y + 1 ), dir, &flag );
			}
			break;
		case MOVE_DIR::LEFT:
			dicisionPos( enemy, enemy_pos, Vector2( enemy_pos.x + 1, enemy_pos.y ), dir, &flag );
			break;
		case MOVE_DIR::RIGHT:
			dicisionPos( enemy, enemy_pos, Vector2( enemy_pos.x - 1, enemy_pos.y ), dir, &flag );
			break;
		case MOVE_DIR::UPPER_LEFT:
			if ( enemy->isNotCornerWall( enemy_pos ) == true ) {
				dicisionPos( enemy, enemy_pos, Vector2( enemy_pos.x + 1, enemy_pos.y - 1 ), dir, &flag );
			}
			break;
		case MOVE_DIR::UPPER:
			dicisionPos( enemy, enemy_pos, Vector2( enemy_pos.x, enemy_pos.y - 1 ), dir, &flag );
			break;
		case MOVE_DIR::UPPER_RIGHT:
			if ( enemy->isNotCornerWall( enemy_pos ) == true ) {
				dicisionPos( enemy, enemy_pos, Vector2( enemy_pos.x - 1, enemy_pos.y - 1 ), dir, &flag );
			}
			break;
		}

	}
}

void EnemyManager::confuseMoveBoss( ) {
	Vector2 enemy_pos = _enemy.at( 0 )->getPos( );
	MOVE_DIR dir;
	bool flag = false;
	while ( flag != true ) {
		dir = MOVE_DIR( 1 + rand( ) % ( MAX_MOVE_DIR - 1 ) );
		switch( dir ) {
		case MOVE_DIR::LOWER_LEFT:
			dicisionPosBoss( enemy_pos, Vector2( enemy_pos.x + 1, enemy_pos.y + 1 ), dir, &flag );
			break;
		case MOVE_DIR::LOWER:
			dicisionPosBoss( enemy_pos, Vector2( enemy_pos.x, enemy_pos.y + 1 ), dir, &flag );
			break;
		case MOVE_DIR::LOWER_RIGHT:
			dicisionPosBoss( enemy_pos, Vector2( enemy_pos.x - 1, enemy_pos.y + 1 ), dir, &flag );
			break;
		case MOVE_DIR::LEFT:
			dicisionPosBoss( enemy_pos, Vector2( enemy_pos.x + 1, enemy_pos.y ), dir, &flag );
			break;
		case MOVE_DIR::RIGHT:
			dicisionPosBoss( enemy_pos, Vector2( enemy_pos.x - 1, enemy_pos.y ), dir, &flag );
			break;
		case MOVE_DIR::UPPER_LEFT:
			dicisionPosBoss( enemy_pos, Vector2( enemy_pos.x + 1, enemy_pos.y - 1 ), dir, &flag );
			break;
		case MOVE_DIR::UPPER:
			dicisionPosBoss( enemy_pos, Vector2( enemy_pos.x, enemy_pos.y - 1 ), dir, &flag );
			break;
		case MOVE_DIR::UPPER_RIGHT:
			dicisionPosBoss(  enemy_pos, Vector2( enemy_pos.x - 1, enemy_pos.y - 1 ), dir, &flag );
			break;
		}

	}
}

void EnemyManager::dicisionPos( EnemyPtr enemy, Vector2 pre_pos, Vector2 pos, MOVE_DIR dir, bool* flag ) {
	if ( _floor->getTile( ( int )pos.x, ( int )pos.y ).bond == Floor::ENEMY ) {
		otherEnemy( enemy, &pos );
		*flag = true;
	}
	else if ( _floor->getTile( ( int )pos.x, ( int )pos.y ).type != Floor::WALL ) {
		_floor->setBondNone( ( int )pre_pos.x, ( int )pre_pos.y );
		enemy->setDir( dir );
		enemy->moveAnim( pos );
		*flag = true;
	}
}

void EnemyManager::dicisionPos( EnemyPtr enemy, Vector2 pre_pos, Vector2 pos, MOVE_DIR dir ) {
	if ( _floor->getTile( ( int )pos.x, ( int )pos.y ).bond == Floor::ENEMY ) {
		otherEnemy( enemy, &pos );
	}
	else if ( _floor->getTile( ( int )pos.x, ( int )pos.y ).type != Floor::WALL ) {
		_floor->setBondNone( ( int )pre_pos.x, ( int )pre_pos.y );
		enemy->setDir( dir );
		enemy->moveAnim( pos );
	}
}

void EnemyManager::dicisionMovePos( EnemyPtr enemy, int x, int y ) {
	Vector2 enemy_pos = enemy->getPos( );

	// x���W�������ꍇ
	if ( ( int )enemy_pos.x == x ) {
		// y���W��Player�ȉ��̎�
		if ( ( int )enemy_pos.y < y ) {
			dicisionPos( enemy, enemy->getPos( ), Vector2( enemy_pos.x, enemy_pos.y + 1 ), MOVE_DIR::LOWER );
		} else if ( ( int )enemy_pos.y > y ) { 
			dicisionPos( enemy, enemy->getPos( ), Vector2( enemy_pos.x, enemy_pos.y - 1 ), MOVE_DIR::UPPER );
		}
	}
	// x���W��enemy�ȏ�̎�
	else if ( ( int )enemy_pos.x < x ) {
		dicisionPos( enemy, enemy_pos, Vector2( enemy_pos.x + 1, enemy_pos.y ), MOVE_DIR::LEFT );
		// y���W��enemy�ȏ�̎�
		if ( ( int )enemy_pos.y < y ) {
			if (  _floor->getTile( ( int )enemy_pos.x + 1, ( int )enemy_pos.y ).type == Floor::WALL ) {
				dicisionPos( enemy, enemy->getPos( ), Vector2( enemy_pos.x, enemy_pos.y + 1 ), MOVE_DIR::LOWER );
			} else if ( _floor->getTile( ( int )enemy_pos.x, ( int )enemy_pos.y + 1 ).type != Floor::WALL && _floor->getTile( ( int )enemy_pos.x + 1, ( int )enemy_pos.y ).type != Floor::WALL ) {
				dicisionPos( enemy, enemy->getPos( ), Vector2( enemy_pos.x + 1, enemy_pos.y + 1 ), MOVE_DIR::LOWER_LEFT );
			}
		} else if ( ( int )enemy_pos.y > y ) {
			if (  _floor->getTile( ( int )enemy_pos.x + 1, ( int )enemy_pos.y ).type == Floor::WALL ) {
				dicisionPos( enemy, enemy->getPos( ), Vector2( enemy_pos.x, enemy_pos.y - 1 ), MOVE_DIR::UPPER );
			} else if ( _floor->getTile( ( int )enemy_pos.x, ( int )enemy_pos.y - 1 ).type != Floor::WALL && _floor->getTile( ( int )enemy_pos.x + 1, ( int )enemy_pos.y ).type != Floor::WALL ) {
				dicisionPos( enemy, enemy->getPos( ), Vector2( enemy_pos.x + 1, enemy_pos.y - 1 ), MOVE_DIR::UPPER_LEFT );
			}
		}
	}
	// x���W��Player�ȉ��̎�
	else if ( ( int )enemy_pos.x > x ) {
		dicisionPos( enemy, enemy_pos, Vector2( enemy_pos.x - 1, enemy_pos.y ), MOVE_DIR::RIGHT );
		// y���W��enemy�ȏ�̎�
		if ( ( int )enemy_pos.y < y ) {
			if (  _floor->getTile( ( int )enemy_pos.x - 1, ( int )enemy_pos.y ).type == Floor::WALL ) {
				dicisionPos( enemy, enemy->getPos( ), Vector2( enemy_pos.x, enemy_pos.y + 1 ), MOVE_DIR::LOWER );
			} else if ( _floor->getTile( ( int )enemy_pos.x, ( int )enemy_pos.y + 1 ).type != Floor::WALL && _floor->getTile( ( int )enemy_pos.x - 1, ( int )enemy_pos.y ).type != Floor::WALL ) {
				dicisionPos( enemy, enemy->getPos( ), Vector2( enemy_pos.x - 1, enemy_pos.y + 1 ), MOVE_DIR::LOWER_RIGHT );
			}
		} else if ( ( int )enemy_pos.y > y ) {
			if (  _floor->getTile( ( int )enemy_pos.x - 1, ( int )enemy_pos.y ).type == Floor::WALL ) {
				dicisionPos( enemy, enemy->getPos( ), Vector2( enemy_pos.x, enemy_pos.y - 1 ), MOVE_DIR::UPPER );
			} else if ( _floor->getTile( ( int )enemy_pos.x, ( int )enemy_pos.y - 1 ).type != Floor::WALL && _floor->getTile( ( int )enemy_pos.x - 1, ( int )enemy_pos.y ).type != Floor::WALL ) {
				dicisionPos( enemy, enemy->getPos( ), Vector2( enemy_pos.x - 1, enemy_pos.y - 1 ), MOVE_DIR::UPPER_RIGHT );
			}
		}
	}
}

void EnemyManager::dicisionPosBoss( Vector2 pre_pos, Vector2 pos, MOVE_DIR dir, bool* flag ) {
	if ( _floor->getTile( ( int )pos.x, ( int )pos.y ).type != Floor::WALL ) {
		setBondBossTile( true );
		_enemy.at( 0 )->setDir( dir );
		_enemy.at( 0 )->moveAnim( pos );
		*flag = true;
	}
}

void EnemyManager::dicisionPosBoss( Vector2 pre_pos, Vector2 pos, MOVE_DIR dir ) {
	if ( _floor->getTile( ( int )pos.x, ( int )pos.y ).type != Floor::WALL ) {
		setBondBossTile( true );
		_enemy.at( 0 )->setDir( dir );
		_enemy.at( 0 )->moveAnim( pos );
	}
}

void EnemyManager::dicisionMovePosBoss( int x, int y ) {
	Vector2 enemy_pos = _enemy.at( 0 )->getPos( );

	// x���W�������ꍇ
	if ( ( int )enemy_pos.x == x ) {
		// y���W��Player�ȉ��̎�
		if ( ( int )enemy_pos.y + 2 < y ) {
			dicisionPosBoss( _enemy.at( 0 )->getPos( ), Vector2( enemy_pos.x, enemy_pos.y + 1 ), MOVE_DIR::LOWER );
		} else if ( ( int )enemy_pos.y - 2 > y ) { 
			dicisionPosBoss( _enemy.at( 0 )->getPos( ), Vector2( enemy_pos.x, enemy_pos.y - 1 ), MOVE_DIR::UPPER );
		}
	}
	// x���W��enemy�ȏ�̎�
	else if ( ( int )enemy_pos.x + 2 < x ) {
		dicisionPosBoss( enemy_pos, Vector2( enemy_pos.x + 1, enemy_pos.y ), MOVE_DIR::LEFT );
		// y���W��enemy�ȏ�̎�
		if ( ( int )enemy_pos.y + 2 < y ) {
			if (  _floor->getTile( ( int )enemy_pos.x + 1, ( int )enemy_pos.y ).type == Floor::WALL ) {
				dicisionPosBoss( _enemy.at( 0 )->getPos( ), Vector2( enemy_pos.x, enemy_pos.y + 1 ), MOVE_DIR::LOWER );
			} else if ( _floor->getTile( ( int )enemy_pos.x, ( int )enemy_pos.y + 1 ).type != Floor::WALL && _floor->getTile( ( int )enemy_pos.x + 1, ( int )enemy_pos.y ).type != Floor::WALL ) {
				dicisionPosBoss( _enemy.at( 0 )->getPos( ), Vector2( enemy_pos.x + 1, enemy_pos.y + 1 ), MOVE_DIR::LOWER_LEFT );
			}
		} else if ( ( int )enemy_pos.y - 2 > y ) {
			if (  _floor->getTile( ( int )enemy_pos.x + 1, ( int )enemy_pos.y ).type == Floor::WALL ) {
				dicisionPosBoss( _enemy.at( 0 )->getPos( ), Vector2( enemy_pos.x, enemy_pos.y - 1 ), MOVE_DIR::UPPER );
			} else if ( _floor->getTile( ( int )enemy_pos.x, ( int )enemy_pos.y - 1 ).type != Floor::WALL && _floor->getTile( ( int )enemy_pos.x + 1, ( int )enemy_pos.y ).type != Floor::WALL ) {
				dicisionPosBoss( _enemy.at( 0 )->getPos( ), Vector2( enemy_pos.x + 1, enemy_pos.y - 1 ), MOVE_DIR::UPPER_LEFT );
			}
		}
	}
	// x���W��enemy�ȏ�̎�
	else if ( ( int )enemy_pos.x < x ) {
		// y���W��enemy�ȏ�̎�
		if ( ( int )enemy_pos.y + 2 < y ) {
			if (  _floor->getTile( ( int )enemy_pos.x + 1, ( int )enemy_pos.y ).type == Floor::WALL ) {
				dicisionPosBoss( _enemy.at( 0 )->getPos( ), Vector2( enemy_pos.x, enemy_pos.y + 1 ), MOVE_DIR::LOWER );
			} else if ( _floor->getTile( ( int )enemy_pos.x, ( int )enemy_pos.y + 1 ).type != Floor::WALL && _floor->getTile( ( int )enemy_pos.x + 1, ( int )enemy_pos.y ).type != Floor::WALL ) {
				dicisionPosBoss( _enemy.at( 0 )->getPos( ), Vector2( enemy_pos.x + 1, enemy_pos.y + 1 ), MOVE_DIR::LOWER_LEFT );
			}
		} else if ( ( int )enemy_pos.y - 2 > y ) {
			if (  _floor->getTile( ( int )enemy_pos.x + 1, ( int )enemy_pos.y ).type == Floor::WALL ) {
				dicisionPosBoss( _enemy.at( 0 )->getPos( ), Vector2( enemy_pos.x, enemy_pos.y - 1 ), MOVE_DIR::UPPER );
			} else if ( _floor->getTile( ( int )enemy_pos.x, ( int )enemy_pos.y - 1 ).type != Floor::WALL && _floor->getTile( ( int )enemy_pos.x + 1, ( int )enemy_pos.y ).type != Floor::WALL ) {
				dicisionPosBoss( _enemy.at( 0 )->getPos( ), Vector2( enemy_pos.x + 1, enemy_pos.y - 1 ), MOVE_DIR::UPPER_LEFT );
			}
		}
	}
	// x���W��Player�ȉ��̎�
	else if ( ( int )enemy_pos.x - 2 > x ) {
		dicisionPosBoss( enemy_pos, Vector2( enemy_pos.x - 1, enemy_pos.y ), MOVE_DIR::RIGHT );
		// y���W��enemy�ȏ�̎�
		if ( ( int )enemy_pos.y + 2 < y ) {
			if (  _floor->getTile( ( int )enemy_pos.x - 1, ( int )enemy_pos.y ).type == Floor::WALL ) {
				dicisionPosBoss( _enemy.at( 0 )->getPos( ), Vector2( enemy_pos.x, enemy_pos.y + 1 ), MOVE_DIR::LOWER );
			} else if ( _floor->getTile( ( int )enemy_pos.x, ( int )enemy_pos.y + 1 ).type != Floor::WALL && _floor->getTile( ( int )enemy_pos.x - 1, ( int )enemy_pos.y ).type != Floor::WALL ) {
				dicisionPosBoss( _enemy.at( 0 )->getPos( ), Vector2( enemy_pos.x - 1, enemy_pos.y + 1 ), MOVE_DIR::LOWER_RIGHT );
			}
		} else if ( ( int )enemy_pos.y + 2 > y ) {
			if (  _floor->getTile( ( int )enemy_pos.x - 1, ( int )enemy_pos.y ).type == Floor::WALL ) {
				dicisionPosBoss( _enemy.at( 0 )->getPos( ), Vector2( enemy_pos.x, enemy_pos.y - 1 ), MOVE_DIR::UPPER );
			} else if ( _floor->getTile( ( int )enemy_pos.x, ( int )enemy_pos.y - 1 ).type != Floor::WALL && _floor->getTile( ( int )enemy_pos.x - 1, ( int )enemy_pos.y ).type != Floor::WALL ) {
				dicisionPosBoss( _enemy.at( 0 )->getPos( ), Vector2( enemy_pos.x - 1, enemy_pos.y - 1 ), MOVE_DIR::UPPER_RIGHT );
			}
		}
	}
	// x���W��Player�ȉ��̎�
	else if ( ( int )enemy_pos.x > x ) {
		// y���W��enemy�ȏ�̎�
		if ( ( int )enemy_pos.y + 2 < y ) {
			if (  _floor->getTile( ( int )enemy_pos.x - 1, ( int )enemy_pos.y ).type == Floor::WALL ) {
				dicisionPosBoss( _enemy.at( 0 )->getPos( ), Vector2( enemy_pos.x, enemy_pos.y + 1 ), MOVE_DIR::LOWER );
			} else if ( _floor->getTile( ( int )enemy_pos.x, ( int )enemy_pos.y + 1 ).type != Floor::WALL && _floor->getTile( ( int )enemy_pos.x - 1, ( int )enemy_pos.y ).type != Floor::WALL ) {
				dicisionPosBoss( _enemy.at( 0 )->getPos( ), Vector2( enemy_pos.x - 1, enemy_pos.y + 1 ), MOVE_DIR::LOWER_RIGHT );
			}
		} else if ( ( int )enemy_pos.y + 2 > y ) {
			if (  _floor->getTile( ( int )enemy_pos.x - 1, ( int )enemy_pos.y ).type == Floor::WALL ) {
				dicisionPosBoss( _enemy.at( 0 )->getPos( ), Vector2( enemy_pos.x, enemy_pos.y - 1 ), MOVE_DIR::UPPER );
			} else if ( _floor->getTile( ( int )enemy_pos.x, ( int )enemy_pos.y - 1 ).type != Floor::WALL && _floor->getTile( ( int )enemy_pos.x - 1, ( int )enemy_pos.y ).type != Floor::WALL ) {
				dicisionPosBoss( _enemy.at( 0 )->getPos( ), Vector2( enemy_pos.x - 1, enemy_pos.y - 1 ), MOVE_DIR::UPPER_RIGHT );
			}
		}
	}
}

void EnemyManager::otherEnemy( EnemyPtr enemy, Vector2 *target_pos ) {
	Vector2 pos = *target_pos;
	// �ړ���ɃG�l�~�[�������ꍇ�ڂ̑O�̃G�l�~�[�̃^�[�Q�b�g�Ɠ����^�[�Q�b�g�ɂ���
	for ( unsigned int i = 0; i < _enemy.size( ); i++ ) {
		if ( pos.x == _enemy.at( i )->getPos( ).x && pos.y == _enemy.at( i )->getPos( ).y ) {
			//enemy->setTargetPos( ( int )_enemy.at( i )->getTargetPos( ).x, ( int )_enemy.at( i )->getTargetPos( ).y );
			//*target_pos = Vector2( ( _enemy.at( i )->getPos( ).x - enemy->getPos( ).x ) * - 1, ( _enemy.at( i )->getPos( ).y - enemy->getPos( ).y ) * - 1 );
			_enemy.at( i )->setTargetPos( ( int )enemy->getTargetPos( ).x, enemy->getTargetPos( ).y );
		}
	}
}

void EnemyManager::confuseAttack( EnemyPtr enemy ) {
	MOVE_DIR dir = MOVE_DIR( 1 + rand( ) % ( MAX_MOVE_DIR - 1 ) );
	enemy->setDir( dir );
	enemy->attackAnim( );
	switch( dir ) {
	case MOVE_DIR::LOWER_LEFT:
		if ( _floor->getTile( ( int )enemy->getPos( ).x + 1, ( int )enemy->getPos( ).y + 1 ).bond == Floor::PLAYER && enemy->isNotCornerWall( enemy->getPos( ) ) == true ) {
			_player->setDamage( enemy->getStatus( ).attack );
		}
		break;
	case MOVE_DIR::LOWER:
		if ( _floor->getTile( ( int )enemy->getPos( ).x, ( int )enemy->getPos( ).y + 1 ).bond == Floor::PLAYER ) {
			_player->setDamage( enemy->getStatus( ).attack );
		}
		break;
	case MOVE_DIR::LOWER_RIGHT:
		if ( _floor->getTile( ( int )enemy->getPos( ).x - 1, ( int )enemy->getPos( ).y + 1 ).bond == Floor::PLAYER && enemy->isNotCornerWall( enemy->getPos( ) ) == true ) {
			_player->setDamage( enemy->getStatus( ).attack );
		}
		break;
	case MOVE_DIR::LEFT:
		if ( _floor->getTile( ( int )enemy->getPos( ).x + 1, ( int )enemy->getPos( ).y ).bond == Floor::PLAYER ) {
			_player->setDamage( enemy->getStatus( ).attack );
		}
		break;
	case MOVE_DIR::RIGHT:
		if ( _floor->getTile( ( int )enemy->getPos( ).x - 1, ( int )enemy->getPos( ).y ).bond == Floor::PLAYER ) {
			_player->setDamage( enemy->getStatus( ).attack );
		}
		break;
	case MOVE_DIR::UPPER_LEFT:
		if ( _floor->getTile( ( int )enemy->getPos( ).x + 1, ( int )enemy->getPos( ).y - 1 ).bond == Floor::PLAYER && enemy->isNotCornerWall( enemy->getPos( ) ) == true ) {
			_player->setDamage( enemy->getStatus( ).attack );
		}
		break;
	case MOVE_DIR::UPPER:
		if ( _floor->getTile( ( int )enemy->getPos( ).x, ( int )enemy->getPos( ).y - 1 ).bond == Floor::PLAYER ) {
			_player->setDamage( enemy->getStatus( ).attack );
		}
		break;
	case MOVE_DIR::UPPER_RIGHT:
		if ( _floor->getTile( ( int )enemy->getPos( ).x - 1, ( int )enemy->getPos( ).y - 1 ).bond == Floor::PLAYER && enemy->isNotCornerWall( enemy->getPos( ) ) == true ) {
			_player->setDamage( enemy->getStatus( ).attack );
		}
		break;
	}
}

void EnemyManager::confuseAttackBoss( ) {
	MOVE_DIR dir = MOVE_DIR( 1 + rand( ) % ( MAX_MOVE_DIR - 1 ) );
	_enemy.at( 0 )->setDir( dir );
	_enemy.at( 0 )->attackAnim( );
	switch( dir ) {
	case MOVE_DIR::LOWER_LEFT:
		if ( _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x + 2, ( int )_enemy.at( 0 )->getPos( ).y + 2 ).bond == Floor::PLAYER ||
			 _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x + 2, ( int )_enemy.at( 0 )->getPos( ).y + 1 ).bond == Floor::PLAYER ||
			 _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x + 1, ( int )_enemy.at( 0 )->getPos( ).y + 2 ).bond == Floor::PLAYER ) {
			_player->setDamage( _enemy.at( 0 )->getStatus( ).attack );
		}
		break;
	case MOVE_DIR::LOWER:
		if ( _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x, ( int )_enemy.at( 0 )->getPos( ).y + 2 ).bond == Floor::PLAYER ||
			 _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x + 1, ( int )_enemy.at( 0 )->getPos( ).y + 2 ).bond == Floor::PLAYER ||
			 _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x - 1, ( int )_enemy.at( 0 )->getPos( ).y + 2 ).bond == Floor::PLAYER ) {
			_player->setDamage( _enemy.at( 0 )->getStatus( ).attack );
		}
		break;
	case MOVE_DIR::LOWER_RIGHT:
		if ( _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x - 2, ( int )_enemy.at( 0 )->getPos( ).y + 2 ).bond == Floor::PLAYER ||
			 _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x - 2, ( int )_enemy.at( 0 )->getPos( ).y + 1 ).bond == Floor::PLAYER ||
			 _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x - 1, ( int )_enemy.at( 0 )->getPos( ).y + 2 ).bond == Floor::PLAYER ) {
			_player->setDamage( _enemy.at( 0 )->getStatus( ).attack );
		}
		break;
	case MOVE_DIR::LEFT:
		if ( _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x + 2, ( int )_enemy.at( 0 )->getPos( ).y ).bond == Floor::PLAYER ||
			 _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x + 2, ( int )_enemy.at( 0 )->getPos( ).y + 1 ).bond == Floor::PLAYER ||
			 _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x + 2, ( int )_enemy.at( 0 )->getPos( ).y - 1 ).bond == Floor::PLAYER ) {
			_player->setDamage( _enemy.at( 0 )->getStatus( ).attack );
		}
		break;
	case MOVE_DIR::RIGHT:
		if ( _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x - 2, ( int )_enemy.at( 0 )->getPos( ).y ).bond == Floor::PLAYER ||
			 _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x - 2, ( int )_enemy.at( 0 )->getPos( ).y + 1 ).bond == Floor::PLAYER ||
			 _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x - 2, ( int )_enemy.at( 0 )->getPos( ).y - 1 ).bond == Floor::PLAYER ) {
			_player->setDamage( _enemy.at( 0 )->getStatus( ).attack );
		}
		break;
	case MOVE_DIR::UPPER_LEFT:
		if ( _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x + 2, ( int )_enemy.at( 0 )->getPos( ).y - 2 ).bond == Floor::PLAYER ||
			 _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x + 2, ( int )_enemy.at( 0 )->getPos( ).y - 1 ).bond == Floor::PLAYER ||
			 _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x + 1, ( int )_enemy.at( 0 )->getPos( ).y - 2 ).bond == Floor::PLAYER ) {
			_player->setDamage( _enemy.at( 0 )->getStatus( ).attack );
		}
		break;
	case MOVE_DIR::UPPER:
		if ( _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x, ( int )_enemy.at( 0 )->getPos( ).y - 2 ).bond == Floor::PLAYER ||
			 _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x + 1, ( int )_enemy.at( 0 )->getPos( ).y - 2 ).bond == Floor::PLAYER ||
			 _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x - 1, ( int )_enemy.at( 0 )->getPos( ).y - 2 ).bond == Floor::PLAYER ) {
			_player->setDamage( _enemy.at( 0 )->getStatus( ).attack );
		}
		break;
	case MOVE_DIR::UPPER_RIGHT:
		if ( _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x - 2, ( int )_enemy.at( 0 )->getPos( ).y - 2 ).bond == Floor::PLAYER ||
			 _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x - 2, ( int )_enemy.at( 0 )->getPos( ).y - 1 ).bond == Floor::PLAYER ||
			 _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x - 1, ( int )_enemy.at( 0 )->getPos( ).y - 2 ).bond == Floor::PLAYER ) {
			_player->setDamage( _enemy.at( 0 )->getStatus( ).attack );
		}
		break;
	}
}

void EnemyManager::attack( EnemyPtr enemy ) {
	FrameworkPtr fw  = Framework::getInstance( );
	SoundPtr sound   = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );

	sound->backgrondPlaySound( Sound::ATTACK );

	if ( _floor->getTile( ( int )enemy->getPos( ).x + 1, ( int )enemy->getPos( ).y ).bond == Floor::PLAYER ) {
		enemy->setDir( MOVE_DIR::LEFT );
	} else if ( _floor->getTile( ( int )enemy->getPos( ).x - 1, ( int )enemy->getPos( ).y ).bond == Floor::PLAYER ) {
		enemy->setDir( MOVE_DIR::RIGHT );
	} else if ( _floor->getTile( ( int )enemy->getPos( ).x, ( int )enemy->getPos( ).y + 1 ).bond == Floor::PLAYER ) {
		enemy->setDir( MOVE_DIR::LOWER );
	} else if ( _floor->getTile( ( int )enemy->getPos( ).x, ( int )enemy->getPos( ).y - 1 ).bond == Floor::PLAYER ) {
		enemy->setDir( MOVE_DIR::UPPER );
	} else if ( _floor->getTile( ( int )enemy->getPos( ).x + 1, ( int )enemy->getPos( ).y + 1 ).bond == Floor::PLAYER && enemy->isNotCornerWall( enemy->getPos( ) ) == true ) {
		enemy->setDir( MOVE_DIR::LOWER_LEFT );
	} else if ( _floor->getTile( ( int )enemy->getPos( ).x + 1, ( int )enemy->getPos( ).y - 1 ).bond == Floor::PLAYER && enemy->isNotCornerWall( enemy->getPos( ) ) == true ) {
		enemy->setDir( MOVE_DIR::UPPER_LEFT );
	} else if ( _floor->getTile( ( int )enemy->getPos( ).x - 1, ( int )enemy->getPos( ).y + 1 ).bond == Floor::PLAYER && enemy->isNotCornerWall( enemy->getPos( ) ) == true ) {
		enemy->setDir( MOVE_DIR::LOWER_RIGHT );
	} else if ( _floor->getTile( ( int )enemy->getPos( ).x - 1, ( int )enemy->getPos( ).y - 1 ).bond == Floor::PLAYER && enemy->isNotCornerWall( enemy->getPos( ) ) == true ) {
		enemy->setDir( MOVE_DIR::UPPER_RIGHT );
	}
	
	enemy->attackAnim( );
	// �X�L�����g�����ǂ������߂�
	int paralysis_num  = 20;
	int poison_num     = 20;
	int skill_seal_num = 20;
	int bind_tile_num  = 20;
	int slow_num       = 20;
	int confuse_num    = 20;
	int buff_num       = 20;

	int num = rand( ) % 100;
	if ( ( enemy->getType( ) == SILVER_OCTO_POT || enemy->getType( ) == GOLD_OCTO_POT ) && num < slow_num ) {    // �ǂ񂻂��U��
		_player->changeSpeedState( SLOW, EFFECT_PLAYER_NUM );
	}
	else if ( ( enemy->getType( ) == SILVER_OCTO_POT || enemy->getType( ) == GOLD_OCTO_POT ) && num < slow_num ) {    // �ǂ񂻂��U��
		_player->changeSpeedState( SLOW, EFFECT_PLAYER_NUM );
	}
	else if ( enemy->getType( ) == GREAT_OCTO_POT && num < buff_num &&
		_player->getStatus( ).buff != BUFF_STATE::DEBUFF ) {    // �f�o�t�U��
		_player->changeBuffState( DEBUFF, EFFECT_PLAYER_NUM );
	}
	else if ( enemy->getType( ) == GREAT_MINOTAUR && num < buff_num ) {    // �f�o�t�U��
		_player->changeBuffState( DEBUFF, enemy->getNumber( ) );
	}
	else if ( _player->getStatus( ).state == NORMAL_STATE && _player->isEquipmentRing4( ) == false ) {
		if ( enemy->getType( ) == SPIDER && num < paralysis_num ) {    // �}�q�U��
			_player->becomeAbnormalState( PARALYSIS, EFFECT_PLAYER_NUM );
		}
		else if ( enemy->getType( ) == GREAT_SPIDER && num < paralysis_num / 2 ) {	// �}�q�U��
			_player->becomeAbnormalState( PARALYSIS, EFFECT_PLAYER_NUM );
		} 
		else if ( enemy->getType( ) == GREAT_SPIDER && num < poison_num ) {	// �ōU��
			_player->becomeAbnormalState( POISON, EFFECT_PLAYER_NUM );
		}
		else if ( enemy->getType( ) == MINOTAUR && num < skill_seal_num / 2 ) {	// �Z����U��
			_player->becomeAbnormalState( SKILL_SEAL, EFFECT_PLAYER_NUM );
		}
		else if ( enemy->getType( ) == MINOTAUR && num < bind_tile_num ) {	  // �ړ��֎~�U��
			_player->becomeAbnormalState( BIND_TILE, EFFECT_PLAYER_NUM );
		} 
		else if ( enemy->getType( ) == GOCHIMPANZEE && num < confuse_num ) {	// �����U��
			_player->becomeAbnormalState( CONFUSE, EFFECT_PLAYER_NUM );
			_player->changeBuffState( BUFF, EFFECT_PLAYER_NUM );
		} 
		else {
			// �ʏ�_���[�W
			_player->setDamage( enemy->getStatus( ).attack );
		}
	}
	else {
		// �ʏ�_���[�W
		_player->setDamage( enemy->getStatus( ).attack );
	}
}

void EnemyManager::attackBoss( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	SoundPtr sound   = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );

	sound->backgrondPlaySound( Sound::ATTACK );

	if ( _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x + 2, ( int )_enemy.at( 0 )->getPos( ).y ).bond == Floor::PLAYER ||
		 _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x + 2, ( int )_enemy.at( 0 )->getPos( ).y + 1 ).bond == Floor::PLAYER ||
		 _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x + 2, ( int )_enemy.at( 0 )->getPos( ).y - 1 ).bond == Floor::PLAYER ) {
		_enemy.at( 0 )->setDir( MOVE_DIR::LEFT );
	} else if ( _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x - 2, ( int )_enemy.at( 0 )->getPos( ).y ).bond == Floor::PLAYER ||
				_floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x - 2, ( int )_enemy.at( 0 )->getPos( ).y + 1 ).bond == Floor::PLAYER ||
				_floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x - 2, ( int )_enemy.at( 0 )->getPos( ).y - 1 ).bond == Floor::PLAYER ) {
		_enemy.at( 0 )->setDir( MOVE_DIR::RIGHT );
	} else if ( _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x, ( int )_enemy.at( 0 )->getPos( ).y + 2 ).bond == Floor::PLAYER ||
				_floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x + 1, ( int )_enemy.at( 0 )->getPos( ).y + 2 ).bond == Floor::PLAYER ||
				_floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x - 1, ( int )_enemy.at( 0 )->getPos( ).y + 2 ).bond == Floor::PLAYER ) {
		_enemy.at( 0 )->setDir( MOVE_DIR::LOWER );
	} else if ( _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x, ( int )_enemy.at( 0 )->getPos( ).y - 2 ).bond == Floor::PLAYER ||
				_floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x + 1, ( int )_enemy.at( 0 )->getPos( ).y - 2 ).bond == Floor::PLAYER ||
				_floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x - 1, ( int )_enemy.at( 0 )->getPos( ).y - 2 ).bond == Floor::PLAYER ) {
		_enemy.at( 0 )->setDir( MOVE_DIR::UPPER );
	} else if ( _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x + 2, ( int )_enemy.at( 0 )->getPos( ).y + 2 ).bond == Floor::PLAYER ) {
		_enemy.at( 0 )->setDir( MOVE_DIR::LOWER_LEFT );
	} else if ( _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x + 2, ( int )_enemy.at( 0 )->getPos( ).y - 2 ).bond == Floor::PLAYER ) {
		_enemy.at( 0 )->setDir( MOVE_DIR::UPPER_LEFT );
	} else if ( _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x - 2, ( int )_enemy.at( 0 )->getPos( ).y + 2 ).bond == Floor::PLAYER ) {
		_enemy.at( 0 )->setDir( MOVE_DIR::LOWER_RIGHT );
	} else if ( _floor->getTile( ( int )_enemy.at( 0 )->getPos( ).x - 2, ( int )_enemy.at( 0 )->getPos( ).y - 2 ).bond == Floor::PLAYER ) {
		_enemy.at( 0 )->setDir( MOVE_DIR::UPPER_RIGHT );
	}
	
	_enemy.at( 0 )->attackAnim( );
	// �X�L�����g�����ǂ������߂�
	int skill_seal_num = 20;
	int buff_num       = 10;

	int num = rand( ) % 100;
	if ( num < buff_num ) {    // �f�o�t�U��
		if ( _player->getStatus( ).buff != BUFF_STATE::DEBUFF ) {
			_player->changeBuffState( DEBUFF, EFFECT_PLAYER_NUM );
		} else {
			_player->setDamage( _enemy.at( 0 )->getStatus( ).attack );
			_effect->playEffect( Effect::EFFECT_BOSS_ATTACK, _player->getDrawPos( ) + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), EFFECT_PLAYER_NUM );
		}
	} else if ( num < skill_seal_num ) {
		if ( _player->getStatus( ).state == NORMAL_STATE && _player->isEquipmentRing4( ) == false ) {	// �Z����U��
			_player->becomeAbnormalState( SKILL_SEAL, EFFECT_PLAYER_NUM );
		} else {
			_player->setDamage( _enemy.at( 0 )->getStatus( ).attack );
			_effect->playEffect( Effect::EFFECT_BOSS_ATTACK, _player->getDrawPos( ) + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), EFFECT_PLAYER_NUM );
		}
	} else {
		_player->setDamage( _enemy.at( 0 )->getStatus( ).attack );
		_effect->playEffect( Effect::EFFECT_BOSS_ATTACK, _player->getDrawPos( ) + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), EFFECT_PLAYER_NUM );
	}
}

void EnemyManager::selectDamagedEnemy( ) {
	// �U�����ꂽ���ǂ���
	if ( _player->isAttack( ) == true ) {
		for ( unsigned int i = 0; i < _enemy.size( ); i++ ) {
			// �U�����ꂽ�G�l�~�[��I�o
			if ( isHitPlayerAttack( ( int )_enemy.at( i )->getPos( ).x, ( int )_enemy.at( i )->getPos( ).y ) == true &&
				 _enemy.at( i )->isDead( ) == false ) {
				// �_���[�W��ݒ�
				_enemy.at( i )->damage( _player->getStatus( ).attack, false, _player->isEquipmentAttackItem( ), false );
				// ���b�Z�[�W��\��
				_message->createFont( _enemy.at( i )->getName( ), "", "", _enemy.at( i )->getDamage( ), MessageLog::DAMAGE );
				if ( _player->isEquipmentSword4( ) == true ) {
					triSwordAbnormal( _enemy.at( i ) );
				}
			}
		}
	}
	// ���@�U�����ꂽ���ǂ���
	if ( _player->isSkillAttack( ) == true ) {
		for ( unsigned int i = 0; i < _enemy.size( ); i++ ) {
			// �U�����ꂽ�G�l�~�[��I�o
			if ( _player->isZanmetuHitEnemy( ) == true ) {
				// �U�����ꂽ�G�l�~�[��I�o
				if ( _enemy.at( i )->getPos( ).x == _player->getHitEnemyPos( ).x &&
					 _enemy.at( i )->getPos( ).y == _player->getHitEnemyPos( ).y &&
					 _enemy.at( i )->isDead( ) == false ) {
					// �_���[�W��ݒ�
					_enemy.at( i )->damage( _player->getSkillAttackDamage( ), true, false, false );
					_player->setZanmetuHitEnemy( false );
					// ���b�Z�[�W��\��
					_message->createFont( _enemy.at( i )->getName( ), "", "", _enemy.at( i )->getDamage( ), MessageLog::DAMAGE );
				}
			} 
			else {
				if ( isHitPlayerAttack( ( int )_enemy.at( i )->getPos( ).x, ( int )_enemy.at( i )->getPos( ).y ) == true &&
					 _enemy.at( i )->isDead( ) == false ) {
					if ( _player->isUseMateriaSword( ) == true ) {
						// �_���[�W��ݒ�
						_enemy.at( i )->damage( _player->getSkillAttackDamage( ), true, false, false );
						// ���b�Z�[�W��\��
						_message->createFont( _enemy.at( i )->getName( ), "", "", _enemy.at( i )->getDamage( ), MessageLog::DAMAGE );
						_effect->playEffect( Effect::EFFECT_SKILL3, _enemy.at( i )->getDrawPos( ) + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), _enemy.at( i )->getNumber( ) );
						_player->materiaAbsorption( _enemy.at( i )->getDamage( ) );
						_player->setUseMateria( false );
					} else {
						// �_���[�W��ݒ�
						_enemy.at( i )->damage( _player->getSkillAttackDamage( ), true, false, true );
						// ���b�Z�[�W��\��
						_message->createFont( _enemy.at( i )->getName( ), "", "", _enemy.at( i )->getDamage( ), MessageLog::DAMAGE );
					}
				}
			}
		}
	}
}

void EnemyManager::damagedBoss( ) {
	// �U�����ꂽ���ǂ���
	if ( _player->isAttack( ) == true ) {
		// �U�����ꂽ�G�l�~�[��I�o
		if ( isHitPlayerAttackBoss( ( int )_enemy.at( 0 )->getPos( ).x, ( int )_enemy.at( 0 )->getPos( ).y ) == true &&
				_enemy.at( 0 )->isDead( ) == false ) {
			// �_���[�W��ݒ�
			_enemy.at( 0 )->damage( _player->getStatus( ).attack, false, _player->isEquipmentAttackItem( ), false );
			// ���b�Z�[�W��\��
			_message->createFont( _enemy.at( 0 )->getName( ), "", "", _enemy.at( 0 )->getDamage( ), MessageLog::DAMAGE );
			if ( _player->isEquipmentSword4( ) == true ) {
				triSwordAbnormal( _enemy.at( 0 ) );
			}
		}
	}
	// ���@�U�����ꂽ���ǂ���
	if ( _player->isSkillAttack( ) == true ) {
		// �U�����ꂽ�G�l�~�[��I�o
		if ( _player->isZanmetuHitEnemy( ) == true ) {
			// �U�����ꂽ�G�l�~�[��I�o
			if ( _enemy.at( 0 )->getPos( ).x - 1 <= _player->getHitEnemyPos( ).x && _enemy.at( 0 )->getPos( ).x + 1 >= _player->getHitEnemyPos( ).x &&
				 _enemy.at( 0 )->getPos( ).y - 1 <= _player->getHitEnemyPos( ).y && _enemy.at( 0 )->getPos( ).y + 1 <= _player->getHitEnemyPos( ).y &&
				 _enemy.at( 0 )->isDead( ) == false ) {
				// �_���[�W��ݒ�
				_enemy.at( 0 )->damage( _player->getSkillAttackDamage( ), true, false, false );
				_player->setZanmetuHitEnemy( false );
				// ���b�Z�[�W��\��
				_message->createFont( _enemy.at( 0 )->getName( ), "", "", _enemy.at( 0 )->getDamage( ), MessageLog::DAMAGE );
			}
		} 
		else {
			if ( isHitPlayerAttackBoss( ( int )_enemy.at( 0 )->getPos( ).x, ( int )_enemy.at( 0 )->getPos( ).y ) == true &&
					_enemy.at( 0 )->isDead( ) == false ) {
				if ( _player->isUseMateriaSword( ) == true ) {
					// �_���[�W��ݒ�
					_enemy.at( 0 )->damage( _player->getSkillAttackDamage( ), true, false, false );
					// ���b�Z�[�W��\��
					_message->createFont( _enemy.at( 0 )->getName( ), "", "", _enemy.at( 0 )->getDamage( ), MessageLog::DAMAGE );
					_effect->playEffect( Effect::EFFECT_SKILL3, _enemy.at( 0 )->getDrawPos( ) + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), _enemy.at( 0 )->getNumber( ) );
					_player->materiaAbsorption( _enemy.at( 0 )->getDamage( ) );
					_player->setUseMateria( false );
				} else {
					// �_���[�W��ݒ�
					_enemy.at( 0 )->damage( _player->getSkillAttackDamage( ), true, false, true );
					// ���b�Z�[�W��\��
					_message->createFont( _enemy.at( 0 )->getName( ), "", "", _enemy.at( 0 )->getDamage( ), MessageLog::DAMAGE );
				}
			}
		}
	}
}

void EnemyManager::triSwordAbnormal( EnemyPtr enemy ) {
	// ��Ԉُ�ɂȂ�m����ݒ�
	int poison    = 10;
	int paralysis = 20;
	int confuse   = 30;

	int num = rand( ) % 100;

	if ( num < poison ) {
		enemy->becomeAbnormalState( STATE::POISON, enemy->getNumber( ) );
	} else if ( num < paralysis ) {
		enemy->becomeAbnormalState( STATE::PARALYSIS, enemy->getNumber( ) );
	} else if ( num < confuse ) {
		enemy->becomeAbnormalState( STATE::CONFUSE, enemy->getNumber( ) );
	}
}

void EnemyManager::itemDamage( ) {
	FrameworkPtr fw = Framework::getInstance( );
	SoundPtr sound = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );

	// �A�C�e���������������ǂ���
	if ( _item->isHitEnemy( ) == true ) {
		for ( unsigned int i = 0; i < _enemy.size( ); i++ ) {
			// �U�����ꂽ�G�l�~�[��I�o
			if ( _enemy.at( i )->getPos( ).x == _item->getHitEnemyPos( ).x &&
				 _enemy.at( i )->getPos( ).y == _item->getHitEnemyPos( ).y  ) {
				if ( _item->getHitEnemyType( ) == ITEM_ID::HERB5 ) {  // �Ȃ��葐
					_enemy.at( i )->refreshState( );
				} else if ( _item->getHitEnemyType( ) == ITEM_ID::HERB6 || _item->getHitEnemyType( ) == ITEM_ID::ROD4 ) {  // ���[�v�n
					_enemy.at( i )->warpStart( _enemy.at( i )->getNumber( ) );
				} else if ( _item->getHitEnemyType( ) == ITEM_ID::HERB7 ) {  // �ő�
					_enemy.at( i )->becomeAbnormalState( STATE::POISON, _enemy.at( i )->getNumber( ) );
				} else if ( _item->getHitEnemyType( ) == ITEM_ID::HERB8 ) {  // ���тꑐ
					_enemy.at( i )->becomeAbnormalState( STATE::PARALYSIS, _enemy.at( i )->getNumber( ) );
				} else if ( _item->getHitEnemyType( ) == ITEM_ID::HERB9 ) {  // ���f��
					_enemy.at( i )->becomeAbnormalState( STATE::CONFUSE, _enemy.at( i )->getNumber( ) );
				} else {
					// �_���[�W��ݒ�
					_enemy.at( i )->itemDamage( _item->getItemDamage( ) );
					if ( _item->getItemDamage( ) > 0 ) {
						// ���b�Z�[�W��\��
						_message->createFont( _enemy.at( i )->getName( ), "", "", _item->getItemDamage( ), MessageLog::DAMAGE );
						sound->backgrondPlaySound( Sound::ATTACK );
					} else {
						sound->backgrondPlaySound( Sound::CURE );
						_message->createFont( _enemy.at( i )->getName( ), "", "", _item->getItemDamage( ), MessageLog::HEAL );
						_effect->playEffect( Effect::EFFECT_HEAL, _enemy.at( i )->getDrawPos( ) + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), _enemy.at( i )->getNumber( ) );
					}
				}
				_item->setHitEnemy( false );
				_item->setInitHitEnemyPos( );
			}
		}
	}
}

void EnemyManager::itemDamageBoss( ) {
	FrameworkPtr fw = Framework::getInstance( );
	SoundPtr sound  = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );

	// �A�C�e���������������ǂ���
	if ( _item->isHitEnemy( ) == true ) {
		// �U�����ꂽ�G�l�~�[��I�o
		if ( _enemy.at( 0 )->getPos( ).x <= _item->getHitEnemyPos( ).x + 1 && _enemy.at( 0 )->getPos( ).x >= _item->getHitEnemyPos( ).x - 1 &&
			 _enemy.at( 0 )->getPos( ).y <= _item->getHitEnemyPos( ).y + 1 && _enemy.at( 0 )->getPos( ).y >= _item->getHitEnemyPos( ).y - 1 ) {
			if ( _item->getHitEnemyType( ) == ITEM_ID::HERB5 ) {  // �Ȃ��葐
				_enemy.at( 0 )->refreshState( );
			} else if ( _item->getHitEnemyType( ) == ITEM_ID::HERB6 || _item->getHitEnemyType( ) == ITEM_ID::ROD4 ) {  // ���[�v�n
				_enemy.at( 0 )->warpStart( _enemy.at( 0 )->getNumber( ) );
			} else if ( _item->getHitEnemyType( ) == ITEM_ID::HERB7 ) {  // �ő�
				_enemy.at( 0 )->becomeAbnormalState( STATE::POISON, _enemy.at( 0 )->getNumber( ) );
			} else if ( _item->getHitEnemyType( ) == ITEM_ID::HERB8 ) {  // ���тꑐ
				_enemy.at( 0 )->becomeAbnormalState( STATE::PARALYSIS, _enemy.at( 0 )->getNumber( ) );
			} else if ( _item->getHitEnemyType( ) == ITEM_ID::HERB9 ) {  // ���f��
				_enemy.at( 0 )->becomeAbnormalState( STATE::CONFUSE, _enemy.at( 0 )->getNumber( ) );
			} else {
				// �_���[�W��ݒ�
				_enemy.at( 0 )->itemDamage( _item->getItemDamage( ) );
				if ( _item->getItemDamage( ) > 0 ) {
					// ���b�Z�[�W��\��
					_message->createFont( _enemy.at( 0 )->getName( ), "", "", _item->getItemDamage( ), MessageLog::DAMAGE );
					sound->backgrondPlaySound( Sound::ATTACK );
				} else {
					sound->backgrondPlaySound( Sound::CURE );
					_message->createFont( _enemy.at( 0 )->getName( ), "", "", _item->getItemDamage( ), MessageLog::HEAL );
					_effect->playEffect( Effect::EFFECT_HEAL, _enemy.at( 0 )->getDrawPos( ) + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), _enemy.at( 0 )->getNumber( ) );
				}
			}
			_item->setHitEnemy( false );
			_item->setInitHitEnemyPos( );
		}
	}
}

void EnemyManager::rodDamage( ) {
	// ���̏���g�������ǂ���
	if ( _item->isUseFlameRod( ) == true ) {
		for ( unsigned int i = 0; i < _enemy.size( ); i++ ) {
			// �U�����ꂽ�G�l�~�[��I�o
			if ( _enemy.at( i )->getPos( ).x == _item->getHitEnemyPos( ).x &&
				 _enemy.at( i )->getPos( ).y == _item->getHitEnemyPos( ).y  ) {
				// �_���[�W��ݒ�
				_effect->playEffect( Effect::EFFECT_FLAME, _enemy.at( i )->getDrawPos( ) + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), _enemy.at( i )->getNumber( ) );
				_enemy.at( i )->itemDamage( _item->getItemDamage( ) );
				_item->setHitEnemy( false );
				_item->setInitHitEnemyPos( );
				if ( _item->getItemDamage( ) > 0 ) {
					// ���b�Z�[�W��\��
					_message->createFont( _enemy.at( i )->getName( ), "", "", _item->getItemDamage( ), MessageLog::DAMAGE );
				}
				_item->setTurnEnd( true );
			}
		}
		_item->setUseFlameRod( false );
	}
	// �����̏���g�������ǂ���
	if ( _item->isUseSuperFlameRod( ) == true && _use_flame_rod == false ) {
		for ( unsigned int i = 0; i < _enemy.size( ); i++ ) {
			if ( _floor->getPlayerTile( ).type == Floor::ROOM ) {
				if ( _floor->getPlayerTile( ).room == _enemy.at( i )->getRoomNum( ) ) {
					// �������̑S�G�l�~�[�Ƀ_���[�W
					_enemy.at( i )->itemDamage( _item->getItemDamage( ) );
				}
			} else if ( _floor->getPlayerTile( ).type == Floor::AISLE ) {
				if ( _enemy.at( i )->getPos( ).x > _floor->getPlayerTile( ).x - AISLE_FLAME_LOD_DIS &&
					 _enemy.at( i )->getPos( ).x < _floor->getPlayerTile( ).x + AISLE_FLAME_LOD_DIS &&
					 _enemy.at( i )->getPos( ).y > _floor->getPlayerTile( ).y - AISLE_FLAME_LOD_DIS &&
					 _enemy.at( i )->getPos( ).y < _floor->getPlayerTile( ).y + AISLE_FLAME_LOD_DIS ) {
					// �͈͓��̑S�G�l�~�[�Ƀ_���[�W
					_enemy.at( i )->itemDamage( _item->getItemDamage( ) );
				}
			} 
		}
		_message->createFont( "�������̂��ׂĂ̓G", "", "", _item->getItemDamage( ), MessageLog::DAMAGE );
		_use_flame_rod = true;
		_item->setUseSuperFlameRod( false );
	}

	// ���[�v�̏���g�������ǂ���
	if ( _item->isUseWarpRod( ) == true ) {
		for ( unsigned int i = 0; i < _enemy.size( ); i++ ) {
			// �U�����ꂽ�G�l�~�[��I�o
			if ( _enemy.at( i )->getPos( ).x == _item->getHitEnemyPos( ).x &&
				 _enemy.at( i )->getPos( ).y == _item->getHitEnemyPos( ).y  ) {
				_floor->setBondNone( ( int )_enemy.at( i )->getPos( ).x, ( int )_enemy.at( i )->getPos( ).y );
				_enemy.at( i )->warpStart( _enemy.at( i )->getNumber( ) );
				_item->setHitEnemy( false );
				_item->setInitHitEnemyPos( );
				_item->setTurnEnd( true );
			}
		}
		_item->setUseWarpRod( false );
	}
}

void EnemyManager::rodDamageBoss( ) {
	// ���̏���g�������ǂ���
	if ( _item->isUseFlameRod( ) == true ) {
		// �U�����ꂽ�G�l�~�[��I�o
		if ( _enemy.at( 0 )->getPos( ).x <= _item->getHitEnemyPos( ).x + 1 && _enemy.at( 0 )->getPos( ).x >= _item->getHitEnemyPos( ).x - 1 &&
			 _enemy.at( 0 )->getPos( ).y <= _item->getHitEnemyPos( ).y + 1 && _enemy.at( 0 )->getPos( ).y >= _item->getHitEnemyPos( ).y - 1 ) {
			// �_���[�W��ݒ�
			_effect->playEffect( Effect::EFFECT_FLAME, _enemy.at( 0 )->getDrawPos( ) + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), _enemy.at( 0 )->getNumber( ) );
			_enemy.at( 0 )->itemDamage( _item->getItemDamage( ) );
			_item->setHitEnemy( false );
			_item->setInitHitEnemyPos( );
			if ( _item->getItemDamage( ) > 0 ) {
				// ���b�Z�[�W��\��
				_message->createFont( _enemy.at( 0 )->getName( ), "", "", _item->getItemDamage( ), MessageLog::DAMAGE );
			}
			_item->setTurnEnd( true );
		}
		_item->setUseFlameRod( false );
	}
	// �����̏���g�������ǂ���
	if ( _item->isUseSuperFlameRod( ) == true && _use_flame_rod == false ) {
		if ( _floor->getPlayerTile( ).type == Floor::ROOM ) {
			if ( _floor->getPlayerTile( ).room == _enemy.at( 0 )->getRoomNum( ) ) {
				// �������̑S�G�l�~�[�Ƀ_���[�W
				_enemy.at( 0 )->itemDamage( _item->getItemDamage( ) );
			}
		} else if ( _floor->getPlayerTile( ).type == Floor::AISLE ) {
			if ( _enemy.at( 0 )->getPos( ).x > _floor->getPlayerTile( ).x - AISLE_FLAME_LOD_DIS &&
					_enemy.at( 0 )->getPos( ).x < _floor->getPlayerTile( ).x + AISLE_FLAME_LOD_DIS &&
					_enemy.at( 0 )->getPos( ).y > _floor->getPlayerTile( ).y - AISLE_FLAME_LOD_DIS &&
					_enemy.at( 0 )->getPos( ).y < _floor->getPlayerTile( ).y + AISLE_FLAME_LOD_DIS ) {
				// �͈͓��̑S�G�l�~�[�Ƀ_���[�W
				_enemy.at( 0 )->itemDamage( _item->getItemDamage( ) );
			}
		} 
		_message->createFont( "�������̂��ׂĂ̓G", "", "", _item->getItemDamage( ), MessageLog::DAMAGE );
		_use_flame_rod = true;
		_item->setUseSuperFlameRod( false );
	}

	// ���[�v�̏���g�������ǂ���
	if ( _item->isUseWarpRod( ) == true ) {
		// �U�����ꂽ�G�l�~�[��I�o
		if ( _enemy.at( 0 )->getPos( ).x <= _item->getHitEnemyPos( ).x + 1 && _enemy.at( 0 )->getPos( ).x >= _item->getHitEnemyPos( ).x - 1 &&
			 _enemy.at( 0 )->getPos( ).y <= _item->getHitEnemyPos( ).y + 1 && _enemy.at( 0 )->getPos( ).y >= _item->getHitEnemyPos( ).y - 1 ) {
			for ( int i = - 1; i <= 1; i++ ) {
				for ( int j = - 1; j <= 1; j++ ) {
					_floor->setBondNone( ( int )_enemy.at( 0 )->getPos( ).x + i, ( int )_enemy.at( 0 )->getPos( ).y + j );
				}
			}
			_enemy.at( 0 )->warpStart( _enemy.at( 0 )->getNumber( ) );
			_item->setHitEnemy( false );
			_item->setInitHitEnemyPos( );
			_item->setTurnEnd( true );
		}
		_item->setUseWarpRod( false );
	}
}

bool EnemyManager::isHitPlayerAttack( int x, int y ) {
	// �E
	if ( _floor->getTile( x - 1, y ).bond == Floor::PLAYER && _player->getStatus( ).dir == MOVE_DIR::LEFT ) {
		return true;
	}
	// ��
	if ( _floor->getTile( x + 1, y ).bond == Floor::PLAYER && _player->getStatus( ).dir == MOVE_DIR::RIGHT ) {
		return true;
	}
	// ��
	if ( _floor->getTile( x, y - 1 ).bond == Floor::PLAYER && _player->getStatus( ).dir == MOVE_DIR::LOWER ) {
		return true;
	}
	// ��
	if ( _floor->getTile( x, y + 1 ).bond == Floor::PLAYER && _player->getStatus( ).dir == MOVE_DIR::UPPER ) {
		return true;
	}
	// �E��
	if ( _floor->getTile( x - 1, y - 1 ).bond == Floor::PLAYER && _player->getStatus( ).dir == MOVE_DIR::LOWER_LEFT ) {
		return true;
	}
	// �E��
	if ( _floor->getTile( x - 1, y + 1 ).bond == Floor::PLAYER && _player->getStatus( ).dir == MOVE_DIR::UPPER_LEFT ) {
		return true;
	}
	// ����
	if ( _floor->getTile( x + 1, y - 1 ).bond == Floor::PLAYER && _player->getStatus( ).dir == MOVE_DIR::LOWER_RIGHT ) {
		return true;
	}
	// ����
	if ( _floor->getTile( x + 1, y + 1 ).bond == Floor::PLAYER && _player->getStatus( ).dir == MOVE_DIR::UPPER_RIGHT ) {
		return true;
	}
	return false;
}

bool EnemyManager::isHitPlayerAttackBoss( int x, int y ) {
	// �E
	if ( _player->getStatus( ).dir == MOVE_DIR::RIGHT &&
		 ( _floor->getTile( x + 2, y ).bond == Floor::PLAYER ||
		   _floor->getTile( x + 2, y + 1 ).bond == Floor::PLAYER ||
		   _floor->getTile( x + 2, y - 1 ).bond == Floor::PLAYER ) ) {
		return true;
	}
	// ��
	if ( _player->getStatus( ).dir == MOVE_DIR::LEFT &&
		 ( _floor->getTile( x - 2, y ).bond == Floor::PLAYER ||
		   _floor->getTile( x - 2, y + 1 ).bond == Floor::PLAYER ||
		   _floor->getTile( x - 2, y - 1 ).bond == Floor::PLAYER ) ) {
		return true;
	}
	// ��
	if ( _player->getStatus( ).dir == MOVE_DIR::LOWER &&
		 ( _floor->getTile( x, y - 2 ).bond == Floor::PLAYER ||
		   _floor->getTile( x + 1, y - 2 ).bond == Floor::PLAYER ||
		   _floor->getTile( x - 1, y - 2 ).bond == Floor::PLAYER ) ) {
		return true;
	}
	// ��
	if ( _player->getStatus( ).dir == MOVE_DIR::UPPER &&
		 ( _floor->getTile( x, y + 2 ).bond == Floor::PLAYER ||
		   _floor->getTile( x + 1, y + 2 ).bond == Floor::PLAYER ||
		   _floor->getTile( x - 1, y + 2 ).bond == Floor::PLAYER ) ) {
		return true;
	}
	// �E��
	if ( _player->getStatus( ).dir == MOVE_DIR::LOWER_RIGHT &&
		 ( _floor->getTile( x + 2, y - 2 ).bond == Floor::PLAYER ||
		   _floor->getTile( x + 1, y - 2 ).bond == Floor::PLAYER ||
		   _floor->getTile( x, y - 2 ).bond == Floor::PLAYER ||
		   _floor->getTile( x + 2, y - 1 ).bond == Floor::PLAYER ||
		   _floor->getTile( x + 2, y ).bond == Floor::PLAYER ) ) {
		return true;
	}
	// �E��
	if ( _player->getStatus( ).dir == MOVE_DIR::UPPER_RIGHT &&
		 ( _floor->getTile( x + 2, y + 2 ).bond == Floor::PLAYER ||
		   _floor->getTile( x + 1, y + 2 ).bond == Floor::PLAYER ||
		   _floor->getTile( x, y + 2 ).bond == Floor::PLAYER ||
		   _floor->getTile( x + 2, y + 1 ).bond == Floor::PLAYER ||
		   _floor->getTile( x + 2, y ).bond == Floor::PLAYER ) ) {
		return true;
	}
	// ����
	if ( _player->getStatus( ).dir == MOVE_DIR::LOWER_LEFT &&
		 ( _floor->getTile( x - 2, y - 2 ).bond == Floor::PLAYER ||
		   _floor->getTile( x - 1, y - 2 ).bond == Floor::PLAYER ||
		   _floor->getTile( x, y - 2 ).bond == Floor::PLAYER ||
		   _floor->getTile( x - 2, y - 1 ).bond == Floor::PLAYER ||
		   _floor->getTile( x - 2, y ).bond == Floor::PLAYER ) ) {
		return true;
	}
	// ����
	if ( _player->getStatus( ).dir == MOVE_DIR::UPPER_LEFT &&
		 ( _floor->getTile( x - 2, y + 2 ).bond == Floor::PLAYER ||
		   _floor->getTile( x - 1, y + 2 ).bond == Floor::PLAYER ||
		   _floor->getTile( x, y + 2 ).bond == Floor::PLAYER ||
		   _floor->getTile( x - 2, y + 1 ).bond == Floor::PLAYER ||
		   _floor->getTile( x - 2, y ).bond == Floor::PLAYER ) ) {
		return true;
	}
	return false;
}

bool EnemyManager::isNextToPlayer( int x, int y ) {
	// �E
	if ( _floor->getTile( x - 1, y ).bond == Floor::PLAYER ) {
		return true;
	}
	// ��
	if ( _floor->getTile( x + 1, y ).bond == Floor::PLAYER ) {
		return true;
	}
	// ��
	if ( _floor->getTile( x, y + 1 ).bond == Floor::PLAYER ) {
		return true;
	}
	// ��
	if ( _floor->getTile( x, y - 1 ).bond == Floor::PLAYER ) {
		return true;
	}
	// �E��
	if ( _floor->getTile( x - 1, y + 1 ).bond == Floor::PLAYER &&
		 _floor->getTile( x - 1, y ).type != Floor::WALL &&
		 _floor->getTile( x, y + 1 ).type != Floor::WALL ) {
		return true;
	}
	// �E��
	if ( _floor->getTile( x - 1, y - 1 ).bond == Floor::PLAYER &&
		 _floor->getTile( x - 1, y ).type != Floor::WALL &&
		 _floor->getTile( x, y - 1 ).type != Floor::WALL ) {
		return true;
	}
	// ����
	if ( _floor->getTile( x + 1, y + 1 ).bond == Floor::PLAYER &&
		 _floor->getTile( x + 1, y ).type != Floor::WALL &&
		 _floor->getTile( x, y + 1 ).type != Floor::WALL ) {
		return true;
	}
	// ����
	if ( _floor->getTile( x + 1, y - 1 ).bond == Floor::PLAYER &&
		 _floor->getTile( x + 1, y ).type != Floor::WALL &&
		 _floor->getTile( x, y - 1 ).type != Floor::WALL ) {
		return true;
	}
	return false;
}

bool EnemyManager::isNextToPlayerBoss( int x, int y ) {
	// �E
	if ( _floor->getTile( x - 2, y ).bond == Floor::PLAYER ||
		 _floor->getTile( x - 2, y + 1 ).bond == Floor::PLAYER ||
		 _floor->getTile( x - 2, y - 1 ).bond == Floor::PLAYER ) {
		return true;
	}
	// ��
	if ( _floor->getTile( x + 2, y ).bond == Floor::PLAYER ||
		 _floor->getTile( x + 2, y + 1 ).bond == Floor::PLAYER ||
		 _floor->getTile( x + 2, y - 1 ).bond == Floor::PLAYER ) {
		return true;
	}
	// ��
	if ( _floor->getTile( x, y + 2 ).bond == Floor::PLAYER ||
		 _floor->getTile( x + 1, y + 2 ).bond == Floor::PLAYER ||
		 _floor->getTile( x - 1, y + 2 ).bond == Floor::PLAYER ) {
		return true;
	}
	// ��
	if ( _floor->getTile( x, y - 2 ).bond == Floor::PLAYER ||
		 _floor->getTile( x + 1, y - 2 ).bond == Floor::PLAYER ||
		 _floor->getTile( x - 1, y - 2 ).bond == Floor::PLAYER ) {
		return true;
	}
	// �E��
	if ( _floor->getTile( x - 2, y + 2 ).bond == Floor::PLAYER ) {
		return true;
	}
	// �E��
	if ( _floor->getTile( x - 2, y - 2 ).bond == Floor::PLAYER ) {
		return true;
	}
	// ����
	if ( _floor->getTile( x + 2, y + 2 ).bond == Floor::PLAYER ) {
		return true;
	}
	// ����
	if ( _floor->getTile( x + 2, y - 2 ).bond == Floor::PLAYER ) {
		return true;
	}
	return false;
}

void EnemyManager::enemyDead( ) {
	int get_exp = 0;
	int get_alchemy_point = 0;
	// ���S�����G�l�~�[��I�o
	for ( unsigned int i = 0; i < _enemy.size( ); i++ ) {
		if ( _enemy.at( i )->getStatus( ).life <= 0 ) {
			if ( _enemy_dead == false ) {
				_enemy.at( i )->deadAnim( );
				_enemy.at( i )->dead( );
				_enemy_dead = true;
				_super_flame_rod_kill_count++;
			}
			// �A�j���[�V�������I��������폜����
			if ( _enemy.at( i )->isEndDeadAnim( ) == true ) {
				_floor->setBondNone( ( int )_enemy.at( i )->getPos( ).x, ( int )_enemy.at( i )->getPos( ).y );
				get_exp += _enemy.at( i )->getExp( );
				get_alchemy_point += _enemy.at( i )->getAlchemyPoint( );
				_message->createFont( _enemy.at( i )->getName( ), "", "", 0, MessageLog::KNOCK_DOWN );
				_enemy.erase( _enemy.begin( ) + i );
				_enemy.shrink_to_fit( );
				if ( _enemy.size( ) > 0 ) {
					for ( unsigned int j = 0; j < _enemy.size( ); j++ ) {
						_network->setSendChipData( NetworkApp::MAP_CHIP_TYPE::ENEMY, _enemy.at( j )->getPos( ), 0, false );
					}
				} else {
					_network->setSendChipData( NetworkApp::MAP_CHIP_TYPE::ENEMY, Vector2( 0, 0 ), 0, true );
				}
				_enemy_dead = false;
				_super_flame_rod_killed_count++;
			}
		}
	}
	// �������������Ă�����B���|�C���g��{�ɂ���
	if ( _player->getEquipment( EQUIPMENT_WEAPON ).id == ITEM_ID::SWORD3 ) {
		get_alchemy_point = get_alchemy_point * 2;
	}

	// �|�����G�l�~�[�̍��v�o���l���v���C���[�ɓn��
	if ( _item->isUseSuperFlameRod( ) == false ) {
		if ( get_exp > 0 ) {
			_player->increaseExp( get_exp );
			_player->alchemyPointManage( get_alchemy_point );
		}
	} else {
		if ( _super_flame_rod_killed_count >= _super_flame_rod_kill_count ) {
			_item->setUseSuperFlameRod( false );
			_use_flame_rod = false;
			if ( get_exp > 0 ) {
				_player->increaseExp( get_exp );
				_player->alchemyPointManage( get_alchemy_point );
			}
		}
	}
}

void EnemyManager::setBondBossTile( bool none ) {
	for ( int i = - 1; i <= 1; i++ ) {
		for ( int j = - 1; j <= 1; j++ ) {
			if ( none == true ) {
				_floor->setBondNone( ( int )_enemy.at( 0 )->getPos( ).x + i, ( int )_enemy.at( 0 )->getPos( ).y + j );
			} else {
				_floor->setBondEnemy( ( int )_enemy.at( 0 )->getPos( ).x + i, ( int )_enemy.at( 0 )->getPos( ).y + j );
			}
		}
	}
}

void EnemyManager::deleteAllEnemy( ) {
	// �K�w�ړ��̍ۑS�G�l�~�[���폜����
	/*
	for ( int i = 0; i < _enemy.size( ); i++ ) {
		_enemy.at( i )->deleatModel( );
	}
	*/
	_enemy.erase( _enemy.begin( ), _enemy.end( ) );
	_enemy.shrink_to_fit( );
}

void EnemyManager::setFloorLevel( int floor_level ) {
	_floor_level = floor_level;
}

ENEMY_DATA EnemyManager::getEnemyDataForName( std::string name ) {
	// id�ɂ���ăf�[�^���擾
	ENEMY_DATA result;
	for ( int i = 0; i < ENEMY_TYPE::MAX_ENEMY_NUM; i++ ) {
		if ( _enemy_data[ i ].name == name ) {
			result = _enemy_data[ i ];
			break;
		}
	}
	
	return result;
}

bool EnemyManager::isTurnEnd( ) {
	if ( _turn_end == true ) {
		return true;
	} else {
		return false;
	}
}

bool EnemyManager::isKnockDownBoss( ) {
	return _knock_down_boss;
}
