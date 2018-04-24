#include "bin_tree.h"
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "seqstack.h"
#include "seqqueue.h"
TreeNode* CreateTreeNode(TreeNodeType value)
{
    TreeNode* newnode = (TreeNode*)malloc(sizeof(TreeNode));
    newnode->data = value;
    newnode->lchild = NULL;
    newnode->rchild = NULL;
    return newnode;
}


void TreeNodeInit(TreeNode** root)
{
    if(root == NULL)
    {
        //非法输入
        return;
    }
    *root = NULL;
}

void Destroy(TreeNode* root)
{
    free(root);
}

//函数指针
//返回值类型为 TreeNodeType
//参数类型为 结构体指针类型 TreeNode* 

//TreeNodeType Print(TreeNode* node)
//{
//    printf("%c ",node->data);
//    return node->data;
//}

//先序遍历
void PreOrder(TreeNode* root)
{
    if(root == NULL)
    {
        //遇到空节点就返回，递归出口
        return;
    }
    //访问该节点
    printf("%c ",root->data); 
    PreOrder(root->lchild);
    PreOrder(root->rchild);
}

//中序遍历
void InOrder(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    InOrder(root->lchild);
    printf("%c ",root->data);
    InOrder(root->rchild);
}

//后序遍历
void PostOrder(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    PostOrder(root->lchild);
    PostOrder(root->rchild);
    printf("%c ",root->data);
}

//层序遍历
void LevelOrder(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    //1.先把根节点插入队列
    SeqQueue seq;
    SeqQueueInit(&seq);
    SeqQueuePush(&seq,root);
    //2.循环的取队首元素
    while(1){
    SeqQueueType node;
    int ret = SeqQueueGetTop(&seq,&node);
    if(ret == 0)
    {
        return;
    }
    //3.访问队首元素并出队列
    SeqQueuePop(&seq);
    if(node != NULL)
    {
    printf("%c ",node->data);
    //4.将队首元素的左子树节点和右子树节点都依次入队列
    SeqQueuePush(&seq,node->lchild);
    //5.进入下一次循环，直到队列为空，说明遍历完了
    SeqQueuePush(&seq,node->rchild);
    }
    }
}

//@brief               根据先序遍历结果(带有空字符标记)
//                     构造一棵树
//@param array[]       先序遍历的结果，加上空字符标记
//@param size          数组的大小
//@param null_node     空字符标记
TreeNode* _TreeCreate(TreeNodeType array[],size_t size,TreeNodeType null_node,size_t* index)
{
    if(index == NULL)
    {
        //非法输入
        return NULL;
    }
    if(*index >= size)
    {
        //树已经构建完了,index已经到了数组的末尾
        return NULL;
    }
    if(array[*index] == null_node)
    {
        //前序遍历结果第一个就是空字符，说明是空树
        return NULL;
    }
    TreeNode* root = CreateTreeNode(array[*index]);
    (*index)++;
    root->lchild = _TreeCreate(array,size,null_node,index);
    (*index)++;
    root->rchild = _TreeCreate(array,size,null_node,index);
    return root;
}

TreeNode* TreeCreate(TreeNodeType array[], size_t size, TreeNodeType null_node)
{
    //当前读到了数组的第几个元素
    size_t index = 0;
    return _TreeCreate(array,size,null_node,&index);
}

//销毁一棵树
TreeNode* TreeDestroy(TreeNode* root)
{
    if(root == NULL)
    {
        //空树
        return NULL;
    }
    TreeDestroy(root->lchild);
    TreeDestroy(root->rchild);
    Destroy(root);
    return NULL;
}

//复制一棵树
TreeNode* TreeClone(TreeNode* root)
{
    if(root == NULL)
    {
        return NULL;
    }
    TreeNode* newnode = CreateTreeNode(root->data);
    newnode->lchild = TreeClone(root->lchild);
    newnode->rchild = TreeClone(root->rchild);
    return newnode;
}

