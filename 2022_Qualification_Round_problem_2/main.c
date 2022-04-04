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

int * all_compose_that_addup_to(
    int color_tab_size,
    int *printer1_color_tab,
    int *printer2_color_tab,
    int *printer3_color_tab,
    int addup_to,
    int *res_table_size
);

int *all_compose_that_addup_to(
    int color_tab_size,
    int *printer1_color_tab,
    int *printer2_color_tab,
    int *printer3_color_tab,
    int addup_to,
    int *res_table_size
){

    int *res_table;
    int res_table_curs;

    if(color_tab_size == 1){

        if(printer1_color_tab[0] >= addup_to && printer2_color_tab[0] >= addup_to && printer3_color_tab[0] >= addup_to){

            res_table = malloc(sizeof(int));
            *res_table = addup_to;

            *res_table_size = 1;
            return res_table;

        }else{
            *res_table_size = 0;
            return NULL;
        }

    }
    
    res_table = malloc(color_tab_size*sizeof(int));
    res_table_curs = 0;

    int *res_res_table;
    int res_res_table_size;

    int color_1_value = printer1_color_tab[0];

    int i, j;
    while(1){

        if(printer2_color_tab[0]<color_1_value || printer3_color_tab[0]<color_1_value){
            color_1_value--;
            continue;
        }

        if(color_1_value>=addup_to){
            res_table[0] = addup_to;
            for(int k = 1; k < color_tab_size; k++){
                res_table[k] = 0;
            }
            *res_table_size = color_tab_size;
            return res_table;
        }

        res_res_table = all_compose_that_addup_to(
            color_tab_size-1,
            printer1_color_tab+1,
            printer2_color_tab+1,
            printer3_color_tab+1,
            addup_to-color_1_value,
            &res_res_table_size
        );

        color_1_value--;

        if(res_res_table == NULL){
            break;
        }

        i = 0;
        j = 0;
        while(i < res_res_table_size){
            if(j%color_tab_size == 0){
                res_table[res_table_curs++] = color_1_value+1;
            }else{
                res_table[res_table_curs++] = res_res_table[i];
                i++;
            }
            j++;
        }

        free(res_res_table);

        break;

    }

    if(res_table_curs == 0){
        free(res_table);
        *res_table_size = 0;
        return NULL;
    }

    *res_table_size = res_table_curs;
    return res_table;

}

int main(){

    char *buffer = malloc(sizeof(char)*MAX_STR);

    next_word(buffer);

    int tests_nbr = atoi(buffer);

    int *colors_1 = malloc(4*sizeof(int));
    int *colors_2 = malloc(4*sizeof(int));
    int *colors_3 = malloc(4*sizeof(int));

    int nbr_res;
    int *sol;

    for(int test_i = 0; test_i < tests_nbr; test_i++){
        
        for(int i=0; i<4; i++){
            next_word(buffer);
            colors_1[i] = atoi(buffer);
        }
        for(int i=0; i<4; i++){
            next_word(buffer);
            colors_2[i] = atoi(buffer);
        }
        for(int i=0; i<4; i++){
            next_word(buffer);
            colors_3[i] = atoi(buffer);
        }

        printf("Case #%d: ", test_i+1);

        
        sol = all_compose_that_addup_to(4, colors_1, colors_2, colors_3, 1000000, &nbr_res);

        if(nbr_res > 0){
            print_tab(sol, nbr_res);
        }else{
            printf("IMPOSSIBLE\n");
        }
    }


    free(colors_1);
    free(colors_2);
    free(colors_3);
    
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