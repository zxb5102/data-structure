#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//构建排序二叉树（BST） 搜索二叉树节点总作为叶节点插入进来 
struct tree{
	int size;
	struct node* root;
};
struct node{
	int value;
	struct node* right;
	struct node* left;
};
struct flag{//作为搜索二叉树后的信号返回
	bool flag ;// true 代表已经找到这个节点 link 是这个节点 false 代表未找到这个节点，返回关联的节点
	struct node* link;
};

struct flag* getNode( struct tree* te, int value );
struct node* getFront( struct tree* te,struct node* node );
struct node* getPare( struct tree* te,struct node* node);
bool delete ( struct tree* te, int value );

main(){
	struct tree te;
	initTree( &te );
	input( &te );
	getDel( &te );
	show( &te );
}

//接受用户的输入
getDel( struct tree* te ){
	int tval ;
	printf("\n输入要删除的节点值：");
	scanf("%d",&tval);
	while( tval != -1 ){
		if( te -> size < 1 ){
			printf("\nBST当前节点为0");
			break;
		}else{
			if( delete( te,tval ) ){
				show( te );
				printf("\nBST的节点个数：%d\n",te -> size );
			}else{
				printf("\n不存在当前节点\n");
			}
			scanf("%d",&tval);
		}

	}

}

//接受用户的输入
input ( struct tree* te){
	int tval ;
	scanf("%d",&tval);
	show( te );
	
	while( tval != -1 ){
		insert( te,tval );
		show( te );
		scanf("%d",&tval);
	}
}

//将数据插入到二叉排序树中
insert( struct tree* te ,int value ){
	struct flag* flag = getNode( te,value );
	if( flag -> flag == true ){
	}else{//元素不存在 构造新节点 插入
		
		struct node* t = ( struct node* )malloc( sizeof(struct node)*1 );
		t -> value = value;
		int temp = flag -> link -> value ;

		if( temp < value ){//比节点值大 插入到右节点中
			flag -> link -> right = t;
		}else{//比节点值小，插入到左节点中
			flag -> link -> left = t;
		}
		te -> size ++;

	}
}

//初始化树
initTree ( struct tree* te ){
	//struct node t = ( struct node* )malloc( sizeof(struct node)*1 );
	te -> size = 0;
	te -> root = NULL;
}

//根据 搜索树和要查找的值 返回 一个 flag
struct flag* getNode( struct tree* te, int value ){

	struct node* t = ( struct node* )malloc( sizeof(struct node)*1 );
	t -> value = value;
	
	struct flag* flag = (struct flag*)malloc( sizeof(struct flag)*1 );//构建用于返回的 flag

	if( te -> root != NULL ){
		struct node* temp = te -> root ;
		struct node* parent ;//定义一个父引用
		while( temp != NULL ){
			parent = temp;
			if( temp -> value > value ){
				temp = temp -> left;
			}else if( temp -> value < value ){
				temp = temp -> right;
			}else{//查找到了相应的 节点
				flag -> flag = true;
				flag -> link = temp;
				return flag;
			}
		}
		//程序到这里 说明没有找到相同的节点
		flag -> flag = false;
		flag -> link = parent;
	}else{//第一次插入
		te -> root = t;
		flag -> link = t;
		flag -> flag = true;
		te -> size ++;
	}
	return flag;
}

//中序遍历 BST 使用递归的算法
show( struct tree* te){
	printf("\n");
 if( te -> root != NULL ){
 	recursion( te -> root );
 }
	printf("\n");
}

//递归中序遍历算法
recursion ( struct node* node){
	if( node -> left != NULL){
		recursion( node -> left );
	}
	printf("%d\t", node -> value);
	if( node -> right ){
		recursion( node -> right );
	}
}
/*含有一个左右节点 区分有无父节点 
 *含有两个子节点 递归处理
 *无子节点
 *
 */
//删除操作，用删除节点的中序遍历的前继节点 填补
bool delete ( struct tree* te, int value ){
	struct flag* flag = getNode( te,value );
	if( flag -> flag == false ){//没有匹配到相应的节点
		return false;
	}else{//匹配到节点删除成功
		struct node* del = flag -> link;
		if( del -> left != NULL && del -> right != NULL ){

			struct node* front = getFront( te,del );//获取前继节点
			int val = front -> value;
			delete( te,front -> value );//递归删除
			del -> value = val;

		}else if( del -> left == NULL && del -> right == NULL ){
		
			struct node* pare = getPare( te,del );//获取父节点
			if( pare != NULL ){
				if( pare -> left == del ){
					pare -> left = NULL;
				}else{
					pare -> right = NULL;
				}
			}else{//删除BST的最后一个节点
				te -> root = NULL;
			}
			
			free( del );//删除节点
			te -> size --;
			
		}else{//这里只有一个左节点或一个右节点
			
			struct node* pare = getPare( te,del );//获取父节点
			struct node* t1 ;
			struct node* t2;//保存要删除节点的左右节点

			if( del -> right == NULL ){
					t2 = del -> left;
				}else{
					t2 = del -> right;
				}
			
			if( pare == NULL ){
			
				te -> root = t2;

			}else{

				if( pare -> left == del ){
					  pare -> left = t2 ;
				}else{
					  pare -> right = t2 ;
				}
				;
				
			}
			
			free( del );
			te -> size --;
		}
		return true;
	}

}

//获取某个已经存在节点的父节点
struct node* getPare( struct tree* te,struct node* node){
	int value = node -> value;
	struct node* temp = te -> root;
	struct node* parent = NULL;
	while( temp != NULL && temp -> value != node -> value ){
		parent = temp;
		if( value > temp -> value ){
			temp = temp -> right;
		}else{
			temp = temp -> left;
		}
	}
	return parent;
}
//寻找某个节点在中序遍历下的后继节点
struct node* getBack( struct tree* te,struct node* node ){

}


//寻找某个节点在中序遍历下的前继节点
struct node* getFront( struct tree* te,struct node* node ){
	struct node* t ;
	if( node -> left == NULL ){
		 t = getPare( te,node );//返回的前继节点可能为 NULL 
		return t;
	}else{
		 t = node -> left;
		while( t -> right != NULL ){
				t = t -> right;
		}
		return t;
	}
}
