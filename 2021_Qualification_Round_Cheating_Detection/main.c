#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 10240

void next_word(char *word);

void print_tab(int *test, int test_size){
    for(int ele_i = 0; ele_i < test_size; ele_i++){
        printf("%d ", test[ele_i]);
    }
    printf("\n");
}

int compute_score(char *exam_cheet){
    int c = 0;
    for(int i = 0; i < 10000; i++){
        if(exam_cheet[i] == '1'){
            c++;
        }
    }
    return c;
}

int max_index(int *score){
    int max = 0;
    int max_i = 0;
    for(int i = 0; i < 100; i++){
        if(max < score[i]){
            max = score[i];
            max_i= i;
        }
    }
    return max_i;
}

int main(){

    char *buffer = malloc(sizeof(char)*MAX_STR);

    next_word(buffer);

    int tests_nbr = atoi(buffer);

    next_word(buffer); // P

    int *score = malloc(100*sizeof(int));

    for(int test_i = 0; test_i < tests_nbr; test_i++){

        for(int player = 0; player < 100; player++){
            next_word(buffer);
            score[player] = compute_score(buffer);
        }
        printf("Case #%d: %d\n", test_i+1, max_index(score)+1);

    }

    free(score);
    free(buffer);

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