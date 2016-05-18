#include "Grid.h"
#include"Components/LED.h"
#include "Components/Gate.h"
#include "Components/SWITCH.h"

Grid::Grid(int r_x, int r_y) {
	Xsize = r_x;
	Ysize = r_y;
	Nodes.resize(Xsize, std::vector<Node>(Ysize));
	GridInitializion();
}

std::vector< std::pair<int, int> > Grid::FindPath(std::pair<int, int> Point1, std::pair<int, int> Point2)
{
	int count = 0;
	std::queue<Node> TempQueue;
	//std::vector< std::vector<bool> >Visited(Xsize, std::vector <bool>(Ysize, false));
	bool **Visited = new bool* [Xsize];
	for (int i = 0; i < Xsize; i++)
	{
		Visited[i] = new bool[Ysize];
	}
	for (int i = 0; i < Xsize; i++)
	{
		for (int j = 0; j < Ysize; j++)
		{
			Visited[i][j] = false;
		}
	}

	bool PathFounded = false;
	int TempArrayX[4] = { 0,0,1,-1 }, TempArrayY[4] = { 1,-1,0,0 };
	int Tempy, Tempx, CurrentX, CurrentY;
	TempQueue.push(Nodes[Point1.first][Point1.second]);
	Visited[Point1.first][Point1.second] = true;
	while (!TempQueue.empty() && !PathFounded)
	{
		CurrentX = TempQueue.front().m_X;
		CurrentY = TempQueue.front().m_Y;
		for (int z = 0; z < 4; z++)
		{
			count++;
			Tempx = TempArrayX[z] + CurrentX;
			Tempy = TempArrayY[z] + CurrentY;
			if (IsValidPoint(Tempx, Tempy, Visited))
			{
                if (Tempx == Point2.first && Tempy == Point2.second)
                {
                    PathFounded = true;
                    Nodes[Tempx][Tempy].m_XParent = CurrentX;
                    Nodes[Tempx][Tempy].m_Yparent = CurrentY;
                    ClearQueue(TempQueue);
                    break;
                }
				if (ISValidState(Tempx, Tempy, TempQueue))
				{
					Nodes[Tempx][Tempy].m_XParent = CurrentX;
					Nodes[Tempx][Tempy].m_Yparent = CurrentY;
					Visited[Tempx][Tempy] = true;
					TempQueue.push(Nodes[Tempx][Tempy]);
				}
			}
		}
		if (!TempQueue.empty())
		{
			TempQueue.pop();
		}
	}
	std::cout << count<<std::endl;
	if(!PathFounded)
        throw;
    return CreateThePath(Point1, Point2);
}

std::vector< std::pair<int, int> > Grid::CreateThePath(std::pair<int, int> Point1, std::pair<int, int> Point2)
{
	std::vector< std::pair<int, int> >Path;
	Path.push_back(std::make_pair(Point2.first, Point2.second));
	int CurrentX = Point2.first, CurrentY = Point2.second, Tempy, Tempx;
	Tempx = CurrentX;
	Tempy = CurrentY;
	CurrentX = Nodes[Tempx][Tempy].m_XParent;
	CurrentY = Nodes[Tempx][Tempy].m_Yparent;
	do
	{
		while ((Tempx != Point1.first || Tempy != Point1.second) && Tempx == CurrentX)
		{
			Tempx = CurrentX;
			Tempy = CurrentY;
			CurrentX = Nodes[Tempx][Tempy].m_XParent;
			CurrentY = Nodes[Tempx][Tempy].m_Yparent;
			if (Tempx != CurrentX)
			{
				Path.push_back(std::make_pair(Tempx, Tempy));
			}
		}
		while ((Tempx != Point1.first || Tempy != Point1.second) && Tempx != CurrentX)
		{
			Tempx = CurrentX;
			Tempy = CurrentY;
			CurrentX = Nodes[Tempx][Tempy].m_XParent;
			CurrentY = Nodes[Tempx][Tempy].m_Yparent;
			if (Tempx == CurrentX)
			{
				Path.push_back(std::make_pair(Tempx, Tempy));
			}
		}

	} while (Tempx != Point1.first || Tempy != Point1.second);
	if (!(Point1.first == Path.back().first && Point1.second == Path.back().second))
	{
		Path.push_back(std::make_pair(Point1.first, Point1.second));
	}
	ClearParent();
	return Path;
}

