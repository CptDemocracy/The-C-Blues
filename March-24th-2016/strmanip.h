#ifndef STRMANIP_H
#define STRMANIP_H

int StringToLong(const char* str, long* OutResult);

int StringToDouble(const char* str, double* OutResult);

int SwapCase(const char* str, char* OutResult);

int DoubleToString(double value, char* OutResult);

#endif /* STRMANIP_H */
