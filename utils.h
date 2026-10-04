#ifndef UTILS_H
#define UTILS_H

int    readInt(const char *prompt, int min, int max);
double readDouble(const char *prompt, double min);
void   readString(const char *prompt, char *dest, int size);
int    containsIgnoreCase(const char *text, const char *key);
void   printLine(char ch, int length);

#endif
