//数据库操作头文件
//
//by baizhongwei
//blog http://haku.webcpp.net
#ifndef DB_H
#define DB_H
#include "stdafx.h"
#include "BTreeM.h"
#include <direct.h>
namespace DBcore{
	class DB
	{
		friend ref class DBcore;
	private:
		//数据库根目录
		string dbroot;
		//表名
		string frmname;
		//B树迭代器
		vector<BTree*> BTreeM;
		//字段名
		vector<string> field;
		//字段属性
		vector<string> fieldtype;
		//数据库名
		string dbname;
	protected:
		/**删除索引
		*@param int Bpos
		*@param string value
		*/
		void delidx(int Bpos,string value);
		/**将value以s分割
		*@param string value
		*@param char s
		*@return vector<string>
		*/
		vector<string> split(string value,char s);
		/**建立表
		*@param string db_name 数据库名
		*/
		void createfrm(string frm_name);
		/**创建字段
		*@param string frmname 表名
		*@vector<string> 字段名
		*/
		void createfield(string frmname,vector<string> tb);
		/**找寻结果
		*@param string frmname 表名
		*@param string tdname 字段名
		*@param string value
		*@return vector<string>* 找到的值的key
		*/
		vector<string>* select(string frmname,string tdname,string value,int y=-1);

		/**找寻比maxvalue小的结果
		*@param string frmname 表名
		*@param string tdname 字段名
		*@param string maxvalue 最大值
		*@return vector<string>* 找到的值的key
		*/
		vector<string>* selectls(string frmname,string tdname,string maxvalue,int y=-1);

		/**找寻比maxvalue小的结果并删除
		*@param string frmname 表名
		*@param string tdname 字段名
		*@param string maxvalue 最大值
		*@return vector<string>* 找到的值的key
		*/
		vector<string>* removels(string frmname,string tdname,string maxvalue,int y=-1);
		/**找寻比minvalue大的结果并删除
		*@param string frmname 表名
		*@param string tdname 字段名
		*@param string maxvalue 最大值
		*@return vector<string>* 找到的值的key
		*/
		vector<string>* removegt(string frmname,string tdname,string minvalue,int y=-1);

		/**找寻比minvalue大的结果
		*@param string frmname 表名
		*@param string tdname 字段名
		*@param string maxvalue 最大值
		*@return vector<string>* 找到的值的key
		*/
		vector<string>* selectgt(string frmname,string tdname,string minvalue,int y=-1);

		/**将result中对应的删除
		*@param string frmname 表名
		*@param string tdname 字段名
		*/
		void removeall(string frmname,string tdname,vector<string> valueAl);
		/**找寻结果存入result中
		*@param string frmname 表名
		*@param string tdname 字段名
		*@param string maxvalue 最大值
		*/
		vector<string>* selectall(string frmname,string tdname,vector<string> valueAl);
		/**读取索引
		*@param string index_filename 索引文件
		*@param int i 序号
		*/
		void loadindex(string index_filename,int i);
		/**表是否存在
		*@return bool
		*/
		bool ifexfrm();
		/**读取字段
		*@param string frmname 表名
		*@return bool
		*/
		bool loadfield(string frmname);
		/**是否存在字段
		*@return bool
		*/
		bool ifexfield();
		/**删除与值相等的数据
		*@param string frmname 表名
		*@param string tdname 字段名
		*@param string value 值
		*/
		vector<string>* remove(string frmname,string tdname,string value,int y=-1);
		/**插入数据
		*@param string frmname 表名
		*@vector<string> row 字段名
		*/
		void insert(string frmname,vector<string> row);
	public:
		/**初始化根节点
		*/
		DB(string dbroot);
			/**结果迭代器
			@access public
			*/
			vector<string>* result;
		/**分析并执行简单的单行sql语句
		*@param string queryline
		*/
		void queryline(string queryline);
	};


}
#endif