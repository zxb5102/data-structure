#include <stdio.h>
main(){
	f();
}
//数组的初始化，字符串的保存，
//用指针保存字符串的首地址
f(){
	int size = 9;
	char string[] = "xiao ming";
	char* strs = "xiao ming";
  char* str = string;
	int i;
	for(i=0;i<size;i++){
		printf("%c",*(str++));
	}
	printf("\n");
	for(i=0;i<size;i++){
		printf("%c",*(strs++));
	}
	printf("\n");
}
