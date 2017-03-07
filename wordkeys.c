#include <stdio.h>

char letter_to_digit(char letter){
    switch (letter){
        case 'a':
        case 'b':
        case 'c':
            return '2';
        case 'd':
        case 'e':
        case 'f':
            return '3';
        case 'g':
        case 'h':
        case 'i':
            return '4';
        case 'j':
        case 'k':
        case 'l':
            return '5';
        case 'm':
        case 'n':
        case 'o':
            return '6';
        case 'p':
        case 'q':
        case 'r':
        case 's':
            return '7';
        case 't':
        case 'u':
        case 'v':
            return '8';
        case 'w':
        case 'x':
        case 'y':
        case 'z':
            return '9';
    }
    fprintf(stderr, "you have provided an invalid digit '%c' to function 'letter_to_digit'\n", letter);
    return 0;
}

int main(int argc, char *argv[]){
    int i;
    for(i = 0; argv[1][i] != '\0'; i++)
        printf("%c", letter_to_digit(argv[1][i]));
    puts("");
}
