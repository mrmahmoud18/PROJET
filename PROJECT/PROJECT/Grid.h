#pragma once

#include<vector>
#include<queue>
#include<algorithm>

class Component;
class Pin;
class InputPin;
class SWITCH;
class LED;
class Gate;

class Grid
{
public:
    Grid(int r_X, int r_Y);
    std::vector< std::pair<int,int> > FindPath(std::pair<int,int> Point1, std::pair<int,int> Point2);
    bool IsValidCenter(std::pair<int,int> Center);
	void AddSwitch(std::pair<int, int> r_Center, SWITCH * r_pComp);
	void AddLed(std::pair<int, int> r_Center, LED * r_pComp);
	void AddGate(std::pair<int, int> r_Center, Gate * r_pComp);
	void AddConnection(const std::vector< std::pair<int,int> >& Path, Component* r_pComp);
    void DeleteComponent(std::pair<int,int> Center);
    void DeleteConnection(std::vector< std::pair<int,int> > Path);
	Component* GetComponent(std::pair<int, int> r_Point);
	Pin* GetPin(std::pair<int, int> r_Point);

private:
	int Xsize, Ysize;
    struct Node
    {
        int m_X, m_Y , m_XParent ,m_Yparent;
        enum {NOCONNECTION, CONNECTIONFULL, VERTICAL ,HORIZONTAL ,GATE ,PINPOINT ,NOTHING} m_Stat;
		Component* pComp;
		Pin* pPin;
    };
    std::vector< std::vector<Node> > Nodes;

	std::vector< std::pair<int, int> > CreateThePath(std::pair<int, int> Point1, std::pair<int, int> Point2);
	bool IsValidPoint(int r_TempX, int r_TempY, bool**r_Visited);
	bool ISValidState(int r_Tempx, int r_TempY, std::queue< Grid::Node>r_TempQueue);
	void ClearQueue(std::queue < Grid::Node >& r_TempQueue);
	void ClearParent();
	void GridInitializion();
};

/*

-------------
-CCCCCCCCCCC-
-CCCCCCCCCCC-
-CCCCCCCCCCC-
-CCGGGGGGGCC-
-C*GGGGGGGCC-
-C*GGGGGGG*C-
-C*GGGGGGGCC-
-CCGGGGGGGCC-
-CCCCCCCCCCC-
-CCCCCCCCCCC-
-CCCCCCCCCCC-
-------------

*/
