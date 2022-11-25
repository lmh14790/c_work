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
    tree->items++;
    if(tree->root == NULL){
        tree->root = newNode;
        return true;
    } else {
       return AddNodes(newNode, tree->root, compare);
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
};
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
};
//遍历数据并回调
void Traverse(const Tree *tree, CallBack callBack){
     if(TreeIsEmpty(tree)){
         fprintf(stderr, "当前树为空树\n");
         return;
     } else { 
      TraverseNode(tree->root, callBack);
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
   } else {
     return pair; 
   }
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
            res = true;
        } else {
          res = AddNodes(newNode, root->left, compare);        
        } 
    }  else if(compare(&(newNode->item), &(root->item)) == 1) {
        if(root->right == NULL){
            root->right = newNode;
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
            res = true;
            break;
        } else {
            previousNode = previousNode->left;
        } 
    }  else if(compare(&(newNode->item), &(previousNode->item)) == 1) {
        if(previousNode->right == NULL){
            previousNode->right = newNode;
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
    printf("被删除的数据为%d\n", ptr[0]->item.data);
    if(ptr[0] -> right == NULL){
       temp = ptr[0];
       ptr[0] = ptr[0] -> left;
    } else {
        temp = ptr[0];
        ptr[0] = ptr[0] -> right;
        Node* rightNodeMin =  ptr[0];
        while (rightNodeMin -> left && rightNodeMin)
        {
             rightNodeMin =  rightNodeMin -> left;
        }
        rightNodeMin->left = temp->left;
    }
    free(temp);
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
      if(ptr->right != NULL){
        tree->root = ptr->right;
      } else {
        tree->root = ptr->left;
      } 
    } else {
    //判断要删除的点是左节点和右节点
    if(parent -> right == ptr){  
     if(temp != NULL){
       //右侧有节点是有右侧 
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
    //找到最右测节点的最小值
    while (temp && temp->left)
    {
    temp = temp->left;
    }
    //将左侧节点赋值给最右侧节点的最小值
    if(temp != NULL) temp->left = ptr->left;
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
        free(node);
        node->left = NULL;
        node->right = NULL;
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
            free(tempArray[i]);
            tempArray[i]->left = NULL;
            tempArray[i]->right = NULL;
         }
    }
}
