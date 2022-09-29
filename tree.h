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
typedef struct pair{
Node *parent;
Node *child;
} Pair;
typedef int (*Compare)(const Item *pi1, const Item *pi2);
typedef void (*CallBack)(Item data);
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
//查找数据在书中的节点
Pair SeekItem(const Item *pi, const Tree *ptree, Compare compare);
//够造数据节点
Node * MakeNodes(const Item *pi);
//添加数据节点到树种的位置
void AddNodes(Node *newNode, Node *root, Compare compare);
//删除节点
void DeleteNode(Node **ptr);
//删除节点
void DeleteNodeWithParent(Node* ptr, Node* parent, Tree *tree);
//左右遍历树
void TraverseNode(const Node *node, CallBack callBack);
//删除树节点
static void DeleteAllNodes(Node * node);

//遍历数据并回调
void TraverseNotRecursion(const Tree *tree, CallBack callBack);
#endif