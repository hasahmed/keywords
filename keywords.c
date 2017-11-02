//  Created by Hasan Y Ahmed on 2/23/17.

#include <string.h>
#include "utilfuncs.h"
#include <time.h>

void printErrorMessage(){
    fprintf(stderr, "\nusage: keywords [-options] phoneNumber\n");
    fprintf(stderr, " -o    specify output file\n -d    specify dictionary file\n");
    fprintf(stderr, "\n **note** \nif using the -d and -o options together, the files\n must come in the same order as the options.\n By default the output file\n is matches.txt, and the dictionary file is dict/7letterdict.txt\n\n");
}

int main(int argc, const char *argv[]) {
    
    
    //pthread_setname_np("keywords");
    
    //input argument processessing
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
        //end input argument processessing
        
        char inputNumber[8];
        char inum_tmp[9];
        strcpy(inum_tmp, argv[phnum_index]);
        undash(inum_tmp);
        strcpy(inputNumber, inum_tmp);
        
        if(!isValidNumber(inputNumber)){
            fprintf(stderr, "error: phone number must NOT contain any 0s or 1s\n");
            return 3;
        }
        
        StringArray dict_arr, three_dict, four_dict;
        init_StringArray(dict, &dict_arr, 7); //scan in dict for whole phone number
        
        init_StringArray("dict/3letterdict.txt", &three_dict, 3);
        init_StringArray("dict/4letterdict.txt", &four_dict, 4);
        
        printf("7 dict length %d\n", dict_arr.length);
        printf("three dict length %d\n", three_dict.length);
        printf("four dict length %d\n", four_dict.length);
        
        StringArray enumerations;
        Key keyArr[7];
        initKeyArr(keyArr, inputNumber);
        int indexes[7] = {0};
        internal_enumerate(&enumerations, indexes, keyArr, 7);
        freeKeyArr(keyArr, 7);
        
        //threads
        pthread_t threads[3] = {NULL};
        for(int i = 0; i < 3; i++)
            pthread_detach(threads[i]);
        
        SearchArgs sArgs[3];
        for(int i = 0; i < 3; i++){
            sArgs[i].enums = &enumerations;
            sArgs[i].dict = &dict_arr;
            sArgs[i].fileout = fileout;
            sArgs[i].three_dict = &three_dict;
            sArgs[i].four_dict = &four_dict;
            if(i == 0){
                sArgs[i].search_end = sArgs[i].enums->length / 4;
                sArgs[i].search_start = 0;
            }
            else{
                //absolutely WRONG division of array searching for 3 & 4 length files
                sArgs[i].search_start = sArgs[i - 1].search_end + 1;
                sArgs[i].search_end = ((sArgs[i].enums->length / 4) * (i + 1)) + 1;
            }
            pthread_create(&threads[i], NULL, multi_search_caller, &sArgs[i]);
        }

        internal_search(
                        &enumerations,
                        sArgs[2].search_end + 1,
                        enumerations.length,
                        &dict_arr,
                        fileout,
                        7
                        );
        internal_search(
                        &enumerations,
                        sArgs[2].search_end + 1,
                        enumerations.length,
                        &three_dict,
                        fileout,
                        3
                        );
        internal_search(
                        &enumerations,
                        sArgs[2].search_end + 1,
                        enumerations.length,
                        &four_dict,
                        fileout,
                        4
                        );

        freeStringArray(&enumerations);
        freeStringArray(&dict_arr);
        
        freeStringArray(&three_dict);
        freeStringArray(&four_dict);
        pthread_exit(NULL);
    }

    
    
    return 0;
}
