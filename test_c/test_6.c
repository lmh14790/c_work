#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define LETTER 26
#define A 65
#define Z 90
#define BUFFER 1024
#define arrtem(i) tem##i
#define intarrtem(i) char tem##i[i+2]
void showLetter();
void showMap();
void showPattern();
void showLetterTower();
void showTable();
void revertStr();
int main(int argc, char* argv[]){
    showMap();
    return 0;
}

void showLetter(){
    char arr[LETTER];
   for (int i = 0; i < LETTER; i++)
   {
     arr[i] = A+i;
     printf("%c\n\n", arr[i]);
   }
}

extern void showMap(){
 const int arr_size = 5;
 char** arr;
 arr = (char**)malloc(sizeof(char*)*5);
//使用数组只能在函数周期内声明 
 intarrtem(0);
 intarrtem(1);
 intarrtem(2);
 intarrtem(3);
 intarrtem(4);
  for (size_t i = 0; i < arr_size; i++)
 {  
   switch (i)
   {
   case 0:
   memset(tem0, '\0', i+2);
   memset(tem0, '$', i+1);
   arr[i] = tem0;
    break;
   case 1:
   memset(tem1, '\0', i+2);
   memset(tem1, '$', i+1);
   arr[i] = tem1;
    break;
    case 2:
   memset(tem2, '\0', i+2);
   memset(tem2, '$', i+1);
   arr[i] = tem2;
    break;
    case 3:
   memset(tem3, '\0', i+2);
   memset(tem3, '$', i+1);
   arr[i] = tem3;
    break;
   default:
   memset(tem4, '\0', i+2);
   memset(tem4, '$', i+1);
   arr[i] = tem4;
   } 
  //============错误示范  
  // static char arr1[i+2];
  // memset(arr1, '\0', i+2);
  // memset(arr1, '$', i+1);
  // printf("单次的结果为%s\n", arr1);
  // printf("单次的指针为%p\n", arr1);
  // arr[i] = arr1;
 }
//==================动态分配内存
//  for (size_t i = 0; i < arr_size; i++)
//  {
//    char* temp;
//    temp = (char*)malloc(sizeof(char)*(i+2));
//    memset(temp, '\0', i+2);
//    memset(temp, '$', i+1);
//    arr[i] = temp;
//  }
int bb[arr_size];
for (size_t i = 0; i < arr_size; i++)
 {  
    bb[i] = i; 
    printf("%s\n", arr[i]);
    printf("%p\n", arr[i]);
    //每个指针的间距为 当前指针内容个字节 由地位像高位存储
    // free(arr[i]);
 }
 free(arr);
}

void showPattern(){
 const int arr_size = 5;
 const char* tempStr="FEDCBA";
 char** arr;
 arr = (char**)malloc(sizeof(char*)*5);
 for (size_t i = 0; i < arr_size; i++)
 {
   char* temp;
   temp = (char*)malloc(sizeof(char)*(i+2));
   memset(temp, '\0', i+2);
   memcpy(temp, tempStr, i+1);
   arr[i] = temp;
 }
 for (size_t i = 0; i < arr_size; i++)
 {
    printf("%s\n", arr[i]);
    free(arr[i]);
 }
 free(arr);
} 

void showLetterTower(){
  char start;
  printf("请输入字符\n");
  scanf("%c", &start);
  if(start < A || start > (Z - 4)){
    printf("输入参数非法\n");
    return;
  }
  char p[5];
  for (size_t i = 0; i < 5; i++)
  {
    p[i] = start + i;
  }
  char line1[10];
  char line2[10];
  char line3[10];
  char line4[10];
  char line5[10];
  for (int  i = 0; i < 10; i++)
  {
    if(i != 9){
    line1[i] = ' ';
    line2[i] = ' ';
    line3[i] = ' ';
    line4[i] = ' ';
    line5[i] = ' ';
    } else {
    line1[i] = '\0';
    line2[i] = '\0';
    line3[i] = '\0';
    line4[i] = '\0';
    line5[i] = '\0';
    }
    if(i==4){
     line1[i] = p[0];
     line2[i] = p[1];
     line3[i] = p[2];
     line4[i] = p[3];
     line5[i] = p[4];
    }
    if(i==3 || i==5){
      line2[i] = p[0];
      line3[i] = p[1];
      line4[i] = p[2];
      line5[i] = p[3];
    }
    if(i==2 || i==6){
      line3[i] = p[0];
      line4[i] = p[1];
      line5[i] = p[2];
    }
    if(i==1 || i==7){
      line4[i] = p[0];
      line5[i] = p[1];
    }
    if(i==0 || i==8){
      line5[i] = p[0];
    }
  }
  printf("%s\n",line1);
  printf("%s\n",line2);
  printf("%s\n",line3);
  printf("%s\n",line4);
  printf("%s\n",line5);
}

void showTable(){
  int min, max;
  printf("请输入上限\n");
  scanf("%d", &min);
  printf("请输入下限\n");
  scanf("%d", &max);
  for(int i=min; i<=max; i++){
    printf("%d\t%d\t%d\n", i, i*i, i*i*i);
  }
}

void revertStr(){
  char input[BUFFER];
  printf("请输入字符串\n");
  scanf("%s", input);
  size_t len = strlen(input)+1;
  char revertChar[len];
  for (size_t i = 0; i < len; i++)
  {
    if(i==len-1){
     revertChar[i] = '\0';
    } else {
      revertChar[i] = input[len-i-2];
    } 
  }
  printf("%s\n", revertChar);
}

