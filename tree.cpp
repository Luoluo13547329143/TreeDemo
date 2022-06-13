#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include "tree.h"

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

Bnode * queryNode(Btree * root, ElemType key, Bnode *parent)
{
	//判断树是否存在
	if (!root) return nullptr;

	while ((root != NULL) && (!isEqual(root->data, key))) {
		if (isLess(key, root->data)) {
			parent = root;
			root = root->lChild;
		}
		else {
			parent = root;
			root = root->rChild;
		}
	}
	return root;
}

Bnode * findMax(Btree * root)
{
	return nullptr;
}

Btree * deleteNode(Btree * root, ElemType key, Bnode *dNode)
{
	//Bnode *node = NULL;
	Bnode *parent = NULL;//删除节点的父节点
	//先判断根节点是否存在(树是否存在)
	if (!root) return nullptr;

	//确定删除节点是否存在树中
	dNode = queryNode(root, key, parent);
	if (!dNode) {
		printf("%d不在该树中，无法删除", key);
	}
	//确定删除节点的位置
	//1如果节点是根节点， 则直接删除
	if (root->data == dNode->data) {
		return NULL;
	}
	//2如果节点是叶子节点， 则判断方位，父节点指针指向空
	if (dNode->lChild == NULL && dNode->rChild == NULL) {
		if (isLess(parent->data, dNode->data)) {
			parent->rChild == NULL;
		}
		else {
			parent->lChild == NULL;
		}
	}
	//3如果节点左右子节点任一为空， 则直接删除，父节点指向左右子节点
	if (dNode->lChild == NULL && dNode->rChild != NULL) {
		parent->rChild = dNode->rChild;
	}
	if (dNode->lChild != NULL && dNode->rChild == NULL) {
		parent->lChild == dNode->lChild;
	}
	//4如果节点左右子节点都不为空， 则用左子树中最大节点取代删除节点(直接将值调换, 再删除最大节点)

}
