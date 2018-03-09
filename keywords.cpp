//  Created by Hasan Y Ahmed on 2/23/17.

#include <string.h>
#include "utilfuncs.hpp"

void printErrorMessage(){
    fprintf(stderr, "\nusage: keywords [-options] phoneNumber\n");
    fprintf(stderr, " -o    specify output file\n -d    specify dictionary file\n");
    fprintf(stderr, "\n **note** \nif using the -d and -o options together, the files\n"
            "must come in the same order as the options.\n"
            "By default the output file\n"
            "is matches.txt, and the dictionary file is dict/7letterdict.txt\n\n");
}

int main(int argc, const char *argv[]) {
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
        if(strcmp(argv[1], "-o") == 0 && strcmp(argv[2], "-d") != 0){ //if there is only output file option
            strcpy(fileout, argv[2]);
            strcpy(dict, dictDefault);
            phnum_index = 3;
        } else if(strcmp(argv[1], "-d") == 0 && strcmp(argv[2], "-o") != 0){ //if there is only the dictionary option
            strcpy(dict, argv[2]);
            strcpy(fileout, fileoutDefault);
            phnum_index = 3;
        } else {
            if(strcmp(argv[1], "-o") == 0 && strcmp(argv[2], "-d") == 0){ //if there are both options
                strcpy(fileout, argv[3]);
                strcpy(dict, argv[4]);
                phnum_index = 5;
            } else if(strcmp(argv[1], "-d") == 0 && strcmp(argv[2], "-o") == 0){ //if there are both options
                strcpy(dict, argv[3]);
                strcpy(fileout, argv[4]);
                phnum_index = 5;
            } else { //if there there are neither options
                if(argv[1][0] == '-'){ //if there is an option other than -d or -o
                    printErrorMessage();
                    return 2;
                } else { //there are no options so take the default
                    strcpy(fileout, fileoutDefault);
                    strcpy(dict, dictDefault);
                }
            }
        }
        /*
         * Need to make sure that there is a number given as input even when arguments are passed in. Right now it is un
         * checked
         */
        //end input argument processessing

        //<setup before actaul processesing>
        char inputNumber[8];
        char inum_tmp[9];
        strcpy(inum_tmp, argv[phnum_index]); //copy the command line input phone number into inum_tmp
        undash(inum_tmp); //remove the dash from the number
        strcpy(inputNumber, inum_tmp); //copy into inputNumer

        if(!isValidNumber(inputNumber)){
            fprintf(stderr, "error: phone number must NOT contain any 0s or 1s\n");
            return 3;
        }
        StringArray enumerations; // for enumerating all the possible letter combinations possible with the given phone
                                    // number
        Key keyArr[7]; //array of Keys
        initKeyArr(keyArr, inputNumber);
        int indexes[7] = {0};
        internal_enumerate(&enumerations, indexes, keyArr, 7); //initialize enumerations array with all possible
                                                                // enumerations for given number
        freeKeyArr(keyArr, 7); //the key array is no longer needed hence free
        // </setup>
        internal_search(&enumerations, dict, fileout); //this is where the actual checking happens
    }
    return 0; //if here is reached everything went okay
}
