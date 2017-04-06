#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define size 5

//exchange( int* ary,int i,int min);
main(){
	int ary[size];
	init( ary );
	show( ary );
	sort( ary );
	show( ary );
}
sort( int* ary ){
	int i,j,min;
	for( i=0;i<size;i++ ){
		min = i;
		for( j=i+1;j<size;j++ ){
			if( ary[min] > ary[j]  ){
				min = j;
			}
		}
			exchange( ary,i,min );
	}
}
exchange( int* ary,int i,int min){
	int tmp ;
	tmp = ary[i];
	ary[i] = ary[min];
	ary[min] = tmp;
}
init( int* ary ){
	int i;
	srand( (unsigned)time( NULL ) );          //初始化随机数
	for( i=0;i<size;i++ ){
		ary[i] = (rand()%20) + 1;
	}
}
show( int* ary ){
	int i;
	printf("=>\t");
	for( i=0;i<size;i++ ){
		printf("%d\t",ary[i]);
	}
	printf("\n");
}
