#pragma once

#include <stdio.h>

#define isLess(a, b) (a < b)
#define isEqual(a, b) (a == b)

typedef int ElemType;

typedef struct _Tree {
	ElemType data;	//数据
	struct _Tree *lChild, *rChild;	//指向左右子节点的指针
}Bnode, Btree;

//给树插入节点 相当于初始化树
bool insertNode(Btree **root, Bnode *node);

//在树中查找节点
Bnode* queryNode(Btree *root, ElemType key);
Bnode* queryNode(Btree *root, ElemType key, Bnode **parent);

//查找子树中的最大子节点
Bnode* findMax(Btree *root, Bnode **parent);

//删除二叉树中的节点 返回该二叉树
Btree* deleteNode(Btree *root, ElemType key, Bnode * &dNode);

//遍历二叉树 仅实现前序遍历和中序遍历 且可用递归和栈分别实现
void printNode(Btree *root);

