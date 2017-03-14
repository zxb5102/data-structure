#include <stdio.h>
main(){
	struct student{
		int age;
		char name[8];//c语言不支持 char[] name 的声明方式
	};

	struct student xl;
	struct student xm;

	xm.age = 10;
//	xm.name = "xiaoming"; 这样赋值不行
	scanf("%s",xm.name);
	printf("%d,%s",xm.age,xm.name);
//	printf(xm); 参数不对
	printf("\n");

}
