#ifndef _kypluklist_H_
#define _kypluklist_H_

#include <kyplukAlgorithm.h>
#include <kyplukDefine.h>

template <class type>
class  List {
	private:
		struct Node;
		class ListIterator;

		friend struct Node;
		friend class ListIterator;

		Node * head;
		uint _size = 0;

	public:
		using Iterator = ListIterator;

		List() {
			head = new Node();
		}

		List(const List& c) {
			head = new Node();
			for (auto item : c) {
				push_back(item);
			}
		}

		template <class ConstIterator>
		List(ConstIterator begin, ConstIterator end) {
			head = new Node();
			for_each(begin, end, [this](const type& item){
				this->push_back(item);
			});
		}

		List(uint count, const type& value = type()) {
			head = new Node();
			for (uint i = count; i--; this->push_back(value));
		}


		void push_back(type value) {
			insert(end(), value);
		}

		void push_front(type value) {
			insert(begin(), value);
		}

		/**
		 * @brief insert - 	Вставляет элементы
		 * @return Iterator на вставленный элемент
		 */
		Iterator insert (Iterator input, type value, uint size = 1) {
			Node* node = input.node;
			for (uint i = 0; i < size; i++) {
				node->back->next = new Node(value, node->back ,node->back->next);
				node->back = node->back->next;
			}
			_size += size;

			return --input;
		}

		Iterator erase(Iterator delet) {
			Node* node = delet.node;
			Node* next = this->end().node;

			if (node->next != node && node != head) {//если осталось не одна нода то все норм
				next = node->back->next = node->next;
				node->next->back = node->back;
				_size--;
				delete node;
			}

			return Iterator(next);

		}

		Iterator begin() const {
			return Iterator(head->next);
		}

		Iterator end() const {
			return Iterator(head);
		}

		type front() {
			return *begin();
		}

		type back() {
			return *(--end());
		}

		uint size() const {
			return _size;
		}

		void clear() {
			while(_size) {
				erase(begin());
			}
		}

		void splice(Iterator pos, List &other) {
			splice(pos, *this, other.begin(), other.end());
			other._size = 0;
		}

		void splice(Iterator pos, List& other, Iterator it) {
			//тупа хак
			splice(pos, *this, it, Iterator(it.node->next));
			other._size--;
		}

		void splice(Iterator pos, List& other, Iterator first, Iterator last) {
			//если накосячить то образуется петля
			//но мы же все знаем топовые алгоритмы для того чтоб понять попали мы в неё иль нет
			//так шо я оставлю все на кодера который будет писать код
			//и назову ето неопределенным поведением
			if (this == &other) {
				//сохраняем указатель для дальнейших действий
				Node *node_start = first.node, *node_stop = (--last).node;

				//выкидывание из листа
				node_stop -> next -> back = node_start -> back;
				node_start -> back -> next = node_stop -> next;
				//вставка в лист
				Node* pred_node_insert = pos.node;
				node_stop->next = pred_node_insert;
				node_start->back = pred_node_insert->back;
				pred_node_insert->back->next = node_start;
				pred_node_insert->back = node_stop;
			}
			else {//если списочек то другой
				while (first != last) {//FIX ME
					//сохраняем указатель для дальнейших действий
					Node *node = first.node;
					first = Iterator(first.node->next);
					//выкидывание из листа
					node -> next -> back = node -> back;
					node -> back -> next = node -> next;
					other._size--;
					//вставка в лист
					Node *pred_node_insert = pos.node;
					node->next = pred_node_insert;
					node->back = pred_node_insert->back;
					pred_node_insert->back->next = node;
					pred_node_insert->back = node;
					//pos.node = node;//3 минуты дебажинга //спустя 10 минут подправок я понел что оно реверсится
					_size++;
				}
			}
		}

		void merge(List & other) {
			for (auto it = begin(); it != end(); ++it) {

			}
		}

		void sort() {

		}

		~List() {
			clear();
		}

		List & operator = (const List& copy) {
			clear();
			for_each(copy.begin(), copy.end(), [this](const type& item){
				this->push_back(item);
			});
			return *this;
		}

};

template <class type>
struct List<type>::Node {
	type value;
	Node* next;
	Node* back;

	Node(type value, Node* back, Node* next) {
		this->value = value;
		this->next = next;
		this->back = back;
	}

	Node() {

		next = this;
		back = this;

	}

	~Node() {
		next = NULL;
		back = NULL;
	}
};

template <class type>
class List<type>::ListIterator {
	private:
		friend class List;
		using Node = List<type>::Node;
		Node * node;

	public:
		ListIterator(Node* cnode) {
			this->node = cnode;
		}

		ListIterator & operator ++ () {
			node = node->next;
			return *this;
		}

		ListIterator operator ++ (int) {
			auto tempN = this->cnode;
			++(*this);
			return ListIterator(tempN);
		}

		const ListIterator & operator = (const ListIterator& c) {
			node = c.node;
			return *this;
		}

		bool operator != (const ListIterator& c) {
			return this->node != c.node;
		}
		bool operator == (const ListIterator& c) {
			return this->node == c.node;
		}

		type & operator * () {
			return this->node->value;
		}

		const type & operator * () const {
			return this->node->value;
		}

		ListIterator & operator -- () {
			node = node->back;
			return *this;
		}

		const ListIterator operator -- (int) {
			auto tempN = this->node;
			--(*this);
			return ListIterator(tempN);
		}

};

#endif
