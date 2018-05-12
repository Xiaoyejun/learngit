#pragma once

#define TESTHEAD printf("\n=============[%s]============\n ",__FUNCTION__);

typedef char SearchTreeType;

typedef struct SearchTreeNode{
    SearchTreeType data;
    struct SearchTreeNode* lchild;
    struct SearchTreeNode* rchild;
}SearchTreeNode;


//初始化二叉搜索树
void SearchTreeInit(SearchTreeNode** root); 

//插入数据
void SearchTreeInsert(SearchTreeNode** root, SearchTreeType key); 

//查找指定数据
SearchTreeNode* SearchTreeFind(SearchTreeNode* root, SearchTreeType to_find); 

//删除指定值
void SearchTreeRemove(SearchTreeNode** root, SearchTreeType key); 