//求树的节点个数
size_t TreeSize(TreeNode* root)
{
    if(root == NULL)
    {
        return 0;
    }
    return 1 + TreeSize(root->lchild) + TreeSize(root->rchild);
}

//求树的叶节点个数
size_t LeafTreeSize(TreeNode* root)
{
    if(root == NULL)
    {
        return 0;
    }
    if(root->lchild == NULL && root->rchild == NULL)
    {
        return 1;
    }
    return LeafTreeSize(root->lchild) + LeafTreeSize(root->rchild);

}

//求第K层节点的个数
size_t TreeLevelSize(TreeNode* root,size_t k)
{
    //我们规定树从第一层开始
    if(root == NULL || k < 1)
    {
        return 0;
    }
    if(k == 1)
    {
        return 1;
    }
    return TreeLevelSize(root->lchild,k-1) + TreeLevelSize(root->rchild,k-1);
}
//求树的高度
size_t TreeHeight(TreeNode* root)
{
    if(root == NULL)
    {
        return 0;
    }
    //比较左右两子树的深度，返回深度大的那个
    size_t lheight = TreeHeight(root->lchild);
    size_t rheight = TreeHeight(root->rchild);
    //相当于是调用次数的比较
    return lheight >= rheight? lheight+1:rheight+1;
    //下面的代码也可以实现相同功能，
    //但是函数会被递归调用三次，上一种方式只会被递归调用两次
    //所以效率比较低
    //return TreeHeight(root->lchild) >= TreeHeight(root->rchild)?TreeHeight(root->lchild):TreeHeight(root->rchild);
}

//在树中查找指定元素
TreeNode* TreeFind(TreeNode* root, TreeNodeType to_find)
{
    if(root == NULL)
    {
        return NULL;
    }
    if(root->data == to_find)
    {
        return root;
    }
    TreeNode* Lresult = TreeFind(root->lchild,to_find);
    TreeNode* Rresult = TreeFind(root->rchild,to_find);
    //时间复杂度为O(n),最坏的情况是所有元素都遍历了也没找到
    //空间复杂度也是O(n)
    return Lresult == NULL?Rresult:Lresult;
}

//给一个节点，找它的父节点
TreeNode* Parents(TreeNode* root,TreeNode* node)
{
    if(root == NULL)
    {
        return NULL;
    }
    if(root->lchild == node || root->rchild == node)
    {
        return root;
    }
    TreeNode* Lresult = Parents(root->lchild,node);
    TreeNode* Rresult = Parents(root->rchild,node);
    return Lresult != NULL? Lresult:Rresult;
}

//非递归遍历二叉树
void PreOrderByLoop(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    SeqStack stack;
    SeqStackInit(&stack);
    SeqStackPush(&stack,root);
    while(1)
    {
        //取栈顶元素
        SeqStackType cur;
        int ret = SeqStackFindTop(&stack,&cur);
        //如果栈空的话说明已经遍历完了
        if(ret == 0)
        {
            break;
        }
        //访问栈顶元素并且出栈
        SeqStackPop(&stack);
        printf("%c ",cur->data);
        //先把每个节点的右孩子节点入栈，
        //再把左孩子节点入栈，
        //保证每次访问完自身后，再访问左子树
        if(cur->rchild != NULL)
        {
            SeqStackPush(&stack,cur->rchild);
        }
        if(cur->lchild != NULL)
        {
            SeqStackPush(&stack,cur->lchild);
        }
    }
    printf("\n");
}

void InOrderByLoop(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    SeqStack stack;
    SeqStackInit(&stack);
    SeqStackType cur = root;
    while(1)
    {
        while(cur != NULL)
        {
            SeqStackPush(&stack,cur);
            cur = cur -> lchild;
        }
        SeqStackType top;
        int ret = SeqStackFindTop(&stack,&top);
        if(ret == 0)
        {
            break;
        }
        printf("%c ",top->data);
        SeqStackPop(&stack);
        cur = top->rchild;
    }
}

