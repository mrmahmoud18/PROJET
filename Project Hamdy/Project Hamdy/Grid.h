#pragma once

#include<vector>
#include<queue>

class Component;
class Gate;
class SWITCH;
class LED;
class Connection;
class Pin;
class InputPin;

class Grid
{
public:
    Grid(int r_X, int r_Y);
    std::vector< std::pair<int,int> > FindPath(std::pair<int,int> Point1, std::pair<int,int> Point2);
    bool IsValidCenter(std::pair<int,int> Center) const;
    void AddGate(Gate* pGate);
    void AddSWITCH(SWITCH* pSWITCH);
    void AddLED(LED* pLED);
    void AddConnection(Connection* pConnection);
    void RemoveGate(Gate* pGate);
    void RemoveSWITCH(SWITCH* pSWITCH);
    void RemoveLED(LED* pLED);
    void RemoveConnection(Connection* pConnection);
	Component* GetComponentAt(std::pair<int, int> Point);
	Pin* GetPinAt(std::pair<int, int> Point);

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
	bool IsValidPoint(int r_TempX, int r_TempY, std::vector< std::vector<bool> >& r_Visited);
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
