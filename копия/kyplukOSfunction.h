#ifndef _kyplukOSfunction_H_
#define _kyplukOSfunction_H_

#include <fstream>
#include <iostream> //ne ydalyau  bez etogo ne rabotaet pover mne
#include <windows.h>
#include <cstdlib>
#include <cstring>
#include <ctime>

using namespace std;

bool is_dir(const char *filename) {
	DWORD dwFileAttributes = GetFileAttributes(filename);
	if (dwFileAttributes == 0xFFFFFFFF)
		return false;
	return dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
}

bool is_file(const char *filename) {
	if (fopen( filename, "r" )) return true;
	return false;
}

/*
tip 1 - 1 puk.txt
tip 2 - 1puk.txt
tip 3 - puk1.txt
tip 4 - puk 1. txt
*/

void vebalnik(string directoria, int skolko_raz, const char name[], const char rashurenie[], int tip) {
	if (is_dir(directoria.c_str())) { //проверка наличия подобного каталога
		ofstream file;
		char stringi[8];
		string a;		
		for (int i=1; i<skolko_raz+1; i++) {
			itoa(i, stringi, 10);
			switch (tip) {
				case 1 : {
					a = directoria + stringi + " " + name + rashurenie;
					break;
				}
				case 2 : {
					a = directoria + stringi + name + rashurenie;
					break;
				}
				case 3 : {
					a = directoria + name + stringi + rashurenie;
					break;
				}
				default : {
					a = directoria + name + " " + stringi + rashurenie;
					break;
				}
			}
			
			//cout << a << endl;
			file.open(a.c_str());
			/*
			for (int x=0; x<256; x++)
				file << "Your read this because admin vstu is bad\n";
			*/
			file.close();
		}
	}
}

typedef void (*LPSEARCHFUNC)(LPCTSTR lpszFileName);
void SearchFiles(LPCTSTR lpszFileName, int &b, string xz[100], int podpapok, int maxpodpapok) { //оно искало рекурсивно? лул
    //if (podpapok>maxpodpapok) return; //максимальная скорость
	LPTSTR part;
    char tmp[MAX_PATH]; // временный массив
    char name[MAX_PATH];

    HANDLE hSearch = NULL;
    WIN32_FIND_DATA wfd;
    memset(&wfd, 0, sizeof(WIN32_FIND_DATA));

    // сначало поиск внутри вложенных папках ...
    if(GetFullPathName(lpszFileName, MAX_PATH, tmp, &part) == 0) return;
	strcpy(name, part);
    strcpy(part, "*.*");
    
    // если папки существуют, то делаем поиск
    wfd.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;
    if (!((hSearch = FindFirstFile(tmp, &wfd)) == INVALID_HANDLE_VALUE))
    do
    {
        // в каждой папке есть две папки с именами "." и ".."
        // и эти папки мы не трогаем

        // пропускаем папки "." и ".."
        if (!strncmp(wfd.cFileName, ".", 1) || !strncmp(wfd.cFileName, "..", 2)) continue;
        
        if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) // если мы нашли папку
        {
            char next[MAX_PATH];
            if(GetFullPathName(lpszFileName, MAX_PATH, next, &part) == 0) return;
            strcpy(part, wfd.cFileName);
            strcat(next, "\\");
            strcat(next, name);
            
            
			//cout << next << endl;
            if (is_dir(next) || is_file(next)) {
				xz[b]=next;
				if (is_dir(next)) xz[b]+="\\";
            	b++;
        	}
        	else {
        		if (podpapok<maxpodpapok) SearchFiles(next, b, xz, podpapok+1, maxpodpapok);
        	}
        }
    } while (FindNextFile(hSearch, &wfd)); // ищем следующий файл
	FindClose (hSearch); // заканчиваем поиск	
}

void set_image_on_desktop(const char directoriya_and_filename[]) {
	char filename[200] = {};
	strcat(filename,directoriya_and_filename);
	SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, &filename, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
}

void download_from_net(string url, const char directoriya_and_filename[]) {
	//typedef void * (__stdcall *MyDownloadToUrl)(LPUNKNOWN,const char*, const char*,DWORD, LPBINDSTATUSCALLBACK);
	typedef HRESULT (__stdcall *MyDownloadToUrl)(LPUNKNOWN, const char*, const char*, DWORD, LPBINDSTATUSCALLBACK);
	HINSTANCE LibHnd = LoadLibrary("Urlmon.dll");
	MyDownloadToUrl MyDownloadFunction =  (MyDownloadToUrl)GetProcAddress(LibHnd,"URLDownloadToFileA");
	MyDownloadFunction(0, url.c_str(), directoriya_and_filename, 0, 0);
}

#endif
