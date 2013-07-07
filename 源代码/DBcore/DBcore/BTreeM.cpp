//B树主操作cpp文件
//
//by baizhongwei
//blog http://haku.webcpp.net
#include "stdafx.h"
#include "BTreeM.h"

int BTree::count(BTreeNode* p)
{
		BTreeNode* p2=p;
		//先往前计算
		int p_i=0;
		while(p2->pre)
		{
			p_i++;
			p2=p2->pre;
		}
		//往后计算
		int n_i=0;
		while(p->next)
		{
			n_i++;
			p=p->next;
		}
		return p_i+n_i+1;
	}

BTree::BTree(){
		this->root=NULL;
	}

 BTree::BTree(string rootvalue,int rootkey){
		
		this->root=new BTreeNode(rootvalue,rootkey);
	
	}

BTreeNode* BTree::del(BTreeNode* p){

		if(p==NULL) return 0;

		int  up=0;
		//如果右孩子为空且左孩子为空.直接删除
		if(p->leftchild==NULL&&p->rightchild==NULL)
		{
			int now=p->key;

			if(p->parent!=NULL)
			{
				BTreeNode* h=p->parent;

				while(h)
				{

					//如果key大于now
					//40       +42+
					//     41
					if(h->key>now&&h->leftchild==p)
					{
						h->leftchild=p->next;
						if(h->pre)h->pre->rightchild=p->next;
						up=1;
						break;
					}
					//游标下移
					if(h->next)
					{
						h=h->next;
					}
					else
					{
						break;
					}
				}
				if(up!=1&&h->rightchild==p)
				{
					h->rightchild=p->next;
					if(h->next)h->next->leftchild=p->next;
				}

			}
			if(p->parent==NULL)
			{
				this->root=NULL;
				if(p->pre)
				{
					this->root=p->pre;
				}
				if(p->next)
				{
					this->root=p->next;
				}
			}
			//如果存在前续..跳过这个结点.
			if(p->pre)
			{
				p->pre->next=p->next;
			}
			//如果存在后续..跳过这个结点.
			if(p->next)
			{
				p->next->pre=p->pre;
			}
			return p;
		}
		//如果左孩子不为空且右孩子为空..左子支上移..然后分裂之
		if(p->leftchild!=NULL&&p->rightchild==NULL)
		{
			BTreeNode* r=p->leftchild;
			int now=p->key;
			r->parent=p->parent;
			while(r->next)
			{
				r->parent=p->parent;
				r=r->next;
			}
			r->parent=p->parent;

			if(p->parent!=NULL)
			{
				BTreeNode* h=p->parent;

				while(h)
				{

					//如果key大于now
					//40       +42+
					//     41
					if(h->key>now&&h->leftchild==p)
					{
						h->leftchild=p->next;
						if(h->pre)h->pre->rightchild=p->next;
						up=1;
						break;
					}
					//游标下移
					if(h->next)
					{
						h=h->next;
					}
					else
					{
						break;
					}
				}
				if(up!=1&&h->rightchild==p)
				{
					h->rightchild=p->next;
					if(h->next)h->next->leftchild=p->next;
				}

			}
			if(p->parent==NULL)
			{
				this->root=NULL;
				if(p->pre)
				{
					this->root=p->pre;
				}
				if(p->next)
				{
					this->root=p->next;
				}
			}
			//如果存在前续..跳过这个结点.
			if(p->pre)
			{
				p->pre->next=p->leftchild;
				p->pre->rightchild=p->leftchild->leftchild;
			}
			//如果存在后续..跳过这个结点.
			if(p->next)
			{
				p->next->pre=r;
				p->next->leftchild=r->rightchild;
			}
			if(p->parent==NULL)
			{
				this->root=p->leftchild;
				splitnode(this->root,1);
			}
			return p;
		}

		//如果右孩子不为空且左孩子为空..右子支上移..然后分裂之
		if(p->leftchild==NULL&&p->rightchild!=NULL)
		{

			BTreeNode* r=p->rightchild;

			int now=p->key;
			//设置父节点
			r->parent=p->parent;
			while(r->next)
			{
				r->parent=p->parent;
				r=r->next;
			}
			r->parent=p->parent;

			if(p->parent!=NULL)
			{
				BTreeNode* h=p->parent;

				while(h)
				{

					//如果key大于now
					//40       +42+
					//     41
					if(h->key>now&&h->leftchild==p)
					{
						h->leftchild=p->next;
						if(h->pre)h->pre->rightchild=p->next;
						up=1;
						break;
					}
					//游标下移
					if(h->next)
					{
						h=h->next;
					}
					else
					{
						break;
					}
				}
				if(up!=1&&h->rightchild==p)
				{
					h->rightchild=p->next;
					if(h->next)h->next->leftchild=p->next;
				}

			}
			if(p->parent==NULL)
			{
				this->root=NULL;
			}
			//如果存在前续..跳过这个结点.
			if(p->pre)
			{
				p->pre->next=p->rightchild;
				p->pre->rightchild=p->rightchild->leftchild;
			}
			//如果存在后续..跳过这个结点.
			if(p->next)
			{
				p->next->pre=r;
				p->next->leftchild=r->rightchild;
			}
			if(p->parent==NULL)
			{
				this->root=p->leftchild;
				splitnode(this->root,1);
			}
			if(p->parent==NULL)
			{
				this->root=p->rightchild;
				splitnode(this->root,1);
			}
			return p;
		}
		//如果右孩子不为空且左孩子不为空..进入左子支的最后一个最大的递归
		if(p->leftchild!=NULL&&p->rightchild!=NULL)
		{
			BTreeNode* r=p->leftchild;

			BTreeNode* w=NULL;

			while(r->next)
			{
				r=r->next;
			}

			while(r->rightchild!=NULL)
			{
				while(r->next)
				{
					r=r->next;
				}
				if(r->rightchild!=NULL)break;

				r=r->rightchild;
			}
			w=r;
			if(r->rightchild)r=r->rightchild;
			//转移节点
			if(r->pre)r->pre->next=NULL;
			//父级删除之
			if(w->rightchild==r){w->rightchild=NULL;}
			//复制顶节点的属性
			if(p->leftchild!=r)r->leftchild=p->leftchild;
			r->rightchild=p->rightchild;
			r->pre=p->pre;
			r->next=p->next;
			r->parent=p->parent;
			if(p->next)p->next->pre=r;
			if(p->pre)p->pre->next=r;
			if(p->leftchild&&p->leftchild!=r)
			{

				BTreeNode* s=p->leftchild;

				while(s)
				{
					s->parent=r;
					s=s->next;
				}
			}
			if(p->rightchild){

				BTreeNode* s=p->rightchild;

				while(s)
				{
					s->parent=r;
					s=s->next;
				}
			}
			if(p->parent==NULL||p==root){

				this->root=r;

				return p;
			}
			if(p->parent->leftchild==p)
			{
				p->parent->leftchild=r;
			}
			if(p->parent->rightchild==p)
			{
				p->parent->rightchild=r;
			}
			return p;

		}


		return NULL;
	}

