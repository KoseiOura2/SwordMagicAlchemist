#pragma once
#include <string>


enum SKILL_ID {
	SKILL_NONE,
	ZANGEKI,
	ZANMETUHA,
	MATERIASWORD,
	SPEED_UP,
	SKILL_TYPE_NUM,
};

const int MAX_SKILL_NUM = SKILL_TYPE_NUM - 1;

struct SKILL_TYPE {
    SKILL_ID id;
	std::string name;

	SKILL_TYPE ( ) {
		this->id = SKILL_ID::SKILL_NONE;
		this->name = "";
	}

	virtual ~SKILL_TYPE( ) {
	
	}
};