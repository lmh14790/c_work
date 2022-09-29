#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define YEAES 5
#define MOUTH 12
//2000 到 2004年雨水量
void  printfRain();
int   *addArray(int *arr1, int arr1_size, int *arr2, int arr2_size, int *size);
void  testArray();
void  testVla();
void  vlagetArray(int row , int arr[][5]);
int main(int argc, char *argv[]){
  testVla();
  return 0;
}
void  printfRain(){
 float **rain, **temp;
 rain = (float **)malloc(sizeof(float *) * YEAES);
 temp = rain;
 for (size_t i = 0; i < YEAES; i++)
 {
   *(rain+i) = (float *)malloc(sizeof(float) * MOUTH);
   printf("%p\n",*(rain+i));
   for (size_t j = 0; j < MOUTH; j++)
   {
     *(*(rain+i)+j) = j;
     printf("%f\t",  *(*(rain+i)+j));
   }
   free(*(rain+i));
   *(rain+i) = NULL;
   printf("\n");
 }
 free(rain);//双层指针需要内外都free掉才生效
 rain = NULL;
 printf("=====>\n");
 //错误使用 使用free的代码了;
 printf("%p\n", temp[4]);
for (size_t i = 0; i < YEAES; i++)
{
   for (size_t j = 0; j < MOUTH; j++)
   {
     printf("%f\t",temp[i][j]);
   }
    printf("\n");
}
}
void testArray(){
  int arr1[] = {1 , 2, 3}, arr2[] = {4, 5, 6, 7};
  int size;
  int* arrre = addArray(arr1, 3, arr2, 4, &size);
  for (size_t i = 0; i < size; i++)
  {
    printf("%d\t", arrre[i]);
  }
   printf("\n");
   free(arrre);
   arrre = NULL;
}

int *addArray(int *arr1, int arr1_size, int *arr2, int arr2_size, int *len){
  *len = arr1_size > arr2_size ? arr1_size : arr2_size;
  int *arr = (int *)malloc(sizeof(int) * (*len));
  for (size_t i = 0; i < *len; i++)
  { 
    if(i > arr1_size - 1){
     arr[i] = 0 + arr2[i];
    } else if(i > arr2_size -1) {
     arr[i] = arr1[i] + 0;     
    } else {
      arr[i] = arr1[i] + arr2[i];
    }      
  }
  return arr;
}

void testVla(){
 printf("输入行数\n");
 int row;
 printf("读取行结果为%d, 行读取值为%d\n",scanf("%d", &row), row);
 int arr[row][5];
 for (int i = 0; i < row; i++)
 {
   printf("输入%d行的数值a,b,c,d\n",i+1);
   for (int j = 0; j < 5; j++)
   {
     printf("读取%d行%d列结果为%d,读取值为%d\n",i+1, j+1, scanf("%d", *(arr+i)+j), arr[i][j]);
     scanf("%*c");
   }
 }
 vlagetArray(row, arr);
}
void  vlagetArray(int row , int (*arr)[5]){
  int max = 0, lineTotal = 0, total = 0;
  float  totalSize = row*5, lineSize = 5;
  for (int i = 0; i < row; i++)
  { 
    for (int j = 0; j < 5; j++)
    {
      max = max > arr[i][j] ? max : arr[i][j];
      lineTotal += arr[i][j];
      total += arr[i][j];
    }
    printf("第%d行的平均值为%f\n",i+1, lineTotal/lineSize);
    lineTotal = 0;
  }
  printf("最大值为%d\n", max);
  printf("数组的平均值为%f\n", total/totalSize);
}