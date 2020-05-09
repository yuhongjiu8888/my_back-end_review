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

	Node* rootP;	//���ڵ�ָ��
	int n;		//�ڵ���
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
		tree& tn = find(d);			//1.�ҵ�ɾ������ĸ��ڵ�
		if ( tn == NULL ) return false ;	
		Node *p = tn;				//2.��ָ�븴��һ��
		if (tn->L!=NULL) insert(tn->R,tn->L);	//3.�����������뵽��������
		tn = tn->R;				//4.�������ָ���ָ��ָ������
		delete p;				//5.ɾ��
		--n;
		return true;
	}
	const T& root() const{ if(!rootP) throw"��"; return rootP->data;}
	void update(const T& old ,const T& newdata){
		if(remove(old)) insert(newdata);

	}

	void print(){
		print(rootP,0,'*');
		cout<<"--------------------------------"<<endl;
	}



	void insert(tree& t, Node* p){//�βδ����ö�ʵ�ν��в���
		if(t==NULL)
			t = p;
		else if(t->data > p->data)
			insert(t->L,p);
		else if(t->data < p->data)
			insert(t->R ,p);
	}


	Node*& find(tree& t,const T& d)	//����ָ��ı�������ǿ�����ָ��(������dΪ���������ĸ�ָ��)
	{
		if ( t == NULL ) return t;	//û�ҵ�
		else if ( d == t->data ) return t;//�ҵ���
		else if (d < t->data){
			return find(t->L,d);
		
		}
		else if (d > t->data){
                        return  find(t->R,d);
                }
	}

	void travel(tree t)const{//����
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

