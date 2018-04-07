#define _CRT_SECURE_NO_WARNINGS
#define number 30
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//Create a structure to hold the text file : stucture point
typedef struct  point {
	double edge[number][number];
	double weight[number][number];
	int except[number];
	int num;
}point;
//Variable to store information about how many points :except_num1 , except_num2
//By setting the minimum value to a large value, the minimum value is calculated, and the length of the line is excluded
double tot_distance = 0.0;
int except_num1 = 0;
int except_num2 = 0;
double min = 10000.0;
int count = 0;

void findmin(point* p);
void exception(point* p);
int main()
{
	struct point p;
	FILE *f;
	int temp = 0;
	int i = 1;
	int j = 0;
	int a;
	char filename[100];
	printf("wirte file name : ");
	gets_s(filename,40);
	f = fopen(filename, "r");

	if (f == NULL) {
		printf("ERROR\n");
		exit(0);
	}
	/*Run while statement until end of file
	Enter data into structure*/

	while (!feof(f))
	{
		//Put data in another struct variable.
		if (temp == 0) {
			fscanf(f, "%d", &p.num);
			printf("%d\n", p.num);
			temp++;
		}
		else {
			fscanf(f, "%lf %lf", &p.edge[i][j], &p.edge[i][j + 1]);
			printf("%lf %lf\n", p.edge[i][j], p.edge[i][j + 1]);
			i++;
			j = 0;
		}
	}
	fclose(f);
	//1 to n are stored in the array as many as the number of points
	for (int k = 0; k<p.num; k++) {
		p.except[k] = k + 1;
	}
	p.edge[0][0] = 0;
	p.edge[0][1] = 0;

	for (int n = 0; n<p.num + 1; n++) {
		for (int k = 0; k<p.num + 1; k++) {
			if (n == 0 || k == 0)
				p.weight[n][k] = 10000;
		}
	}
	//Exclude non - lines,Ignore the directionality of the line.
	//weight variable : distance between point and point(Set the same line and dot; to 10000)
	for (int n = 1; n<p.num + 1; n++) {
		for (int k = 1; k<p.num + 1; k++) {
			if (n == k || n<k) {
				p.weight[n][k] = 10000;
				continue;
			}
			p.weight[n][k] = sqrt(pow(p.edge[n][0] - p.edge[k][0], 2) + pow(p.edge[n][1] - p.edge[k][1], 2));
		}
	}
	/*When excluding lines in A line with a different direction , dot 
	Number of remaining lines : a */
	a = ((p.num)*(p.num) - p.num) / 2;
	for (int k = 0; k < a; k++) {
		if (count == p.num - 1)
			break;
		findmin(&p);
		exception(&p);
	}
	printf("least distance is : %lf", tot_distance);
}
//Find the minimum of the lines.
void findmin(point *p1) {
	for (int n = 1; n<p1->num + 1; n++) {
		for (int k = 1; k<p1->num + 1; k++) {
			if (n == k || n<k)
				continue;
			else {
				if (p1->weight[n][k]<min) {
					min = p1->weight[n][k];
					//The line of the minimum distance connects the kth point at the nth point.
					except_num1 = n;
					except_num2 = k;
				}
			}
		}
	}//reset min variable
	min = 10000;
}
//When we find the line of the minimum distance, we find the corresponding nth point in the except, and set it to zero.
void exception(point* p2) {
	for (int p = p2->num - 1; p > -1; p--) {
		//When the line of the first minimum distance is found, find the position of two points and remove it.
		//Except for the location of two points
		if (count == 0) {
			p2->except[except_num1 - 1] = 0;
			p2->except[except_num2 - 1] = 0;
			count++;
			tot_distance += p2->weight[except_num1][except_num2];
			p2->weight[except_num1][except_num2] = 10000.0;
			break;
		}
		//From the second line, find the first point of the line and Except for the location of points.
		//However, if the point at the first position is excepted, Except the position of another point
		else {
			if (p2->except[p] == except_num1) {
				p2->except[except_num1 -1] = 0;
				count++;
				tot_distance += p2->weight[except_num1][except_num2];
				//printf("present2 total distance is %lf\n", tot_distance);
				p2->weight[except_num1][except_num2] = 10000.0;
				break;


			}
			else if (p2->except[p] == except_num2) {
				p2->except[except_num2 -1] = 0;
				count++;
				tot_distance += p2->weight[except_num1][except_num2];
				p2->weight[except_num1][except_num2] = 10000.0;
				break;
			}
			else
				continue;
		}
	}
	/*If the position of the point has already been excluded.
	To prevent the circulation, initialize it and do exception handling. */
	if (p2->weight[except_num1][except_num2] != 10000)
		p2->weight[except_num1][except_num2] = 10000;
}