bool BTree::del(int key){

	BTreeNode* p=searchNode(root,key);
	
	if(p==NULL) return 0;
	/*p->parent=new BTreeNode("321",5);
	this->root=p->parent;*/

	p=del(p);

	if(p!=NULL)delete p;

	return 1;
 }

BTreeNode* BTree::insert(string value,int key)
	{
		if(this->root==NULL)
		{
			this->root=new BTreeNode(value,key);
			return this->root;
		}
		return addnode(root,value,key);
	}


 void BTree::splitnode(BTreeNode* p,int m)
	{
		if(m==1&&count(p)>2)
		{
			//cout<<"所在是根节点..大于2..分离节点"<<endl;
			//找到处于中间的节点
			while(p->pre)p=p->pre;

			BTreeNode* p_mid=p->next;

			BTreeNode* p_r=p->next->next;

			p_mid->leftchild=p;
			p_mid->rightchild=p_r;
			p_mid->pre=NULL;
			p_mid->next=NULL;
			//左节点清理
			p->parent=p_mid;
			p->next=NULL;
			BTreeNode* vec=NULL;
			vec=p->leftchild;
			while(vec)
			{
				vec->parent=p;
				vec=vec->next;
			}
			vec=p->rightchild;
			while(vec)
			{
				vec->parent=p;
				vec=vec->next;
			}
			//右节点清理
			p_r->parent=p_mid;
			p_r->pre=NULL;
			vec=p_r->leftchild;
			while(vec)
			{
				vec->parent=p_r;
				vec=vec->next;
			}
			vec=p_r->rightchild;
			while(vec)
			{
				vec->parent=p_r;
				vec=vec->next;
			}
			//新根节点
			this->root=p_mid;
		}
		else{
			if(m!=1&&count(p)>m){
				//cout<<m<<"级节点过多..分离节点"<<endl;
				//cout<<"取中间节点..位置:"<<m/2<<endl;
				//标记p
				int i=0;
				//左节点
				while(p->pre)p=p->pre;
				BTreeNode* p_mid=p;
				//中间节点
				while(i++<m/2&&p_mid->next)
				{
					//cout<<i<<endl;
					p_mid=p_mid->next;
				}
				BTreeNode* p_r=p_mid->next;
				//左节点清理
				//更新父节点
				BTreeNode* pt=p;
				while(pt->next!=NULL&&pt!=p_mid)
				{
					pt->parent=p_mid;
					pt=pt->next;
				}
				p_mid->pre->next=NULL;
				//右节点清理
				//更新父节点
				pt=p_mid->next;
				while(pt!=NULL)
				{
					pt->parent=p_mid;
					pt=pt->next;
				}
				if(p_r!=NULL)p_r->pre=NULL;
				//中间节点清理
				p_mid->leftchild=p;
				p_mid->rightchild=p_r;
				p_mid->pre=NULL;
				p_mid->next=NULL;
				//修改中间节点的父节点
				BTreeNode* p_p=p_mid->parent;
				/*这里可能有问题..待检测*/
				p_mid->parent=p_p->parent;
				//在上层寻找p应该插入的位置
				int key_p=0;
				i=0;
				while(p_p)
				{
					key_p=p_p->key;
					//如果第一个就比key大..则直接插入
					if(i==0&&key_p>p_mid->key)
					{
						//cout<<key_p<<endl;
						p_mid->next=p_p;
						p_p->pre=p_mid;
						p_p->leftchild=p_mid->rightchild;
						if(p_p==this->root)this->root=p_mid;
						splitnode(p_p,m-1);
						break;
					}
					//如果所在节点的key比中间节点key小
					//则在所在key后插入中间节点
					if(key_p<p_mid->key)
					{
						//cout<<key_p<<endl;
						BTreeNode* p_pn=p_p->next;
						p_p->next=p_mid;
						p_mid->pre=p_p;
						p_p->rightchild=p_mid->leftchild;
						p_mid->leftchild->parent=p_p;
						if(p_pn){
							p_pn->leftchild=p_mid->rightchild;
							p_mid->next=p_pn;
							p_pn->pre=p_mid;
							p_mid->rightchild->parent=p_pn;
							p_mid=p_pn;
						}
						//cout<<m<<endl;
						splitnode(p_p,m-1);
						break;
					}
					p_p=p_p->next;
					i++;
				}
			}
		}
	}

	BTreeNode* BTree::addnode(BTreeNode* p,string value,int key,int m){
		//如果p是空节点..返回空
		if(p==NULL)
		{
				return p;
		}
		int now_key=p->key;
		//如果相等..则返回空
		if(now_key==key)
		{
			//throw exception("已经存在此节点");
			return NULL;
		}
		else{
			//如果当前节点值比key大.且左节点不为空.去找当前节点左子支
			if(now_key>key&&p->leftchild!=NULL)
			{
				return addnode(p->leftchild,value,key,m+1);
			}
			
			//如果当前节点值比key大.且左节点为空.在这个结点前加入节点且
			if(now_key>key&&p->leftchild==NULL)
			{
				/**cout<<"节点key:"<<key<<"  加入层级:"<<m<<endl;*/
				BTreeNode* i=new BTreeNode(value,key);
				BTreeNode* p_h=p->pre;
				p->pre=i;
				i->next=p;
				i->pre=p_h;
				if(p_h!=NULL)p_h->next=i;
				i->rightchild=p->leftchild;
				i->parent=p->parent;
				//把父节点的下一级设为新的节点
				if(p->parent!=NULL&&p->parent->leftchild==p){
					p->parent->leftchild=i;
				}
				else if(p->parent!=NULL&&p->parent->rightchild==p)
				{
					p->parent->rightchild=i;
				}
				//如果是根节点..转换之
				if(p==this->root)
				{
					this->root=i;
				}
				//分离节点所在层
				splitnode(i,m);
			}
			//如果当前节点值比key小.且右子支不为空.去找当前节点右子支
			if(now_key<key&&p->rightchild!=NULL)
			{
				//如果这个结点的右子支的key比右边节点key小..去右边节点寻找
				if(p->next!=NULL&&p->rightchild->key<p->next->key)
				{
					return addnode(p->next,value,key,m);
				}
				return addnode(p->rightchild,value,key,m+1);
			}
			
			//如果当前节点值比key小.且右子支为空.去找当前节点后继
			if(now_key<key&&p->rightchild==NULL)
			{
				if(p->next!=NULL)
				{
					return addnode(p->next,value,key,m);
				}
				else
				{
					/**cout<<"节点key:"<<key<<"  加入层级:"<<m<<endl;*/
					BTreeNode* i=new BTreeNode(value,key);
					p->next=i;
					i->pre=p;
					i->leftchild=p->rightchild;
					i->parent=p->parent;
					//分离节点所在层
					splitnode(i,m);
				}
			}
		
			
		}

		return p;
	}
