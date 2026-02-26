#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
	int pid;
	int arrival_time;
	int burst_time;
} process;

//Prints the process ID which is executed every second and finds the Waiting Time in case we need it.
void findWaitingTime(process* arr, int wt[], int rt[], int n) {

	for (int j = 0; j < n; j++) {
		rt[j] = arr[j].burst_time;
	}

	int complete = 0, t = 0, minm = INT_MAX;
	int shortest = 0, finish_time;
	int flag = 0;

	while (complete != n) {

		for (int j = 0; j < n; j++) {
			if ((arr[j].arrival_time <= t) && (rt[j] < minm) && rt[j] > 0) {
				minm = rt[j];
				shortest = j;
				flag = 1;
			}
		}
		if (flag == 0) {
			t++;
		}
		printf("%d\n", arr[shortest].pid);
		rt[shortest]--;
		minm = rt[shortest];

		if (minm == 0)
			minm = INT_MAX;

		if (rt[shortest] == 0) {

			complete++;
			flag = 1;
			finish_time = t + 1;
			wt[shortest] = finish_time - arr[shortest].burst_time - arr[shortest].arrival_time;

			if (wt[shortest] < 0) {
				wt[shortest] = 0;
			}
		}
		t++;
	}
}

//Finds Turn Around Time in case we need it.
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
    int* rt = malloc(n * sizeof(int));
	process *arr;
	arr = malloc(n * sizeof(process));
	for (int i = 0; i < n ; ++i) {
		scanf("%d", &arr[i].pid);
		scanf("%d", &arr[i].arrival_time);
		scanf("%d", &arr[i].burst_time);
	}
	/* read in data - DO NOT EDIT (END) */

    findWaitingTime(arr, wt, rt, n);
	for (int i = 0; i < n; i++) {
		tat[i] = findTurnAroundTime(arr, wt, tat, i);
	}

	return 0; /* DO NOT EDIT THIS LINE */
}
