#ifndef STRMANIP_H
#define STRMANIP_H

int CountWords(const char* text);

int Substring(const char* target, int start, int count, char* OutResult);

int IsSubstringOf(const char* target, const char* substring);

int FindString(const char* target, const char* substring);

int RemoveString(char* text, int start, int count);

#endif /* STRMANIP_H */
