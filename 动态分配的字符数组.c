#include <stdio.h>
#include <stdlib.h>
main(){

 char* str = (char*)malloc(sizeof(char)*3);
 scanf("%c",str);
 printf("输出字符：%c\n",*str);

	printf("下面是是数组的输出\n");
	char string[] = {'a','b','c','d'};
	printf("这里输出数组的开头的一个字母 %c\n",*(string));
	//这里直接指明了输出某个字符
	printf("这里输出整个字符串 %s\n",(string));
	//这里提供字符串首地址的指针，自动输入所有的字符
}
