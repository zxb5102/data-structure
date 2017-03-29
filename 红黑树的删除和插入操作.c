#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct tree{
	int size;
	struct node* root;
};
struct node{
	int color;
	struct node* left;
	struct node* right;
	int value;
};
struct rec{
	int flag;
	struct node* node;
};
//定义三个常量 用来标识递归中返回的信息
#define CHECK 1//进行检查
#define SKIP -1//跳过检查 直接凭借
#define CANCEL 0//不进行任何操作

#define FIRSTNODE true//这是第一个节点
#define BLACK 1//黑色
#define RED 0//红色
#define NOCOLOR -1//当前节点为空 没有颜色属性


int getFront( struct node* node );
struct rec* dealFalg( struct node* pare,struct node* node, struct rec* flag );
struct rec* insert( struct tree* te, struct node* pare ,struct node* node,int value );
struct node* ll( struct node* pare,struct node* node );
struct node* lr( struct node* pare,struct node* node );
bool delete( struct node* pare,struct node* node,int value );
main (){
//初始化 红黑树的时候把头节点的 颜色 设置为没哟颜色 的NOCOLOR
	struct tree te;
	init( &te );
	getInput( &te );
	getDel( &te );
}

getDel( struct tree* te ){
	int value ;
	printf("键入想要删除的节点值 输入 -1 代表结束\n");
	scanf("%d",&value);
	while( value != -1 ){
		if( te -> size >0 ){
			bool flag =	delete( te -> root,te -> root -> left,value );
			if( flag == true ){
				te -> size --;
				show( te );
			}else{
				printf("没有当前节点\n");
			}
		}else{
			printf("节点数为0\n");
			break;
		}
		scanf("%d",&value);
	}
}

bool delete( struct node* pare,struct node* node,int value ){
	bool flag ;
	if( node -> value > value ){
		if( node -> left != NULL ){
			flag = delete( node,node -> left,value );
		}else{
			flag = false;
		}
	}else if( node -> value < value ){
		if( node -> right != NULL ){
			flag = delete( node,node -> right,value );
		}else{
			flag = false;
		}
	}else{
		if( node -> left == NULL && node -> right == NULL ){//直接删除没有左右孩子的节点
			if( pare -> left == node ){
				pare -> left = NULL;
			}else{
				pare -> right = NULL;
			}	
			free( node );
			flag = true;

		}else if( node -> left != NULL && node -> right != NULL ){
			int tvalue = getFront( node );
			flag = delete( pare,node,tvalue);//接着从这个节点往下递归删除节点
		}else{
			struct node* tnode ;//用来保存那个不为NULL 的节点
			if( node -> left != NULL ){
				tnode = node -> left;
			}else{
				tnode = node -> right;
			}
			if( pare -> left == node ){
				pare -> left = tnode;
			}else{
				pare -> right = tnode;
			}
			free( node );
			flag = true;
		}
	}
	return flag;
}

//返回 一个含有两个孩子的节点的 中序下的前继节点
int getFront( struct node* node ){
	struct node* front = node -> left;
	while( front -> right != NULL ){
		front = front -> right;
	}
	return front -> value;
}

getInput( struct tree* te ){
	int value ;
	printf("请输入要插入的数字 输入 -1 结束输入\n");
	scanf("%d",&value);
	while( value != -1 ){
		insert( te,te -> root,te -> root -> left,value );
		show( te );
		scanf("%d",&value);
	}
}
//传入一个 tree 
show( struct tree* te ){
	printf("节点个数：%d\n",te -> size);
	if( te -> root -> left != NULL ){
		showAll( te -> root -> left );
	}else{
		printf("当前的没有可以输出的节点");
	}
	printf("\n");
}
//传入第一个节点 不包含头节点
showAll( struct node* node ){
	if( node -> left != NULL ){
		showAll( node -> left );
	}	
	if( node -> color == BLACK ){
		printf("%d(BLACK)\t",node -> value);
	}else{
		printf("%d(RED)\t",node -> value);
	}
	if( node -> right != NULL ){
		showAll( node -> right );
	}
}

init ( struct tree* te ){
	te -> size = 0;
	struct node* tnode = (struct node*)malloc( sizeof(struct node) );
	tnode -> color = NOCOLOR;
	tnode -> value = -1;
	tnode -> left = NULL;
	tnode -> right = NULL;
	te -> root = tnode;
} 
struct rec* insert( struct tree* te, struct node* pare ,struct node* node,int value ){

