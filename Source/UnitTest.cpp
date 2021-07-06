#include "UnitTest.h"
#include "Orion.hpp"
#include <time.h>
#include <iostream>
#define size 1000
using namespace Orion;
struct Foo
{
	Foo()
	{
		//std::cout << ".";
	}
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
int TestBetel()
{
	Foo* fooArray1[size];
	for (int i = 0; i < size; ++i)
	{
		fooArray1[i] = Betel::Allocate<Foo>(size);
		if (!fooArray1[i]) return 1;
	}
	Betel::Display();
	for (int i = 0; i < size; ++i)
	{
		Betel::Deallocate(fooArray1[i]);
	}
	return 0;
}
int TestNew()
{
	Foo* fooArray2[size];
	for (int i = 0; i < size; ++i)
	{
		fooArray2[i] = new Foo[size];
		if (!fooArray2[i]) return 1;
	}
	for (int i = 0; i < size; ++i)
	{
		delete[] fooArray2[i];
	}
	return 0;
}
int TestComponents()
{
	Entity e;
	Transform* t = Betel::Allocate<Orion::Transform>();
	e.Add(t);
	Transform* trans = e.Get<Orion::Transform>();
	if (!trans) return 1;
	trans->t = 6;
	std::cout << "-" << trans->t << "-" << std::endl;
	return 0;
}
int RunUnitTests()
{
	Stopwatch s;
	Betel::Initialize(1000000);

	//Betel's turn
	s.Start();
	if(TestBetel()) return 1;
	std::cout << "Betel: " << s.Stop() << " ms" << std::endl;

	//System's turn
	s.Start();
	if (TestNew()) return 1;
	std::cout << "Keyword new: " << s.Stop() << " ms" << std::endl;

	//Make sure the component system is working
	if (TestComponents()) return 1;

	return 0;
}