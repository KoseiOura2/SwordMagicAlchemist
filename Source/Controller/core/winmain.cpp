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
	// Effekseerを終了する。
	Effkseer_End();
	Framework::finalize( );
	DxLib_End() ;				// ＤＸライブラリ使用の終了処理

	return 0 ;				// ソフトの終了 
}

int initialize( ) {
	srand( ( unsigned int ) time ( NULL ) );

	//画面サイズ設定 1920 * 1080固定で
	SetGraphMode( 1920, 1080, 32 );
	SetMouseDispFlag( TRUE );
	/*if ( SetGraphMode( 1920, 1080, 32 ) != DX_CHANGESCREEN_OK ) {
		 return -1;
	}*/
	
	//ウィンドウモード
	ChangeWindowMode( TRUE );
	SetUseDirect3DVersion( DX_DIRECT3D_9 );
	SetDoubleStartValidFlag( TRUE ); 
	SetAlwaysRunFlag( TRUE );
	if ( DxLib_Init( ) == -1 ) {		// ＤＸライブラリ初期化処理
		return -1 ;			// エラーが起きたら直ちに終了
	}
	//SetDrawArea( 0, 0, 1920 / 2, 1080 / 2 );
	SetUseZBuffer3D( TRUE );
	SetWriteZBuffer3D( TRUE );
	SetDrawScreen( DX_SCREEN_BACK );
	SetCameraNearFar( 20.0f, 500.0f );
	SetUseBackCulling( TRUE );
	//-----------ライト------------
	SetUseLighting( FALSE );
	//ChangeLightTypeDir( VGet( 0.0f, -1.0f, 0.0f ) );
	//CreateDirLightHandle( VGet( 0.0f, 1.0f, 0.0f ) );
	/*CreateDirLightHandle( VGet( 1.0f, 0.0f, 0.0f ) );
	CreateDirLightHandle( VGet( -1.0f, 0.0f, 0.0f ) );*/
	// Effekseer用設定
	Effkseer_Init(2000);
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// Zバッファは上で設定しているので除外
	Framework::initialize( );
	return 0;
}