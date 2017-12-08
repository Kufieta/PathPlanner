#include "include/Planner.hpp"
#include <cstdlib>


State getStartState();
State getTargetState();

int main(int argc,  char** argv){

	printf("Hello Hybrid_Astar\n");
	printf("Init Map !\n");
	Map map;
	printf("Start State\n");
	State start=getStartState();
	printf("Get State %i %i %i argc%i\n",atoi(argv[1]),atoi(argv[2]),atoi(argv[3]), argc);
	State target=State(atoi(argv[1]),atoi(argv[2]),atoi(argv[3])/Theta_Res);
	//getTargetState();
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
	return State(50, 300, 0);
}
