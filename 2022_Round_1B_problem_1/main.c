#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#define MAX_STR 120

void next_word(char *word);


int main(){

    char buffer[MAX_STR];

    next_word(buffer);

    int tests_nbr = atoi(buffer);

    long int *deque; 
    int deque_size;

    int ml, mr;
    int y;

    int max_last;
    int current;

    for(int test_i = 0; test_i < tests_nbr; test_i++){
        
        next_word(buffer);
        deque_size = atoi(buffer);

        deque = malloc(deque_size * sizeof(long int));

        for(int i = 0; i < deque_size; i++){
            next_word(buffer);
            deque[i] = atoi(buffer);
        }

        ml = 0;
        mr = deque_size-1;
        y = 0;
        max_last = -1;

        while(ml!=mr){
            if(deque[ml] < deque[mr]){
                current = deque[ml];
                ml++;
            }else{
                current = deque[mr];
                mr--;
            }

            if(current >= max_last){
                y++;
                max_last = current;
            }

        }

        if(deque[ml] >= max_last){
            y++;
        }

        printf("Case #%d: %d\n", test_i+1, y);

        free(deque);

    }

    
    return 0;
}

void next_word(char *word){
    char c = fgetc(stdin);
    int i=0;

    while(c!=' ' && c!='\n' && c!=EOF && c!='\0'){
        word[i++] = c;
        c = fgetc(stdin);
    }

    word[i] = '\0';
}