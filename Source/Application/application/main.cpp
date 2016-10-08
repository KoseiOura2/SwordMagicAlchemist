#include "DxLib.h"
#include "Framework.h"
#include "Viewer.h"
#include "Application.h"
#include "Keyboard.h"
#include "SoundManager.h"
#include "Sound.h"

bool main( ) {
	FrameworkPtr fw = Framework::getInstance( );

	TaskPtr keyboard = KeyboardPtr( new Keyboard( ) );
	fw->addTask( keyboard );

	TaskPtr viewer = ViewerPtr( new Viewer( ) );
	fw->addTask( viewer );

	TaskPtr sound_manager = SoundManagerPtr( new SoundManager( ) );
	fw->addTask( sound_manager );

	TaskPtr sound = SoundPtr( new Sound( ) );
	fw->addTask( sound );

	TaskPtr application = ApplicationPtr( new Application( ) );
	fw->addTask( application );


	return true;
}