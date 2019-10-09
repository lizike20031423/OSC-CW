// First Come First Served (FCFS) process scheduling algorithm.
// Jizhou Che 20032291 scyjc1.
// Zike Li 20031423 scyzl2.

#include "coursework.h"
#include "linkedlist.h"
#include <stdlib.h>

int main() {
	// Queue of processes.
	struct element * pHead = NULL;
	struct element * pTail = NULL;
	
	// Create all processes and append to list in order.
	for (int i = 0; i < NUMBER_OF_JOBS; i++) {
		struct process * p = generateProcess();
		addLast(p, &pHead, &pTail);
	}
	
	// Sum of response time and turn around time.
	long int sumResponseTime = 0;
	long int sumTurnAroundTime = 0;
	
	while (pHead != NULL) {
		// Take first process in the queue.
		struct process * p = removeFirst(&pHead, &pTail);
		
		struct timeval pStartTime, pEndTime;
		
		// Complete the process in one go.
		runNonPreemptiveJob(p, &pStartTime, &pEndTime);
		
		// Time calculations.
		printf("Process Id = %d, ", p -> iProcessId);
		printf("Previous Burst Time = %d, ", p -> iPreviousBurstTime);
		printf("New Burst Time = %d, ", p -> iRemainingBurstTime);
		long int responseTime = getDifferenceInMilliSeconds(p -> oTimeCreated, pStartTime);
		printf("Response Time = %ld ,", responseTime);
		sumResponseTime += responseTime;
		long int turnAroundTime = getDifferenceInMilliSeconds(p -> oTimeCreated, pEndTime);
		printf("Turn Around Time = %ld\n", turnAroundTime);
		sumTurnAroundTime += turnAroundTime;
		
		// Memory deallocation.
		free(p);
	}
	
	// Calculate average response time and turn around time.
	printf("Average response time = %lf\n", (double)sumResponseTime / NUMBER_OF_JOBS);
	printf("Average turn around time = %lf\n", (double)sumTurnAroundTime / NUMBER_OF_JOBS);
	
	return 0;
}