BTreeNode* BTree::searchNode(int key)
	{
		return searchNode(this->root,key);
	}

BTreeNode* BTree::searchNode(BTreeNode* p,int key){
		//如果p是空节点..返回空
		if(p==NULL)
		{
				return NULL;
		}
		int now_key=p->key;
		//如果相等..则返回空
		if(now_key==key)
		{
			//throw exception("已经存在此节点");
			return p;
		}
		else{
			//如果当前节点值比key大.且左节点不为空.去找当前节点左子支
			if(now_key>key&&p->leftchild!=NULL)
			{
				return searchNode(p->leftchild,key);
			}
			
			//如果当前节点值比key大.且左节点为空.返回空
			if(now_key>key&&p->leftchild==NULL)
			{
				return NULL;
			}
			//如果当前节点值比key小.且右子支不为空.去找当前节点右子支
			if(now_key<key&&p->rightchild!=NULL)
			{
				//如果这个结点的右子支的key比右边节点key小..去右边节点寻找
				if(p->next!=NULL&&p->rightchild->key<p->next->key)
				{
					return searchNode(p->next,key);
				}
				return searchNode(p->rightchild,key);
			}
			
			//如果当前节点值比key小.且右子支为空.去找当前节点后继
			if(now_key<key&&p->rightchild==NULL)
			{
				if(p->next!=NULL)
				{
					return searchNode(p->next,key);
				}
				else
				{
					return NULL;
				}
			}
		
			
		}

		return p;
	}


