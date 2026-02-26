#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int pid;
	int arrival_time;
	int burst_time;
} process;

//Prints the process ID which is executed every second, subtract the burst time of every 
//process till it's zero and increases the time (as for seconds passing).
int clock(process* arr, int* bt, int i, int time) {
	for (int j = 0; j < arr[i].burst_time; j++) {
		bt[i]--;
		time++;
		printf("%d\n", arr[i].pid);
	}
	return time;
}

int main() {

	/* read in data - DO NOT EDIT (START) */
	int n;
	int quantum;
	scanf("%d", &n);
	scanf("%d", &quantum);
	process *arr;
	arr = malloc(n * sizeof(process));
	for (int i = 0; i < n ; ++i) {
		scanf("%d", &arr[i].pid);
		scanf("%d", &arr[i].arrival_time);
		scanf("%d", &arr[i].burst_time);
	}
	/* read in data - DO NOT EDIT (END) */
	int pos, temp, time = 0;
	int* bt = malloc(3 * sizeof(int));
	int* at = malloc(3 * sizeof(int));
	int* p = malloc(3 * sizeof(int));
	//initialization of the bt, at, p arrays with the burst time, arrival time and process id respectively
	for (int i = 0; i < n; i++) {
		bt[i] = arr[i].burst_time;
		at[i] = arr[i].arrival_time;
		p[i] = arr[i].pid;
	}
	//implementation of SJF algorithm
	for (int i = 0; i < n; i++) {
		int index = i;
		for (int j = i + 1; j < n; j++) {
			if (bt[j] > bt[index] && at[j] == time && bt[j] > 0) {
				index = j;
			}
			time = clock(arr, bt, index, time);
		}
		temp = bt[i];
		bt[i] = bt[index];
		bt[index] = temp;

		temp = p[i];
		p[i] = p[index];
		p[index] = temp;
	}

	return 0; /* DO NOT EDIT THIS LINE */
}
