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

// void sort(int *tab, int size){
//     int tmp;
//     for(int i = 0; i<size; i++){
//         for(int j = 0; j < size-i-1; j++){
//             if(tab[j]>tab[j+1]){
//                 tmp = tab[j];
//                 tab[j] = tab[j+1];
//                 tab[j+1] = tmp;
//             }
//         }
//     }
// }

void sort_fusion(int *tab, int size);

void sort_fusion(int *tab, int size){

    if(size == 1){
        return ;
    }

    int m = size / 2;

    int *tab1 = tab;
    int tab1_size = m;

    int *tab2 = tab+m;
    int tab2_size = size-m;
    
    sort_fusion(tab1, tab1_size);
    sort_fusion(tab2, tab2_size);

    int tmp_tab[size];

    int tab1_i = 0;
    int tab2_i = 0;
    for(int i=0; i < size; i++){
        
        if(tab1_i >= tab1_size){
            tmp_tab[i] = tab2[tab2_i];
            tab2_i++;
            continue;
        }

        if(tab2_i >= tab2_size){
            tmp_tab[i] = tab1[tab1_i];
            tab1_i++;
            continue;
        }

        if(tab1[tab1_i] < tab2[tab2_i]){
            tmp_tab[i] = tab1[tab1_i];
            tab1_i++;
        }else{
            tmp_tab[i] = tab2[tab2_i];
            tab2_i++;
        }
    }

    memcpy(tab, tmp_tab, size*sizeof(int));
}

int long_straight(int *tab, int size){
    int first_index = 0;
    for(int i = 0; i<size; i++){
        if(tab[i]-1 < i - first_index){
            first_index++;
        }
    }
    return size - first_index;
}



int main(){

    char *buffer = malloc(sizeof(char)*MAX_STR);

    next_word(buffer);

    int tests_nbr = atoi(buffer);

    int *des_tab;
    int des_tab_size;
    for(int test_i = 0; test_i < tests_nbr; test_i++){
        
        next_word(buffer);
        des_tab_size = atoi(buffer);

        des_tab = malloc(des_tab_size * sizeof(int));

        for(int i = 0; i <  des_tab_size; i++){
            next_word(buffer);
            des_tab[i] = atoi(buffer);
        }

        sort_fusion(des_tab, des_tab_size);

        printf("Case #%d: %d\n", test_i+1, long_straight(des_tab, des_tab_size));

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