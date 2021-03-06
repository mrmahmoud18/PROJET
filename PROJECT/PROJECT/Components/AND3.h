#pragma once

#include "Gate.h"

class AND3: public Gate
{
public:
	AND3(const GraphicsInfo &r_GfxInfo, std::string r_Label = "");
	virtual void Operate();
	virtual void Draw(Interface* pInterface);
};

