#pragma once

/**
 * @file	List.tpp
 * @author	Adrian Szczepanski
 * @date	24-03-2021
 * @brief
 * @details
**/

namespace util::stat
{
	template <class Type, size_t SIZE>
	List<Type, SIZE>::List()
	{
		_head = nullptr;
		_tail = nullptr;
		_count = 0;
	}

	template <class Type, size_t SIZE>
	const Type* List<Type, SIZE>::front() const
	{
		if (_head != nullptr)
			return &_head->object;
		else
			return nullptr;
	}

	template <class Type, size_t SIZE>
	const Type* List<Type, SIZE>::back() const
	{
		if (_tail != nullptr)
			return &_tail->object;
		else
			return nullptr;
	}

	template <class Type, size_t SIZE>
	bool List<Type, SIZE>::pushFront(const Type & object)
	{
		Node *newNode = _getFreeNode();

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

	template <class Type, size_t SIZE>
	bool List<Type, SIZE>::pushBack(const Type & object)
	{
		Node *newNode = _getFreeNode();

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

	template <class Type, size_t SIZE>
	bool List<Type, SIZE>::popFront()
	{
		if (_head == nullptr)
			return false;

		Node *tmp = _head;

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

	template <class Type, size_t SIZE>
	bool List<Type, SIZE>::popBack()
	{
		if (_tail == nullptr)
			return false;

		Node *tmp = _tail;

		if (_head == _tail)
		{
			_head = nullptr;
			_tail = nullptr;
		}
		else
		{
			Node *tmp2 = _head;

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

	template <class Type, size_t SIZE>
	void List<Type, SIZE>::clear()
	{
		for (uint32_t i = 0; i < SIZE; i++)
		{
			_nodes[i].next = nullptr;
			_nodes[i].isFree = true;
		}

		_count = 0;
	}

	template <class Type, size_t SIZE>
	Type * List<Type, SIZE>::operator[](size_t index)
	{
		if (index > _count)
			return nullptr;

		Node *tmp = _head;

		uint32_t i = 0;
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

	template <class Type, size_t SIZE>
	typename List<Type, SIZE>::Node * List<Type, SIZE>::_getFreeNode()
	{
        auto result = std::find_if(_nodes.begin(),
            _nodes.end(),
            [](const Node& node) { return (node.isFree == true); });

        if(result == _nodes.end())
            return nullptr;
        else
            return result;
	}
}