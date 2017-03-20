//  Created by Hasan Yusuf Ahmed on 2/23/17.
#include <stdio.h>
#include <pthread.h>
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

struct search_args_t { //struct containing pointers to 'enumerations' and 'dictionary' for multithreading use
    StringArray *enums; // pointer to enumerations
    int search_start;
    int search_end;
    StringArray *dict; // pointer to dictionary name string
    char *fileout; // pointer to fileout name string
};
typedef struct search_args_t SearchArgs;

char* letterToArray(char digit);
void initKey(Key *k, char digit);
void freeKey(Key *k);
void freeKeyArr(Key kArr[], int arrLen);
int isDone(int idxArr[], Key keyArr[], int arrLen);
void initKeyArr(Key kArr[], char phoneNumber[]);
void enumerate(char *fileName, int indexArr[], Key keyArr[], int arrLen);
void printKeyArrStrByIndexArr(FILE *f, int indexArr[], Key keyArr[], int arrLen);
int isValidNumber(char *phoneNumber);
int search(char *dictFile, char *fileout);
void internal_search(
                     StringArray *enums,
                     int search_start,
                     int search_end,
                     StringArray *dict,
                     char *fileout
                     );
void initStringArrayWith7LetterWordFile(char *file, StringArray *s);
void freeStringArray(StringArray *s);
void undash(char str[8]);
void internal_enumerate(StringArray *str_arr, int indexArr[], Key keyArr[], int arrLen);
int factorial(int n);
void copy_mem_by_keyArr(char *dest_str, int indexArr[], Key keyArr[], int arrLen);
int chararrcmp(register char *arr1, register char *arr2, int cmp_up_to);
void* multi_search_caller(void *enum_and_dict_obj);
