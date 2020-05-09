#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;


/****************
*�㷨��:���ֲ���(�۰����)
*ʹ�ù���:1.�Ѿ��ź�������Ա�2.�ҵ��м�mid��㣬�ֳ�ǰ����������,������ҵ��Ĺؼ���key<=mid,��ȥǰ�������ң�����������
*	3.�ظ���2����ֱ���ҵ��ؼ���key,����û�ҵ�����
*
* ***************/

int SearchPosition(int arr[],int length ,int key)
{
	int low = 0;
	int high= length-1;
	int mid;

	if( arr[low] == key )
		return low;

	if( arr[high] == key )
		return high;

	while( low <= high )
	{
		mid = low+((high-low)/2);	//�м�λ�õ�

		if( arr[mid] == key )
			return mid;

		if( arr[mid] < key )
			low = mid+1 ;
		else
			high = mid-1;
	}

	if ( low > high )
	{
		return -1;	/*Not Found*/

	}


}

int main(int argc , char* argv[])
{
	if(argc !=2 )
	{
		cout<<"Please Input key?"<<endl;
		exit(0);
	}

	int arr[] = {1,2,3,4,5,6};

	int p = SearchPosition(arr , sizeof(arr),atoi(argv[1]));
	if ( p!=-1 )
		cout<<"Find key posision is ["<<p<<"]"<<endl;
	else
		cout<<"Not Found key in arr!"<< endl;
}
