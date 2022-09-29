#include<stdio.h>
#include "b.h"
#include "c.h"
void function_tree(){
    printf("方法三中调用方法二\n");
    function_two();
    printf("调用方法三\n");
}