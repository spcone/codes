#include<stdio.h>
#include<pthread.h>
#define num 4

long long results[num];
void* factorial(void* arg){
	int thread_id = *(int*)arg;
	long long fact = 1;
	for(int i = 1;i<=5+thread_id;i++){
		fact*=i;
	}
	results[thread_id] = fact;
	return NULL;
}
int main(){
	pthread_t threads[num];
	int thread_ids[num];
	for(int i =0;i<num;i++){
		thread_ids[i] = i;
		pthread_create(&threads[i],NULL,factorial,(void*)&thread_ids[i]);
	}
	for(int i =0;i<num;i++){
		pthread_join(threads[i],NULL);
		printf("Factorial computed by thread %d: %lld\n",i,results[i]);
	}
	return 0;
}

