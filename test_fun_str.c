#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 4
#define TEST_SIZE 5
void  testEOF();
void  testFileEOF();
long  fiBonacci(long);
void  testfiBonacci(void);
int   sum1(int *, int);
//函数声明和定义的时候 数组形式和指针形式是等价的都相当于指针形式
int   sum2(int [], int *);
void  testPointer(void);
void  pointerCalculate(void);
void testMultipleArray();
void testPointerAutoTransform();
void testVariableParam();
//可变长数组
void testChangeParam(int rows, int cols, int arr[rows][cols]);
//c99标准规定可以省略函数原型中的名称 但是如果省略 需要用*号代替省略维数
void testChangeParam1(int,int,int[*][*]);
void sum(int ar[], int n);
int main(){
  // //函数的声明可以在任何地方 只要在调用之前声明就行
  // int getInt();
  // getInt();
  // pointerCalculate();
  // testMultipleArray();
  testPointerAutoTransform();
  // testVariableParam();
  return 0;
}
void  testEOF(){
  char re;  
  while((re = getchar()) != EOF) putchar(re);
}

void  testFileEOF(){
    char ch;
    FILE *fp;
    char fname[128]; //用于存放文件名
    printf("输入文件的名称\n");
    scanf("%s",fname);
    printf("文件的名称%s\n", fname);
    fp = fopen(fname, "r");
    if(fp == NULL){
        printf("打开文件失败\n");
        exit(1);
    }
    while((ch = getc(fp)) != EOF){
        putchar(ch);
    }
    fclose(fp);
}

int getInt(){
  int input;
  char ch ;
  // while(scanf("%d",&input) != 1){
  // while((ch = getchar()) != '\n'){
  //     if(ch == EOF){
  //       printf("到达文件结尾\n");
  //       goto label;
  //     }
  // }
  // printf("不是一个数字，请重新输入\n");
  // }
  int res = 0;
  printf("输入一个数字\n");
  do{
   if(scanf("%d",&input) == 1) break;
   do{
    ch = getchar();
    if(ch == '\n' || ch == EOF) break;
   } while(1);
   printf("不是一个数字，请重新输入\n");
  }while(1);
  label: printf("输入的数字是%d\n",input);
  return input;
}

long fiBonacci(long  n){
  if(n>2){
  return fiBonacci(n-1)+fiBonacci(n-2);
  } else {
   return 1;
  }
}
void  testfiBonacci(void){
  printf("输入数字计算斐波那契函数值\n");
  long n = -1;
  char ch ;
  while((scanf("%ld",&n) != 1 || n < 3) && ch != EOF){
  while((ch = getchar()) != '\n' && ch != EOF){}
  }
  printf("数字为：%ld\n",n);
  long result = fiBonacci(n);  
  printf("结果为：%ld\n",result);
}

int sum1(int *arr, int n){
  int re = 0 ;
  for(int i = 0; i< n; i++){
    re += arr[i];
  }
  return re;
}
//C语言允许指针指向数组最后一个元素的后面(只针对指针即 start+SIZE合法 start[SIZE]非法 *(start+SIZE)非法)
int sum2(int start[], int *end){
   int re = 0;
   while(start < end){
    re += *(start++);
   }
   return re;
}

void  testPointer(void){
 int arr[SIZE] = {1,2,3,4};
 int re1= sum1(arr, SIZE);
 printf("sum1 re:%d\n",re1);
 int re2 = sum2(arr, arr+SIZE);
 printf("sum2 re:%d\n",re2);
}

