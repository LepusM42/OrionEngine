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
	/**********************************************************************!
	* \class Block
	* \brief Wrapper class around an address that points somewhere within a
	*  chunk of preallocated raw memory.
	***********************************************************************/
	class Block
	{
	public:
		//! Block constructor.
		Block(char* address, unsigned size);
		//! Split a block into two smaller blocks during partitioning.
		void Split(unsigned size);
		//! Access the next block in a list.
		Block* Next();
		//! Access the address that this block will give to the user after
		//! partitioning.
		char* Address();
		//! Place a new block after this one in a list.
		void SetNext(Block* block);
		//! Place a new block before this one in a list.
		void SetPrevious(Block* block);
		//! Remove this block from the middle of a list.
		void Cut();
		//! Print a visual representation of a block of memory.
		void Display();
	private:
		//! The next block in a list.
		Block* m_next{ nullptr };
		//! The previous block in a list.
		Block* m_previous{ nullptr };
		//! Pointer to an address within a chunk of raw memory preallocated by
		//! this block's page.
		char* m_address{ nullptr };
		//! Amount of space within a preallocated chunk of raw memory that an
		//! object allocated using this block may occupy without corruption.
		unsigned m_size{ 0 };
	};

	/**********************************************************************!
	* \class Page
	* \brief A structure representing a preallocated chunk of raw memory, which
	*  it partitions and gives to the user upon request. To do this it uses two
	*  doubly linked lists of Blocks (free and allocated memory). Each page can
	*  partition blocks of memory of a certain predetermined size, up to the
	*  size of the chunk of memory allocated upon its creation.
	***********************************************************************/
	class Page
	{
	public:
		//! Page constructor.
		Page(unsigned max, unsigned blockSize, unsigned growthFactor);
		//! Page destructor.
		~Page();
		//! Does nothing.
		void* Allocate();
		//! Does nothing.
		void Deallocate(void* address);
		//! Does nothing.
		Page* Next();
		//! Does nothing.
		bool Invalid(unsigned size);
		//! Does nothing.
		bool Contains(void* address);
		//! Does nothing.
		void AddPage();
		//! Show all allocated/unallocated blocks on this page.
		void Display();
	private:
		//! Does nothing.
		void AdvanceList(Block*& blockList);
		//! Does nothing.
		void AddToList(Block*& blockList, Block* block);
		//! Does nothing.
		Block* BlockContaining(void* address);
		//! Does nothing.
		void DestroyList(Block*& blockList);
		//! Does nothing.
		void ListDump(Block*& blockList, const char* msg);
		//! Does nothing.
		Page* m_next{ nullptr };
		//! Does nothing.
		Block* m_freeList{ nullptr };
		//! Does nothing.
		Block* m_usedList{ nullptr };
		//! Does nothing.
		unsigned m_blockSize{ 0 };
		//! Does nothing.
		unsigned m_pageSize{ 0 };
		//! Does nothing.
		unsigned m_growthFactor{ 2 };
		//! Does nothing.
		char* m_rawMemory{ nullptr };
	};

	/**********************************************************************!
	* \class Allocator
	* \brief Holds a singly linked list of Pages, each able to partition blocks
	*  twice as large as the previous page is able to. The maximum amount of
	*  memory each page can partition in total is specified during construction.
	*  The minimum amount of memory a page can partition at once be set during
	*  construction as well, though specifying this is optional.
	***********************************************************************/
	class Allocator
	{
	public:
		//! Does nothing.
		void Initialize(unsigned max, unsigned min = 8, unsigned factor = 2);
		//! Does nothing.
		void* Allocate(unsigned size);
		//! Does nothing.
		void Deallocate(void* address);
		//! Display the current state of all pages.
		void Display();
		//! Does nothing.
		~Allocator();
	private:
		//! Does nothing.
		Page* FirstAvailablePage(unsigned size);
		//! Does nothing.
		Page* PageContaining(void* address);
		//! Does nothing.
		void DestroyPages();
		//! Does nothing.
		Page* m_pageList{ nullptr };
		//! Does nothing.
		unsigned m_maxSize{ 0 };
		//! Does nothing.
		unsigned m_minSize{ 0 };
	};

	//! Set Betel's maximum and minimum page size.
	void Initialize(unsigned max, unsigned min = 8, unsigned factor = 2);

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

	//! Show all allocated and unallocated blocks in all pages.
	void Display();
}