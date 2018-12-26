#include <iostream>
#include <kyplukarray.h>

/*
strlen(имя_строки)	определяет длину указанной строки, без учёта нуль-символа
Копирование строк
strcpy(s1,s2)	выполняет побайтное копирование символов из строки  s2 в строку s1
strncpy(s1,s2, n)	выполняет побайтное копирование n символов из строки  s2 в строку s1. возвращает значения s1
Конкатенация строк
strcat(s1,s2)	объединяет строку s2 со строкой s1. Результат сохраняется в s1
strncat(s1,s2,n)	объединяет n символов строки s2 со строкой s1. Результат сохраняется в s1
Сравнение строк
strcmp(s1,s2)	сравнивает строку s1 со строкой s2 и возвращает результат типа int: 0 –если строки эквивалентны, >0 – если s1<s2,  <0  — если s1>s2 С учётом регистра
strncmp(s1,s2,n)	сравнивает n символов строки s1 со строкой s2 и возвращает результат типа int: 0 –если строки эквивалентны, >0 – если s1<s2,  <0  — если s1>s2 С учётом регистра
stricmp(s1,s2)	сравнивает строку s1 со строкой s2 и возвращает результат типа int: 0 –если строки эквивалентны, >0 – если s1<s2,  <0  — если s1>s2 Без учёта регистра
strnicmp(s1,s2,n)	сравнивает n символов строки s1 со строкой s2 и возвращает результат типа int: 0 –если строки эквивалентны, >0 – если s1<s2,  <0 — если s1>s2 Без учёта регистра

Функции поиска
strchr(s,c)	поиск первого вхождения символа с в строке s. В случае удачного поиска возвращает указатель на место первого вхождения символа с. Если символ не найден, то возвращается ноль.
strcspn(s1,s2)	определяет длину начального сегмента строки s1, содержащего те символы, которые не входят в строку s2
strspn(s1,s2)	возвращает длину начального сегмента строки s1, содержащего только те символы, которые входят в строку s2
strprbk(s1,s2)	Возвращает указатель  первого вхождения любого символа строки s2 в строке s1
Функции преобразования
*/

/*
Функция	Описание
Insert	Insert(const AnsiString& str, int ind)
Вставляет в строку подстроку str, начиная с индекса ind
Pos	Pos(const AnsiString& subStr) const
Возвращает индекс первого символа первого вхождения subStr в строке. Индексы начинаются с 1. Если subStr не содержится в встроке, возвращается 0. Не поддерживает многобайтные символы
IsEmpty	Возвращает true, если строка пустая
Delete	Delete(int ind, int count)
Удаляет из строки, начиная с позиции ind символы в количестве count
Length	Возвращает длину строки (количество символов в строке)
LowerCase	Возвращает строку, в которой все символы приведены к нижнему регистру. Не изменяет исходную строку
UpperCase	Возвращает строку, в которой все символы приведены к верхнему регистру. Не изменяет исходную строку
SubString	 SubString(int ind, int count)
Возвращает подстроку, начинающуюся с символа в позиции ind и содержащую count символов
SetLength	SetLength(int newLen)
Обрезает строку до newLen символов. Если исходная строка короче, то она не увеличивается
ToDouble	Преобразует строку в число с плавающей запятой. Если строка не соответствует формату числа с плавающей запятой, генерируется исключение
Tolnt	Преобразует строку в целое число. Если строка не соответствует формату целого числа, генерируется исключение
Trim	Возвращает строку, соответствующую исходной, но без пробельных символов до и после значащих символов
TrimLeft	Возвращает строку, соответствующую исходной, но без начальных пробельных символов
TrimRight	Возвращает строку, соответствующую исходной, но без заключительных пробельных символов
c_str	Возвращает указатель на строку с нулевым символом в конце char*, содержащую те же символы, что в AnsiString
IsDelimiter	IsDelimiter(const AnsiString& delimiters, int ind) const
Возвращает true, если символ с индексом ind является одним из разделителей, указанных в строке delimiters
*/

using namespace std;

class String {
	private:
    
		Array <char> text;
    
	public:
		inline char * c_str() {
			return text.to_arr();
		}
		
		String(unsigned int size = 255) {
			text.add_neskolko(0, 255); 
		}
		
		String(const char * puk) {
			text.add_neskolko(0, strlen(puk)); 
			strcpy(text.to_arr(), puk);
		}
		
		~String() {
			text.full_delete();
		}
		
		char & operator [](int H) {
			return text[H];
		}
		
		//херь которая не работает
		//более менее
		//izi
		//я забыл что она делает
		template <size_t sizevod>
		void operator = (const char (&str)[sizevod]) {//переделать
			if (text.size()<sizevod)
				text.add_neskolko(0, sizevod-text.size());
			strncpy(text.to_arr(), str, sizevod);
		}
		
		template <size_t sizevod>
		void operator += (const char (&str)[sizevod]) {//переделать
			if (text.size()<sizevod)
				text.add_neskolko(0, sizevod-text.size());
			strncat(text.to_arr(), str, sizevod);
		}
		
		
		friend std::ostream& operator<<(std::ostream& os, /*const*/ String& obj) {
			return os << obj.c_str();
		}
 
