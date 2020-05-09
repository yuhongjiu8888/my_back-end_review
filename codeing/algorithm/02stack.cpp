#include <iostream>
#include <string>
using namespace std;

typedef std::string T;

class Stack{
	T  a[5];
	int cur;
public:
	Stack():cur(0){}
	void push(const T& d) throw (const char*);	//������ջ��Ϊջ��
	T pop() throw (const char*);	//ջ�����ݳ�ջ����һ��Ԫ�س�Ϊջ��
	const T& top()const throw (const char*);	//ȡ��ջ������
	bool empty() const{return cur==0;}	//�Ƿ��ջ
	bool full() const{ return cur==5;}	//�Ƿ�����
	void clear(){cur = 0 ;}		//ջ���
	int size() const{return cur;}	//ջ�����ݸ���
};

void Stack::push(const T& d) throw (const char*){
	if(full()) throw "��";
	a[cur++] = d;
}

T Stack::pop()  throw (const char*){
	if(full()) throw "��";
	return a[--cur];
}

const T& Stack::top()const throw (const char*){
	if(full()) throw "��";
        return a[cur-1];
}
int main()
{
	Stack s;
	try{
		s.push("����");
		s.push("�ؾ���");
		s.push("���ٻ�");
		s.push("����");
		//s.push("Ϭ����");
		//s.push("aaa");
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
