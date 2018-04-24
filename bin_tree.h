#pragma once
#include <stdio.h>
#define TESTHEAD printf("\n==========%s=========\n",__FUNCTION__);
//函数指针
//返回值类型为 TreeNodeType
//参数类型为 结构体指针类型 TreeNode* 

typedef char TreeNodeType;

typedef struct TreeNode{
    struct TreeNode* lchild;//左孩子
    struct TreeNode* rchild;//右孩子
    TreeNodeType data;
}TreeNode;

//函数指针
//typedef TreeNodeType (*Handler)(TreeNode* node);

//初始化二叉树
void TreeNodeInit(TreeNode** root);

//先序遍历二叉树
void PreOrder(TreeNode* root);

//中序遍历
void InOrder(TreeNode* root);

//后序遍历
void PostOrder(TreeNode* root);

//层序遍历
void LevelOrder(TreeNode* root);

//构造一棵树
//
//@brief               根据先序遍历结果(带有空字符标记)
//                     构造一棵树
//@param array[]       先序遍历的结果，加上空字符标记
//@param size          数组的大小
//@param null_node     空字符标记
TreeNode* TreeCreate(TreeNodeType array[], size_t size, TreeNodeType null_node);

//销毁一棵树
TreeNode* TreeDestroy(TreeNode* root);

void Destroy(TreeNode* root);

//复制一棵树
TreeNode* TreeClone(TreeNode* root);

//求树的节点个数
size_t TreeSize(TreeNode* root);

//求树的叶节点的个数
size_t LeafTreeSize(TreeNode* root);

//求第K层节点的个数
size_t TreeLevelSize(TreeNode* root,size_t k);

//求树的高度
size_t TreeHeight(TreeNode* root);

//在树中查找指定元素
TreeNode* TreeFind(TreeNode* root, TreeNodeType to_find);

//给一个节点，找它的父节点
TreeNode* Parents(TreeNode* root,TreeNode* node);

//非递归遍历二叉树

void PreOrderByLoop(TreeNode* root);

void InOrderByLoop(TreeNode* root);

void PostOrderByLoop(TreeNode* root);

//求一个二叉树的镜像
//递归版
void TreeMirror(TreeNode* root);
//非递归版
void TreeMirrorByLoop(TreeNode* root);


//判断一个树是不是完全二叉树
//前提是进行层序遍历
int IsCompleteTree(TreeNode* root);
