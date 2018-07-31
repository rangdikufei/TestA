#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//1���ṩһ�����������Դ�ӡ�������͵�����
void printAllArray(  void * arr  , int eleSize, int len , void(*myFunc)(void *) )
{
	char * p = arr;
	for (int i = 0; i < len; i++)
	{
		char * eleAddr = p + i * eleSize; //����ÿ��Ԫ���׵�ַ
		//printf("%d\n", *(int*)eleAddr);

		myFunc(eleAddr);

	}
}




void myPrintInt(void * data)
{
	int * num = data;
	printf("%d\n", *num);
}

void test01()
{
	int arr[6] = { 1,2, 3, 4, 5, 6 };
	int len = sizeof(arr) / sizeof(int);
	printAllArray(arr, sizeof(int), len, myPrintInt);
}


struct Person
{
	char name[64];
	int age;
};

void myPrintPerson(void * data)
{
	struct Person * p = data;
	printf("������ %s ���䣺 %d\n", p->name, p->age);
}
void test02()
{
	struct Person pArray[] =
	{
		{ "aaa", 10 },
		{ "bbb", 20 },
		{ "ccc", 30 },
		{ "ddd", 40 },
	};
	int len = sizeof(pArray) / sizeof(struct Person);
	printAllArray(pArray, sizeof(struct Person), len, myPrintPerson);
}



// ����1   �����׵�ַ   ����2  ÿ��Ԫ��ռ���ڴ�ռ�   ����3  Ԫ�ظ���  ����4  ���ҵ�Ԫ�صĵ�ַ ����5  �ص�����
int myFindPerson(void * arr, int eleSize, int len , void * data  ,  int (*myCompare)( void *  , void *  )  )
{
	char * p = arr;
	for (int i = 0; i < len;i++)
	{
		char * eleAddr = p + i * eleSize; //��ȡÿ��Ԫ�ص��׵�ַ

		//if ( eleAddr ��  data ��Ԫ�� ���  )
		if ( myCompare(eleAddr , data ))
		{
			return 1;
		}
	}
	return 0;
}


int  myComparePerson(void * data1, void * data2)
{
	struct Person * p1 = data1;
	struct Person * p2 = data2;

	if ( strcmp(  p1->name,  p2->name ) == 0 && p1->age == p2->age)
	{
		return 1;
	}
	return 0;

}

void test03()
{
	struct Person pArray[] =
	{
		{ "aaa", 10 },
		{ "bbb", 20 },
		{ "ccc", 30 },
		{ "ddd", 40 },
	};

	struct Person p = { "ccc", 30 };
	int len = sizeof(pArray) / sizeof(struct Person);
	//���������е�Ԫ�أ�������ҵ�����1  ���Ҳ�������0 
	int ret = myFindPerson(pArray, sizeof(struct Person), len, &p, myComparePerson);

	if (ret)
	{
		printf("�ҵ���Ԫ��\n");
	}
	else
	{
		printf("δ�ҵ�Ԫ��\n");
	}
}


int main(){

	//test01();
	//test02();
	test03();
	system("pause");
	return EXIT_SUCCESS;
}