#include "Effect.h"
#include "Framework.h"
#include "Viewer.h"
#include "EffekseerForDXLib.h"

Effect::Effect( ) {
	loadEffect( );
}


Effect::~Effect( ) {

}

void Effect::loadEffect( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	// エフェクトを読み込む。
	_heal_handle    = LoadEffekseerEffect( "work/effect_2_0/effect_heal.efk" );
	_stamina_handle = LoadEffekseerEffect( "work/effect_2_0/effect_stamina.efk" );
	_flame_handle   = LoadEffekseerEffect( "work/effect_2_0/effect_fire3.efk" );
	
	_skill_1_handle = LoadEffekseerEffect( "work/effect_2_0/effect_skill1.efk" );
	_skill_2_handle = LoadEffekseerEffect( "work/effect_2_0/effect_skill3.efk" );
	_skill_3_handle = LoadEffekseerEffect( "work/effect_2_0/effect_skill2.efk" );
	_skill_4_handle = LoadEffekseerEffect( "work/dummy/Effect/wind.efk" );
	
	_poison_handle    = LoadEffekseerEffect( "work/effect_2_0/effect_poison.efk" );
	_paralysis_handle = LoadEffekseerEffect( "work/effect_2_0/effect_paralysis.efk" );
	_confuse_handle   = LoadEffekseerEffect( "work/effect_2_0/effect_confusion.efk" );
	_buff_handle      = LoadEffekseerEffect( "work/effect_2_0/effect_buff.efk" );
	_debuff_handle    = LoadEffekseerEffect( "work/effect_2_0/effect_debuff.efk" );
	_seal_handle      = LoadEffekseerEffect( "work/effect_2_0/effect_sealed.efk" );

	_sporn_handle       = LoadEffekseerEffect( "work/effect_2_0/effect_sporn.efk" );
	_boss_attack_handle = LoadEffekseerEffect( "work/effect_2_0/effect_boss_attack.efk" );
													 
	_frame_dummy[ 0 ] = viewer->loadGraph( "work/dummeffect_2_0/y/frame/flame_1.png" );
	_frame_dummy[ 1 ] = viewer->loadGraph( "work/dummeffect_2_0/y/frame/flame_2.png" );
	_frame_dummy[ 2 ] = viewer->loadGraph( "work/dummeffect_2_0/y/frame/flame_3.png" );
	_frame_dummy[ 3 ] = viewer->loadGraph( "work/dummy/frame/flame_4.png" );
	_frame_dummy[ 4 ] = viewer->loadGraph( "work/dummy/frame/flame_5.png" );
}

void Effect::deleteEffect( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	// エフェクトを削除
	DeleteEffekseerEffect( _heal_handle );
	DeleteEffekseerEffect( _stamina_handle );
	DeleteEffekseerEffect( _flame_handle );
	DeleteEffekseerEffect( _skill_1_handle );
	DeleteEffekseerEffect( _skill_2_handle );
	DeleteEffekseerEffect( _skill_3_handle );
	DeleteEffekseerEffect( _skill_4_handle );
	DeleteEffekseerEffect( _poison_handle );
	DeleteEffekseerEffect( _paralysis_handle );
	DeleteEffekseerEffect( _confuse_handle );
	DeleteEffekseerEffect( _buff_handle );
	DeleteEffekseerEffect( _debuff_handle );
	DeleteEffekseerEffect( _seal_handle );
	DeleteEffekseerEffect( _sporn_handle );

	viewer->deleteGraph( _frame_dummy[ 0 ] );
	viewer->deleteGraph( _frame_dummy[ 1 ] );
	viewer->deleteGraph( _frame_dummy[ 2 ] );
	viewer->deleteGraph( _frame_dummy[ 3 ] );
	viewer->deleteGraph( _frame_dummy[ 4 ] );
}

void Effect::init( ) {
	_supper_flame_effect_draw  = false;
	_supper_flame_effect_index = 0;
	_supper_flame_effect_time  = 0;
}

