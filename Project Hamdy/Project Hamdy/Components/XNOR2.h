#pragma once

#include "Gate.h"

class XNOR2 :public Gate
{
public:
	XNOR2(const GraphicsInfo &r_GfxInfo, std::string r_Label = "");
	virtual void Operate();
	virtual void Draw(Interface* pInterface) const;
	virtual void Copy(ApplicationManager* pManager) const;
};

