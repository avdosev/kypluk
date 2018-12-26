#ifndef _kyplukLogs_h_
#define _kyplukLogs_h_

#include <fstream>
#include <ctime>
#include <string.h>
#include <cstdlib>

#include <kyplukDefine.h>

class Logs {
	private:
		std::ofstream f;
		char file_name[200] = {};
		char vremya[6] = {32,32,':',32,32,0};//xuu nikto ze ne bude razbiratsa
		
	public:
		
		Logs(const char * name = NULL) {
			setlocale(0, "");
			
			strcpy(file_name, "Logs.txt");
			
			if (name!=NULL)
				strcpy(file_name, name);
			
			f.open(file_name, ios_base::app);
			/*
			if (!f.is_open())
				f.open(file_name);
			*/	
		}
		
		~Logs() {
			f.close();
		}
		
		void stop () {
			f.close();
		}
		void start() {
			f.open(file_name, ios_base::app);
		}
		
		inline std::ofstream& file () {
			return f;
		}
		
		Logs& separ() {
			f << kypluk::Separator;
			return *this;
		}
		
		const char * timeLog() {
			itoa(time(0)%(3600*24)/3600 + 3, vremya, 10);//ch
			if (vremya[1] == '\0')
			{
				vremya[1] =  vremya[0];
				vremya[0] = ' ';
			}
			//itoa(i, stringi, 10);
			itoa(time(0)%3600/60, vremya+3, 10);//min
			if (vremya[4] == '\0')
			{
				vremya[4] =  vremya[3];
				vremya[3] = '0';
			}
			return vremya;
		}
		
		Logs& nLine() {
			f << std::endl << std::endl;
			return *this;
		}
		
		Logs& operator != (const char info[200])
		{
			f << info;
			return *this;
		}
		
		Logs& operator < (const char info[200])
		{
			f << info << kypluk::Separator;
			return *this;
		}
		
		Logs& operator > (const char info[200])
		{
			f << kypluk::Separator << info;
			return *this;
		}
		
		Logs& operator >= (const char info[200])
		{
			f << std::endl << std::endl << info;
			return *this;
		}
		
		Logs& operator <= (const char info[200])
		{
			f << info << std::endl << std::endl;
			return *this;
		}
		
		Logs& operator ! ()
		{
			return nLine();
		}
		
		
};

#endif
