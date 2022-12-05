#include "tree.h"
#include<unistd.h> 
//初始化树
void InitializeTree(Tree *tree){
    tree->root = NULL;
    tree->items = 0;
}
//判断树是否已满
bool TreeIsFull(const Tree *tree){
    return tree->items == MAXTREE;
}
//判断树是否为空
bool TreeIsEmpty(const Tree *tree){
 return tree == NULL ? true : tree->items == 0;
}
//当前树的数量
size_t TreeItemCount(const Tree *tree){
  return tree->items;  
}
//插入数据
bool AddItem(const Item *item, Tree *tree, Compare compare){
    if(TreeIsFull(tree)){
     fprintf(stderr,"tree成员已满不能添加\n");
     return false;
    }
    if(SeekItem(item, tree, compare).child != NULL){
        fprintf(stderr,"当前数据已存在不可重复添加\n");
        return false;
    } 
    Node *newNode = MakeNodes(item);   
    if(newNode == NULL){
    fprintf(stderr,"节点生成错误\n");
    return false;  
    }  
    if(tree->root == NULL){
        tree->root = newNode;
        newNode->travel = 1;
        tree->items++;
        return true;
    } else {
       bool res = AddNodes(newNode, tree->root, compare);
       if(res) tree->items++;
       return res;
    }
}
//删除数据
bool DeleteItem(const Item *item, Tree *tree, Compare compare){
  if(TreeIsEmpty(tree)){
     fprintf(stderr,"tree成员为空\n");
     return false;
    }
    Pair pair = SeekItemRecursion(item, &tree->root, &tree->root, compare);
    if(pair.child == NULL){
        fprintf(stderr,"当前成员不在树结构中\n");
        return false;
    } 
    // if(pair.parent == NULL){
    //     DeleteNodeWithParent(pair.child, pair.child, tree);
    // } else {
    //     DeleteNodeWithParent(pair.child, pair.parent, tree);
    // }
    DeleteNode(pair.childAddress);
    tree->items--;
    return true;
}
//数据是否在树里
bool InTree(const Item *item, const Tree *tree, Compare compare){
    return SeekItem(item, tree, compare).child != NULL;
}
//清除列表数据
void DeleteAll(Tree *tree){
 if(tree != NULL){
//    DeleteAllNodes(tree->root);
   DeleteAllNodesLoop(tree->root, tree->items);
   tree->items = 0;
   tree->root = NULL;
 }
}
//遍历数据并回调
void Traverse(const Tree *tree, CallBack callBack){
     if(TreeIsEmpty(tree)){
         fprintf(stderr, "当前树为空树\n");
         return;
     } else { 
     TraverseNodeLoop(tree->root, callBack, tree->items);
     }
}

Pair SeekItem(const Item *pi, const Tree *ptree, Compare compare){
    Pair look;
    look.parent = NULL;
    look.child = ptree->root;
    look.childAddress = (Node **)&ptree->root;
    if(look.child == NULL){
        return look;
    }
    while (look.child)
    {
      if(compare(pi, &(look.child->item)) == -1){
          look.parent = look.child;
          look.child = look.parent->left;
          look.childAddress = (Node **)&look.parent->left; 
      } else if(compare(pi, &(look.child->item)) == 1){
          look.parent = look.child;
          look.child = look.parent->right;
          look.childAddress = (Node **)&look.parent->right;
      } else {
          break;
      }
    }
    return look;
}

Pair SeekItemRecursion(const Item *pi, Node **parent, Node **root, Compare compare){
   Pair pair;
   pair.parent = parent[0];
   pair.child  = root[0]; 
   pair.childAddress = root;    
   if(root[0] == NULL){
      return pair; 
   }
   if(compare(pi, &(root[0]->item)) == -1){
     pair = SeekItemRecursion(pi, root, &root[0]->left, compare);
   } else if(compare(pi, &(root[0]->item)) == 1){
     pair = SeekItemRecursion(pi, root, &root[0]->right, compare);
   }
   return pair; 
}

