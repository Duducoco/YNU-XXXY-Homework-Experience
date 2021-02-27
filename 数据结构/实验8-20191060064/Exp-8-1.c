#include<stdio.h>  
#include <string.h>
int get_mid( char b[], int left, int right )
{
	int pivot = b[left];
	//b[left]的值由pivot保存，则b[left]可以作为一个空位置供插入
	while( left < right )
	{
		while( b[right] >= pivot && left < right )
		{
			right--;
		}
		b[left] = b[right];
		while( b[left] <= pivot && left < right )
		{
			left++;
		}
		b[right] = b[left];
	}
	b[left] = pivot;
	return left;
}

void QuickSort( char b[], int left, int right )
{
	if( left < right )
	{
		int mid = get_mid( b, left, right );
		QuickSort( b, left, mid-1 );
		QuickSort( b, mid+1, right );
	}
}

int main()
{
	char a[1024];
	printf("输入一串字符\n");
	gets(a);
	int n = strlen(a);

	QuickSort( a, 0, n-1 );//快速排序
	for( int i = 0; i< n; i++)
	{
		printf("%c ",a[i]);
	}
	return 0;
}

