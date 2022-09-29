#ifndef QUEUE_H
#define QUEUE_H
#include<stdbool.h>
#include"item.h"
#include<stdlib.h>
#include<stdio.h>
#define MAXQUEUE 10
typedef struct node{
    Item item;
    struct node *next;
} Node;
typedef struct queue{
    Node *front;//指向队列首的
    Node *end;//指向队列尾的
    size_t items;//当前的数据数量
} Queue;
//初始化列表
void InitializeQueue(Queue *pq);
//判断列表是否已满
bool QueueIsFull(const Queue *pq);
//判断列表是否为空
bool QueueIsEmpty(const Queue *pq);
//当前列表的数量
size_t QueueItemCount(const Queue *pq);
//插入数据
bool EnQueue(Item item, Queue *pq);
//获取首节点的数据
bool DeQueue(Item *pitem, Queue *pq);
//清除列表数据
void EmptyTheQueue(Queue *pq);
//节点复制数据
void CopyItemToNode(Item item, Node * pn); 
//复制节点数据到item
void CopyNodetoItem(Item *item, Node * pn); 
#endif