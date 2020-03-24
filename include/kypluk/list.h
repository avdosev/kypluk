#pragma once

#include "algorithm.h"
#include "define.h"
namespace kypluk {
	
template <class type>
class  List {
    private:
		struct Node;
        class ListIterator;

        friend struct Node;
        friend class ListIterator;
        
		Node * head;
        
		template <class swap_type>
		friend void swap(List<swap_type>& raz, List<swap_type>& dva);
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


        void push_back(const type& value) {
            insert(end(), value);
        }
        
        void pop_back() {
        	erase(--end());	
		}

        void push_front(const type& value) {
            insert(begin(), value);
        }
        
        void pop_front() {
        	erase(begin());
		}

        Iterator insert (Iterator input, const type& value, uint size = 1) {
            Node* node = input.node;
            for (uint i = 0; i < size; i++) {
                node->back->next = new Node(value, node->back ,node->back->next);
                node->back = node->back->next;
            }

            return --input;
        }

        Iterator erase(Iterator delet) {
            Node* node = delet.node;
            Node* next = this->end().node;

            if (node->next != node || node != head) {//���� �������� �� ���� ���� �� ��� ����
                next = node->back->next = node->next;
                node->next->back = node->back;
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
        
        Iterator mid() const {
			auto start = this->begin(), finish = --this->end();
			auto pred_start = start;
			while (start != finish && pred_start != finish) {
				pred_start = start;
				start++;
				finish--;
			}
			return finish;
		}

        type& front() const {
            return *begin();
        }

        type& back() const {
            return *(--end());
        }

        uint size() const {
            return distance(begin(), end());
        }
        
        bool empty() const {
			return head->next == head || head->back == head;
		}
		
		type& at(size_t index) {
			auto it = begin();
			while (index--) 
				++it;
			return *it;
		}
		
		const type& at(size_t index) const {
			auto it = begin();
			while (index--) 
				++it;
			return *it;
		}

        void clear() {
            while(!empty()) {
                erase(begin());
            }
        }

        void splice(Iterator pos, List &other) {
            splice(pos, *this, other.begin(), other.end());
        }

        void splice(Iterator pos, Iterator it) {
            //���� ���
            splice(pos, *this, it, Iterator(it.node->next));
        }

        void splice(Iterator pos, Iterator first, Iterator last) {
            //���� ���������� �� ���������� �����
            //�� �� �� ��� ����� ������� ��������� ��� ���� ���� ������ ������ �� � �� ��� ���
            //��� �� � ������� ��� �� ������ ������� ����� ������ ���
            //� ������ ��� �������������� ���������� // ��� ����� ������ �����
            
            //��������� ��������� ��� ���������� ��������
            Node *node_start = first.node, *node_stop = (--last).node;

            //����������� �� �����
            node_stop -> next -> back = node_start -> back;
            node_start -> back -> next = node_stop -> next;
            //������� � ����
            Node* pred_node_insert = pos.node;
            node_stop->next = pred_node_insert;
            node_start->back = pred_node_insert->back;
            pred_node_insert->back->next = node_start;
            pred_node_insert->back = node_stop;

        }

        void merge(List & other) {
            for (auto it = begin(), in = other.begin(); in != other.end();) {
                if (*in < *it || it == end()) {
                    splice(it, other, in++);
                } else if (it != end()) {
                    ++it;
                }
            }
        }

		//FIX MEE PLEASE
        void sort() {
            /*if (_size <= 1) return;
            elif (_size == 2) {
                if (back() < front())
                    swap(back(), front());
                return;
            }
            List puk;
            auto tit = begin();
            uint ps = 0;
            while (ps != (_size/2)) {
                ++tit;
                ++ps;
            }

            puk.splice(puk.begin(), *this, tit, end());
            puk.sort();
            this->sort();

            this->merge(puk);*/
        }

        void reverse() {
            for (auto it = begin(); it != end(); --it) {
                swap(it.node->next, it.node->back);
            }
            swap(head->next, head->back);
        }

        ~List() {
            clear();
        }

        List & operator = (const List& copy) {
            this->clear();
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

        Node(const type& value, Node* back, Node* next) {
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
            auto tempN = this->node;
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

	template <class type>
	void swap(List<type>& raz, List<type>& dva) {
		swap(raz.head, dva.head);
	}

}
