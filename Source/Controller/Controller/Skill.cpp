#include "Skill.h"
#include "Framework.h"
#include "Viewer.h"
#include "Touch.h"
#include "ItemImage.h"

Skill::Skill( Vector2 pos, NetworkControllerPtr network, ItemImagePtr item_image ) : Icon( pos ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	_image = viewer->loadGraph( "work/ctrl_UI/skill.png" );
	_window = viewer->loadGraph( "work/ctrl_UI/window/window_skill.png" );
	_window_use = viewer->loadGraph( "work/ctrl_UI/window/window_item_use.png" );
	_network = network;
	_item_image = item_image;
	_open_num = -1;
	SKILL_DATA teble[ ] = {
		SKILL_DATA( ZANGEKI, "�a��", "�y�a���z�������܂��ꂽ�������ڂ̑O�̓G���т��B��������5" ),
		SKILL_DATA( ZANMETUHA, "�a�Ŕj", "�y�a�Ŕj�z�a���ɂ��Ռ��g��2�}�X��܂ł̓G���P���B��������10" ),
		SKILL_DATA( MATERIASWORD, "�}�e���A�\�[�h", "�y�}�e���A�\�[�h�z���͂ɂ��G����̗͂��z�����a���B�^�����_���[�W��HP���񕜂���B��������20" ),
		SKILL_DATA( SPEED_UP, "�����̉���", "�y�����̉���z���̗͂�g�ɂ܂Ƃ������{���̑�������ɓ����B���^�[���̊�2��s�����ł���B��������30" ),
	};
	for ( int i = 0; i < MAX_SKILL_NUM; i++ ) {
		_skill_table [ i ] = teble[ i ];
	}

	_zangeki = viewer->loadGraph( "work/ctrl_UI/skill/zangeki.png" );
	_zanmetuha = viewer->loadGraph( "work/ctrl_UI/skill/zanmetuha.png" );
	_materiasword = viewer->loadGraph( "work/ctrl_UI/skill/materiasword.png" );
	_speed_up = viewer->loadGraph( "work/ctrl_UI/skill/speed_up.png" );

	_zangeki_seal = viewer->loadGraph( "work/ctrl_UI/skill/zangeki_seal.png" );
	_zanmetuha_seal = viewer->loadGraph( "work/ctrl_UI/skill/zanmetuha_seal.png" );
	_materiasword_seal = viewer->loadGraph( "work/ctrl_UI/skill/materiasword_seal.png" );
	_speed_up_seal = viewer->loadGraph( "work/ctrl_UI/skill/speed_up_seal.png" );
	//�f�o�b�O�p
	/*_skill_list.push_back( _skill_table[ 0 ] );
	_skill_list.push_back( _skill_table[ 1 ] );
	_skill_list.push_back( _skill_table[ 2 ] );
	_skill_list.push_back( _skill_table[ 3 ] );*/
}

Skill::~Skill( ) {
}

void Skill::init( ) {
	_skill_list.clear( );
	close( );
}

void Skill::close( ) {
	_open_num = -1;
}

void Skill::touch( ) {
	FrameworkPtr fw = Framework::getInstance( );
	TouchPtr touch = std::dynamic_pointer_cast< Touch >( fw->getTask( typeid( Touch ).name( ) ) );

	drawWindow( );
	if ( _open_num != -1 ) {
		openSkill( _open_num );
	}
	if ( touch->isSeparate( ) ) {
		_separate_flag = true;
		_close_flag = false;
	}
}

void Skill::drawWindow( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	TouchPtr touch = std::dynamic_pointer_cast< Touch >( fw->getTask( typeid( Touch ).name( ) ) );

	// �E�B���h�E�̕`��
	viewer->drawGraph( SKILL_WINDOW_X, SKILL_WINDOW_Y, _window );

	unsigned int count = 0;		// vector�̎Q�Ƃ𓾂邽�߂Ɏg���̂�watning�΍��unsigned�^
	for ( int i = 0; i < SKILL_COLUMN; i++ ) {
		for ( int j = 0; j <= SKILL_ROW; j++ ) {
			// �`��ʒu��ݒ�
			Vector2 skill_pos ( SKILL_WINDOW_X + SKILL_X_SPACE + ( SKILL_X_INTERVAL * j ), SKILL_WINDOW_Y + SKILL_Y_SPACE + ( SKILL_Y_INTERVAL * i ) );
			
			// �A�C�R����`��
			if ( count < _skill_list.size( ) ) { 
				// �I�𒆂̃A�C�e��
				if ( count == _open_num ) {
					viewer->drawGraph( ( int )skill_pos.x, ( int )skill_pos.y, _item_image->getFrameWhite( ) );
				}

				// �X�L�����󏈗�
				if ( _network->getStatusData( ).state == STATE::SKILL_SEAL ) {
					drawSkillSeal( );
					viewer->drawGraph ( ( int )skill_pos.x, ( int )skill_pos.y, getSkillSealImage( _skill_list.at( count ).type.id ) );
				} else {	
					viewer->drawGraph ( ( int )skill_pos.x, ( int )skill_pos.y, getSkillImage( _skill_list.at( count ).type.id ) );
					// �X�L�����^�b�`�������̏���
					if ( touch->isTouch( skill_pos, SKILL_IMAGE_WIDTH, SKILL_IMAGE_HEIGHT ) ) {
						if ( _open_num == count && _separate_flag == true ) {
							_open_num = NOT_OEPN_SKILL;
							_separate_flag = false;
						} else if ( _separate_flag == true ) {
							_open_num = count;
							_separate_flag = false;

						}
					}
				}
			}
			count++;
		}
	}

	// �����̕`��
	/*Vector2 string_pos = Vector2( SKILL_LIST_POS_X, SKILL_LIST_POS_Y );
	for ( int i = 0; i < _skill_list.size( ); i++ ) {	
		if ( i == _open_num ) {
			drawStringColor( string_pos, _skill_list.at( i ).type.name, 0, 180, 255 );
		} else {
			drawString( string_pos, _skill_list.at( i ).type.name );
		}
		
		if ( touch->isTouch( string_pos, string_pos.x + SKILL_NAME_WIDTH, FONT_SIZE  ) ) {
			// ����
			if ( _open_num == i && _separate_flag == true ) {
				 _close_flag = true;
				 close( );
				 touch->rejectTouch( );
			} 
			// �J��
			else if ( _close_flag == false ) {
				_separate_flag = false;
				_open_num = i;
			}
		}
		string_pos.y += SKILL_DISTANCE;
	}*/

}

