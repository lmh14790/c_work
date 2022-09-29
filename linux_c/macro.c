#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<termios.h>
#include<string.h>
#define _STR(s,a) #s#a
#define STR(s,a) _STR(s,a) //转换宏   
#define _CONS0(a,b) a##0##b
#define CONS0(a,b) _CONS0(a,b) //转换宏
#define TOW 2
#define MUL(a,b) (a*b)
#define _LEN(a) strlen(#a)
#define LEN(a) _LEN(a)
void testMacro();
int main(int argc, char *argv[]){
   testMacro();
}
//一旦遇到 #和## 宏不会被展开 例如 _STR(TOW) #TOW(因为第一层展开有#所以TOW 没展开)    STR(TOW)=> 第一次展开为 _STR(TOW) 没有#号所以发生了第二次展开 => _STR(2) => #2
void testMacro(){
  printf("显示宏定义内容========\n\n");
  printf("STR(s,a) #s\n");
  printf("CONS0(a,b) a##0##b\n");
  printf("TOW 2\n");
  printf("MUL(a,b) (a*b)\n\n");
  printf("显示 # 和 ## 的宏定义========\n\n");
  printf("STR(10,11) = %s\n", STR(10,11));
  printf("CONS0(10,1) = %d\n\n", CONS0(10,1));
  printf("显示不包含 #和##的时候 嵌套宏定义========\n\n");
  printf("TOW*TOW=MUL(TOW,TOW) = %d*%d=%d\n\n",TOW, TOW, MUL(TOW,TOW));
  printf("显示包含 #和##的时候 嵌套宏定义========\n\n");
  printf("STR(TOW,TOW) = %s\n", STR(TOW,TOW));
  //STR(TOW) => _STR()
  printf("CONS0(TOW,TOW) = %d\n", CONS0(TOW,TOW)); 
  printf("STR(\"abc\",\"def\") = %s\n", STR(abc,def));
  printf("_LEN(TOW) = %d\n", _LEN(TOW));
  printf("LEN(TOW) = %d\n", LEN(TOW));
}