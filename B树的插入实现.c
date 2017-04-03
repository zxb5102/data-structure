#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STEP 3 //step 的值必须要 >= 3

#define CANCEL 0//当前节点不进行操作
#define EXIT -1//作为在数组寻找元素的判断
#define JOIN 1//插入节点不进行分裂
#define BELLOW 2//接受下层传过来 的数据 这里不一定进行分裂
#define SPIT 3//对当前的 节点进行分裂处理

struct tree{
	int size;
	struct node* root;
};
struct node{
	int size;//记录当前的节点数目
	struct node* point[STEP + 1];//记录指针的指向
	int value[STEP];//value 值从小到大排列
};
struct msg{//作为递归返回来的消息 
	int flag;//告诉上层是否要进行插入操作
	int value;
	struct node* node;
};
struct qnode{
	struct qnode* next;
	struct node* node;
};
struct queue{
	int size;
	struct qnode* head; 
	struct qnode* end;
};

struct msg* bellow( struct msg* msg,struct node* node,int locate);
struct msg* insert( struct tree* te, struct node* node ,int value );
struct msg* spit( int value ,int locate,struct node* node );
main (){
	struct tree te;
	init( &te );
	getInput( &te );
}
initq( struct queue* qu){
	struct qnode* qnode = (struct qnode*)malloc( sizeof(struct qnode) );
	qnode -> next = NULL;
	qnode -> node = NULL;
	qu -> size = 0;
	qu -> head = qu -> end = qnode;
}
set( struct queue* qu,struct node* node ){
	
	struct qnode* qnode = (struct qnode*)malloc( sizeof(struct qnode) );
	qnode -> next = NULL;
	qnode -> node = node;

	qu -> end -> next = qnode;
	qu -> end = qnode;
	qu -> size ++;
}
struct qnode* get( struct queue* qu ){
	struct qnode* rnode = NULL ;
	if( qu -> size > 0){
		rnode = qu -> head -> next;
		qu -> head -> next = rnode -> next;
		qu -> size --;
		if( qu -> size == 0){
			qu -> end = qu -> head;
		}
	}
	return rnode;
}
init( struct tree* te){
	te -> size = 0;
	
	struct node* tnode = (struct node*)malloc( sizeof(struct node) );
	tnode -> size = 0;

	te -> root = tnode;
}
show( struct tree* te){
	struct queue qu;
	initq( &qu );
	set( &qu,te -> root );

	int size = qu.size;
	int i,j;
	struct qnode* tnode;
	struct node* node;
	int* ary;
	struct node** pary;
	while( size > 0 ){
		printf("==>");
		for( i=0;i<size;i++){
			tnode = get( &qu );
			node = tnode -> node;//输出信息
			free( tnode );
			ary = node -> value;
			for( j=0; j<node -> size ;j++){
				printf("%d\t",ary[j]);
			}
			printf("|\t");
			//加入队列
			pary = node -> point;
			for( j=0; j < node -> size + 1;j++ ){
				if( pary[j] != NULL ){
					set( &qu,pary[j] );
				}
			}
		}
		printf("\n");
		//更新 i 值
		size = qu.size;
	}
	// free the queue
	free( qu.head );

}
getInput( struct tree* te){
	int value;
	printf("情输入要键入的值 输入 -1 结束输入 \n");
	scanf("%d",&value);
	while( value != -1 ){
		insert( te,te -> root,value );
		show( te );
		scanf("%d",&value);
	}
}
struct msg* insert( struct tree* te, struct node* node ,int value ){
	int i;
	int* ary = node -> value;
	struct node** pary = node -> point;
	struct msg* rmsg = (struct msg*)malloc( sizeof(struct msg) );// return msg
	for( i=0; i < node -> size ; i++ ){
		if( ary[i] < value ){
			continue;
		}else if( ary[i] == value ){
			// cancael msg 
			rmsg -> flag = EXIT;
		}else{// this node is > value 
			break;
		}	
	}
	// get the point 
	if( rmsg -> flag != EXIT ){
		if( pary[i] == NULL ){// this level is the last
		//judge whether can insert	
		if( node -> size + 1 >= STEP ){// msg is SPIT
			rmsg -> flag = SPIT;
		}else{
			//msg is join
			rmsg -> flag = JOIN;
		}
		}else{
			struct msg* tmsg = insert( te,pary[i],value );
			rmsg -> flag = tmsg -> flag;
			rmsg -> value = tmsg -> value;
			rmsg -> node = tmsg -> node;
			free( tmsg );
		}
	}

	//deal the msg 
	if( rmsg -> flag == JOIN ){
		join( node,value,i+1 );
		rmsg -> flag = CANCEL;
	}else if( rmsg -> flag == CANCEL ){

	}else if( rmsg -> flag == EXIT ){
		
	}else if( rmsg -> flag == BELLOW ){
		struct msg* mmsg = bellow( rmsg ,node,i+1);
		rmsg -> flag = mmsg -> flag;
		rmsg -> value = mmsg -> value;
		rmsg -> node = mmsg -> node;
		free( mmsg );
	}else if( rmsg -> flag == SPIT ){
		struct msg* mmsg = spit( value,i+1,node);
		rmsg -> flag = BELLOW;
		rmsg -> value = mmsg -> value;
		rmsg -> node = mmsg -> node;
		free( mmsg );
	}
	//whether first node
	if( te -> root == node ){
		if( rmsg -> flag == BELLOW ){
			deal( rmsg,te );
		} 
		if( rmsg -> flag != EXIT ){
			te -> size ++;//the size inc
		}
		free( rmsg );
	}
	return rmsg;
}
deal( struct msg* msg,struct tree* te ){
	struct node* root = te -> root;
	struct node* troot = (struct node*)malloc( sizeof(struct node) );

	(troot -> value)[0] = msg -> value;
	troot -> size = 1;
	(troot -> point)[0] = root;
	(troot -> point)[1] = msg -> node;

	te -> root = troot;
}
struct msg* bellow( struct msg* msg,struct node* node,int locate){
	int ivalue = msg -> value;
	struct node* inode = msg -> node;
	int size = node -> size;
	