void PostOrderByLoop(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    SeqStack stack;
    SeqStackInit(&stack);
    TreeNode* cur = root;
    //保存上一个访问的元素
    TreeNode* pre = NULL;
    while(1)
    {
        //循环的将左子树入栈
        while(cur!=NULL)
        {
            SeqStackPush(&stack,cur);
            cur = cur -> lchild;
        }
        //取出栈顶元素
        SeqStackType top;
        int ret = SeqStackFindTop(&stack,&top);
        if(ret == 0)
        {
            return;
        }
        //在访问前要判断
        //   1.它的右子树是否为空
        //   2.或者判断它的右子树是否刚被访问过
        //满足任意一个条件就可以访问当前元素并将其出栈
        if(top->rchild == NULL || top->rchild == pre)
        {
            printf("%c ",top->data);
            SeqStackPop(&stack);
            pre = top;
        }
        //否则cur = cur->rchild ，跳到循环开始继续
        else{
            cur = top->rchild;
        }
    }
}

//求一个二叉树的镜像
void TreeMirror(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    TreeNode* tmp = root->lchild;
    root->lchild = root->rchild;
    root->rchild = tmp;
    TreeMirror(root->lchild);
    TreeMirror(root->rchild);
}
//非递归版
void TreeMirrorByLoop(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    SeqStack stack;
    SeqStackInit(&stack);
    SeqStackPush(&stack,root);
    while(1)
    {
        SeqStackType top;
        int ret = SeqStackFindTop(&stack,&top);
        if(ret == 0)
        {
            return;
        }
        TreeNode* tmp = top->lchild;
        top->lchild = top->rchild;
        top->rchild = tmp;
        SeqStackPop(&stack);
        if(top -> lchild != NULL)
        {
            SeqStackPush(&stack,top->lchild);
        }
        if(top -> rchild != NULL)
        {
            SeqStackPush(&stack,top->rchild);
        }
    }
}
//判断一个树是不是完全二叉树
//前提是进行层序遍历
int IsCompleteTree(TreeNode* root)
{
    if(root == NULL)
    {
        return 1;
    }
    SeqQueue seq;
    SeqQueueInit(&seq);
    SeqQueuePush(&seq,root);
    int com_l_r_null_flag = 0;
    while(1)
    {
        //进行层序遍历
        SeqQueueType top;
        SeqQueueGetTop(&seq,&top);
        if(top  == NULL)
        {
            break;
        }
        //访问队首元素
        if(com_l_r_null_flag == 0){
            if(top->lchild == NULL && top->rchild == NULL)
            {
                return 1;
            }
            else if(top->lchild == NULL && top->rchild != NULL)
            {
                return 0;
            }
      //      else if(top->lchild != NULL && top->rchild != NULL)
      //      {
      //          com_l_r_null_flag = 1;
      //      }
            else if(top->lchild != NULL && top->rchild == NULL)
            {
                com_l_r_null_flag = 1;
            }
        }else
        {
            if(top->lchild == NULL && top->rchild == NULL);
            else
            {
                return 0;
            }
        }
        SeqQueuePop(&seq);
        //取队首元素
        if(top ->lchild != NULL)
        {
            SeqQueuePush(&seq,top->lchild);
        }
        if(top ->rchild != NULL)
        {
            SeqQueuePush(&seq,top->rchild);
        }
    }
    return 1;
}
////////////////////////////////////////////////
////以下为测试代码
////////////////////////////////////////////////



void TestInit()
{
    TreeNode* root;
    TreeNodeInit(&root);
}

