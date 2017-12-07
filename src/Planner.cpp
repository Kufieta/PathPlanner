#include "../include/Planner.hpp"


State previous[GX][GY][Theta];

void Planner::plan(State start, State target, Map map){

	//initialize variables for the Compare class
	Compare::target=target;
	Compare::obs_map=map.obs_map;
	Compare::grid_obs_map=new int*[DX];
	for(int i=0;i<DX;i++)
	{
		Compare::grid_obs_map[i]=new int[DY];
		for(int j=0;j<DY;j++)
			Compare::grid_obs_map[i][j]=0;
	}
	for(int i=0;i<MAPX;i++)
		for(int j=0;j<MAPY;j++)
		{
			if(Compare::obs_map[i][j])
				Compare::grid_obs_map[i*DX/MAPX][j*DY/MAPY]=1;
		}
	Compare cmp;
	cmp.runDijkstra();


	map.initCollisionChecker();
	printf("find_near_obs\n");
	map.find_near_obs();
	printf("find_near_obs done\n");

	priority_queue<State, vector<State>, Compare> pq;
	start.cost3d=0;
	pq.push(start);
	printf("GUI\n");
	GUI display(800, 800);
	display.drawObs(map);
	display.drawCar(start,0);
	display.drawCar(target,255);

	int vis[GX][GY][Theta];
	memset(vis, 0, sizeof(int)*GX*GY*Theta);
	State Dummy = start;
	int iter=0;
	while(pq.size()>0)
	{
		State current=pq.top();
		//cout<<"current state., currentx:"<< current.gx << "currenty:" << current.gy << endl;
		pq.pop();

		/*This code can be seen as the final visualisation step ... only exec once*/		
		if(abs(current.gx-target.gx)<=1 && abs(current.gy-target.gy)<=1 && abs(current.gtheta-target.gtheta)<=5){
			cout<<"Reached target., targetx:"<< target.gx << "targety:" << target.gy << endl;
			cout<<"Reached target., currentx:"<< current.gx << "currenty:" << current.gy << endl;
			cout<<"Reached target., Dummy:"<< Dummy.gx << "currenty:" << Dummy.gy << endl;

			
			current.change=PRIORITY_OBSTACLE_NEAR*(map.obs_dist_max-map.nearest_obstacle_distance(current))/(float)(map.obs_dist_max-1)+
						   fabs(current.theta)/BOT_M_ALPHA+1; 
				
			while(current.x!=start.x || current.y!=start.y || current.theta!=start.theta){
				
				
				current.velocity=VELOCITY_MAX/current.change;
				display.drawCar(Dummy,255);
			        display.show(1);//2000/Dummy.velocity);//This can be removed while executing the algo
				Dummy=previous[current.gx][current.gy][current.gtheta];
				Dummy.change=PRIORITY_MOVEMENT*fabs(Dummy.theta-current.theta)/(2.0*BOT_M_ALPHA)+
					     PRIORITY_OBSTACLE_NEAR*(map.obs_dist_max-map.nearest_obstacle_distance(Dummy))/(float)(map.obs_dist_max-1)+
					     fabs(Dummy.theta)/BOT_M_ALPHA+1;

				current=Dummy;


			}
			cout<<"Reached target finally., currentx:"<< current.gx << "currenty:" << current.gy << endl;
			break;
		}

		if(vis[current.gx][current.gy][current.gtheta]){
			continue;
		}

		vis[current.gx][current.gy][current.gtheta]=1;

		vector<State> next=current.getNextStates();
		//Wie bekomme ich den gewonnenen Pfad?
		for(int i=0;i<next.size();i++){
			display.drawCar(next[i],0);
			if(!map.checkCollision(next[i])){


				if(!vis[next[i].gx][next[i].gy][next[i].gtheta]){
					//display.drawCar(next[i],100);
					current.next=&(next[i]);
					next[i].previous=&(current);
					//was bedeutet das? Ich vermute ... geradeaus ist günstiger?
					//Hier kann ich die kosten der "Lenkung" einstellen
					if(i==1)
						next[i].cost3d=current.cost3d+5;
					else
						next[i].cost3d=current.cost3d+5;
						//next[i].cost3d=current.cost3d+1;
					pq.push(next[i]);

					previous[next[i].gx][next[i].gy][next[i].gtheta]=current;

				}
			}
		}
	}
	cout<<"Done."<<endl;

	int x = 0;
	display.show(0);
	display.show(0);
	printf("Bye\n");

	return;
}
