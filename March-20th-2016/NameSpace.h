#ifndef NAMESPACE_H
#define NAMESPACE_H

#include <stdio.h>

struct NameSpace {
	void   (*PrintName)  (const char*, FILE*);
	double (*ReadDouble) (FILE*, void(*)(void));	
	int	   (*CountWords) (FILE*);
	int	   (*IsWordIn)	 (FILE*, int(*)(const char*));
	int	   (*IsPrime)	 (long);
} const ns;

#endif /* NAMESPACE_H */
