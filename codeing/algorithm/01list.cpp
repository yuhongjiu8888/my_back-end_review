#include <iostream>
using namespace std;
typedef int T;
#include "01list.h"

void List::push_front(const T& d){	//头插
	Node *p = new Node(d);//动态内存
	p->next = head;
	head = p;
}

void  List::push_back(const T& d){	//尾插
	insert(d,size());
}

int  List::size() const{	//计算链表长度
	int cnt = 0;
	Node *p = head;
	while(p!=NULL)
	{
		++cnt;
		p = p->next;
	
	}
	return cnt;
}

List::Node*&  List::getptr(int pos)//找链表中指向制定位置的指针
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

void  List::insert(const T& d,int pos){//在任意位置插入
	Node*& pn = getptr(pos);	//引用初始化（就是原始指针)
	Node *p = new Node(d);
	p->next = pn;
	pn = p;
	++len;
}

void  List::erase( int pos ){//有效位置为0~size()-1
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

//靠
void  List::remove (const T& d){
	int pos;
	while((pos = find(d))!=-1)
		erase(pos);
}

int  List::find (const T& d) const{
	int pos;
	Node *p = head;
	while(p){
		if(p->data == d) return pos;
		p=p->next;
		++pos;
	}
	return -1;
}

void  List::set(int pos ,const T& d){//修改数据
	if(pos<0||pos>=size()) return ;
	getptr(pos)->data = d;
}


//靠
T  List::back() const{
	if(empty()) throw "空";
	Node *p = head;
	while(p->next!=NULL){
		p = p->next;
	}
	return p->data;
}

void  List::travel() const{//遍历
	Node *p = head;
	while (p!=NULL){
		cout<<p->data<< " ";
		p = p->next;
	}
	cout<<endl;
}		

void  List::clear(){//清空所有链表
		
	while(head!=NULL){
		Node *temp = head->next;
		delete head;
		head = temp;
	}
}
 List::~List()
{
	clear();
}
		