bool Grid::IsValidPoint(int r_Tempx, int r_Tempy, bool**r_Visited /*std::vector< std::vector<bool> > &r_Visited*/)
{
	return (r_Tempx < Xsize && r_Tempx>0 && r_Tempy < Ysize  && r_Tempy>0 && !r_Visited[r_Tempx][r_Tempy]
		&& Nodes[r_Tempx][r_Tempy].m_Stat != Grid::Node::GATE && Nodes[r_Tempx][r_Tempy].m_Stat != Grid::Node::CONNECTIONFULL);
}

bool Grid::ISValidState(int r_Tempx, int r_Tempy, std::queue<Grid::Node> r_TempQueue)
{
	return ((r_Tempy == r_TempQueue.front().m_Y && Nodes[r_Tempx][r_Tempy].m_Stat != Grid::Node::HORIZONTAL)
		|| (r_Tempx == r_TempQueue.front().m_X && Nodes[r_Tempx][r_Tempy].m_Stat != Grid::Node::VERTICAL));
}

void Grid::ClearQueue(std::queue<Grid::Node>& r_TempQueue)
{
	while (!r_TempQueue.empty())
	{
		r_TempQueue.pop();
	}
}

void Grid::ClearParent()
{
	for (int i = 0; i < Xsize; i++)
	{
		for (int j = 0; j < Ysize; j++)
		{
			Nodes[i][j].m_XParent = 0;
			Nodes[i][j].m_Yparent = 0;
		}
	}
}

void Grid::GridInitializion() {
	for (int i = 0; i < Xsize; i++)
	{
		for (int j = 0; j < Ysize; j++)
		{
			Nodes[i][j].m_Stat = Node::NOTHING;
			Nodes[i][j].m_X = i;
			Nodes[i][j].m_Y = j;
			Nodes[i][j].pComp = NULL;
			Nodes[i][j].pPin = NULL;
		}
	}
}

bool Grid::IsValidCenter(std::pair<int, int> r_componentCenter)
{
    if(-6+r_componentCenter.first <0 || -6+r_componentCenter.second <0 || 6+r_componentCenter.first > Xsize || 6+r_componentCenter.second >Ysize)
    {
        return false;
    }
	for (int i = -6; i <= 6; i++)
	{
		for (int j = -6; j <= 6; j++)
		{
			if (Nodes[i + r_componentCenter.first][j + r_componentCenter.second].m_Stat != Node::NOTHING)
			{
				return false;
			}
		}
	}
	return true;
}

void Grid::AddSwitch(std::pair<int, int> r_Center, Component * r_pComp)
{
	for (int i = -3; i <= 3; i++)
	{
		for (int j = -2; j <= 2; j++)
		{
			Nodes[i + r_Center.first][j + r_Center.second].m_Stat = Node::GATE;
			Nodes[i + r_Center.first][j + r_Center.second].pComp = r_pComp;
		}
	}
	Nodes[r_Center.first + 4][r_Center.second].m_Stat = Node::PINPOINT;
	Nodes[r_Center.first + 4][r_Center.second].pPin = dynamic_cast<SWITCH*>(r_pComp)->GetOutputPin();
	for (int i = -6; i <= 6; i++)
	{
		for (int j = -6; j <= 6; j++)
		{
			if (Nodes[i + r_Center.first][j + r_Center.second].m_Stat == Node::NOTHING)
			{
				Nodes[i + r_Center.first][j + r_Center.second].m_Stat = Node::NOCONNECTION;
			}
		}
	}
}

void Grid::AddLed(std::pair<int, int> r_Center, Component * r_pComp)
{
	for (int i = -3; i <= 3; i++)
	{
		for (int j = -2; j <= 2; j++)
		{
			Nodes[i + r_Center.first][j + r_Center.second].m_Stat = Node::GATE;
			Nodes[i + r_Center.first][j + r_Center.second].pComp = r_pComp;
		}
	}
	Nodes[r_Center.first - 4][r_Center.second].m_Stat = Node::PINPOINT;
	Nodes[r_Center.first - 4][r_Center.second].pPin = dynamic_cast<LED*>(r_pComp)->GetInputPin();
	for (int i = -6; i <= 6; i++)
	{
		for (int j = -6; j <= 6; j++)
		{
			if (Nodes[i + r_Center.first][j + r_Center.second].m_Stat == Node::NOTHING)
			{
				Nodes[i + r_Center.first][j + r_Center.second].m_Stat = Node::NOCONNECTION;
			}
		}
	}
}

