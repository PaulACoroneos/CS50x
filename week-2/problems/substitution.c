#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main (int argc, char *argv[]) {

    //is key even passed?
    if(argc < 2) {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];

    //is key at least 26 chars?
    int keyLen = strlen(argv[1]);
    if(keyLen != 26 ) {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    //does key contain only alpha character and no dupes
    char lettersInKey[26];
    for(int i = 0; i< keyLen; i++) {
        if(!isalpha(key[i]) || strchr(lettersInKey,key[i])) {
            printf("Usage: ./substitution key\n");
            return 1;
        }
        lettersInKey[i] = key[i];
    }

    //normalize key to upper case
    for(int i =0; i< keyLen; i++) {
        key[i] = toupper(key[i]);
    }

    string plaintext = get_string("plaintext: ");

    //now letter by letter convert plaintext
    for(int i = 0; i< strlen(plaintext); i++) {
        if(isalpha(plaintext[i])) {
            if(isupper(plaintext[i])) {
                plaintext[i] = key[ (int) plaintext[i] - 65];
            }
            else {
                plaintext[i] = tolower(key[ (int) plaintext[i] - 97]);
            }
        }
    }

    printf("ciphertext: %s",plaintext);
    printf("\n");

    return 0;
}