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
	//�жϴ���Ľڵ��Ƿ�Ϊ�գ���Ϊ������ϴ�ýڵ�ָ�����ָ��
	if (!node) {
		return false;
	}
	else {
		node->lChild = NULL;
		node->rChild = NULL;
	}

	//����ڵ��Ϊ�������
	//1 ����������Ľڵ�Ϊ���ڵ�
	//2 ���нڵ㣬�ȽϺ����
	if (*root) {//���ڸ��ڵ�
		tem = *root;
	}
	else
	{//�����ڸ��ڵ�
		*root = node;
		return true;
	}

	//���ҵ�Ҫ�������ײ㸸�ڵ�
	while (tem != NULL) {
		parent = tem;
		if (isLess(parent->data, node->data)) {
			tem = parent->rChild;
		}
		else {
			tem = parent->lChild;
		}
	}

	//�ٸ���ֵ�Ĵ�С���в���
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
	//�ж����Ƿ����
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
	//�ж����Ƿ����
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
	//�����������ڵ㲻Ϊ��
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
	Bnode *parent = NULL;//ɾ���ڵ�ĸ��ڵ�
	//���жϸ��ڵ��Ƿ����(���Ƿ����)
	if (!root) return nullptr;

	//ȷ��ɾ���ڵ��Ƿ��������
	dNode = queryNode(root, key, &parent);
	if (!dNode) {
		printf("%d���ڸ����У��޷�ɾ��", key);
		return root;
	}
	//ȷ��ɾ���ڵ��λ��
	//1����ڵ��Ǹ��ڵ㣬 ��ֱ��ɾ��
	if (root->data == dNode->data) {
		return NULL;
	}
	//2����ڵ���Ҷ�ӽڵ㣬 ���жϷ�λ�����ڵ�ָ��ָ���
	if (dNode->lChild == NULL && dNode->rChild == NULL) {
		if (isLess(parent->data, dNode->data)) {
			parent->rChild = NULL;
		}
		else {
			parent->lChild = NULL;
		}
	}
	//3����ڵ������ӽڵ���һΪ�գ� ��ֱ��ɾ�������ڵ�ָ�������ӽڵ�
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
	//4����ڵ������ӽڵ㶼��Ϊ�գ� ���������������ڵ�ȡ��ɾ���ڵ�
	//ע���1 ɾ���ڵ��븸�ڵ�Ĵ�С�Ƚ�
	//2  �����ɾ���ڵ��������� ҪôΪҶ�ӽڵ� Ҫôֻ��������
	if (dNode->lChild != NULL && dNode->rChild != NULL) {
		Bnode *tem = NULL;
		Bnode *lParent = NULL;//�����������ڵ�ĸ��ڵ�
		
		if (isLess(dNode->data, parent->data)) {
			tem = findMax(dNode->lChild, &lParent);
			dNode->data = tem->data;
			dNode = tem;
			//���ж��������Ƿ�ֻ��һ�����ڵ�
			if (lParent == NULL) {//����һ���ڵ�
				parent->lChild->lChild = NULL;
				return root;
			}

			//����ڵ���Ҷ�ӽڵ㣬 ���жϷ�λ�����ڵ�ָ��ָ���
			if (dNode->lChild == NULL && dNode->rChild == NULL) {
				if (isLess(lParent->data, dNode->data)) {
					lParent->rChild = NULL;
				}
				else {
					lParent->lChild = NULL;
				}
			}
			//��Ϊ�����������ڵ� �����ҽڵ�ض�Ϊ��
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
			//���ж��������Ƿ�ֻ��һ�����ڵ�
			if (lParent == NULL) {//����һ���ڵ�
				parent->rChild->lChild = NULL;
				return root;
			}

			//����ڵ���Ҷ�ӽڵ㣬 ���жϷ�λ�����ڵ�ָ��ָ���
			if (dNode->lChild == NULL && dNode->rChild == NULL) {
				if (isLess(lParent->data, dNode->data)) {
					lParent->rChild = NULL;
				}
				else {
					lParent->lChild = NULL;
				}
			}
			//��Ϊ�����������ڵ� �����ҽڵ�ض�Ϊ��
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
	//�ݹ�ʵ��ǰ�����
	/*if (!root) return;
	printf("-%d-", root->data);
	printNode(root->lChild);
	printNode(root->rChild);*/

	//�ݹ�ʵ���������
	if (!root) return;
	printNode(root->lChild);
	printf("-%d-", root->data);
	printNode(root->rChild);
}
