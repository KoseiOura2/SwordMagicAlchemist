#pragma once
#include "Icon.h"
#include "Framework.h"
#include "Item.h"

PTR ( Alchemy );
PTR ( Item );
PTR ( NetworkController );
PTR ( Camera );
PTR ( ItemImage );

	const int BIG_ITEM_WIDTH = 150;
	const int BIG_ITEM_HEIGHT = 150;

	const int ALCHEMY_WIDTH = 350;
	const int ALCHEMY_POS_X = WINDOW_POS_X + WINDOW_WIDTH;
	//const int WINDOW_DIS = SCREEN_WIDTH / 2 - ( ALCHEMY_POS_X + ALCHEMY_WIDTH ) + ALCHEMY_WIDTH;
	const int WINDOW_DIS = ALCHEMY_WIDTH + 95;
	const int ALCHEMY_POS_Y = 90;

	const int MAX_RARITY = 5;	// �ō����A���e�B
	// �e���A���e�B���̃A�C�e����
	const int RARITY_ONE_MAX = 6;
	const int RARITY_TWO_MAX = 7;
	const int RARITY_THREE_MAX = 7;
	const int RARITY_FOUR_MAX = 9;
	const int RARITY_FIVE_MAX = 6;
	
	const int MAX_RECIPE_NUM = 8;	// �Œ�B���̃��V�s�̐�
	const int RECIPE_MAX_ITEM = 2;	// �B���Ɏg����A�C�e���̍ő吔
	
	const int ITEM_DIS = 200;
	const int GLAB_COUNT = 10;	// �������ł��ݏ�ԂɈڍs����܂ł̎���
	const int GLAB_ITEM_WIDTH = 256;	// �I�𒆂̃A�C�e���̉���
	const int GLAB_ITEM_HEIGHT = 256;	// �I�𒆂̃A�C�e���̏c��
	const Vector2 CHOICE_AREA_1 = Vector2( 300, 300 );
	const Vector2 CHOICE_AREA_2 = Vector2( SCREEN_WIDTH - CHOICE_AREA_1.x - BIG_ITEM_WIDTH, CHOICE_AREA_1.y );

	/*const int CONFIRMATION_WIDTH = 700;
	const int CONFIRMATION_HEIGHT = 190;
	const Vector2 CONFIRMATION_POS = Vector2( SCREEN_WIDTH / 2 - CONFIRMATION_WIDTH / 2, SCREEN_HEIGHT / 2 - CONFIRMATION_HEIGHT );*/

	const int POINT_POS_X = 100;	// �B���|�C���gX���W
	const int POINT_POS_Y = 200;	// �B���|�C���gY���W

	// �B���|�C���g�I����ʊ֘A
	const int POINT_SELECT_NUM = 3;	// �B���|�C���g������ۂ̑I�����̐�

	const int POINT_WINDOW_HEIGHT = 272;
	const int POINT_WINDOW_WIDTH = 448;
	const int POINT_WINDOW_POS_Y = SCREEN_HEIGHT / 2 - POINT_WINDOW_HEIGHT / 2;
	const int POINT_WINDOW_INTERVAL = SCREEN_WIDTH / POINT_SELECT_NUM;
	const int POINT_WINDOW_SPACE = ( SCREEN_WIDTH - ( POINT_WINDOW_INTERVAL * ( POINT_SELECT_NUM - 1 ) + POINT_WINDOW_WIDTH ) ) / 2;

	const int POINT_MESSAGE_WIDTH = 700;
	const int POINT_MESSAGE_POS_X = SCREEN_WIDTH / 2 - POINT_MESSAGE_WIDTH / 2;
	const int POINT_MESSAGE_POS_Y = 200;

	const int RESULT_ITEM_POS_X = POINT_MESSAGE_POS_X + POINT_MESSAGE_WIDTH - GLAB_ITEM_WIDTH;
	const int RESULT_ITEM_POS_Y = POINT_MESSAGE_POS_Y;
	const int POINT_NOT_TOUCH = -1;

	// �e�E�B���h�E���Ƃ̎g���B���|�C���g��
	const int POINT_ZERO = 0;
	const int POINT_ONE = 100;
	const int POINT_TWO = 500;

	const int STRING_DIS = 30;

	// �A�j���[�V�����֌W
	const float ANIM_SPEED = 0.5;
	const float ANIM_INIT_TIME = 8;
