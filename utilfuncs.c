//  Created by Hasan Y Ahmed on 1/23/17.


#include <stdlib.h>
#include <string.h>
#include "utilfuncs.h"

void undash(char str[8]){
    int i;
    for(i = 3; i < 8; i++){
        str[i] = str[i + 1];
    }
}

int search(char *dictFile, char *fileout){
    FILE *enumerations, *dict, *out;
    enumerations = fopen("tmp.txt", "r");
    dict = fopen(dictFile, "r");
    out = fopen(fileout, "w");
    char enumtmp[8];
    char dicttmp[8];
    int i = 0;
    if(enumerations != NULL){
        while(!feof(enumerations)){
            fscanf(enumerations, "%s", enumtmp);
            while(!feof(dict)){
                i++;
                fscanf(dict, "%s", dicttmp);
                if(strcmp(dicttmp, enumtmp) == 0){
                    fprintf(out, "%s\n", dicttmp);
                    fseek(dict, 0, SEEK_SET);
                    printf("word '%s' found at %d iterations\n", enumtmp, i);
                    break;
                }
            }
            fseek(dict, 0, SEEK_SET);
        }
    }
    else fprintf(stderr, "Error opening one of %s, %s, or %s\n", "tmp.txt", dictFile, fileout);
    printf("Search ended after %d iterations\n", i);
    fclose(enumerations);
    fclose(dict);
    fclose(out);
    return 0;
}

void freeStringArray(StringArray *s){
    int i;
    for(i = 0; i < s->length; i++){
        free(s->array[i]);
    }
    free(s->array);
}

void initStringArrayWith7LetterWordFile(char *file, StringArray *s){
    FILE *f = fopen(file, "r");
    fseek(f, 0, SEEK_END);
    size_t fileLength = ftell(f) / 8;
    rewind(f);
    char **p = (char**) malloc(sizeof(*p) * fileLength);
    int i;
    for(i = 0; i < fileLength; i++){
        p[i] = (char*) malloc(sizeof(char) * 8);
        fscanf(f, "%s", p[i]);
    }
    fclose(f);
    s->length = fileLength;
    s->array = p;
}

//does the same thing as search except instead of using files, uses internal arrays
int internal_search(char *dictFile, char *fileout){
    StringArray dict, phoneEnums;
    FILE *fout;
    initStringArrayWith7LetterWordFile("tmp.txt", &phoneEnums);
    initStringArrayWith7LetterWordFile(dictFile, &dict);
    fout = fopen(fileout, "w");
    int i = 0;
    int j, k;
    for(k = 0; k < phoneEnums.length; k++){
            for(j = 0; j < dict.length; j++){
                i++;
                if(strcmp(dict.array[j], phoneEnums.array[k]) == 0){
                    fprintf(fout, "%s\n", dict.array[j]);
                    printf("word '%s' found at %d iterations\n", dict.array[j], i);
                    break;
                }
            }
        }
    printf("Search ended after %d iterations\n", i);
    fclose(fout);
    freeStringArray(&dict);
    freeStringArray(&phoneEnums);
    return 0;
}


void printKeyArrStrByIndexArr(FILE *f, int indexArr[], Key keyArr[], int arrLen){
    int j;
    for(j = 0; j < arrLen; j++)
        fprintf(f, "%c", keyArr[j].letters[indexArr[j]]);
    fprintf(f, "\n");
}

int isValidNumber(char *phoneNumber){
    int i;
    for(i = 0; i < 7; i++)
        if(phoneNumber[i] == '1' || phoneNumber[i] == '0')
            return 0;
    return 1;
}

//enumerate all possiblilities
void enumerate(char *fileName, int indexArr[], Key keyArr[], int arrLen){
    FILE *f;
    f = fopen(fileName, "w");
    int i = 0, j,  k,  l,  m,  n,  o,  p;
        for(j = 0; j < keyArr[0].length; j++)
            for(k = 0; k < keyArr[1].length; k++)
                for(l = 0; l < keyArr[2].length; l++)
                    for(m = 0; m < keyArr[3].length; m++)
                        for(n = 0; n < keyArr[4].length; n++)
                            for(o = 0; o < keyArr[5].length; o++)
                                for(p = 0; p < keyArr[6].length; p++){
                                    i++;
                                    indexArr[0] = j;
                                    indexArr[1] = k;
                                    indexArr[2] = l;
                                    indexArr[3] = m;
                                    indexArr[4] = n;
                                    indexArr[5] = o;
                                    indexArr[6] = p;
                                    printKeyArrStrByIndexArr(f, indexArr, keyArr, arrLen);
                                }
    fclose(f);
}

//the stop condition for printing nubmers
int isDone(int idxArr[], Key keyArr[], int arrLen){
    int i;
    for(i = 0; i < arrLen; i++){
        if(idxArr[i] < keyArr[i].length -1)
            return 0;
    }
    return 1;
}

void freeKey(Key *k){
    free(k->letters);
}
void freeKeyArr(Key kArr[], int arrLen){
    int i;
    for(i = 0; i < arrLen; i++){
        freeKey(&kArr[i]);
    }
}
// initializes a Key object with values given a digit
void initKey(Key *k, char digit){
    k->digit = digit;
    k->letters = letterToArray(digit);
    k->length = (digit == '7' || digit == '9') ? 4 : 3;
}
void initKeyArr(Key kArr[], char phoneNumber[]){
    int i;
    for(i = 0; i < 7; i++)
        initKey(&kArr[i], phoneNumber[i]);
}

// the non-prgrammy implementation of ntletter_map
char* letterToArray(char digit){
    int returnArraySize = (digit == '9' || digit == '7') ? 4 : 3;
    char *c = (char*) malloc(sizeof(char) * returnArraySize);
    switch(digit){
        case '2':
            c[0] = 'a';
            c[1] = 'b';
            c[2] = 'c';
            return c;
        case '3':
            c[0] = 'd';
            c[1] = 'e';
            c[2] = 'f';
            return c;
        case '4':
            c[0] = 'g';
            c[1] = 'h';
            c[2] = 'i';
            return c;
        case '5':
            c[0] = 'j';
            c[1] = 'k';
            c[2] = 'l';
            return c;
        case '6':
            c[0] = 'm';
            c[1] = 'n';
            c[2] = 'o';
            return c;
        case '7':
            c[0] = 'p';
            c[1] = 'q';
            c[2] = 'r';
            c[3] = 's';
            return c;
        case '8':
            c[0] = 't';
            c[1] = 'u';
            c[2] = 'v';
            return c;
        case '9':
            c[0] = 'w';
            c[1] = 'x';
            c[2] = 'y';
            c[3] = 'z';
            return c;
        default:
            fprintf(stderr, "you have passed an invalid argument to function 'letterToArray('%c')'\n", digit);
            return NULL;
    }
}
