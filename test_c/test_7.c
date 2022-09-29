#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define END '#'
#define SPACE ' '
#define LINE_FEED '\n'
void countCharNumber();
void countCharAndPrint();
int main(int argc, char *argv[]){
  countCharAndPrint();
  return 0;
}

void countCharNumber(){
  char temp;
  int spaceCount, lineFeedCount, otherCount;
  printf("请输入字符\n");
  while((temp = getchar()) != END){
    switch (temp)
    {
    case SPACE:
    spaceCount++;  
    break;
    case LINE_FEED:
    lineFeedCount++;
    break;
    default:
    otherCount++;
    }
  }
  printf("空格%d->换行%d->其他%d\n", spaceCount, lineFeedCount, otherCount);
}

void countCharAndPrint(){
  printf("请输入字符\n");
  char temp;
  int  size = 0;
  while ((temp = getchar()) != '#')
  {  
    printf("%c:%d\t",temp, temp);
    size++;
    if(size%4 == 0)  printf("\n");
  }
  
}