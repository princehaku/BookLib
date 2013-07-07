//B树主操作头文件
//
//by baizhongwei
//blog http://haku.webcpp.net
#ifndef BTree_H
#define BTree_H

#include "BTreeNode.h"
#include <fstream>
#include <sstream>
class BTree{
	
private:
	/**结果迭代器
	*用于保存临时结果
	*@access private
	*/
	vector<string> k;
	/**根节点
	*@access private
	*/
	BTreeNode* root;
	/**添加节点
	 *@access private
	 *@param BTreeNode* p 节点
	 *@param string value 节点值
	 *@param int key 节点key
	 *@param int m 层级 默认为1
	 */
	BTreeNode* addnode(BTreeNode* p,string value,int key,int m=1);
	/**遍历p节点及其子节点..输出至文件
	  *@param ofstream* fout
	  *@param BTreeNode* p 节点
	  */
	int dump(ofstream* fout,BTreeNode* p);
	/**删除这个结点
	*不删除节点空间
	*@param BTreeNode* p 节点
	*return BTreeNode*
	*/
	BTreeNode* del(BTreeNode* p);
	/**搜索B树
	*@param BTreeNode* p 节点
	*@param int key 节点索引key值
	*@return BTreeNode*
	*/
	BTreeNode* searchNode(BTreeNode* p,int key);
	/**计算p节点所在层级的节点数量
	*@param BTreeNode* p 节点
	*@return int 节点数量
	*/
	int count(BTreeNode* p);
	/**分离p节点所在层级的所有节点..层级为m
	*@param BTreeNode* p 节点
	*@param int m 节点层级
	*@return void
	*/
	void splitnode(BTreeNode* p,int m);
	/**遍历树查找key=的节点
	*@return value
	*/
	string BTree::search(BTreeNode* p,int key,string pit="\0");
	/**遍历节点所在层级及其子节点找寻比它小的节点
	*@return string
	*/
	string BTree::tovector_le(BTreeNode* p,int max_key,int m=0);
	/**搜索B树中所有key比maxkey小的节点
	*@param BTreeNode* p 节点
	*@param int key 节点索引key值
	*@return int
	*/
	int BTree::searchNode_le(int maxkey,BTreeNode* w,int dep=0);
	/**遍历节点所在层级及其子节点找寻比它大的节点
	*@return string
	*/
	string BTree::tovector_gt(BTreeNode* p,int min_key,int m=0);
	/**搜索B树中所有key比minkey大的节点
	*@param BTreeNode* p 节点
	*@param int key 节点索引key值
	*@return int
	*/
	int BTree::searchNode_gt(int minkey,BTreeNode* w,int dep=0);
public:
	/**空构造函数
	  */
	BTree();
	/**遍历树查找key=的节点
	*@return BTreeNode*
	*/
	BTreeNode* BTree::searchNode(int key);
	/**默认构造函数
	  *@param string rootvalue 根节点值
	  *@param int rootkey 根节点索引key值
	  */
	BTree(string rootvalue,int rootkey);
	/**插入新节点到B树
	  *@param string value 节点值
	  *@param int key 节点索引key值
	  *@return BTreeNode*
	  */
	BTreeNode* insert(string value,int key);
	/**遍历节点下子节点..清空value相等的子节点..和节点的空间
	*@param BTreeNode* p 节点
	*/
	bool del(int key);
	/**遍历整个B树..输出至文件
	  *@param ofstream* fout
	  */
	int dump(ofstream* fout);
	/**读取文件..读取前不会清空当前节点	 
	  *@param ifstream* fin
	  */
	int load(ifstream* fin);
	/**清空整个B树
	  */
	void clear();
	/**遍历树查找key=的节点
	 *@return value
	 */
	string BTree::search(int key){
		return search(this->root,key);
	}
	/**遍历树查找key<maxkey的节点
	*@return vector<string>
	*/
	vector<string> BTree::searchNode_le(int maxkey,int dep=0);
	/**遍历树查找key>minkey的节点
	*@return vector<string>
	*/
	vector<string> BTree::searchNode_gt(int minkey,int dep=0);

};


#endif