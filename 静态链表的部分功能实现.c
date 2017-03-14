#include <stdio.h>
#include <stdlib.h>
#define init_size  50

struct spare{//用链表管理空闲的node
 int size;
 struct node* head;
};

struct student{//存放数据的链表
 int size;
 struct node* head;
 struct node* end;
};

struct node{ //链表的节点
	char key;
	int next;
};

main(){
	struct spare spa;//这里是空闲节点的链表
	struct student stu;
	struct node nodes[ init_size + 1 ];//这里存放所有的节点
 	init( &spa,&stu,nodes );
	
	insert( &stu,&spa );
	showAll( &stu,&spa );
}

showAll( struct student* stu,struct spare* spa ){
	int all = stu -> size;
	int pos = stu -> head -> next;
	while( all > 0 ){
	  char temp = (spa -> head + pos) -> key ;	
	  pos = (spa -> head + pos) -> next;	
		printf("%c\t",temp);
		all --;
	}
}

insert( struct student* stu,struct spare* spa ){
	char ichar;
	scanf( "%c",&ichar );
	while( ichar != '\n' ){
		int index = spa -> head -> next;
		( spa -> head + index ) -> key = ichar;
		spa -> head -> next = ( spa -> head + index ) -> next ;
		spa -> size --;
		stu -> end -> next = index;
		stu -> end = spa -> head + index;
		stu -> size ++;
		scanf( "%c",&ichar );
	}
}

init( struct spare* spa, struct student* stu , struct node* nodes ){
	int i;
	for( i=0 ; i<=init_size ;i++){
		nodes[i].next = i+1;
	}
	nodes[ init_size ].next = 0;
	spa -> size = init_size;
	spa -> head = nodes;
	//开始初始化 存放数据 的链表
	int tnode = spa -> head -> next;
	spa -> head -> next = (nodes + tnode) -> next ;
	spa -> size --;

	stu -> head = nodes + tnode ;
	stu -> head -> next = 0;
	stu -> end = stu -> head;
	stu -> size = 0;
}


