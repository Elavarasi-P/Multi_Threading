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
	void setValues(int varX,int varY)
	{
		input = varX;
		*output = varY;
	}
	~context()
	{
		delete output;
		cout << "Destructor executed"<<endl;
	}
};

void evenSum(void*  param)
{
	cout << "\nExecuting Even Thread...";
	struct context* cont = reinterpret_cast<struct context*>(param);
	if (cont != NULL) {
		int sum = 0;
		for (int i = 0; i < cont->input; i += 2)
			sum += i;
		cont->setValues(cont->input, sum);
	}
	else
	{
		cout << "Invalid Param passed" << endl;
	}
}

void oddSum(void* param)
{
	cout << "\nExecuting Odd Thread...";
	//context svarC = *(struct context*)param;
	struct context* cont = reinterpret_cast<struct context*>(param);
	if (cont != NULL) 
	{
		int sum = 0;
		for (int i = 1; i < cont->input; i += 2)
			sum += i;
		cont->setValues(cont->input, sum);
	}
	//*cpy = svarC;
	else
	{
	cout << "Invalid Param passed" << endl;
	}
}
int main()
{
	//initialize and check for errors

	HANDLE handleEven =NULL;
	HANDLE handleOdd=NULL;
	DWORD dwEven=0,dwOdd=0;
	int result = 0;
	context varContA;
	varContA.setValues(5, 0);
	context varContB=varContA;
	
	void* vptr = reinterpret_cast<void*>(&varContA);
	void* vptr1 = reinterpret_cast<void*>(&varContB);
	
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
	varContA.display();
	cout << "\nOdd Sum:" <<endl;
	varContB.display();

	return result;
}