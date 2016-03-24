#ifndef STRMANIP_H
#define STRMANIP_H

int KMP(const char* source, 
	int start, 
	int sourceSize, 
	const char* pattern, 
	int patternSize);

int* KMPCalculateDFA(const char* pattern, 
	int patternLen, 
	int** pOutResultDFA);

int CountWords(const char* text);

int Substring(const char* target, 
	int start, 
	int count, 
	char* OutResult);

int IsSubstringOf(const char* target, const char* substring);

int FindString(const char* target, const char* substring);

int RemoveString(char* text, 
	int start, 
	int count);

int InsertString(const char* source, 
	const char* insert, 
	int index, 
	char* OutResult);

int FindSubstring(const char* source, 
	const char* substring, 
	int start);

int ReplaceFirstSubstring(const char* source,
	const char* target,
	const char* replac,
	char* OutResult);

int ReplaceAllSubstrings(const char* source, 
	const char* target, 
	const char* replac, 
	char* OutResult);

#endif /* STRMANIP_H */
