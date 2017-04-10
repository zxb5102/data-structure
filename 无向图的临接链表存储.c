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

struct queue{
	int size;
	struct qnode* head;
	struct qnode* end;
};
struct qnode{
	struct vnode* node;
	struct qnode* next;
};
struct stack{
	int size;
	struct snode* head;
};
struct snode{
	struct vnode* node;
	struct snode* next;
};
struct chain{
	int size;
	int next;
	char* cary;
};
bool isVnode( struct vary* vary,char value );
struct vnode* varyInsertValue( struct vary* vary,char value );
bool isLinkValue( struct lary* lary,int value );
bool lvarInsertValue( struct lary* lary,char value );
struct lary* getLary( struct vary* vary,char value);
struct vnode* varyInsertValue( struct vary* vary,char value );
addValue( struct vary* tvary,char begin,char end );
struct qnode* deQueue( struct queue* qu );
struct snode* pop( struct stack* st );
struct vnode* getVnode( struct vary* vary,char ch );
bool connected( struct vary* vary, char a,char b );
bool toPath( struct vary* vary, struct chain* chain,struct vnode* vnode,char tar ,struct chain* paths );
struct chain* getPath( struct vary* vary ,char begin,char tar );

main(){
	struct vary tvary;
	initVary( &tvary );
	getInput( &tvary );
	showPath( &tvary );

}
//判读某个元素 是否已经存在于 链表中
bool isExist( struct chain* chain,char find ){
	bool flag = false;
	int i;
	int size = chain -> next;
	char* cary = chain -> cary;
	for( i=0; i < size ;i++ ){
		if( cary[i] == find ){
			flag = true;
			break;
		}
	}
	return flag;
}
//添加一个新的元素到 链表中 
addValueToChain( struct chain* chain,char value ){
	bool flag;
	if( !isExist( chain,value ) ){
		char* cary = chain -> cary;
		int loca = chain -> next;
		cary[loca] = value;

		chain -> next ++;
		flag = true;
	}else{
		flag = false;
	}
	return flag;
}
//初始化 已经遍历的值 的链表  
initChain( struct chain* chain ,int size ){
	chain -> cary = (char*)malloc( sizeof(char)* size );
	chain -> size = size;
	chain -> next = 0;
}
//输出两个节点间的路径
showPath( struct vary* vary ){
	char begin,tar;
	printf("输入你想要 查询的两个节点的 格式：a,b 键入一个#值 结束寻找\n");
	scanf("%c,%c",&begin,&tar);
	getchar();
	//while( begin != '#' && tar != '#' ){
		struct chain* ch = getPath( vary,begin,tar );
		if( ch == NULL ){
			printf("当期俩个节点没有通路\n");
		}else{
			showChain( ch );
		}	
		//scanf("%c,%c",&begin,&tar);
		//getchar();
	//}

}
showChain( struct chain* ch ){
	if( ch != NULL ){
		char* chr = ch -> cary;
		int all = ch -> size;
		int i;
		for( i=0; i < all ;i++ ){
			printf("%c\t",chr[i]);
		}
	}
	printf("\n");
}
//根据 开始值 和 结束值 利用深度优先搜索的方法 找到一条路径
struct chain* getPath( struct vary* vary ,char begin,char tar ){
	struct chain* ch;
	if( isVnode( vary,begin ) && isVnode( vary,tar ) ){
		struct chain chain;
		initChain( &chain,vary -> size );
		struct vnode* tnode = getVnode( vary,begin );

		struct chain paths;
		initChain( &paths,vary -> size );
		bool flag = toPath( vary,&chain,tnode,tar,&paths );
		if( flag ){
			ch = &chain;
		}else{
			ch = NULL;
		}
	}else{
		ch = NULL;
	}
	return ch;
}
bool toPath( struct vary* vary, struct chain* chain,struct vnode* vnode,char tar ,struct chain* paths ){
	// chain 是最终的连通路径 paths 是判读是否当前节点被访问过了
	bool flag;
	if( !isExist( paths,vnode -> value ) ){
		int dex = chain -> next;
		char* cary = chain -> cary;
		if( vnode -> value == tar ){
			cary[ dex ] = vnode -> value ;
			chain -> next ++;
			flag = true;
		}else{
			addValueToChain( paths,vnode -> value );// 将当期节点添加到 以遍历的数组中
			struct stack st;
			initStack( &st );
			batAddToStack( vary,&st,vnode -> right );

			chain -> next ++;
			struct vnode* tvnode;
			struct snode* tsnode;
			bool flag2 = false;
			char temp = vnode -> value;
			while( st.size > 0 ){
				tsnode = pop( &st ); 
				tvnode = tsnode -> node;
				//temp = tvnode -> value;

				flag2 = toPath( vary,chain,tvnode,tar,paths );
				if( flag2 == true){
					break;
				}
			}
			if( flag2 ){
				cary[ dex ] = temp;
				flag = true;
			}else{
				chain -> next --;
			}
			
		}
	}else{
		flag = false;
	}

	return flag;
}
//从一个链接数组中添加 vnode 到stack中
batAddToStack( struct vary* vary,struct stack* st,struct lary* lary ){
	int size = lary -> size;
	struct vnode* tnode ;
	struct lnode* tlnode = lary -> head -> right;
	while( size > 0 ){
		tnode = getVnode( vary,tlnode -> value );
		push( st,tnode );
		
		tlnode = tlnode -> right;
		size --;
	}
}
//判断某个元素是否在数组里面
initStack( struct stack* st ){
	struct snode* tnode = (struct snode*)malloc( sizeof(struct snode) );
	tnode -> next = NULL;
	tnode -> node = NULL;
	 
	st -> size = 0;
	st -> head = tnode;
}
//初始化队列
initQueue( struct queue* qu ){
	struct qnode* tnode = (struct qnode*)malloc( sizeof(struct qnode) );
	tnode -> next = NULL;
	tnode -> node = NULL;
	
	qu -> size = 0;
	qu -> head = qu -> end = tnode;
}
//入栈操作
push( struct stack* st,struct vnode* node ){
	struct snode* tnode = (struct snode*)malloc( sizeof(struct snode) );
	tnode -> next = st -> head -> next;
	tnode -> node = node;
	
	st -> head -> next = tnode;
	st -> size ++;
}
//出栈 当栈为空时候返回一个NULL
struct snode* pop( struct stack* st ){
	struct snode* tnode = st -> head -> next;
	if( st -> size > 0 ){
		st -> head -> next = tnode -> next;
		st -> size --;
	}
	return tnode;
}
//出队 当返回NULL 时，队列为空
struct qnode* deQueue( struct queue* qu ){
	struct qnode* tnode = qu -> head -> next;
	if( qu -> size > 0 ){
		qu -> head -> next = tnode -> next;
		qu -> size --;
		if( qu -> size == 0 ){
			qu -> end = qu -> head;
		}
	}
	return tnode;
}
enQueue( struct queue* qu ,struct vnode* node ){
	struct qnode* tnode = (struct qnode*)malloc( sizeof(struct qnode) );
	tnode -> next = NULL;
	tnode -> node = node;

	qu -> end -> next = tnode;
	qu -> end = tnode;
	qu -> size ++;
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
//根据相关的 值 放回 vary 里面的 vnode
struct vnode* getVnode( struct vary* vary,char ch ){
	struct vnode* tnode;
	if( isVnode( vary,ch ) ){
		struct vnode* ttnode = vary -> head -> bottom;
		while( ttnode != NULL ){
			if( ttnode -> value == ch ){
				tnode = ttnode;
				break;
			}else{
				ttnode = ttnode -> bottom;
			}
		}
	}else{
		tnode = NULL;
	}
	return tnode;
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
