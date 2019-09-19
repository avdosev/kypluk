//this top define in the world
//polubasu eto yze est v qt(
#pragma once

#include "kyplukSyntacticSugar.h"
#include "kyplukTypedef.h"

#define USE(chtoto) using namespace chtoto;

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

