#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define SPACE 32
void showChar();
void countFile();
void readFilePrint();
int main(int argc, char *argv[]){
  readFilePrint();
  return 0;
}
void showChar(){
  char temp;
  while((temp = getchar()) != '#'){
    putchar(temp);
  }
}
void countFile(){
  char temp;
  int count;
  while((temp = getchar()) != EOF){
    putchar(temp);
    count++;
  }
  putchar('\n');
  printf("输入数量为%d\n", count);
}
void readFilePrint(){
  char temp;
  int count;
  while((temp = getchar()) != EOF){
    if(temp < SPACE){
      switch(temp){
        case '\n':
        printf("%d:%s\t",temp, "\\n");
        break;
        case '\t':
        printf("%d:%s\t",temp, "\\t");
        break;
        default:
        printf("%d:%s\t",temp, "ERROR");
        break;
      }
    } else {
      printf("%d:%c\t",temp, temp);
    }
    if(++count%5 == 0)printf("\n");
  }
  printf("\n");
}