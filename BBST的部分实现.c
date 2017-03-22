#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//定义三个常量 用来标识递归中节点的插入信息
#define RIGHT 1
#define LEFT -1
#define CANCEL 0

struct node{
	int value;
	struct node* left;
	struct node* right;
	int bf;//平衡因子
};

struct tree{
	int size;
	struct node* root;
};

struct node* ll( struct node* f1 );
struct node* lr( struct node* f1 );
struct node* rl( struct node* f1 );
struct node* rr( struct node* f1 );
int insert( struct tree* te,struct node* pare, struct node* node,int value );

//AVL树的 实现
main(){

	struct tree te;
	init( &te );
	getInput( &te );
}

//中序遍历BBST
showAll( struct node* node ){
	if( node -> left != NULL ){
		showAll( node -> left );
	}
	printf("%d\t",node -> value );
	if( node -> right != NULL ){
		showAll( node -> right );
	}
};

//接受用户的输入
getInput( struct tree* te ){
	int value ;
	printf("输入要插入的数字,键入 -1 结束输入\n");
	scanf("%d",&value);
	bool flag = true;
	while( value != -1 ){
		if( flag ){
			insert( te,NULL,NULL,value);
			flag = false;
		}else{
			insert( te,te -> root,te -> root -> left,value );
		}
		printf("\n节点个数为：%d\n",te -> size );
		showAll( te -> root -> left );//因为多了一个头节点
		printf("\n");
		scanf("%d",&value);
	}
}

//初始化 BBSTroot 后面跟一个头节点
init( struct tree* te ){
	struct node* t = (struct node* )malloc(sizeof(struct node));
	t -> bf = 0;
	t -> left = NULL;
	t -> right = NULL;
	t -> value = -1;
	te -> root = t;
	te -> size = 0;
}

int insert( struct tree* te,struct node* pare, struct node* node,int value ){
	if( node != NULL ){

		int flag = CANCEL;
		if( node -> value > value ){//区分左节点 是否为空 
			if( node -> left == NULL ){
				flag = LEFT;
				struct node* t = (struct node* )malloc(sizeof(struct node));
				t -> value = value;
				t -> left = NULL;
				t -> right = NULL;
				t -> bf = 0;
				node -> left = t;
				flag = LEFT;
				node -> bf++;
				te -> size ++;
			}else{
				int f2 = insert( te,node,node -> left,value );//递归处理
				if( f2 != CANCEL ){//递归操作 插入了节点 处理完成后 子树的高度不变 递归传递 Cancel 默认信息
					node -> bf ++;
					if( node -> bf > 1 ){//产生了不平衡
						struct node* temp;
						switch( f2 ){
							case 1://lr类型
								temp = lr( node );
								break;
							case -1://ll类型
								temp = ll( node );
								break;
						}	
						if( pare -> left == node ){//节点是父节点的左节点
							pare -> left = temp;
						}else{
							pare -> right = temp ;
						}
					}
				}
			}
				//flag = LEFT;
		}else if( node -> value < value ){//节点值小于要插入的值 区分右节点 是否为空

			if( node -> right == NULL ){
				flag = RIGHT;
				struct node* t = (struct node* )malloc(sizeof(struct node));
				t -> value = value;
				t -> left = NULL;
				t -> right = NULL;
				t -> bf = 0;
				node -> right = t;
				flag = RIGHT;
				node -> bf--;
				te -> size ++;
			}else{
				int f2 = insert( te,node,node -> right ,value );//递归处理
				if( f2 != CANCEL ){//递归操作 插入了节点 处理完成后 子树的高度不变 递归传递 Cancel 默认信息
					node -> bf --;
					if( node -> bf < -1 ){//产生了不平衡
						struct node* temp;
						switch( f2 ){
							case 1://rr类型
								temp = rr( node );
								break;
							case -1://rl类型
								temp = rl( node );
								break;
						}	
						if( pare -> left == node ){//节点是父节点的左节点
							pare -> left = temp ;
						}else{
							pare -> right = temp ;
						}
					}
				}
			}

		//	flag = RIGHT;
		}else{//节点值和要插入的值相等 返回取消
			printf("\n输入的值存在");
		}
			return flag;


	}else{//提供 的节点指针值为NULL
		struct node* t = (struct node* )malloc(sizeof(struct node));
		t -> value = value;
		t -> left = NULL;
		t -> right = NULL;
		t -> bf = 0;
		te -> root -> left = t;//root 节点后的 头节点的 左节点 作为第一个节点
		te -> size ++;
	}
}

//ll型的插入的旋转,传入的是父节点对这个节点的引用,之后放回新的 root 节点
struct node* ll( struct node* f1 ){
	struct node* f2 =  f1 -> left;

	struct node* a =  f1 -> right;
	struct node* b =  f2 -> right;

	f2 -> right = f1;
	f1 -> left = b;
	//处理旋转后 的平衡因子
	f1 -> bf = 0;
	f2 -> bf = 0;
	return f2;
}
//lr型的插入的旋转
struct node* lr( struct node* f1 ){
  struct node* f2 =  f1 -> left;
	struct node* f3 =  f2 -> right;

	struct node* a =  f1 -> right;
	struct node* b =  f2 -> left;
	struct node* c =  f3 -> left;
	struct node* d =  f3 -> right;
  
	//进行一次左旋
	f1 -> left = f3;
	f3 -> left = f2;
	f2 -> right = c;
	//一次右旋
	return ll( f1 );
}
//rr型的插入的旋转
struct node* rr( struct node* f1 ){
  struct node* f2 =  f1 -> right;

	struct node* a =  f1 -> left;
	struct node* b =  f2 -> left;
	
	f2 -> left = f1;
	f1 -> right = b;
	//处理旋转后 的平衡因子 
	f1 -> bf = 0;
	f2 -> bf = 0;
	return f2;
}
//rl型的插入的旋转
struct node* rl( struct node* f1 ){
  struct node* f2 =  f1 -> right;
	struct node* f3 =  f2 -> left;

	struct node* a =  f1 -> left;
	struct node* b =  f2 -> right;
	struct node* c =  f3 -> left;
	struct node* d =  f3 -> right;
	//进行一次右旋
	f1 -> right = f3;
	f3 -> right = f2;
	f2 -> left = d;
	//进行一次右旋
	return rr( f1 );
}
