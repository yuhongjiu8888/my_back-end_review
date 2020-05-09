#include <iostream>
#include <string>
#include "01list.h"
using namespace std;

typedef int T;

class Stack{
	List l;	//��Ϲ�ϵ��
public:
	void push(const T& d) ;	//������ջ��Ϊջ��
	T pop() ;	//ջ�����ݳ�ջ����һ��Ԫ�س�Ϊջ��
	const T& top()const;	//ȡ��ջ������
	bool empty() const{return l.empty();}	//�Ƿ��ջ
	bool full() const{ return false;}	//�Ƿ�����
	void clear(){ l.clear() ;}		//ջ���
	int size() const{return l.size();}	//ջ�����ݸ���
};

void Stack::push(const T& d){
	l.push_front(d);
}

T Stack::pop() {
	T t  = l.front();
	l.erase(0);
	return t;
}

const T& Stack::top()const{
	return l.front();
}
int main()
{
	Stack s;
	try{
		s.push(1);
		s.push(2);
		s.push(3);
		s.push(4);
		s.push(5);
		s.push(6);
	}
	catch(const char* e)
	{
		cout<<"�쳣��"<< e << endl;
	}

	while(!s.empty())
	{
		cout<<s.pop()<<endl;
	}

	return 0;
}
