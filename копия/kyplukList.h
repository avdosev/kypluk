#ifndef _kypluklist_H_
#define _kypluklist_H_

#include <cstdlib>
#include "kyplukFunction.h"

/*
ну че, пацаны, документация?

freenode - освобождает память от нода

createnode - создает нод

poisk_elementa - начинается поиск элемента от нулевого либо последнего использованного 
				полученная ссылка становится последней использованной 
				нет возможности получить нулл
iterator - 
addnode - создает нод после индекса 
	пример введя индекс 7 появится восьмой нод если того небыло
*/

//охохо соло леарн впервые помог
template <class type>
class  List {
	private:
		struct node {	
				node *next; //8! байт здесь что то не так//все так, как бы мне не было от этого грустно
				//node *back;
				/*
				идея не нова
				но если я сделаю замкнутый массив то будет быстрее
				но память!
				память 8(!) байт дополнительной памяти
				все оч не просто
				и да, в след комментарии будет написано, что все изи, просто я в этот момент тупее чем следующем
				*/
				//бля все наебка, чел сверху пиздит, я стал тупее( 
				type znach;
				
		};
		
		int razmer=1;
		
		node *massiv; //самый первый элемент он должен существовать всегда
		
		node *posledniy_yspolzovannuy_element=NULL; //короче, он хранит ссылку на последний элемент к которому обращались
		int posledniy_index=0;
		
		//освобождение памяти для других элементов
		inline void freenode(node* deleted) {
			delete deleted;
		}
		
		//из названия думаю ясно
		inline node* createnode() {
			return new node;
		}
		
		//поиск элемента из начала в конец
		//обращение к последнему элементу медленнее чем к первому на номер элемента раз, хех
		//стало чуточку быстрее
				
		node* poisk_elementa(int index) {
			node *puk=massiv;
			int posledindex = 0;

			if (index>razmer-1) index=razmer-1;
			
			if (index>posledniy_index and posledniy_index>0) {
				puk=posledniy_yspolzovannuy_element;
				posledindex=posledniy_index;			
			}
			
			puk=iterator(index-posledindex, puk);
			
			if (index!=0 and puk->next!=NULL) {
				posledniy_index=index;
				posledniy_yspolzovannuy_element=puk;
			}
			
			return puk;
		}
		
		//итератор итерирует пока не до итерируется до итерированного значения либо до значения ссылающееся на нул
		node* iterator(int kol_vo, node* skakogo) {
			node *puk=skakogo;
				
			for (int b=0; b<kol_vo && puk->next!=NULL; b++) {
				puk=puk->next;
			}
			
			return puk;
		}
		
		//Добавление объекта в связанный список
		/*
		охохо
		я дошел до сюдава
		осталось реализовать совсем чучуть
		и можно будет переходить к операторам
		аххааха операторы осталось только их придумать
		*/
		/*
		такс суть идеи
		мы получаем индекс после которого должны вставить нод
		ох
		думаю лучше всего будет если ...
		нод будет создан
		запоминаем ссылку нода на номмер инекса
		меняем ссылку на ссылку созданного нода
		ссылку созданого нода мы ставим как запомненую ссылку
		*/
		void addnode(int index) {
			node *nodeindex = poisk_elementa(index);
			node *nodesled =  nodeindex->next; //вылетает при значении индекс больше размера тк нодиндекс получает нул(орнул) //больше не вылетает ПС поиск почти доведен до идеала
			nodeindex->next = createnode();
			nodeindex->next->next = nodesled;
		}
	public:
		
		
		//Добавление объектов в связанный список
		/*
		такс суть идеи
		мы получаем индекс после которого должны вставить нод
		ох
		думаю лучше всего будет если ...
		*/
		void add_neskolko(int index,int kolvo_element) {
			for (int i=0; i<kolvo_element; i++) {
				addnode(index);
				razmer++;
			}
		}
		
		//добавление в конец
		void add_last(type znachenie) {	
			node *raz = poisk_elementa(razmer-1);
			raz->next = createnode();
			raz->next->next = NULL;
			raz->next->znach = znachenie;
			razmer++;
		}
		
		//в середину
		void add_middle(int index, type znachenie) {
			add_neskolko(index, 1);	
			node *raz = poisk_elementa(index+1);
			raz->znach = znachenie;
		}
		
