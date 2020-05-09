#include <iostream>
using namespace std;

/*��������*/
/**
 *���������㷨һ������������㷨�������˼����� ���� ������ģ�

��1�� ѡ��һ����׼����

��2�� �����������д��ڻ�׼�������ݷ�Ϊһ����������С�ڵ��ڻ�׼�������ݷ�Ϊһ����

��3�� �ݹ飬�����������ظ�(1)(2)��ֱ��ÿ������ֻ��һ������
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
	int pivot = arr[high];    // ѡ���׼��Ϊ���һ��Ԫ��
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
	cout<<"���������:"<<endl;
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
