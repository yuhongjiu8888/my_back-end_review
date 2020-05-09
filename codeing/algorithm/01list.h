#ifndef _LIST_H
#define _LIST_H
typedef int T;


class List{

struct Node{
        T data;
        Node* next;
        Node(const T& d=T()):data(d),next(0){}//���ʼ��
};

	Node* head;//ͷָ�룬��������ͷ����ַ
	int len;
public:
	List():head(NULL),len(0){}
	void push_front(const T& d);//ͷ��

	void push_back(const T& d);//β��

	int size() const;//�����С

	Node*& getptr(int pos);//����posλ��

	void insert(const T& d,int pos);//��posλ�ò�������

	void erase( int pos );//ɾ��posλ������

	void remove (const T& d);
	int find (const T& d) const;

	void set(int pos ,const T& d);//�޸�posλ������


	bool empty() const{return head==NULL;}
	T front() const{if(empty()) throw "��";return head->data;}
	T back() const;

	void travel() const;	

	void clear();
	~List();
		
};
#endif
