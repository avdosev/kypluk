//this top define in the world
//polubasu eto yze est v qt(
#ifndef _kyplukDefine_H_
#define _kyplukDefine_H_

	#include <kyplukSyntacticSugar.h>
	#include <kyplukTypedef.h>
	
	#define USE(chtoto) using namespace chtoto;
	#define WATCH(x) cout << (#x) << " is " << (x) << endl
	
	#ifndef kNULL
		#ifdef NULL
			#undef NULL
		#endif
		#define NULL nullptr
		#define kNULL
	#endif

	namespace kypluk {
		const char space[] = " ",
		endl[] = "\n",
		separator[] = " | ";
	}

#endif
