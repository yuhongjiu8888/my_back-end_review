#include <iostream>
#include "01list.h"
using namespace std;

class Queue{
	List l;
public:
	Queue& push(const T& d){
		l.push_back(d);
		return *this;
	}

	T pop(){
		T t = front();
		l.erase(0);
		return t;
	}

	const T& front()const{return l.front();}
	const T& back()const{return l.back();}
	int size() const{ return l.size();}

	void clear(){ l.clear();}
	bool empty()const{return l.empty();}
	bool full()const{return false;}
};

int main()
{
	Queue q;
	q.push(1).push(2);
	q.push(3).push(4);
	q.push(5).push(6);
	while( !q.empty() )
	{
		cout<<q.pop()<<endl;
	}


	return 0;
}
