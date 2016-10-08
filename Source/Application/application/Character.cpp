#include "Character.h"
#include "Floor.h"
#include "Framework.h"
#include "Viewer.h"
#include "Turn.h"
#include "MessageLog.h"
#include "Effect.h"
#include "Sound.h"

const double BUFF_POWER   = 1.5;
const double DEBUFF_POWER = 0.5;

Character::Character( FloorPtr floor, NetworkAppPtr network, MessageLogPtr message, EffectPtr effect ) {
	_floor   = floor;
	_network = network;
	_message = message;
	_effect  = effect;
}


Character::~Character( ) {

}

void Character::loadShadow( int shadow_image ) {
	_shadow_image = shadow_image;
}

void Character::angleChange( ) {	
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	// ���f���̌�����ݒ�
	switch ( _status.dir ) {
	case LOWER_LEFT:
		_angle = -135.0f;
		break;
	case LOWER:
		_angle = 180.0f;
		break;
	case LOWER_RIGHT:
		_angle = 135.0f;
		break;
	case LEFT:
		_angle = -90.0f;
		break;
	case RIGHT:
		_angle = 90.0f;
		break;
	case UPPER_LEFT:
		_angle = -45.0f;
		break;
	case UPPER:
		_angle = 0.0f;
		break;
	case UPPER_RIGHT:
		_angle = 45.0f;
		break;
	}
	viewer->modelSetRotation( _anim_hundle.model, 0.0f, _angle, 0.0f );
}

void Character::rotateByWarp( ) {	
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	// ���f������]�����Ă���
	float speed = 30.0f;
	_warp_angle += speed;
	viewer->modelSetRotation( _anim_hundle.model, 0.0f, _warp_angle, 0.0f );
}

void Character::draw( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	
	// ���[�v�����ȊO�̎��A�C�e���Ȃǂɏ��������W���C������
	double correction = 1;
	if ( _warp == false && _warp_stair == false && _return_start == false && _ride_return_trap == false ) {
		if ( _floor->getTile( ( int )_pos.x, ( int )_pos.y ).item_exist == true ||
			 _floor->getTile( ( int )_pos.x, ( int )_pos.y ).stair_exist == true ) {
			_draw_pos.y = correction;
		} else {
			_draw_pos.y = 0;
		}
	}
	viewer->drawPolygonFloor( _draw_pos, _shadow_image );
	// ���f���̕`��֘A
	viewer->modelSetPos( _anim_hundle.model, _draw_pos );
	viewer->drawModel( _anim_hundle.model );
}

void Character::move( ) {
	// �ړ���ւ̃x�N�g��
	int move_x = ( _pos.x * TILE_SIZE - getPreDrawPos( ).x ) / WALK_ANIM_TIME * 2;
	int move_z = ( _pos.y * TILE_SIZE - getPreDrawPos( ).z ) / WALK_ANIM_TIME * 2;

	// ���X�ɕ`����W��ς��Ă���
	if ( move_x > 0 ) {  // ������
		_draw_pos.x += move_x;
		if ( _draw_pos.x > _pos.x * TILE_SIZE ) {
			_draw_pos.x = _pos.x * TILE_SIZE;
			_pre_pos.x = _pos.x * TILE_SIZE;
		}
	} else if ( move_x < 0 ) {  // �E����
		_draw_pos.x += move_x;
		if ( _draw_pos.x < _pos.x * TILE_SIZE ) {
			_draw_pos.x = _pos.x * TILE_SIZE;
			_pre_pos.x = _pos.x * TILE_SIZE;
		}
	} else {  // �ړI�n�ɓ��B������`����W���C��
		_draw_pos.x = _pos.x * TILE_SIZE;
		_pre_pos.x = _pos.x * TILE_SIZE;
	}
	
	if ( move_z > 0 ) {  // ������
		_draw_pos.z += move_z;
		if ( _draw_pos.z > _pos.y * TILE_SIZE ) {
			_draw_pos.z = _pos.y * TILE_SIZE;
			_pre_pos.z = _pos.y * TILE_SIZE;
		}
	} else if ( move_z < 0 ) {  // �����
		_draw_pos.z += move_z;
		if ( _draw_pos.z < _pos.y * TILE_SIZE ) {
			_draw_pos.z = _pos.y * TILE_SIZE;
			_pre_pos.z = _pos.y * TILE_SIZE;
		}
	} else {  // �ړI�n�ɓ��B������`����W���C��
		_draw_pos.z = _pos.y * TILE_SIZE;
		_pre_pos.z = _pos.y * TILE_SIZE;
	}
}

