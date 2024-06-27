/**Chapter 2, Section 6, Exercise 6 of Horowitz's Fundamentals of Data Structures in C.*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 100

char string1[MAX_SIZE];
char string2[MAX_SIZE];

//Function prototypes
void strnins(char *s, char *t, int i);
void altstrnins(char *s, char *t, int i);

int main(){
    char s[] = "amobile";
    char t[] = "uto";
    char pat[] = "auto";
    altstrnins(s, t, 1);
    //strnins(s, t, 1);
    printf("%s\n", s);
    getchar();
    return EXIT_SUCCESS;
}

//Function definitions
/**Inserts string t into string s at position i*/
void strnins(char *s, char *t, int i){
    char string[MAX_SIZE], *temp = string;
    if (i < 0 && i > strlen(s)){
        fprintf(stderr, "Position is out of bounds.\n");
        exit(1);
    }
    if (!strlen(s)) strcpy(s, t);
    else if (strlen(t)){
        strncpy(temp, s, i);
        strcat(temp, t);
        strcat(temp, (s + i));
        strcpy(s, temp);
    }
}

void altstrnins(char *s, char *t, int i){
    char string[MAX_SIZE];
    int j, k;
    if (i < 0 && i > strlen(s)){
        fprintf(stderr, "Postion is out of bounds\n");
        exit(1); 
    }
    if (!strlen(s)) strcpy(s,t);
    else if(strlen(t)) {
        for (j = strlen(s); j >= i; j--)
            s[j + strlen(t)] = s[j];
        k = 0;
        for (j = i; k < strlen(t); j++)
            s[j] = t[k++];
    }
}
