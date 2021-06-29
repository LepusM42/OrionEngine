/******************************************************************************!
* \file Betel.cpp
* \author Lepus
* \brief The Betelgeuse Memory Manager (hereafter called Betel) is a custom
*  memory management system for C++ applications. It uses a singly-linked list
*  of pages, each used for allocating chunks of graduating size (by a factor of
*  2 each time). Each page uses two separate lists to keep track of allocated/
*  unallocated blocks of memory, making allocation and deallocation fairly quick
*  processes, each being roughly O(N) in complexity.
*******************************************************************************/
#include "Betel.hpp"
#include <iostream>
namespace Betel
{
	//The internal allocator used to manage allocation and deallocation.
	static Betel::Allocator Betelgeuse;

	/**************************************************************************!
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
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
		if (m_size > size)
		{
			block = new Block(m_address + size, m_size - size);
			m_size = size;
			SetNext(block);
		}
	}

	/**************************************************************************!
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	Block* Block::Next()
	{
		return m_next;
	}

	/**************************************************************************!
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	char* Block::Address()
	{
		return m_address;
	}

	/**************************************************************************!
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	void Block::SetNext(Block* block)
	{
		m_next = block;
		if (block) block->m_previous = this;
	}

	/**************************************************************************!
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	void Block::SetPrevious(Block* block)
	{
		m_previous = block;
		if (block) block->m_next = this;
	}

	/**************************************************************************!
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	void Block::Cut()
	{
		if (m_previous) m_previous->SetNext(m_next);
		if (m_next) m_next->SetPrevious(m_previous);
	}

	/**************************************************************************!
	* \fn
	* \brief Print a visual representation of a block of memory.
	* \param
	* \return
	***************************************************************************/
	void Block::Display()
	{
		std::cout << "[" << m_size << "]->";
	}

	/**************************************************************************!
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	Page::Page(unsigned max, unsigned blockSize, unsigned growthFactor) :
		m_blockSize{ blockSize }
		, m_pageSize{ max }
		, m_growthFactor{ growthFactor }
	{
		m_rawMemory = new char[max];
		Block* block = new Block(m_rawMemory, max);
		AddToList(m_freeList, block);
	}

	/**************************************************************************!
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	Page::~Page()
	{
		DestroyList(m_freeList);
		DestroyList(m_usedList);
		delete[] m_rawMemory;
	}

	/**************************************************************************!
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	void* Page::Allocate()
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

	/**************************************************************************!
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	void Page::Deallocate(void* address)
	{
		if (Block* block = BlockContaining(address))
		{
			if (block == m_usedList) AdvanceList(m_usedList);
			else block->Cut();
			AddToList(m_freeList, block);
		}
	}

	/**************************************************************************!
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	Page* Page::Next()
	{
		return m_next;
	}

	/**************************************************************************!
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	bool Page::Invalid(unsigned size)
	{
		return m_blockSize < size || m_freeList == nullptr;
	}

	/**************************************************************************!
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	bool Page::Contains(void* address)
	{
		if (address < m_rawMemory)
			return false;
		else if (address > m_rawMemory + m_pageSize)
			return false;
		else
			return true;
	}

	/**************************************************************************!
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	void Page::AddPage()
	{
		if (m_blockSize <= m_pageSize)
		{
			Page* nextPage = m_next;
			m_next = new Page(m_pageSize, m_blockSize * m_growthFactor, m_growthFactor);
			m_next->m_next = nextPage;
		}
	}


	void Page::Display()
	{
		ListDump(m_freeList, "FREE  : ");
		ListDump(m_usedList, "IN USE: ");
		std::cout << std::endl;
	}

	/**************************************************************************!
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	void Page::AdvanceList(Block*& blockList)
	{
		blockList = blockList->Next();
		if (blockList) blockList->SetPrevious(nullptr);
	}

	/**************************************************************************!
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	void Page::AddToList(Block*& blockList, Block* block)
	{
		block->SetNext(blockList);
		blockList = block;
	}

	/**************************************************************************!
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	Block* Page::BlockContaining(void* address)
	{
		Block* currentBlock = m_usedList;
		while (currentBlock && currentBlock->Address() != address)
		{
			currentBlock = currentBlock->Next();
		}
		return currentBlock;
	}

	/**************************************************************************!
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	void Page::DestroyList(Block*& blockList)
	{
		while (blockList)
		{
			Block* toDestroy = blockList;
			blockList = blockList->Next();
			delete toDestroy;
		}
	}

	/**************************************************************************!
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	void Page::ListDump(Block*& blockList, const char* msg)
	{
		std::cout << msg;
		Block* currentBlock = blockList;
		while (currentBlock)
		{
			currentBlock->Display();
			currentBlock = currentBlock->Next();
		}
		std::cout << std::endl;
	}

	/**************************************************************************!
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	void Allocator::Initialize(unsigned max, unsigned min, unsigned factor)
	{
		m_maxSize = max;
		m_minSize = min;
		m_pageList = new Page(max, min, factor);
	}

	/**************************************************************************!
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	void* Allocator::Allocate(unsigned size)
	{
		if (Page* currentPage = FirstAvailablePage(size))
		{
			return currentPage->Allocate();
		}
		return nullptr;
	}

	/**************************************************************************!
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	void Allocator::Deallocate(void* address)
	{
		if (Page* currentPage = PageContaining(address))
		{
			currentPage->Deallocate(address);
		}
	}

	void Allocator::Display()
	{
		std::cout << "---------------------------------------------------------------------------------" << std::endl;
		Page* currentPage = m_pageList;
		int pageCount = 1;
		while (currentPage)
		{
			std::cout << "PAGE [" << pageCount++ << "]:" << std::endl;
			currentPage->Display();
			currentPage = currentPage->Next();
		}
		std::cout << "---------------------------------------------------------------------------------" << std::endl;
	}

	/**************************************************************************!
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	Allocator::~Allocator()
	{
		DestroyPages();
	}

	/**************************************************************************!
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	Page* Allocator::FirstAvailablePage(unsigned size)
	{
		if (m_pageList == nullptr) Initialize(4096);

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

	/**************************************************************************!
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	Page* Allocator::PageContaining(void* address)
	{
		Page* currentPage = m_pageList;
		while (currentPage && currentPage->Contains(address) == false)
		{
			currentPage = currentPage->Next();
		}
		return currentPage;
	}

	/**************************************************************************!
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	void Allocator::DestroyPages()
	{
		while (m_pageList)
		{
			Page* toDestroy = m_pageList;
			m_pageList = m_pageList->Next();
			delete toDestroy;
			toDestroy = nullptr;
		}
	}

	/**************************************************************************!
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	void Initialize(unsigned max, unsigned min, unsigned factor)
	{
		Betelgeuse.Initialize(max, min, factor);
	}

	/**************************************************************************!
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	void* Balloc(unsigned size)
	{
		return Betelgeuse.Allocate(size);
	}

	/**************************************************************************!
	* \fn
	* \brief
	* \param
	* \return
	***************************************************************************/
	void Deallocate(void* address)
	{
		Betelgeuse.Deallocate(address);
	}
	
	void Display()
	{
		Betelgeuse.Display();
	}
}