#ifndef _kypluklist_H_
#define _kypluklist_H_

#include <cstdlib>
#include "kyplukFunction.h"

/*
�� ��, ������, ������������?

freenode - ����������� ������ �� ����

createnode - ������� ���

poisk_elementa - ���������� ����� �������� �� �������� ���� ���������� ��������������� 
				���������� ������ ���������� ��������� �������������� 
				��� ����������� �������� ����
iterator - 
addnode - ������� ��� ����� ������� 
	������ ����� ������ 7 �������� ������� ��� ���� ���� ������
*/

//����� ���� ����� ������� �����
template <class type>
class  List {
	private:
		struct node {	
				node *next; //8! ���� ����� ��� �� �� ���//��� ���, ��� �� ��� �� ���� �� ����� �������
				//node *back;
				/*
				���� �� ����
				�� ���� � ������ ��������� ������ �� ����� �������
				�� ������!
				������ 8(!) ���� �������������� ������
				��� �� �� ������
				� ��, � ���� ����������� ����� ��������, ��� ��� ���, ������ � � ���� ������ ����� ��� ���������
				*/
				//��� ��� ������, ��� ������ ������, � ���� �����( 
				type znach;
				
		};
		
		int razmer=1;
		
		node *massiv; //����� ������ ������� �� ������ ������������ ������
		
		node *posledniy_yspolzovannuy_element=NULL; //������, �� ������ ������ �� ��������� ������� � �������� ����������
		int posledniy_index=0;
		
		//������������ ������ ��� ������ ���������
		inline void freenode(node* deleted) {
			delete deleted;
		}
		
		//�� �������� ����� ����
		inline node* createnode() {
			return new node;
		}
		
		//����� �������� �� ������ � �����
		//��������� � ���������� �������� ��������� ��� � ������� �� ����� �������� ���, ���
		//����� ������� �������
				
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
		
		//�������� ��������� ���� �� �� ����������� �� �������������� �������� ���� �� �������� ����������� �� ���
		node* iterator(int kol_vo, node* skakogo) {
			node *puk=skakogo;
				
			for (int b=0; b<kol_vo && puk->next!=NULL; b++) {
				puk=puk->next;
			}
			
			return puk;
		}
		
		//���������� ������� � ��������� ������
		/*
		�����
		� ����� �� ������
		�������� ����������� ������ ������
		� ����� ����� ���������� � ����������
		������� ��������� �������� ������ �� ���������
		*/
		/*
		���� ���� ����
		�� �������� ������ ����� �������� ������ �������� ���
		��
		����� ����� ����� ����� ���� ...
		��� ����� ������
		���������� ������ ���� �� ������ ������
		������ ������ �� ������ ���������� ����
		������ ��������� ���� �� ������ ��� ���������� ������
		*/
		void addnode(int index) {
			node *nodeindex = poisk_elementa(index);
			node *nodesled =  nodeindex->next; //�������� ��� �������� ������ ������ ������� �� ��������� �������� ���(�����) //������ �� �������� �� ����� ����� ������� �� ������
			nodeindex->next = createnode();
			nodeindex->next->next = nodesled;
		}
	public:
		
		
		//���������� �������� � ��������� ������
		/*
		���� ���� ����
		�� �������� ������ ����� �������� ������ �������� ���
		��
		����� ����� ����� ����� ���� ...
		*/
		void add_neskolko(int index,int kolvo_element) {
			for (int i=0; i<kolvo_element; i++) {
				addnode(index);
				razmer++;
			}
		}
		
		//���������� � �����
		void add_last(type znachenie) {	
			node *raz = poisk_elementa(razmer-1);
			raz->next = createnode();
			raz->next->next = NULL;
			raz->next->znach = znachenie;
			razmer++;
		}
		
		//� ��������
		void add_middle(int index, type znachenie) {
			add_neskolko(index, 1);	
			node *raz = poisk_elementa(index+1);
			raz->znach = znachenie;
		}
		
