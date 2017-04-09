#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct lnode{
	char value;
	struct lnode* right;
};

struct lary{//定义 和节点连通的 节点链表
	int size;
	struct lnode* head;
	struct lnode* end;
};

struct vnode{
	char value;
	struct vnode* bottom;
	struct lary* right;
};

struct vary{//定义 图节点的 节点链表
	int size;
	struct vnode* head;
	struct vnode* end;
};
bool isVnode( struct vary* vary,char value );
struct vnode* varyInsertValue( struct vary* vary,char value );
bool isLinkValue( struct lary* lary,int value );
bool lvarInsertValue( struct lary* lary,char value );
struct lary* getLary( struct vary* vary,char value);
struct vnode* varyInsertValue( struct vary* vary,char value );
addValue( struct vary* tvary,char begin,char end );

main(){
	struct vary tvary;
	initVary( &tvary );
	getInput( &tvary );
}
//打印连接数组
showLink( struct lary* lary ){
	if( lary != NULL ){
		struct lnode* tnode = lary -> head;
		while( tnode != NULL ){
			printf("%c\t",tnode -> value );
			tnode = tnode -> right;
		}
	}
}
show( struct vary* vary){
	struct vnode* tvnode = vary -> head -> bottom;
	struct lary* tlary;
	printf("--------------------------show----------------------------\n");
	while( tvnode != NULL ){
		printf("%c\t-->\t",tvnode -> value );
		showLink( tvnode -> right );
		printf("\n");
		tvnode = tvnode -> bottom;
	}
}
getInput( struct vary* tvary ){
	char begin,end;
	printf("请输入图中的边 格式：one,second 当 one 或是 second 中有一个是 # 时停止输入\n");
	scanf("%c,%c",&begin,&end );
	getchar();
	while( begin != '#' && end != '#' ){
		addValue( tvary,begin,end );
		show( tvary );
		scanf("%c,%c",&begin,&end );
		getchar();
	}
}
addValue( struct vary* tvary ,char begin,char end ){
	if( isVnode( tvary, begin ) ){
		struct lary* lary = getLary( tvary,begin );
		lvarInsertValue( lary,end );
	}else{
		struct vnode* vnode = varyInsertValue( tvary,begin );
		vnode -> right = (struct lary*)malloc( sizeof(struct lary) );
		initLary( vnode -> right );
		lvarInsertValue( vnode -> right,end );
	}
	if( isVnode( tvary,end ) ){
		struct lary* lary = getLary( tvary,end );
		lvarInsertValue( lary,begin );
	}else{
		struct vnode* vnode = varyInsertValue( tvary,end );
		vnode -> right = (struct lary*)malloc( sizeof(struct lary) );
		initLary( vnode -> right );
		lvarInsertValue( vnode -> right,begin );
	}
}
//在连接链表中 插入一个 新的值 返回是否插入成功
bool lvarInsertValue( struct lary* lary,char value ){
	bool flag;
	if( !isLinkValue( lary,value ) ){
		struct lnode* tnode = (struct lnode*)malloc( sizeof(struct lnode) );
		tnode -> value = value;
		tnode -> right = NULL;

		lary -> end -> right = tnode;
		lary -> end = tnode;
		lary -> size ++;
		flag = true;
	}else{
		flag = false;
	}
}
//判断某个 连接链表中是否存在某个节点
bool isLinkValue( struct lary* lary,int value ){
	bool flag = false;
	if( lary != NULL ){
		struct lnode* tnode = lary -> head; 
		while( tnode != NULL ){
			if( tnode -> value == value ){
				flag = true;
				break;
			}else{
				tnode = tnode -> right;
			}
		}
	}
	return flag;
}
//在 图节点 链表中 插入一个新的值，并返回连接链表 当返回一个空指针 的时候，代表当前节点存在，不允许插入
struct vnode* varyInsertValue( struct vary* vary,char value ){
	struct vnode* vnode;
	if( !isVnode( vary,value ) ){
		struct vnode* tnode = (struct vnode*)malloc( sizeof(struct vnode) );
		tnode -> value = value;
		tnode -> right = NULL;
		tnode -> bottom = NULL;

		vary -> end -> bottom = tnode;
		vary -> end = tnode;
		vary -> size ++;

		vnode = tnode;
	}else{
		vnode = NULL;
	}
	return vnode;
}
//返回一个节点的 连接链表 返回NULL代表 不存在当前的节点
struct lary* getLary( struct vary* vary,char value){
	struct vnode* tnode = vary -> head -> bottom;
	struct lary* lary = NULL;
	while( tnode != NULL ){
		if( tnode -> value == value ){
			lary = tnode -> right;
			break;
		}else{
			tnode = tnode -> bottom;
		}
	}
	return lary;
}
//判断 当前的节点是否在 图中存在
bool isVnode( struct vary* vary,char value ){
	bool flag = false;
	if( vary -> size == 0){
		flag = false;
	}else{
		struct vnode* tnode = vary -> head -> bottom;
		while( tnode != NULL ){
			if( tnode -> value == value ){
				flag = true;
				break;
			}else{
				tnode = tnode -> bottom;
			}
		}
	}
	return flag;
}

//初始化 连接链表
initLary( struct lary* lary ){
	struct lnode* tnode = (struct lnode*)malloc( sizeof(struct lnode) );
	tnode -> value = 0;
	tnode -> right = NULL;

	lary -> head = lary -> end = tnode;
	lary -> size = 0;
}
//初始化 图节点链表
initVary( struct vary* vary ){
	struct vnode* tnode = (struct vnode*)malloc( sizeof(struct vnode) );
	tnode -> value = 0;
	tnode -> bottom = NULL;
	tnode -> right = NULL;

	vary -> head = vary -> end = tnode;
	vary -> size = 0;
}
