#include <stdio.h>
main(){
	f4();
}
//输出最大和最小的值,通过传递引用来实现
f(){
	/*int a,b,*p1,*p2,*p3;
	scanf("%d,%d",&a,&b);
	p1 = &a;
	p2 = &b;
	if(a<b){
		g(p1,p2);
	}
	printf("Max=%d,Min=%d\n",*p1,*p2);
	*/
	f3();
}
void g(int* p1,int* p2){
	int p3 = *p1;
	*p1 = *p2;
	*p2 = p3;
}
//通过指针初始化数组
void f2(){
	int a[4];
	int* b = a;
	int i;
	for(i=0;i<4;i++){
		*b = i;
		b++;
	}
	for(i=0;i<4;i++){
		printf("%d\t",a[i]);
	}
	printf("\n");
}
//通过指针输出二维数组
f3(){
	int a[2][3] = {1,2,3,4,5,6};
	int* b;
	for(b=a[0];b<a[0]+6;b++){
		if((b-a[0])%3==0){
			printf("\n");
		}
		printf("%d \t",*b);
	}
	printf("\n");
}
//*(a+1)和a[1]的等价性
f4(){
	int a[][2] = {1,2,3,4};
	printf("%d",*(a+1));
	printf("\n");
	printf("%d",a[1]);
}
