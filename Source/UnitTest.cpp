#include "UnitTest.h"
#include "Betel.hpp"
struct Foo
{
int a{ 0 }, b{ 0 }, c{ 0 };
};
int RunUnitTests()
{
	auto* foo = Betel::Allocate<Foo>();
	Betel::Deallocate(foo);
	return 0;
}