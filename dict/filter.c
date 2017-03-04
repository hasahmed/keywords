#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void writeout(FILE *readfile, FILE *outfile, int outWordLen){
    char buff[50];
    while(!feof(readfile)){
        fscanf(readfile, "%s", buff);
        if(strlen(buff) == outWordLen)
            fprintf(outfile, "%s\n", buff);
    }

}
int main(int argc, char **argv){
    if(argc < 4){
        fprintf(stderr, "\nuseage1:\nfilter word_length output_file dict\n");
        fprintf(stderr, "\nuseage2:\nfilter word_length output_file dict1 dict2 ...\n");
        fprintf(stderr, "\n\n Example: filter 7 7letterwords.txt words.txt words2.txt words3.txt\n\n");
    }
    else{    
        FILE *fout = fopen(argv[2], "w");
        int wordLen = atoi(argv[1]);
        int i;
        for(i = 3; i < argc; i++){
            FILE *dict = fopen(argv[i], "r");
            writeout(dict, fout, wordLen);
            fclose(dict);
        }
    }
}