int BTree::dump(ofstream* fout)
{
	return dump(fout,this->root);
}

int BTree::dump(ofstream* fout,BTreeNode* p){
		if(p==NULL) return 0;
			fout->write(p->value.c_str(),p->value.length());
			fout->write("\x0B",1);
			stringstream s;
			s<<p->key;
			fout->write(s.str().c_str(),s.str().length());
			fout->write("\x7E",1);
			if(p->pre==NULL)dump(fout,p->leftchild);
			dump(fout,p->rightchild);
			dump(fout,p->next);
		return 1;
	}

int BTree::load(ifstream* fin){

		char ch;

		stringstream s;

		string value="";

		string key="";

		int y=0;

		if(fin->fail())return 0;

		while(!fin->eof()) {
			ch = fin->get(); 
			s<<ch;
			if (ch == '\x0B')
			{
				//cout<<s.str()<<endl;
				//清空s,,并保存到value
				value=s.str().substr(0,s.str().length()-1);
				s.str("");
			}
			if (ch == '\x7E')
			{
				y++;
				//cout<<s<<endl;
				key=s.str().substr(0,s.str().length()-1);
				this->insert(value,(int)atof(key.c_str()));
				//清空s
				s.str("");
			}
		}
			
		return y;
	}

void BTree::clear()
	{
		//del(this->root);
		this->root=NULL;
	}

