#include <stdio.h>
#include <stdlib.h>
#define MAX 1000
int dist[MAX], A[MAX][MAX], p[MAX];

int BellmanFord(int N){
	int status;
	int v,u,i;
	for (i=1; i<N; i++){
		for (u = 0; u < N; u++)
			for (v = 0; v < N; v++)
				if (dist[v] > dist[u] + A[u][v]){
					dist[v] = dist[u] + A[u][v];
					p[v] = u;
				}
	}

	for (u=0;u<N;u++)
		for (v = 0; v < N; v++)
			if (dist[v] > dist[u] + A[u][v]){
				printf("\nNegative Edge Cycle detected");
				return -1;
			}
	return 1;
}


int main(){
	int n,i,j,source,f;
	printf("Enter the no. of nodes : ");
	scanf("%d",&n);
	printf("Enter the adjacent matrix : \n");
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++){
			scanf("%d",&A[i][j]);
			//if (A[i][j] == MAX || A[i][j] == 0)
			//	A[i][j] = MAX;
		}
	printf("\n\n");
	for (source = 0; source < n; source++){
		for (i = 0; i < n; i++)
			if (source != i)
				dist[i] = MAX;
			else
				dist[i] = 0;
		f = BellmanFord(n);
		if (f==-1)
			break;
		for (i = 0; i < n; i++)
			if (i != source)
				printf("Shortest Distance from %d to %d = %d\n",source,i,dist[i]);
	}
	return 0;
}