void Character::playbackAnim( float stay_anim_time, float walk_anim_time , float attack_anim_time, float dead_anim_time, float damage_time, float revive_time ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	// �A�j���[�V������������鎞�Ԃ��擾
	_total_time = viewer->animTotalTime( _anim_hundle.model, _main_anim );

	// �L�����N�^�[�̏�Ԃɂ���ăA�j���[�V�������Đ����鑬�x��ς���{����ݒ�
	float magnification;
	float slow = 0.7f;
	float fast = 3.0f;
	if ( _status.state == SLOW ) {
		magnification = slow;
	} else if ( _status.state == FAST ) {
		magnification = fast;
	} else {
		magnification = 1.0f;
	}

	// �Đ����Ԃ�i�߂�
	if ( _anim_state == STAY_ANIM ) {
		_anim_play_time += ( stay_anim_time * magnification );
	}
	if ( _anim_state == WALK_ANIM ) {
		_anim_play_time += ( walk_anim_time * magnification );
	}
	if ( _anim_state == ATTACK_ANIM ) {
		_anim_play_time += ( attack_anim_time * magnification );
	}
	if ( _anim_state == DEAD_ANIM ) {
		_anim_play_time += ( dead_anim_time * magnification );
	}
	if ( _anim_state == DAMAGE_ANIM ) {
		_anim_play_time += ( damage_time * magnification );
	}
	if ( _anim_state == REVIVE_ANIM ) {
		_anim_play_time -= ( revive_time * magnification );
	}

	_anim_count++;

    // �A�j���[�V�����Đ����Ԃ���������珉��������
    if( _anim_play_time >= _total_time ) {
		if ( _anim_state != DEAD_ANIM ) {
			// �A�j���[�V������Stay�ɐ؂�ւ�
			if ( _anim_state == ATTACK_ANIM ) {
				viewer->dettachAnim( _anim_hundle.model, _anim_index.attack );
				_anim_index.stay = viewer->attachAnim( _anim_hundle.model, 0, _anim_hundle.stay );
				_main_anim       = _anim_index.stay;
				_anim_count      = 0;
				_anim_state      = STAY_ANIM;
			}
			if ( _anim_state == DAMAGE_ANIM ) {
				viewer->dettachAnim( _anim_hundle.model, _anim_index.damage );
				_anim_index.stay = viewer->attachAnim( _anim_hundle.model, 0, _anim_hundle.stay );
				_main_anim       = _anim_index.stay;
				_anim_count      = 0;
				_anim_state      = STAY_ANIM;
			}
			// �Đ����Ԃ̏�����
			_anim_play_time = 0.0f;
		}
	}
	
	if ( _anim_play_time <= 0 && _anim_state == REVIVE_ANIM ) {
		viewer->dettachAnim( _anim_hundle.model, _anim_index.damage );
		_anim_index.stay = viewer->attachAnim( _anim_hundle.model, 0, _anim_hundle.stay );
		_main_anim       = _anim_index.stay;
		_anim_count      = 0;
		_anim_state      = STAY_ANIM;
		// �Đ����Ԃ̏�����
		_anim_play_time = 0.0f;
	}

	// �ړ��A�j���[�V�����̂ݍ��W�ړ��ɂ����鎞�ԂƓ�������
	if( _anim_count > WALK_ANIM_TIME ) {
		if ( _anim_state == WALK_ANIM ) {
			viewer->dettachAnim( _anim_hundle.model, _anim_index.walk );
			_anim_index.stay = viewer->attachAnim( _anim_hundle.model, 0, _anim_hundle.stay );
			_main_anim       = _anim_index.stay;
			_anim_count      = 0;
			_anim_state      = STAY_ANIM;
			_walking         = false;
		}
    }
	// �A�j���[�V�����̍Đ�
	viewer->setAttachAnimTime( _anim_hundle.model, _main_anim, _anim_play_time );
}