Node * MakeNodes(const Item *pi){
    Node *newNode;
    newNode = (Node *)malloc(sizeof(Node));
    if(newNode == NULL){
           fprintf(stderr,"内存已满不能分配内存给Node\n");
           exit(1);  
    }
    newNode->item = *pi;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

bool AddNodes(Node *newNode, Node *root, Compare compare){
    bool res = false;
    if(compare(&(newNode->item), &(root->item)) == -1){
        if(root->left == NULL){
            root->left = newNode;
            newNode->travel = root->travel+1;
            res = true;
        } else {
          res = AddNodes(newNode, root->left, compare);        
        } 
    }  else if(compare(&(newNode->item), &(root->item)) == 1) {
        if(root->right == NULL){
            root->right = newNode;
            newNode->travel = root->travel+1;
            res = true;
        } else {
         res = AddNodes(newNode, root->right, compare); 
        }
    } else {
        fprintf(stderr,"不能添加权重相同的节点\n");
        res = false;
    }
    return res;
}

bool AddNodesLoop(Node *newNode, Node *root, Compare compare){
    Node *previousNode = root;
    bool res = false;
    while (previousNode)
    {   
      if(compare(&(newNode->item), &(previousNode->item)) == -1){
        if(previousNode->left == NULL){
            previousNode->left = newNode;
            newNode->travel = previousNode->travel+1;
            res = true;
            break;
        } else {
            previousNode = previousNode->left;
        } 
    }  else if(compare(&(newNode->item), &(previousNode->item)) == 1) {
        if(previousNode->right == NULL){
            previousNode->right = newNode;
            newNode->travel = previousNode->travel+1;
            res = true;
            break;
        } else {
          previousNode = previousNode->right;
        }
    } else {
        fprintf(stderr,"不能添加权重相同的节点\n");
        res = false;
        break;
    }
    }
    return res;
}
//删除节点 为了给被删除节点赋值 所以选择传递当前节点指针的地址(用来替换指针)
void DeleteNode(Node **ptr){
    //该节点在树里面节点本身的地址
    Node* temp;
    if(ptr[0] == NULL) return;
    printf("被删除的数据为%d\n", ptr[0]->item.data);
    if(ptr[0] -> right == NULL){
       temp = ptr[0];
       ptr[0] = ptr[0] -> left;
      TraverseChangeNode(temp->left, -1, 1, option); 
    } else {
        temp = ptr[0]; 
        ptr[0] = ptr[0] -> right;
        Node* rightNodeMin =  ptr[0];
        //找到(被删除的节点的右侧节点)的最小值
        int increaseTravel = 0;
        while (rightNodeMin && rightNodeMin -> left &&  temp->left)
        {
             rightNodeMin =  rightNodeMin -> left;
             increaseTravel++;
        }
        TraverseChangeNode(temp->right, -1, 1, option);
        if(increaseTravel > 0) TraverseChangeNode(temp->left, 1, increaseTravel, option);
        rightNodeMin->left = temp->left;
    }
    if(temp != NULL){
    temp->left = NULL;
    temp->right = NULL;    
    free(temp);
    }
}
 
//这种写法要删除的节点是跟节点的时候不好处理 所以不要这样写
void DeleteNodeWithParent(Node* ptr, Node* parent, Tree *tree){
    printf("被删除的数据为%d\n", ptr->item.data);
    if(ptr == NULL || parent == NULL){
     fprintf(stderr,"被删除节点不能为空 父节点不能为空\n");
     return;  
    }
    Node* temp = ptr;
    temp = ptr->right;
    //要删除的节点是跟节点
    if(ptr == parent){
      if(temp != NULL){
        tree->root = ptr->right;
      } else {
        tree->root = ptr->left;
      }
    } else {
    //判断要删除的点是左节点和右节点
    if(parent -> right == ptr){  
     if(temp != NULL){
       //右侧有节点使用右侧节点
       parent -> right = ptr -> right;
     } else {
       //右侧没有接地啊使用左侧数据 
       parent -> right = ptr -> left; 
     }
    } else {  
     if(temp != NULL) {
       parent -> left = ptr -> right;
     } else {
       parent -> left = ptr -> left;
     } 
    }
    }
   //找到(被删除的节点的右侧节点)的最小值
    int increaseTravel = 0;
    while (temp && temp->left && ptr->left)
    {
    temp = temp->left;
    increaseTravel++;
    }
    //(被删除的节点的右侧节点不为空)右侧节点的最小值将左侧节点赋值给最
    if(temp != NULL) {
     TraverseChangeNode(ptr->right, -1, 1, option);   
     temp->left = ptr->left;
     //右侧节点的有左子节点
     if(increaseTravel > 0) TraverseChangeNode(ptr->left, 1, increaseTravel, option);
    } else {
    //修改被删除节点的及其孩子节点的travel值
     TraverseChangeNode(ptr->left, -1, 1, option); 
    } 
    ptr->left = NULL;
    ptr->right = NULL;
    free(ptr);
}

void TraverseNode(const Node *root, CallBack callBack){
    if(root){
       TraverseNode(root->left, callBack);
       callBack(root->item);
       TraverseNode(root->right, callBack);
    }
}

void TraverseNodeLoop(const Node *root, CallBack callBack, int size){
    if(root){
         const Node *previousNode = root;
         const Node *tempArray[size];
         int tempArraySize = 0; 
         const Node *parentArray[size];
         int parentArraySize = 0;    
         while (previousNode)
         {    
            //当前节点的左子节点不为空
            if(previousNode -> left != NULL){
                int index = parentArraySize-1;
                //如果当前节点结合中包含改节点说明已经找到最小节点 此时改节点是回退节点 所以应该指向该节点的右子节点
               if(index >= 0 && previousNode -> item.data == parentArray[index] -> item.data){
                   tempArray[tempArraySize++] = previousNode;
                   parentArray[--parentArraySize] = NULL;
                   if(previousNode -> right != NULL){
                    previousNode = previousNode->right;
                   } else {
                    if(index == 0){
                     break;
                    } else previousNode =  parentArray[parentArraySize-1];
                   }
               } else {
                parentArray[parentArraySize++] = previousNode;
                previousNode = previousNode->left; 
               } 
            } else {
                //当前节点左子节点为空 右子节点不为空
               if(previousNode -> right !=  NULL){
                tempArray[tempArraySize++] = previousNode;
                previousNode = previousNode->right; 
               } else { //当前节点左右子节点都为空
               tempArray[tempArraySize++] = previousNode;
               if(parentArraySize-1 >= 0){
                  previousNode = parentArray[parentArraySize-1];
               } else break;  
               } 
            }
         }
         for(int i =  0; i < tempArraySize; i++){
            callBack(tempArray[i]->item);
         }
    }
}

//删除树节点
void DeleteAllNodes(Node * node){
    if(node != NULL)
    {
        DeleteAllNodes(node->left);   
        DeleteAllNodes(node->right);
        node->left = NULL;
        node->right = NULL;
        free(node);
    }
}

//循环删除树节点
static void DeleteAllNodesLoop(Node * node, int size){
  if(node){
         Node *previousNode = node;
         Node *tempArray[size];
         int tempArraySize = 0; 
         Node *parentArray[size];
         int parentArraySize = 0;    
         while (previousNode)
         {    
            //当前节点的左子节点不为空
            if(previousNode -> left != NULL){
                int index = parentArraySize-1;
                //如果当前节点结合中包含改节点说明已经找到最小节点 此时改节点是回退节点 所以应该指向该节点的右子节点
               if(index >= 0 && previousNode -> item.data == parentArray[index] -> item.data){
                   tempArray[tempArraySize++] = previousNode;
                   parentArray[--parentArraySize] = NULL;
                   if(previousNode -> right != NULL){
                    previousNode = previousNode->right;
                   } else {
                    if(index == 0){
                     break;
                    } else previousNode =  parentArray[parentArraySize-1];
                   }
               } else {
                parentArray[parentArraySize++] = previousNode;
                previousNode = previousNode->left; 
               } 
            } else {
                //当前节点左子节点为空 右子节点不为空
               if(previousNode -> right !=  NULL){
                tempArray[tempArraySize++] = previousNode;
                previousNode = previousNode->right; 
               } else { //当前节点左右子节点都为空
               tempArray[tempArraySize++] = previousNode;
               if(parentArraySize-1 >= 0){
                  previousNode = parentArray[parentArraySize-1];
               } else break;  
               } 
            }
         }
         for(int i =  0; i < tempArraySize; i++){
            tempArray[i]->left = NULL;
            tempArray[i]->right = NULL;
            free(tempArray[i]);
         }
    }
}

void TraverseWidth(const Tree *tree, CallBack callBack){
    if(tree->root == NULL) return;
    LinkNode *linkNode = MakeLinkNodes(tree->root);
    LinkNode *end = linkNode;
    LinkNode *root = linkNode;
    Node *current = linkNode->data;
    while(current){      
     if(current->left != NULL && current->right != NULL){
        LinkNode* right = MakeLinkNodes(current->right);
        LinkNode* Left = MakeLinkNodes(current->left);
        end->next = Left;
        end->next->next = right;
        end = right;
       linkNode = linkNode->next;
       current = linkNode->data;
     } else if(current->left != NULL){
         LinkNode* Left = MakeLinkNodes(current->left);
         end->next = Left;
         end = Left;
         linkNode = linkNode->next;
         current = linkNode->data;
     } else if(current->right != NULL){
        LinkNode* right = MakeLinkNodes(current->right);
        end->next = right;
        end = right;
        linkNode = linkNode->next;
        current = linkNode->data;
     } else {
         linkNode = linkNode->next;
        if(linkNode) {
           current = linkNode->data;
        } else {
            current = NULL; 
            break;
        }
     }
    }
    LinkNode *rootLink = root;
     int lastTravel = 0;
     printf("-----------");
     while (rootLink)
     {  
        if(lastTravel == rootLink->data->travel){
         printf("\t(%d, %d) ", rootLink->data->item.data,rootLink->data->travel);   
        } else {
          printf("\n(%d, %d) ", rootLink->data->item.data,rootLink->data->travel);  
        }
         lastTravel = rootLink->data->travel;
         rootLink = rootLink->next;
         
     }
     printf("\n-----------\n");   
    while (root)
    {
       LinkNode* tem = root;
       root = root->next;
       tem->next = NULL;
       tem->data = NULL;
       free(tem); 
    } 
}

static LinkNode * MakeLinkNodes(Node *pi){
    LinkNode *newNode;
    newNode = (LinkNode *)malloc(sizeof(LinkNode *));
    if(newNode == NULL){
           fprintf(stderr,"内存已满不能分配内存给LinkNode\n");
           exit(1);  
    }
    newNode->data = pi;
    newNode->next = NULL;
    return newNode;
}

//遍历数据并回调
void TraverseChangeNode(Node *root, int option, int count, NodeCallBack callBack){
if(root){
       TraverseChangeNode(root->left, option, count, callBack);
       callBack(root, option, count);
       TraverseChangeNode(root->right, option, count, callBack);
    }
}

//操作节点的traval
void option(Node *data, int option, int count){
     if(option >= 0){
        data->travel += count;
     } else {
        data->travel -= count;
     }
}
