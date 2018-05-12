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


void _SearchTreeRomove(SearchTreeNode** cur)
{
    if(cur == NULL)
    {
        return;
    }
    if(*cur == NULL)
    {
        return;
    }
    if((*cur)->lchild != NULL){
        Swap(&(*cur)->data,&(*cur)->lchild->data);
        _SearchTreeRomove(&(*cur)->lchild);
    }
    else if((*cur)->rchild != NULL){
        Swap(&(*cur)->data,&(*cur)->rchild->data);
        _SearchTreeRomove(&(*cur)->rchild);
    }else
    {
        free(*cur);
        *cur = NULL;
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
    SearchTreeNode* cur = SearchTreeFind(*root,key);
    _SearchTreeRomove(&cur);
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
    SearchTreeNodePrintChar(root,"插入五个元素");
    SearchTreeRemove(&root,'c');
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
