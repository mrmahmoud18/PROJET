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
	const std::vector< std::pair<int,int> >& GetPath();
	virtual std::set<Component*> GetAssociatedComponents();
	virtual void ShiftBy(std::pair<int,int> Delta);
	virtual std::pair<int,int> GetCenter() const;
	virtual void GetIn(Grid* SimGrid);
	virtual void GetOut(Grid* SimGrid);
	virtual void Operate();
	virtual void Draw(Interface* pInterface) const;
    virtual void Copy(ApplicationManager* pManager) const;
};
