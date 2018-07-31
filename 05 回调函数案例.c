#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//1、提供一个函数，可以打印任意类型的数组
void printAllArray(  void * arr  , int eleSize, int len , void(*myFunc)(void *) )
{
	char * p = arr;
	for (int i = 0; i < len; i++)
	{
		char * eleAddr = p + i * eleSize; //计算每个元素首地址
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
	printf("姓名： %s 年龄： %d\n", p->name, p->age);
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



// 参数1   数组首地址   参数2  每个元素占的内存空间   参数3  元素个数  参数4  查找的元素的地址 参数5  回调函数
int myFindPerson(void * arr, int eleSize, int len , void * data  ,  int (*myCompare)( void *  , void *  )  )
{
	char * p = arr;
	for (int i = 0; i < len;i++)
	{
		char * eleAddr = p + i * eleSize; //获取每个元素的首地址

		//if ( eleAddr 和  data 的元素 相等  )
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
	//查找数组中的元素，如果查找到返回1  ，找不到返回0 
	int ret = myFindPerson(pArray, sizeof(struct Person), len, &p, myComparePerson);

	if (ret)
	{
		printf("找到了元素\n");
	}
	else
	{
		printf("未找到元素\n");
	}
}


int main(){

	//test01();
	//test02();
	test03();
	system("pause");
	return EXIT_SUCCESS;
}