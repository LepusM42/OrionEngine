#include "UnitTest.h"
int RunUnitTests()
{
	Foo* foo = static_cast<Foo*>(Betel::Allocate(sizeof(Foo)));
	Betel::Deallocate(foo);
	return 0;
}