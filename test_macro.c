#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define TWO 2
#define OW "随便的一个输出\
测试换行符"
#define FOUR TWO*TWO
#define SIX 2 * 3
#define PX(param) printf("参数"#param":的值为->%d.\n", param)
#define FMT "X is %d.\n"
#define SQUARE(x) ((x)*(x))
#define XNAME(n) x##n
#define PRINT_XN(n) printf("参数"#n":的值为->%d.\n", x##n)
#define PR(x, ...) printf(#x":"__VA_ARGS__)
#define ERROR -1
#define INFO 0
void testMacro();
void testDebug();
void testHook();
int main(){
    testMacro(); 
    return 0;
}
void testMacro(){
    int x = TWO;
    PX(x);
    x = FOUR;
    PX(x); 
    PX(ERROR);
    int b = SQUARE(ERROR);
    PX(b);
    //成对出现 先声明 后打印
    int XNAME(6);
    XNAME(6)  = 8;
    PRINT_XN(6);
    printf("参数" "XNAME(6)" ":的值为->%d.\n", XNAME(6));
    printf("%s\n", OW);
    printf("TWO: OW\n");
    //参数中存在# 或者##运算符时 宏不对递归展开 因为这两个符号会把宏定义本身的语言符号转换为字符符号 p449 语言和字符符号的区别
    //g++ -D DEBUG=100 这样定义宏 
    #ifdef DEBUG 
    PR(ERROR,"测试错误%d\n",1);
    PR(INFO,"测试提示%d\n",1);
    PX(DEBUG);
    testDebug();
    #endif
    double res = sqrt(1000.0);
    PR(INFO,"res的结果为:%f\n", res);
    atexit(testHook);
    exit(3); 
}

void testDebug(){
    //重置 __LINE__ 和 __FILE__
    #line 990 "aa.c"
    printf("行号%d""\n",__LINE__);
    printf("文件名为"__FILE__"\n");
    printf("行号%d""\n",__LINE__);
    printf("日期为"__DATE__"\n");
    printf("时间为"__TIME__"\n");
    printf("方法名称为%s\n",__func__);
}

void testHook(){
    PR(INFO,"exit函数被调用是触发\n");
}