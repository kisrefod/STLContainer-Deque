#include "MyDeque.h"

#include <iostream>
#include <deque>
#include <string>

using namespace std;

template<class Container>
class front_insert_iterator : public std::iterator< std::output_iterator_tag, void, void, void, void >
{
private:
	Container& c;
public:
	front_insert_iterator(Container& c)
	{
		this->c = c;
	}

	front_insert_iterator& operator * ()
	{
		return *this;
	}

	front_insert_iterator& operator ++ ()
	{
		return *this;
	}

	front_insert_iterator& operator ++ (int)
	{
		return *this;
	}

	template<typename TypeName>
	front_insert_iterator<Container>& operator=(const TypeName& value)
	{
		c.push_front(value);
		return *this;
	}
};

template<typename TypeName>
MyDeque<TypeName>::MyDeque()
{
	_size = 0;
	first = NULL;
	last = NULL;
}

template<typename TypeName>
MyDeque<TypeName>::MyDeque(int elementNum, TypeName element)
{
	_size = elementNum;
	if (elementNum != 0)
		first = new Node;

	Node *temp, *temp_prev = NULL;
	for (int i = 0; i < elementNum; i++)
	{
		temp = new Node;
		if (i == 0)
		{
			first = temp;
			temp->prev = NULL;
			temp->value = element;
			temp_prev = temp;
			continue;
		}

		if (i == elementNum - 1)
		{
			last = temp;
			temp->next = NULL;
		}

		temp->value = element;
		temp->prev = temp_prev;
		temp_prev->next = temp;
		temp_prev = temp;
	}
}

template<typename TypeName>
MyDeque<TypeName>::~MyDeque()
{
	if (_size == 0)
	{
		return;
	}

	Node *temp_next = NULL;
	for (Node *temp = first; temp != NULL;)
	{
		temp_next = temp->next;
		delete temp;
		temp = temp_next;
	}
}

template<typename TypeName>
void MyDeque<TypeName>::assign(int elementNum, TypeName element)
{
	this->clear();
	_size = elementNum;
	if (elementNum != 0)
		first = new Node;

	Node *temp, *temp_prev = NULL;
	for (int i = 0; i < elementNum; i++)
	{
		temp = new Node;
		if (i == 0)
		{
			first = temp;
			temp->prev = NULL;
			temp->value = element;
			temp_prev = temp;
			continue;
		}

		if (i == elementNum - 1)
		{
			last = temp;
			temp->next = NULL;
		}

		temp->value = element;
		temp->prev = temp_prev;
		temp_prev->next = temp;
		temp_prev = temp;
	}
}

template<typename TypeName>
TypeName & MyDeque<TypeName>::at(int index)
{
	Node *temp = first;
	for (int i = 0; i < index; i++)
	{
		temp = temp->next;
	}

	return temp->value;
}

template<typename TypeName>
TypeName & MyDeque<TypeName>::front()
{
	return first->value;
}

template<typename TypeName>
TypeName & MyDeque<TypeName>::back()
{
	return last->value;
}

template<typename TypeName>
bool MyDeque<TypeName>::isEmpty()
{
	if (_size == 0)
		return true;
	else
		return false;
}

template<typename TypeName>
int MyDeque<TypeName>::size()
{
	return _size;
}

template<typename TypeName>
void MyDeque<TypeName>::clear()
{
	if (_size == 0)
	{
		return;
	}

	Node *temp_next = NULL;
	for (Node *temp = first; temp != NULL;)
	{
		temp_next = temp->next;
		delete temp;
		temp = temp_next;
	}
}

template<typename TypeName>
void MyDeque<TypeName>::push_front(TypeName value)
{
	Node *temp = new Node;
	temp->value = value;
	temp->next = first;
	if (first != NULL)
	{
		first->prev = temp;
	}
	else
	{
		last = temp;
	}

	first = temp;
	_size++;
}

template<typename TypeName>
void MyDeque<TypeName>::pop_front()
{
	first = first->next;
	delete first->prev;
	first->prev = NULL;
	_size--;
}

template<typename TypeName>
void MyDeque<TypeName>::push_back(TypeName value)
{
	Node *temp = new Node;
	temp->value = value;

	temp->prev = last;
	if (last != NULL)
	{
		last->next = temp;
	}
	else
	{
		first = temp;
	}

	last = temp;
	_size++;
}

template<typename TypeName>
void MyDeque<TypeName>::pop_back()
{
	last = last->prev;
	delete last->next;
	last->next = NULL;
	_size--;
}

template<typename TypeName>
void MyDeque<TypeName>::resize(int newSize)
{
	resize(newSize, 0);
}

template<typename TypeName>
void MyDeque<TypeName>::resize(int newSize, TypeName value)
{
	if (newSize > _size)
	{
		for (int i = newSize - _size; i > 0; i--)
			push_back(value);
	}
	else if (newSize < _size)
	{
		for (int i = _size = newSize; i > 0; i--)
			erase(end());
	}

	_size = newSize;
}

template<typename TypeName>
void MyDeque<TypeName>::swap(MyDeque<TypeName>& deq)
{
	Node *temp = first;
	first = deq.first;
	deq.first = temp;

	temp = last;
	last = deq.last;
	deq.last = temp;

	int itemp = _size;
	_size = deq._size;
	deq._size = itemp;
}

template<typename TypeName>
TypeName & MyDeque<TypeName>::operator[](int index)
{
	return this->at(index);
}

template<typename TypeName>
const TypeName & MyDeque<TypeName>::operator[](int index) const
{
	return this->at(index);
}

template<typename TypeName>
bool MyDeque<TypeName>::operator==(MyDeque right)
{
	if (size() != right.size())
		return false;

	for (size_t i = 0; i < size(); i++)
	{
		if (this->at(i) != right[i])
			return false;
	}
	return true;
}

template<typename TypeName>
bool MyDeque<TypeName>::operator!=(MyDeque right)
{
	if (size() != right.size())
		return true;

	for (size_t i = 0; i < size(); i++)
	{
		if (this->at(i) != right[i])
			return true;
	}
	return false;
}

template<typename TypeName>
void MyDeque<TypeName>::insert(Iterator index, TypeName value)
{
	Node *temp = index.getNode();
	Node *node = new Node;
	node->value = value;

	if (temp == first)
	{
		node->next = temp;
		temp->prev = node;
		first = node;
	}

	node->next = temp;
	node->prev = temp->prev;
	temp->prev = node;
	_size++;
}

template<typename TypeName>
void MyDeque<TypeName>::erase(Iterator firstIt, Iterator lastIt)
{
	if (firstIt < lastIt)
	{
		int len = lastIt - firstIt;

		Iterator it = firstIt;

		for (int i = 0; i < len; i++)
		{
			erase(it);
			it++;
		}
	}
}

template<typename TypeName>
void MyDeque<TypeName>::erase(Iterator pos)
{
	Node *node = pos.getNode();
	Node *temp;

	if (node != last)
	{
		temp = node->next;
		temp->prev = node->prev;
	}

	if (node != first)
	{
		temp = node->prev;
		temp->next = node->next;
	}

	if (node == first)
	{
		first = first->next;
	}

	if (node == last)
	{
		last = last->prev;
	}

	delete node;
	_size--;
}
