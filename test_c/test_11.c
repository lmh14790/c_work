#include<stdio.h>
#include<string.h>
#include <stdbool.h>
#include<stdlib.h>
#include<ctype.h>
#define BUFFER 1024*1024
char *getArrayFromStdInput(int *);
void  testGetFun();
void  testGetLineLetter();
void  testContainChar();
const char *containChar(const char *firstChar, const char *seondChar);
bool  is_within(char temp, char *src);
void  testWithin();
char* revertString(const char * src);
void  testRevert();
void  testInput(int argc, char *argv[]);
int main(int argc, char *argv[]){
  testInput(argc, argv);
  return 0;
}

char *getArrayFromStdInput(int *size){
  printf("请输入读取字符的长度\n");
  scanf("%d", size);
  scanf("%*c");
  char *array = (char*)malloc(sizeof(char)*size[0]);
  memset(array, '\0', size[0]); 
  int totalSize = 0;
  char temp;
  printf("请输入字符\n");
  while ((temp = getchar()) != '\n' && temp != '\t' && temp != ' ')
  { 
     array[totalSize] = temp; 
     if(++totalSize == size[0]) break;
  }
  *size = totalSize;
  return array; 
}
void  testGetFun(){
  int size;
  char *res = getArrayFromStdInput(&size);
  printf("数组的长度为%d\n", size);
  for (size_t i = 0; i < size; i++)
  {
    printf("%c\n", res[i]);
  }
  free(res);
  res = NULL;
}

void  testGetLineLetter(){
 char temp[BUFFER];
 int size = 0, totalSize = 0;
 printf("请输入字符的串的长度\n");
 scanf("%d", &size);
 scanf("%*c");
 char arrar[size+1];
 memset(arrar, '\0', size+1);
 while (printf("请输入字符\n") && gets(temp) && temp[0] != '\n' && temp[0] != '\t' && temp[0]!= ' ')
 { 
   temp[1] = '\0';
   strcat(arrar, temp);
   if(++totalSize == size) break;
 }
printf("当前的字符串为%s\n", arrar);
}

const char *containChar(const char *firstChar, const char *seondChar){
  int len1 = strlen(firstChar);
  int len2 = strlen(seondChar);
  const char * result = NULL;
  if(len1 >= len2){
   int i = 0;
   startLoop: 
   while(firstChar[i] != '\0' && (len1-i) >= len2){
     int j = 0;
     while (seondChar[j] != '\0')
     {
      if(firstChar[i+j] != seondChar[j]){
       i++; 
       goto startLoop; 
      }
      j++;
     }
     if(j == len2){
      result = firstChar+i;    
      break;
     }
   } 
  }
  return result;
}

void  testContainChar(){
  char first[BUFFER], second[BUFFER];
  printf("输入原始的字符串\n");
  scanf("%s", first);
  printf("输入查找的字符串\n");
  scanf("%s", second);
  const char* res = containChar(first, second);
  if(res){
    printf("查找到结果为%s\n", res);
  }else {
    printf("不包含改字符串\n");
  }
}

bool  is_within(char temp, char *src){
  bool res = false;
  char tempC;
  while((tempC = *src++) != '\0'){
   if(tempC == temp) res = true; 
  }
  return res;
}

void  testWithin(){
  char src[BUFFER], temp;
  memset(src, '\0', BUFFER);
  printf("输入字符串\n");
  scanf("%s", src);
  getchar();
  printf("输入字符\n");
  scanf("%c", &temp);
  bool res = is_within(temp, src);
  if(res){
    printf("字符串%s包含字符%c\n",src, temp);
  } else {
     printf("字符串%s不包含字符%c\n",src, temp);
  } 
}

void  testRevert(){
 char temp[BUFFER];
 memset(temp, '\0', BUFFER);
 printf("输入字符\n");
 gets(temp);
 char *res = revertString(temp);
 printf("输入的字符串为:\n%s\n", res);
 free(res);
 res = NULL;
}

char* revertString(const char * src){
int size = strlen(src);
char *result = (char *)malloc(sizeof(char) * (size + 1));
memset(result, '\0', size + 1);
for (size_t i = 0; i < size; i++)
{
  result[i] = src[size - i - 1];
}
return result;
}

void  testInput(int argc, char *argv[]){
  char temp[BUFFER];
  memset(temp, '\0', BUFFER);
  if(argc != 2 || strlen(argv[1]) != 2 || argv[1][0] != '-' || (argv[1][1] != 'p' && argv[1][1] != 'u' && argv[1][1] != 'l')){
    printf("参数非法 请输入 -p 或者 -u 或者 -l\n");
    exit(0);
    return;
  }
  char tt;
  int  i = 0;
  while ((tt = getchar()) != EOF)
  {  
  
    switch (argv[1][1])
    {
    case 'p':
      temp[i] = tt;  
      break;
    case 'u':
    if(tt >= 'a' && tt <= 'z'){
       temp[i] = tt - 32;
    } else {
      temp[i] = tt;
    }
    break;
    default:
    if(tt >= 'A' && tt <= 'Z'){
       temp[i] = tolower(tt);
    } else {
      temp[i] = tt;
    }
      break;
    }
    i++;
  }
  printf("输出的结果为:\n%s\n",temp);
}