void Effect::update( ) {
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();
	// 各エフェクトの描画位置の更新と再生終了時に削除
	for ( unsigned int i = 0; i < _play_effect.size( ); i++ ) {
		SetPosPlayingEffekseer3DEffect( _play_effect.at( i ).play_hundle, _play_effect.at( i ).draw_pos.x, _play_effect.at( i ).draw_pos.y, _play_effect.at( i ).draw_pos.z );
		if ( IsEffekseer3DEffectPlaying( _play_effect.at( i ).play_hundle ) == 1 ) {
			_play_effect.erase( _play_effect.begin( ) + i );
		}
	}
	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer3D( );
	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer3D( );

	drawSupperFlameEffect( );
}

void Effect::playEffect( EFFECT_TYPE type, Vector pos, Vector rotate, int fllow_num ) {
	EFFECT_DATA play_effect;
	// 追従するオブジェクト
	play_effect.type = type;
	play_effect.fllow_num = fllow_num;
	// エフェクトを再生する。
	switch ( type ) {
	case EFFECT_HEAL:
		play_effect.play_hundle = PlayEffekseer3DEffect( _heal_handle );
		SetScalePlayingEffekseer3DEffect( play_effect.play_hundle, 3, 3, 3 );
		break;
	case EFFECT_STAMINA:
		play_effect.play_hundle = PlayEffekseer3DEffect( _stamina_handle );
		SetScalePlayingEffekseer3DEffect( play_effect.play_hundle, 1, 1, 1 );
		break;
	case EFFECT_FLAME:
		play_effect.play_hundle = PlayEffekseer3DEffect( _flame_handle );
		SetScalePlayingEffekseer3DEffect( play_effect.play_hundle, 5, 5, 5 );
		break;
	case EFFECT_SKILL1:
		play_effect.play_hundle = PlayEffekseer3DEffect( _skill_1_handle );
		SetScalePlayingEffekseer3DEffect( play_effect.play_hundle, 2, 2, 2 );
		break;
	case EFFECT_SKILL2:
		play_effect.play_hundle = PlayEffekseer3DEffect( _skill_2_handle );
		SetScalePlayingEffekseer3DEffect( play_effect.play_hundle, 3, 3, 3 );
		break;
	case EFFECT_SKILL3:
		play_effect.play_hundle = PlayEffekseer3DEffect( _skill_3_handle );
		SetScalePlayingEffekseer3DEffect( play_effect.play_hundle, 5, 5, 5 );
		break;
	case EFFECT_WIND:
		play_effect.play_hundle = PlayEffekseer3DEffect( _skill_4_handle );
		SetScalePlayingEffekseer3DEffect( play_effect.play_hundle, 1.5f, 1.5f, 1.5f );
		break;
	case EFFECT_POISON:
		play_effect.play_hundle = PlayEffekseer3DEffect( _poison_handle );
		SetScalePlayingEffekseer3DEffect( play_effect.play_hundle, 5, 5, 5 );
		break;
	case EFFECT_PARALYSIS:
		play_effect.play_hundle = PlayEffekseer3DEffect( _paralysis_handle );
		SetScalePlayingEffekseer3DEffect( play_effect.play_hundle, 5, 5, 5 );
		break;
	case EFFECT_CONFUSE:
		play_effect.play_hundle = PlayEffekseer3DEffect( _confuse_handle );
		SetScalePlayingEffekseer3DEffect( play_effect.play_hundle, 3, 3, 3 );
		pos.y += TILE_SIZE;
		break;
	case EFFECT_BUFF:
		play_effect.play_hundle = PlayEffekseer3DEffect( _buff_handle );
		SetScalePlayingEffekseer3DEffect( play_effect.play_hundle, 3, 3, 3 );
		break;
	case EFFECT_DEBUFF:
		play_effect.play_hundle = PlayEffekseer3DEffect( _debuff_handle );
		SetScalePlayingEffekseer3DEffect( play_effect.play_hundle, 3, 3, 3 );
		break;
	case EFFECT_SEALED:
		play_effect.play_hundle = PlayEffekseer3DEffect( _seal_handle );
		SetScalePlayingEffekseer3DEffect( play_effect.play_hundle, 5, 5, 5 );
		break;
	case EFFECT_SPORN:
		play_effect.play_hundle = PlayEffekseer3DEffect( _sporn_handle );
		SetScalePlayingEffekseer3DEffect( play_effect.play_hundle, 5, 5, 5 );
		break;
	case EFFECT_BOSS_ATTACK:
		play_effect.play_hundle = PlayEffekseer3DEffect( _boss_attack_handle );
		SetScalePlayingEffekseer3DEffect( play_effect.play_hundle, 10, 10, 10 );
		break;
	}
	play_effect.draw_pos = pos;
	
	SetPosPlayingEffekseer3DEffect( play_effect.play_hundle, play_effect.draw_pos.x, play_effect.draw_pos.y + TILE_SIZE, play_effect.draw_pos.z );
	SetRotationPlayingEffekseer3DEffect( play_effect.play_hundle, ( float )( rotate.x * DX_PI_F / 180 ), ( float )( rotate.y * DX_PI_F / 180 ), ( float )( rotate.z * DX_PI_F / 180 ) );
	
	_play_effect.push_back( play_effect );
}

