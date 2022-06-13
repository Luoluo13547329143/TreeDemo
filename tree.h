#pragma once

#include <stdio.h>

#define isLess(a, b) (a < b)
#define isEqual(a, b) (a == b)

typedef int ElemType;

typedef struct _Tree {
	ElemType data;	//����
	struct _Tree *lChild, *rChild;	//ָ�������ӽڵ��ָ��
}Bnode, *Btree;


bool insertNode(Btree **root, Bnode *node);