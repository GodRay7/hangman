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

void get_available_letters(const char letters_guessed[], char available_letters[]) {
    int lGlen = strlen(letters_guessed);
    char alph[27] = "abcdefghijklmnopqrstuvwxyz";
    int foundFlag;
    int x = 0;

    for (int i = 0; i < 26; i++) {
        foundFlag = 0;
        for (int j = 0; j < lGlen; j++) {
            if (letters_guessed[j] == alph[i]) {
                foundFlag = 1;
                break;
            }
        }
        if (!foundFlag) {
            available_letters[x] = alph[i];
            x++;
        }
    }
}

void hangman(const char secret[]){
    int secretLen = strlen(secret);
    int attemps = 8;
    char letters_guessed[27] = "";
    int letters_guessed_index;
    char available_letters[27];
    char input[255] = "", inputLen = 0;

    printf("Welcome to the game, Hangman!\n");
    printf("I am thinking of a word that is %i letters long.\n", secretLen);

    while(attemps > 0 && !is_word_guessed(secret, letters_guessed)){
        printf("-------------");
        printf("You have %i guesses left.\n", attemps);
        get_available_letters(letters_guessed, available_letters);
        printf("Available letters: %s\n", available_letters);

        printf("Please guess a letter: ");
        
        fgets(input, 255, stdin);
        inputLen = strlen(input) - 1;
        if(inputLen > 1){
            //this is string
        }else{
            //this is char
            //bad scenario:
            //1)uppercase => lowercase
            //2)anyother symbol => cancle
            char symbol = input[0];
            if(symbol >= 65 && symbol <= 90){
                symbol += 32;
            }
            if(symbol <= 97 || symbol >= 122){
                printf("Wrong symbol\n");
                continue;
            }
            letters_guessed[letters_guessed_index] = symbol;
            letters_guessed_index++;
            // 1) определеить есть ли такой символ в слове 
            // 2) если есть определить вводит ли его пользователь повторно: 
            // 2.1) если да уведомить его и пропустить попытку 
            // 2.2) если нет обновить слово 
            // 3) если нет -уведомить его и снять попытку
        }
        printf("%s\n", input);




        attemps--;
    }
}