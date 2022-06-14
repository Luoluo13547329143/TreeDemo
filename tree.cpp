#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <stack>
#include <assert.h>
#include "tree.h"

using namespace std;

bool insertNode(Btree **root, Bnode * node)
{

	Bnode *tem = NULL;
	Bnode *parent = NULL;
	//判断传入的节点是否为空，不为空则清洗该节点指针域的指向
	if (!node) {
		return false;
	}
	else {
		node->lChild = NULL;
		node->rChild = NULL;
	}

	//插入节点分为两种情况
	//1 空树，插入的节点为根节点
	//2 已有节点，比较后插入
	if (*root) {//存在根节点
		tem = *root;
	}
	else
	{//不存在根节点
		*root = node;
		return true;
	}

	//先找到要插入的最底层父节点
	while (tem != NULL) {
		parent = tem;
		if (isLess(parent->data, node->data)) {
			tem = parent->rChild;
		}
		else {
			tem = parent->lChild;
		}
	}

	//再根据值的大小进行插入
	if (isLess(parent->data, node->data)) {
		parent->rChild = node;
	}
	else {
		parent->lChild = node;
	}

	return true;
}

Bnode * queryNode(Btree * root, ElemType key)
{
	//判断树是否存在
	if (!root) return nullptr;

	while ((root != NULL) && (!isEqual(root->data, key))) {
		if (isLess(key, root->data)) {
			root = root->lChild;
		}
		else {
			root = root->rChild;
		}
	}
	return root;
}

Bnode * queryNode(Btree * root, ElemType key, Bnode * *parent)
{
	//判断树是否存在
	if (!root) return nullptr;

	while ((root != NULL) && (!isEqual(root->data, key))) {
		if (isLess(key, root->data)) {
			*parent = root;
			root = root->lChild;
		}
		else {
			*parent = root;
			root = root->rChild;
		}
	}
	return root;
}

Bnode* findMax(Btree * root, Bnode **parent)
{
	//断言子树根节点不为空
	assert(root != NULL);
	*parent = NULL;
	while(root->rChild) {
		*parent = root;
		root = root->rChild;
	}
	return root;
}

Btree * deleteNode(Btree * root, ElemType key, Bnode *&dNode)
{
	//Bnode *node = NULL;
	Bnode *parent = NULL;//删除节点的父节点
	//先判断根节点是否存在(树是否存在)
	if (!root) return nullptr;

	//确定删除节点是否存在树中
	dNode = queryNode(root, key, &parent);
	if (!dNode) {
		printf("%d不在该树中，无法删除", key);
		return root;
	}
	//确定删除节点的位置
	//1如果节点是根节点， 则直接删除
	if (root->data == dNode->data) {
		return NULL;
	}
	//2如果节点是叶子节点， 则判断方位，父节点指针指向空
	if (dNode->lChild == NULL && dNode->rChild == NULL) {
		if (isLess(parent->data, dNode->data)) {
			parent->rChild = NULL;
		}
		else {
			parent->lChild = NULL;
		}
	}
	//3如果节点左右子节点任一为空， 则直接删除，父节点指向左右子节点
	if (dNode->lChild == NULL && dNode->rChild != NULL) {
		if (isLess(dNode->data, parent->data)) {
			parent->lChild = dNode->rChild;
		}
		else {
			parent->rChild = dNode->rChild;
		}
	}
	if (dNode->lChild != NULL && dNode->rChild == NULL) {
		if (isLess(dNode->data, parent->data)) {
			parent->lChild = dNode->lChild;
		}
		else {
			parent->rChild = dNode->lChild;
		}
	}
	//4如果节点左右子节点都不为空， 则用左子树中最大节点取代删除节点
	//注意点1 删除节点与父节点的大小比较
	//2  替代后删除节点分两种情况 要么为叶子节点 要么只有左子树
	if (dNode->lChild != NULL && dNode->rChild != NULL) {
		Bnode *tem = NULL;
		Bnode *lParent = NULL;//左子树中最大节点的父节点
		
		if (isLess(dNode->data, parent->data)) {
			tem = findMax(dNode->lChild, &lParent);
			dNode->data = tem->data;
			dNode = tem;
			//先判断左子树是否只有一个根节点
			if (lParent == NULL) {//仅有一个节点
				parent->lChild->lChild = NULL;
				return root;
			}

			//如果节点是叶子节点， 则判断方位，父节点指针指向空
			if (dNode->lChild == NULL && dNode->rChild == NULL) {
				if (isLess(lParent->data, dNode->data)) {
					lParent->rChild = NULL;
				}
				else {
					lParent->lChild = NULL;
				}
			}
			//因为找左子树最大节点 所以右节点必定为空
			if (dNode->lChild != NULL && dNode->rChild == NULL) {
				if (isLess(lParent->data, dNode->data)) {
					lParent->rChild = dNode->lChild;
				}
				else {
					lParent->lChild = dNode->lChild;
				}
			}
		}
		else {
			tem = findMax(dNode->lChild, &lParent);
			dNode->data = tem->data;
			dNode = tem;
			//先判断左子树是否只有一个根节点
			if (lParent == NULL) {//仅有一个节点
				parent->rChild->lChild = NULL;
				return root;
			}

			//如果节点是叶子节点， 则判断方位，父节点指针指向空
			if (dNode->lChild == NULL && dNode->rChild == NULL) {
				if (isLess(lParent->data, dNode->data)) {
					lParent->rChild = NULL;
				}
				else {
					lParent->lChild = NULL;
				}
			}
			//因为找左子树最大节点 所以右节点必定为空
			if (dNode->lChild != NULL && dNode->rChild == NULL) {
				if (isLess(lParent->data, dNode->data)) {
					lParent->rChild = dNode->lChild;
				}
				else {
					lParent->lChild = dNode->lChild;
				}
			}
		}
	}

	return root;
}

void printNode(Btree * root)
{
	//递归实现前序遍历
	/*if (!root) return;
	printf("-%d-", root->data);
	printNode(root->lChild);
	printNode(root->rChild);*/

	//递归实现中序遍历
	if (!root) return;
	printNode(root->lChild);
	printf("-%d-", root->data);
	printNode(root->rChild);
}
