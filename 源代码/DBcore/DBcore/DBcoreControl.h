#pragma once

using namespace System;
using namespace System::Collections;
using namespace System::Windows::Forms;
#include "DB.h"

namespace DBcore {

	/// <summary>
	/// CCDControl 摘要
	/// </summary>
	///
	/// 警告: 如果更改此类的名称，则需要更改
	///          与此类所依赖的所有 .resx 文件关联的托管资源编译器工具的
	///          “资源文件名”属性。否则，
	///          设计器将不能与此窗体的关联
	///          本地化资源正确交互。
	public ref class DBcore : public System::Windows::Forms::UserControl
	{
	public:
		DBcore(String^ dbroot)
		{
			d=new DB(ConvertToString(dbroot));
			line=new vector<string>();
		}
		void query(String^ query)
		{
			try
			{
				d->result->clear();
				d->queryline(ConvertToString(query));
				nowline=0;
				totalnums=d->result->size();
			}
			catch (Exception^ e)
			{
				throw e;
			}
		}
		/**将结果处理成行
		 *每运行一次这个语句下移一行
		 */
		bool fetchline()
		{
			if(d->field.size()<=0) return false;
			int i=0,y=0;
			line->clear();
			string tmp="";
			while(y<(int)(totalnums/d->field.size()))
			{
				for (i=0;i<(int)d->field.size();i++)
				{
					tmp=d->result->at(y*d->field.size()+i);
					if(y==nowline)
					{
						line->push_back(tmp);
					}
				}
				if(y==nowline)
				{
					nowline++;
					break;
				}
				y++;
			}
			
			if(line->size()==0)
				return false;
			return true;

		}
		/**得到当前行时的值
		 *@param String^ tablename
		 */
		String^ get(String^ tablename)
		{
			if(line->size()==0)
				return "";
			int i=0;
			int tablepos=-1;
			//得到表对应tablepos
			for(i=0;i<(int)d->field.size();i++){
				if(d->field[i]==ConvertToString(tablename))
				{
					tablepos=i;
					break;
				}
			}
			if(tablepos==-1)
			{
				cout<<"error:错误的表名"<<endl;
				return "";
			}

			return gcnew String(line->at(tablepos).c_str());
		}
	private:
		DB* d;
		vector<string>* line;
		int nowline;
		int totalnums;
	protected:
		std::string ConvertToString(System::String^ str)
		{
			int q=(int)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(str);
			char* p=(char*)q;
			return std::string(p);
		}
	};
}