string BTree::search(BTreeNode* p,int key,string pit)
{
		if(p==NULL) return "\0";

		if(p->pre==NULL){

			pit=search(p->leftchild,key);

			if(pit!="\0")return pit;

		}
		pit=search(p->rightchild,key);

		if(pit!="\0")return pit;

		pit=search(p->next,key);

		if(pit!="\0")return pit;

		if(p->key==key)return p->value;

		return "\0";
	}

string BTree::tovector_le(BTreeNode* p,int max_key,int m){

	if(p==NULL)return " ";

	if(p->pre==NULL)tovector_le(p->leftchild,max_key,m+1);

	tovector_le(p->rightchild,max_key,m+1);

	tovector_le(p->next,max_key,m+1);

	if(p->key<max_key)
	{
		//cout<<p->key<<endl;

		stringstream ss;

		ss<<p->key;

		this->k.push_back(ss.str());

		ss.str("");
	}
	return " ";
}



int BTree::searchNode_le(int maxkey,BTreeNode* w,int dep){

	if(dep==0)k.clear();

	BTreeNode* p=NULL;

	//如果存在w节点(从上一级递归下来的)切换到p节点
	if(w!=NULL)
	{
		p=w;
	}
	else
	{
		p=searchNode(this->root,maxkey);
	}
	//上级节点不为空且上级节点的key比它小
	if(p->parent!=NULL&&p->parent->key<maxkey)
	{
		return searchNode_le(maxkey,p->parent,1);

	}
	//前序节点不为空且前序节点的key比它小
	if(p->pre!=NULL&&p->pre->key<maxkey)
	{
		return searchNode_le(maxkey,p->pre,1);

	}
	//从节点开始遍历那层的节点
	this->tovector_le(p,maxkey);

	return 1;
}


string BTree::tovector_gt(BTreeNode* p,int min_key,int m){

	if(p==NULL)return " ";

	if(p->pre==NULL)tovector_gt(p->leftchild,min_key,m+1);

	tovector_gt(p->rightchild,min_key,m+1);

	tovector_gt(p->next,min_key,m+1);

	if(p->key>min_key)
	{
		//cout<<p->key<<endl;

		stringstream ss;

		ss<<p->key;

		this->k.push_back(ss.str());

		ss.str("");
	}
	return " ";
}


int BTree::searchNode_gt(int minkey,BTreeNode* w,int dep){

	if(dep==0)k.clear();

	BTreeNode* p=NULL;

	//如果存在w节点(从上一级递归下来的)切换到p节点
	if(w!=NULL)
	{
		p=w;
	}
	else
	{
		p=searchNode(this->root,minkey);
	}

	//上级节点不为空且上级节点的key比它大
	if(p->parent!=NULL&&p->parent->key>minkey)
	{
		return searchNode_gt(minkey,p->parent,1);

	}
	//从节点开始遍历那层的节点
	this->tovector_gt(p,minkey);

	return 1;
}


vector<string> BTree::searchNode_le(int maxkey,int dep){

	//加入临时节点
	this->insert("NULL",maxkey);

	this->searchNode_le(maxkey,NULL,0);

	//删除临时节点
	this->del(maxkey);

	return k;
}


vector<string> BTree::searchNode_gt(int minkey,int dep){

	//加入临时节点
	this->insert("NULL",minkey);

	this->searchNode_gt(minkey,NULL,0);

	//删除临时节点
	this->del(minkey);

	return k;
}