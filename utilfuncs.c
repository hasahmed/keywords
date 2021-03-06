//  Created by Hasan Y Ahmed on 1/23/17.


#include <stdlib.h>
#include <string.h>
#include "utilfuncs.h"
#include "stringset.h"

#define INITIAL_STRSET_SIZE 10000



int inline chararrcmp(register char *arr1, register char *arr2, int cmp_up_to){
    int i;
    for(i = 0; i < cmp_up_to; i++)
        if(arr1[i] != arr2[i]) return 0; //this line is causing an issue
    return 1;
}

void undash(char str[8]){
    int i;
    if(str[3] == '-'){
        for(i = 3; i < 8; i++){
            str[i] = str[i + 1];
        }
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

// void initStringArrayWith7LetterWordFile(char *file, StringArray *s){
//     FILE *f = fopen(file, "r");
//     if(f){
//         fseek(f, 0, SEEK_END);
//         size_t fileLength = ftell(f) / 8;
//         rewind(f);
//         char **p = (char**) malloc(sizeof(*p) * fileLength);
//         int i;
//         for(i = 0; i < fileLength; i++){
//             p[i] = (char*) malloc(sizeof(char) * 8);
//             fscanf(f, "%s", p[i]);
//         }
//         fclose(f);
//         s->length = fileLength;
//         s->array = p;
//     }
//     else fprintf(stderr, "error opening file '%s'\n", file);
// }

stringset* initHashSetWith7LetterWordFile(char *file) {
    FILE *f = fopen(file, "r"); //open the file for reading
    stringset *word_set = stringset_new(INITIAL_STRSET_SIZE, STRSET_DEFAULT);
    int i = 0; //counter to check how many lines were read in
    if (f){ //check to see if the file opened properly
        char buff[8]; //buffer for reading strings into
        while(fscanf(f, "%s", buff) == 1){
            i++;
            stringset_add(&word_set, buff); //add the string we read in into the set
        }
        fclose(f); //close the file that was opened
    } else fprintf(stderr, "error opening file '%s'\n", file);
    return word_set;

}

//does the same thing as search except instead of using files, uses internal arrays
int internal_search(StringArray *enums, char *dictFile, char *fileout){

    stringset *word_set = initHashSetWith7LetterWordFile(dictFile);
    int i = 0;
    int k;
    for(k = 0; k < enums->length; k++){
        i++;
        if (stringset_contains(&word_set, enums->array[k])) {
            printf("word '%s' found at %d iterations\n", enums->array[k], i);
        }
    }
    printf("Search ended after %d iterations\n", i);
    stringset_free(&word_set);
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

//dest_str length must be 1 more than its number of numbers.
void copy_mem_by_keyArr(char *dest_str, int indexArr[], Key keyArr[], int arrLen){
    int j;
    for(j = 0; j < arrLen; j++)
        dest_str[j] = keyArr[j].letters[indexArr[j]];

    dest_str[j + 1] = '\0';
}

void internal_enumerate(StringArray *str_arr, int indexArr[], Key keyArr[], int arrLen){
    int numberLen = 7;
    int ii;
    int total_iterations = 1;
    for(ii = 0; ii < arrLen; ii++){
        total_iterations *= keyArr[ii].length;
    }
    str_arr->length = total_iterations;

    str_arr->array = (char**) malloc(total_iterations * sizeof(char*));

    int i = 0, j,  k,  l,  m,  n,  o,  p;
    for(j = 0; j < keyArr[0].length; j++)
        for(k = 0; k < keyArr[1].length; k++)
            for(l = 0; l < keyArr[2].length; l++)
                for(m = 0; m < keyArr[3].length; m++)
                    for(n = 0; n < keyArr[4].length; n++)
                        for(o = 0; o < keyArr[5].length; o++)
                            for(p = 0; p < keyArr[6].length; p++){
                                indexArr[0] = j;
                                indexArr[1] = k;
                                indexArr[2] = l;
                                indexArr[3] = m;
                                indexArr[4] = n;
                                indexArr[5] = o;
                                indexArr[6] = p;

                                str_arr->array[i] = (char*) malloc((numberLen + 1) * sizeof(char));
                                copy_mem_by_keyArr(str_arr->array[i], indexArr, keyArr, arrLen);
                                i++;
                            }
    //printf("actual iterations: %d\n", i);
    //printf("calculated iterations: %d\n", total_iterations);
    //printf("str_arr->length: %lu\n", str_arr->length);
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
