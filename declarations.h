//  Created by Hasan Yusuf Ahmed on 2/23/17.

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
int isDone(int idxArr[], Key keyArr[], int arrLen);
void initKeyArr(Key kArr[], char phoneNumber[]);
void enumerate(char *fileName, int indexArr[], Key keyArr[], int arrLen);
void printKeyArrStrByIndexArr(FILE *f, int indexArr[], Key keyArr[], int arrLen);
int isValidNumber(char *phoneNumber);
int search(char *dictFile, char *fileout);
int internal_search(char *dictFile, char *fileout);
void initStringArrayWith7LetterWordFile(char *file, StringArray *s);
void freeStringArray(StringArray *s);

