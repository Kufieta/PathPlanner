#include "include/Planner.hpp"

State getStartState();
State getTargetState();

int main(){

	printf("Hello Hybrid_Astar\n");
	printf("Init Map !\n");
	Map map;
	printf("Start State\n");
	State start=getStartState();
	printf("Get State\n");
	State target=getTargetState();
	printf("\n \n Start Planner\n");
	Planner astar;
	
	printf("Planning now\n");
	astar.plan(start, target, map);
}

State getStartState()
{
	//to do: read from yml file
	return State(750, 300, 90);
}

State getTargetState()
{
	//to do: read from yml file
	return State(50, 300, 45);
}
