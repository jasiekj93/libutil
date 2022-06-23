#pragma once

/**
 * @file	StaticList.hpp
 * @author	Adrian Szczepanski
 * @date	24-03-2021
 * @brief
 * @details
**/

#include <libutil/Array.hpp>

namespace util
{
    template<typename T>
    struct Node
    {
        T object;
        Node* next = nullptr;
        bool isFree = true;
    };
    
	template <class Type, class Container> 
	class ListBase
	{		
	public:
		ListBase();
		explicit ListBase(size_t);

		const Type* front() const;
		const Type* back() const;

		bool pushFront(const Type& object);
		bool pushBack(const Type& object);

		bool popFront();
		bool popBack();

		void clear();

		constexpr auto size() { return _nodes.size(); }
		inline auto count() const { return _count; }
		inline bool isEmpty() const { return (_count == 0); }
		inline bool isNotEmpty() const { return (_count != 0); }
		inline bool isFull() const { return (_count == _nodes.size()); }

		Type* operator[](size_t index);

	protected:
		Node<Type>* _getFreeNode();

	private:
		Node<Type>* _head;
		Node<Type>* _tail;
		Container _nodes;
		size_t _count;
	};

    template<typename T>
    using List = ListBase<T, DynArray<Node<T>>>;

    template<typename T, size_t SIZE>
    using SList = ListBase<T, Array<Node<T>, SIZE>>;
}

#include <libutil/List.tpp>
