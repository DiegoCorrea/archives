# include <stdio.h>
# include <iostream>
# include <string.h>
# include <vector>
# include <algorithm>

void mat(int matrix[][30]){
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10;j++){
			matrix[i][j] = i + j;
		}
	}
}


int main(){
	int matrix[10][10];
	mat(matrix);
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10;j++){
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
	return 0;
}