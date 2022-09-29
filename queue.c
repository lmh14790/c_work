#include "queue.h"
 
void InitializeQueue(Queue *pq){
    pq->front = pq->end = NULL;
    pq->items = 0;
}

bool QueueIsFull(const Queue *pq){
   return pq->items == MAXQUEUE;
}

bool QueueIsEmpty(const Queue *pq){
    return  pq->front == NULL && pq->end == NULL;
}

size_t QueueItemCount(const Queue *pq){
    return pq->items;
}

bool EnQueue(Item item, Queue *pq){
    Node *pNew;
    if(QueueIsFull(pq)) return false;
    pNew = (Node *) malloc(sizeof(Node));
    if(pNew == NULL){
        fprintf(stderr, "内存空间不足");
        exit(1);
    }
    CopyItemToNode(item, pNew);
    pNew->next = NULL;
    if(QueueIsEmpty(pq)){
        //首次 收尾指向同一个节点指针
        pq->end = pq->front = pNew;
    } else {
        //非首次把新节点添加到上一次末尾节点的后面 在将末尾节点赋值为新节点
        pq->end->next = pNew;
        pq->end = pNew;
    }
    pq->items++;
    return true;
}
bool DeQueue(Item *pitem, Queue *pq){
    if(QueueIsEmpty(pq)) return false;
    CopyNodetoItem(pitem, pq->front);
    Node *needDelete = pq->front;
    pq->front = pq->front->next;
    free(needDelete);
    pq->items--;
    if(QueueIsEmpty(pq)){
      //最后一次 pq->front会被设置成NULL  此时pq->end 没有意义也应该设置成NULL  
      pq->end = NULL;
    }
    return true;
}

void EmptyTheQueue(Queue *pq){ 
 if(pq == NULL) return;     
 while (!QueueIsEmpty(pq)){
    Node *needDelete = pq->front;
    pq->front = pq->front->next;
    free(needDelete);
    pq->items--;
 }
 InitializeQueue(pq);
}

void CopyItemToNode(Item item, Node * pn){
  pn->item = item;
}

void CopyNodetoItem(Item *item, Node * pn){
   item->data = pn->item.data;
   item->status = pn->item.status;
}
