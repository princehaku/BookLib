//B树节点cpp文件
//
//by baizhongwei
//blog http://haku.webcpp.net
#include "stdafx.h"
#include "BTreeNode.h"

BTreeNode::BTreeNode(string value,int key){
		this->value     =   value;
		this->key       =   key;
		this->parent    =   NULL;   /*父节点*/
		this->pre       =   NULL;	/*前驱节点*/
		this->next      =   NULL;   /*后继节点*/
		this->leftchild =   NULL;	/*左孩子*/
		this->rightchild=   NULL;   /*右孩子*/
	}