void Skill::openSkill( int num ) {
	FrameworkPtr fw = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );
	TouchPtr touch = std::dynamic_pointer_cast< Touch >( fw->getTask( typeid( Touch ).name( ) ) );

	viewer->drawGraph( SKILL_WINDOW_X + SKILL_WINDOW_WIDTH, SKILL_WINDOW_Y, _window_use );	// �E�B���h�E�̕`��
	drawDescription( _skill_list.at( num ) );

	int use_dis = SKILL_USE_HEIGHT / 4; // �E�B���h�E�̍��� / �R�}���h�̐� + 2
	Vector2 string_pos[  ] = { Vector2 ( SKILL_USE_STRING_X, SKILL_WINDOW_Y + use_dis ),
							   Vector2 ( SKILL_USE_STRING_X, SKILL_WINDOW_Y + use_dis * 2 ) };
	drawString( string_pos[ 0 ], "����" );
	drawString( string_pos[ 1 ], "�Ƃ���" );

	// �����R�}���h�̏���
	if ( touch->isTouch( string_pos[ 0 ], SKILL_USE_WIDTH, FONT_SIZE ) ) {
		_network->setSendMagicAttack( true );
		_network->setSendSkillId( _skill_list.at( num ).type.id );
		touch->rejectTouch( );
		close( );
	// �Ƃ���R�}���h
	} else if ( touch->isTouch( string_pos[ 1 ], SKILL_USE_WIDTH, FONT_SIZE ) ) {
		close( );
		touch->rejectTouch( );
	}
}

void Skill::drawDescription( SKILL_DATA skill ) {
	int line = 0;
	line = skill.description.find( "�z" );
	if ( line == std::string::npos ) {
		line = skill.description.find( "�B" );
	}
	line += 2;
	std::string tmp = skill.description.substr( 0, line );	// �B�܂ł̈ʒu����s�ڂƂ���
	drawStringSmallFont( Vector2 ( SKILL_DESCRIPTION_X, SKILL_DESCRIPTION_Y ), tmp );
	tmp = skill.description.substr( line );					// �B�ȍ~�̕�����2�s�ڂɂ���
	drawStringSmallFont( Vector2 ( SKILL_DESCRIPTION_X, SKILL_DESCRIPTION_Y + FONT_SIZE ), tmp );
}

void Skill::skillGet( ) {
	SKILL_ID id = _network->getSkillType( ).id;
	if ( id != SKILL_NONE ) {
		_skill_list.push_back( getSkillData( id ) );
		_network->resetSkillData( );
	}
}

Skill::SKILL_DATA Skill::getSkillData( SKILL_ID id ) {
	SKILL_DATA result;

	for ( int i = 0; i < MAX_SKILL_NUM; i++ ) {
		if ( _skill_table[ i ].type.id == id ) {
			result = _skill_table[ i ];
			break;
		}
	}

	return result;
}

int Skill::getSkillImage( SKILL_ID id ) {
	int image = 0;
	
	switch ( id ) {
		case SKILL_ID::ZANGEKI : {
			image = _zangeki;
			break;
		}
		case SKILL_ID::ZANMETUHA : {
			image = _zanmetuha;
			break;
		}
		case SKILL_ID::MATERIASWORD : {
			image = _materiasword;
			break;
		}
		case SKILL_ID::SPEED_UP : {
			image = _speed_up;
			break;
		}
	}

	return image;

}

int Skill::getSkillSealImage( SKILL_ID id ) {
	int image = 0;
	
	switch ( id ) {
		case SKILL_ID::ZANGEKI : {
			image = _zangeki_seal;
			break;
		}
		case SKILL_ID::ZANMETUHA : {
			image = _zanmetuha_seal;
			break;
		}
		case SKILL_ID::MATERIASWORD : {
			image = _materiasword_seal;
			break;
		}
		case SKILL_ID::SPEED_UP : {
			image = _speed_up_seal;
			break;
		}
	}

	return image;

}

void Skill::drawSkillSeal( ) {
	std::string str = "�X�L���͕��󂳂�Ă���I";
	drawString( Vector2 ( SKILL_DESCRIPTION_X, SKILL_DESCRIPTION_Y ), str );
}