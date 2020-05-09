#include <iostream>
using namespace std;

/*快速排序*/
/**
 *快速排序算法一种最常见的排序算法，其核心思想就是 分治 ，具体的：

（1） 选定一个基准数；

（2） 分区，将所有大于基准数的数据分为一区，将所有小于等于基准数的数据分为一区；

（3） 递归，对上述分区重复(1)(2)，直到每个分区只有一个数。
 * **/

void swap(int *p,int *q  )
{
	int temp;
	temp = *p;
	*p = *q;
	*q = temp;
}

int postion(int arr[],int low,int high)
{
	int i = low;
	int pivot = arr[high];    // 选择基准数为最后一个元素
	int j;
	for(j=low;j<high;j++)
	{
		if(arr[j]<=arr[high]) 
		{
			swap(&arr[j],&arr[i]);
			i++;
		}
	
	}
	swap(&arr[i],&arr[high]);
	return i;
}


void quickSort(int arr[],int low, int high)
{

	if(low < high)
	{
		int i = postion(arr,low,high);
		quickSort(arr,low,i-1);
		quickSort(arr,i+1,high);
	}
}


void printfSort(int arr[],int length)
{
	cout<<"快速排序后:"<<endl;
	for (int i=0;i<length;i++)
		cout<<arr[i]<<" ";
	cout<<endl;
}

int main()
{
	int arr[] = {12,1,23,4,10,7,9,8};

	quickSort(arr,0,7);

	printfSort(arr,8);

	return 0;
}
