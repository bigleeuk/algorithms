#define _CRT_SECURE_NO_WARNINGS
#define number 1000
#include <stdio.h>
#include <stdlib.h>

//Create a structure to hold the text file : stucture elephant
typedef struct elephant{
	int iq_sort[number];
	int iq[number];
	int weight_sort[number];
	int weight[number];
}elephant;

void recur_BestCase(int,elephant* e);
int count_smart[number][number];
int standard[number];
int who[number];
int main()
{
	struct elephant e;
	FILE *f;
	int i = 0;
	int temp;
	int a=0;
	char filename[100];
	printf("wirte file name : ");
	gets_s(filename);   
	//File open
	f = fopen(filename, "r");      
	
	if (f == NULL) {
		printf("ERROR\n");
		exit(0);
	}
	/*Run while statement until end of file
	Enter data into structure*/
	while (!feof(f)) 
	{
		fscanf(f, "%d %d", &e.weight[i], &e.iq[i]);
		printf("%d %d\n", e.weight[i], e.iq[i]);
		i++;
	}
	fclose(f);
	//Put data in another struct variable.
	for (int p = 0; p < i; p++)
	{
		e.weight_sort[p] = e.weight[p];
		e.iq_sort[p] = e.iq[p];
	}
	//sorting; Sort iq_sort according to weight_sort.
	for (int j = 0; j < i; j++)
	{
		for (int k = 0; k < i - 1; k++)
		{
			if (e.weight_sort[k] > e.weight_sort[k + 1])
			{
				temp = e.weight_sort[k];
				e.weight_sort[k] = e.weight_sort[k + 1];
				e.weight_sort[k + 1] = temp;

				temp = e.iq_sort[k];
				e.iq_sort[k] = e.iq_sort[k + 1];
				e.iq_sort[k + 1] = temp;

			}
		}
	}
	//print sorting 
	printf("--------------Sorting----------------\n");
	printf("Weight  IQ  \n");
	for (int l = 0; l < i; l++)
	{
		printf("%d  %d\n", e.weight_sort[l], e.iq_sort[l]);
	}
	//The value that is duplicated in the data is treated as 0.
	for (int p = 0; p < i; p++)
	{
		for (int t = p + 1; t < i; t++)
		{
			if (e.weight_sort[p] == e.weight_sort[t]) {
				e.weight_sort[t] = 0;
				e.iq_sort[t] = 0;
			}
		}
	}
	recur_BestCase(i,&e);
}
void recur_BestCase(int num ,elephant *e1) {
	int max = 0;
	int b;
	int q = 0;
	/*	expression (A (n) = A (n-1) +1)
	Put the values ​​from the sorted values ​​into the standard in order from the first value.
	*/
	//A (n): the number of values ​​that satisfy the condition based on the standard variable, ie, [standard, n]
	for (int j = 0; j < num; j++)
	{
		standard[j] = e1->iq_sort[j];
		//who variable : when the condition is met, who increases the value to determine how many conditions
		who[j] = 1;
		/*count_smart variable: If the value that matches the condition is found from the reference value,
		1 is added to the corresponding index.*/
		count_smart[j][j] = 1;
		/*In the equation A (n) = A (n-1) +1,
		the value is +1 when the value is satisfied, and the reference changes the reference value 
		when the value satisfies.*/
		for (int k = j+1; k < num; k++ ) {
			if (e1->iq_sort[k] != 0) {
				if (standard[j] < e1->iq_sort[k] || standard[j] == e1->iq_sort[k])
					count_smart[j][k] = 0;
				else {
					count_smart[j][k] = 1;
					standard[j] = e1->iq_sort[k];
					who[j]++;
				}
			}
			//If the value is 0, the value is ignored because it is duplicated.
			else
				continue;
		}
	}
	//When the condition is satisfied, it finds the number with the greatest number of cases.
	for (b = 1; b < num; b++)
	{
		max = who[0];
		if (who[b] > max) {
			max = who[b];
			q = b;
		}
	}
	printf("RESULT : %d th elephant Starting is best ( Standard in Sorting Data )\n", q+1);
	printf("--------------Simple Output----------------\n");
	for (int n = q; n < num; n++)
	{
		if (count_smart[q][n] == 1) {
			for (int t = 0; t < num; t++)
			{
				if (e1->iq_sort[n] == e1->iq[t]) 
					printf("%d \n", t + 1);
			}
			printf("Weight:%d IQ:%d\n",e1->weight_sort[n], e1->iq_sort[n]);
		}
	}
}