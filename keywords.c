//  Created by Hasan Y Ahmed on 2/23/17.

#include <string.h>
#include "utilfuncs.h"

void printErrorMessage(){
    fprintf(stderr, "\nusage: keywords [-options] phoneNumber\n");
    fprintf(stderr, " -o    specify output file\n -d    specify dictionary file\n");
    fprintf(stderr, "\n **note** \nif using the -d and -o options together, the files\n must come in the same order as the options.\n By default the output file\n is matches.txt, and the dictionary file is dict/7letterdict.txt\n\n");
}

int main(int argc, const char *argv[]) {
    
    int phnum_index = 1;
    if (argc < 2){
        printErrorMessage();
        return 1;
    }
    else{
        char fileout[50];
        char dict[50];
        char fileoutDefault[] = "matches.txt";
        char dictDefault[] = "dict/7letterdict.txt";
        if(strcmp(argv[1], "-o") == 0 && strcmp(argv[2], "-d") != 0){
            strcpy(fileout, argv[2]);
            strcpy(dict, dictDefault);
            phnum_index = 3;
        }
        else if(strcmp(argv[1], "-d") == 0 && strcmp(argv[2], "-o") != 0){
            strcpy(dict, argv[2]);
            strcpy(fileout, fileoutDefault);
            phnum_index = 3;
        }
        else{
            if(strcmp(argv[1], "-o") == 0 && strcmp(argv[2], "-d") == 0){
                strcpy(fileout, argv[3]);
                strcpy(dict, argv[4]);
                phnum_index = 5;
            }
            else if(strcmp(argv[1], "-d") == 0 && strcmp(argv[2], "-o") == 0){
                strcpy(dict, argv[3]);
                strcpy(fileout, argv[4]);
                phnum_index = 5;
            }
            else{
                if(argv[1][0] == '-'){
                    if(argv[1][1] != 'd' || argv[1][1] != 'c'){
                        printErrorMessage();
                        return 2;
                    }
                }
                else{
                    strcpy(fileout, fileoutDefault);
                    strcpy(dict, dictDefault);
                }
            }
        }
        
        char inputNumber[8];
        strcpy(inputNumber, argv[phnum_index]);
        
        //printf("fileout: %s, dict: %s, inputNumber: %s\n", fileout, dict, inputNumber);
        if(!isValidNumber(inputNumber)){
            fprintf(stderr, "error: phone number must NOT contain any 0s or 1s\n");
            return 3;
        }
        Key keyArr[7];
        initKeyArr(keyArr, inputNumber);
        int indexes[7] = {0};
        enumerate("tmp.txt", indexes, keyArr, 7);
        freeKeyArr(keyArr, 7);
        internal_search(dict, fileout);
    }
    return 0;
}