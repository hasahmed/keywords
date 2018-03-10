//  Created by Hasan Y Ahmed on 2/23/17.

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "utilfuncs.h"

int rand_lim(int limit) {
/* return a random number between 0 and limit inclusive.
 */

    int divisor = RAND_MAX/(limit+1);
    int retval;

    do { 
        retval = rand() / divisor;
    } while (retval > limit);

    return retval;
}


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
                printf("Your options may be ignored\n");
                strcpy(fileout, fileoutDefault);
                strcpy(dict, dictDefault);
                    // printErrorMessage();
                    // return 2;
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
        srand(time(NULL));
        if (strcmp(argv[1], "--rand") == 0 || strcmp(argv[1], "-r") == 0) {
            int i = 0;
            for (i = 0; i < 7; i++) {
                inum_tmp[i] = (rand_lim(7)) + 50; //random ascii character for numbers between 2 and 9. 52 because numbers start at 50. + 2 for ignoring 0 and 1
                // printf("%c\n", (rand() % 7) + 50);
            }
            inum_tmp[8] = 0;
            printf("random number: %s\n", inum_tmp);
        } else {
            strcpy(inum_tmp, argv[phnum_index]); //copy the command line input phone number into inum_tmp
        }
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
        internal_enumerate(&enumerations, indexes, keyArr, 7); //initialize enumerations array with all possible enumerations for given number
        freeKeyArr(keyArr, 7); //the key array is no longer needed hence free
        // </setup>
        internal_search(&enumerations, dict, fileout); //this is where the actual checking happens
        freeStringArray(&enumerations);
    }
    return 0; //if here is reached everything went okay
}
