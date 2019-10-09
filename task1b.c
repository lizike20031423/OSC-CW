// Round Robin (RR) process scheduling algorithm.
// Jizhou Che 20032291 scyjc1.
// Zike Li 20031423 scyzl2.

#include "coursework.h"
#include "linkedlist.h"
#include <stdlib.h>

int main() {
	// Queue of processes.
	struct element * pHead = NULL;
	struct element * pTail = NULL;
	
	printf("PROCESS LIST:\n");
	
	// Create all processes and append to list in order.
	for (int i = 0; i < NUMBER_OF_JOBS; i++) {
		struct process * p = generateProcess();
		printf("\t Process Id = %d,  ", p -> iProcessId);
		printf("Initial Burst Time = %d, ", p -> iInitialBurstTime);
		printf("Remaining Burst Time = %d\n", p -> iRemainingBurstTime);
		addLast(p, &pHead, &pTail);
	}
	
	printf("END\n\n");
	
	// Sum of response time and turn around time.
	long int sumResponseTime = 0;
	long int sumTurnAroundTime = 0;
	
	while (pHead != NULL) {
		// Take first process in the queue.
		struct process * p = removeFirst(&pHead, &pTail);
		
		struct timeval pStartTime, pEndTime;
		
		// Run the process until it is either interrupted or finished.
		runPreemptiveJob(p, &pStartTime, &pEndTime);
		
		// Time calculations.
		printf("Process Id = %d, ", p -> iProcessId);
		printf("Previous Burst Time = %d, ", p -> iPreviousBurstTime);
		printf("Remaining Burst Time = %d", p -> iRemainingBurstTime);
		// Check if process is running for the first time.
		if (p -> iPreviousBurstTime == p -> iInitialBurstTime) {
			// Calculate response time.
			long int responseTime = getDifferenceInMilliSeconds(p -> oTimeCreated, pStartTime);
			printf(", Response Time = %ld", responseTime);
			sumResponseTime += responseTime;
		}
		// Check if process has finished.
		if (p -> iRemainingBurstTime == 0) {
			// Calculate turn around time.
			long int turnAroundTime = getDifferenceInMilliSeconds(p -> oTimeCreated, pEndTime);
			printf(", Turnaround Time = %ld", turnAroundTime);
			sumTurnAroundTime += turnAroundTime;
			// Memory deallocation.
			free(p);
		} else {
			// Append process to the end of queue.
			addLast(p, &pHead, &pTail);
		}
		printf("\n");
	}
	
	// Calculate average response time and turn around time.
	printf("Average response time = %lf\n", (double)sumResponseTime / NUMBER_OF_JOBS);
	printf("Average turn around time = %lf\n", (double)sumTurnAroundTime / NUMBER_OF_JOBS);
	
	return 0;
}
