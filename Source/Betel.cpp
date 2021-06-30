/*!*****************************************************************************
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
#include <iostream>
//! If the client doesn't specify a max page size, this value will be used instead.
#define DEFAULT_PAGE_LIMIT 10000
// Betel class interfaces
namespace Betel
{
	/*!*************************************************************************
	* \class Block
	* \brief Wrapper class around an address that points somewhere within a
	*  chunk of preallocated raw memory.
	***************************************************************************/
	class Block
	{
	public:
		//! Block constructor.
		Block(char* address, unsigned size);
		//! Split a Block into two smaller Blocks during partitioning.
		void Split(unsigned size);
		//! Access the next Block in a list.
		Block* Next();
		//! Access the address that this Block will give to the user after
		//! partitioning.
		char* Address();
		//! Place a new Block after this one in a list.
		void SetNext(Block* block);
		//! Place a new Block before this one in a list.
		void SetPrevious(Block* block);
		//! Remove this Block from the middle of a list.
		void Cut();
		//! Print a visual representation of a Block of memory.
		void Display();
	private:
		//! The next Block in a list.
		Block* m_next{ nullptr };
		//! The previous Block in a list.
		Block* m_previous{ nullptr };
		//! Pointer to an address within a chunk of raw memory preallocated by
		//! this Block's Page.
		char* m_address{ nullptr };
		//! Amount of space within a preallocated chunk of raw memory that an
		//! object allocated using this Block may occupy without corruption.
		//! Primarily used to determine whether a Block can be split into two
		//! smaller blocks or not.
		unsigned m_size{ 0 };
	};

	/*!*************************************************************************
	* \class Page
	* \brief Allocates chunks of a specific size.
	*  
	*  A structure representing a preallocated chunk of raw memory, which
	*  it partitions and gives to the user upon request. To do this it uses two
	*  doubly linked lists of Blocks (free and allocated memory). Each Page can
	*  partition Blocks of memory of a certain predetermined size, up to the
	*  size of the chunk of memory allocated upon its creation.
	***************************************************************************/
	class Page
	{
	public:
		//! Page constructor.
		Page(unsigned max, unsigned blockSize, unsigned growth);
		//! Partition a Block of this Page's blocksize.
		void* Allocate();
		//! Mark a Block containing an address as able to be used again.
		void Deallocate(void* address);
		//! The next Page in a list.
		Page* Next();
		//! Whether this page can be partition Blocks of a specific size.
		bool Invalid(unsigned size);
		//! Whether an address is within this Page's range of addresses.
		bool Contains(void* address);
		//! Add a new, larger Page after this one.
		void AddPage();
		//! Show all allocated/unallocated Blocks on this Page.
		void Display();
		//! Page destructor.
		~Page();
	private:
		//! Pop the first element from a list of Blocks, making the next Block
		//! the head of its list.
		void AdvanceList(Block*& blockList);
		//! Add a Block to the front of a list of Blocks, making it the new head
		//! of the list.
		void AddToList(Block*& blockList, Block* block);
		//! Find a Block in the usedlist containing an address to be freed.
		Block* BlockContaining(void* address);
		//! Deallocate all nodes in a list of Blocks.
		void DestroyList(Block*& blockList);
		//! Display the contents of a list of Blocks.
		void ListDump(Block* blockList, const char* msg);
		//! Next Page in the list.
		Page* m_next{ nullptr };
		//! List of Blocks whose held addresses are available to be given to the
		//! user for use.
		Block* m_freeList{ nullptr };
		//! List of Blocks currently is use by the user.
		Block* m_usedList{ nullptr };
		//! The size of each Block on this Page.
		unsigned m_blockSize{ 0 };
		//! The total maximum memory that this page can allocate.
		unsigned m_pageSize{ 0 };
		//! How much larger the next Page is than this one.
		unsigned m_growth{ 2 };
		//! Chunk of preallocated memory, which Blocks contain pointers to. Each
		//! Block returns an address somewhere within this chunk to the user.
		char* m_rawMemory{ nullptr };
	};

	/*!*************************************************************************
	* \class Allocator
	* \brief Responsible for allocation and deallocation requests from the
	*  client.
	*  
	*  Holds a singly linked list of Pages, each able to partition Blocks
	*  twice as large as the previous Page is able to. The maximum amount of
	*  memory each Page can partition in total is specified during construction.
	*  The minimum amount of memory a Page can partition at once be set during
	*  construction as well, though specifying this is optional.
	***************************************************************************/
	class Allocator
	{
	public:
		//! Configure the settings for this allocator.
		void Init(unsigned max, unsigned min = 8, unsigned growth = 2);
		//! Allocate a chunk of memory of a specific size.
		void* Allocate(unsigned size);
		//! Return used memory back to the system for future reuse.
		void Deallocate(void* address);
		//! Display the current state of all Pages.
		void Display();
		//! Allocator destructor.
		~Allocator();
	private:
		//! Find a page able to accomodate Blocks of a specific size.
		Page* FindPage(unsigned size);
		//! Find a Page for which this address falls within its address range.
		Page* PageContaining(void* address);
		//! Deallocate all Pages and their Blocks.
		void DestroyPages();
		//! List of Pages, each able to allocate larger Blocks than the last.
		Page* m_pageList{ nullptr };
	};
	//! Betel's internal Allocator, for client-side simplicity.
	static Allocator Betelgeuse;
}
// Betel class method implementations
namespace Betel
{
	/*!*************************************************************************
	* \fn Block::Block(char* address, unsigned size);
	* \brief Block constructor.
	* \param address Address this Block will contain
	* \param size Maximum number of bytes from this Block that the user can use
	*  without corruption.
	***************************************************************************/
	Block::Block(char* address, unsigned size) :
		m_address{ address }
		, m_size{ size }
	{

	}

