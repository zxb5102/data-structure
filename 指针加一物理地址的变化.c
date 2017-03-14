#include <stdio.h>
main(){
	//测试 char 类型
	char* str = "xiaoming";
	printf("%d\n",sizeof(char));
	printf("%c,%d\n",*str,str);
	printf("%c,%d",*(str+1),str+1);
	

	printf("\n\n");
	//测试结构体
  struct student {
		int age ;
		char* name;
		float score;
	};
	struct student stu;
	stu.name = "xiao ming";
	printf("%s\n",stu.name);
	printf("一个结构体的大小为  %d\n",sizeof(struct student));
	printf("%c\n",*(stu.name));
	printf("%c\n",*(stu.name+1));
	printf("一个float类型的大小为 %d\n",sizeof(float));
	
	float array[] ={10.2,10.3};
	printf("%d\n",array);

	//在指针上加一根据指针类型和在机器上的存储大小，
	//物理内存地址会自动的增加相应的大小，
	printf("%d\n",array+1);
}