	struct msg* rmsg = (struct msg*)malloc( sizeof(struct msg) );
	rmsg -> value = 0;//init

	int middle;
	if( (size+1) % 2 != 0 ){
		middle = (size+2)/2;
	}else{
		middle = (size+1)/2;
	}

	if( size + 1 >= STEP ){
		rmsg -> flag = BELLOW;
		struct msg* mmsg = spit( ivalue,locate,node );

		rmsg -> value = mmsg -> value;
		rmsg -> node = mmsg -> node;
		rmsg -> flag = BELLOW;
		struct node* tnode = mmsg -> node;

		struct node** tpoint = tnode -> point;
		int i;
		int dex;
		if( locate == middle ){
			dex = 0;
			tpoint[0] = inode;
			dex ++;
			for( i=locate;i<=size;i++,dex++){
				tpoint[dex] = (node -> point)[i];
				(node -> point)[i] = NULL;
			}
		}else if( locate < middle ){
			for( dex=0,i=middle -1; i<=size;i++,dex++ ){
				tpoint[dex] = (node -> point)[i];
				(node -> point)[i] = NULL;
			}
			//move front point
			for( i=middle-1;i>=locate+1;i--){
				(node -> point)[i] = (node -> point)[i-1];
			}
			(node -> point)[locate] = inode;
		}else if( locate > middle ){
			for( dex=0,i=middle;i<=size;i++,dex++ ){
				if( i+1 == locate + 1 ){
					tpoint[dex] = inode;
					dex++;
				}
				tpoint[dex] = (node -> point)[i];
				(node -> point)[i] = NULL;
			}
			if( size+1 +1 == locate + 1){//这里考虑到 例如 元素个数是3 要插入到 4 的位置的情况
					tpoint[dex] = inode;
					dex++;
			}
		}
	}else{
	//this is join 
		int i;
		rmsg -> flag = CANCEL;
		int* ary = node -> value;
		struct node** pary = node -> point;
		
		for( i=size ;i>=locate;i-- ){
			ary[i] = ary[i-1];
		}
		ary[locate -1] = ivalue;
		for( i=size +1 ;i>=locate+1;i-- ){
			pary[i] = pary[i-1];
		}
		pary[locate] = inode;
		node -> size ++;
	}
	return rmsg;
}
join( struct node* node,int value,int locate ){
	int* ary = node -> value;
	int size = node -> size;
	int i;
	for( i=size; i >= locate ;i-- ){
		ary[i] = ary[i-1];
	}
	ary[locate -1] = value;
	node -> size ++;
}

struct msg* spit( int value ,int locate,struct node* node ){

	struct msg* rmsg = (struct msg*)malloc( sizeof(struct msg) );
	struct node* rnode = (struct node*)malloc( sizeof(struct node) );
	int middle = node -> size;
	int i;
	int dex;
	if( (middle + 1) % 2 != 0){
		middle = (middle + 2)/2;
	}else{
		middle = (middle + 1)/2;
	}
	int allsize = node -> size;
	if( locate == middle ){
		for( dex=0,i=middle - 1; i < allsize ;i++,dex++ ){
			(rnode -> value)[dex] = (node -> value)[i];
			(node -> value)[i] = 0;
			rnode -> size ++;
			node -> size --;
		}
		//node -> size ++;
		//(node -> value)[locate -1] = value;
		rmsg -> value = value;
	}else if( locate < middle ){
		for( dex=0,i=middle - 1; i < allsize ;i++,dex++ ){
			(rnode -> value)[dex] = (node -> value)[i];
			(node -> value)[i] = 0;
			rnode -> size ++;
			node -> size --;
		}
		rmsg -> value = (node -> value)[middle -2];
		//move the front element
		for( i=middle-1; i >= locate  ;i-- ){
			(node -> value)[i] = (node -> value)[i-1];
		}
		(node -> value)[locate -1] = value;
	}else{
		for( dex=0,i=middle; i < node -> size ;i++,dex++ ){
			if( middle +1 == locate ){
				(rnode -> value)[dex] = value;
				dex++;
				rnode -> size ++;
			}
			(rnode -> value)[dex] = (node -> value)[i];
			(node -> value)[i] = 0;
			rnode -> size ++;
			node -> size --;
		}
		if( allsize +1  == locate ){
				(rnode -> value)[dex] = value;
				dex++;
				rnode -> size ++;
		}
		rmsg -> value = (node -> value)[middle -1];
		(node -> value)[middle -1] = 0;
		node -> size --;
	}
	rmsg -> node = rnode;
	return rmsg;
}
