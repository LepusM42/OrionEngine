/******************************************************************************!
* \file Betel.hpp
* \author Lepus
* \brief The Betelgeuse Memory Manager (hereafter called Betel) is a custom
*  memory management system for C++ applications.
*******************************************************************************/
#pragma once
namespace Betel
{
	/**********************************************************************!
	* \class
	* \brief
	***********************************************************************/
	class Block
	{
	public:
		//! Does nothing.
		Block(char* address, unsigned size);
		//! Does nothing.
		void Split(unsigned size);
		//! Does nothing.
		Block* Next();
		//! Does nothing.
		char* Address();
		//! Does nothing.
		void SetNext(Block* block);
		//! Does nothing.
		void SetPrevious(Block* block);
		//! Does nothing.
		void Cut();
	private:
		//! Does nothing.
		Block* m_next{ nullptr };
		//! Does nothing.
		Block* m_previous{ nullptr };
		//! Does nothing.
		char* m_address{ nullptr };
		//! Does nothing.
		unsigned m_size{ 0 };
	};

	/**********************************************************************!
	* \class
	* \brief
	***********************************************************************/
	class Page
	{
	public:
		//! Does nothing.
		Page(unsigned max, unsigned blockSize);
		//! Does nothing.
		~Page();
		//! Does nothing.
		void* Allocate(unsigned size);
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
		char* m_rawMemory{ nullptr };
	};

	/**********************************************************************!
	* \class
	* \brief
	***********************************************************************/
	class Allocator
	{
	public:
		//! Does nothing.
		Allocator(unsigned max, unsigned min = 8);
		//! Does nothing.
		void* Allocate(unsigned size);
		//! Does nothing.
		void Deallocate(void* address);
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

	Allocator& GetAllocator();

	template <typename ObjectType>
	ObjectType* Allocate(unsigned count = 1)
	{
		return static_cast<ObjectType*>(GetAllocator().Allocate(count));
	}

	void Deallocate(void* address);
}