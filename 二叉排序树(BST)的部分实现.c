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

main(){
	struct tree te;
	initTree( &te );
	input( &te );
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
		//printf( "元素 %d 已经存在被抛弃",value );
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

recursion ( struct node* node){
	if( node -> left != NULL){
		recursion( node -> left );
	}
	printf("%d\t", node -> value);
	if( node -> right ){
		recursion( node -> right );
	}
}