void Character::refreshState( ) {
	FrameworkPtr fw = Framework::getInstance( );
	SoundPtr sound = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );

	sound->backgrondPlaySound( Sound::CURE );
	_status.state      = NORMAL_STATE;
	_elapsed_time      = 0;
	_state_change_turn = 0;
	_message->createFont( _name, "", "", 0, MessageLog::MESSAGE_TYPE::CURE_ABNORMAL );
}

void Character::refreshStateNextFloor( ) {

	_status.state      = NORMAL_STATE;
	_elapsed_time      = 0;
	_state_change_turn = 0;
	_message->createFont( _name, "", "", 0, MessageLog::MESSAGE_TYPE::CURE_ABNORMAL );
}

void Character::becomeAbnormalState( STATE state, int effect_num ) {
	FrameworkPtr fw = Framework::getInstance( );
	SoundPtr sound = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );

	if ( _status.state == NORMAL_STATE ) {
		// ������
		_status.state = state;
		_elapsed_time = 0;
		// ��Ԉُ킪�Ȃ���^�[����ݒ�
		switch ( state ) {
		case POISON:
			_state_change_turn = 1;
			_effect->playEffect( Effect::EFFECT_TYPE::EFFECT_POISON, _draw_pos + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), effect_num );
			_message->createFont( _name, "�ǂ�", "", 0, MessageLog::STATE_ABNORMAL );
			sound->backgrondPlaySound( Sound::DEBUFF );
			break;
		case PARALYSIS:
			_state_change_turn = 1 + rand( ) % 2;
			_effect->playEffect( Effect::EFFECT_TYPE::EFFECT_PARALYSIS, _draw_pos + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), effect_num );
			_message->createFont( _name, "�}�q", "", 0, MessageLog::STATE_ABNORMAL );
			sound->backgrondPlaySound( Sound::DEBUFF );
			break;
		case SKILL_SEAL:
			_effect->playEffect( Effect::EFFECT_TYPE::EFFECT_SEALED, _draw_pos + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), effect_num );
			_message->createFont( _name, "�X�L������", "", 0, MessageLog::STATE_ABNORMAL );
			break;
		case BIND_TILE:
			_state_change_turn = 5 + rand( ) % 4;
			_effect->playEffect( Effect::EFFECT_TYPE::EFFECT_SEALED, _draw_pos + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), effect_num );
			_message->createFont( _name, "�o�C���h", "", 0, MessageLog::STATE_ABNORMAL );
			break;
		case CONFUSE:
			_state_change_turn = 6 + rand( ) % 3;
			_effect->playEffect( Effect::EFFECT_TYPE::EFFECT_CONFUSE, _draw_pos + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), effect_num );
			_message->createFont( _name, "������", "", 0, MessageLog::STATE_ABNORMAL );
			sound->backgrondPlaySound( Sound::DEBUFF );
			break;
		}
	} else {
		_message->createFont ( _name, "", "", 0, MessageLog::NO_CHANGE_ABNORMAL );
	}
}

void Character::elapsedAbnormalTurn( ) {
	if ( _status.state != NORMAL_STATE && _status.state != SKILL_SEAL ) {
		_elapsed_time++;
		// ��Ԉُ�ɂ������Ă���̌o�ߎ��Ԃ����^�[���𒴂������Ԉُ������
		if ( _elapsed_time >= _state_change_turn ) {
			if ( _status.state == CONFUSE || _status.state == PARALYSIS || 
				 _status.state == BIND_TILE ) {
				refreshState( );
			} else if ( _status.state == POISON ) {
				// �ŏ�Ԃ̂�HP����
				_elapsed_time = 0;
				decreaseHPForPoison( );
			}
		}
	}
}

void Character::refreshSpeed( ) {
	_status.speed       = NORMAL_SPEED;
	_speed_elapsed_time = 0;
	_speed_change_turn  = 0;
	_speed_abnormal     = false;
	_message->createFont( _name, "", "", 0, MessageLog::CURE_SPEED );
}