void Grid::AddGate(std::pair<int, int> r_Center, Component * r_pComp)
{
	for (int i = -3; i <= 3; i++)
	{
		for (int j = -2; j <= 2; j++)
		{
			Nodes[i + r_Center.first][j + r_Center.second].m_Stat = Node::GATE;
			Nodes[i + r_Center.first][j + r_Center.second].pComp = r_pComp;
		}
	}

	Nodes[r_Center.first + 4][r_Center.second].m_Stat = Node::PINPOINT;
	Nodes[r_Center.first - 4][r_Center.second].m_Stat = Node::PINPOINT;
	Nodes[r_Center.first - 4][r_Center.second + 1].m_Stat = Node::PINPOINT;
	Nodes[r_Center.first - 4][r_Center.second - 1].m_Stat = Node::PINPOINT;

	Nodes[r_Center.first + 4][r_Center.second].pPin = dynamic_cast<Gate*>(r_pComp)->GetOutputPin();
	Nodes[r_Center.first + 4][r_Center.second].pComp = r_pComp;
	std::vector<InputPin>& temp = dynamic_cast<Gate*>(r_pComp)->GetInputPins();
	std::vector<InputPin>::iterator min = temp.begin();
	std::vector<InputPin>::iterator it = temp.begin();
	for (unsigned int i = 1; i < temp.size(); i++)
	{
		while (it != temp.end())
		{
			if (min->GetCenter().first > it->GetCenter().first)
			{
				min = it;
			}
			it++;
		}
		std::swap(min, temp.begin()+i);
		min = it = temp.begin() + i;
	}

	if (temp.size() == 2)
	{
		Nodes[r_Center.first - 4][r_Center.second - 1].pPin = &(temp[0]);
		Nodes[r_Center.first - 4][r_Center.second - 1].pComp = r_pComp;
		Nodes[r_Center.first - 4][r_Center.second + 1].pPin = &(temp[1]);
		Nodes[r_Center.first - 4][r_Center.second + 1].pComp = r_pComp;
	}
	else
	{
		Nodes[r_Center.first - 4][r_Center.second - 1].pPin = &(temp[0]);
		Nodes[r_Center.first - 4][r_Center.second - 1].pComp = r_pComp;
		Nodes[r_Center.first - 4][r_Center.second].pPin = &(temp[1]);
		Nodes[r_Center.first - 4][r_Center.second].pComp = r_pComp;
		Nodes[r_Center.first - 4][r_Center.second + 1].pPin = &(temp[2]);
		Nodes[r_Center.first - 4][r_Center.second + 1].pComp = r_pComp;
	}
	for (int i = -6; i <= 6; i++)
	{
		for (int j = -6; j <= 6; j++)
		{
			if (Nodes[i + r_Center.first][j + r_Center.second].m_Stat == Node::NOTHING)
			{
				Nodes[i + r_Center.first][j + r_Center.second].m_Stat = Node::NOCONNECTION;
			}
		}
	}
}

void Grid::AddConnection(const std::vector< std::pair<int, int> >& Path, Component * r_pComp)
{
	int TempY, TempX,Count=1;
	TempX = Path.front().first;
	TempY = Path.front().second;
	do
	{
		while ((TempX != Path.back().first || TempY != Path.back().second) && TempX == Path[Count].first)
		{
			if (Nodes[TempX][TempY].m_Stat == Grid::Node::NOTHING || Nodes[TempX][TempY].m_Stat == Grid::Node::NOCONNECTION)
			{
				Nodes[TempX][TempY].m_Stat = Grid::Node::VERTICAL;
			}
			if (Nodes[TempX][TempY].m_Stat == Grid::Node::HORIZONTAL)
			{
				Nodes[TempX][TempY].m_Stat = Grid::Node::CONNECTIONFULL;
			}
			if (Nodes[TempX][TempY].pComp == NULL)
			{
				Nodes[TempX][TempY].pComp = r_pComp;
			}
			else
			{
				Nodes[TempX][TempY].pComp = NULL;
			}

			TempY++;
			if (TempY == Path[Count].second)
			{
				Count++;
			}
		}
		while ((TempX != Path.back().first || TempY != Path.back().second) && TempX != Path[Count].second)
		{
			if (Nodes[TempX][TempY].m_Stat == Grid::Node::NOTHING || Nodes[TempX][TempY].m_Stat == Grid::Node::NOCONNECTION)
			{
				Nodes[TempX][TempY].m_Stat = Grid::Node::HORIZONTAL;
			}
			if (Nodes[TempX][TempY].m_Stat == Grid::Node::VERTICAL)
			{
				Nodes[TempX][TempY].m_Stat = Grid::Node::CONNECTIONFULL;
			}
			if (Nodes[TempX][TempY].pComp == NULL)
			{
				Nodes[TempX][TempY].pComp = r_pComp;
			}
			else
			{
				Nodes[TempX][TempY].pComp = NULL;
			}
			TempX++;
			if (TempX == Path[Count].first)
			{
				Count++;
			}
		}

	} while (TempX != Path.back().first || TempY != Path.back().second);
}

