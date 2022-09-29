#include<stdio.h>
#include<time.h>
#define SQUARD(n) n*n
#define ADD(n) n+n
//page 31
void showName1();
void showNameAddress2();
/**
 * @brief 
 * 输入年龄 展示天数
 * @param age 
 */
void showDays3(int age);

void showExample4();

void showExample5();

void showExample6();
int main(){
    showName1();
    showNameAddress2();
    showDays3(31);
    showExample4();
    showExample5();
    showExample6();
    return 0;
}
void showName1(){
   printf("Antom Bruckner\n");
   printf("Antom\nBruckner\n");
   printf("Antom ");
   printf("Bruckner\n"); 
}
void showNameAddress2(){
    printf("姓名：李明辉, 地址：建材城西二里\n");
}

void showDays3(int age){
    time_t timep;
    struct tm *p;
    time(&timep);
    p = gmtime(&timep);
    int year = 1900 + p->tm_year;
    printf("当前的年龄是" "%d" "岁\n", age);
    printf("现在是%d年\n", year);
    int sumDays = 0;
    for(int i = 1; i<= 31; i++){
        int caculatorYear = year - i;
        if((caculatorYear % 400) == 0 ){
         sumDays += 366;
          printf("%d年是------>瑞年\n",caculatorYear);
        } else if((caculatorYear % 100) != 0 && (caculatorYear % 4) == 0) {
         sumDays += 366;
           printf("%d年是------>瑞年\n",caculatorYear);
        } else {
         sumDays += 365;
            printf("%d年是平年\n",caculatorYear);
        }
    }
    printf("%d岁总共是%d天\n",age,sumDays);
}

void showExample4(){
    int count = 0;
    do
    {
    printf("For he's a jolly good fellow!\n");    
    count++;
    } while (count < 3);
    printf("Which nobody can deny!\n"); 
}

void showExample5(){
     int toes = 10;
     int squardToes = SQUARD(10);
     int addToes = ADD(10);
     printf("toes=%d,squardToes=%d,addToes=%d\n", toes, squardToes, addToes);
}

void showExample6(){
    char* arr[] = {"Smile!","Smile!","Smile!"};
    int arraySize = sizeof(arr)/sizeof(arr[0]);
    printf("array size -> %d\n", arraySize);
    int n = arraySize - 1;
    while (n >= 0)
    {
        for (int i = n; i >= 0; i--)
        {
            printf("%s", arr[i]);
        }
          printf("\n");
          n--;
    }
    
}