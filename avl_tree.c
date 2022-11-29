#include "avl_tree.h"
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
        newNode->parent = NULL;
        return true;
    } else {
       return AddNodesLoop(newNode, tree->root, compare);
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
    DeleteNodeWithParent(pair.child, tree);
    // DeleteNode(pair.childAddress);
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
   DeleteAllNodesLoop(tree->root);
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
            res = true;
        } else {
          res = AddNodes(newNode, root->left, compare);        
        } 
    }  else if(compare(&(newNode->item), &(root->item)) == 1) {
        if(root->right == NULL){
            root->right = newNode;
            newNode->parent = root;
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
            newNode->parent = previousNode;
            res = true;
            break;
        } else {
            previousNode = previousNode->left;
        } 
    }  else if(compare(&(newNode->item), &(previousNode->item)) == 1) {
        if(previousNode->right == NULL){
            previousNode->right = newNode;
            newNode->parent = previousNode;
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
     if(ptr[0] != NULL) ptr[0]->parent = temp->parent;
    } else {
        temp = ptr[0];
        ptr[0] = ptr[0] -> right;
        ptr[0]->parent = temp->parent;
        Node* rightNodeMin =  ptr[0];
        while (rightNodeMin -> left && rightNodeMin)
        {
             rightNodeMin =  rightNodeMin -> left;
        }
        rightNodeMin->left = temp->left;
        if(temp->left != NULL) temp->left->parent = rightNodeMin->left;
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
        if(ptr->left != NULL) ptr->left->parent = NULL;
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
    //找到最右测节点的最小值
    while (temp && temp->left)
    {
    temp = temp->left;
    }
    //将左侧节点赋值给最右侧节点的最小值
    if(temp != NULL) {
     temp->left = ptr->left;
     if(ptr->left != NULL) ptr->left->parent = temp;
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
                if(lastShow == previousNode -> right){ //从右子节点回溯回来的(说明该节点及其子节点已经被遍历)
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
static void DeleteAllNodesLoop(Node * node){
 //回溯节点
    Node* lastShow = NULL;
    if(node){
         Node *previousNode = node;
         while (previousNode)
         {   
            if(previousNode -> left != NULL){//左子节点不为空
             if(lastShow != previousNode -> left){ //不是从左子节点回溯回来的  
                if(lastShow == previousNode -> right){ //从右子节点回溯回来的(说明该节点及其子节点已经被遍历)
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