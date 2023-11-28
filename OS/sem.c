#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t toiletsem;

void* guest(void* arg){
	int cnt = -1;

	sem_wait(&toiletsem);
	sem_getvalue(&toiletsem, &cnt);
	printf("customer%s into toilet... semaphore counter = %d\n", (char*)arg,cnt);
	sleep(1);
	printf("customer%s out toilet.\n", (char*)arg);
	sem_post(&toiletsem);
}

#define NO 0
#define MAX_COUNTER 3

int main() {
	int counter = -1;
	char *name[] = {"1","2","3","4","5"};
	pthread_t t[5];

	int res = sem_init(&toiletsem, NO, MAX_COUNTER);
	if(res == -1){
		printf("semaphore is not supported\n");
		return 0;
	}
	sem_getvalue(&toiletsem, &counter);
	printf("semaphore counter = %d\n", counter);

	for (int i = 0; i < 5; i++)
		pthread_create(&t[i], NULL, guest, (void*)name[i]);

	for (int i = 0; i < 5; i++)
		pthread_join(t[i], NULL);

	sem_getvalue(&toiletsem, &counter);
	printf("semaphore counter = %d\n", counter);
	sem_destroy(&toiletsem);

	return 0;
}
