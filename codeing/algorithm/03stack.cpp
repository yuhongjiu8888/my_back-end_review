#include <iostream>
#include <string>
#include "01list.h"
using namespace std;

typedef int T;

class Stack{
	List l;	//组合关系类
public:
	void push(const T& d) ;	//数据入栈成为栈顶
	T pop() ;	//栈顶数据出栈，下一个元素成为栈顶
	const T& top()const;	//取得栈顶数据
	bool empty() const{return l.empty();}	//是否空栈
	bool full() const{ return false;}	//是否已满
	void clear(){ l.clear() ;}		//栈清空
	int size() const{return l.size();}	//栈中数据个数
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
		cout<<"异常："<< e << endl;
	}

	while(!s.empty())
	{
		cout<<s.pop()<<endl;
	}

	return 0;
}
