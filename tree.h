#pragma once

#include <stdio.h>

#define isLess(a, b) (a < b)
#define isEqual(a, b) (a == b)

typedef int ElemType;

typedef struct _Tree {
	ElemType data;	//����
	struct _Tree *lChild, *rChild;	//ָ�������ӽڵ��ָ��
}Bnode, Btree;

//��������ڵ� �൱�ڳ�ʼ����
bool insertNode(Btree **root, Bnode *node);

//�����в��ҽڵ�
Bnode* queryNode(Btree *root, ElemType key);
Bnode* queryNode(Btree *root, ElemType key, Bnode **parent);

//���������е�����ӽڵ�
Bnode* findMax(Btree *root, Bnode **parent);

//ɾ���������еĽڵ� ���ظö�����
Btree* deleteNode(Btree *root, ElemType key, Bnode * &dNode);

//���������� ��ʵ��ǰ�������������� �ҿ��õݹ��ջ�ֱ�ʵ��
void printNode(Btree *root);

