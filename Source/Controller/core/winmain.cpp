#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "Framework.h"
#include <time.h>
int initialize( );
bool main( );
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {

	if ( initialize( ) == -1 ) {
		return -1;
	}

	if ( main( ) ){
		Framework::getInstance( )->run( );
	}
	// Effekseer���I������B
	Effkseer_End();
	Framework::finalize( );
	DxLib_End() ;				// �c�w���C�u�����g�p�̏I������

	return 0 ;				// �\�t�g�̏I�� 
}

int initialize( ) {
	srand( ( unsigned int ) time ( NULL ) );

	//��ʃT�C�Y�ݒ� 1920 * 1080�Œ��
	SetGraphMode( 1920, 1080, 32 );
	SetMouseDispFlag( TRUE );
	/*if ( SetGraphMode( 1920, 1080, 32 ) != DX_CHANGESCREEN_OK ) {
		 return -1;
	}*/
	
	//�E�B���h�E���[�h
	ChangeWindowMode( TRUE );
	SetUseDirect3DVersion( DX_DIRECT3D_9 );
	SetDoubleStartValidFlag( TRUE ); 
	SetAlwaysRunFlag( TRUE );
	if ( DxLib_Init( ) == -1 ) {		// �c�w���C�u��������������
		return -1 ;			// �G���[���N�����璼���ɏI��
	}
	//SetDrawArea( 0, 0, 1920 / 2, 1080 / 2 );
	SetUseZBuffer3D( TRUE );
	SetWriteZBuffer3D( TRUE );
	SetDrawScreen( DX_SCREEN_BACK );
	SetCameraNearFar( 20.0f, 500.0f );
	SetUseBackCulling( TRUE );
	//-----------���C�g------------
	SetUseLighting( FALSE );
	//ChangeLightTypeDir( VGet( 0.0f, -1.0f, 0.0f ) );
	//CreateDirLightHandle( VGet( 0.0f, 1.0f, 0.0f ) );
	/*CreateDirLightHandle( VGet( 1.0f, 0.0f, 0.0f ) );
	CreateDirLightHandle( VGet( -1.0f, 0.0f, 0.0f ) );*/
	// Effekseer�p�ݒ�
	Effkseer_Init(2000);
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// Z�o�b�t�@�͏�Őݒ肵�Ă���̂ŏ��O
	Framework::initialize( );
	return 0;
}