class Alchemy : public Icon {
public:
	Alchemy( Vector2 pos, ItemPtr item, NetworkControllerPtr network, CameraPtr camera, ItemImagePtr item_image );
	~Alchemy( );
	void touch( );
	void close( );
	void setAlchemyPoint( );
	void setStartFlag( bool flag );
	void AlchemyTile( );
	void init( );
private:
	struct CHOSEN_ITEM {
		Item::ITEM_DATA item;
		int num;	// item_list�ŉ��Ԗڂ̃A�C�e���Ȃ̂�
		int image;
		bool separate;	// ��x�w�𗣂������ǂ����̃t���O
		bool open;		// ���J���Ă��邩�ǂ���
		bool foot;

		CHOSEN_ITEM( ){
			this->num = -1;	//	���݂��Ȃ��A�C�e���̔ԍ������Ƃ�
			this->image = 0;
			this->open = false;
			this->foot = false;
		}
	};

	struct ALCHEMY_ITEM {
		Item::ITEM_DATA item;
		int image;
		Vector2 pos;
	//	bool chosen;

		ALCHEMY_ITEM( ){
			this->image = 0;
			this->pos = Vector2( );
			//this->chosen = false;
		}
		
		ALCHEMY_ITEM( int image, Vector2 pos ) {
			this->image = image;
			this->pos = pos;
			//this->chosen = false;
		}
	};
private:
	void createItem( int alchemy_point );	// �B�����ɌĂ΂��֐�
	ITEM_ID itemLottery( int num[ MAX_RARITY ] );
	void alchemyWindow( );
	void setAlchemyItem( );
	void selectAlchemyPoint( );
	void itemScroll( );
	void itemSelect( );
	void createConfirmationWindow( );
	void drawAlchemy( );
	void drawItem( );
	void cancelAlchemy( );
	void createItemObtain( );
	ITEM_ID randamAlchemy( int sum_rarity, int alchemy_point );
	void result( );
	void startAnim( );
	void potAlchemyAnim( );
	bool isRecipe( );	// �Œ�B�����ǂ����𔻒f
private:
	ItemPtr _item;
	NetworkControllerPtr _network;
	CameraPtr _camera;
	ItemImagePtr _item_image;
	std::vector< Item::ITEM_DATA > _item_list; // �A�C�e���E�B���h�E�\���p
	//std::vector< ALCHEMY_ITEM > _alchemy_item; // �A�C�e���X�N���[���p�̕\���p
	ALCHEMY_ITEM _alchemy_item [ MAX_ITEM_NUM ];	// �莝���̃A�C�e��
	ALCHEMY_ITEM _drag_item;	// �h���b�O���̃A�C�e��
	Item::ITEM_DATA _foot_item;	// �A�C�e���E�B���h�E�\���p
	CHOSEN_ITEM _chosen_item_1;
	CHOSEN_ITEM _chosen_item_2;
	ITEM_ID _create_item;	// �B���ł���A�C�e����ۑ����Ă���
	bool _camera_check;	// �J�����̓������I��������ǂ������m�F���邩�ǂ���
	int _pot;
	int _alchemy_window;
	int _point_window_rank1;
	int _point_window_close_rank1;
	int _point_window_rank2;
	int _point_window_close_rank2;
	int _point_window_rank3;
	int _point_window_close_rank3;
	int _message_window;
	int _plus;
	int _point;	// �B���|�C���g
	bool _foot_open;
	int _confirmation_window;	// �m�F���Ɏg���E�B���h�E
	bool _item_set_flag;
	bool _drag;	// �A�C�e�����h���b�O���Ă邩�ǂ���
	bool _remove_area_1;	// ��x�I�������A�C�e�����h���b�O���ăG���A����o����true�ɂ���
	bool _remove_area_2;	
	bool _separate;
	bool _result_flag;
	bool _anim_flag;	// ����N�����̃A�j���[�V�����I���t���O
	bool _move_flag;	// �J�����������o�����ǂ���
	bool _start_flag;	// ����N�����ɗ��Ă�t���O
	bool _performance_finish;	// ���o���I��������ǂ���
	bool _randam_alchemy;	// �����_���B�����ǂ���
	int _item_drag_num;	// �h���b�O���Ă���A�C�e���̔ԍ�
	Vector2 _old_pos;	// �h���b�O�O�̈ʒu��ۑ����Ă���
	int _wait_count;
	float _anim_count;
	float _pot_anim_total_time;	// �A�j���[�V�����̑�����
};

