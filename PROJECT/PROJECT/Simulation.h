#pragma once

#include<vector>

class Component;

class Simulation
{
public:
	Simulation();
	~Simulation();
	static bool IsValidToSimulate(std::vector<Component*> ComponentList);
};