void Character::changeSpeedState( SPEED speed, int effect_num ) {
	FrameworkPtr fw = Framework::getInstance( );
	SoundPtr sound = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );

	if ( _status.speed == SPEED::SLOW && speed == SPEED::FAST ) {
		refreshSpeed( );
	} else if ( _status.speed == SPEED::FAST && speed == SPEED::SLOW ) {
		refreshSpeed( );
	} else if ( _status.speed == SPEED::FAST && speed == SPEED::FAST ) {
		_message->createFont ( _name, "�����Ȃ�Ȃ��B", "", 0, MessageLog::NO_CHANGE_SPEED );
	} else if ( _status.speed == SPEED::SLOW && speed == SPEED::SLOW ) {
		_message->createFont ( _name, "�x���Ȃ�Ȃ��B", "", 0, MessageLog::NO_CHANGE_SPEED );
	} else if ( _status.speed != speed ) {
		// ������
		_status.speed       = speed;
		_speed_elapsed_time = 0;
		// �͂₳��Ԃ��Ȃ���^�[����ݒ�
		switch ( speed ) {
		case SLOW:
			_speed_change_turn = 4 + rand( ) % 3;
			sound->backgrondPlaySound( Sound::BUFF );
			_effect->playEffect( Effect::EFFECT_TYPE::EFFECT_DEBUFF, _draw_pos + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), effect_num );
			_message->createFont( _name, "�x���Ȃ����B", "", 0, MessageLog::CHANGE_SPEED );
			break;
		case FAST:
			_speed_change_turn = 4 + rand( ) % 3;
			sound->backgrondPlaySound( Sound::DEBUFF );
			_effect->playEffect( Effect::EFFECT_TYPE::EFFECT_BUFF, _draw_pos + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), effect_num );
			_message->createFont( _name, "�����Ȃ����B", "", 0, MessageLog::CHANGE_SPEED );
			break;
		}
	}
}

void Character::elapsedSpeedTurn( ) {
	if ( _status.speed != SPEED::NORMAL_SPEED ) {
		if ( _speed_abnormal == false ) {
			_speed_elapsed_time++;
			if ( _status.speed == SPEED::SLOW || _status.speed == SPEED::FAST ) {
				_speed_abnormal = true;
			}
		} else {
			_speed_abnormal = false;
		}
		// �͂₳��Ԃ��ω����Ă���̌o�ߎ��Ԃ����^�[���𒴂������Ԉُ������
		if ( _speed_elapsed_time >= _speed_change_turn ) {
			refreshSpeed( );
		}
	}
}

void Character::refreshBuff( ) {
	_status.buff       = NO_BUFF;
	_buff_elapsed_time = 0;
	_buff_change_turn  = 0;
	_buff_end = true;
	_message->createFont( _name, "", "", 0, MessageLog::CURE_BUFF );
}

void Character::changeBuffState( BUFF_STATE buff, int effect_num ) {
	FrameworkPtr fw = Framework::getInstance( );
	SoundPtr sound = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );

	if ( _status.buff == BUFF_STATE::DEBUFF && buff == BUFF_STATE::BUFF ) {
		refreshBuff( );
	} else if ( _status.buff == BUFF_STATE::BUFF && buff == BUFF_STATE::DEBUFF ) {
		refreshBuff( );
	} else if ( _status.buff == BUFF_STATE::BUFF && buff == BUFF_STATE::BUFF ) {
		_message->createFont ( _name, "�����Ȃ�Ȃ��B", "", 0, MessageLog::NO_CHANGE_SPEED );
	} else if ( _status.buff == BUFF_STATE::DEBUFF && buff == BUFF_STATE::DEBUFF ) {
		_message->createFont ( _name, "�キ�Ȃ�Ȃ��B", "", 0, MessageLog::NO_CHANGE_SPEED );
	} else if ( _status.buff != buff ) {
		// ������
		_status.buff       = buff;
		_buff_elapsed_time = 0;
		_buff = true;
		// �o�t��Ԃ��Ȃ���^�[����ݒ�
		switch ( buff ) {
		case BUFF:
			_buff_change_turn = 5;
			sound->backgrondPlaySound( Sound::BUFF );
			_effect->playEffect( Effect::EFFECT_TYPE::EFFECT_DEBUFF, _draw_pos + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), effect_num );
			_message->createFont( _name, "�����Ȃ����B", "", 0, MessageLog::CHANGE_BUFF );
			break;
		case DEBUFF:
			_buff_change_turn = 5;
			sound->backgrondPlaySound( Sound::DEBUFF );
			_effect->playEffect( Effect::EFFECT_TYPE::EFFECT_BUFF, _draw_pos + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), effect_num );
			_message->createFont( _name, "�キ�Ȃ����B", "", 0, MessageLog::CHANGE_BUFF );
			break;
		}
	}
}

