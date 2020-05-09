#include<stdio.h>  
#include<stdlib.h>  
#define INFINITE 1000
/****************************
 �鲢����������һ�������㷨������һ�ֻ��ڡ����Ρ����Ե�һ���㷨
���鲢�����㷨�ǵ��͵ķ����㷨�����ڹ�ģ�ϴ�����⣬���Էֽ�������������ļ򵥵����⣬
���ѽ�ϲ����ɳ�ʼ����Ľ⡣��ϸ��������̿��Բο������ݽṹ�����ߡ��㷨���ۡ���

****************************/

//���������н��кϲ�,�����mid�ֿ�
////��a[start...mid]��a[start+1...end]���кϲ� 

void merge(int *a,int start,int mid,int end)  
{  
    	int i,j,k; 
	//���븨������
	
	int *array1=(int *)malloc(sizeof(int)*(mid-start+2)); 
	int *array2=(int *)malloc(sizeof(int)*(end-mid+1));

	//��a��mid�ֿ��ֱ�ֵ������ 
	for(i=0;i<mid-start+1;i++)
		*(array1+i)=a[start+i];

	*(array1+i)=INFINITE;//��Ϊ�ڱ�
	for(i=0;i<end-mid;i++) 
		*(array2+i)=a[i+mid+1];
	*(array2+i)=INFINITE;

	//����Ĺ鲢������a�� 
	i=j=0;

	for(k=start;k<=end;k++){ 
		if(*(array1+i) > *(array2+j)){
			a[k]=*(array2+j);
			j++;
		}
		else{
			a[k]=*(array1+i);
			i++;
		}

	}

	free(array1);
	free(array2);
}


//�鲢����
void mergeSort(int *a,int start,int end)
{
	int mid=(start+end)/2;
	if(start<end){
		//�ֽ�
		mergeSort(a,start,mid);
		mergeSort(a,mid+1,end);

		//�ϲ�
		merge(a,start,mid,end);
	}
}


int  main()
{
	int i; 
	int a[7]={0,3,5,8,9,1,2};//������a[0] 

	mergeSort(a,1,6);
	for(i=1;i<=6;i++)  
        	printf("%-4d",a[i]);  
    	printf("\n");
	
	return 0;
}