		//������������
		/*
		�������� ���� ��� ������ ��� ������
		������ �������� ������
		� ���������
		*/
		void perestanovka(int s_kakogo, int kyda, int kolvo_element) {
			//���, ������ ���
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
			//�� ���� �� ���� ��� 
			//�������� � ����������� �� ���������
			//node *dokakogo = poisk_elementa(s_kakogo+kolvo_element-1);
			node *dokakogo = iterator(kolvo_element, skakogo);
			node *puk = dokakogo->next;
			
			//� ��� �� ������� ��� ��� �������� �� ��� ���������� ����� �������� ��������
			//���� �����(���, ��� ��������)
			//�� ������ �������
			dokakogo->next = kkyda->next;
			kkyda->next = skakogo->next;
			skakogo->next = puk;
			
			//������ ��� ���������� 
			//posledniy_index=kyda+kolvo_element;
			
			//� ��������� ���� �� ���� ��� ��
			//posledniy_index=kyda;
			posledniy_index=s_kakogo-1+kolvo_element;
			return;
		}
		
		//������ ����� �� ��������� �������������� ����������
		int size() {
			return razmer;
		}
		int sizebyte() {
			return razmer*sizeof(node);
		}
		int sizefull() {
			return (razmer)*sizeof(node)+sizeof(List);
		}
				
		//�������� �������� �� ������
		/*
		� ��� ����?
		������� ����� ������ � ������ ������(�������������� ��������) �� ����� ���������� �� ��������� �����
		�� ���� ����� �� ���
		�� ��� ��?
		� ����� ����� ����� ��������� ������
		�� ����� �� ������ ������ ���� ���?
		�� ���� ��������
		*/
		
		void delet (int index, int kolvo_element) {
			//���������� ����������
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
		 ������� ����� ������� - ���������
		 ����� ������
		 ��� ������
		 ��
		 */
		 	
		//� ����������
		/*
		���� ������
		�� ����� � �������� ���  ���� ������ &
		��� �� ����� ��� ����� ��� ������
		*/
		type & operator [](int H) {
			node *puk = poisk_elementa(H);
			return puk->znach;
		}
		//���� �� ���� ����������� ���������� ���� �� �������� ��� � ������,
		//����� ������� ������ �������
		//���
		//������ �����������
		/*
		���, ��� �� ����
		������ �� ��� ����� ��� ������ �������( 
		*/
		
		//�� ������ ����������� ��������� ������
		type * const to_arr() {
			type * mas = new type [razmer];
			for (int i=0; i<razmer; i++)
				mas[i]=(*this)[i];
			return mas;
		}
		
		void sort(bool vozrastanie) {
			Sort(*this, razmer, vozrastanie, (*this)[0]);
		}
		
		//��������� ������ ��������� ���������� �������
		List(unsigned int size=1) {

			massiv = createnode();
			massiv->next = NULL;
			
			//��� ��� ���������� �� add(1,iznachalnuy_razmer-2) //�� � ���� �� ��� //���
			if (size>1) add_neskolko(0,size-1);
			//for (int i=1; i<iznachalnuy_razmer; i++) {				
			//	puk->next = createnode();
			//	puk=puk->next;
			//	puk->next = NULL;
			//	cout << i << endl;		
			//}			
		}
		
		//���������� ������, �����, ���� ������ �� ���� ��� �������� ����������
		//���c
		/*
		����� ������� �� ��������� �� ������ �������
		����� ���������� ������ �� ���������
		������� ����
		��������� �� ����. � ��� ���� �� �� �������� ��� ������
		�����
		�� ������ ��� ����� ������� � ����� ��� � �����, ������ ��� ���������� ��� ���������� �� ��� ���������� ������ ������, � ���� ��� ������ ������. 
		��� ���t ���� �������? ����������� ������� ����? ��������. K���� ����� ����� - ��
		*/
		/*
		��� �����������
		������� ������� ��� �� ��� ���� � ������� � ������� ������ 
		�� ��� ��������� ������� ���������� ���������� ������ 
		*/
		/*�����
		� ����� ����
		��� �� � ��� ����
		� ����� ��� ������ �������� � �����������
		�� �� ����� ��� � ��������(
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
			//�� ������ ������
			full_delete();
		}

};

#endif
