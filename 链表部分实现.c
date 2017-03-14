#include <stdio.h>
#include <stdlib.h>

//链表 student
struct student {
	struct node* head; //这里指向头结点
	struct node* end; //这里指向未结点
	int size;
};

//结点node
struct node{
	char key;
	struct node* next;//指向下一个结点
};

main (){

  int getPos( struct student* stu);

	struct student stu;
	printf("请输入一段字符后回车\n");
  init( &stu );
	printf("初始化链表完成\n");
	insert( &stu );
	showAll( &stu );
	int flag = getPos( &stu );
	if( flag != -1){
		printf("%d",flag);
	}else{
		printf("\n不存在要查找的字符\n");
	}

}
//定位某个元素返回一个位置
int getPos( struct student* stu){
	printf("\n请输入查找的字符：");
	char fchar;
	getchar();
	scanf("%c",&fchar);
	int index = 0 ;
	struct node* tnode = stu -> head;
	while( tnode -> next != NULL ){
		tnode = tnode -> next;
		index ++;
		if( tnode -> key == fchar ){
			return index;
		}
	}
	return -1;
}

//在链表有限个元素里面插入一个字符
insert( struct student* stu ){
	printf("请输入要插入的字符，格式为：位置,字符\n");
	int locate;
	int ichar;
	scanf("%d,%c",&locate,&ichar);
	if( locate<=0 || locate > stu->size ){
		printf("输入的范围不存在\n");
	}else{//输入的位置合格
		struct node*  tnode = (struct node* )malloc( sizeof(struct node) );
		if( tnode != NULL ){//成功获取节点
			tnode -> key = ichar;
			tnode -> next = NULL;
		}else{
			exit(0);
		}
		struct node* thead =  stu -> head;
		int index = 0;
		while( index < locate-1 ){
			thead = thead -> next;
			index ++;
		}
		tnode -> next = thead ->next;
		thead -> next = tnode;
		stu -> size ++;
	}
}

//显示全部的元素
showAll ( struct student* stu){
	 int index = stu -> size;
	 struct node* tnode = stu -> head;
	 while( index > 0 ){
		char tchar = tnode -> next -> key;
		tnode = tnode -> next;
	 	printf("%c\t",tchar );
		index --;
	 }
}

//这里初始化链表
init( struct student* stu ){
	
	stu -> head = (struct node* )malloc( sizeof(struct node) );
	stu -> end = stu -> head;
	stu -> size = 0;

	char temp;
	scanf("%c",&temp);
	while( temp != '\n' ){
		struct node*  tnode = (struct node* )malloc( sizeof(struct node) );
		tnode -> key = temp;
		tnode -> next = NULL;
		stu -> end -> next = tnode;
		stu -> end = tnode;
		stu -> size ++;
	  scanf("%c",&temp);
	}
}