void Effect::rePlayEffect( Vector pos, Vector rotate, int num ) {
	// エフェクトを再生する。
	switch ( _play_effect.at( num ).type ) {
	case EFFECT_HEAL:
		_play_effect.at( num ).play_hundle = PlayEffekseer3DEffect( _flame_handle );
		SetScalePlayingEffekseer3DEffect( _play_effect.at( num ).play_hundle, 3, 3, 3 );
		break;
	case EFFECT_STAMINA:
		_play_effect.at( num ).play_hundle = PlayEffekseer3DEffect( _stamina_handle );
		SetScalePlayingEffekseer3DEffect( _play_effect.at( num ).play_hundle, 1, 1, 1 );
		break;
	case EFFECT_FLAME:
		_play_effect.at( num ).play_hundle = PlayEffekseer3DEffect( _flame_handle );
		SetScalePlayingEffekseer3DEffect( _play_effect.at( num ).play_hundle, 5, 5, 5 );
		break;
	case EFFECT_SKILL1:
		_play_effect.at( num ).play_hundle = PlayEffekseer3DEffect( _skill_1_handle );
		SetScalePlayingEffekseer3DEffect( _play_effect.at( num ).play_hundle, 2, 2, 2 );
		break;
	case EFFECT_SKILL2:
		_play_effect.at( num ).play_hundle = PlayEffekseer3DEffect( _skill_2_handle );
		SetScalePlayingEffekseer3DEffect( _play_effect.at( num ).play_hundle, 3, 3, 3 );
		break;
	case EFFECT_SKILL3:
		_play_effect.at( num ).play_hundle = PlayEffekseer3DEffect( _skill_3_handle );
		SetScalePlayingEffekseer3DEffect( _play_effect.at( num ).play_hundle, 5, 5, 5 );
		break;
	case EFFECT_WIND:
		_play_effect.at( num ).play_hundle = PlayEffekseer3DEffect( _skill_4_handle );
		SetScalePlayingEffekseer3DEffect( _play_effect.at( num ).play_hundle, 1.5f, 1.5f, 1.5f );
		break;
	case EFFECT_POISON:
		_play_effect.at( num ).play_hundle = PlayEffekseer3DEffect( _poison_handle );
		SetScalePlayingEffekseer3DEffect( _play_effect.at( num ).play_hundle, 5, 5, 5 );
		break;
	case EFFECT_PARALYSIS:
		_play_effect.at( num ).play_hundle = PlayEffekseer3DEffect( _paralysis_handle );
		SetScalePlayingEffekseer3DEffect( _play_effect.at( num ).play_hundle, 5, 5, 5 );
		break;
	case EFFECT_CONFUSE:
		_play_effect.at( num ).play_hundle = PlayEffekseer3DEffect( _confuse_handle );
		SetScalePlayingEffekseer3DEffect( _play_effect.at( num ).play_hundle, 3, 3, 3 );
		pos.y += TILE_SIZE;
		break;
	case EFFECT_BUFF:
		_play_effect.at( num ).play_hundle = PlayEffekseer3DEffect( _buff_handle );
		SetScalePlayingEffekseer3DEffect( _play_effect.at( num ).play_hundle, 3, 3, 3 );
		break;
	case EFFECT_DEBUFF:
		_play_effect.at( num ).play_hundle = PlayEffekseer3DEffect( _debuff_handle );
		SetScalePlayingEffekseer3DEffect( _play_effect.at( num ).play_hundle, 3, 3, 3 );
		break;
	case EFFECT_SEALED:
		_play_effect.at( num ).play_hundle = PlayEffekseer3DEffect( _seal_handle );
		SetScalePlayingEffekseer3DEffect( _play_effect.at( num ).play_hundle, 5, 5, 5 );
		break;
	case EFFECT_SPORN:
		_play_effect.at( num ).play_hundle = PlayEffekseer3DEffect( _sporn_handle );
		SetScalePlayingEffekseer3DEffect( _play_effect.at( num ).play_hundle, 5, 5, 5 );
		break;
	case EFFECT_BOSS_ATTACK:
		_play_effect.at( num ).play_hundle = PlayEffekseer3DEffect( _boss_attack_handle );
		SetScalePlayingEffekseer3DEffect( _play_effect.at( num ).play_hundle, 10, 10, 10 );
		break;
	}
	_play_effect.at( num ).draw_pos = pos;
	SetPosPlayingEffekseer3DEffect( _play_effect.at( num ).play_hundle, _play_effect.at( num ).draw_pos.x, _play_effect.at( num ).draw_pos.y, _play_effect.at( num ).draw_pos.z );
	SetRotationPlayingEffekseer3DEffect( _play_effect.at( num ).play_hundle, ( float )( rotate.x * DX_PI_F / 180 ), ( float )( rotate.y * DX_PI_F / 180 ), ( float )( rotate.z * DX_PI_F / 180 ) );
	
}

