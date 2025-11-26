#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#define size 1000000
int arr[size];
int main(){
	for(int i =0;i<size;i++){
		arr[i] = rand() %100;
	}
#pragma omp parallel 
{
	if(omp_get_thread_num() == 0){
		printf("Runnding with %d threads\n",omp_get_num_threads());
	}
}

	int sum =0;
#pragma omp parallel for reduction(+:sum)
	for(int i =0;i<size;i++){
		sum+=arr[i];
	}
	printf("Total sum: %d\n",sum);
	return 0;
}
