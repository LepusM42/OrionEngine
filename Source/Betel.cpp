/******************************************************************************!
* \file Betel.cpp
* \author Lepus
* \brief The Betelgeuse Memory Manager (hereafter called Betel) is a custom
*  memory management system for C++ applications. It uses a singly-linked list
*  of pages, each used for allocating chunks of graduating size. Each page uses
*  two separate lists to keep track of allocated/unallocated blocks of memory,
*  making allocation and deallocation fairly quick processes, each being roughly
*  O(N) in complexity.
*******************************************************************************/
#include "Betel.hpp"

namespace Betel
{
	static BetelInterior::Allocator Betelgeuse(4096);
	void* Allocate(unsigned count)
	{
		return static_cast<void*>(Betelgeuse.Allocate(count));
	}
	void Deallocate(void* address)
	{
		Betelgeuse.Deallocate(address);
	}
}

namespace BetelInterior
{
	Block::Block(char* address, unsigned size) :
		m_address{ address }
		, m_size{ size }
	{

	}

	/**************************************************************************!
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	void Block::Split(unsigned size)
	{
		Block* block = nullptr;
		if (m_size >= size)
		{
			block = new Block(m_address + size, m_size - size);
			m_size = size;
		}
		SetNext(block);
	}

	Block* Block::Next()
	{
		return m_next;
	}

	char* Block::Address()
	{
		return m_address;
	}

	void Block::SetNext(Block* block)
	{
		m_next = block;
		if (block) block->m_previous = this;
	}

	void Block::SetPrevious(Block* block)
	{
		m_previous = block;
		if (block) block->m_next = this;
	}

	void Block::Cut()
	{
		if (m_previous) m_previous->SetNext(m_next);
		if (m_next) m_next->SetPrevious(m_previous);
	}

	Page::Page(unsigned max, unsigned blockSize) :
		m_blockSize{ blockSize }
		, m_pageSize{ max }
	{
		m_rawMemory = new char[max];
		Block* block = new Block(m_rawMemory, max);
		AddToList(m_freeList, block);
	}

	void Page::DestroyList(Block*& blockList)
	{
		while (blockList)
		{
			Block* toDestroy = blockList;
			blockList = blockList->Next();
			delete toDestroy;
		}
	}

	void Page::AdvanceList(Block*& blockList)
	{
		blockList = blockList->Next();
		if (blockList) blockList->SetPrevious(nullptr);
	}

	bool Page::Invalid(unsigned size)
	{
		return m_blockSize < size || m_freeList == nullptr;
	}

	Page* Page::Next()
	{
		return m_next;
	}

	bool Page::Contains(void* address)
	{
		if (address < m_rawMemory)
			return false;
		else if (address > m_rawMemory + m_pageSize)
			return false;
		else
			return true;
	}

	Block* Page::BlockContaining(void* address)
	{
		Block* currentBlock = m_usedList;
		while (currentBlock && currentBlock->Address() != address)
		{
			currentBlock = currentBlock->Next();
		}
		return currentBlock;
	}

	void Page::AddToList(Block*& blockList, Block* block)
	{
		block->SetNext(blockList);
		blockList = block;
	}

	void Page::Deallocate(void* address)
	{
		if (Block* block = BlockContaining(address))
		{
			if (block == m_usedList) AdvanceList(m_usedList);
			else block->Cut();
			AddToList(m_freeList, block);
		}
	}

	void* Page::Allocate(unsigned size)
	{
		if (Block* currentBlock = m_freeList)
		{
			currentBlock->Split(m_blockSize);
			AdvanceList(m_freeList);
			AddToList(m_usedList, currentBlock);
			return currentBlock->Address();
		}
		return nullptr;
	}

	Page::~Page()
	{
		DestroyList(m_freeList);
		DestroyList(m_usedList);
		delete[] m_rawMemory;
	}

	Allocator::Allocator(unsigned max, unsigned min) :
		m_maxSize{ max }
		, m_minSize{ min }
	{
		m_pageList = new Page(max, min);
	}

	void* Allocator::Allocate(unsigned size)
	{
		if (Page* currentPage = FirstAvailablePage(size))
		{
			return currentPage->Allocate(size);
		}
		return nullptr;
	}

	void Allocator::Deallocate(void* address)
	{
		if (Page* currentPage = PageContaining(address))
		{
			currentPage->Deallocate(address);
		}
	}

	Page* Allocator::FirstAvailablePage(unsigned size)
	{
		Page* currentPage = m_pageList;

		while (currentPage->Next())
		{
			if (currentPage->Invalid(size) == false)
			{
				return currentPage;
			}
			currentPage = currentPage->Next();
		}

		while (currentPage && currentPage->Invalid(size))
		{
			currentPage->AddPage();
			currentPage = currentPage->Next();
		}

		return currentPage;
	}

	Page* Allocator::PageContaining(void* address)
	{
		Page* currentPage = m_pageList;
		while (currentPage && currentPage->Contains(address) == false)
		{
			currentPage = currentPage->Next();
		}
		return currentPage;
	}

	//! Does nothing.
	void Page::AddPage()
	{
		if (m_blockSize <= m_pageSize)
		{
			Page* nextPage = m_next;
			m_next = new Page(m_pageSize, m_blockSize * 2);
			m_next->m_next = nextPage;
		}
	}

	void Allocator::DestroyPages()
	{
		while (m_pageList)
		{
			Page* toDestroy = m_pageList;
			m_pageList = m_pageList->Next();
			delete toDestroy;
		}
	}

	Allocator::~Allocator()
	{
		DestroyPages();
	}
}