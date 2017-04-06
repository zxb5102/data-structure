#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define size 5

main(){

	int ary[size];
	init( ary );
	show( ary );
	sort4( ary ,0,size -1);
	show( ary );
}
//快速排序
sort4( int* ary ,int begin,int end){
	if( end > begin ){
		int tmp = ary[begin];
		// add some criteria like end > begin
		int i = begin;
		int j = end;
		int z;
		bool flag;
		int loca = begin;
		while( i < j ){
			while( j >= begin ){
				if( i != j){
					if( ary[j] < tmp){
						flag = false;
						break;
					}
				}else{
					// find the location
					flag = true;
					break;
				}
				j--;
			}
			while( i <= end){
				if( i != j){
					if( ary[i] > tmp){
						flag = false;
						break;
					}
				}else{
					// find the location
					flag = true;
					break;
				}
				i++;
			}

			if( flag == false ){
				exchange( ary,i,j );
			}else{
				loca = i;
				exchange( ary,begin,loca );
			}
		}
		// recursion 
		sort4( ary,begin,loca -1 );
		sort4( ary,loca + 1,end );
	}
}
//快速排序 这个排序算法是 不太好的实现， sort4 更正了实现
sort( int* ary ,int begin,int end ){
	if( begin >=0 && end > begin){
		int temp = ary[begin];
		int i = begin + 1;
		int j,min;
		int locate = begin ;
		int num = ary[ begin ];
		for( i = begin + 1;i <= end ; i++ ){
			if( num > ary[i] ){
				min = ary[i];
				for( j=i;j>=locate + 1;j-- ){
					ary[ j ] = ary[ j -1 ];
				}
				ary[locate] = min;
				locate ++;
			}
		}
		sort( ary,locate+1,end );
		sort( ary,begin,locate-1 );
	}

}
//希尔排序
sort3( int* ary ){
	int inc = 2;
	int round = size/inc;
	int i,j,z;
	do{
		for( i=0;i<round;i++ ){
			for( j=i+round;j<size;j+=round ){
				for( z = j ; z>=round && ary[z] < ary[z - round] ; z-=round ){
					exchange( ary,z,z-round );	
				}
			}
		}
		round = round / inc;
	}while( round > 0 );
}
//选择排序 
sort1( int* ary ){
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
//插入排序
sort2( int* ary ){
	int i,j;
	for( i=0;i<size;i++ ){
		for( j=i; j>0 && ary[j] < ary[j-1] ;j-- ){
			exchange( ary,j,j-1 );
		}
	}
}
//交换数组里面两个位置处的元素
exchange( int* ary,int i,int min){
	int tmp ;
	tmp = ary[i];
	ary[i] = ary[min];
	ary[min] = tmp;
}
//初始化数组
init( int* ary ){
	int i;
	srand( (unsigned)time( NULL ) );          //初始化随机数
	for( i=0;i<size;i++ ){
		ary[i] = (rand()%20) + 1;
	}
}
//打印数组元素
show( int* ary ){
	int i;
	printf("=>\t");
	for( i=0;i<size;i++ ){
		printf("%d\t",ary[i]);
	}
	printf("\n");
}
