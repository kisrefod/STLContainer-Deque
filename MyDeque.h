#pragma once
template <typename TypeName>
class MyDeque
{
public:
	MyDeque();
	explicit MyDeque(int elementNum, TypeName element);
	~MyDeque();
	
	struct Node
	{
	public:
		TypeName value;
		Node* next;
		Node* prev;
		Node()
		{
			value = TypeName();
			next = NULL;
			prev = NULL;
		}

		Node(TypeName _value, Node* _prev, Node* _next)
		{
			value = _value;
			next = _next;
			prev = _prev;

			if (_prev != NULL)
				_prev->next = this;

			if (_next != NULL)
				_next->prev = this;
		}

		void delete_node()
		{
			if (prev != NULL)
				prev->next = next;

			if (next != NULL)
				next->prev = prev;

			delete this;
		}

		TypeName get_value()
		{
			return value;
		}

		TypeName set_value(TypeName _value)
		{
			value = _value;
		}
	};

	Node* first;
	Node* last;
	int _size;

	class Iterator
	{
	private:
		const MyDeque *myDeque;
		int index;
		Node *node;

	public:
		Iterator()
		{
			myDeque = NULL;
			index = 0;
			node = NULL;
		}

		Iterator(Iterator & it)
		{
			myDeque = it.myDeque;
			index = it.index;
			node = it.node;
		}

		Iterator(const MyDeque *deque, int index)
		{
			this->myDeque = deque;
			this->index = index;

			Node *temp = deque->first;
			if (temp != NULL)
			{
				for (int i = 0; i < index; i++)
				{
					if (temp->next != NULL)
						temp = temp->next;
				}
			}

			this->node = temp;
		}

		MyDeque * getDeque()
		{
			return myDeque;
		}

		Node * getNode()
		{
			return node;
		}

		Iterator & operator++()
		{
			index++;
			node = node->next;

			return *this;
		}

		Iterator operator++(int)
		{
			Iterator temp(*this);
			operator++();
			return temp;
		}

		Iterator & operator--()
		{
			index--;
			node = node->prev;

			return *this;
		}

		Iterator operator--(int)
		{
			Iterator temp(*this);
			operator--();
			return temp;
		}

		bool operator==(const Iterator & it)
		{
			return ((myDeque == it.myDeque) && (index == it.index));
		}

		bool operator!=(const Iterator & it)
		{
			return !(*this == it);
		}

		bool operator<(const Iterator & it)
		{
			if (myDeque != it.myDeque) return false;
			return (index < it.index);
		}

		bool operator<=(const Iterator & it)
		{
			if (myDeque != it.myDeque) return false;
			return (index <= it.index);
		}

		bool operator>(const Iterator & it)
		{
			if (myDeque != it.myDeque) return false;
			return (index > it.index);
		}

		bool operator>=(const Iterator & it)
		{
			if (myDeque != it.myDeque) return false;
			return (index >= it.index);
		}

		Iterator operator+(const int &step)
		{
			return Iterator(myDeque, index + step);
		}

		Iterator operator+=(const int & step)
		{
			this->index += step;
			for (int i = step; i > 0; i--)
			{
				this->node = this->node->next;
			}

			return (*this);
		}

		Iterator operator-(const int & step)
		{
			return Iterator(myDeque, index - step);
		}

		Iterator operator-=(const int & step)
		{
			this->index -= step;
			for (int i = step; i > 0; i--)
			{
				this->node = this->node->prev;
			}

			return (*this);
		}

		int operator-(const Iterator & it)
		{
			if (myDeque != it.myDeque) return 0;
			return index - it.index;
		}

		TypeName & operator*()
		{
			return node->value;
		}

		TypeName *operator->()
		{
			return &(node->value);
		}

		TypeName & operator[](int step)
		{
			Node *temp = node;
			for (int i = step; i > 0; i--)
			{
				temp = temp->next;
			}

			return temp->value;
		}
	};

	class FrontInsertIterator
	{
	private:
		const MyDeque *myDeque;
		int index;
		Node *node;
	public:
		FrontInsertIterator()
		{
			this->myDeque = NULL;
			index = 0;
			node = NULL;
		}

		FrontInsertIterator(FrontInsertIterator & it)
		{
			this->myDeque = it.myDeque;
			this->index = it.index;
			this->node = it.node;
		}

		FrontInsertIterator(const MyDeque *myDeque, int index)
		{
			this->myDeque = myDeque;
			this->index = index;

			Node *temp = deque->first;
			for (int i = index; i > 0; i--)
			{
				temp = temp->next;
			}

			this->node = temp;
		}

		bool operator==(const Iterator & it)
		{
			return ((myDeque == it.myDeque) && (index == it.index));
		}

		bool operator!=(const Iterator & it)
		{
			return !(*this == it);
		}

		bool operator<(const Iterator & it)
		{
			if (myDeque != it.myDeque) return false;
			return (index < it.index);
		}

		bool operator<=(const Iterator & it)
		{
			if (myDeque != it.myDeque) return false;
			return (index <= it.index);
		}

		bool operator>(const Iterator & it)
		{
			if (myDeque != it.myDeque) return false;
			return (index > it.index);
		}

		bool operator>=(const Iterator & it)
		{
			if (myDeque != it.myDeque) return false;
			return (index >= it.index);
		}

		int operator-(const Iterator & it)
		{
			if (myDeque != it.myDeque) return 0;
			return index - it.index;
		}

		TypeName & operator*()
		{
			return node->value;
		}

		TypeName *operator->()
		{
			return &(node->value);
		}

		TypeName & operator[](int step)
		{
			Node *temp = node;
			for (int i = step; i > 0; i--)
			{
				temp = temp->next;
			}

			return temp->value;
		}
	};

	void assign(int elementNum, TypeName element);
	TypeName & at(int index);
	TypeName & front();
	TypeName & back();
	bool isEmpty();
	int size();
	void clear();

	void push_front(TypeName value);
	void pop_front();
	void push_back(TypeName value);
	void pop_back();

	void resize(int newSize);
	void resize(int newSize, TypeName value);
	void swap(MyDeque<TypeName>& deq);
	TypeName & operator[](int index);
	const TypeName & operator[](int index) const;

	bool operator==(MyDeque right);
	bool operator!=(MyDeque right);

	Iterator begin()
	{
		return Iterator(this, 0);
	}

	Iterator end()
	{
		return Iterator(this, _size);
	}

	FrontInsertIterator secondBegin()
	{
		return FrontInsertIterator(this, 0);
	}

	FrontInsertIterator secondEnd()
	{
		return FrontInsertIterator(this, _size);
	}

	void insert(Iterator index, TypeName value);
	void erase(Iterator, Iterator);
	void erase(Iterator);
};