void Effect::moveDrawPos( Vector draw_pos, int fllow_num ) {
	for ( unsigned int i = 0; i < _play_effect.size( ); i++ ) {
		if ( _play_effect.at( i ).fllow_num == fllow_num ) {
			switch ( _play_effect.at( i ).type ) {
			//case EFFECT_HEAL:
			case EFFECT_CONFUSE:
				draw_pos.y += TILE_SIZE;
				break;
			}
			_play_effect.at( i ).draw_pos = draw_pos;
		}
	}
}

void Effect::drawSupperFlameEffect( ) {
	FrameworkPtr fw  = Framework::getInstance( );
	ViewerPtr viewer = std::dynamic_pointer_cast< Viewer >( fw->getTask( typeid( Viewer ).name( ) ) );

	if ( _supper_flame_effect_draw == true ) {
		_supper_flame_effect_time++;
		_supper_flame_effect_index++;
		if ( _supper_flame_effect_index > 4 ) {
			_supper_flame_effect_index = 0;
		}
		viewer->drawGraph( 0, 0, _frame_dummy[ _supper_flame_effect_index ] );
		if ( _supper_flame_effect_time > SUPPER_FLAME_EFFECT_TIME ) {
			_supper_flame_effect_draw  = false;
			_supper_flame_effect_time  = 0;
			_supper_flame_effect_index = 0;
		}
	}
}

void Effect::startSupperFlameEffect( ) {
	_supper_flame_effect_draw = true;
}

int Effect::isPlayEndEffect( EFFECT_TYPE type, int fllow_num ) {
	for ( unsigned int i = 0; i < _play_effect.size( ); i++ ) {
		if ( _play_effect.at( i ).type == type && _play_effect.at( i ).fllow_num == fllow_num ) {
			if ( IsEffekseer3DEffectPlaying( _play_effect.at( i ).play_hundle ) != 0 ) {
				return i;
			} else {
				_play_effect.erase( _play_effect.begin( ) + i );
			}
		}
	}
	return -1;
}