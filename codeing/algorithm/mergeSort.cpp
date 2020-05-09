#include<stdio.h>  
#include<stdlib.h>  
#define INFINITE 1000
/****************************
 归并排序又是另一类排序算法，它是一种基于“分治”策略的一种算法
。归并排序算法是典型的分治算法，对于规模较大的问题，可以分解成若干容易求解的简单的问题，
最后把解合并构成初始问题的解。详细的排序过程可以参考《数据结构》或者《算法导论》。

****************************/

//对两个序列进行合并,数组从mid分开
////对a[start...mid]和a[start+1...end]进行合并 

void merge(int *a,int start,int mid,int end)  
{  
    	int i,j,k; 
	//申请辅助数组
	
	int *array1=(int *)malloc(sizeof(int)*(mid-start+2)); 
	int *array2=(int *)malloc(sizeof(int)*(end-mid+1));

	//把a从mid分开分别赋值给数组 
	for(i=0;i<mid-start+1;i++)
		*(array1+i)=a[start+i];

	*(array1+i)=INFINITE;//作为哨兵
	for(i=0;i<end-mid;i++) 
		*(array2+i)=a[i+mid+1];
	*(array2+i)=INFINITE;

	//有序的归并到数组a中 
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


//归并排序
void mergeSort(int *a,int start,int end)
{
	int mid=(start+end)/2;
	if(start<end){
		//分解
		mergeSort(a,start,mid);
		mergeSort(a,mid+1,end);

		//合并
		merge(a,start,mid,end);
	}
}


int  main()
{
	int i; 
	int a[7]={0,3,5,8,9,1,2};//不考虑a[0] 

	mergeSort(a,1,6);
	for(i=1;i<=6;i++)  
        	printf("%-4d",a[i]);  
    	printf("\n");
	
	return 0;
}
