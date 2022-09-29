#include<stdio.h>
#include<string.h>
//定义了 整型和浮点型的一些常量
#include<limits.h>
#include<float.h>
#define SIZE 128
void getAndShowName();
void getAndShowFormatName();
int main(int argc, char* argv[]){
    getAndShowFormatName();
    return 0;
}

void getAndShowName(){
    char name[SIZE], lastName[SIZE];
    memset(name,'\0', SIZE);
    memset(lastName,'\0', SIZE);
    printf("请输入性\n");
    scanf("%s", name);
    printf("请输入名字\n");
    scanf("%s",lastName);
    printf("%s，%s\n",name,lastName);
}

void getAndShowFormatName(){
    char name[SIZE];
    memset(name,'\0', SIZE);
    printf("请输入名字\n");
    scanf("%s", name);
    int size = strlen(name) + 3;
    printf("\"%20s\"\n",name);
    printf("\"%-20s\"\n",name);
    printf("\"%-*s\"\n",size,name);
}