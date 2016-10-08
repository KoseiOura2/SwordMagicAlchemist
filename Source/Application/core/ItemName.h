#pragma once
#include <string>


enum ITEM_ID {
	ITEM_NONE,
	HERB1,			// 薬草
	HERB2,			// 上薬草
	HERB3,			// 特上薬草
	HERB4,			// 見通し草
	HERB5,			// なおり草
	HERB6,			// ぶっとび草
	HERB7,			// 毒草
	HERB8,			// しびれ草
	HERB9,			// 幻惑草
	MEAT1,			// 獣の肉
	MEAT2,			// 大きな肉
	MEAT3,			// 特上スワロース
	MEAT4,			// 腐った肉
	RING1,			// 普通の指輪
	RING2,			// 増命の指輪
	RING3,			// 加撃の指輪
	RING4,			// 守りの指輪
	RING5,			// 創造の指輪
	RING6,			// 罠除けの指輪
	ROD1,			// 木の杖
	ROD2,			// 炎の杖
	ROD3,			// 豪炎の杖
	ROD4,			// ワープの杖
	SWORD1,			// 銅の剣
	SWORD2,			// 聖命の剣
	SWORD3,			// 魔導剣
	SWORD4,			// トライソード
	STONE1,			// 焼け石
	STONE2,			// 魔導石
	STONE3,			// 復活の石
	STONE4,			// 奇跡の石
	STONE5,			// 罠壊しの石
	STONE6,			// 大魔導石
	GARBAGE1,		// ごみ
	GARBAGE2,		// 上質なごみ
	ITEM_TYPE_NUM,
};

const int MAX_ITEM_TYPE = ITEM_TYPE_NUM - 1;

const std::string ITEM_NAME_LIST[ ] = {
	"NONE",
	"薬草",
	"上薬草",
	"特上薬草",
	"見通し草",
	"なおり草",
	"ぶっとび草",
	"毒草",
	"しびれ草",
	"幻惑草",
	"獣の肉",
	"大きな肉",
	"特上スワロース",
	"腐った肉",
	"普通の指輪",
	"増命の指輪",
	"加撃の指輪",
	"守りの指輪",
	"創造の指輪",
	"罠除けの指輪",
	"木の杖",
	"炎の杖",
	"豪炎の杖",
	"ワープの杖",
	"銅の剣",
	"聖騎士の剣",
	"魔導剣",
	"トライソード",
	"焼け石",
	"魔導石",
	"復活の石",
	"奇跡の石",
	"罠壊しの石",
	"大魔導石",
	"ごみ",
	"上質なごみ",
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