#include <iostream>
#include <kyplukarray.h>

/*
strlen(���_������)	���������� ����� ��������� ������, ��� ����� ����-�������
����������� �����
strcpy(s1,s2)	��������� ��������� ����������� �������� �� ������  s2 � ������ s1
strncpy(s1,s2, n)	��������� ��������� ����������� n �������� �� ������  s2 � ������ s1. ���������� �������� s1
������������ �����
strcat(s1,s2)	���������� ������ s2 �� ������� s1. ��������� ����������� � s1
strncat(s1,s2,n)	���������� n �������� ������ s2 �� ������� s1. ��������� ����������� � s1
��������� �����
strcmp(s1,s2)	���������� ������ s1 �� ������� s2 � ���������� ��������� ���� int: 0 ����� ������ ������������, >0 � ���� s1<s2,  <0  � ���� s1>s2 � ������ ��������
strncmp(s1,s2,n)	���������� n �������� ������ s1 �� ������� s2 � ���������� ��������� ���� int: 0 ����� ������ ������������, >0 � ���� s1<s2,  <0  � ���� s1>s2 � ������ ��������
stricmp(s1,s2)	���������� ������ s1 �� ������� s2 � ���������� ��������� ���� int: 0 ����� ������ ������������, >0 � ���� s1<s2,  <0  � ���� s1>s2 ��� ����� ��������
strnicmp(s1,s2,n)	���������� n �������� ������ s1 �� ������� s2 � ���������� ��������� ���� int: 0 ����� ������ ������������, >0 � ���� s1<s2,  <0 � ���� s1>s2 ��� ����� ��������

������� ������
strchr(s,c)	����� ������� ��������� ������� � � ������ s. � ������ �������� ������ ���������� ��������� �� ����� ������� ��������� ������� �. ���� ������ �� ������, �� ������������ ����.
strcspn(s1,s2)	���������� ����� ���������� �������� ������ s1, ����������� �� �������, ������� �� ������ � ������ s2
strspn(s1,s2)	���������� ����� ���������� �������� ������ s1, ����������� ������ �� �������, ������� ������ � ������ s2
strprbk(s1,s2)	���������� ���������  ������� ��������� ������ ������� ������ s2 � ������ s1
������� ��������������
*/

/*
�������	��������
Insert	Insert(const AnsiString& str, int ind)
��������� � ������ ��������� str, ������� � ������� ind
Pos	Pos(const AnsiString& subStr) const
���������� ������ ������� ������� ������� ��������� subStr � ������. ������� ���������� � 1. ���� subStr �� ���������� � �������, ������������ 0. �� ������������ ������������ �������
IsEmpty	���������� true, ���� ������ ������
Delete	Delete(int ind, int count)
������� �� ������, ������� � ������� ind ������� � ���������� count
Length	���������� ����� ������ (���������� �������� � ������)
LowerCase	���������� ������, � ������� ��� ������� ��������� � ������� ��������. �� �������� �������� ������
UpperCase	���������� ������, � ������� ��� ������� ��������� � �������� ��������. �� �������� �������� ������
SubString	 SubString(int ind, int count)
���������� ���������, ������������ � ������� � ������� ind � ���������� count ��������
SetLength	SetLength(int newLen)
�������� ������ �� newLen ��������. ���� �������� ������ ������, �� ��� �� �������������
ToDouble	����������� ������ � ����� � ��������� �������. ���� ������ �� ������������� ������� ����� � ��������� �������, ������������ ����������
Tolnt	����������� ������ � ����� �����. ���� ������ �� ������������� ������� ������ �����, ������������ ����������
Trim	���������� ������, ��������������� ��������, �� ��� ���������� �������� �� � ����� �������� ��������
TrimLeft	���������� ������, ��������������� ��������, �� ��� ��������� ���������� ��������
TrimRight	���������� ������, ��������������� ��������, �� ��� �������������� ���������� ��������
c_str	���������� ��������� �� ������ � ������� �������� � ����� char*, ���������� �� �� �������, ��� � AnsiString
IsDelimiter	IsDelimiter(const AnsiString& delimiters, int ind) const
���������� true, ���� ������ � �������� ind �������� ����� �� ������������, ��������� � ������ delimiters
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
		
		//���� ������� �� ��������
		//����� �����
		//izi
		//� ����� ��� ��� ������
		template <size_t sizevod>
		void operator = (const char (&str)[sizevod]) {//����������
			if (text.size()<sizevod)
				text.add_neskolko(0, sizevod-text.size());
			strncpy(text.to_arr(), str, sizevod);
		}
		
		template <size_t sizevod>
		void operator += (const char (&str)[sizevod]) {//����������
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
	    
	    //��� ���� ��������
	    //String& operator = (List& puk) {
//	    	text = puk.text;
//	    }
	    template <class chur>
	    String& operator = (Array <chur>& puk ) {
	    	text = puk;
	    }
	    
	    //��� �� �� ������ �� �����
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

		//��������� � ������ ��������� str, ������� � ������� ind    
		//Insert(const AnsiString& str, int ind)
		
		
		//���������� ������ ������� ������� ������� ��������� subStr � ������. ������� ���������� � 1. ���� subStr �� ���������� � �������, ������������ 0. �� ������������ ������������ �������
		//Pos(const AnsiString& subStr) const

		//���������� true, ���� ������ ������
		bool IsEmpty() {
			return strlen(text.to_arr()) == 0;
		}
 

//��� ��� ����������� ���� ��� ���� �������������
		//������� �� ������, ������� � ������� ind ������� � ���������� count
		void Delete(int ind, int count) {
			int len = strlen(text.to_arr());
			text.delet(ind, count);
			if (ind+count >= len && ind < len)
				text.add_last('\0');
		}
		
		
		//���������� ����� ������ (���������� �������� � ������)
		unsigned int Length() {
			return strlen(text.to_arr());
		}
		
		//LowerCase	���������� ������, � ������� ��� ������� ��������� � ������� ��������. �� �������� �������� ������
		
		//UpperCase	���������� ������, � ������� ��� ������� ��������� � �������� ��������. �� �������� �������� ������
		
//		SubString(int ind, int count)
//		���������� ���������, ������������ � ������� � ������� ind � ���������� count ��������
//		
//		SetLength(int newLen)
//		�������� ������ �� newLen ��������. ���� �������� ������ ������, �� ��� �� �������������
//		
//		ToDouble ����������� ������ � ����� � ��������� �������. ���� ������ �� ������������� ������� ����� � ��������� �������, ������������ ����������
//		
//		Tolnt ����������� ������ � ����� �����. ���� ������ �� ������������� ������� ������ �����, ������������ ����������
		
		//����, ���� ��� ����� ������������
		//Trim ���������� ������, ��������������� ��������, �� ��� ���������� �������� �� � ����� �������� ��������
		//TrimLeft	���������� ������, ��������������� ��������, �� ��� ��������� ���������� ��������
		//rimRight	���������� ������, ��������������� ��������, �� ��� �������������� ���������� ��������
		
//		IsDelimiter(const AnsiString& delimiters, int ind) const
//		���������� true, ���� ������ � �������� ind �������� ����� �� ������������, ��������� � ������ delimiters

};

int main() {
	String b = "xardbas", a;
	cin >> a;
	a *= 3;
	a += "eto ";
	a += b;
	cout << a << endl;
}

