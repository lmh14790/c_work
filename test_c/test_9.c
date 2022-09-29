#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define SPACE 32
void  testMin();
double* min(double *x, double *y);
void  chline(char, int, int);
int  fibonacci(int x);
int  fibonacci2(int x);
int main(int argc, char *argv[]){
  printf("数值卫：%d\n", fibonacci(3));
  return 0;
}

void  testMin(){
 double a , b;
 printf("请输入a\n");
 scanf("%lf",&a);
 printf("请输入b\n");
 scanf("%lf",&b);
 printf("最小值为%.10f\n",min(&a, &b)[0]);
}

double* min(double *x, double *y){
  return *x < *y ? x : y;
}

void  chline(char a, int i, int j){
     for (size_t count = i; i <= j; i++)
     {  
       putchar(a);
       putchar('\t');
     } 
     putchar('\n'); 
}
int  fibonacci(int x){
  if(x == 0){
    return 0;
  }
  if(x == 1){
    return 1;
  }
  return fibonacci(x-1)+fibonacci(x-2);
}