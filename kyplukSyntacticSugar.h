#ifndef _kyplukSyntacticSugar_H_
#define _kyplukSyntacticSugar_H_
	
	#define elif else if
	#define no !
	//#define and &&
	//#define or ||
	#define unless(bo) if (!(bo))
	#define until(bo) while(!(bo))
	#define loop while(true)
	
	//const
	//#define readonly const
	//#define final const
	
#endif
