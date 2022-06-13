#pragma once

#include <stdio.h>

#define isLess(a, b) (a < b)
#define isEqual(a, b) (a == b)

typedef int ElemType;

typedef struct _Tree {
	ElemType data;	//数据
	struct _Tree *lChild, *rChild;	//指向左右子节点的指针
}Bnode, *Btree;


bool insertNode(Btree **root, Bnode *node);