#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int BinarySearch( char input[], int n, char key );
int main()
{
	int n;
	char input[1024], key;
	printf("请输入一段非递减有序序列\n");
	gets(input);
	n = strlen(input);
	printf("请输入要查找的字符\n");
	scanf("%c",&key);
	if( BinarySearch( input, n, key) )
	{
		printf("找到该字符\n");
	}
	else
	{
		printf("未找到该字符\n");
	}
	return 0;
}
int BinarySearch( char input[], int n, char key )
{
	int low, high, mid;
	low = 0;
	high = n-1;
	while( high >= low )
	{
		int mid = (low + high)/2;
		if( key == input[mid] )
		{
			return 1;
		}
		else if( key > input[mid] )
		{
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
		}
	}
	return 0;
}