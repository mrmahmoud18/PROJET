#pragma once

#include<vector>
#include<numeric>
#include<string>

class Component;

class Simulation
{
public:
	Simulation();
	~Simulation();
	static bool IsValidToSimulate(std::vector<Component*> ComponentList);
	static void Simulate(std::vector<Component*> ComponentList);
	static void ClearStatus(std::vector<Component*> ComponentList);
	static void TruthTable(std::vector<Component*> ComponentList);
	std::string CreatePossibilites(int NumberOfSwitches , std::string Possibilities="");

};

