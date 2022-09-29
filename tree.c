#include "tree.h"
 
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
    } else {
        AddNodes(newNode, tree->root, compare);
    }
    return true;
}
//删除数据
bool DeleteItem(const Item *item, Tree *tree, Compare compare){
  if(TreeIsEmpty(tree)){
     fprintf(stderr,"tree成员为空\n");
     return false;
    }
    Pair pair = SeekItem(item, tree, compare);
    if(pair.child == NULL){
        fprintf(stderr,"当前成员不在树结构中\n");
        return false;
    }
    // if(pair.parent == NULL){
    //     DeleteNode(&tree->root);
    //     //删除左子节点
    // } else if(pair.parent->left == pair.child){
    //   //删除原始数据上的节点
    //   DeleteNode(&pair.parent->left);
    // } else {
    //     //删除右子节点  
    // DeleteNode(&pair.parent->right);  
    // }
    if(pair.parent == NULL){
        DeleteNodeWithParent(pair.child, pair.child, tree);
    } else {
        DeleteNodeWithParent(pair.child, pair.parent, tree);
    }
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
   DeleteAllNodes(tree->root);
   tree->items = 0;
   tree->root = NULL;
 }
};
//遍历数据并回调
void Traverse(const Tree *tree, CallBack callBack){
     if(TreeIsEmpty(tree)){
         fprintf(stderr, "当前树为空树\n");
         exit(1);
     } else {
      TraverseNode(tree->root, callBack);
     }
}

Pair SeekItem(const Item *pi, const Tree *ptree, Compare compare){
    Pair look;
    look.parent = NULL;
    look.child = ptree->root;
    if(look.child == NULL){
        return look;
    }
    while (look.child)
    {
      if(compare(pi, &(look.child->item)) == -1){
          look.parent = look.child;
          look.child = look.parent->left;
      } else if(compare(pi, &(look.child->item)) == 1){
          look.parent = look.child;
          look.child = look.parent->right;
      } else {
          break;
      }
    }
    return look;
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

void AddNodes(Node *newNode, Node *root, Compare compare){
    if(compare(&(newNode->item), &(root->item)) == -1){
        if(root->left == NULL){
            root->left = newNode;
        } else {
            AddNodes(newNode, root->left, compare);
        } 
    }  else if(compare(&(newNode->item), &(root->item)) == 1) {
        if(root->right == NULL){
            root->right = newNode;
        } else {
          AddNodes(newNode, root->right, compare);
        }
    } else {
            fprintf(stderr,"不能添加权重相同的节点\n");
            exit(1);
    }
}
//删除节点 为了给被删除节点赋值 所以选择传递当前节点指针的地址(用来替换指针)
void DeleteNode(Node **ptr){
    Node* temp;
    printf("被删除的数据为%d\n", (*ptr)->item.data);
    if((*ptr)->left == NULL){
        temp = *ptr;
        *ptr = (*ptr)->right;
        free(temp);
    } else if((*ptr)->right == NULL) {
        temp = *ptr;
        *ptr = (*ptr)->left;
        free(temp);
    } else {
       for(temp = (*ptr)->left; temp->right != NULL; temp = temp->right){
          continue;    
       }
       temp->right = (*ptr)->right;
       temp = *ptr;
       *ptr = (*ptr)->left;
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
    //要删除的节点是跟节点
    if(ptr == parent){
      Node* temp;
      if(ptr->left == NULL){
         tree->root = ptr->right;
         free(ptr);
      } else if(ptr->right == NULL){
        tree->root = ptr->left; 
        free(ptr);
      } else {
        Node *temp;
        //找到被删除节点第一个左节点的右侧节点(为空的地方)
        for(temp = ptr->left; temp->right != NULL; temp = temp->right){
          continue;
        }
        temp->right = ptr->right;
        tree->root = ptr->left; 
        free(ptr);
      }
    } else {
    if(ptr->left == NULL){
        //判断被删除的节点是父节点的左节点还是有节点
         if(parent->left == ptr){
            parent->left = ptr->right;
        } else {
            parent->right = ptr->right; 
        }
      free(ptr);
    } else if(ptr->right == NULL){
        if(parent->left == ptr){
            parent->left = ptr->left;
        } else {
           parent->right = ptr->left; 
        }
      free(ptr);
    } else {
        Node *temp;
        //找到被删除节点第一个左节点的右侧节点(为空的地方)
        for(temp = ptr->left; temp->right != NULL; temp = temp->right){
          continue;
        }
        temp->right = ptr->right;
        if(parent->left == ptr){
         parent->left = ptr->left;
        } else {
        parent->right = ptr->left;
        } 
        free(ptr);
    }
    }
}

void TraverseNode(const Node *root, CallBack callBack){
    if(root){
       TraverseNode(root->left, callBack);
       callBack(root->item);
       TraverseNode(root->right, callBack);
    }
}

//删除树节点
void DeleteAllNodes(Node * node){
    Node *pright;
    if(node != NULL)
    {   pright = node->right;
        DeleteAllNodes(node->left);
        free(node);
        DeleteAllNodes(node->right);
    }
}

//遍历数据并回调 使用循环遍历数据
void TraverseNotRecursion(const Tree *tree, CallBack callBack){
    if(tree->items == 0){
      fprintf(stderr, "当前树为空树\n");
      exit(1);
    } else {
        Node *temp = tree->root;
        Node* parent = NULL;  
        int count = 0;
        while (count < tree->items)
        {
        if(temp->travel)    
        //查找左子树  
        while ((temp->left) && (temp->travel != 1))
        {    
            parent = temp;
            temp = temp->left;        
        } 
        callBack(temp->item);
        count++;
        //左边找到最小了 找右边分支
        if(temp->right == NULL){
        //该节点需要展示    
        parent->travel = 1;    
        temp = parent;
        } else {
          temp = parent->right;
        }
        }
    }
}