void Character::elapsedBuffTurn( ) {
	if ( _status.buff != BUFF_STATE::NO_BUFF ) {
		_buff_elapsed_time++;		
		// �͂₳��Ԃ��ω����Ă���̌o�ߎ��Ԃ����^�[���𒴂������Ԉُ������
		if ( _buff_elapsed_time >= _buff_change_turn ) {
			refreshBuff( );
		}
	}
}

void Character::statusForBuff( ) {
	if ( _buff == true ) {
		if ( _status.buff == BUFF_STATE::BUFF ) {
			_status.attack = _status.attack * BUFF_POWER;
			_buff = false;
		} else if ( _status.buff == BUFF_STATE::DEBUFF ) {
			_status.attack = _status.attack * DEBUFF_POWER;
			_buff = false;
		}
	}
}

void Character::warpPos( ) {
	if ( _warp_start == true ) {
		if ( warpProduction( true ) == true ) {
			_floor->setBondNone( ( int )_pos.x, ( int )_pos.y );
			while ( true ) {
				// �`����W
				Vector draw_pos = _floor->getRandomFloor( ).pos;
				_draw_pos.x = draw_pos.x;
				_draw_pos.z = draw_pos.z;
				_pre_pos  = _draw_pos;
				// �^�C�����W
				_pos.x = _draw_pos.x / TILE_SIZE;
				_pos.y = _draw_pos.z / TILE_SIZE;
				if ( _floor->getTile( ( int )_pos.x, ( int )_pos.y ).bond != Floor::BOND::ENEMY &&
					 _floor->getTile( ( int )_pos.x, ( int )_pos.y ).bond != Floor::BOND::PLAYER &&
					 _floor->getTile( ( int )_pos.x, ( int )_pos.y ).myistery_type == Floor::MYSTERY_TILE::NONE_MISTERY ) {
					_warp_start = false;
					_warp_move = true;
					break;
				}
			}
		}
	} else {
		if ( warpProduction( false ) == true ) {
			_warp = false;
		}
	}
}

void Character::warpStairPos( ) {
	if ( _warp_start == true ) {
		if ( warpProduction( true ) == true ) {
			_floor->setBondNone( ( int )_pos.x, ( int )_pos.y );
			while ( true ) {
				// �`����W
				Vector draw_pos = _floor->getRandomStairFloor( ).pos;
				_draw_pos.x = draw_pos.x;
				_draw_pos.z = draw_pos.z;
				_pre_pos  = _draw_pos;
				// �^�C�����W
				_pos.x = _draw_pos.x / TILE_SIZE;
				_pos.y = _draw_pos.z / TILE_SIZE;
				if ( _floor->getTile( ( int )_pos.x, ( int )_pos.y ).bond != Floor::BOND::ENEMY &&
					 _floor->getTile( ( int )_pos.x, ( int )_pos.y ).bond != Floor::BOND::PLAYER &&
					 _floor->getTile( ( int )_pos.x, ( int )_pos.y ).myistery_type == Floor::MYSTERY_TILE::NONE_MISTERY ) {
					_warp_start = false;
					_warp_move = true;
					break;
				}
			}
		}
	} else {
		if ( warpProduction( false ) == true ) {
			_warp_stair = false;
		}
	}
}

bool Character::warpProduction( bool up ) {
	double speed = 3.0;
	if ( up == true ) {
		// �`����W
		_draw_pos.y += speed;
		if ( _draw_pos.y > WARP_LIMIT_Y ) {
			return true;
		}
	} else {
		// �`����W
		_draw_pos.y -= speed;
		if ( _draw_pos.y < 0 ) {
			_draw_pos.y = 0;
			return true;
		}
	}
	return false;
}

