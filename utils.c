#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

static void trimNewline(char *s)
{
    size_t n = strlen(s);
    while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r'))
        s[--n] = '\0';
}

static int isBlank(const char *s)
{
    while (*s) {
        if (!isspace((unsigned char)*s))
            return 0;
        s++;
    }
    return 1;
}

/* Keeps asking until the user types a whole number between min and max */
int readInt(const char *prompt, int min, int max)
{
    char buf[64];
    char *end;
    long value;

    while (1) {
        printf("%s", prompt);
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            printf("\nInput closed. Exiting.\n");
            exit(0);
        }
        value = strtol(buf, &end, 10);
        if (end == buf || (*end != '\n' && *end != '\0')) {
            printf("  Invalid input. Please enter a whole number.\n");
            continue;
        }
        if (value < min || value > max) {
            printf("  Please enter a number between %d and %d.\n", min, max);
            continue;
        }
        return (int)value;
    }
}

/* Keeps asking until the user types a number that is >= min */
double readDouble(const char *prompt, double min)
{
    char buf[64];
    char *end;
    double value;

    while (1) {
        printf("%s", prompt);
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            printf("\nInput closed. Exiting.\n");
            exit(0);
        }
        value = strtod(buf, &end);
        if (end == buf || (*end != '\n' && *end != '\0')) {
            printf("  Invalid input. Please enter a number.\n");
            continue;
        }
        if (value < min) {
            printf("  Value cannot be less than %.2f.\n", min);
            continue;
        }
        return value;
    }
}

/* Reads a non-empty line of text that fits into dest (size includes '\0') */
void readString(const char *prompt, char *dest, int size)
{
    char buf[256];

    while (1) {
        printf("%s", prompt);
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            printf("\nInput closed. Exiting.\n");
            exit(0);
        }
        trimNewline(buf);
        if (isBlank(buf)) {
            printf("  This field cannot be empty.\n");
            continue;
        }
        if ((int)strlen(buf) >= size) {
            printf("  Too long. Maximum %d characters.\n", size - 1);
            continue;
        }
        strcpy(dest, buf);
        return;
    }
}

/* Case-insensitive "is key found inside text?" used by the search functions */
int containsIgnoreCase(const char *text, const char *key)
{
    char a[256], b[256];
    size_t i;

    strncpy(a, text, sizeof(a) - 1);
    a[sizeof(a) - 1] = '\0';
    strncpy(b, key, sizeof(b) - 1);
    b[sizeof(b) - 1] = '\0';

    for (i = 0; a[i]; i++) a[i] = (char)tolower((unsigned char)a[i]);
    for (i = 0; b[i]; i++) b[i] = (char)tolower((unsigned char)b[i]);

    return strstr(a, b) != NULL;
}

void printLine(char ch, int length)
{
    int i;
    for (i = 0; i < length; i++)
        putchar(ch);
    putchar('\n');
}
