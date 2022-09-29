#include<unistd.h>
#include<stdio.h>
#define arraySize(array) (sizeof(array)/sizeof(array[0]))
typedef struct 
{
   char* data;
   int key; 
} Item;
//数组中插入一条数据
void insertArray(Item *array, Item *data, int start, int end);
void sort(Item *array, int n);
void quickSort(Item *array, int n, int start);
void insertSort(Item *array, int n);
void show(Item *array, int n);
int main(int argc, char *argv[]){
    Item array[] = {{"bill",5},
    {"neil",4},
    {"john",3},
    {"rick",2},
    {"alex",1},
     {"neil",4},
    {"john",3},
    {"rick",2},
    {"alex",1},
     {"neil",4},
    {"john",3},
    {"rick",2},
    {"alex",1}
    };
    int size = arraySize(array);
    show(array, size);
    insertSort(array, size);
    printf("================================\n");
    show(array, size);
    return 0;
}
void sort(Item *array, int n){
     for (int i = 0; i < n-1; i++)
     {    
       for (int j = (i+1); j < n; j++)
        {
          if(array[j].key < array[i].key) {
           Item temp = array[j];
           array[j] = array[i];
           array[i] = temp;
          }  
        }    
     }
}

void quickSort(Item *array, int n, int start){
    if(n <= 1) return;
    int refenceIndex = start;//参考点为数组最左边的index 例如0
    //因为参考点总是在最左边 所以只有小于参考点的才需要移动到参考点的左边
    //交换refence后影响的数据范围
    for (int i = start+1; i < n; i++)
    {
      if(array[i].key < array[refenceIndex].key){
        Item temp = array[refenceIndex];
        array[refenceIndex] = array[i];
        // for (size_t j = refenceIndex + 1; j <= i; j++)
        // {  
        //   Item temp_inner = array[j];
        //   array[j] = temp;
        //   temp = temp_inner;
        // }
        insertArray(array, &temp, refenceIndex + 1, i);
        refenceIndex++;
      }
      printf("内部展示%d\n", i);
      show(array, n);
      printf("内部展示%d结束\n", i);
    }
    //小于参考点的排序
    printf("左边排序==长度=%d=index=%d=\n", refenceIndex-0, 0);
    quickSort(array, refenceIndex-0, 0);
    printf("右边排序==长度=%d=index=%d=\n",n-refenceIndex, refenceIndex+1);
    quickSort(array, n-refenceIndex, refenceIndex+1);
}
void insertSort(Item *array, int n){
      int finishIndex = 0;//已经完成排序数的最大位置
      for (int i = 1; i < n; i++)
     { 
       int realIndex = 0;//当前数要插入的位置
       for (int j = 0; j <= finishIndex; j++)
       {     
          if(array[i].key < array[j].key){
             realIndex = j;
             Item temp = array[realIndex];
             array[realIndex] = array[i];
             insertArray(array, &temp, realIndex+1, finishIndex+1);
             break;
          } else {
            realIndex++;
          }
       }
       printf("内部展示%d\n",i);
       show(array, n);
       printf("内部展示完成%d\n",i);
       finishIndex++;
     }
}
void show(Item *array, int n){
    for (int i = 0; i < n; i++)
     {    
        printf("key:%d \t data:%s\n", array[i].key, array[i].data);
     } 
}

void insertArray(Item *array, Item *data, int start, int end){
 for (size_t i = start; i <= end; i++)
        {  
          Item temp_inner = array[i];
          array[i] = *data;
          *data = temp_inner;
        }
}
