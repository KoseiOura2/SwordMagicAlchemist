#pragma once
#include "Icon.h"

PTR ( Option )

class Option : public Icon {
public:
	Option( Vector2 pos );
	~Option( );
	void touch( );
};

