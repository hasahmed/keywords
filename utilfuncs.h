//  Created by Hasan Yusuf Ahmed on 2/23/17.
#include <stdio.h>
struct key{ //key. analogous to a key of a phone keypad
    char digit; //a number 2-9
    char *letters; // the array of letters associated with number
    int length; //the number of letters associated with that number
};
typedef struct key Key;

struct stringArr{
    char **array;
    size_t length;
};
typedef struct stringArr StringArray;

char* letterToArray(char digit);
void initKey(Key *k, char digit);
void freeKey(Key *k);
void freeKeyArr(Key kArr[], int arrLen);
void initKeyArr(Key kArr[], char phoneNumber[]);
void printKeyArrStrByIndexArr(FILE *f, int indexArr[], Key keyArr[], int arrLen);
int isValidNumber(char *phoneNumber);
int internal_search(StringArray *enums, char *dictFile, char *fileout);
void initStringArrayWith7LetterWordFile(char *file, StringArray *s);
void freeStringArray(StringArray *s);
void undash(char str[8]);
void internal_enumerate(StringArray *str_arr, int indexArr[], Key keyArr[], int arrLen);
int factorial(int n);
void copy_mem_by_keyArr(char *dest_str, int indexArr[], Key keyArr[], int arrLen);
int chararrcmp(register char *arr1, register char *arr2, int cmp_up_to);