void TestPreOrder()
{
    TESTHEAD;
    TreeNode* a = CreateTreeNode('a');
    TreeNode* b = CreateTreeNode('b');
    TreeNode* c = CreateTreeNode('c');
    TreeNode* d = CreateTreeNode('d');
    TreeNode* e = CreateTreeNode('e');
    TreeNode* f = CreateTreeNode('f');
    a->lchild = b;
    a->rchild = c;
    b->lchild = d;
    c->lchild = e;
    c->rchild = f;
    printf("先序遍历结果:\n");
    PreOrder(a);
    printf("\n");
}

void TestInOrder()
{
    TESTHEAD;
    TreeNode* a = CreateTreeNode('a');
    TreeNode* b = CreateTreeNode('b');
    TreeNode* c = CreateTreeNode('c');
    TreeNode* d = CreateTreeNode('d');
    TreeNode* e = CreateTreeNode('e');
    TreeNode* f = CreateTreeNode('f');
    a->lchild = b;
    a->rchild = c;
    b->lchild = d;
    c->lchild = e;
    c->rchild = f;
    printf("中序遍历结果:\n");
    InOrder(a);
    printf("\n");
}

void TestPostOrder()
{
    TESTHEAD;
    TreeNode* a = CreateTreeNode('a');
    TreeNode* b = CreateTreeNode('b');
    TreeNode* c = CreateTreeNode('c');
    TreeNode* d = CreateTreeNode('d');
    TreeNode* e = CreateTreeNode('e');
    TreeNode* f = CreateTreeNode('f');
    a->lchild = b;
    a->rchild = c;
    b->lchild = d;
    c->lchild = e;
    c->rchild = f;
    printf("后序遍历结果:\n");
    PostOrder(a);
    printf("\n");
}
void TestLevelOrder()
{
    TESTHEAD;
    TreeNode* a = CreateTreeNode('a');
    TreeNode* b = CreateTreeNode('b');
    TreeNode* c = CreateTreeNode('c');
    TreeNode* d = CreateTreeNode('d');
    TreeNode* e = CreateTreeNode('e');
    TreeNode* f = CreateTreeNode('f');
    a->lchild = b;
    a->rchild = c;
    b->lchild = d;
    c->lchild = e;
    c->rchild = f;
    printf("层序遍历结果:\n");
    LevelOrder(a);
    printf("\n");
}
void TestTreeCreate()
{
    TESTHEAD;
    TreeNode* root;
    TreeNodeInit(&root);
    char array[] = "abd###ce##f##";
    root = TreeCreate(array,strlen(array),'#');
    printf("先序遍历结果:\n");
    PreOrder(root);
    printf("\n");
    printf("中序遍历结果:\n");
    InOrder(root);
    printf("\n");
    printf("后序遍历结果:\n");
    PostOrder(root);
    printf("\n");

}

void TestDestroy()
{
    TESTHEAD;
    TreeNode* root;
    TreeNodeInit(&root);
    char array[] = "abd###ce##f##";
    root = TreeCreate(array,strlen(array),'#');
    root = TreeDestroy(root);
    printf("expect: NULL,actual: %p\n",root);
    printf("\n");
}
void TestTreeCLone()
{
    TESTHEAD;
    TreeNode* root;
    TreeNodeInit(&root);
    char array[] = "abd###ce##f##";
    root = TreeCreate(array,strlen(array),'#');
    TreeNode* newroot = TreeClone(root);
    printf("root: %p ,newroot: %p \n",root,newroot);
    printf("先序遍历结果\n");
    PreOrder(newroot);
}

