#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
int stacksize;
int count = 0;
int curr_size = 0;
int check = 0;
/* Reverses arr[0..i] */
void flip(int arr[], int i)
{
	int temp, start = 0, same = 0;
	while (start < i)
	{
		temp = arr[start];
		arr[start] = arr[i];
		arr[i] = temp;
		start++;
		i--;
	}
	count++;
	printf("flip (%d)", count);
	for (int p = 0; p < stacksize; p++)
	{
		printf("%d ", arr[p]);
	}
	printf("\n");

}
/* Returns index of the maximum element in arr[0..n-1] */
int findMax(int arr[], int n)
{
	int mi, i;
	for (mi = 0, i = 0; i < n; ++i) {
		if (arr[i] > arr[mi] || arr[i] == arr[mi])
			mi = i;
	}
	//if max is first, Only move the maximum number to end by reversing
	if (mi == 0) {
		check = -1;
	}
	//if max is last, Apply size -1
	if (mi == n - 1)
	{
		curr_size--;
		check = 1;
	}
	return mi;
}

// The main function that sorts given array using flip 
// operations
void pancakeSort(int *arr, int n)
{
	// Start from the complete array and one by one reduce
	// current size by one
	for (int curr_size = n; curr_size > 1; --curr_size)
	{
		// Find index of the maximum element in 
		// arr[0..curr_size-1]
		int mi = findMax(arr, curr_size);

		// Move the maximum element to end of current array
		// if it's not already at the end

		if (check == 1) {
			check = 0;
		}

		else {
			if (check == 0) {
				if (mi != curr_size - 1)
				{
					// To move at the end, first move maximum number
					// to beginning 
					flip(arr, mi);

					// Now move the maximum number to end by reversing
					// current array
					flip(arr, curr_size - 1);
				}
			}
			else {
				// Now move the maximum number to end by reversing
				// current array
				check = 0;
				flip(arr, curr_size - 1);
			}
		}
	}
}

/* A utility function to print an array of size n */
void printArray(int arr[], int n)
{
	for (int i = 0; i < n; ++i)
		printf("%d ", arr[i]);
}

// Driver program to test above function
int main()
{
	while (1)
	{
		int arr[] = { 0 };
		int num = 0;
		char resp = ' ';
		printf("\nSTART : PRESS s \nFINISH : PRESS q\n");
		scanf(" %c", &resp);
		switch (resp)
		{
		case 'q':
			printf("Quit!");
			exit(0);
		case 's':
			printf("how many pancakes do you want ;stack : ");
			scanf_s("%d", &stacksize);
			if (stacksize > 31) {
				printf("again!\n");
				scanf_s("%d", &stacksize);
			}
			for (int n = 0; n < stacksize; n++) {
				scanf_s("%d", &arr[n]);
			}
			pancakeSort(arr, stacksize);
			puts("Sorted Array ");
			printArray(arr, stacksize);
			curr_size = 0;
			count = 0;
		}

	}
	return 0;
}
