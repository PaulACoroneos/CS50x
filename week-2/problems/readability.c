#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

double calcColemanLiau(double avgLetters, double avgSentences);
int countLetters(string word);
int countWords(string sentence);
int countSentences(string excerpt);

int main(void) {

    int grade;
    int letters;
    int words;
    int sentences;
    double avgLetters;
    double avgSentences;

    string entry = get_string("Enter an excerpt to determine grade level difficulty: ");

    letters = countLetters(entry);
    words = countWords(entry);
    sentences = countSentences(entry);

    avgLetters =  ((double) letters/words)*100.0;
    avgSentences = ((double) sentences/words)*100.0;

    grade = round(calcColemanLiau(avgLetters,avgSentences));

    //report result to user
    if( grade < 1) {
        printf("Before Grade 1\n");
    }
    else if (grade > 16) {
        printf("Grade 16+\n");
    }
    else {
        printf("Grade %i\n",grade);
    }
}

int countLetters(string word) {
    int count = 0;
    for(int i =0; i< strlen(word); i++) {
        if(isalpha(word[i])) {
            count++;
        }
    }
    return count;
}

int countWords(string sentence) {
    int count = 1;
    for(int i =0; i< strlen(sentence); i++) {
        if(isspace(sentence[i])) {
            count++;
        }
    }
    return count;
}

double calcColemanLiau(double avgLetters, double avgSentences) {
    return (0.0588 * avgLetters) - (0.296 * avgSentences) - 15.8;
}

int countSentences(string excerpt) {
    int count = 0;
    for(int i =0; i< strlen(excerpt); i++) {
        if(excerpt[i] == '.' || excerpt[i] == '?' || excerpt[i] == '!') {
            count++;
        }
    }
    return count;
}