void Grid::DeleteComponent(std::pair<int, int> r_componentCenter)
{
	for (int i = -6; i <= 6; i++)
	{
		for (int j = -6; j <= 6; j++)
		{
			if (Nodes[i + r_componentCenter.second][j + r_componentCenter.first].m_Stat == Node::GATE || Nodes[i + r_componentCenter.second][j + r_componentCenter.first].m_Stat == Node::NOCONNECTION || Nodes[i + r_componentCenter.second][j + r_componentCenter.first].m_Stat == Node::PINPOINT)
			{
				Nodes[i + r_componentCenter.second][j + r_componentCenter.first].m_Stat = Node::NOTHING;
				Nodes[i + r_componentCenter.second][j + r_componentCenter.first].pComp = NULL;
				Nodes[i + r_componentCenter.second][j + r_componentCenter.first].pPin = NULL;
			}
		}
	}
}

void Grid::DeleteConnection(std::vector< std::pair<int, int> > Path)
{
	int TempY, TempX, Count = 1;
	TempX = Path.front().first;
	TempY = Path.front().second;
	do
	{
		while ((TempX != Path.back().first || TempY != Path.back().second) && TempX == Path[Count].first)
		{
			if (Nodes[TempX][TempY].m_Stat == Grid::Node::CONNECTIONFULL )
			{
				Nodes[TempX][TempY].m_Stat = Grid::Node::HORIZONTAL;
			}
			if (Nodes[TempX][TempY].m_Stat == Grid::Node::VERTICAL)
			{
				Nodes[TempX][TempY].m_Stat = Grid::Node::NOCONNECTION;
			}
			if (Nodes[TempX][TempY].pComp !=NULL)
			{
				Nodes[TempX][TempY].pComp = NULL;
			}
			else
			{
				if (Nodes[TempX + 1][TempY].pComp == NULL || Nodes[TempX - 1][TempY].pComp == NULL)
				{
					Nodes[TempX][TempY].pComp = Nodes[TempX][TempY + 1].pComp;
				}
				else
				{
					Nodes[TempX][TempY].pComp = Nodes[TempX + 1][TempY].pComp;
				}
			}

			TempY++;
			if (TempY == Path[Count].second)
			{
				Count++;
			}
		}
		while ((TempX != Path.back().first || TempY != Path.back().second) && TempX != Path[Count].first)
		{
			if (Nodes[TempX][TempY].m_Stat == Grid::Node::CONNECTIONFULL )
			{
				Nodes[TempX][TempY].m_Stat = Grid::Node::VERTICAL;
			}
			if (Nodes[TempX][TempY].m_Stat == Grid::Node::HORIZONTAL)
			{
				Nodes[TempX][TempY].m_Stat = Grid::Node::NOCONNECTION;
			}
			if (Nodes[TempX][TempY].pComp != NULL)
			{
				Nodes[TempX][TempY].pComp = NULL;
			}
			else
			{
				if (Nodes[TempX + 1][TempY].pComp == NULL || Nodes[TempX - 1][TempY].pComp == NULL)
				{
					Nodes[TempX][TempY].pComp = Nodes[TempX][TempY + 1].pComp;
				}
				else
				{
					Nodes[TempX][TempY].pComp = Nodes[TempX + 1][TempY].pComp;
				}
			}
			TempX++;
			if (TempX == Path[Count].first)
			{
				Count++;
			}
		}

	} while (TempX != Path.back().first || TempY != Path.back().second);
}

Component * Grid::GetComponent(std::pair<int, int> r_Point)
{
	return Nodes[r_Point.first][r_Point.second].pComp;
}

Pin * Grid::GetPin(std::pair<int, int> r_Point)
{
	return Nodes[r_Point.first][r_Point.second].pPin;
}


