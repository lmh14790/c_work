#ifndef TREE_H
#define TREE_H
#include<stdbool.h>
#include"item.h"
#include<stdlib.h>
#include<stdio.h>
#define MAXTREE 10
typedef struct node{
    Item item;
    struct node *left;
    struct node *right;
    int travel;
} Node;
typedef struct tree{
    Node *root;//树的根节点
    size_t items;//当前的数据数量
} Tree;
typedef struct LinkNode{
    Node* data;
    struct LinkNode *next;
} LinkNode;
typedef struct pair{
Node *parent;
Node *child;
Node **childAddress;
} Pair;
typedef int (*Compare)(const Item *pi1, const Item *pi2);
typedef void (*CallBack)(Item data);
typedef void (*NodeCallBack)(Node *data, int option, int count);
//初始化树
void InitializeTree(Tree *tree);
//判断树是否已满
bool TreeIsFull(const Tree *tree);
//判断树是否为空
bool TreeIsEmpty(const Tree *tree);
//当前树的数量
size_t TreeItemCount(const Tree *tree);
//插入数据
bool AddItem(const Item *item, Tree *tree, Compare compare);
//删除数据
bool DeleteItem(const Item *item, Tree *tree, Compare compare);
//数据是否在树里
bool InTree(const Item *item, const Tree *tree, Compare compare);
//清除列表数据
void DeleteAll(Tree *tree);

//遍历数据并回调
void Traverse(const Tree *tree, CallBack callBack);
//循环的方式查找数据在树中的节点 
Pair SeekItem(const Item *pi, const Tree *ptree, Compare compare);
//递归方式查找数据在树中的节点
Pair SeekItemRecursion(const Item *pi, Node **parent, Node **root, Compare compare);
//够造数据节点
Node * MakeNodes(const Item *pi);
//递归方式添加数据节点到树种的位置
bool AddNodes(Node *newNode, Node *root, Compare compare);
//循环方式添加数据节点到树种的位置
bool AddNodesLoop(Node *newNode, Node *root, Compare compare);
//删除节点
void DeleteNode(Node **ptr);
//删除节点
void DeleteNodeWithParent(Node* ptr, Node* parent, Tree *tree);
//递归左右遍历树
void TraverseNode(const Node *node, CallBack callBack);
//循环左右遍历树
void TraverseNodeLoop(const Node *node, CallBack callBack, int size);
//删除树节点
static void DeleteAllNodes(Node * node);

//循环删除树节点
static void DeleteAllNodesLoop(Node * node, int size);

//广度遍历数据并回调
void TraverseWidth(const Tree *tree, CallBack callBack);

//够造数据节点
static LinkNode * MakeLinkNodes(Node *pi);

//遍历数据并回调
void TraverseChangeNode(Node *root, int option, int count, NodeCallBack callBack);

//操作节点的traval
void option(Node *data, int option, int count);
#endif