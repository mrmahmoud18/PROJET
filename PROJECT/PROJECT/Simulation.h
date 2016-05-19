#pragma once

#include<vector>
#include<numeric>
#include <sstream>

class Component;
class LED;
class SWITCH;

class Simulation
{
public:
	Simulation();
	~Simulation();
	static bool IsValidToSimulate(std::vector<Component*> ComponentList);
	static void Simulate(std::vector<Component*> ComponentList);
	static void ClearStatus(std::vector<Component*> ComponentList);
	//static void TruthTable(std::vector<Component*> ComponentList);
	static void Simulation::CreatePossibilites(int NumberOfSwitches, std::string Possibilities = "");
	static std::vector<Pin::Status> StringToStatus(std::string s);
	static std::vector<SWITCH*> GetSWITCHList();
	static std::vector<LED*> GetLEDList();
	static void SetSWITCHStatus(std::vector<SWITCH*> v ,std::vector<Pin::Status>Values);
	static void GetLEDStatus(std::vector<LED*> v);
};

