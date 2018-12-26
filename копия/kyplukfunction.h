#ifndef _kyplukfunction_H_
#define _kyplukfunction_H_

#include <fstream>
#include <iostream> //ne ydalyau  bez etogo ne rabotaet pover mne
#include <cstdlib>
#include <cstring>
#include <ctime>

#include "kyplukOSfunction.h"

using namespace std;

void * memcopy( void * destptr, const void * srcptr, size_t num ) {
	char * xranilishe = new char [num];
	memcpy(destptr, memcpy(xranilishe, srcptr, num), num);
	//psss tak bustree хех
	//strncpy((char *)destptr, strncpy(xranilishe, (char *)srcptr, num), num);
	delete[] xranilishe;
}
template <class type, class type2>
unsigned int binary_poisk(type massiv, bool vozrastanie, unsigned int left,unsigned int right, type2 znach) {
	int mid_index=(right-left)/2+left;
	if (mid_index==left) {throw 0; return 0;}
	if (massiv[mid_index]>znach)
	{
		return !vozrastanie ? binary_poisk(massiv, vozrastanie, mid_index, right, znach) : binary_poisk(massiv, vozrastanie, left, mid_index, znach);
	}
	else if (massiv[mid_index]<znach)
	{
		return !vozrastanie ? binary_poisk(massiv, vozrastanie, left, mid_index, znach) : binary_poisk(massiv, vozrastanie, mid_index, right, znach);
	}
	else
	{
		return mid_index;
	}	
}
 
template <class type, class type2>
void Qsort(type mas, int left, int right, type2 puk) {
    //Указатели в начало и в конец массива
    int i = left;
    int j = right;
 
    //Центральный элемент массива
    type2 mid = mas[(i+j)/2];
 
    //Делим массив
    while (i <= j) {
        //Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
        //В левой части массива пропускаем(оставляем на месте) элементы, которые меньше центрального
        while(mas[i] < mid) /*mas[i] < mid*/
        {
		    i++;
        }
        //В правой части пропускаем элементы, которые больше центрального
        while (mas[j] > mid) /*mas[j] > mid*/ 
        {
		    j--;
        }
 
        //Меняем элементы местами
        if (i <= j) {
            type2 tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;
 
            i++;
            j--;
        }
    }
 
    //Рекурсивные вызовы, если осталось, что сортировать
    if(j > left) {
        //"Левый кусок"
        Qsort(mas, left, j, mas[0]);
    }
    if (i < right) {
        //"Прaвый кусок"
        Qsort(mas, i, right, mas[0]);
    }
}

template <class type3, class type4>
void Rsort (type3 mas, int size, type4 puk)
{
	type4 temp;
	for(int i=0; i<size/2; i++) {
		temp=mas[i];
		mas[i]=mas[size-i];
		mas[size-i]=temp;
	}
}

template <class type5, class type6>
void Sort(type5 mas, int size, bool vozrastanie, type6 puk) {
	size--;
	Qsort(mas, 0, size, puk);
	
	if (!vozrastanie) {
		Rsort(mas, size, puk);
	}
}

bool proverka_na_nalichie (string proveryaemoe, string proverochnoe, short int procentoe_nalichie) {
	int maxsovpadenie=0, sovpadenie=0; 
	for (int i=0; i<proveryaemoe.length(); i++) {
		if (proveryaemoe[i] == proverochnoe[0]) {
			for (int j=0; j<proverochnoe.length(); j++) {
				if (proveryaemoe[i+j] == proverochnoe[j]) {
					sovpadenie++;
				}
			}
			if (sovpadenie>maxsovpadenie) {
				maxsovpadenie=sovpadenie;
			}
			sovpadenie=0;
		}
	}
	if ((maxsovpadenie*100/proverochnoe.length())>=procentoe_nalichie) 
		return true;
	return false;
}

#endif
