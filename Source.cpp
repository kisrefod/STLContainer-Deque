#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>

using namespace std;


////DEQUE////
template <typename TypeName>
struct Node
{
	TypeName value;
	Node<TypeName>* next;
	Node<TypeName>* prev;
	Node<TypeName>()
	{
		value = TypeName();
		next = NULL;
		prev = NULL;
	}

	Node<TypeName>(TypeName _value, Node<TypeName>* _prev, Node<TypeName>* _next)
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

template <typename TypeName>
class MyDeque
{
public:
	Node<TypeName>* first;
	Node<TypeName>* last;
	int _size;

	class Iterator
	{
	private:
		const MyDeque *myDeque;
		int index;
		Node<TypeName> *node;

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

			Node<TypeName> *temp = deque->first;
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

		Node<TypeName> * getNode()
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
			Node<TypeName> *temp = node;
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
		Node<TypeName> *node;
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

			Node<TypeName> *temp = deque->first;
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
			Node<TypeName> *temp = node;
			for (int i = step; i > 0; i--)
			{
				temp = temp->next;
			}

			return temp->value;
		}
	};

	MyDeque();
	explicit MyDeque(int elementNum, TypeName element);
	~MyDeque();

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

template< class Container >
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
		first = new Node<TypeName>;

	Node<TypeName> *temp, *temp_prev = NULL;
	for (int i = 0; i < elementNum; i++)
	{
		temp = new Node<TypeName>;
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

	Node<TypeName> *temp_next = NULL;
	for (Node<TypeName> *temp = first; temp != NULL;)
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
		first = new Node<TypeName>;

	Node<TypeName> *temp, *temp_prev = NULL;
	for (int i = 0; i < elementNum; i++)
	{
		temp = new Node<TypeName>;
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
	Node<TypeName> *temp = first;
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

	Node<TypeName> *temp_next = NULL;
	for (Node<TypeName> *temp = first; temp != NULL;)
	{
		temp_next = temp->next;
		delete temp;
		temp = temp_next;
	}
}

template<typename TypeName>
void MyDeque<TypeName>::push_front(TypeName value)
{
	Node<TypeName> *temp = new Node<TypeName>;
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
	if (first->next != NULL)
	{
		first = first->next;
		delete first->prev;
		first->prev = NULL;
	}
	else
	{
		delete first;
		first = last = NULL;
	}
	_size--;
}

template<typename TypeName>
void MyDeque<TypeName>::push_back(TypeName value)
{
	Node<TypeName> *temp = new Node<TypeName>;
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
	if (last->prev != NULL)
	{
		last = last->prev;
		delete last->next;
		last->next = NULL;
	}
	else
	{
		delete last;
		last = first = NULL;
	}
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
	Node<TypeName> *temp = first;
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
	Node<TypeName> *temp = index.getNode();
	Node<TypeName> *node = new Node<TypeName>;
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
	Node<TypeName> *node = pos.getNode();
	Node<TypeName> *temp;

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
////DEQUE////


#define SUBDIMENSION	(3)
#define MIN_NUM		(1)
#define MAX_NUM		(9)
#define TOTAL_NUMS	(9)
#define ARRAY_SIZE	(MIN_NUM + TOTAL_NUMS)

#ifdef ASSERT
#define assert_(A) assert(A)
#else
#define assert_(A)
#endif

typedef array<int, ARRAY_SIZE> candidates;

struct cell {
	int has_value;
	int value;

	candidates *row_candidates;
	candidates *col_candidates;
	candidates *square_candidates;
};

class Board {
private:
	string input_file_name;
	int unset_cells;
	struct cell cells[ARRAY_SIZE][ARRAY_SIZE];

	void init_candidates(candidates *c);
	void use_candidate(candidates *cp, int num);
	void restore_candidate(candidates *cp, int num);
	bool is_num_can_be_set(int r, int c, int num);
	bool is_row_suitable(int r, int num);
	bool is_column_suitable(int c, int num);
	bool is_block_suitable(int r, int c, int num);
public:
	array<candidates, ARRAY_SIZE> rows;
	array<candidates, ARRAY_SIZE> columns;
	array<candidates, ARRAY_SIZE> squares;

	Board();
	void read_board(const char* file_name);
	int get_cell_value(int i, int j);
	int get_unset_cells();
	int find_common_free(int row, int column, int atleast);
	int is_set(int r, int c);
	void set_cell(int r, int c, int val);
	void unset_cell(int r, int c, int val);
	string get_input_file_name();
};

class Solver {
private:
	Board *b;
	MyDeque<Board> *boards;

	int solve_board(int r, int c);
	void print_board();
public:
	Solver(Board *board);
	Solver(MyDeque<Board> *board_deque);
	void set_board(Board *board);
	void solve_all_boards();
};


int square(int row, int col);
int next_cell(int *r, int *c);


////BOARD////
Board::Board() {
	int i;
	int j;

	assert_(this != NULL);

	this->unset_cells = TOTAL_NUMS * TOTAL_NUMS;

	for (i = MIN_NUM; i <= MAX_NUM; ++i) {
		this->init_candidates(&this->rows[i]);
		this->init_candidates(&this->columns[i]);
		this->init_candidates(&this->squares[i]);

		for (j = MIN_NUM; j <= MAX_NUM; ++j) {
			this->cells[i][j].has_value = 0;
			this->cells[i][j].value = 0;
			this->cells[i][j].row_candidates = &this->rows[i];
			this->cells[i][j].col_candidates = &this->columns[j];
			this->cells[i][j].square_candidates = &this->squares[square(i, j)];
		}
	}
}

int Board::find_common_free(int row, int column, int atleast)
{
	candidates *r = this->cells[row][column].row_candidates;
	candidates *c = this->cells[row][column].col_candidates;
	candidates *s = this->cells[row][column].square_candidates;
	assert_(r != NULL && c != NULL && s != NULL);
	
	int i;
	for (i = atleast; i <= MAX_NUM; ++i)
	{
		if (is_num_can_be_set(row, column, i))
		{
			return i;
		}
	}

	return (-1);
}

bool Board::is_num_can_be_set(int r, int c, int num)
{
	if (!cells[r][c].has_value &&
		is_row_suitable(r, num) &&
		is_column_suitable(c, num) &&
		is_block_suitable(r, c, num))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Board::is_row_suitable(int r, int num)
{
	for (int i = MIN_NUM; i <= MAX_NUM; i++)
	{
		cell* point = &cells[r][i];
		if (point->has_value && point->value == num)
		{
			return false;
		}
	}
	return true;
}

bool Board::is_column_suitable(int c, int num)
{
	for (int i = MIN_NUM; i <= MAX_NUM; i++)
	{
		cell* point = &cells[i][c];
		if (point->has_value && point->value == num)
		{
			return false;
		}
	}
	return true;
}

bool Board::is_block_suitable(int r, int c, int num)
{
	int block_num = square(r, c);
	int col_shift = ((block_num - 1) % SUBDIMENSION) * 3;//1, 4, 7 block = 0; 2, 5, 8 block = 3; 3, 6, 9 block = 6
	int row_shift = ((block_num - 1) / SUBDIMENSION) * 3;//1, 2, 3 block = 0; 4, 5, 6 block = 3; 7, 8, 9 block = 6
	candidates cand;

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		cand[i] = 0;
	}

	for (int i = MIN_NUM + row_shift; i < MIN_NUM + row_shift + 3; i++)
	{
		for (int j = MIN_NUM + col_shift; j < MIN_NUM + col_shift + 3; j++)
		{
			if (cells[i][j].has_value)
			{
				int value = cells[i][j].value;
				cand[value] = 1;
			}
		}
	}

	if (cand[num] == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Board::init_candidates(candidates *c) {
	int i;

	for (i = MIN_NUM; i <= MAX_NUM; ++i)
		(*c)[i] = 0;
}

void Board::use_candidate(candidates *cp, int num)
{
	assert_(cp != NULL && num >= MIN_NUM && num <= MAX_NUM);

	(*cp)[num] = 1;
}

void Board::restore_candidate(candidates *cp, int num)
{
	assert_(cp != NULL && num >= MIN_NUM && num <= MAX_NUM);

	(*cp)[num] = 0;
}

void Board::read_board(const char* file_name)
{
	this->input_file_name = file_name;

	ifstream f;
	f.open(file_name);
	if (!f.is_open()) {
		fprintf(stderr, "ERROR: could not open \"%s\"\n", file_name);
		return;
	}

	int row;
	int col;
	char c;

	assert_(f != NULL && this != NULL);

	row = MIN_NUM;
	col = MIN_NUM;

	while (!f.eof()) {
		c = f.get();
		if ((isdigit(c) && c != '0') || c == '.') {
			if (c != '.')
				this->set_cell(row, col, c - '0');
			if (!next_cell(&row, &col))
				break;
		}
	}

	f.close();
}

void Board::set_cell(int r, int c, int val)
{
	assert_(this != NULL &&
		r >= MIN_NUM && r <= MAX_NUM &&
		c >= MIN_NUM && c <= MAX_NUM &&
		val >= MIN_NUM && val <= MAX_NUM);

	assert_((!(*(this->cells[r][c].row_candidates))[val]) &&
		(!(*(this->cells[r][c].col_candidates))[val]) &&
		(!(*(this->cells[r][c].square_candidates))[val]));

	this->unset_cells -= 1;
	this->cells[r][c].has_value = 1;
	this->cells[r][c].value = val;
	this->use_candidate(this->cells[r][c].row_candidates, val);
	this->use_candidate(this->cells[r][c].col_candidates, val);
	this->use_candidate(this->cells[r][c].square_candidates, val);
}

void Board::unset_cell(int r, int c, int val)
{
	assert_(this != NULL &&
		r >= MIN_NUM && r <= MAX_NUM &&
		c >= MIN_NUM && c <= MAX_NUM &&
		val >= MIN_NUM && val <= MAX_NUM);

	assert_((*(this->cells[r][c].row_candidates))[val] &&
		(*(this->cells[r][c].col_candidates))[val] &&
		(*(this->cells[r][c].square_candidates))[val]);

	this->unset_cells += 1;
	this->cells[r][c].has_value = 0;
	this->cells[r][c].value = 0;
	this->restore_candidate(this->cells[r][c].row_candidates, val);
	restore_candidate(this->cells[r][c].col_candidates, val);
	restore_candidate(this->cells[r][c].square_candidates, val);
}

int Board::is_set(int r, int c)
{
	assert_(this != NULL &&
		r >= MIN_NUM && r <= MAX_NUM &&
		c >= MIN_NUM && c <= MAX_NUM);

	return (this->cells[r][c].has_value);
}

int Board::get_cell_value(int row, int column)
{
	return this->cells[row][column].value;
}

int Board::get_unset_cells()
{
	return unset_cells;
}

string Board::get_input_file_name()
{
	return input_file_name;
}
////BOARD////


////SOLVER////
void Solver::set_board(Board *board)
{
	this->b = board;
}

void Solver::print_board()
{
	int i;
	int j;

	assert_(this != NULL);

	string output_file_name = "SOLVED " + b->get_input_file_name();
	cout << output_file_name << endl;
	ofstream output;
	output.open(output_file_name, ios::out);

	for (i = MIN_NUM; i <= MAX_NUM; ++i) 
	{
		for (j = MIN_NUM; j <= MAX_NUM; ++j)
		{
			output << " " << b->get_cell_value(i, j);
		}
		output << endl;
	}
}

int Solver::solve_board(int r, int c)
{
	int prev;
	int val;

	assert_(this != NULL &&
		r >= MIN_NUM && r <= MAX_NUM &&
		c >= MIN_NUM && c <= MAX_NUM);

	/* Base case: board solved, print it. */
	if (b->get_unset_cells() == 0) {
		print_board();
		return 1;
	}

	/* Find the next unset cell. */
	while (b->is_set(r, c) && next_cell(&r, &c))
		;

	/* This should never happen. */
	if (b->is_set(r, c))
		return 1;

	/* Try every possible cell value until the board can be solved. */
	prev = MIN_NUM;
	while (1) {
		val = b->find_common_free(r, c, prev);
		if (val == -1)
			break;
		b->set_cell(r, c, val);
		
		if (solve_board(r, c))
			return 1;
		b->unset_cell(r, c, val);

		prev = val + 1;
	}

	return 0;
}

void Solver::solve_all_boards()
{
	if (this->boards == NULL)//Если решатор был создан чере подачу одной доски судоку, то...
	{
		solve_board(MIN_NUM, MIN_NUM);
	}
	else
	{
		while (!boards->isEmpty())
		{
			this->b = &(boards->at(0));

			solve_board(MIN_NUM, MIN_NUM);
			boards->pop_front();//Убрать из очереди первый элемент
		}
	}
}

Solver::Solver(Board *board)
{
	this->b = board;
	this->boards = NULL;
}

Solver::Solver(MyDeque<Board> *boardDeque)
{
	this->boards = boardDeque;
}
////SOLVER////


////OTHER FUNCTIONS////
vector<string> read_sudoku_files_names(char* input_file_name)
{
	vector<string> result;
	
	ifstream in;
	in.open(input_file_name);
	while(!in.eof())
	{
		string file_name;
		in >> file_name;
		if (!file_name.empty())
		{
			result.push_back(file_name);
		}
	}

	return result;
}

int square(int row, int col)
{
	assert_(row >= MIN_NUM && row <= MAX_NUM &&
		col >= MIN_NUM && col <= MAX_NUM);

	return (((row - 1) / SUBDIMENSION) * SUBDIMENSION) +
		((col - 1) / SUBDIMENSION) + 1;
}

int following(int num)
{
	assert_(num >= MIN_NUM && num <= MAX_NUM);

	return ((num - MIN_NUM + 1) % TOTAL_NUMS + MIN_NUM);
}

int next_cell(int *r, int *c)
{
	assert_(r != NULL && c != NULL);

	if ((*r) == MAX_NUM && (*c) == MAX_NUM)
		return 0;

	*c = following(*c);
	if ((*c) == MIN_NUM)
		(*r) = following(*r);
	return 1;
}
////OTHER FUNCTIONS////

int main(int argc, char *argv[])
{
	if (argc > 2) {
		fprintf(stderr, "ERROR: too many arguments\n");
		return 1;
	}

	if (argc < 2) {
		fprintf(stderr, "ERROR: not enough arguments\n");
		return 1;
	}
	
	//Аргументом подается файл, в котором перечисляются файлы с судоку
	vector<string> sudoku_files_names = read_sudoku_files_names(argv[1]);
	
	MyDeque<Board> deq;
	for (string str : sudoku_files_names)
	{
		Board b;
		b.read_board(str.c_str());
		deq.push_back(b);
	}
	
	Solver s(&deq);
	s.solve_all_boards();

	return 0;
}