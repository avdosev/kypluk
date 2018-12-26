#ifndef _kyplukAlgorithm_H_
#define _kyplukAlgorithm_H_

#include <kyplukDefine.h>
#include <kyplukIterator.h>

template <class type>
void swap (type& raz, type& dva) {
	type temp = raz;
	raz = dva;
	dva = temp;
}

template <class type>
void xor_swap (type& raz, type& dva) {
	if (&raz == &dva) return;
	
	raz ^= dva;
	dva ^= raz;
	raz ^= dva;
}

template <class type>
int compare (const type& raz, const type& dva)
{
	if (raz > dva)
		return 1;
	elif (raz < dva)
		return -1;
	else
		return 0;
}

/*
универсальная функция копирования подходящая для всех контейнеров
проверка на выход за границы которых не производится
dest входит и выходит
source только входит
size размер копирования
start`s начальные индексы для контейнеров
*/
template <class cont_one, class cont_two, class type>
type & copy(cont_one & dest, const cont_two & source, Size_t size, Size_t start_src = 0, Size_t start_dest = 0) {
	type * storage = new type [size];
	for (auto i = 0; i < size; i++)
	{
		 storage[i] = source[i + start_src];
	}
	for (auto i = 0; i < size; i++)
	{
		dest[i + start_dest] = storage[i];
	}
	delete[] storage;
	return dest;
}

/*
бинарный поиск
right - size или место +1 до которого идет поиск
left = 0 или то место от которого идет поиск
*/
template <class type, class type_element>
int binary_search(const type& mas, type_element znach ,int left, int right, int ( * comparator ) (const type_element , const type_element)) {
	
	while (left < right)
	{
		int mid_index=(right-left)/2+left;
		int cmp = comparator(znach, mas[mid_index]);
		if (cmp > 0) {
			left = mid_index + 1;
		}
		elif (cmp < 0) {
			right = mid_index;
		}
		else {
			while (!comparator(znach, mas[mid_index-1]) and mid_index!=0) mid_index--;
			return mid_index;
		}
	}
	
	return -1;
}
 
template <class type, class type_element>
void Qsort(type& mas, int left, int right, int ( * comparator ) (const type_element& , const type_element&)) {
    //Указатели в начало и в конец массива
    int i = left;
    int j = right;

    //Центральный элемент массива
    type_element mid = mas[(i+j)/2];
    
    //Делим массив
    while (i <= j) {
        //Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
        //В левой части массива пропускаем(оставляем на месте) элементы, которые меньше центрального
        while (comparator(mas[i], mid) < 0) /*mas[i] < mid*/
        {
		    i++;
        }
        //В правой части пропускаем элементы, которые больше центрального
        while (comparator(mas[j], mid) > 0) /*mas[j] > mid*/ 
        {
		    j--;
        }
 
        //Меняем элементы местами
        if (i <= j) {
            swap(mas[i], mas[j]);
            i++;
            j--;
        }
    }
 
    //Рекурсивные вызовы, если осталось, что сортировать
    if(j > left) {
        //"Левый кусок"
        Qsort(mas, left, j, comparator);
    }
    if (i < right) {
        //"Прaвый кусок"
        Qsort(mas, i, right, comparator);
    }
}

template <class type_cont>
void reverse (type_cont & mas, int size)
{
	for (int i = 0; i < size/2; i++)
	{
		swap(mas[i], mas[size-i-1]);
	}
}

#endif
