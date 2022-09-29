#include<stdio.h>
#include<stdlib.h>
//volatile restrict page347
//变量的作用域
extern int rand0(); //extern 可省略 意思为使用外部连接的函数
void testRand0();
void testMem();
int main(){
// testRand0();
testMem();  
return 0;
}
void testRand0(){
    int count ;
    for (count = 0; count < 5; count++)
    printf("%d\n",rand0());
}
void testMem(){
    do{
    double *ptd;
    int max;
    int number;
    int i = 0;
    int test[] = {1,2,3};
    puts("What is maximum number of type double entries?");
    scanf("%d",&max);
    // ptd = (double *)malloc(max * sizeof(double));
    //分配内存的两种方式malloc 和calloc
    ptd = (double *)calloc(max, sizeof(double));
    if(ptd == NULL){
    puts("Memory allocation failed. goodBye");
    break;
    }
    puts("enter value q to quit");
    for(;i< max && scanf("%lf", &ptd[i]) == 1;)
    i++;
    printf("here are your %d entries: \n", number = i);
    for(i = 0; i < number; i++){
        printf("%7.2f\t", ptd[i]);
        if(i%7 == 6)
        putchar('\n'); 
    }
    if(i%7 != 0) putchar('\n');
    puts("Done");
    free(ptd);
    // free(test);
    } while(0);
}