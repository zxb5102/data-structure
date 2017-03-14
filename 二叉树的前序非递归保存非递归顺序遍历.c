#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//利用栈实现对二叉树的初始化
struct node{
	char value;
	struct node* left;
	struct node* right;
};
struct qnode{//队列中元素的节点
	struct qnode* next;
	struct node* value;
};
struct queue{
	struct qnode* head;
	struct qnode* end;
};
struct tree{
 int num;//二叉节点的数量
 struct node* root;//根节点
};
struct stack{//带有头节点
	int size;
	struct stackNode* head;
};
struct stackNode{
	struct stackNode* next;
	struct node** value;
};

bool insertStack( struct stack* stack ,struct node** value);
struct node** pop( struct stack* stack );
struct node*  dequeue( struct queue* que );

main(){

	struct stack stck;
	initStack( &stck );
	struct tree te ;
	initTree( &te ,&stck );
	showAll( &te );
}

//顺序遍历显示所有的节点
showAll( struct tree* te ){
	struct queue que;
	initQueue( &que );
	enter( &que,te -> root);
	//开始出队遍历元素
	struct node* tnode = dequeue( &que );
	while( tnode != NULL ){
		printf("%c\t",tnode -> value );
		if( tnode -> left != NULL ){
			enter( &que,tnode -> left );
		}
		if( tnode -> right != NULL ){
			enter( &que,tnode -> right );
		}
		tnode = dequeue( &que );
	}
	printf("\n");
}
enter( struct queue* que,struct node* value ){
	struct qnode* tnode = (struct qnode*)malloc(sizeof(struct qnode));
	tnode -> value = value;
	que -> end -> next = tnode;
	que -> end = tnode;
}

struct node*  dequeue( struct queue* que ){
	if( que-> head -> next != NULL){
		struct qnode* tnode = que -> head -> next;
		que -> head -> next = tnode -> next;
		if( que -> head -> next == NULL){
			que -> end = que -> head;
		}else{
			free(tnode);
		}
		struct node* t = tnode -> value;
		return t;
	}else{
		return NULL;
	}
}
//构造顺序显示二叉树的队列
initQueue( struct queue* que){
	struct qnode* tnode = (struct qnode*)malloc(sizeof(struct qnode));
	que -> head = tnode;
	que -> end = que -> head ;
}

initTree( struct tree* te,struct stack* stck ){
	printf("请输入前序遍历的二叉树的次序，空节点用?表示");
	char tchar;
	scanf("%c",&tchar);
	if( tchar != '?' ){
		struct node* tnode = (struct node*)malloc(sizeof(struct node));
		tnode -> value = tchar;
		te -> root = tnode;
		te -> num = 1;
		insertStack(stck,&(tnode -> right));	
		insertStack(stck,&(tnode -> left));	
	}else{
		te -> root = NULL;
		te -> num = 0;
		printf("二叉树为空");
		return ;
	}
	//完成了对root节点的 初始化
	scanf("%c",&tchar);
	struct node** tstack = pop( stck );
	if( tstack == NULL){
		printf("is null over\n");
	}
	while( tstack != NULL){
		if( tchar != '?' ){
			
			struct node* t2 = (struct node*)malloc(sizeof(struct node));
			t2 -> value = tchar;
			insertStack(stck,&(t2 -> right));	
			insertStack(stck,&(t2 -> left));	
			*tstack = t2;//为相应的节点指针赋值
			te -> num ++;//树的节点数量加一
		}else{
			tstack = NULL;
		}

		tstack = pop( stck );
		scanf("%c",&tchar);
	}

}

//实现一个存放节点的 栈 存储结构
initStack( struct stack* stck ){
	stck -> head = (struct stackNode*)malloc( sizeof(struct stackNode) );//这里动态分配未进行是否分配异常的检测
	stck -> size = 0;
}

struct node** pop( struct stack* stack ){
	if( stack -> size > 0 ){
	  struct stackNode* tnode = stack -> head -> next;
		stack -> head -> next = tnode -> next;
		stack -> size --;
		return tnode -> value;
	}else{
		return NULL;
	}
}

bool insertStack( struct stack* stack ,struct node** value){
	
	struct stackNode* tnode = (struct stackNode*)malloc( sizeof(struct stackNode) );//这里动态分配未进行是否分配异常的检测
	if( tnode != NULL ){
			tnode -> next = NULL;
			tnode -> value = value;
			//插入到栈顶，头结点的后面
			struct stackNode* tsnode = stack -> head -> next;
			tnode -> next = tsnode;
			stack -> head -> next = tnode;
			stack -> size ++;
		return true;
	}else{
		return false;
	}
}
