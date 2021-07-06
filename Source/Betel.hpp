/*!*****************************************************************************
* \file Betel.hpp
* \author Lepus
* \mainpage Welcome to the Betelgeuse Memory Manager Doxygen page!
*  The Betelgeuse Memory Manager (hereafter called Betel) is a custom
*  memory management system for C++ applications. It uses a singly-linked list
*  of pages, each used for allocating chunks of graduating size (by a factor of
*  2 each time). Each page uses two separate lists to keep track of allocated/
*  unallocated blocks of memory, making allocation and deallocation fairly quick
*  processes, each being roughly O(N) in complexity.
*  The following functions are available to the client:
*  - Initialize
*  - Balloc
*  - Allocate
*  - Deallocate
*  - Display
*  Credit to https://en.cppreference.com/w/cpp/language/new for information on
*  placement new.
*******************************************************************************/
#pragma once
//! \namespace Betel Contains all Betel functions and classes
namespace Betel
{
	//! Set Betel's maximum and minimum Page size, as well as how much larger
	//! sequential Pages are.
	void Initialize(unsigned max, unsigned min = 8, unsigned growth = 2);

	//! Malloc-style allocation for a chunk of memory.
	void* Balloc(unsigned size);

	//! Allocate memory for one or more objects of a specified type.
	template <typename ObjectType>
	ObjectType* Allocate(unsigned count = 1)
	{
		unsigned size = count * static_cast<unsigned>(sizeof(ObjectType));
		ObjectType* obj = static_cast<ObjectType*>(Balloc(size));
		if (obj)
		{
			return new(obj)ObjectType();
		}
		return nullptr;
	}

	//! Give allocated memory back to the system.
	void Deallocate(void* address);

	//! Show all allocated and unallocated Blocks in all Pages.
	void Display();
}