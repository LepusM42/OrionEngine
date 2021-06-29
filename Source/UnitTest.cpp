#include "UnitTest.h"
#include "Betel.hpp"
#include <time.h>
#include <iostream>
#define nodecount 1000
#define sizeofnode 1000
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
int RunUnitTests()
{
	Stopwatch s;
	//Pages can allocate up to 100,000 bytes of data each
	Betel::Initialize(10000000);
	//Betel's turn
	s.Start();
	//Allocate 100,000 arrays
	Foo* fooArray1[nodecount];
	for (int i = 0; i < nodecount; ++i)
	{
		//Allocate an array of 1000 Foo structs (each 12 bytes)
		fooArray1[i] = Betel::Allocate<Foo>(sizeofnode);
		fooArray1[i]->a = i;
	}
	//Betel::Display();
	for (int i = 0; i < sizeofnode; ++i)
	{
		Betel::Deallocate(fooArray1[i]);
	}
	std::cout << "Betel: " << s.Stop() << " ms" << std::endl;
	//System's turn
	s.Start();
	//Allocate 100,000 arrays
	Foo* fooArray2[nodecount];
	for (int i = 0; i < nodecount; ++i)
	{
		//Allocate an array of 1000 Foo structs (each 12 bytes)
		fooArray2[i] = new Foo[sizeofnode];
		fooArray2[i]->a = i;
	}
	for (int i = 0; i < sizeofnode; ++i)
	{
		delete[] fooArray2[i];
	}
	std::cout << "Keyword new: " << s.Stop() << " ms" << std::endl;
	return 0;
}