#pragma once

/**
 * @file	StaticList.hpp
 * @author	Adrian Szczepanski
 * @date	24-03-2021
 * @brief
 * @details
**/

#include <cstdint>
#include <cstddef>

namespace Utils::Static
{
	template <class Type, size_t SIZE> 
	class List
	{		
	public:
		List();

		const Type* Front() const;
		const Type* Back() const;

		bool PushFront(const Type & object);
		bool PushBack(const Type & object);

		bool PopFront();
		bool PopBack();

		void Clear();

		static constexpr auto Size() { return SIZE; }
		inline auto Count() const { return _count; }
		inline bool IsEmpty() const { return (_count == 0); }
		inline bool IsNotEmpty() const { return (_count != 0); }
		inline bool IsFull() const { return (_count == SIZE); }

		Type * operator[](uint32_t index);

	protected:
		struct Node
		{
			Type object;
			Node *next = nullptr;
			bool isFree = true;
		};

		Node * _GetFreeNode();

	private:
		Node *_head;
		Node *_tail;
		Node _nodes[SIZE];
		size_t _count;
	};
}

#include <libUtils/Static/List.tpp>
