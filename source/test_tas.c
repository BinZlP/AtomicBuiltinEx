#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

#define LIMIT 100000
#define THREAD_COUNT 8

unsigned long int i=0;
bool flag = 0;

void *iterate();

int main(void){
	int status;
	//pthread_t new_thread;
	pthread_t threads[THREAD_COUNT];
	//pthread_attr_t attr;

	/*if(pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0){
		perror("Thread detach attribute setting error: ");
		exit(0);
	}*/

	for(int j=0;j<THREAD_COUNT;j++){
		//printf("Creating thread %d...\n", j);
		if(pthread_create(&threads[j], NULL, iterate, NULL) < 0) {
			perror("Thread creation error:");
			exit(0);
		}
		//pthread_detach(new_thread);
	}

	//pthread_attr_destroy(&attr);
	for(int j=0;j<THREAD_COUNT;j++)
		pthread_join(threads[j], (void **)&status);

	printf("Execution complete: %ld\n", i);

	return 0;
}

void *iterate(){
	while(1){
		if(__atomic_test_and_set(&flag, __ATOMIC_SEQ_CST) != true){
			//printf("%d\n",++i);
			__atomic_clear(&flag, __ATOMIC_SEQ_CST);
		}
		else break;
	}
}