		//перестановка
		/*
		получаем есть три ссылки или четыре
		должны вставить ссылки
		я запутался
		*/
		void perestanovka(int s_kakogo, int kyda, int kolvo_element) {
			//хех, теперь нет
			if (s_kakogo==kyda) {
				throw 1;
				return;
			}
			else { 
				int temp = s_kakogo-kyda;
				if ((temp<0 ? -temp : temp) < kolvo_element) {
					throw 2;
					return;
				}
				else if (kolvo_element<1) {
					throw 0;
					return;
				}
			}
			
			
			
			node *kkyda = poisk_elementa(kyda);
			node *skakogo = poisk_elementa(s_kakogo-1);
			
			//zamenit li na iterator xmm
			//хз либо да либо нет 
			//заменять в зависимости от сутиуации
			//node *dokakogo = poisk_elementa(s_kakogo+kolvo_element-1);
			node *dokakogo = iterator(kolvo_element, skakogo);
			node *puk = dokakogo->next;
			
			//я сам не понимаю как это работает но это заработало после получаса перебора
			//было легко(нет, она вылетает)
			//см начало функции
			dokakogo->next = kkyda->next;
			kkyda->next = skakogo->next;
			skakogo->next = puk;
			
			//поверь это необходимо 
			//posledniy_index=kyda+kolvo_element;
			
			//я запутался либо то либо это хз
			//posledniy_index=kyda;
			posledniy_index=s_kakogo-1+kolvo_element;
			return;
		}
		
		//всякая хрень не достойная многострочного коментария
		int size() {
			return razmer;
		}
		int sizebyte() {
			return razmer*sizeof(node);
		}
		int sizefull() {
			return (razmer)*sizeof(node)+sizeof(List);
		}
				
		//Удаление объектов из списка
		/*
		в чем идея?
		сначала берем индекс и меняем ссылку(предварительно сохранив) на адрес следующего не удаляемым нодом
		по сути вроде бы все
		не так ли?
		я думаю будет лучше осободить память
		но лучше не значит быстре ведь так?
		не знаю возможно
		*/
		
		void delet (int index, int kolvo_element) {
			//вычисление удаляемого
			if (index+kolvo_element>razmer-1) {
				kolvo_element=razmer-index-1;
			}
			
			
			node *prednode = poisk_elementa(index);
			node *slednode = prednode->next;
			
			
			node *poslednode = poisk_elementa(index+kolvo_element+1);
			posledniy_index=-1;
			
			prednode->next=poslednode;
			for (int i=index; i<kolvo_element or prednode==NULL; i++) {
				prednode = slednode;
				slednode = slednode->next;
				freenode(prednode);
			}
			posledniy_index-=kolvo_element;
			razmer-=kolvo_element;
		}
		
		 /*
		 настало самое сложное - операторы
		 счего начать
		 что делать
		 хз
		 */
		 	
		//я представил
		/*
		было трудно
		но благо я вспомнил про  этот значок &
		хех не думал что будет так просто
		*/
		type & operator [](int H) {
			node *puk = poisk_elementa(H);
			return puk->znach;
		}
		//пока не могу представить реализацию такю же простоую как и массив,
		//чтобы разницы небыло заметно
		//изи
		//смотри курлыкаррау
		/*
		бля, изи не было
		походу во мне потух тот огонек радости( 
		*/
		
		//он должен формировать отдельный массив
		type * const to_arr() {
			type * mas = new type [razmer];
			for (int i=0; i<razmer; i++)
				mas[i]=(*this)[i];
			return mas;
		}
		
		void sort(bool vozrastanie) {
			Sort(*this, razmer, vozrastanie, (*this)[0]);
		}
		
		//создается список указаного изначально размера
		List(unsigned int size=1) {

			massiv = createnode();
			massiv->next = NULL;
			
			//все это заменяется на add(1,iznachalnuy_razmer-2) //но я пока хз как //изи
			if (size>1) add_neskolko(0,size-1);
			//for (int i=1; i<iznachalnuy_razmer; i++) {				
			//	puk->next = createnode();
			//	puk=puk->next;
			//	puk->next = NULL;
			//	cout << i << endl;		
			//}			
		}
		
		//уничтожает список, ухххх, пишу комент до того как придумал реализацию
		//такc
		/*
		думаю сначала мы переходим на первый элемент
		потом запоминаем ссылку на следующий
		удаляем этот
		переходим на след. и так пока мы не осободим всю память
		охохо
		на словах все легко надеюсь в реале так и будет, потому что компилятор уже показывает на две возхможные утечки памяти, а ведь это только начало. 
		Что ждеt меня впереди? Модификация третьей лабы? Возможно. Kонец этого класа - хз
		*/
		/*
		хех модификация
		гораздо сложнее это то что если я посылаю в функцию список 
		то при окончании функции вызывается деструктор класса 
		*/
		/*хыыыы
		я тупой овощ
		как же я был глуп
		я понял как решить проблему с дструктором
		но не понял как её избежать(
		*/
		void full_delete() {
			node *puk = massiv->next;
			freenode(massiv);
			if (puk!=NULL) {
				while (puk->next!=NULL) {
					node* sled_element = puk;
					puk = puk->next;				
					freenode(sled_element);
				}
				freenode(puk);
			}
		}
		
		~List() {
			//хз должно помочь
			full_delete();
		}

};

#endif
