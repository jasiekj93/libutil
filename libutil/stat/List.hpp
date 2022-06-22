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
#include <algorithm>
#include <array>

namespace util::stat
{
	template <class Type, size_t SIZE> 
	class List
	{		
	public:
		List();

		const Type* front() const;
		const Type* back() const;

		bool pushFront(const Type & object);
		bool pushBack(const Type & object);

		bool popFront();
		bool popBack();

		void clear();

		static constexpr auto size() { return SIZE; }
		inline auto count() const { return _count; }
		inline bool isEmpty() const { return (_count == 0); }
		inline bool isNotEmpty() const { return (_count != 0); }
		inline bool isFull() const { return (_count == SIZE); }

		Type * operator[](size_t index);

	protected:
		struct Node
		{
			Type object;
			Node *next = nullptr;
			bool isFree = true;
		};

		Node * _getFreeNode();

	private:
		Node *_head;
		Node *_tail;
		std::array<Node, SIZE> _nodes;
		size_t _count;
	};
}

#include <libutil/stat/List.tpp>
