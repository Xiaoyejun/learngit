#include "search_tree.h"
#include <stdio.h>
#include <stdlib.h>

//初始化二叉搜索树
void SearchTreeInit(SearchTreeNode** root)
{
    if(root == NULL)
    {
        //非法输入
        return;
    }
    *root = NULL;
}

//创建一个二叉搜索树的节点
SearchTreeNode* CreateNode(SearchTreeType value)
{
    SearchTreeNode* new_node = (SearchTreeNode*)malloc(sizeof(SearchTreeNode));
    new_node->data = value;
    new_node->lchild = NULL;
    new_node->rchild = NULL;
    return new_node;
}

//插入数据
void SearchTreeInsert(SearchTreeNode** root, SearchTreeType key) 
{
    if(root == NULL)
    {
        //非法输入
        return;
    }
    if(*root == NULL)
    {
        *root = CreateNode(key);
        return;
    }
    if((*root)->data < key)
    {
        SearchTreeInsert(&(*root)->rchild,key);
    }else if((*root)->data > key)
    {
        SearchTreeInsert(&(*root)->lchild,key);
    }else
    {
        //相等的情况就直接舍弃掉好了
        return;
    }
}

//查找指定数据
SearchTreeNode* SearchTreeFind(SearchTreeNode* root, SearchTreeType to_find) 
{
    if(root == NULL)
    {
        return NULL;
    }
    if(root->data == to_find)
    {
        return root;
    }
    else if(root->data > to_find)
    {
        return SearchTreeFind(root->lchild,to_find);
    }else
    {
        return SearchTreeFind(root->rchild,to_find);
    }
}

void Swap(SearchTreeType* a, SearchTreeType* b)
{
    SearchTreeType tmp = *a;
    *a = *b;
    *b = tmp;
}



void _SearchTreeRemove(SearchTreeNode** cur)
{
    if(cur == NULL)
    {
        return;
    }
    //1.要删除的节点是叶子节点，就直接释放，然后置空，注意要用二级指针接收
    if((*cur)->lchild == NULL && (*cur)->rchild == NULL)
    {
        free(*cur);
        *cur = NULL;
        return;
    }
    SearchTreeNode** to_delete = cur;
    //仅有左子树，就把左子树上移，因为是二级指针，所以直接解引用将其置空就好
    //仅有右子树，就把右子树上移
    if((*cur)->rchild == NULL )
    {
        to_delete = cur;
        *cur = (*cur)->lchild;
        free(*to_delete);
        return;
    }
    else if((*cur)->lchild == NULL )
    {
        to_delete = cur;
        *cur = (*cur)->lchild;
        free(*to_delete);
        return;
    }
    //3.要删除节点的左孩子和右孩子节点不是叶子节点，也就是说子树较多
    //      1.找到左子树中的最大值，
    //      2.将这个最大值与当前节点要被删除的值交换
    //      3.保证被删除的值处于一个叶子节点上
    else{
        to_delete = &(*cur)->lchild;
        while((*to_delete)->rchild != NULL)
        {
            *to_delete = (*to_delete)->rchild;
        }
        Swap(&(*cur)->data,&(*to_delete)->data);
        _SearchTreeRemove(to_delete);
    }
}
//删除指定值
void SearchTreeRemove(SearchTreeNode** root, SearchTreeType key) 
{
    if(root == NULL)
    {
        //非法输入
        return;
    }
    if(*root == NULL)
    {
        //空的二叉搜索树
        return;
    }
    else{
        if((*root)->data == key)
        {
            _SearchTreeRemove(root);
            return;
        }
        else if(key < (*root)->data && (*root)->lchild != NULL)
        {
            SearchTreeRemove(&(*root)->lchild,key);
        }else if (key > (*root)->data && (*root)->rchild != NULL)
        {
            SearchTreeRemove(&(*root)->rchild,key);
        }
    }
}

//////////////////////////////////////////////////
///////////////TEST  PART/////////////////////////
//////////////////////////////////////////////////

void Preorder(SearchTreeNode* root)
{
    if(root == NULL)
        return;
    printf("%c ",root->data);
    Preorder(root->lchild);
    Preorder(root->rchild);
}
void Inorder(SearchTreeNode* root)
{
    if(root == NULL)
        return;
    Inorder(root->lchild);
    printf("%c ",root->data);
    Inorder(root->rchild);
}

void SearchTreeNodePrintChar(SearchTreeNode* root, const char* msg)
{
    if(root == NULL || msg == NULL)
    {
        return;
    }
    printf("%s \n",msg);
    printf("\n");
    printf("前序遍历结果为: ");
    Preorder(root);
    printf("\n");
    printf("中序遍历结果为: ");
    Inorder(root);
    printf("\n");
}

void TestInit()
{
    TESTHEAD;
    SearchTreeNode* root;
    SearchTreeInit(&root);
    printf("except NULL , actural %p \n",root);
}
void TestInsert()
{
    TESTHEAD;
    SearchTreeNode* root;
    SearchTreeInit(&root);
    SearchTreeInsert(&root,'d');
    SearchTreeInsert(&root,'c');
    SearchTreeInsert(&root,'e');
    SearchTreeInsert(&root,'a');
    SearchTreeInsert(&root,'b');
    SearchTreeInsert(&root,'f');
    SearchTreeInsert(&root,'g');
    SearchTreeNodePrintChar(root,"插入七个元素");
}
void TestFind()
{
    TESTHEAD;
    SearchTreeNode* root;
    SearchTreeInit(&root);
    SearchTreeInsert(&root,'d');
    SearchTreeInsert(&root,'c');
    SearchTreeInsert(&root,'e');
    SearchTreeInsert(&root,'a');
    SearchTreeInsert(&root,'b');
    SearchTreeNodePrintChar(root,"插入五个元素");
    SearchTreeNode* cur = SearchTreeFind(root,'a');
    if(cur != NULL)
    {
        printf("except a ,actural %c \n",cur->data);
    }
}
void TestRemove()
{
    TESTHEAD;
    SearchTreeNode* root;
    SearchTreeInit(&root);
    SearchTreeInsert(&root,'d');
    SearchTreeInsert(&root,'c');
    SearchTreeInsert(&root,'e');
    SearchTreeInsert(&root,'a');
    SearchTreeInsert(&root,'b');
    SearchTreeInsert(&root,'f');
    SearchTreeInsert(&root,'g');
    SearchTreeNodePrintChar(root,"插入七个元素");
    SearchTreeRemove(&root,'g');
    SearchTreeNodePrintChar(root,"删除一个指定元素");
}

int main()
{
    TestInit();
    TestInsert();
    TestFind();
    TestRemove();
    return 0;
}
