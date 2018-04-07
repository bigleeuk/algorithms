#define _CRT_SECURE_NO_WARNINGS
#define number 100
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<string.h>


//Structure info :
//vvisit - store information to visit
//weight - each time; Information about minutes
//distance - Save time for each region
//last time - store the index for the first departure from the route
//first time - store the index for the last arrival at the route
typedef struct  info {
	char vvisit[number][number];
	int weight[number][number];
	int distance[number];
	char region[1][number];
	int last_time[number];
	int first_time[number];
	int routing[number][number];
}info;


//variable:
//start - departure area
//dist - Destination area
char start[number];
char dist[number];
int starttime;
int data_number;
int region_number;

//variable:
//station - Several stops
//tot_distance - Total distance
int route_count;
int station;
int tot_distance[number];
int distance_store;
int k = -1;
void findDist(struct info *f);
int main()
{
	struct info f;
	int dataset;
	int p = 0;
	int arrive_min = 0;
	int start_min = 0;
	int result=0;
	//Scanning process Start!!
	printf("Sample input\n");
	scanf(" %d", &dataset);
	scanf(" %d", &region_number);
	for (int i = 0; i < region_number; i++) {
		scanf(" %s", &f.region[i]);
	}
	scanf(" %d", &route_count);
	for (int i = 0; i < route_count; i++)
	{
		scanf(" %d", &station);
		for (int j = 0; j < station; j++)
		{
			scanf("%d %s", &f.weight[i][j], &f.vvisit[p]);
			p++;
		}
	}
	scanf("%d", &starttime);
	scanf("%s", &start);
	scanf("%s", &dist);
	//Scanning process Finish!!

	//The process of changing time to minutes
	starttime = (starttime / 100) * 60 + (starttime % 100);
	for (int i = 0; i < route_count; i++)
	{
		f.weight[i][0] = (f.weight[i][0] / 100) * 60 + (f.weight[i][0] % 100);
		f.weight[i][1] = (f.weight[i][1] / 100) * 60 + (f.weight[i][1] % 100);
		f.distance[i] = f.weight[i][1] - f.weight[i][0];
	}
	//The process of finding the starting point and connecting the destination to the next starting point.
	for (int i = 0; i < route_count; i++)
	{
		distance_store = 0;
		if (strcmp(f.vvisit[2 * i] , start)==0) {
			if (starttime < f.weight[i][0])
			{
				k++;
				tot_distance[k] += f.distance[i];
				f.last_time[k] = i;
				f.first_time[k] = i;
				findDist(&f);
			}
			else
				continue;		
		}
		tot_distance[k] += distance_store;
	}
	//Initialize departure and distination times on the first completed route.
	//	If the arrival time is earlier, reset it.
	//	if you arrive at the same time but leave later, reset it
	arrive_min = f.weight[f.last_time[0]][1];
	start_min = f.weight[f.first_time[0]][0];
	for (int i = 1; i < k+1; i++) {
		if (f.weight[f.last_time[i]][1] < arrive_min) {
			arrive_min = f.weight[f.last_time[i]][1];
			start_min = f.weight[f.first_time[i]][0];
			result = i;
		}
		else if (f.weight[f.last_time[i]][1] == arrive_min) {
			if (f.weight[f.first_time[i]][0] > start_min) {
				start_min = f.weight[f.first_time[i]][0];
				arrive_min = f.weight[f.last_time[i]][1];
				result = i;
			}
		}
	}
	printf("Sample Output\n");
	printf("Departure    :   %02d:%02d   %s\n", (start_min / 60), (start_min % 60), f.vvisit[(f.first_time[result] * 2)]);
	printf("Arrival      :   %02d:%02d   %s\n", (arrive_min / 60), (arrive_min % 60), f.vvisit[(f.last_time[result] * 2) +1]);
}
/*
Through the recursive function,
departure - arrival(departure) - arrival.
This is the findDist recursive function that connects as above.
*/
void findDist(struct info * f1) {
	for (int i = 0; i < route_count; i++)
	{		
		if (strcmp(f1->vvisit[2*i] ,f1->vvisit[2*f1->last_time[k] +1])==0) {
			distance_store += f1->distance[i];
			f1->last_time[k] = i;
			findDist(f1);
		}
	}
}