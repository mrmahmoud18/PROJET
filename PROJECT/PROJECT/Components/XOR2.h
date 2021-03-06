#pragma once

#include "Gate.h"

class XOR2 : public Gate
{
public:
	XOR2(const GraphicsInfo &r_GfxInfo, std::string r_Label = "");
	virtual void Operate();
	virtual void Draw(Interface* pInterface);
};

