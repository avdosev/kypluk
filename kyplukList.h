#ifndef _kypluklist_H_
#define _kypluklist_H_

#include <kyplukAlgorithm.h>
#include <kyplukDefine.h>
namespace kypluk {
	
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
        
        void pop_back() {
        	erase(--end());	
		}

        void push_front(type value) {
            insert(begin(), value);
        }
        
        void pop_front() {
        	erase(begin());
		}

        /**
         * @brief insert - 	��������� ��������
         * @return Iterator �� ����������� �������
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

            if (node->next != node || node != head) {//���� �������� �� ���� ���� �� ��� ����
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

        type& front() const {
            return *begin();
        }

        type& back() const {
            return *(--end());
        }

        uint size() const {
            return _size;
        }
        
        bool is_empty() const {
			return head->next == head || head->back == head;
		}
		
		type& at(Size_t index) {
			auto it = begin();
			while (index--) 
				++it;
			return *it;
		}
		
		const type& at(Size_t index) const {
			auto it = begin();
			while (index--) 
				++it;
			return *it;
		}

        void clear() {
            while(_size) {
                erase(begin());
            }
        }

        void splice(Iterator pos, List &other) {
            splice(pos, *this, other.begin(), other.end());
            if (&other != this) {
                this->_size += other.size();
                other._size = 0;
            }
        }

        void splice(Iterator pos, List& other, Iterator it) {
            //���� ���
            splice(pos, *this, it, Iterator(it.node->next));
            if (&other != this) {
                other._size--;
                this->_size++;//aaaaa, ������� �� �� ����� ���������� ��������� ����
            }
        }

        void splice(Iterator pos, List& other, Iterator first, Iterator last) {
            //���� ���������� �� ���������� �����
            //�� �� �� ��� ����� ������� ��������� ��� ���� ���� ������ ������ �� � �� ��� ���
            //��� �� � ������� ��� �� ������ ������� ����� ������ ���
            //� ������ ��� �������������� ����������
            if (this == &other) {
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
            else {//���� �������� �� ������
                while (first != last) {//FIX ME
                    //��������� ��������� ��� ���������� ��������
                    Node *node = first.node;
                    first = Iterator(first.node->next);
                    //����������� �� �����
                    node -> next -> back = node -> back;
                    node -> back -> next = node -> next;
                    other._size--;
                    //������� � ����
                    Node *pred_node_insert = pos.node;
                    node->next = pred_node_insert;
                    node->back = pred_node_insert->back;
                    //pos.node = node;//3 ������ ��������� //������ 10 ����� ��������� � ����� ��� ��� ����������
                    pred_node_insert->back->next = node;
                    pred_node_insert->back = node;//������ ����
                    _size++;
                }
            }
        }

        void merge(List & other) {
            for (auto it = begin(), in = other.begin(); in != other.end();) {
                if (*in < *it || it == end()) {
                    splice(it, other, in++);
                } elif (it != end()) {
                    ++it;
                }
            }
        }

        void sort() {
            if (_size <= 1) return;
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

            this->merge(puk);
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

}

#endif
