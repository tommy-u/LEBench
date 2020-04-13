#define _GNU_SOURCE
#include <sched.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/poll.h>
#include <sys/epoll.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/un.h>

#define NUM_SAMPLES 50

struct timespec *calc_diff(struct timespec *smaller, struct timespec *bigger)
{
	struct timespec *diff = (struct timespec *)malloc(sizeof(struct timespec));
	if (smaller->tv_nsec > bigger->tv_nsec)
    {
      diff->tv_nsec = 1000000000 + bigger->tv_nsec - smaller->tv_nsec;
      diff->tv_sec = bigger->tv_sec - 1 - smaller->tv_sec;
    }
	else 
    {
      diff->tv_nsec = bigger->tv_nsec - smaller->tv_nsec;
      diff->tv_sec = bigger->tv_sec - smaller->tv_sec;
    }
	return diff;
}

void add_diff_to_sum(struct timespec *result,struct timespec a, struct timespec b)
{
	if (result->tv_nsec +a.tv_nsec < b.tv_nsec)
    {
      result->tv_nsec = 1000000000+result->tv_nsec+a.tv_nsec-b.tv_nsec;
      result->tv_sec = result->tv_sec+a.tv_sec-b.tv_sec-1;
    }
	else if (result->tv_nsec+a.tv_nsec-b.tv_nsec >=1000000000)
    {
      result->tv_nsec = result->tv_nsec+a.tv_nsec-b.tv_nsec-1000000000;
      result->tv_sec = result->tv_sec+a.tv_sec-b.tv_sec+1;
    }
	else
    {
      result->tv_nsec = result->tv_nsec + a.tv_nsec - b.tv_nsec;
      result->tv_sec = result->tv_sec +a.tv_sec - b.tv_sec;
    }
}

void getppid_test(struct timespec *diffTime) {
	struct timespec startTime, endTime;
	clock_gettime(CLOCK_MONOTONIC, &startTime);
	syscall(SYS_getppid);
	clock_gettime(CLOCK_MONOTONIC, &endTime);
	add_diff_to_sum(diffTime, endTime, startTime);
	return;
}

void run_test(){
	struct timespec testStart, testEnd;
	clock_gettime(CLOCK_MONOTONIC,&testStart);

	printf("Performing get_ppid test \n");

	printf("Total test iteration %d.\n", NUM_SAMPLES);

	struct timespec* timeArray = (struct timespec *)
    malloc(sizeof(struct timespec) * NUM_SAMPLES);

  // Hit the path a few times to avoid first start delay.
	/* syscall(SYS_getpid); */

	for (int i=0; i < NUM_SAMPLES; i++) {
		timeArray[i].tv_sec = 0;
		timeArray[i].tv_nsec = 0;
		getppid_test(&timeArray[i]);
	}

	clock_gettime(CLOCK_MONOTONIC,&testEnd);
	struct timespec *diffTime = calc_diff(&testStart, &testEnd);
	printf("Test took: %ld.%09ld seconds\n",diffTime->tv_sec, diffTime->tv_nsec);
	free(diffTime);


  // Dump out samples.
	for (int i=0; i < NUM_SAMPLES; i++) {
    printf("Sample %d: %ld.%09ld\n",i, timeArray[i].tv_sec, timeArray[i].tv_nsec);
  }

	free(timeArray);
}

int main(int argc, char *argv[])
{
  printf("Running ppid test\n");

	run_test();
  return 0;

}