	/*!*************************************************************************
	* \fn void Block::Split(unsigned size);
	* \brief Split a Block into two smaller Blocks during partitioning.
	* \param size New size (in bytes) of the first Block, the byte offset from
	*  the first Block's address from which the second Block's address will be,
	*  as well as how much smaller the second Block will be than the original
	*  size of the first Block.
	***************************************************************************/
	void Block::Split(unsigned size)
	{
		if (m_size > size)
		{
			Block* block = new Block(m_address + size, m_size - size);
			m_size = size;
			SetNext(block);
		}
	}

	/*!*************************************************************************
	* \fn Block* Block::Next();
	* \brief Access the next Block in a list.
	* \return Next Block.
	***************************************************************************/
	Block* Block::Next()
	{
		return m_next;
	}

	/*!*************************************************************************
	* \fn char* Block::Address();
	* \brief Access the address that this Block will give to the user after
	*  partitioning.
	* \return Address stored in this Block.
	***************************************************************************/
	char* Block::Address()
	{
		return m_address;
	}

	/*!*************************************************************************
	* \fn void Block::SetNext(Block* block);
	* \brief Place a new Block after this one in a list. The new Block will also
	*  set this as its previous Block.
	* \param block Next Block in the list.
	***************************************************************************/
	void Block::SetNext(Block* block)
	{
		m_next = block;
		if (block)
		{
			block->m_previous = this;
		}
	}

	/*!*************************************************************************
	* \fn void Block::SetPrevious(Block* block);
	* \brief Place a new Block before this one in a list. The new Block will
	*  also set this as its next Block.
	* \param block Previous Block in the list.
	***************************************************************************/
	void Block::SetPrevious(Block* block)
	{
		m_previous = block;
		if (block)
		{
			block->m_next = this;
		}
	}

	/*!*************************************************************************
	* \fn void Block::Cut();
	* \brief Remove this Block from the middle of a list.
	***************************************************************************/
	void Block::Cut()
	{
		if (m_previous)
		{
			m_previous->SetNext(m_next);
		}
		if (m_next)
		{
			m_next->SetPrevious(m_previous);
		}
	}

	/*!*************************************************************************
	* \fn void Block::Display();
	* \brief Print a visual representation of a Block of memory.
	***************************************************************************/
	void Block::Display()
	{
		std::cout << "[" << m_size << "]->";
	}

	/*!*************************************************************************
	* \fn Page::Page(unsigned max, unsigned blockSize, unsigned growth);
	* \brief Page constructor.
	* \param max The maximum amount of memory, in bytes, that this Page can
	*  allocate.
	* \param blockSize The amount of memory each Block can allocate at once.
	* \param growth How much larger the next Page will be than this one.
	***************************************************************************/
	Page::Page(unsigned max, unsigned blockSize, unsigned growth) :
		m_blockSize{ blockSize }
		, m_pageSize{ max }
		, m_growth{ growth }
	{
		m_rawMemory = new char[max];
		Block* block = new Block(m_rawMemory, max);
		AddToList(m_freeList, block);
	}

	/*!*************************************************************************
	* \fn void* Page::Allocate();
	* \brief Partition a Block of this Page's blocksize.
	* \return The address contained within the first free Block of this page,
	*  which points to somewhere within this Page's preallocated chunk of
	*  memory. If this Page has no more free Blocks to allocate, it returns
	*  NULL.
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

	/*!*************************************************************************
	* \fn void Page::Deallocate(void* address);
	* \brief Mark a Block containing an address as able to be used again.
	* \param address Address to return to the system for reuse.
	***************************************************************************/
	void Page::Deallocate(void* address)
	{
		if (Block* block = BlockContaining(address))
		{
			if (block == m_usedList)
			{
				AdvanceList(m_usedList);
			}
			else
			{
				block->Cut();
			}
			AddToList(m_freeList, block);
		}
	}

