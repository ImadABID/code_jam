#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 16

void next_word(char *word);

void print_tab(int *test, int test_size){
    for(int ele_i = 0; ele_i < test_size; ele_i++){
        printf("%d ", test[ele_i]);
    }
    printf("\n");
}

void print_ascii_art(int r, int c){
    for(int ri = 0; ri < r; ri++){
        if(ri==0){

            printf("..+");
            for(int ci = 1; ci < c; ci++){
                printf("-+");
            }
            printf("\n");

            printf("..|");
            for(int ci = 1; ci < c; ci++){
                printf(".|");
            }
            printf("\n");

            printf("+");
            for(int ci = 0; ci < c; ci++){
                printf("-+");
            }
            printf("\n");

        }else{

            printf("|");
            for(int ci = 0; ci < c; ci++){
                printf(".|");
            }
            printf("\n");

            printf("+");
            for(int ci = 0; ci < c; ci++){
                printf("-+");
            }
            printf("\n");

        }
    }
}

int main(){

    char *buffer = malloc(sizeof(char)*MAX_STR);

    next_word(buffer);

    int tests_nbr = atoi(buffer);

    int r,c;
    for(int test_i = 0; test_i < tests_nbr; test_i++){
        
        next_word(buffer);
        r = atoi(buffer);

        next_word(buffer);
        c = atoi(buffer);

        printf("Case #%d:\n", test_i+1);

        print_ascii_art(r, c);

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