void TestSize()
{
    TESTHEAD;
    TreeNode* root;
    TreeNodeInit(&root);
    char array[] = "abd###ce##f##";
    root = TreeCreate(array,strlen(array),'#');
    size_t ret = TreeSize(root);
    printf("except: 6,actual: %lu \n",ret);
    printf("\n");
}
void TestLeafTreeSize()
{
    TESTHEAD;
    TreeNode* root;
    TreeNodeInit(&root);
    char array[] = "abd###ce##f##";
    root = TreeCreate(array,strlen(array),'#');
    size_t ret = LeafTreeSize(root);
    printf("except: 3,actual: %lu \n",ret);
    printf("\n");
}
void TestTreeLevelSize()
{
    TESTHEAD;
    TreeNode* root;
    TreeNodeInit(&root);
    char array[] = "abd###ce##f##";
    root = TreeCreate(array,strlen(array),'#');
    size_t ret = TreeLevelSize(root,3);
    printf("except: 3 ,actural: %lu \n",ret);
}
void TestTreeHeight()
{
    TESTHEAD;
    TreeNode* root;
    TreeNodeInit(&root);
    char array[] = "abd###ce##f##";
    root = TreeCreate(array,strlen(array),'#');
    int ret =  TreeHeight(root);
    printf("except: 3,actural: %d\n",ret);
}
void TestTreeFind()
{
    TESTHEAD;
    TreeNode* root;
    TreeNodeInit(&root);
    char array[] = "abd###ce##f##";
    root = TreeCreate(array,strlen(array),'#');
    TreeNode* find = TreeFind(root,'d');
    printf("except: d ,actual: %c \n",find->data);
}
void TestParents()
{
    TESTHEAD;
    TreeNode* root;
    TreeNodeInit(&root);
    char array[] = "abd###ce##f##";
    root = TreeCreate(array,strlen(array),'#');
    TreeNode* par = Parents(root,root->lchild->lchild);
    printf("except: %p ,actual: %p \n",root->lchild,par);
}
void TestPreOrderByLoop()
{
    TESTHEAD;
    TreeNode* root;
    TreeNodeInit(&root);
    char array[] = "abd###ce##f##";
    root = TreeCreate(array,strlen(array),'#');
    PreOrderByLoop(root);
}
void TestInOrderByLoop()
{
    TESTHEAD;
    TreeNode* root;
    TreeNodeInit(&root);
    char array[] = "abd###ce##f##";
    root = TreeCreate(array,strlen(array),'#');
    InOrderByLoop(root);
}
void TestTreeMirror()
{
    TESTHEAD;
    TreeNode* root;
    TreeNodeInit(&root);
    char array[] = "abd###ce##f##";
    root = TreeCreate(array,strlen(array),'#');
    TreeMirror(root);
    PreOrder(root);
}
void TestIsCompleteTree()
{
    TESTHEAD;
    TreeNode* root;
    TreeNodeInit(&root);
    char array[] = "abd##e##cf##g##";
    root = TreeCreate(array,strlen(array),'#');
    int ret = IsCompleteTree(root);
    PreOrder(root);
    printf("\n");
    printf("except: 1 , actull: %d \n",ret);
}
void TestPostOrderByLoop()
{
    TESTHEAD;
    TreeNode* root;
    TreeNodeInit(&root);
    char array[] = "abd###ce##f##";
    root = TreeCreate(array,strlen(array),'#');
    PostOrderByLoop(root);
}
void TestTreeMirrorByLoop()
{
    TESTHEAD;
    TreeNode* root;
    TreeNodeInit(&root);
    char array[] = "abd###ce##f##";
    root = TreeCreate(array,strlen(array),'#');
    TreeMirrorByLoop(root);
    PreOrder(root);
}
int main()
{
    TestInit();
    TestPreOrder();
    TestInOrder();
    TestPostOrder();
    TestLevelOrder();
    TestTreeCreate();
    TestDestroy();
    TestSize();
    TestLeafTreeSize();
    TestTreeCLone();
    TestTreeLevelSize();
    TestTreeHeight();
    TestTreeFind();
    TestParents();
    TestPreOrderByLoop();
    TestInOrderByLoop();
    TestPostOrderByLoop();
    TestTreeMirror();
    TestIsCompleteTree();
    TestTreeMirrorByLoop();
    printf("\n");
    printf("\n");
    printf("\n");
    return 0;
}