	/*!*************************************************************************
	* \fn Page* Page::Next()
	* \brief The next Page in a list.
	* \return Next Page in the list.
	***************************************************************************/
	Page* Page::Next()
	{
		return m_next;
	}

	/*!*************************************************************************
	* \fn bool Page::Invalid(unsigned size);
	* \brief Whether this page can be partition Blocks of a specific size.
	* \param size Amount of memory the user wishes to allocate.
	* \return Return true if Blocks on this Page are too small to accomodate
	*  the requested size or if there are no free Blocks on this Page. Return
	*  false otherwise.
	***************************************************************************/
	bool Page::Invalid(unsigned size)
	{
		return m_blockSize < size || m_freeList == nullptr;
	}

	/*!*************************************************************************
	* \fn bool Page::Contains(void* address);
	* \brief Whether an address is within this Page's range of addresses.
	* \param address Address to be compared against this Page's range of
	*  addresses.
	* \return Return true if the requested address falls between the beginning
	*  and end of the preallocated chunk. Otherwise, if its address is somewhere
	*  outside of this range, return false.
	***************************************************************************/
	bool Page::Contains(void* address)
	{
		return address >= m_rawMemory && address < m_rawMemory + m_pageSize;
	}

	/*!*************************************************************************
	* \fn void Page::AddPage();
	* \brief Add a new, larger Page after this one.
	***************************************************************************/
	void Page::AddPage()
	{
		if (m_blockSize <= m_pageSize)
		{
			Page* nextPage = m_next;
			m_next = new Page(m_pageSize, m_blockSize * m_growth, m_growth);
			m_next->m_next = nextPage;
		}
	}

	/*!*************************************************************************
	* \fn void Page::Display();
	* \brief Show all allocated/unallocated Blocks on this Page.
	***************************************************************************/
	void Page::Display()
	{
		ListDump(m_freeList, "FREE  : ");
		ListDump(m_usedList, "IN USE: ");
		std::cout << std::endl;
	}

	/*!*************************************************************************
	* \fn Page::~Page();
	* \brief Page destructor.
	***************************************************************************/
	Page::~Page()
	{
		DestroyList(m_freeList);
		DestroyList(m_usedList);
		delete[] m_rawMemory;
	}

	/*!*************************************************************************
	* \fn void Page::AdvanceList(Block*& blockList);
	* \brief Pop the first element from a list of Blocks, making the next Block
	*  the head of its list.
	* \param blockList Block list to pop.
	***************************************************************************/
	void Page::AdvanceList(Block*& blockList)
	{
		blockList = blockList->Next();
		if (blockList)
		{
			blockList->SetPrevious(nullptr);
		}
	}

	/*!*************************************************************************
	* \fn void Page::AddToList(Block*& blockList, Block* block);
	* \brief Add a Block to the front of a list of Blocks, making it the new
	*  head of the list.
	* \param blockList List of Blocks to which this new Block will be added.
	* \param block Block to add to the front of the list.
	***************************************************************************/
	void Page::AddToList(Block*& blockList, Block* block)
	{
		block->SetNext(blockList);
		blockList = block;
	}

	/*!*************************************************************************
	* \fn Block* Page::BlockContaining(void* address);
	* \brief Find a Block in the usedlist containing an address to be freed.
	* \param address Address to search the usedlist for.
	* \return If a Block is found that contains the queried address, return it.
	*  Otherwise, return NULL.
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

	/*!*************************************************************************
	* \fn void Page::DestroyList(Block*& blockList);
	* \brief Deallocate all nodes in a list of Blocks.
	* \param blockList Head of the list of Blocks to deallocate.
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

	/*!*************************************************************************
	* \fn void Page::ListDump(Block*& blockList, const char* msg);
	* \brief Display the contents of a list of Blocks.
	* \param blockList List of Blocks of display.
	* \param msg A message to print before displaying the list.
	***************************************************************************/
	void Page::ListDump(Block* blockList, const char* msg)
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

	/*!*************************************************************************
	* \fn void Allocator::Init(unsigned max, unsigned min, unsigned growth);
	* \brief Configure the settings for this allocator. If there are no Pages,
	*  creates a Page of the smallest Block size.
	* \param max Maximum amount of memory a Page can allocate. This is also the
	*  maximum Block size a Page can have; such a Page can only hold one Block,
	*  its size being equal to this value. No more Pages can be created after
	*  that Page.
	* \param min Minimum amount of memory a Page can allocate. The first Page
	*  allocates Blocks of this size.
	* \param growth Growth factor between Pages. Each Page is this much larger
	*  than the one before it.
	***************************************************************************/
	void Allocator::Init(unsigned max, unsigned min, unsigned growth)
	{
		if (m_pageList == nullptr)
		{
			m_pageList = new Page(max, min, growth);
		}
	}