void pointerCalculate(void){
int urn[TEST_SIZE] = {100, 200, 300, 400, 500};
int *ptr1, *ptr2, *ptr3;
ptr1 = urn;
ptr2 = &urn[1];
printf("指针的值,\t指针代表的值,\t指针的地址\n"); 
printf("ptr1 = %p,\t*ptr1 = %d,\t&ptr1 = %p\n", ptr1, *ptr1, &ptr1);
printf("ptr2 = %p,\t*ptr2 = %d,\t&ptr2 = %p\n", ptr2, *ptr2, &ptr2);
ptr3 = ptr1 +3;
printf("ptr3 = %p,\t*ptr3 = %d,\t&ptr3 = %p\n", ptr3, *ptr3, &ptr3);
printf("指针添加int值\n");
printf("ptr1 + 4 = %p, *(ptr1 + 3) = %d\n", ptr1 + 4, *(ptr1 + 3));
ptr1++;
printf("ptr1自增后的值\n");
printf("ptr1 = %p,\t*ptr1 = %d,\t&ptr1 = %p\n", ptr1, *ptr1, &ptr1);
ptr2--;
printf("ptr2自减后的值\n");
printf("ptr2 = %p,\t*ptr2 = %d,\t&ptr2 = %p\n", ptr2, *ptr2, &ptr2);
ptr1--;
ptr2++;
printf("重置后的值\n");
printf("ptr1 = %p,\t*ptr1 = %d,\t&ptr1 = %p\n", ptr1, *ptr1, &ptr1);
printf("ptr2 = %p,\t*ptr2 = %d,\t&ptr2 = %p\n", ptr2, *ptr2, &ptr2);
printf("指针之间的减法\n");//减出来的值为(数组index的差值)
printf("ptr2 = %p,\t*ptr1 = %p,\tptr2-ptr1 = %d\n", ptr2, ptr1, ptr2-ptr1);
}
//page 267 多维数组指针的代表含义
void testMultipleArray(){
  int zippo[4][2] = {{2,4},{6,8},{1,3},{5,7}};
  //多维数组的指针形式
  int (*pz)[2];
  pz = zippo;
  printf(" zippo = %p, zippo+1 = %p\n", zippo, zippo+1);
  printf(" zippo[0] = %p, zippo[0]+1 = %p\n", zippo[0], zippo[0]+1);
  printf(" *zippo = %p, *zippo+1 = %p\n", *zippo, *zippo+1);
  printf(" zippo[0][0] = %d\n", zippo[0][0]);
  printf(" *zippo[0] = %d\n", *zippo[0]);
  printf(" **zippo = %d\n", **zippo);
  printf(" **(zippo+1) = %d\n", **(zippo+1));
  printf(" *(*zippo+1) = %d\n", *(*zippo+1));
  printf(" zippo[2][1] = %d\n", zippo[2][1]);
  printf(" *(*(zippo+2)+1)= %d\n", *(*(zippo+2)+1));
  //=========
  printf(" pz = %p, pz+1 = %p\n", pz, pz+1);
  printf(" pz[0] = %p, pz[0]+1 = %p\n", pz[0], pz[0]+1);
  printf(" *pz = %p, *pz+1 = %p\n", *pz, *pz+1);
  printf(" pz[0][0] = %d\n", pz[0][0]);
  printf(" *pz[0] = %d\n", *pz[0]);
  printf(" **pz = %d\n", **pz);
  printf(" **(pz+1) = %d\n", **(pz+1));
  printf(" *(*pz+1) = %d\n", *(*pz+1));
  printf(" pz[2][1] = %d\n", pz[2][1]);
  printf(" *(*(pz+2)+1)= %d\n", *(*(pz+2)+1));
}
//typedef typedef可以这样理解：首先去掉typedef,定义的是一个变量,然后加上typedef,定义的是一个数据类型；这样看更容易理解；
// typedef int int4[4] 去掉typedef 定义一个名为int4的4个长度的int数组 加上typedef变成定义一个长度为4的int型的数组类型
// typedef int4 int3X4[3] 去掉typedef 定义一个名为int3X4的3个长度的int4类型的数组 加上typedef变成定义一个长度为3的int4类型的数组的类型
//同时int4 代表长度为4的int数组 所以int3X4代表定义一个长度为3的(长度为4的int型数组)类型的数组
typedef int int4[4];
typedef int4 int3X4[3];
// arr3X4 = int arr[3][4]
//page 270
void testPointerAutoTransform(){
  int *pt;
  int (*pa) [3];
  int ar1[2][3] = {{1,2,3},{4,5,6}};
  int ar2[3][2] = {{1,2},{3,4},{5,6}};
  int3X4 arr = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
  for(int i = 0; i< 3; i++){
    printf("第%d行==================\n",i);
    for(int j = 0; j<4; j++ ){
         printf("第%d列\t",arr[i][j]);
    }
    printf("\n");
  }
  
  int **p2;//指向指针的指针
  pt = &ar1[0][0];
  printf(" pt = &ar1[0][0] %p\n",pt);
  pt = ar1[0];
  printf(" pt = ar1[0] %p\n",pt);
  *pt = ar1[1][0];
  printf(" *pt = ar1[1][0] %d\n",*pt);
  *pt = *(*(ar1+1)+1);
  printf(" *pt = *(*(ar1+1)+1) %d\n",*pt);
  printf("*(pt+3) %d\n", *(pt+3));
  printf("pt %p\n",pt);
  //pt = ar1;//非法赋值 ar1代表指向数组int[3]的指针 pt代表指向整数的指针
  pa = ar1;
  printf(" pa = ar1 %p\n", pa);
  pa = &ar1[0];
  printf(" pa = &ar1[0] %p\n",pa);
  //*pa = ar1[0];//*pa 代表int[3] 不能被赋值;
  (*pa)[0] = 8;
  printf(" (*pa)[0] = %d\n", *pa[0]);
  (*(pa+1))[0] = 9;
  printf(" (*(pa+1))[0] = %d\n", *(pa+1)[0]);
  **pa = 7;
  printf(" **pa = %d\n", **pa);
  **(pa+1) = 10;
  printf(" **(pa+1) = %d\n", **(pa+1));
  // pa = &(&ar1[0][1]);//错误 pa代表指向数组int[3]的指针 &(&ar1[0][1])代表指向int* 的指针
  // pa = ar2;//非法赋值 ar2代表指向数组int[2]的指针 pa代表指向数组int[3]的指针
  p2 = &pt;
  printf(" p2 = &pt %p\n", p2);
  printf(" *p2 =  %p\n", *p2);
  printf(" **p2 =  %d\n", **p2);
  *p2 = ar2[0];
  printf("p2 = ar2[0] %p\n", p2);
  printf(" *p2 =  %p\n", *p2);
  printf(" pt =  %p\n", pt);
  printf("**p2 = &pt %d\n", **p2);
  //指针相加没问题
  printf("**p2+1 = &pt %d\n", *(*p2+5));
 // p2 = ar2;//非法赋值 ar2代表指向数组int[2]的指针 p2是指向int* 的指针 不是同一类型
 int *p1;
 const int *p3;
 const int ** p4;
//  p1 = p3;//非法 常量指针不能赋值给非常量指针
 p3 = p1;//合法 非常量指针赋值给常量指针是允许的 前提是只有一层的间接运算
//  p4 = &p1;//非法 非常量指针赋值给常量指针 只能是一次指针 
}

void testVariableParam(){
  int rows = 3, cols = 4;
  //变长数组不能在声明时直接初始化
  // int arrs[rows][cols] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
  int arrs[rows][cols];
  int *pt1;
  //复合文字 p276
  pt1 = (int[2]){10,20};
  //复合文字作为参数
  sum((int []) {1,2,3,4,5}, 5);
}

void sum(int ar[], int n){
  for(int i = 0; i < n; i++){
    printf("当前的值是%d\n",i);
    }
}
