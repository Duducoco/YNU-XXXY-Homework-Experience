#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BitNode
{
	char data;
	struct BitNode *lchild;
	struct BitNode *rchild;
} BitNode;

BitNode *Creat_ProperBiTree(char *pre, char *post, int length, int *tag); //前序后序转中序
void InOrderTraverse(BitNode*T);

int main(void)
{
	int c;
	while(1)
	{
		printf("请开始选择：0、构造真二叉树，1、退出\n");
		scanf("%d", &c);
		fflush(stdin);
		switch(c)
		{
		case 0:
		{
			FILE *fp ;
			int tag = 0;//标记错误，0为无错误
			if((fp = fopen("proper-bitree.txt", "a")) == NULL)
			{
				printf("打开文件失败\n");
				exit(EXIT_FAILURE);
			}
			system("cls");
			char pre[1024];
			char post[1024];
			//文件写入前序序列
			printf("请输入前序输出序列(不要有空格)\n");
			gets(pre);
			fputs(pre, fp);
			fprintf(fp, "\n");
			//文件写入后序序列
			printf("请输入后序输出序列(不要有空格)\n");
			gets(post);
			fputs(post, fp);
			fprintf(fp, "\n");
			fclose(fp);
			int prelength = strlen(pre);
			int postlength = strlen(post);
			if(prelength != postlength || prelength % 2 == 0 || postlength % 2 == 0)
			{
				tag = 1;//长度不符合要求，设置错误
			}
			//开始构造真二叉树
			BitNode* T;
			T = Creat_ProperBiTree(pre, post, prelength, &tag);//tag指示是否出错

			if(tag == 0)
			{
				InOrderTraverse(T);
				if((fp = fopen("proper-bitree.txt", "a")) == NULL)
				{
					printf("打开文件失败\n");
					exit(EXIT_FAILURE);
				}
				fprintf(fp, "\n");//行末增加换行
				fclose(fp);
				printf("结果已写入文件\n");
			}
			else
			{
				if((fp = fopen("proper-bitree.txt", "a")) == NULL)
				{
					printf("打开文件失败\n");
					exit(EXIT_FAILURE);
				}
				fprintf(fp, "对不起，输入的序列无法构成真二叉树\n");
				fclose(fp);
				printf("结果已写入文件\n");
			}
			system("pause");
		}
		break;
		case 1:
		{
			return 0;
			break;
		}
		default:
			printf("输入错误，请重新输入\n");
			break;
		}
	}
	return 0;
}


void InOrderTraverse(BitNode*T)
{
	if(T)
	{
		InOrderTraverse(T->lchild);
		//在文件中写入中序遍历序列
		FILE *fp1;
		if((fp1 = fopen("proper-bitree.txt", "a")) == NULL)
		{
			printf("打开文件失败\n");
			exit(EXIT_FAILURE);
		}
		fputc(T->data, fp1);
		fclose(fp1);
		InOrderTraverse(T->rchild);
	}
}

BitNode *Creat_ProperBiTree(char *pre, char *post, int length, int *tag) //前序后序转中序
{
	if(length == 1)//有一个节点，必为根
	{
		BitNode* T = (BitNode*)malloc(sizeof(BitNode));
		if(pre[0] == post[0])//唯一的节点相同
		{
			T->data = pre[0];
			T->lchild = NULL;
			T->rchild = NULL;
			return T;
		}
		else//唯一的节点不相同，必错误
		{
			*tag = 1;
			return NULL;
		}
	}
	if(length % 2 == 0)//序列长度为偶数，无法构成真二叉树
	{
		*tag = 1;
		return NULL;
	}

	int i = 0;
	if(pre[0] != post[length - 1])//在前序和后序遍历序列中找到的根不一样
	{
		*tag = 1;//设置错误
		return NULL;
	}

	char Root = pre[0];//根
	char rightRoot = post[length - 2]; //右子树根
	while(pre[i] != rightRoot && i < length)
	{
		i++;//在前序遍历中找到右子树的根，从而分隔左右子树
	}
	if( i == length )
	{
		*tag = 1;//在前序序列没找到右子树的根，错误
		return NULL;
	}

	int leftlength = i - 1;//左子树节点个数
	int rightlength = length - i;//右子树节点个数

	BitNode * T = (BitNode*)malloc(sizeof(BitNode));
	T->data = Root;

	T->lchild = Creat_ProperBiTree(&pre[1], &post[0], leftlength,tag);
	T->rchild = Creat_ProperBiTree(&pre[i], &post[i - 1], rightlength,tag);
	return T;
}
