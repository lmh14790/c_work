#include "avl_tree.h"
#include <time.h>
void testTree();
void showItem(Item item);
int  compareItem(const Item *item1, const Item *item2);
int main()
{   
    testTree();
    return 0;
}
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
  Item titem = {.data = 10};
  Item tit1em = {.data = 2};
  Item tit2em = {.data = 36};
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
//  Item item1 = {.data = 10};
//  Item item2 = {.data = 32};
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
 Item item11 = {.data = 15};
 Pair pair = SeekItemRecursion(&tit2em, &tree.root, &tree.root, compareItem);
 if(pair.child != NULL){
        fprintf(stderr,"数据%d在树中\n", pair.child->item.data);  
    } else {
     fprintf(stderr,"数据%d不在树中\n", tit2em.data);
    } 
//  printf("删除数据-->%d\n", item1.data);
//  DeleteItem(&item1, &tree, compareItem);
 Traverse(&tree, showItem);
 printf("删除数据-->%d\n", titem.data);
 DeleteItem(&titem, &tree, compareItem);
 Traverse(&tree, showItem);
 printf("删除数据-->%d\n", tit1em.data);
 DeleteItem(&tit1em, &tree, compareItem);
 Traverse(&tree, showItem);
 printf("删除数据-->%d\n", tit2em.data);
 DeleteItem(&tit2em, &tree, compareItem);
 Traverse(&tree, showItem);
 DeleteAll(&tree);
 Traverse(&tree, showItem);
}
