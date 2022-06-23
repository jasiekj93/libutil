#pragma once

/**
 * @file	List.tpp
 * @author	Adrian Szczepanski
 * @date	24-03-2021
 * @brief
 * @details
**/

namespace util
{
	template <class Type, class C>
	ListBase<Type, C>::ListBase()
        : _nodes((size_t)0)
	{
		_head = nullptr;
		_tail = nullptr;
		_count = 0;
	}

	template <class Type, class C>
	const Type* ListBase<Type, C>::front() const
	{
		if (_head != nullptr)
			return &_head->object;
		else
			return nullptr;
	}

	template <class Type, class C>
	const Type* ListBase<Type, C>::back() const
	{
		if (_tail != nullptr)
			return &_tail->object;
		else
			return nullptr;
	}

	template <class Type, class C>
	bool ListBase<Type, C>::pushFront(const Type & object)
	{
		auto newNode = _getFreeNode();

		if (newNode == nullptr)
			return false;

		newNode->object = Type(object);
		newNode->isFree = false;

		if (_head == nullptr)
		{
			newNode->next = nullptr;
			_head = newNode;
			_tail = newNode;
		}
		else
		{
			newNode->next = _head;
			_head = newNode;
		}

		_count++;
		return true;
	}

	template <class Type, class C>
	bool ListBase<Type, C>::pushBack(const Type & object)
	{
		auto newNode = _getFreeNode();

		if (newNode == nullptr)
			return false;

		newNode->object = Type(object);
		newNode->isFree = false;

		if (_tail == nullptr)
		{
			_head = newNode;
			_tail = newNode;
		}
		else
		{
			_tail->next = newNode;
			_tail = newNode;
		}

		_count++;
		return true;
	}

	template <class Type, class C>
	bool ListBase<Type, C>::popFront()
	{
		if (_head == nullptr)
			return false;

	    auto* tmp = _head;

		if (_head == _tail)
		{
			_head = nullptr;
			_tail = nullptr;
		}
		else
			_head = _head->next;

		tmp->next = nullptr;
		tmp->isFree = true;

		_count--;
		return true;
	}

	template <class Type, class C>
	bool ListBase<Type, C>::popBack()
	{
		if (_tail == nullptr)
			return false;

		auto* tmp = _tail;

		if (_head == _tail)
		{
			_head = nullptr;
			_tail = nullptr;
		}
		else
		{
			auto* tmp2 = _head;

			while (tmp2->next != _tail)
				tmp2 = tmp2->next;

			tmp2->next = nullptr;
			_tail = tmp2;
		}

		tmp->next = nullptr;
		tmp->isFree = true;

		_count--;
		return true;
	}

	template <class Type, class C>
	void ListBase<Type, C>::clear()
	{
		for (auto &node : _nodes)
		{
			node.next = nullptr;
			node.isFree = true;
		}

		_count = 0;
	}

	template <class Type, class C>
	Type * ListBase<Type, C>::operator[](size_t index)
	{
		if (index > _count)
			return nullptr;

		auto* tmp = _head;

		size_t i = 0;
		while (tmp != nullptr && i < index)
		{
			i++;
			tmp = tmp->next;
		}
		if (tmp == nullptr)
			return nullptr;
		else
			return &tmp->object;
	}

	template <class Type, class C>
	Node<Type> * ListBase<Type, C>::_getFreeNode()
	{
        auto result = std::find_if(_nodes.begin(),
            _nodes.end(),
            [](const Node<Type>& node) { return (node.isFree == true); });

        if(result == _nodes.end())
            return nullptr;
        else
            return result;
	}
}