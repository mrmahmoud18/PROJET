#pragma once

#include "Component.h"

#include <vector>

class Pin;

class Connection: public Component
{
private:
    Pin* m_InputPin;
    Pin* m_OutputPin;
    std::vector< std::pair<int,int> > m_Vertices;

public:
	Connection(Pin* r_InputPin, Pin* r_OutputPin, const std::vector< std::pair<int,int> >& r_Vertices);
	void Update(const std::vector< std::pair<int,int> >& r_Vertices);
	virtual void Operate();
	virtual void Draw(Interface* pInterface);
	virtual bool IsValidToOperate();
	virtual void ClearStatus();
};
