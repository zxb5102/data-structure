#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct vnode{ //值节点
	struct vnode* right;
	struct vnode* bottom;
	char value;
	int row,col;
};
struct nnode{//导航行节点,这里的导航节点是堆内存动态分配的
	struct nnode* right;
	struct vnode* bottom;
};
struct nnode_c{//导航列节点,这里的导航节点是堆内存动态分配的
	struct vnode* right;
	struct nnode_c* bottom;
};
struct cnode{ //总节点
	int num,row,col;//num是非空节点的个数，
	struct nnode* rhead;
	struct nnode_c* chead;
};
	//char get( struct conde* coll ,int row,int col );
main (){
	//初始化请求用户输入行和列
	
	struct cnode coll;
	init( &coll );
	insert( &coll );
	printf("\n");
	showAll(&coll);
}

char get( struct cnode* coll ,int row,int col ){
	struct nnode_c* tc ;
	int index;
	//导航到相应的行
	for( index=0;index<row;index++){
		if( index ==0 ){
			tc = coll -> chead;
		}else{
			tc = tc -> bottom ;
		}
	}
	//导航到相应的列
	struct vnode* tv = tc -> right;
	while( tv != NULL ){
		if( tv -> col == col ){
			return tv -> value;
		}else{
			tv = tv -> right;
		}
	}
	return '\n';
}

showAll( struct cnode* coll){
	
	int row = coll -> row;
	int col = coll -> col;
	int index,index2;
	for( index=0;index<row;index++){
		for( index2=0;index2<col;index2++){
			char tmp = get(coll,index+1,index2+1);
			if( tmp != '\n' ){
				printf("%c\t",tmp);
			}else{
				printf("0\t");
			}
		}
		printf("\n");
	}
}

insert( struct cnode* coll){
	printf("请输入矩阵的三元组表示，格式：行，列，值");
	int row,col;
	char value;
	scanf("%d,%d,%c",&row,&col,&value);
	bool flag = true;
	while( flag ){
		//先生成一个值节点,把相应的值附上去
		struct vnode* tvalue  =(struct vnode*)malloc(sizeof(struct vnode));
		tvalue -> row = row;
		tvalue -> col = col;
		tvalue -> value = value;
		//当行到相应的列
		int index;
		struct nnode* tr;//指向相应列的节点的指针
		for( index=0;index<col;index++){
			if( index==0 ){
				tr = coll -> rhead;
			}else{
				tr = tr -> right;
			}
		}
		//在行上面插入数据，判断 NULL 和 节点的 row 值
		struct vnode* tv;
		tv = tr -> bottom;
		bool tf = true;//设计缺陷，导致行导航无法向下导航，添加 bool 值判断待插入的是否是第一个 节点
		//bool tf2 = true;//设计缺陷，两次比较用到不同的条件
		while( tv != NULL  ){
			if( tf ){//两次执行的判断语句不一样
			
				if( tv -> row > tvalue -> row ){//已存在节点的 row 值大于 待插入节点
						tvalue ->bottom = tv;
						tr -> bottom = tvalue;//这里变换第一个节点
						//tv = tvalue;
						break;
				}
				tf = false;
			}else{//第二次判断的语句
			 if(tv -> bottom != NULL){
				 if( tv -> bottom -> row > tvalue -> row){
						tvalue -> bottom = tv -> bottom;
						tv -> bottom = tvalue;
						break;
					}else{
						tv = tv -> bottom ;
					}
			 }else{
					tv -> bottom = tvalue;
			 		break;
			 }

			}

		}
		if( tv == NULL ){//导航还是为空的情况
			tr -> bottom = tvalue;
		}
		//处理在纵向导航上的信息
		/*
		 *
		 *到183行上的注释不太准确，下面是复制上面的代码 
		 *
		 * 
		 **/
		struct nnode_c* tl;
		for( index=0;index<row;index++){
			if( index==0 ){
				tl = coll -> chead;
			}else{
				tl = tl -> bottom;
			}
		}


		//struct vnode* tv;
		tv = tl -> right;
		tf = true;//设计缺陷，导致行导航无法向下导航，添加 bool 值判断待插入的是否是第一个 节点
		//bool tf2 = true;//设计缺陷，两次比较用到不同的条件
		while( tv != NULL  ){
			if( tf ){//两次执行的判断语句不一样
			
				if( tv -> col > tvalue -> col){//已存在节点的 col 值大于 待插入节点
						tvalue -> right= tv;
						tl -> right = tvalue;//这里变换第一个节点
						//tv = tvalue;
						break;
				}
				tf = false;
			}else{//第二次判断的语句
			 if(tv -> right != NULL){
				 if( tv -> right -> col > tvalue -> col ){
						tvalue -> right = tv -> right;
						tv -> right = tvalue;
						break;
					}else{
						tv = tv -> right ;
					}
			 }else{
					tv -> right = tvalue;
			 		break;
			 }

			}

		}
		if( tv == NULL ){//导航还是为空的情况
			tl -> right = tvalue;
		}


		coll -> num ++;


		//判断用户是否需要输入下一个三元组
		char flag2 ;
		getchar();
		printf("\n是否需要输入下一组三元组，按 y 确认 按 n 否认:");
		scanf("%c",&flag2);
		if( flag2 == 'n' ){
			flag = false;	
		}else{
			printf("\n请输入矩阵的三元组表示，格式：行，列，值");
			scanf("%d,%d,%c",&row,&col,&value);
		}
	}
}

init( struct cnode* coll){
	printf("请输入行和列，格式：行数，列数");
	int row,col;
	scanf("%d,%d",&row,&col);
	//初始化行
	int index;
	struct nnode* head = NULL;
	struct nnode* end = NULL;
	for( index=0;index<row;index++){
		if( index==0 ){
			head = (struct nnode*)malloc(sizeof(struct nnode));
			head -> right = NULL;
			head -> bottom = NULL;
			end = head;
		}else{
			end -> right = (struct nnode*)malloc(sizeof(struct nnode));
			end -> right -> right = NULL;
			end -> right -> bottom  = NULL;
			end =  end -> right;
		}
	}
	coll -> rhead = head ;
	coll -> row = row;
	//初始化列
	struct nnode_c* head_c = NULL;
	struct nnode_c* end_c = NULL;
	for( index=0;index<col;index++){
		if( index==0 ){
			head_c = (struct nnode_c*)malloc(sizeof(struct nnode_c));
			head_c -> right = NULL;
			head_c -> bottom = NULL;
			end_c = head_c;
		}else{
		
			end_c -> bottom = (struct nnode_c*)malloc(sizeof(struct nnode_c));
			end_c -> bottom -> right = NULL;
			end_c -> bottom -> bottom  = NULL;
			end_c =  end_c -> bottom ;
		}
	}
	coll -> chead = head_c;
	coll -> col = col;
}
