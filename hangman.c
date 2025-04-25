#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "hangman.h"


int get_word(char secret[]){
    // check if file exists first and is readable
    FILE *fp = fopen(WORDLIST_FILENAME, "rb");
    if( fp == NULL ){
        fprintf(stderr, "No such file or directory: %s\n", WORDLIST_FILENAME);
        return 1;
    }

    // get the filesize first
    struct stat st;
    stat(WORDLIST_FILENAME, &st);
    long int size = st.st_size;

    do{
        // generate random number between 0 and filesize
        long int random = (rand() % size) + 1;
        // seek to the random position of file
        fseek(fp, random, SEEK_SET);
        // get next word in row ;)
        int result = fscanf(fp, "%*s %20s", secret);
        if( result != EOF )
            break;
    }while(1);

    fclose(fp);

    return 0;
}

int is_word_guessed(const char secret[], const char letters_guessed[]){
    //code...
    int secretLen = strlen(secret);
    int lettersLen = strlen(letters_guessed);
    int notFoundFlag;
    for(int i = 0; i < secretLen; i++ ){
        notFoundFlag = 1;
        for(int j = 0; j < lettersLen; j++){
            if(letters_guessed[j] == secret[i]){
                notFoundFlag = 0;
                break;
            }
        }
        if(notFoundFlag){
            return 0;
        }
    }
    return 1;
}
void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[]) {
    int length = strlen(secret);
    for (int i = 0; i < length; i++) {
        int found = 0;
        for (int j = 0; letters_guessed[j] != '\0'; j++) {
            if (secret[i] == letters_guessed[j]) {
                found = 1;
                break;
            }
        }
        guessed_word[i] = found ? secret[i] : '_';
    }
    guessed_word[length] = '\0';
}