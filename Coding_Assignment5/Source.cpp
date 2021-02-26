//CODING ASSIGNMENT 5
//MULTI-THREADING
//Given an integer n, Create two threads. One to add all the even numbers less than n and other to add all odd numbers less n.

#include<Windows.h>
#include<process.h>
#include<stdio.h>
#include<iostream>
using namespace std;

struct context
{
	int input;
	int *output;
	context()
	{
		input = 0;
		output = new int;
	}
	context(context& varA)
	{
		input = varA.input;
		output = new int;
		*output = (*varA.output);
	}
	void display()
	{
		cout << "Input:" << input << endl;
		cout << "Output:" << *output << endl;
	}
	void getValues(int varX,int varY)
	{
		input = varX;
		*output = varY;
	}
};

void evenSum(void*  param)
{
	cout << "\nExecuting Even Thread...";
	context svarC=* (struct context*)param;;
	struct context* cpy = reinterpret_cast<struct context*>(param);
	int sum = 0;
	for (int i = 0; i < svarC.input; i += 2)
		sum += i;
	svarC.getValues(svarC.input, sum);
	*cpy = svarC;
}

void oddSum(void* param)
{
	cout << "\nExecuting Odd Thread...";
	context svarC = *(struct context*)param;
	struct context* cpy = reinterpret_cast<struct context*>(param);
	int sum = 0;
	for (int i = 1; i < svarC.input; i += 2)
		sum += i;
	svarC.getValues(svarC.input, sum);
	*cpy = svarC;
}
int main()
{
	//initialize and check for errors

	HANDLE handleEven =NULL;
	HANDLE handleOdd=NULL;
	DWORD dwEven=0,dwOdd=0;
	int result = 0;
	context svarA;
	svarA.getValues(5, 0);
	context svarB=svarA;
	
	void* vptr = reinterpret_cast<void*>(&svarA);
	void* vptr1 = reinterpret_cast<void*>(&svarB);
	
	handleEven = (HANDLE)_beginthread(evenSum, 0,vptr);

	if (handleEven==NULL)
	{
		printf("Could not create a thread (%d).\n",GetLastError());
		result= 1;
	}
	
	handleOdd = (HANDLE)_beginthread(oddSum, 0, vptr1);
	if (handleOdd==NULL)
	{
		printf("Could not create a thread (%d).\n",GetLastError());
		result= 1;
	}
	
	if (!result)
	{
		dwEven = WaitForSingleObject(handleEven, INFINITE);

		switch (dwEven)
		{
		case WAIT_OBJECT_0:
			printf("\nEven Thread ended.\n");
			break;

		default:
			printf("WaitForSingleObject failed (%d)\n", GetLastError());
			result = 1;
		}
		dwOdd = WaitForSingleObject(handleOdd, INFINITE);
		switch (dwEven)
		{
		case WAIT_OBJECT_0:
			printf("Odd Thread ended.\n");
			break;

		default:
			printf("WaitForSingleObject failed (%d)\n", GetLastError());
			result = 1;
		}
	}
	cout << "\nEven Sum:" << endl;
	svarA.display();
	cout << "\nOdd Sum:" <<endl;
	svarB.display();

	return result;
}