// #include "queue.h"
#include "tree.h"
#include <time.h>
// void testQueue();
void testTree();
void showItem(Item item);
int  compareItem(const Item *item1, const Item *item2);
int main()
{   
    testTree();

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
void showItem(Item item){
    printf("当前item的值为-->%d\n",item.data);
}
int compareItem(const Item *item1, const Item *item2){
    int res = item1->data - item2->data;
    return (res == 0) ? 0 : (res < 0) ? -1 : 1;
}
void testTree(){
  Tree tree;
  char choice;
  InitializeTree(&tree);
  srand((unsigned)time(NULL));
  Item titem;
  Item tit1em;
  Item tit2em;
  for(int i= 0; i< MAXTREE && !TreeIsFull(&tree); i++){ 
  int a = rand() % 100;
  Item item = {.data = a};
  if(i == 0) titem.data = item.data;
  if(i == 3) tit1em.data = item.data;
  if(i == 7) tit2em.data = item.data;
  if(AddItem(&item, &tree, compareItem)){ 
    printf("添加数据成功-->%d\n", item.data);
   } else {
     i--;
   }
  }
//  Item item1 = {.data = 35};
//  Item item2 = {.data = 10};
//  Item item3 = {.data = 76};
//  Item item4 = {.data = 2};
//  Item item5 = {.data = 38};
//  Item item6 = {.data = 13};
//  Item item7 = {.data = 22};
//  Item item8 = {.data = 36};
//  Item item9 = {.data = 46};
//  Item item10 = {.data = 77};

//  AddItem(&item1, &tree, compareItem);
//  AddItem(&item2, &tree, compareItem);
//  AddItem(&item3, &tree, compareItem);
//  AddItem(&item4, &tree, compareItem);
//  AddItem(&item5, &tree, compareItem);
//  AddItem(&item6, &tree, compareItem);
//  AddItem(&item7, &tree, compareItem);
//  AddItem(&item8, &tree, compareItem);
//  AddItem(&item9, &tree, compareItem);
//  AddItem(&item10, &tree, compareItem);
//  Traverse(&tree, showItem);
//  TraverseWidth(&tree, showItem);
//  Item item11 = {.data = 35};
//  Pair pair = SeekItemRecursion(&tit2em, &tree.root, &tree.root, compareItem);
//  if(pair.child != NULL){
//         fprintf(stderr,"数据%d在树中\n", pair.child->item.data);  
//     } else {
//      fprintf(stderr,"数据%d不在树中\n", tit2em.data);
//     } 
//  printf("删除数据-->%d\n", item11.data);
//  DeleteItem(&item11, &tree, compareItem);
//  Traverse(&tree, showItem);
//  TraverseWidth(&tree, showItem);
//  Item item22 = {.data = 10};
//  printf("删除数据-->%d\n", item22.data);
//  DeleteItem(&item22, &tree, compareItem);
//  Traverse(&tree, showItem);
//  TraverseWidth(&tree, showItem);
//  Item item33 = {.data = 36};
//  printf("删除数据-->%d\n", item33.data);
//  DeleteItem(&item33, &tree, compareItem);
//  Traverse(&tree, showItem);
//  TraverseWidth(&tree, showItem);

//========================================
 printf("删除数据-->%d\n", titem.data);
 DeleteItem(&titem, &tree, compareItem);
 Traverse(&tree, showItem);
 TraverseWidth(&tree, showItem);
 printf("删除数据-->%d\n", tit1em.data);
 DeleteItem(&tit1em, &tree, compareItem);
 Traverse(&tree, showItem);
 TraverseWidth(&tree, showItem);
 printf("删除数据-->%d\n", tit2em.data);
 DeleteItem(&tit2em, &tree, compareItem);
 Traverse(&tree, showItem);
 TraverseWidth(&tree, showItem);
 DeleteAll(&tree);
 Traverse(&tree, showItem);
 TraverseWidth(&tree, showItem);
}
