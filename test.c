#include <stdio.h> 
#include <pthread.h> 
#include <stdlib.h>
#include <unistd.h>

int value = 0;
pthread_barrier_t our_barrier;
pthread_mutex_t llave;




void *thread(void *val) {

	pthread_barrier_wait(&our_barrier);
	pthread_mutex_lock(&llave);
	fflush(stdout);
	printf("%d\n",value );
	value++;
	pthread_mutex_unlock(&llave);
	//scanf("%d",&t4);
	//

	//printf("\nvalues entered by the threads are  %d %d %d %d \n",t1,t2,t3,t4);
}



int main() {
	system("clear");
	pthread_mutex_init(&llave,NULL);
	pthread_barrier_init(&our_barrier,NULL,100);
	//pthread_t thread_id_1,thread_id_2,thread_id_3,thread_id_4;
	//pthread_attr_t attr;
	int N = 100;
	pthread_t hilos[N];
	int i;
	for(i=0;i<N;i++){
		pthread_create(&hilos[i],NULL,&thread,NULL);
	}
	for(i=0;i<N;i++){
		pthread_join(hilos[i],NULL);
	}

/*
	pthread_create(&hilos[0],NULL,&thread,NULL);
	pthread_create(&hilos[1],NULL,&thread,NULL);
	pthread_create(&hilos[2],NULL,&thread,NULL);
	pthread_create(&hilos[3],NULL,&thread,NULL);
	pthread_create(&hilos[4],NULL,&thread,NULL);

	pthread_join(hilos[0],NULL);
	pthread_join(hilos[1],NULL);
	pthread_join(hilos[2],NULL);
	pthread_join(hilos[3],NULL);
	pthread_join(hilos[4],NULL);
*/


}
