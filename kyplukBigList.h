#ifndef _kypluk_BigList_h_
#define _kypluk_BigList_h_

#include <kyplukDefine.h>
#include <kyplukIterator.h>

template <class type>
class BigList {
	private:
		Size_t _size = 0;
		class Node {
			public:
				/*
				(2(?)*sizeof(void*))/((k-1)*sizeof(type)) + ?
				к - коэфицент увеличения объема при плюсовании размера указателей от размера типа данных
				точно не уверен какой должен быть коэфицент поэтому во избежание чего либо угодна решил что 1.5 это достаточно не плохой вариант
				+ 1 нужен для точной уверенности что это будет не пустой массив
				и да я не пытаюсь уйти от О(н) сложности доступа к произвольному элементу
				я пытаюсь уйти от роста занимаемой памяти для маленьких типов данных из-за размера указателя (это четко поставленнная цель и она четко выполняется)  
				k Не должен быть больше 2 и меньше 1
											         perfect
											            |
											            |
											           \*/
				static const Size_t size_block = (3*sizeof(void*))/((1.5-1)*sizeof(type)) + 1;
				type znach[size_block];
				Node * next;
				
				Node(Node * finaly = NULL)
				{
					next = finaly;
				}
				
				Node * node_create(Size_t otr = 1, Node * finaly = NULL) {
					Node * otrnext = this;
					if (this.next != NULL) throw 0;//xmm
					for (Size_t i = 0; i < otr; i++)
					{
						otrnext->next = new Node;
						otrnext = otrnext->next;
					}
				}
				
				~Node() {
					Node * nextdelete = next, * nextnod = next;
					
					while (nextnod != NULL)
					{
						nextdelete = nextnod;
						nextnod = next->next;
						nextdelete -> next = NULL;
						delete nextdelete;
					}
				}
				
				type & at(Size_t H) {
					if (H > size_block) throw 0;
					return znach[H];
				}
		};
		
		//mega fix 
		class BigListIterator : public Iterator<type> {
			private:
				friend class BigList;
				friend class Node;
				const BigList * list;
				Node * iter;
				Size_t i = 0;//fix this
			public:
				BigListIterator(Node * startiter, const BigList * uk) {
					iter = startiter;
					list = uk;
				}
				
				type& operator * () {
					return iter->at(i);
				}
				
				const type& operator * () const {
					return iter->at(i);
				}
				
				const BigListIterator & operator ++ () {//prefix
					if (iter != NULL) {
						if ((iter == list->list.head.node and i+1 >= list->list.head.fullness)
							or (iter == list->list.end.node and i+1 >= list->list.end.fullness) 
							or (i+1 >= Node::size_block) 
							) 
						{
							iter = iter->next;
							i = 0;
						}
						else 
							i++;
					}
					return *this;
				}

				const BigListIterator & operator = (const BigListIterator& puk) {
					if (this != &puk) {
						list = puk.list;
						iter = puk.iter;
						i = puk.i;
					}
					return *this;
				}
				bool operator != (const BigListIterator& puk) {
					return this->iter != puk.iter or this->i != puk.i;
				} 
		};
		
		struct { struct { union { Size_t insert = 0, fullness;} ; Node * node = NULL; } end, head; } list;
		
		void create_end_node() {
			list.end.insert = 0;
			if (list.end.node != NULL)
				list.end.node = list.end.node->next = new Node(list.end.node->next);
			else
				create_start_node();
		}
		
		void create_start_node() {
			list.head.fullness = 0;
			list.head.node = new Node(list.head.node);
			if (list.end.node == NULL) list.end.node = list.head.node;
		}
	public:
		
		BigList(Size_t size = 0) {
			add_neskolko_to_the_end_or_start(size, true);
		}
		
		BigList(const BigList &copy) {
			this->copy(copy);
		}
		
		~BigList() {
			clear();
		}
		
		//Добавление в начало
		void add_first(type znach) 
		{
			//выясняем количество нодов
			//и выполняем определнные действия в зависимости от них
			if (list.head.node == NULL or list.head.fullness >= Node::size_block)//дитовкин отпиздил бы меня за это (особенно за последнее выражение), но я не литовкин и знаю что в си используются ленивые вычисления позволяющие мне проворачивать подобные костыли не думая о проверках
				create_start_node();
				
			if (list.head.node->next == NULL)
				list.end.insert++;
			
			for (Size_t i = list.head.fullness; i > 0; i--) {
				list.head.node->znach[i] = list.head.node->znach[i-1];
			}
			list.head.node->at(0) = znach;
			list.head.fullness++;
			_size++;
		}
		
		//Добавление в конец
		void add_last(type znach) 
		{
			if (list.head.node == NULL)
				create_start_node();
			if (list.head.node->next == NULL)
				list.head.fullness++;
			if (list.end.fullness >= list.end.node->size_block)
				create_end_node();
			list.end.node->at(list.end.insert) = znach;
			list.end.insert++;
			_size++;
		}
		
		void add_neskolko_to_the_end_or_start(Size_t size, bool switch_adding) {
			if (switch_adding) {//end
				if (list.head.node != NULL and list.end.fullness < Node::size_block) {
					size -= (Node::size_block - list.end.fullness);
					if (list.head.node->next == NULL) list.head.fullness = Node::size_block;
				}
				
				for (Size_t i = 0; i < size/Node::size_block; i++)
					create_end_node();
					
				list.end.fullness = size % Node::size_block;
				
			}
			else {//start
				if (list.head.node != NULL and list.head.fullness < Node::size_block) {
					size -= (Node::size_block - list.head.fullness);
					if (list.head.node->next == NULL) list.end.fullness = Node::size_block;
				}
				for (Size_t i = 0; i < size/Node::size_block; i++)
					create_start_node();
					
				list.head.fullness = size % Node::size_block;
			}
		}
		
		void clear() {
			if (list.head.node != NULL)
			{
				delete list.head.node;
				list.head.node = NULL; list.head.fullness = 0;
				list.end.node = NULL; list.end.fullness = 0;
			}
			_size = 0;
		}
		
		void copy(const BigList &copy) {
			if (this != &copy) // если кто-то напишет "a = a;", лучше всего ничего не делать
		    {
				clear();
				for (auto i = copy.begin(); i != copy.end(); ++i)
					add_last(*i);
				_size = copy.size();
			}
		}
		
		Size_t size() const {
			return _size;
		}
		
		BigListIterator begin() const {
			return BigListIterator(list.head.node, this);
		}
		
		BigListIterator end() const {
			return BigListIterator(NULL, this);
		}
		
		BigList & operator = (const BigList & puk) {
			this->copy(puk);
			return *this;
		}
};

#endif
