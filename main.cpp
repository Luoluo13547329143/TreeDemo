#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main() {

	int test[] = { 25, 20, 30, 38, 10, 5, 25, 12, 11};
	Btree *root = NULL, *node = NULL;
	
	node = new Bnode;
	node->data = test[0];
	insertNode(&root, node);
	for (int i = 1; i < sizeof(test) / sizeof(test[0]); i++) {
		node = new Bnode;
		node->data = test[i];
		insertNode(&root, node);//����ָ���Ӧ�� �����ڵ�ָ�������
	}
	printNode(root);
	system("pause");
	//��ѯ�ڵ�
	Bnode *node1 = queryNode(root, 11);
	printf("��ѯ11 %s", node1 ? "����" : "������");
	Bnode *node2 = queryNode(root, 33);
	printf("��ѯ33 %s", node2 ? "����" : "������");

	//ɾ���ڵ�
	Bnode *deleteN = NULL;
	deleteNode(root, 20, deleteN);
	if (deleteN) {
		delete deleteN;
		deleteN = NULL;
	}
	printNode(root);
	system("pause");
	Bnode *node3 = queryNode(root, 20);
	printf("��ѯ20 %s", node3 ? "����" : "������");
	

	deleteNode(root, 30, deleteN);
	if (deleteN) {
		delete deleteN;
		deleteN = NULL;
	}
	else {
		printf("�ýڵ㲻����");
	}
	printNode(root);
	return 0;
}