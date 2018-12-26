#ifndef _kyplukString_H_
#define _kyplukString_H_

#include <kyplukarray.h>

using namespace std;
#include <cstring>
class String {
	private:
    
		Array <char> * text = new Array <char>;
    
	public:
		inline char * c_str() {
			return text->to_arr();
		}
		
		String(unsigned int size = 255) {
			text->add_neskolko(0, size+1); 
		}
		
		String(const char * puk) {
			text->add_neskolko(0, strlen(puk)); 
			strcpy(c_str(), puk);
		}
		
	    String(Array <char>& puk ) {
	    	*text = puk;
	    }
		
		char & operator [](int H) {
			return (*text)[H];
		}
		
		//���� ������� �� ��������
		//����� �����
		//izi
		//� ����� ��� ��� ������ //������ ����� ��������
		template <size_t sizevod>
		void operator = (const char (&str)[sizevod]) {
			if (text->size()<sizevod)
				text->add_neskolko(0, sizevod-text->size());
			strncpy(c_str(), str, sizevod);
		}
		
		void operator = (const char * puk) {
			if (text->size()<strlen(puk))
				text->add_neskolko(0, strlen(puk)-text->size());
			strcpy(c_str(), puk);
		}
		
		template <size_t sizevod>
		void operator += (const char (&str)[sizevod]) {//����������
			if (text->size()<sizevod)
				text->add_neskolko(0, sizevod-text->size());
			strncat(c_str(), str, sizevod);
		}
		
		
		friend std::ostream& operator<<(std::ostream& os, /*const*/ String& obj) {
			return os << obj.c_str();
		}
 
		friend std::istream& operator>>(std::istream& is, String& obj)
		{
    		char BUFF[2048];
 
    		is.getline(BUFF, sizeof BUFF);
    		
    		if (obj.text->size() < strlen(BUFF)+1 )
    			obj.text->add_neskolko(obj.text->size(), strlen(BUFF) - obj.text->size());
    		strcpy(obj.c_str(), BUFF);
 
    		return is;
		}

	    String& operator = (String& puk) {
	    	text = puk.text;
	    }
	    
	    //��� ���� ��������
	    //String& operator = (List& puk) {
	    //	text = puk.text;
	    //}
	    String& operator = (Array <char>& puk ) {
	    	*text = puk;
	    }
	    
	    friend String& operator += (String& raz, String& dva) {
	    	if (raz.text->size() < strlen(dva.c_str())+1 )
    			raz.text->add_neskolko(raz.text->size(), strlen(dva.c_str())+1 - raz.text->size());
			strcat(raz.c_str(), dva.c_str());
	    	return raz;
	    }
	    
	    String& operator *= (unsigned int povtor) {
	    	const int mas_size = strlen(this->c_str())*povtor+1;
	    	char buf[mas_size];
			strcpy(buf, c_str());
	    	for (unsigned int i = 1; i < povtor; i++)
	    		strcat(buf ,c_str());
	    	(*this) = buf;
	    	return *this;
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
	    
	    void clear() {
	    	text->full_delete();
	    }

		//��������� � ������ ��������� str, ������� � ������� ind    
		//Insert(const AnsiString& str, int ind)
		
		
		//���������� ������ ������� ������� ������� ��������� subStr � ������. ������� ���������� � 1. ���� subStr �� ���������� � �������, ������������ 0.
		//Pos(const AnsiString& subStr) const

		//���������� true, ���� ������ ������
		bool IsEmpty() {
			return strlen(c_str()) == 0;
		}
 

//��� ��� ����������� ���� ��� ���� �������������
		//������� �� ������, ������� � ������� ind ������� � ���������� count
		void Delete(int ind, int count) {
			int len = strlen(c_str());
			text->delet(ind, count);
			if (ind+count >= len && ind < len)
				text->add_last('\0');
		}
		
		
		//���������� ����� ������ (���������� �������� � ������)
		unsigned int Length() {
			return strlen(c_str());
		}
		
		
//		SubString(int ind, int count)
//		���������� ���������, ������������ � ������� � ������� ind � ���������� count ��������
//		
		//�������� ������ �� newLen ��������. ���� �������� ������ ������, �� ��� �� �������������
		void SetLength(int newLen) {
			if (strlen(c_str()) > newLen) {
				text->delet(newLen, strlen(c_str())-newLen);
				(*text)[newLen]='\0';
			}
		}
		
//		
//		ToDouble ����������� ������ � ����� � ��������� �������. ���� ������ �� ������������� ������� ����� � ��������� �������, ������������ ����������
//		
		//����������� ������ � ����� �����. ���� ������ �� ������������� ������� ������ �����, ������������ ����������
		unsigned int ToInt()
		{
			int result = 0;
			for (int i=0; i < this->Length(); i++)
			{
				short int chislo = (*this)[i] - 48;
				if (chislo > 9 or chislo < 0) {
					throw 1;
					return 0;
				}
				
				(result*=10) += chislo; 
			}
			return result;
		} 
		
		//����, ���� ��� ����� ������������
		//Trim ���������� ������, ��������������� ��������, �� ��� ���������� �������� �� � ����� �������� ��������
		//TrimLeft	���������� ������, ��������������� ��������, �� ��� ��������� ���������� ��������
		//rimRight	���������� ������, ��������������� ��������, �� ��� �������������� ���������� ��������
		
		//���������� true, ���� ������ � �������� ind �������� ����� �� ������������, ��������� � ������ delimiters
		bool IsDelimiter(const char * delimiters, int ind) {
			for (int i = 0; i < strlen(delimiters); i++)
				if (delimiters[i]==(*this)[ind]) return true;
			return false;
		}
		template <size_t sizevod>
		void IsDelimiter(const char (&delimiters)[sizevod], int ind) {
			for (int i = 0; i < strlen(delimiters); i++)
				if (delimiters[i]==(*this)[ind]) return true;
			return false;
		}
		bool IsDelimiter(String &delimiters, int ind) {
			for (int i = 0; i < delimiters.Length(); i++)
				if (delimiters[i]==(*this)[ind]) return true;
			return false;
		}
		
};

#endif