bool Character::pitProduction( ) {
	double speed = 1.0;

	// �`����W
	_draw_pos.y -= speed;
	_draw_pos.z += 1;
	if ( _draw_pos.y < -30 ) {
		_draw_pos.y = -30;
		return true;
	}

	return false;
}

void Character::warpStart( int num ) {
	FrameworkPtr fw = Framework::getInstance( );
	SoundPtr sound = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );

	sound->backgrondPlaySound( Sound::WARP );
	_warp = true;
	_warp_start = true;
	_warp_angle = _angle;
	_effect->playEffect( Effect::EFFECT_TYPE::EFFECT_WIND,  _draw_pos + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), num );
}

void Character::warpStairStart( int num ) {
	FrameworkPtr fw = Framework::getInstance( );
	SoundPtr sound = std::dynamic_pointer_cast< Sound >( fw->getTask( typeid( Sound ).name( ) ) );

	sound->backgrondPlaySound( Sound::WARP );
	_warp_stair = true;
	_warp_start = true;
	_warp_angle = _angle;
	_effect->playEffect( Effect::EFFECT_TYPE::EFFECT_WIND,  _draw_pos + Vector( 5, 0, 5 ), Vector( 0, 0, 0 ), num );
}

void Character::decreaseHPForPoison( ) {
	_status.life--;
}

bool Character::isNotCornerWall( Vector2 pos ) {
	switch( _status.dir ) {
	case LOWER_LEFT:
		if ( _floor->getTile( pos.x + 1, pos.y ).type == Floor::TYPE::WALL ||
			 _floor->getTile( pos.x, pos.y + 1 ).type == Floor::TYPE::WALL ) {
			return false;
		}
		break;
	case LOWER_RIGHT:
		if ( _floor->getTile( pos.x - 1, pos.y ).type == Floor::TYPE::WALL ||
			 _floor->getTile( pos.x, pos.y + 1 ).type == Floor::TYPE::WALL ) {
			return false;
		}
		break;
	case UPPER_LEFT:
		if ( _floor->getTile( pos.x + 1, pos.y ).type == Floor::TYPE::WALL ||
			 _floor->getTile( pos.x, pos.y - 1 ).type == Floor::TYPE::WALL ) {
			return false;
		}
		break;
	case UPPER_RIGHT:
		if ( _floor->getTile( pos.x - 1, pos.y ).type == Floor::TYPE::WALL ||
			 _floor->getTile( pos.x, pos.y - 1 ).type == Floor::TYPE::WALL ) {
			return false;
		}
		break;
	}
	return true;
}

void Character::setDir( MOVE_DIR dir ) {
	_status.dir = dir;
}

Vector Character::getDrawPos( ) {
	return _draw_pos;
}

Vector Character::getPreDrawPos( ) {
	return _pre_pos;
}

Vector2 Character::getPos( ) {
	return _pos;
}

STATUS_DATA Character::getStatus( ) {
	return _status;
}

std::string Character::getName( ) {
	return _name;
}

float Character::getAngle( ) {
	return _angle;
}

Character::ANIM_HUNDLE Character::getAnimHundle( ) {
	return _anim_hundle;
}

Character::ANIM_INDEX Character::getAnimIndex( ) {
	return _anim_index;
}

int Character::getMainAnim( ) {
	return _main_anim;
}

Character::ANIM_STATE Character::getAnimState( ) {
	return _anim_state;
}

int Character::getAnimCount( ) {
	return _anim_count;
}

float Character::getAnimTime( ) {
	return _anim_play_time;
}

float Character::getTotalAnimTime( ) {
	return _total_time;
}

float Character::getAttackAnimTime( ) {
	return _attack_time;
}

float Character::getDamageAnimTime( ) {
	return _damage_time;
}

float Character::getDeadAnimTime( ) {
	return _dead_time;
}

bool Character::isWalking( ) {
	return _walking;
}

bool Character::isSpeedAbnormal( ) {
	return _speed_abnormal;
}

bool Character::isWarp( ) {
	return _warp;
}

bool Character::isWarpMove( ) {
	if ( _warp_move == true ) {
		_warp_move = false;
		return true;
	}
	return false;
}