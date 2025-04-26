#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hangman.h"

int main () {
    srand(time(NULL));

    char secret[11];

    int resultWord = get_word(secret);
    if(resultWord){
        return 1;
    }
    printf("%s\n", secret);

    printf("%d\n",is_word_guessed("secret", "aeiou"));
    // prints: 0
    printf("%d\n",is_word_guessed("hello", "aeihoul"));
    // prints: 1

    char result[30];
    get_available_letters("arpstxgoieyu", result);
    printf("%s", result);



    return 0;
}