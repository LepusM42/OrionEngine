#include "UnitTest.h"
#include "Betel.hpp"
#include <time.h>
#include <iostream>
#define size 10000
struct Foo
{
	int a{ 0 }, b{ 0 }, c{ 0 }, d{ 0 };
};
struct Stopwatch
{
	void Start()
	{
		initialTime = clock();
	}
	int Stop()
	{
		clock_t currentTime = clock();
		clock_t elapsedTime = currentTime - initialTime;
		initialTime = 0;
		return elapsedTime;
	}
	clock_t initialTime{ 0 };
};
void TestBetel()
{
	Foo* fooArray1[size];
	for (int i = 0; i < size; ++i)
	{
		fooArray1[i] = Betel::Allocate<Foo>(size);
	}
	Betel::Display();
	for (int i = 0; i < size; ++i)
	{
		Betel::Deallocate(fooArray1[i]);
	}
}
void TestNew()
{
	Foo* fooArray2[size];
	for (int i = 0; i < size; ++i)
	{
		fooArray2[i] = new Foo[size];
	}
	for (int i = 0; i < size; ++i)
	{
		delete[] fooArray2[i];
	}
}
int RunUnitTests()
{
	Stopwatch s;
	Betel::Initialize(1000000);

	//Betel's turn
	s.Start();
	TestBetel();
	std::cout << "Betel: " << s.Stop() << " ms" << std::endl;

	//System's turn
	s.Start();
	TestNew();
	std::cout << "Keyword new: " << s.Stop() << " ms" << std::endl;

	return 0;
}