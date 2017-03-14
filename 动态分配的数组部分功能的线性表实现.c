#include <stdio.h>
#include <stdlib.h>
#define init_size  3
#define increase_size 3

//基于动态堆内存的顺序存储
struct list{
	char* head;
	int size;
	int now;
}

main(void){
	int find(struct list* ist,char car);//函数声明
	//void insert( struct list* ist  );
	//初始化 size=4 
	struct list ist;
	init( &ist );
	//请求用户输入 测试输入的值大于初始值，动态改变大小
	insert(&ist);
	printf("输入字符结束\n");
	//查找
	char tep ;
	printf("输入想要查找的字符：");
	scanf("%c",&tep);
	int flag = find(&ist,tep);
	//int flag = -1;
	if(flag == -1 ){
		printf("不存在想要查找的字符 \n");
	}else{
		printf("字符位置为 %d\n",flag+1);
	}
	showAll(&ist);
	//插入
	inserts(&ist);
	//删除
	//显示全部的元素
	showAll(&ist);
}

 inserts ( struct list * ist){
	printf("\n插入字符操作——>格式：位置,字符");
	int locate;
	char temp;
	scanf("%d,%c",&locate,&temp);
	if( locate > ist->now){
		printf("输入的范围不存在\n");
		return;
	}
	if( ist->now >= ist->size ){//当前没有足够的空间
			ist->head =	(char*)realloc(ist-> head ,( ist->size+increase_size)*sizeof(char)  );		
			ist->size += increase_size;
	}
	int index = 0;
	for(index=ist->now;locate-1<index;index--){
		*(ist->head+index) = *(ist->head+index-1);
	}
	*(ist->head+locate-1 ) = temp;
	ist->now ++;
	
}
//查找某个元素并返回
int find(struct list* ist,char car){
	int index = 0;
	while( index < ist->now ){
		char temp = *(ist->head + index);
		if( temp == car ){
			return index;
		}
		index++;
	}	
		return -1;
}
//输出全部的元素
showAll( struct list* ist){
	int index;
	for(index=0 ;index<ist->now ;index++){
		printf("%c\t",*( ist->head+index) );
	}
}
//请求用户输入
insert( struct list* ist  ){
	char temp ;
	scanf("%c",&temp);
	while( temp != '\n' ){
		
		if( ist->size <= ist->now ){//没有足够的空间
			ist->head =	(char*)realloc(ist-> head ,( ist->size+increase_size)*sizeof(char)  );		
			ist->size += increase_size;
		}	
			*( ist->head +ist->now ) = temp;
			ist->now ++;
		scanf("%c",&temp);
	}
};

//初始化操作
init( struct list* ist ){

	(*ist).head = (char*)malloc( sizeof(char)*init_size );

	if( (*ist).head != NULL ){
		(*ist).size = init_size;//初始化长度为3
		(*ist).now = 0;
	}else{
		exit(0);
	}

}
