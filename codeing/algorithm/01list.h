#ifndef _LIST_H
#define _LIST_H
typedef int T;


class List{

struct Node{
        T data;
        Node* next;
        Node(const T& d=T()):data(d),next(0){}//零初始化
};

	Node* head;//头指针，用来保存头结点地址
	int len;
public:
	List():head(NULL),len(0){}
	void push_front(const T& d);//头插

	void push_back(const T& d);//尾插

	int size() const;//链表大小

	Node*& getptr(int pos);//查找pos位置

	void insert(const T& d,int pos);//在pos位置插入数据

	void erase( int pos );//删除pos位置数据

	void remove (const T& d);
	int find (const T& d) const;

	void set(int pos ,const T& d);//修改pos位置数据


	bool empty() const{return head==NULL;}
	T front() const{if(empty()) throw "空";return head->data;}
	T back() const;

	void travel() const;	

	void clear();
	~List();
		
};
#endif
