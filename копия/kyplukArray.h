#ifndef _kyplukarray_H_
#define _kyplukarray_H_

#include <cstdlib>
#include "kyplukFunction.h"

/*
в чем пРИКол?
короче
это моя реализация вектора и иже с ними
пока не придумал чего то интересного
*/
template <class type>
void Sort(type masiv, int size, bool vozrastanie);
template <class type>
class  Array {
	private:
		type * massiv;
		int razmer=1;
		int real_razmer=1;
		
		void pererozdenie() {
			real_razmer = (real_razmer * 3)/2 + 1;
			type * ret = new type[real_razmer];
			memcpy(ret, massiv, razmer*sizeof(type));
			full_delete();
			massiv=ret;
		}
		
		inline void proverka(int plus_size) {
			while (razmer+plus_size > real_razmer)
				//then пересоздание того массива
				pererozdenie();
		}
	public:
		
		Array(unsigned int size=1) {
			massiv = new type[size];
			razmer=size;
			real_razmer=size;
		}
		
		~Array() {
			full_delete();
		}
		
		//если расширение больше не требуется
		//void trimToSize();
		//Если заранее известно, сколько элементов следует хранить, то перед заполнением массива вызовите метод 
		//void ensureCapacity();
		
		//Добавление в начало
		void add_first(type znachenie) {
			proverka(1);
			memcpy(massiv+1, massiv, sizeof(type)*razmer);
			massiv[0]=znachenie;
			razmer++;
		}
		//Добавление в конец
		void add_last(type znachenie) {
			proverka(1);
			massiv[razmer]=znachenie;
			razmer++;
		}
		//Добавление в середину
		void add_middle(int index, type znachenie) {
			proverka(1);
			add_neskolko(index, 1);
			massiv[index]=znachenie;
			razmer++;
		}
		
		void add_neskolko(int index,int kolvo_element)
		{
			proverka(kolvo_element);
			razmer+=kolvo_element;
			memcpy(massiv+index+kolvo_element, massiv+index, (razmer-(index+kolvo_element))*sizeof(type));
		}
		/*
		хмм
		здесь не все так просто как мне показалось на перввый взгляд
		блэд, так везде
		*/
		void perestanovka(int s_kakogo, int kyda, int kolvo_element)
		{
			//s_kakogo++; 
			if (s_kakogo==kyda) {
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
			
			unsigned long long int kolvo_byte = kolvo_element*sizeof(type);
			proverka(kolvo_element);
			
			if (kyda>s_kakogo) {//куда правее
				
				memcpy(massiv+kyda+kolvo_element, massiv+kyda, (razmer-(kyda))*sizeof(type)); //освобождаем пространтсво для перемещения
				
				memcpy(massiv+kyda, massiv+s_kakogo, kolvo_byte); //делаем перестановку
				
				memcpy(massiv+s_kakogo, massiv+s_kakogo+kolvo_element, (razmer-(s_kakogo))*sizeof(type)); //смещаем влево
			}
			else {//с какого правее
				type xranilishe[kolvo_element];//подготовка
				memcpy(xranilishe, massiv+s_kakogo, kolvo_byte);
				
				memcpy(massiv+s_kakogo, massiv+s_kakogo+kolvo_element, (razmer-(s_kakogo+kolvo_element))*sizeof(type));
				
				memcpy(massiv+kyda+kolvo_element, massiv+kyda, (razmer-kyda)*sizeof(type));//освобождение пространства
				memcpy(massiv+kyda, xranilishe, kolvo_byte);//перестановка
			}
		}
		
		//Удаление по индексу
		//void delet(int index) {
		//delet(index, 1);
		//лел, зочем создавать две функции если в их склете одно и тоже, ни кто же не будет создовать две версии одного и того же, говоря что оно различается, да Бог?
		/*
		только что посмотрел как я все это реализовывал в списке....
		я этого не реализовывал....
		кто уменее? я сейчас или я из прошлого, который реализовал одну функцию
		хмм
		поступлю также как и я, но какой я?
		*/
		void delet(int index, int kolvo_element) {
			if (kolvo_element <= 0) return;
			if (razmer-(index+kolvo_element) < 0)
			{
				kolvo_element = razmer - index - 1;
				if (kolvo_element <= 0)
				{
					int na_v_ebalo = 0;
					throw na_v_ebalo;
					return;
				}
					
			}
			
			memcpy(massiv+index, massiv+index+kolvo_element, (razmer-(index+kolvo_element))*sizeof(type));
			razmer-=kolvo_element;
			//в идеале здесь должна быть проверка на выход знаечений за пределы массива
			//но кого это волнует
			//зочем мне с этим париться
			//сверху пиздел пидор за которым мне пришлось убирать говно из падика
		}
		
		inline type & operator [](int H) {
			return massiv[H];
		}
		
		Array & operator = (Array & puk) {
			real_razmer = puk.size();
			razmer = puk.size();
			
	    	type * buffer = new type [razmer];
	    	memcpy( buffer, puk.massiv, razmer * sizeof(type));
	    	
	    	this->full_delete();
	    	
	    	this->massiv = new type [razmer];
	    	
	    	memcpy(this->massiv, buffer, razmer * sizeof(type));
	    	
			return *this; 
	    }
		
		void full_delete() {
			delete[] massiv;
		}
		
		void sort(bool vozrastanie) {
			Sort(*this, razmer, vozrastanie, (*this)[0]);
		}
		
		type * to_arr() {
			return massiv;
		}
		
		int size() {
			return razmer;
		}		
		int sizebyte() {
			return real_razmer*sizeof(type);
		}
		int sizefull() {
			return (real_razmer)*sizeof(type)+sizeof(Array);
		}
};

#endif
