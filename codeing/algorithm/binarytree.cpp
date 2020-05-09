#include <iostream>
#include <iomanip>
using namespace std;

typedef char T;



class bst{
	struct Node{
		T data ;
		Node * L;
		Node * R;
		Node(const T& d):data(d),L(0),R(0) {}
		Node(const T& d,Node * l, Node * r):data(d),L(l),R(r) {}

	};
	typedef Node* tree;

	Node* rootP;	//根节点指针
	int n;		//节点数
public:
	bst():rootP(),n(){}
	void clear(){ clear(rootP);n=0; }
	~bst(){clear(); }
	void insert(const T& d){ insert(rootP,new Node(d)); ++n; }
	tree& find(const T& d){ return find(rootP,d);}
	void travel() const{ travel(rootP);cout<<endl; }
	bool empty()const{ return rootP==NULL; }
	int size()const{return n;}
	bool remove(const T& d){
		tree& tn = find(d);			//1.找到删除几点的根节点
		if ( tn == NULL ) return false ;	
		Node *p = tn;				//2.将指针复制一份
		if (tn->L!=NULL) insert(tn->R,tn->L);	//3.将左子树插入到又子树中
		tn = tn->R;				//4.将跟结点指向的指针指向子树
		delete p;				//5.删除
		--n;
		return true;
	}
	const T& root() const{ if(!rootP) throw"空"; return rootP->data;}
	void update(const T& old ,const T& newdata){
		if(remove(old)) insert(newdata);

	}

	void print(){
		print(rootP,0,'*');
		cout<<"--------------------------------"<<endl;
	}



	void insert(tree& t, Node* p){//形参传引用对实参进行操作
		if(t==NULL)
			t = p;
		else if(t->data > p->data)
			insert(t->L,p);
		else if(t->data < p->data)
			insert(t->R ,p);
	}


	Node*& find(tree& t,const T& d)	//返回指针的本身而不是拷贝的指针(返回以d为根的子树的根指针)
	{
		if ( t == NULL ) return t;	//没找到
		else if ( d == t->data ) return t;//找到了
		else if (d < t->data){
			return find(t->L,d);
		
		}
		else if (d > t->data){
                        return  find(t->R,d);
                }
	}

	void travel(tree t)const{//遍历
		if(t!=NULL){
			travel(t->L);
			cout<<t->data<<" ";
			travel(t->R);
		}

	}

	void clear(tree& t ){
		if(t!=NULL){
			clear(t->L);
			clear(t->R);
			delete t;
			t = NULL;
		}

	}


	int hight(tree t)
	{
		if ( t==NULL) return 0;
		int lh = hight(t->L);
		int rh = hight(t->R);
		return 1+(lh>rh?lh:rh);
	}

	void print(tree t, int space ,char sign){
		if (t==NULL) return ;
		print(t->R,space+3,'/');
		cout<<setw(space+1)<<sign<<t->data<<endl;
		print(t->L,space+3,'\\');
	}

};



int main()
{
	bst b;
	b.insert('k'); b.insert('s');b.insert('f');b.insert('t');
	b.insert('a'); b.insert('m');b.insert('x');b.insert('e');
	b.insert('b'); b.insert('w');b.insert('u');b.insert('j');
//	b.travel();
	b.print();	

	b.update('a','*'); b.update('x','z');
	//b.travel();
	b.print();

	while(!b.empty()) b.remove(b.root());
	cout<<"size:" <<b.size()<<endl;
//	 b.travel();
	b.print();
	return 0;
}

