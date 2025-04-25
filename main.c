#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hangman.h"

int main () {
    srand(time(NULL));

    char secret[11];

    int result = get_word(secret);
    if(result){
        return 1;
    }
    printf("%s\n", secret);

    printf("%d\n",is_word_guessed("secret", "aeiou"));
    // prints: 0
    printf("%d\n",is_word_guessed("hello", "aeihoul"));
    // prints: 1

    char result1[30];
    get_guessed_word("container", "arpstxgoieyu", result1);
    printf("%s\n", result1); 
    


    return 0;
}