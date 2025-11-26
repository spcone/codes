#include <stdio.h>
#include<pthread.h>
#define size 3
int a[size][size] = {{1,2,3},{4,5,6},{7,8,9}};
int b[size][size] = {{9,8,7},{6,5,4},{3,2,1}};
int c[size][size];

void *add_matrices(void* arg){
	int i = *(int*)arg;
	for(int j = 0;j<size;j++){
		c[i][j] = a[i][j] + b[i][j];
	}
	return NULL;
}

int main(){
	int indices[size];
	pthread_t threads[size];
	for(int i =0;i<size;i++){
		indices[i] = i;
		pthread_create(&threads[i],NULL,add_matrices,(void*)&indices[i]);
	}
	for(int i =0;i<size;i++){
		pthread_join(threads[i],NULL);
	}

	printf("resultant matrix:\n");
	for(int i =0;i<size;i++){
		for(int j =0;j<size;j++){
			printf("%d\t",c[i][j]);
			
		}
		printf("\n");
	}
	return 0;
}

