//B树节点头文件
//
//by baizhongwei
//blog http://haku.webcpp.net
#ifndef BTreeNode_H
#define BTreeNode_H

class BTreeNode{
	friend class BTree;
private:
	//节点内容
	string value;
	//关键key
	int key;
	//父节点
	BTreeNode* parent;
	//前驱节点
	BTreeNode* pre;
	//后续
	BTreeNode* next;
	//左子节点
	BTreeNode* leftchild;
	//右子节点
	BTreeNode* rightchild;
public:
	//构造函数
	BTreeNode(string value,int key);
};

#endif