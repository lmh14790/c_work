#include "avl_tree.h"
#include<unistd.h>
#include<math.h>
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
        newNode->parent = NULL;
        newNode->travel = 1;
        tree->items++;
        printf("当前的添加节点为%d\n", newNode->item.data);
        return true;
    } else {
       bool res = AddNodesLoop(newNode, tree->root, compare);
       if(res) {
        printf("当前的添加节点为%d\n", newNode->item.data);
        //平衡
        TraverseWidth(tree, NULL);
        balanceRoot(tree);
        tree->items++;
       }
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
    // DeleteNodeWithParent(pair.child, tree);
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
   DeleteAllNodesLoop(tree->root);
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
    //   TraverseNode(tree->root, callBack);
    TraverseNodeLoop(tree->root, callBack);
     }
}

Pair SeekItem(const Item *pi, const Tree *ptree, Compare compare){
    Pair look;
    look.child = ptree->root;
    look.childAddress = (Node **)&ptree->root;
    if(ptree->root == NULL){
        return look;
    }
    look.parent = ptree->root->parent;
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
    newNode->parent = NULL;
    return newNode;
}

bool AddNodes(Node *newNode, Node *root, Compare compare){
    bool res = false;
    if(compare(&(newNode->item), &(root->item)) == -1){
        if(root->left == NULL){
            root->left = newNode;
            newNode->parent = root;
            newNode->travel = root->travel+1;
            res = true;
        } else {
          res = AddNodes(newNode, root->left, compare);        
        } 
    }  else if(compare(&(newNode->item), &(root->item)) == 1) {
        if(root->right == NULL){
            root->right = newNode;
            newNode->parent = root;
            newNode->travel = root->travel+1;
            res = true;
        } else {
         res = AddNodes(newNode, root->right, compare); 
        }
    } else {
        fprintf(stderr,"不能添加权重相同的节点\n");
        res = false;
    }
    if(res){
    //添加节点的层级和平衡因子
     changeParentBanlanceFator(newNode, true);
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
            newNode->parent = previousNode;
            newNode->travel = 1;
            res = true;
            break;
        } else {
            previousNode = previousNode->left;
        } 
    }  else if(compare(&(newNode->item), &(previousNode->item)) == 1) {
        if(previousNode->right == NULL){
            previousNode->right = newNode;
            newNode->parent = previousNode;
            newNode->travel = 1;
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
    if(res){
          //添加节点的层级和平衡因子
        changeParentBanlanceFator(newNode, true);
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
     if(ptr[0] != NULL){
       ptr[0]->parent = temp->parent;
       changeParentBanlanceFator(ptr[0], false);
     }
    } else {
        temp = ptr[0];
        ptr[0] = ptr[0] -> right;
        ptr[0]->parent = temp->parent;
        Node* rightNodeMin =  ptr[0];
        while (rightNodeMin && rightNodeMin -> left && temp->left)
        {
             rightNodeMin =  rightNodeMin -> left;
        }
        rightNodeMin->left = temp->left;
        changeParentBanlanceFator(temp->right, false);
        if(temp->left != NULL) {
           temp->left->parent = rightNodeMin;
          changeParentBanlanceFator(temp->left, false);
        } 
    }
    if(temp != NULL){
    free(temp);
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = NULL;   
    }
}
 
//这种写法要删除的节点是跟节点的时候不好处理 所以不要这样写
void DeleteNodeWithParent(Node* ptr, Tree *tree){
    printf("被删除的数据为%d\n", ptr->item.data);
    if(ptr == NULL){
     fprintf(stderr,"被删除节点不能为空 \n");
     return;  
    }
    Node* temp = ptr->right;
    //要删除的节点是跟节点
    if(ptr->parent ==  NULL){
      if(temp != NULL){
        tree->root = ptr->right;
        ptr->right->parent = NULL;
      } else {
         tree->root = ptr->left;
        if(ptr->left != NULL){
           ptr->left->parent = NULL;
        } 
      } 
    } else {
    //判断要删除的点是左节点和右节点
    if(ptr->parent->right == ptr){  
     if(temp != NULL){
       //右侧有节点使用右侧节点
       ptr->parent->right = ptr->right;
       ptr->right->parent = ptr->parent;
     } else {
       //右侧没有接地啊使用左侧数据 
       ptr->parent->right = ptr->left; 
       if(ptr->left != NULL) ptr->left->parent = ptr->parent;
     }
    } else {  
     if(temp != NULL) {
       ptr->parent->left = ptr->right;
       ptr->right->parent = ptr->parent;
     } else {
       ptr->parent->left = ptr->left;
       if(ptr->left != NULL) ptr->left->parent = ptr->parent;
     } 
    }
    }
    //找到(被删除节点右侧节点的最左侧节点)最右测节点的最小值
    while (temp && temp->left && ptr->left)
    {
    temp = temp->left;
    }
    //(被删除节点存在右侧节点并且找到了右侧节点的最左侧节点) 并且 被删除节点的左节点不为空
    if(temp != NULL) {
      changeParentBanlanceFator(ptr->right, false);
      if(ptr->left != NULL){
        temp->left = ptr->left;
        ptr->left->parent = temp;
        //修改节点的层级和平衡因子
       changeParentBanlanceFator(ptr->left, false);
      }
    } else { //被删除的节点右侧为空
       if(ptr->left != NULL) changeParentBanlanceFator(ptr->left, false);
    }
    free(ptr);
    ptr->parent = NULL;
    ptr->left = NULL;
    ptr->right = NULL;
}

void TraverseNode(const Node *root, CallBack callBack){
    if(root){
       TraverseNode(root->left, callBack);
       callBack(root->item);
       TraverseNode(root->right, callBack);
    }
}

void TraverseNodeLoop(const Node *root, CallBack callBack){
    //回溯节点
     const Node* lastShow = NULL;
    if(root){
        const Node *previousNode = root;
         while (previousNode)
         {  
            if(previousNode -> left != NULL){//左子节点不为空
             if(lastShow != previousNode -> left){ //不是从左子节点回溯回来的  
                if(lastShow != NULL && lastShow == previousNode -> right){ //从右子节点回溯回来的(说明该节点及其子节点已经被遍历)
                     lastShow = previousNode;
                     previousNode = previousNode->parent;
                } else {//这是一次正常的左节点遍历
                    previousNode = previousNode->left;
                }
             } else { //说明这是一次左子节点回溯操作
                if(previousNode->right != NULL){//回溯节点的右节点不为空
                    callBack(previousNode->item);
                    lastShow = previousNode;
                    previousNode = previousNode->right;
                } else { //回溯节点的右节点为空
                    callBack(previousNode->item); 
                    lastShow = previousNode;
                    previousNode = previousNode->parent;
                } 
             }
            } else {//左子节点为空
               if(previousNode->right != NULL){ //右子节点不为空
                if(lastShow == previousNode->right){ //从右子节点回溯回来的(说明该节点及其子节点已经被遍历)
                   lastShow = previousNode;
                   previousNode = previousNode->parent;
                } else {//这是一次正常的右节点遍历
                   callBack(previousNode->item);
                   lastShow = previousNode;
                   previousNode = previousNode->right;
                }
               } else {//左右子节点都为空
                 callBack(previousNode->item);
                 lastShow = previousNode;
                 previousNode = previousNode->parent;
               } 
            }
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
        node->parent = NULL;
        free(node);
    }
}

//循环删除树节点
void DeleteAllNodesLoop(Node * node){
 //回溯节点
    Node* lastShow = NULL;
    if(node){
         Node *previousNode = node;
         while (previousNode)
         {   
            if(previousNode -> left != NULL){//左子节点不为空
             if(lastShow != previousNode -> left){ //不是从左子节点回溯回来的  
                if(lastShow != NULL && lastShow == previousNode -> right){ //从右子节点回溯回来的(说明该节点及其子节点已经被遍历)
                    Node* temp;
                     temp = previousNode;
                     lastShow = previousNode;
                     previousNode = previousNode->parent;
                     temp->parent = NULL;
                     temp->left = NULL;
                     temp->left = NULL;
                     free(temp);
                } else {//这是一次正常的左节点遍历
                    previousNode = previousNode->left;
                }
             } else { //说明这是一次左子节点回溯操作
                if(previousNode->right != NULL){//回溯节点的右节点不为空
                    lastShow = previousNode;
                    previousNode = previousNode->right;
                } else { //回溯节点的右节点为空
                    Node *temp;
                    temp = previousNode;
                    lastShow = previousNode;
                    previousNode = previousNode->parent;
                    temp->parent = NULL;
                    temp->left = NULL;
                    free(temp);
                } 
             }
            } else {//左子节点为空
               if(previousNode->right != NULL){ //右子节点不为空
                if(lastShow == previousNode->right){ //从右子节点回溯回来的(说明该节点及其子节点已经被遍历)
                   Node *temp;
                   temp = previousNode;
                   lastShow = previousNode;
                   previousNode = previousNode->parent;
                   temp->right = NULL;
                   temp->parent = NULL;
                   free(temp);
                } else {//这是一次正常的右节点遍历
                   lastShow = previousNode;
                   previousNode = previousNode->right;
                }
               } else {//左右子节点都为空
                 Node *temp; 
                 temp = previousNode;
                 lastShow = previousNode;
                 previousNode = previousNode->parent;
                 temp->parent = NULL;
                 free(temp);
               } 
            }
         }
    }
}

//树的右旋
void rightRotate(Node **parent){//被旋转节点的父节点 如果被旋转节点是跟节点则为自身
    if(parent[0] != NULL && parent[0]->left == NULL) return;
     Node *pivot = parent[0]->left;
    if(pivot->right != NULL){
       parent[0]->left = pivot->right;
       pivot->right->parent = parent[0];
       //调整pivot的travel 
       if(pivot->left != NULL){
          pivot->travel = pivot->left->travel + 1;
       } else {
          pivot->travel = 1;
       }
      //重新调整parent的travel  
      if(parent[0]->right && parent[0]->right->travel >= parent[0]->left->travel){
          parent[0]-> travel = parent[0]->right->travel + 1;
      } else {
        parent[0]-> travel = parent[0]->left->travel + 1;
      }
    } else {
      parent[0]->left = NULL;
       //重新调整parent的travel  
      if(parent[0]->right){
         parent[0]-> travel = parent[0]->right->travel + 1;
      } else {
        parent[0]-> travel = 1;
      }
    }
    printf("%d节点的值为%d\n",parent[0]->item.data ,parent[0]->travel);
    pivot->parent = parent[0]->parent;
    pivot->right = parent[0];
    //重新调整pivot的travel值
    if(pivot->left == NULL || (pivot->left && pivot->left->travel < pivot->right->travel)){
      pivot->travel = pivot->right->travel + 1;
    }
    printf("%d节点的值为%d\n",pivot->item.data ,pivot->travel);
    parent[0]->parent = pivot;
    parent[0] = pivot;
   changeParentBanlanceFator(pivot, false);
}

//树的左旋
void leftRotate(Node **parent){//被旋转节点的父节点 如果被旋转节点是跟节点则为自身
    if(parent[0] != NULL && parent[0]->right == NULL) return;
    Node *pivot = parent[0]->right;
    //pivot的右节点变为root[0]的左节点
    if(pivot->left != NULL){  
      parent[0]->right = pivot->left;
      pivot->left->parent = parent[0];
      //调整pivot的travel 
       if(pivot->right != NULL){
          pivot->travel = pivot->right->travel + 1;
       } else {
          pivot->travel = 1;
       }
        //重新调整parent的travel  
      if(parent[0]->left && parent[0]->left->travel >= parent[0]->right->travel){
          parent[0]-> travel = parent[0]->left->travel + 1;
      } else {
        parent[0]-> travel = parent[0]->right->travel + 1;
      }
    } else {
      parent[0]->right = NULL;
      if(parent[0]->left){
        parent[0]-> travel = parent[0]->left->travel + 1;
      } else {
        parent[0]-> travel = 1;
      }
    }
    printf("%d节点的值为%d\n",parent[0]->item.data ,parent[0]->travel);
    pivot->parent = parent[0]->parent;
    pivot->left = parent[0];
    if(pivot->right == NULL || (pivot->right && pivot->right->travel < pivot->left->travel)){
      pivot->travel = pivot->left->travel + 1;
    }
    printf("%d节点的值为%d\n",pivot->item.data ,pivot->travel);
    parent[0]->parent =  pivot;
    parent[0] = pivot;
    changeParentBanlanceFator(pivot, false);
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

void changeParentBanlanceFator(Node *node, bool isAdd){
    //添加节点的层级和平衡因子
       while (node && node->parent)
       { 
         int parentTravel = node->parent->travel;
         int currentTravel = node->travel;
          //子节点平衡因子小于父节点
          if((currentTravel+1) <= parentTravel){
              if(isAdd){
                 break;
              } else {
                if(node->parent->left == node){ //该节点为父节点的左子节点
                    //父节点的右子节点为空
                    if(node->parent->right == NULL){
                      node->parent->travel = currentTravel+1; 
                      node = node->parent;
                    } else {
                      if(node->parent->right->travel <=  currentTravel){
                      node->parent->travel = currentTravel+1; 
                      node = node->parent;
                      } else {
                      node->parent->travel = node->parent->right->travel+1; 
                      node = node->parent;
                      }
                    }
                } else { //该节点为父节点的右子节点
                     //父节点的左节点为空
                    if(node->parent->left == NULL){
                      node->parent->travel = currentTravel+1; 
                      node = node->parent;
                    } else {
                      if(node->parent->left->travel <=  currentTravel){
                      node->parent->travel = currentTravel+1; 
                      node = node->parent;
                      } else {
                      node->parent->travel = node->parent->left->travel+1; 
                      node = node->parent;
                      }
                   }
                }   
              }
             } else {
               node->parent->travel = currentTravel+1;
               node = node->parent;
             }
       }
}

Node* getUnBalanceFactor(Tree* tree, TYPE *type){
  if(TreeIsEmpty(tree)){
    type[0] = -1;
    return NULL;
  } else {
   int res = judgyLeftRight(tree->root);
   printf("平衡结果为%d\n", res);
   while(tree){
    
   }
   if(abs(res) <= 1){
     type[0] = -1;
     return NULL;
   } else if(res > 1){ //左边大
      Node *current = tree->root->left;
        while (current)
        {
           res = judgyLeftRight(current);
           if(res > 0) {
             current = current->left;
             *type = LL;
           } else {
            current = current->right;
             *type = LR;
           }
           if(current->travel == 1){
             current = current->parent;
             break;
           } 
        }
        return tree->root->left;
   } else { //右边大
     Node *current = tree->root->right;
     while(current){
           res = judgyLeftRight(current);
           if(res > 0) {
             current = current->left;
             *type = RL;
           } else {
            current = current->right;
             *type = RR;
           } 
        if(current->travel == 1){
           current = current->parent;
           break;       
        } 
      } 
      return tree->root->right;
   }
  }
}

int judgyLeftRight(Node *node){
  if(node->left && node->right){
    printf("节点%dres 差值为%d\n",node->item.data , node->left->travel - node->right->travel);
   return node->left->travel - node->right->travel;
  } else if(node->left && !node->right){
    printf("节点%dres左侧差值为%d\n", node->item.data ,node->left->travel);
    return node->left->travel;  
  } else if(!node->left && node->right){
    printf("节点%dres右侧差值为%d\n", node->item.data ,-node->right->travel);
    return -node->right->travel; 
  } else {
   return 0;
  }
}


//平衡树 
void balanceRoot(Tree* tree){
        TYPE type;
        Node* temp = getUnBalanceFactor(tree, &type);
        Node **parentAdderss;
        if(temp) parentAdderss = getNodeParentLocationAddress(temp, tree);
        if(temp){
        switch (type)
        {
        case LL: 
          printf("开始平衡, 平衡节点为%d, 平衡类型为%s\n", temp->item.data, "LL");  
          rightRotate(parentAdderss);
          return;
        case LR:
          printf("开始平衡, 平衡节点为%d, 平衡类型为%s\n", temp->item.data, "LR");  
          leftRotate(parentAdderss);
          parentAdderss = getNodeParentLocationAddress(temp, tree);
          rightRotate(parentAdderss);
         return;
        case RL:
          printf("开始平衡, 平衡节点为%d, 平衡类型为%s\n", temp->item.data, "RL");  
          rightRotate(parentAdderss);
          parentAdderss = getNodeParentLocationAddress(temp, tree);
          leftRotate(parentAdderss);
        return;
        default:
          printf("开始平衡, 平衡节点为%d, 平衡类型为%s\n", temp->item.data, "RR");  
          leftRotate(parentAdderss);
          return;
        }
        balanceRoot(tree);
        } 
}

Node** getNodeParentLocationAddress(Node *node, Tree* tree){
    printf("获取平衡节点的父地址%d\n", node->parent->item.data);
    Node **parentAdderss;
    Node *grandFather = node->parent->parent;
    if(grandFather == NULL){
       parentAdderss = &tree->root;
      } else {
        if(node->parent == grandFather->left){
          parentAdderss = &grandFather->left;
        } else {
           parentAdderss = &grandFather->right;
        }
    } 
    return parentAdderss;
}