	struct rec* flag = (struct rec*)malloc( sizeof(struct rec) );
	bool isfirst;
	if( te -> root -> left == node ){
		isfirst = FIRSTNODE;
	}else{
		isfirst = false;
	}
	if( node != NULL ){//考虑第一次插入的情况
		struct node* tnode;
		
		if( value > node -> value ){
				tnode = node -> right;
				if( tnode == NULL ){
					//生成节点
					//拼接
					//flag 里面的 flag 为CHECK
					//树的节点数加 + 
					struct node* inode = (struct node*)malloc( sizeof(struct node) );
					inode -> left = NULL;
					inode -> right = NULL;
					inode -> color = RED;
					inode -> value = value;
					node -> right = inode;
					flag -> flag = CHECK;
					te -> size ++;
				}else{
					flag = insert( te,node,node -> right, value );
				}
		}else if( value < node -> value ){
			tnode = node -> left;
			if( tnode == NULL ){//节点为空的情况 不递归 直接插入处理 
				//生成节点
				//拼接
				//flag 里面的 flag 为CHECK
				//树的节点数加 + 
				struct node* inode = (struct node*)malloc( sizeof(struct node) );
				inode -> left = NULL;
				inode -> right = NULL;
				inode -> color = RED;
				inode -> value = value;
				node -> left = inode;
				flag -> flag = CHECK;
				te -> size ++;
			}else{
				flag = insert( te,node ,node -> left,value );
			}
		}else{//出现相等的节点 拒绝插入
			printf("出现相同的节点 %d 拒绝插入 ",value);
			flag -> flag = CANCEL;
		}

	}else{//考虑第一次插入的情况
		struct node* inode = (struct node*)malloc( sizeof(struct node) );
		inode -> left = NULL;
		inode -> right = NULL;
		inode -> color = BLACK;
		inode -> value = value;
		pare -> left = inode;//第一次插入 节点 插入到 头结点的 左边
		flag -> flag = CANCEL;
		te -> size ++;
	}

	//无论是递归处理还是 直接添加节点 都需要检测 节点是否符合 红黑树的规则 
	flag = dealFalg( pare, node, flag );//处理后会返回一个新的的值给 flag 以通知 父节点是否需要进行处理

	if( isfirst ){//判断是否是第一节点，如果是第一个节点自己处理返回的信息
		flag = dealFalg( pare, node, flag );
		te -> root -> left -> color = BLACK;
		//printf("aaaaaaaaaaaaaaaaaa");
		free( flag );//这里是根节点 处理完信息 释放节点 的资源
	}
	
	return flag;
}

struct rec* dealFalg( struct node* pare,struct node* node, struct rec* flag ){
	//改方法里面读取玩递归信息需要把节点的 释放 生成一个新的节点返回 
	struct rec* recnode = (struct rec*)malloc( sizeof(struct rec) );
	int color ;
	switch( flag -> flag ){
		case CANCEL:
			recnode -> flag = CANCEL;
			break;
		case CHECK:
			color = node -> color;		
			int colorLeft,colorRight,colorPare;

			if( node -> left != NULL ){
				colorLeft = node -> left -> color;
			}else{
				colorLeft = NOCOLOR ;
			}
			if( node -> right != NULL ){
				colorRight = node -> right -> color;
			}else{
				colorRight = NOCOLOR;
			}
			//colorPare = pare -> color;//获取父节点的 颜色信息
			if( color == RED && colorLeft == RED ){//父 当前 左
				recnode -> flag = SKIP;
				recnode -> node = ll( pare,node );
			}else if( color == RED && colorRight == RED ){//父 当前 右
				//旋转过后 父节点 变颜色 父节点变指向
				recnode -> flag = SKIP;
				recnode -> node = lr( pare,node );
			}else if( colorLeft == RED && colorRight == RED ){//左 右
				//左右变颜色
				//父节点变颜色
				recnode -> flag = CHECK;
				inverse( pare,node );
			}else if( colorRight == RED ){//直接插入到右边的情况
				//旋转过后
				//父节点 变指向 节点颜色没有改变 上一级不需要改变
				recnode -> flag = CANCEL;
				rr( pare,node );
			}
			break;
		case SKIP://跳过检查直接拼接
			if( pare -> left == node ){
				pare -> left = flag -> node;
			}else{
				pare -> right = flag -> node;
			}
			recnode -> flag = CHECK;
			break;
	}
	free( flag );//释放 传递 过来的信号
	return recnode;
}
rr( struct node* pare,struct node* node ){//变换之后 父节点指向调整 颜色没有改变 上层不需要调整
	struct node* right =	node -> right; 
	struct node* rightL = right -> left;
	right -> left = node;
	node -> right = rightL;

	if( pare -> left == node ){
		pare -> left = right;
	}else{
		pare -> right = right;
	}

	right -> color = BLACK;
	node -> color = RED;
}
struct node* ll( struct node* pare,struct node* node ){
	struct node* left = node -> left;
	pare -> left = NULL;
	node -> right = pare;
	left -> color = BLACK;
	return node;
}
inverse( struct node* pare, struct node* node ){//反转颜色 上层检测 节点是否平衡 不传递节点
	struct node* right = node -> right;
	struct node* left = node -> left;
	left -> color = BLACK;
	right -> color = BLACK;
	node -> color = RED;
}
struct node* lr( struct node* pare,struct node* node ){
	struct node* right = node -> right;
	right -> left = node;
	right -> right = pare;
	node -> color = BLACK;
	node -> right = NULL;
	pare -> left = NULL;
	return right;
}
