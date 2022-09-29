#include "./queue.h"
void testQueue();
int main(){
    Queue array;
    int a = 1, b = 1;

    printf("这是一个测试%d\n",);
    EmptyTheQueue(&array);
    return 0;
}

// void testQueue()
// {
//     Queue list;
//     Item temp;
//     char ch;
//     InitializeQueue(&list);
//     puts("测试queue接口输入a添加输入d删除输入q退出");
//     while ((ch = getchar()) != 'q')
//     {
//         if (ch != 'a' && ch != 'd')
//         {
//             continue;
//         }
//         if (ch == 'a')
//         {
//             puts("请输入一个整数");
//             scanf("%d", &temp.data);
//             if (!QueueIsFull(&list))
//             {
//                 if (EnQueue(temp, &list))
//                 {
//                     printf("输入%d到队列中\n", temp.data);
//                 }
//                 else
//                 {
//                     fprintf(stderr, "输入%d到队列中失败了\n", temp.data);
//                 }
//             }
//             else
//             {
//                 puts("队列已满不能添加数据请先删除数据");
//             }
//         }
//         else
//         {
//             if (!QueueIsEmpty(&list))
//             {
//                 if (DeQueue(&temp, &list))
//                 {
//                     printf("取出队列中的数据%d\n", temp.data);
//                 }
//                 else
//                 {
//                     printf("取出队列中的数据失败%d\n", temp.data);
//                 }
//             }
//             else
//             {
//                 puts("队列已空 不能取数据请先添加数据");
//             }
//         }
//     }
// }