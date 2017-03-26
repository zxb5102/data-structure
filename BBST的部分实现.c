#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//定义三个常量 用来标识递归中节点的插入信息
#define RIGHT 1
#define LEFT -1
#define CANCEL 0

/*struct patter{
	struct node* node;
	struct node* pare;
};*/
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

bool delete( struct tree* te, struct node* pare,struct node* node,int value );
bool dealNode( struct node* node,struct node* pare);
struct node* getFront( struct node* node );
bool dealbf( struct node* node ,struct node* pare,int flag,bool nextFlag );
struct node* ll( struct node* f1 );
struct node* lr( struct node* f1 );
struct node* rl( struct node* f1 );
struct node* rr( struct node* f1 );
int insert( struct tree* te,struct node* pare, struct node* node,int value );

//AVL树的 实现
main(){

	struct tree te ;
	init( &te );
	getInput( &te );
	delete( &te,te.root,te.root -> left,1);
	showAll( te.root -> left );
	printf("\n");
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
				struct node* t = (struct node* )malloc(sizeof(struct node));
				t -> value = value;
				t -> left = NULL;
				t -> right = NULL;
				t -> bf = 0;
				node -> left = t;
				if( node -> bf == -1 ){//判断 添加节点 对父节点的高度是否有影响
					flag = CANCEL;
				}else{
					flag = LEFT;
				}
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
					}else if( node -> bf == 1){
					//递归操作后 当前的节点的保持了 平衡 但是 高度增加了 放回值 通知父节点
					//bf == 1 原来节点 为 0 平衡状态 添加后 节点 的高度改变但是任然是平衡
						flag = LEFT;	
					}
				}
			}
				//flag = LEFT;
		}else if( node -> value < value ){//节点值小于要插入的值 区分右节点 是否为空

			if( node -> right == NULL ){
				struct node* t = (struct node* )malloc(sizeof(struct node));
				t -> value = value;
				t -> left = NULL;
				t -> right = NULL;
				t -> bf = 0;
				node -> right = t;
				if( node -> bf == 1 ){//判断 添加节点 对父节点的高度是否有影响
					flag = CANCEL;
				}else{
					flag = RIGHT;
				}
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
					}else if( node -> bf == -1 ){//原来是 0 的平衡度 添加节点平衡度改变 增高 向上传递
						flag = RIGHT;
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
//下面是删除节点维持平衡的逻辑

//递归删除节点
bool delete( struct tree* te, struct node* pare,struct node* node,int value ){
	int flag ;//这个 flag 用来标识节点是在左边删除了，还是在右边删除了
	bool nextFlag;//用来标识 递归 放回的是在左边还是在右边

	//判读当前的节点是否为 NULL 
	if( node != NULL ){
		if( node -> value == value ){
			//寻找到要删除的节点 判读 左右孩子 来选择删除方案
			bool tflag = dealNode( node,pare );//返回是否删除了节点
			if( tflag == false ){
				struct node* front = getFront( node );
				int t1 = front -> value;
				delete( te,pare,node,front -> value );//递归删除前继节点
				node -> value = t1;
			}
			te -> size --;
			nextFlag = true;
			flag = CANCEL;
		}else if( node -> value > value ){//节点值大于要删除的值
			nextFlag = delete( te, node,node -> left,value );
			flag = LEFT;
		}else{//节点值小于要删除的值
			nextFlag = delete( te,node,node -> right,value );
			flag = RIGHT;
		}
		
		//根据递归返回的 nextFlag 和 flag 判断当前的节点是否满足平衡,不平衡进行相应的判读
		//后旋转平衡，判断是否要修改 nextFlag 的值
		if( flag != CANCEL ){
			nextFlag = dealbf( node,pare,flag,nextFlag );
		}

	}else{//没有当前要删除的值

		nextFlag = false;
	}

	return nextFlag;
}
//删除当前节点的方法
bool dealNode( struct node* node,struct node* pare){
	bool flag = true;
	if( node -> left == NULL && node -> right == NULL ){//没有子女节点
		if( pare -> left == node ){
			pare -> left = NULL;
		}else{
			pare -> right = NULL;
		}
		free( node );
	}else if( node -> left != NULL && node -> right != NULL ){//含有两个节点
		//将要删除的节点转移到 删除它的中序遍历下的前继节点
		/*struct patter* tnode = getFront( node );
		int value = tnode -> node -> value;
		dealNode( tnode -> node,tnode -> pare );
		free( tnode );//删除 传输信息的节点
		node -> value = value;//将 实际要删除的节点的值替换
		*/
		flag = false;
	}else{//含有一个节点 改变父节点的指向 删除要删除的节点
		struct node* t ;
		if( node -> left != NULL ){//获取那个不空的子女节点
			t = node -> left;
		}else{
			t = node -> right;
		}
		if( pare -> left == node ){//父节点的左节点指向当前要删除的节点
			pare -> left = t; 
		}else{
			pare -> right = t;
		}
		free( node );//删除节点
	}
	return flag;
}

//这个节点肯定还有 前继节点 因为 它还有俩个孩子,
struct node* getFront( struct node* node ){
	struct node* front ;
	front = node -> left;
	while( front -> right != NULL ){
		front = front -> right;
	}
	/*struct patter* pat = (struct patter*)malloc( sizeof(struct patter) );
	pat -> node = front;
	pat -> pare = pare;*/
	return front;//返回中序前继节点,和它的父节点
}



//检测当前 节点 是否满足平衡 进行相应的旋转
//当前方法正确的条件 删除节点 后 产生了不平衡，旋转回来后会降低高度 ,
//所以只要递归删除的时候，递归返回删除成功了，那么当前的节点的 bf 值必须改变。
bool dealbf( struct node* node ,struct node* pare,int flag,bool nextFlag ){
	bool new_flag;
	if( nextFlag == true ){
		int tbf = node -> bf + flag;//判断平衡因子
		int nextbf;
		if( tbf >= 2 || tbf <= -2 ){
			if( flag == LEFT ){//获取右节点的 bf  ，并且右边节点不可能为空
				nextbf = node -> right -> bf;	
			}else{
				nextbf = node -> left -> bf;
			}
			//判断旋转的方法
			struct node* tnode;
			if( tbf > 0 && nextbf >0 ){//ll类型旋转
				tnode = ll( node );
			}else if( tbf < 0 && nextbf < 0 ){//rr类型旋转
				tnode = rr( node );
			}else if( tbf < 0 && nextbf >0 ){//rl类型的旋转
				tnode = rl( node );
			}else{//lr类型的旋转
				tnode = lr( node );
			}
			//更改旋转后的父节点指向
			if( pare -> left == node ){//父节点的左节点指向，当前不平衡的节点
				pare -> left = tnode;
			}else{
				pare -> right = tnode;
			}
			//因为删除节点，不平衡后，旋转导致，高度变化了，父节点任然收到影响，任然需要进行 平衡检测
			//删除节点后 旋转搞平衡 节点高度必定降低
			new_flag = true;
		}else{//删除节点平衡后的情况
			if( node -> bf != 0 ){//当前节点，删除节点后虽然平衡,当高度改变了，上面的节点任然要进行判断
				new_flag = true;
			}else{
				new_flag = false;
			}
			node -> bf = tbf;//删除节点后节点任然平衡,更新平衡因子
		}
	}else{
		new_flag = nextFlag;
	}
	return new_flag;
}
