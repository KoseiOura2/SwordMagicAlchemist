#pragma once
#include <string>


enum ITEM_ID {
	ITEM_NONE,
	HERB1,			// ��
	HERB2,			// ���
	HERB3,			// �����
	HERB4,			// ���ʂ���
	HERB5,			// �Ȃ��葐
	HERB6,			// �Ԃ��Ƃё�
	HERB7,			// �ő�
	HERB8,			// ���тꑐ
	HERB9,			// ���f��
	MEAT1,			// �b�̓�
	MEAT2,			// �傫�ȓ�
	MEAT3,			// ����X�����[�X
	MEAT4,			// ��������
	RING1,			// ���ʂ̎w��
	RING2,			// �����̎w��
	RING3,			// �����̎w��
	RING4,			// ���̎w��
	RING5,			// �n���̎w��
	RING6,			// 㩏����̎w��
	ROD1,			// �؂̏�
	ROD2,			// ���̏�
	ROD3,			// �����̏�
	ROD4,			// ���[�v�̏�
	SWORD1,			// ���̌�
	SWORD2,			// �����̌�
	SWORD3,			// ������
	SWORD4,			// �g���C�\�[�h
	STONE1,			// �Ă���
	STONE2,			// ������
	STONE3,			// �����̐�
	STONE4,			// ��Ղ̐�
	STONE5,			// 㩉󂵂̐�
	STONE6,			// �喂����
	GARBAGE1,		// ����
	GARBAGE2,		// �㎿�Ȃ���
	ITEM_TYPE_NUM,
};

const int MAX_ITEM_TYPE = ITEM_TYPE_NUM - 1;

const std::string ITEM_NAME_LIST[ ] = {
	"NONE",
	"��",
	"���",
	"�����",
	"���ʂ���",
	"�Ȃ��葐",
	"�Ԃ��Ƃё�",
	"�ő�",
	"���тꑐ",
	"���f��",
	"�b�̓�",
	"�傫�ȓ�",
	"����X�����[�X",
	"��������",
	"���ʂ̎w��",
	"�����̎w��",
	"�����̎w��",
	"���̎w��",
	"�n���̎w��",
	"㩏����̎w��",
	"�؂̏�",
	"���̏�",
	"�����̏�",
	"���[�v�̏�",
	"���̌�",
	"���R�m�̌�",
	"������",
	"�g���C�\�[�h",
	"�Ă���",
	"������",
	"�����̐�",
	"��Ղ̐�",
	"㩉󂵂̐�",
	"�喂����",
	"����",
	"�㎿�Ȃ���",
};

struct ITEM_TYPE {
	ITEM_ID id;
	std::string name;
	int amount;

	ITEM_TYPE( ) {
		this->id     = ITEM_NONE;
		this->name   = ITEM_NAME_LIST[ ITEM_NONE ];
		this->amount = 1;
	}

	ITEM_TYPE( ITEM_ID id ) {
		this->id     = id;
		this->name   = ITEM_NAME_LIST[ id ];
		this->amount = 1;
	}

	virtual ~ITEM_TYPE( ) {

	}
};