#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;


/****************
*算法名:二分查找(折半查找)
*使用规则:1.已经排好序的线性表2.找到中间mid结点，分成前后两个区间,如果待找到的关键字key<=mid,则去前半区间找，否则后半区间
*	3.重复第2步，直至找到关键字key,或者没找到返回
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
		mid = low+((high-low)/2);	//中间位置点

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
