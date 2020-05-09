#include <iostream>
using namespace std;
typedef int T;
#include "01list.h"

void List::push_front(const T& d){	//ͷ��
	Node *p = new Node(d);//��̬�ڴ�
	p->next = head;
	head = p;
}

void  List::push_back(const T& d){	//β��
	insert(d,size());
}

int  List::size() const{	//����������
	int cnt = 0;
	Node *p = head;
	while(p!=NULL)
	{
		++cnt;
		p = p->next;
	
	}
	return cnt;
}

List::Node*&  List::getptr(int pos)//��������ָ���ƶ�λ�õ�ָ��
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

void  List::insert(const T& d,int pos){//������λ�ò���
	Node*& pn = getptr(pos);	//���ó�ʼ��������ԭʼָ��)
	Node *p = new Node(d);
	p->next = pn;
	pn = p;
	++len;
}

void  List::erase( int pos ){//��Чλ��Ϊ0~size()-1
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

//��
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

void  List::set(int pos ,const T& d){//�޸�����
	if(pos<0||pos>=size()) return ;
	getptr(pos)->data = d;
}


//��
T  List::back() const{
	if(empty()) throw "��";
	Node *p = head;
	while(p->next!=NULL){
		p = p->next;
	}
	return p->data;
}

void  List::travel() const{//����
	Node *p = head;
	while (p!=NULL){
		cout<<p->data<< " ";
		p = p->next;
	}
	cout<<endl;
}		

void  List::clear(){//�����������
		
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
		