		friend std::istream& operator>>(std::istream& is, String& obj)
		{
    		char BUFF[2048];
 
    		is.getline(BUFF, sizeof BUFF);
    		
    		if (obj.text.size() < strlen(BUFF)+1 )
    			obj.text.add_neskolko(obj.text.size(), strlen(BUFF) - obj.text.size());
    		strcpy(obj.c_str(), BUFF);
 
    		return is;
		}

	    String& operator = (String& puk) {
	    	text = puk.text;
	    }
	    
	    //еще пока рановато
	    //String& operator = (List& puk) {
//	    	text = puk.text;
//	    }
	    template <class chur>
	    String& operator = (Array <chur>& puk ) {
	    	text = puk;
	    }
	    
	    //все не то херачь по новой
	    //friend String& operator+(String& raz, String& dva) {
//	    	String buf(strlen(dva.c_str())+strlen(raz.c_str())+1);
//	    	strcat(strcpy(buf.c_str(),raz.c_str()), dva.c_str());
//	    	return buf;
//	    }
	    
	    friend String& operator += (String& raz, String& dva) {
	    	if (raz.text.size() < strlen(dva.c_str())+1 )
    			raz.text.add_neskolko(raz.text.size(), strlen(dva.c_str())+1 - raz.text.size());
			strcat(raz.c_str(), dva.c_str());
	    	return raz;
	    }
	    
	    friend String& operator *= (String& raz, unsigned int povtor) {
	    	String buf;
			buf = raz;
	    	raz.text.add_neskolko(raz.text.size(), strlen(raz.c_str())*povtor+1);
	    	for (unsigned int i = 1; i < povtor; i++)
	    		strcat(raz.c_str(), buf.c_str());
	    	return raz;
	    }
	 
	    friend bool operator==(String& raz, String& dva) {
	    	return strcmp(raz.c_str(), dva.c_str()) == 0;
	    }
	    friend bool operator!=(String& raz, String& dva) {
	    	return strcmp(raz.c_str(), dva.c_str()) != 0;
	    }
	    friend bool operator>(String& raz, String& dva) {
	    	return strcmp(raz.c_str(), dva.c_str()) > 0;
	    }
	    friend bool operator>=(String& raz, String& dva) {
	    	return strcmp(raz.c_str(), dva.c_str()) >= 0;
	    }
	    friend bool operator<(String& raz, String& dva) {
	    	return strcmp(raz.c_str(), dva.c_str()) < 0;
	    }
	    friend bool operator<=(String& raz, String& dva) {
	    	return strcmp(raz.c_str(), dva.c_str()) <= 0;
	    }

		//Вставляет в строку подстроку str, начиная с индекса ind    
		//Insert(const AnsiString& str, int ind)
		
		
		//Возвращает индекс первого символа первого вхождения subStr в строке. Индексы начинаются с 1. Если subStr не содержится в встроке, возвращается 0. Не поддерживает многобайтные символы
		//Pos(const AnsiString& subStr) const

		//Возвращает true, если строка пустая
		bool IsEmpty() {
			return strlen(text.to_arr()) == 0;
		}
 

//все что закоменчено ниже мне лень реализовывать
		//Удаляет из строки, начиная с позиции ind символы в количестве count
		void Delete(int ind, int count) {
			int len = strlen(text.to_arr());
			text.delet(ind, count);
			if (ind+count >= len && ind < len)
				text.add_last('\0');
		}
		
		
		//Возвращает длину строки (количество символов в строке)
		unsigned int Length() {
			return strlen(text.to_arr());
		}
		
		//LowerCase	Возвращает строку, в которой все символы приведены к нижнему регистру. Не изменяет исходную строку
		
		//UpperCase	Возвращает строку, в которой все символы приведены к верхнему регистру. Не изменяет исходную строку
		
//		SubString(int ind, int count)
//		Возвращает подстроку, начинающуюся с символа в позиции ind и содержащую count символов
//		
//		SetLength(int newLen)
//		Обрезает строку до newLen символов. Если исходная строка короче, то она не увеличивается
//		
//		ToDouble Преобразует строку в число с плавающей запятой. Если строка не соответствует формату числа с плавающей запятой, генерируется исключение
//		
//		Tolnt Преобразует строку в целое число. Если строка не соответствует формату целого числа, генерируется исключение
		
		//бред, кому это может понядобиться
		//Trim Возвращает строку, соответствующую исходной, но без пробельных символов до и после значащих символов
		//TrimLeft	Возвращает строку, соответствующую исходной, но без начальных пробельных символов
		//rimRight	Возвращает строку, соответствующую исходной, но без заключительных пробельных символов
		
//		IsDelimiter(const AnsiString& delimiters, int ind) const
//		Возвращает true, если символ с индексом ind является одним из разделителей, указанных в строке delimiters

};

int main() {
	String b = "xardbas", a;
	cin >> a;
	a *= 3;
	a += "eto ";
	a += b;
	cout << a << endl;
}

