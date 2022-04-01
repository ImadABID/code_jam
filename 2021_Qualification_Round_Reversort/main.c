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

int find_min(int *tab, int size){
    int min_index = 0;
    int min = tab[0];
    for(int i = 1; i < size; i++){
        if(tab[i] < min){
            min = tab[i];
            min_index = i;
        }
    }
    return min_index;
}

void reverse(int *tab, int size){
    int tab_tmp[size];
    for(int i = 0; i < size; i++){
        tab_tmp[size-1-i] = tab[i];
    }
    memcpy(tab, tab_tmp, size*sizeof(int));
}

int cost(int *test, int size){
    int c = 0;
    int t = 0;
    int next_min_index;
    while (t < size - 1){
        next_min_index = find_min(test+t, size-t);
        reverse(test+t, next_min_index+1);
        c += next_min_index +1;
        t++;
    }

    return c;
}

int main(){

    char *buffer = malloc(sizeof(char)*MAX_STR);

    next_word(buffer);

    int tests_nbr = atoi(buffer);

    int **tests = malloc(tests_nbr*sizeof(int *));
    int *tests_size = malloc(tests_nbr*sizeof(int));

    int test_size;
    for(int test_i = 0; test_i < tests_nbr; test_i++){
        
        next_word(buffer);
        test_size = atoi(buffer);

        tests_size[test_i] = test_size;

        tests[test_i] = malloc(test_size*sizeof(int));
        for(int ele_i = 0; ele_i < test_size; ele_i++){
            next_word(buffer);
            tests[test_i][ele_i] = atoi(buffer);
        }
    }

    //printf("%d\n", tests_nbr);
    // for(int test_i = 0; test_i < tests_nbr; test_i++){

    //     test_size = tests_size[test_i];

    //     for(int ele_i = 0; ele_i < test_size; ele_i++){
    //         printf("%d ", tests[test_i][ele_i]);
    //     }
    //     printf("\n");
    // }

    int c;
    for(int test_i = 0; test_i < tests_nbr; test_i++){

        test_size = tests_size[test_i];
        c = cost(tests[test_i], test_size);
        
        printf("Case #%d: %d\n", test_i+1, c);

    }



    for(int test_i = 0; test_i < tests_nbr; test_i++){
        free(tests[test_i]);
    }
    free(tests);
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