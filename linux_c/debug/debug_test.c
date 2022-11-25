#include <stdio.h>
#include <stdlib.h>
#define _UNWRAP(x) #x
#define UNWRAP(x) _UNWRAP(x)
int main(int argc, char *argv[])
{
    int a = 10;
    const char *str = "abc";
#if defined (DEBUG)
    printf("编译: "__DATE__" at "__TIME__"\n");
    printf("这是文件%s的第%d行\n",__FILE__,__LINE__);
#endif
    printf("hello world\n");
}
