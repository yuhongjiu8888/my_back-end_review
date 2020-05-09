#include <iostream>
using namespace std;

typedef int T;
struct Node{
	T data;
	Node* next;
	Node(const T& d=T()):data(d),next(0){}//零初始化
};

class List{
	Node* head;//头指针，用来保存头结点地址
	int len;
public:
	List():head(NULL),len(0){}
	void push_front(const T& d){	//头插
		Node *p = new Node(d);//动态内存
		p->next = head;
		head = p;
	}

	void push_back(const T& d){	//尾插
		insert(d,size());
	}

	int size() const{	//计算链表长度
		int cnt = 0;
		Node *p = head;
		while(p!=NULL)
		{
			++cnt;
			p = p->next;
		}
		return cnt;
	}

	Node*& getptr(int pos)//找链表中指向制定位置的指针
	{
		if(pos<0 || pos>size()) pos = 0;
		if(pos==0)	return head;
		Node *p = head;
		for(int i =1 ;i<pos;i++)
		{
			p = p->next;
		}
		return (*p).next;
	}

	void insert(const T& d,int pos){//在任意位置插入
		Node*& pn = getptr(pos);	//引用初始化（就是原始指针)
		Node *p = new Node(d);
		p->next = pn;
		pn = p;
		++len;
	}

	void erase( int pos ){//有效位置为0~size()-1
		if ( pos<0 || pos>=size() )
		{
			return;
		}

		Node *& pn = getptr(pos);
		Node * p = pn;
		pn = pn->next;
		delete p;
		--len;
		
	}


	void remove (const T& d){
		int pos;
		while((pos = find(d))!=-1)
			erase(pos);
	}

	int find (const T& d) const{
		int pos;
		Node *p = head;
		while(p){
			if(p->data == d) return pos;
			p=p->next;
			++pos;
		}
		return -1;
	}

	void set(int pos ,const T& d){//修改数据
		if(pos<0||pos>=size()) return ;
		getptr(pos)->data = d;
	}


	bool empty() const{return head==NULL;}
	T front() const{if(empty()) throw "空";return head->data;}
	T back() const{
		if(empty()) throw "空";
		Node *p = head;
		while(p->next!=NULL){
			p = p->next;
		}
		return p->data;
	}

	void travel() const{//遍历
		Node *p = head;
		while (p!=NULL){
			cout<<p->data<< " ";
			p = p->next;
		}
		cout<<endl;
	}		

	void clear(){//清空所有链表
		
		while(head!=NULL){
		Node *temp = head->next;
		delete head;
		head = temp;
		}
	}
	~List()
	{
		clear();
	}
		
};
int main()
{
	List l;
	l.push_front(5);
	l.push_front(8);
	l.push_front(34);
	l.insert(52,1);
	l.insert(100,1);
	l.push_back(102);
	l.erase(l.size()-1);
	l.travel();
	l.set(0,888);
	l.travel();

	return 0;
}

