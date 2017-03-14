#include <stdio.h>
#include <stdlib.h>
main(){

 char a,b;
 scanf("%c",&a);//这里用 %s 接受字符串也只能接受到一个字符
 scanf("%c",&b);
	printf("第一个字符 %c\n",a);
	printf("第二个字符 %c",b);
	//判断第二个字符是否是 '\n'
	if( b == '\n' ){
		printf("第二个字符为 换行  ");
	}
}
