#include<stdio.h>
static const int TIME_RANGE = 60;
#define WEEK_RANGE 7
void getAndShowTime();
void getAndShowData();
void showWeek();
void allMoney();
int main(int argc, char* argv[]){
    allMoney();
    return 0;
}

void getAndShowTime(){
     int time;
     do {
      printf("请输入数字\n\n\n");
      scanf("%d", &time);
      if(time <= 0) break;
      int min = time/TIME_RANGE;
      int second = time%TIME_RANGE;
      if(min == 0){
       printf("时间为%d秒\n", second);
      } else if (second == 0) {
        printf("时间为%d分\n", min);
      } else {
        printf("时间为%d分%d秒\n", min, second);
      }
     } while (time>0);
    printf("测试结束\n");
}

void getAndShowData(){
    int count;
    printf("请输入数字\n");
    scanf("%d", &count);
    for (int i = count; i <= count+10; i++)
    {
        printf("%d\t", i);
    }
    printf("\n");
}

void showWeek(){
    int count;
    do
    {   
    printf("请输入天数\n");
    scanf("%d", &count);
    if(count <= 0) goto error;
    int week = count/WEEK_RANGE;
    int day = count%WEEK_RANGE;
    printf("%d天是%d周%d天\n", count, week, day);
    } while (count);
    error:
    printf("参数非法\n");
} 

void allMoney(){
    int count;
    printf("请输入天数\n");
    scanf("%d", &count);
    if(count <= 0){
     printf("参数错误\n");
     return;
    }
    count=(1+count)*count/2;
    printf("赚钱%d\n",count);
}