	/*!*************************************************************************
	* \fn void* Allocator::Allocate(unsigned size);
	* \brief Allocate a chunk of memory of a specific size.
	* \param size Amount of memory to allocate, in bytes.
	* \return If a suitable address was found, return it. Otherwise, if that
	*  much memory could not be found within the Allocator, return NULL.
	***************************************************************************/
	void* Allocator::Allocate(unsigned size)
	{
		if (Page* currentPage = FindPage(size))
		{
			return currentPage->Allocate();
		}
		return nullptr;
	}

	/*!*************************************************************************
	* \fn void Allocator::Deallocate(void* address);
	* \brief Return used memory back to the system for future reuse.
	* \param address Address that was previously allocated via the Allocate
	*  method.
	***************************************************************************/
	void Allocator::Deallocate(void* address)
	{
		if (Page* currentPage = PageContaining(address))
		{
			currentPage->Deallocate(address);
		}
	}

	/*!*************************************************************************
	* \fn void Allocator::Display();
	* \brief Display the current state of all Pages.
	***************************************************************************/
	void Allocator::Display()
	{
		std::cout << "-BETEL START-" << std::endl;
		Page* currentPage = m_pageList;
		int pageCount = 1;
		while (currentPage)
		{
			std::cout << "PAGE [" << pageCount++ << "]:" << std::endl;
			currentPage->Display();
			currentPage = currentPage->Next();
		}
		std::cout << "-BETEL   END-" << std::endl;
	}

	/*!*************************************************************************
	* \fn Allocator::~Allocator();
	* \brief Allocator destructor.
	***************************************************************************/
	Allocator::~Allocator()
	{
		DestroyPages();
	}

	/*!*************************************************************************
	* \fn Page* Allocator::FindPage(unsigned size);
	* \brief Find a page able to accomodate Blocks of a specific size.
	* \param size Number of bytes that a Page must be able to allocate at one
	*  time.
	* \return Return the first Page that can accomodate the requested size and
	*  is able to perform another allocation. If such a Page could not be found,
	*  return NULL.
	***************************************************************************/
	Page* Allocator::FindPage(unsigned size)
	{
		Init(DEFAULT_PAGE_LIMIT);
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

	/*!*************************************************************************
	* \fn Page* Allocator::PageContaining(void* address);
	* \brief Find a Page for which this address falls within its address range.
	* \param address Address to search the Page list for.
	* \return Return the first Page for which this address falls within its
	*  range of addresses. If such a Page could not be found, return NULL.
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

	/*!*************************************************************************
	* \fn void Allocator::DestroyPages();
	* \brief Deallocate all Pages and their Blocks.
	***************************************************************************/
	void Allocator::DestroyPages()
	{
		while (m_pageList)
		{
			Page* toDestroy = m_pageList;
			m_pageList = m_pageList->Next();
			delete toDestroy;
		}
	}

	/*!*************************************************************************
	* \fn void Initialize(unsigned max, unsigned min, unsigned growth);
	* \brief Set Betel's maximum and minimum Page size, as well as how much
	*  larger sequential Pages are.
	* \param max Maximum amount of total memory each Page can allocate.
	* \param min Minimum amount of memory each Page can allocate at once.
	* \param growth How much more memory each Page can allocate at once than the
	*  last.
	***************************************************************************/
	void Initialize(unsigned max, unsigned min, unsigned growth)
	{
		Betelgeuse.Init(max, min, growth);
	}

	/*!*************************************************************************
	* \fn void* Balloc(unsigned size)
	* \brief Malloc-style allocation for a chunk of memory.
	* \param size Number of bytes to allocate.
	* \return If allocation was successful, return an address to a chunk of
	*  memory of the requested size. Otherwise, return NULL.
	***************************************************************************/
	void* Balloc(unsigned size)
	{
		return Betelgeuse.Allocate(size);
	}

	/*!*************************************************************************
	* \fn void Deallocate(void* address);
	* \brief Give allocated memory back to the system.
	* \param address Address allocated by Betel to be returned to it.
	***************************************************************************/
	void Deallocate(void* address)
	{
		Betelgeuse.Deallocate(address);
	}

	/*!*************************************************************************
	* \fn void Display();
	* \brief Show all allocated and unallocated Blocks in all Pages.
	***************************************************************************/
	void Display()
	{
		Betelgeuse.Display();
	}
}