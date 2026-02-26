#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int pid;
	int arrival_time;
	int burst_time;
} process;

//Adds the incoming process to the ready queue(if any arrives)
void queueUpdation(int q[], int timer, process* arr, int n, int maxProccessIndex) {
	int zeroIndex;
	for (int i = 0; i < n; i++) {
		if (q[i] == 0) {
			zeroIndex = i;
			break;
		}
	}
	q[zeroIndex] = maxProccessIndex + 1;
}

//Maintain the entries of processes after each premption in the ready Queue
void queueMaintainence(int q[], int n) {
	for (int i = 0; (i < n - 1) && (q[i + 1] != 0); i++) {
		int temp = q[i];
		q[i] = q[i + 1];
		q[i + 1] = temp;
	}
}

//Checks and updates the ready queue until all the processes arrive
void checkNewArrival(int timer, process* arr, int n, int maxProccessIndex, int q[]) {
	if (timer <= arr[n - 1].arrival_time) {
		int newArrival = 0;
		for (int j = (maxProccessIndex + 1); j < n; j++) {
			if (arr[j].arrival_time <= timer) {
				if (maxProccessIndex < j) {
					maxProccessIndex = j;
					newArrival = 1;
				}
			}
		}
		if (newArrival)
			queueUpdation(q, timer, arr, n, maxProccessIndex);
	}
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
	int maxProccessIndex = 0;
	int timer;
	int* temp = malloc(3 * sizeof(int));
	int* q = malloc(3 * sizeof(int));
	//Initialize temp array with the burst times of every process
	for (int i = 0; i < n; i++) {
		temp[i] = arr[i].burst_time;
	}
	//Initialition of the q array
	for (int i = 0; i < n; i++) {
		q[i] = 0;
	}
	//Starts the timer when the process arrives and loads the queue array with the first process
	for (int i = 0; i < n; i++) {
		if (arr[i].arrival_time == 0) {
			timer = 0;
			q[0] = arr[i].pid;
		}
	}
	int bool1 = 1;
	//Main body of the algorithm round robin. Changes the queue values as needed along with
	//the timer and the burst times. Prints the process executing every second.
	while (bool1) {
		int flag = 1;
		for (int i = 0; i < n; i++) {
			if (temp[i] != 0) {
				flag = 0;
				break;
			}
		}
		if (flag)
			break;
		for (int i = 0; (i < n) && (q[i] != 0); i++) {
			int ctr = 0;
			while ((ctr < quantum) && (temp[q[0] - 1] > 0)) {
				printf("%d\n", q[0]);
				timer += 1;
				temp[q[0] - 1] -= 1;
				ctr++;
				checkNewArrival(timer, arr, n, maxProccessIndex, q);
			}
			queueMaintainence(q, n);
		}
	}

	return 0; /* DO NOT EDIT THIS LINE */
}
