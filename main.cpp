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
		insertNode(&root, node);//二级指针的应用 传根节点指针的引用
	}
	printNode(root);
	system("pause");
	//查询节点
	Bnode *node1 = queryNode(root, 11);
	printf("查询11 %s", node1 ? "存在" : "不存在");
	Bnode *node2 = queryNode(root, 33);
	printf("查询33 %s", node2 ? "存在" : "不存在");

	//删除节点
	Bnode *deleteN = NULL;
	deleteNode(root, 20, deleteN);
	if (deleteN) {
		delete deleteN;
		deleteN = NULL;
	}
	printNode(root);
	system("pause");
	Bnode *node3 = queryNode(root, 20);
	printf("查询20 %s", node3 ? "存在" : "不存在");
	

	deleteNode(root, 30, deleteN);
	if (deleteN) {
		delete deleteN;
		deleteN = NULL;
	}
	else {
		printf("该节点不存在");
	}
	printNode(root);
	return 0;
}