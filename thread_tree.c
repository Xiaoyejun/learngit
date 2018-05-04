#include "thread_tree.h"

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
ThreadTree* CreateNode(ThreadTreeType value)
{
    ThreadTree* newNode = (ThreadTree*)malloc(sizeof(ThreadTree));
    newNode->data = value;
    newNode->lchild = NULL;
    newNode->rchild = NULL;
    newNode->left = CHILD;
    newNode->right = CHILD;
    return newNode;
}
   
//@brief               根据先序遍历结果(带有空字符标记)
//                     构造一棵树
//@param array[]       先序遍历的结果，加上空字符标记
//@param size          数组的大小
//@param null_node     空字符标记
ThreadTree* _ThreadCreate(ThreadTreeType array[], size_t size, size_t* index,ThreadTreeType null_node)
{
    if(index == NULL)
    {
        return NULL;
    }
    if(*index >= size)
    {
        //树已经创建好了
        return NULL;
    }
    if(array[*index] == null_node)
    {
        return NULL;
    }
    ThreadTree* newNode = CreateNode(array[*index]);
    (*index)++;
    newNode->lchild = _ThreadCreate(array,size,index,null_node);
    (*index)++;
    newNode->rchild = _ThreadCreate(array,size,index,null_node);
    return newNode;
}


ThreadTree* ThreadTreeCreate(ThreadTreeType array[], size_t size, ThreadTreeType null_node)
{
    size_t index = 0;
    return _ThreadCreate(array,size,&index,null_node);
}


void _PreOrderThreading(ThreadTree* root, ThreadTree** prev)
{
    if(prev == NULL)
    {
        //非法输入
        return;
    }
    if(root == NULL)
    {
        return;
    }
    //如果根节点的左子树为空
    //就让它指向前驱节点
    if(root->lchild == NULL)
    {
        root->lchild = *prev;
        root->left = THREAD;
    }
    //如果前驱节点的右子树为空，就让它指向根节点
    if((*prev) != NULL && (*prev)->rchild == NULL)
    {
        (*prev)->rchild = root;
        (*prev)->right = THREAD;
    }
    (*prev) = root;
    //访问左子树
    if(root->left == CHILD){
    _PreOrderThreading(root->lchild,prev);
    }
    //访问右子树
    if(root->right == CHILD){
    _PreOrderThreading(root->rchild,prev);
    }
}
void PreOrderThreading(ThreadTree* root)
{
    if(root == NULL)
    {
        return;
    }
    ThreadTree* prev = NULL;
    _PreOrderThreading(root,&prev);
}

void PreOrderByThreading(ThreadTree* root)
{
    if(root == NULL)
    {
        return;
    }
    //访问根节点
    ThreadTree* cur = root;
    while(cur != NULL)
    {
        while(cur->left == CHILD)
        {
            printf("%c ",cur->data);
            cur=cur->lchild;
        }
        printf("%c ",cur->data);
        cur = cur->rchild;
    }
}

void _InOrderThreading(ThreadTree* root, ThreadTree** prev)
{
    if(root == NULL || prev == NULL)
    {
        return;
    }
    //处理左子树
    if(root->left == CHILD)
    {
        _InOrderThreading(root->lchild,prev);
    }
    //处理根节点
    if(root->lchild == NULL)
    {
        root->lchild = *prev;
        root->left = THREAD;
    }
    if(*prev != NULL && (*prev)->rchild == NULL)
    {
        (*prev)->rchild = root;
        (*prev)->right = THREAD;
    }
    *prev = root;
    //处理右子树
    if(root->right == CHILD)
    {
        _InOrderThreading(root->rchild,prev);
    }
    
}


void InOrderThreading(ThreadTree* root)
{
    ThreadTree* prev = NULL;
    _InOrderThreading(root,&prev);
}

void InOrderByThreading(ThreadTree* root)
{
    if(root == NULL)
    {
        return;
    }
    ThreadTree* cur = root;
    while(cur->left == CHILD && cur->lchild != NULL)
    {
        cur = cur->lchild;
    }
    while(cur->rchild != NULL)
    {
        printf("%c ",cur->data);
        cur = cur->rchild;
    }
    printf("%c ",cur->data);

}

void _PostOrderThreading(ThreadTree* root, ThreadTree** prev)
{
    if(root == NULL || prev == NULL)
    {
        return;
    }
    //处理左子树
    if(root->left == CHILD)
    {
        _InOrderThreading(root->lchild,prev);
    }
    //处理右子树
    if(root->right == CHILD)
    {
        _InOrderThreading(root->rchild,prev);
    }
    //处理根节点
    if(root->lchild == NULL)
    {
        root->lchild = *prev;
        root->left = THREAD;
    }
    if(*prev != NULL && (*prev)->rchild == NULL)
    {
        (*prev)->rchild = root;
        (*prev)->right = THREAD;
    }
    *prev = root;
}

void PostOrderThreading(ThreadTree* root)
{
    ThreadTree* prev = NULL;
    _PostOrderThreading(root,&prev);
}

///////////////////////////////////////////////////////
/////TEST
///////////////////////////////////////////////////////
void PreOrder(ThreadTree* root)
{
    if(root == NULL)
    {
        return;
    }
    printf("%c ",root->data);
    PreOrder(root->lchild);
    PreOrder(root->rchild);
}

void TestCreata()
{
    ThreadTree* root = NULL;
    ThreadTreeType array[] = "abd##e##c#f##";
    root = ThreadTreeCreate(array,strlen(array),'#');
    printf("前序遍历结果是:");
    PreOrder(root);
    printf("\n");
}
void TestPreOrderThreading()
{
    ThreadTree* root = NULL;
    ThreadTreeType array[] = "abd##e##c#f##";
    root = ThreadTreeCreate(array,strlen(array),'#');
    printf("前序遍历结果是:");
    PreOrderThreading(root);
    PreOrderByThreading(root);
    printf("\n");
}
void TestInOrderThreading()
{
    ThreadTree* root = NULL;
    ThreadTreeType array[] = "abd##e##c#f##";
    root = ThreadTreeCreate(array,strlen(array),'#');
    printf("中序遍历结果是:");
    InOrderThreading(root);
    InOrderByThreading(root);
    printf("\n");
}
int main()
{
    printf("\n");
    printf("\n");
    TestCreata();
    printf("\n");
    TestPreOrderThreading();
    printf("\n");
    TestInOrderThreading();
    return 0;
}
