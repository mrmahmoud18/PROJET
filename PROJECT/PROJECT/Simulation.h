#pragma once

#include<vector>
#include<numeric>

class Component;

class Simulation
{
public:
	Simulation();
	~Simulation();
	static bool IsValidToSimulate(std::vector<Component*> ComponentList);
	static void Simulate(std::vector<Component*> ComponentList);
};

