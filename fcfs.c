#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int pid;
	int arrival_time;
	int burst_time;
} process;

//Prints the process ID which is executed every second
void clock(process* arr, int tat[], int n) {

	int* t = malloc(n * sizeof(int));
	t[0] = 0;
	int temp = 0;
	for (int i = 0; i < n; i++) {
		t[i] = tat[i];
		tat[i] = tat[i] - temp;
		temp = t[i];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < tat[i]; j++) {
			printf("%d\n", arr[i].pid);
		}
	}
}

//Calcuates Waiting Time incase we need it
int findWaitingTime(process* arr, int wt[], int i) {

	wt[i] = arr[i - 1].burst_time + wt[i - 1];
	return wt[i];
}

//Calculates Turn Around Time
int findTurnAroundTime(process* arr, int wt[], int tat[], int i) {

	tat[i] = arr[i].burst_time + wt[i];
	return tat[i];
}

int main() {

	/* read in data - DO NOT EDIT (START) */
	int n;
	int quantum;
	scanf("%d", &n);
	scanf("%d", &quantum);
	int* wt = malloc(n * sizeof(int));
	int* tat = malloc(n * sizeof(int));
	process *arr;
	arr = malloc(n * sizeof(process));
	for (int i = 0; i < n ; ++i) {
		scanf("%d", &arr[i].pid);
		scanf("%d", &arr[i].arrival_time);
		scanf("%d", &arr[i].burst_time);
	}
	/* read in data - DO NOT EDIT (END) */

	for (int i = 1; i < n; i++) {
		wt[0] = 0;
		wt[i] = findWaitingTime(arr, wt, i);
	}
	for (int i = 0; i < n; i++) {
		tat[i] = findTurnAroundTime(arr, wt, tat, i);
	}
	clock(arr, tat, n);
	
	return 0; /* DO NOT EDIT THIS LINE */
}
