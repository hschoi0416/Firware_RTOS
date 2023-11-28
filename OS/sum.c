#include <stdio.h>
#include <pthread.h>

int sum = 0;

void* worker(void *arg){
	for (int i = 0; i < 1000000; i++){
		sum = sum + 10;
	}
}

int main() {
	char *name[] = {"Kim", "Choi"};
	pthread_t tid[2];
	pthread_attr_t attr[2];

	pthread_attr_init (&attr[0]);
	pthread_attr_init (&attr[1]);

	pthread_create(&tid[0], &attr[0], worker, name[0]);
	pthread_create(&tid[1], &attr[1], worker, name[1]);

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	printf("sum = %d\n", sum);

	return 0;
}
