/**
此部分为C语言的表达式和控制语句部分
包含 条件 循环 分支跳转
**/
//左值 变量名称 右值(可以赋值给可修改左值的值) 常量 变量 或者任何产生值的表达式
//表达式 6 -7 4+21 q=5+2(这个也是表达式  这个表达式的值为7 所以c语言中可以连续赋值 例如 l=m=q=5+2) q>3
#include <stdio.h>
#include <string.h>
#include <limits.h>
#define SPACE ' '
void  assignOperandTest();
void  opreandSequence();
void  sizeOfTest();
void  autoTypeChangeTest();
void getCharPutCharTest(void);
int main(){
printf("===============控制语句和表达式部分==============\n");
getCharPutCharTest();
return 0;
}
void  assignOperandTest(){
    int jane, tarzan, cheeta;
    jane = tarzan = cheeta = 25;
    //只存在右值也可以 java必须得有左值
    11;
    3+4;
    int m;
    //>从左往右运算 出现加减乘除先算加减乘除
    int q = sizeof(m)>5>3>(m=0+-11);
    printf("jane tarzan cheeta \n");
    printf("第一次得分\t %4d %8d %8d\n",jane,tarzan,cheeta);
    printf("sizeof(m):%d sizeof(m)>5>3>(m=0+-11):%d\n",sizeof m,q);
}

void  opreandSequence(){
    int top,score;
    top = score = -(2+5)*6 + (4+3*(2+3));
    printf("top = %d\n", score); 
}

//page 104 
void  sizeOfTest(){
    int n = 0;
    size_t intSize;
    intSize = sizeof(int);
    printf("n  = %d, n has %zd bytes, all ints have %zd bytes.\n", n, sizeof n, intSize);
}
//自动类型转换 向上转型
void  autoTypeChangeTest(){
    char ch;
    int i;
    float f1;
    f1 = i = ch = 'A';
    printf("ch = %c, i = %d, f1 = %2.2f\n", ch , i , f1);
    ch = ch+1;
    i = f1 + 2*ch;
    f1 = 2.0*ch +i;
    printf("ch = %c, i = %d, f1 = %2.2f\n", ch , i , f1);
    ch = 5212205;//对256取余 得到45 assi吗45为-
    printf("Now ch = %c\n",ch);

}
void getCharPutCharTest(){
    char ch;
    ch = getchar();
    while(ch != '\n'){
        if(ch == SPACE){
            putchar(ch);
        } else {
            putchar(ch+1);
        } 
        ch = getchar(); 
    }
    putchar(ch);
}