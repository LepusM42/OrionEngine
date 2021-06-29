/******************************************************************************!
* \file Betel.hpp
* \author Lepus
* \brief The Betelgeuse Memory Manager (hereafter called Betel) is a custom
*  memory management system for C++ applications. It uses a singly-linked list
*  of pages, each used for allocating chunks of graduating size (by a factor of
*  2 each time). Each page uses two separate lists to keep track of allocated/
*  unallocated blocks of memory, making allocation and deallocation fairly quick
*  processes, each being roughly O(N) in complexity.
*******************************************************************************/
#pragma once
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
		return static_cast<ObjectType*>(Balloc(size));
	}

	//! Give allocated memory back to the system.
	void Deallocate(void* address);

	//! Show all allocated and unallocated Blocks in all Pages.
	void Display();
}