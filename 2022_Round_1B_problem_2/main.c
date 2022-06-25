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

typedef long long int pression;


void sort_fusion(pression *tab, int size);

void sort_fusion(pression *tab, int size){

    if(size == 1){
        return ;
    }

    int m = size / 2;

    pression *tab1 = tab;
    int tab1_size = m;

    pression *tab2 = tab+m;
    int tab2_size = size-m;
    
    sort_fusion(tab1, tab1_size);
    sort_fusion(tab2, tab2_size);

    pression tmp_tab[size];

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

    memcpy(tab, tmp_tab, size*sizeof(pression));
}

pression my_abs(pression a){
    if(a<0)
        return -a;
    return a;
}

pression my_min(pression *tab, int size){
    pression min = tab[0];
    for(int i = 1; i< size; i++){
        if(min > tab[i]){
            min = tab[i];
        }
    }
    return min;
}

pression nbr_click_per_client(pression *tab, int tab_size, pression *min, pression *max){

    sort_fusion(tab, tab_size);

    pression nbr_click = tab[0];

    for(int i = 1; i < tab_size; i++){
        nbr_click += (tab[i] - tab[i-1]);
    }

    *min = tab[0];
    *max = tab[tab_size-1];

    return nbr_click;
}


struct client_usefull_info{
    pression max_pression;
    pression min_pression;
    pression nbr_clicks;
};

pression compute_trans(
    struct client_usefull_info c1,
    struct client_usefull_info c2,
    pression **tans,
    int trans_index
){

    tans[0][trans_index] = my_abs(c1.max_pression-c2.max_pression);
    tans[1][trans_index] = my_abs(c1.max_pression-c2.min_pression);
    tans[2][trans_index] = my_abs(c1.min_pression-c2.max_pression);
    tans[3][trans_index] = my_abs(c1.min_pression-c2.min_pression);

}

void update_path(
    pression *price,
    pression *last_price,
    pression **tans,
    int path_index,
    struct client_usefull_info c
){

    // 0
    if(last_price[1]+tans[1][path_index] < last_price[3]+tans[3][path_index]){
        price[0] = last_price[1]+tans[1][path_index];
    }else{
        price[0] = last_price[3]+tans[3][path_index];
    }

    // 1
    if(last_price[1]+tans[1][path_index] < last_price[3]+tans[3][path_index]){
        price[1] = last_price[1]+tans[1][path_index];
    }else{
        price[1] = last_price[3]+tans[3][path_index];
    }

    // 2
    if(last_price[0]+tans[0][path_index] < last_price[2]+tans[2][path_index]){
        price[2] = last_price[0]+tans[0][path_index];
    }else{
        price[2] = last_price[2]+tans[2][path_index];
    }

    // 3
    if(last_price[0]+tans[0][path_index] < last_price[2]+tans[2][path_index]){
        price[3] = last_price[0]+tans[0][path_index];
    }else{
        price[3] = last_price[2]+tans[2][path_index];
    }

    for(int i = 0; i < 4; i++){
        price[i] += c.nbr_clicks;
    }

    memcpy(last_price, price, 4*sizeof(pression));

}

int main(){

    pression **tans = malloc(4*sizeof(pression*));

    pression price[4];
    pression last_price[4];
    memset(last_price, 0, 4*sizeof(pression));

    pression *products_pres_buffer;
    struct client_usefull_info *usfull_info_tab;


    char *buffer = malloc(sizeof(char)*MAX_STR);

    next_word(buffer);

    int tests_nbr = atoi(buffer);

    int N, P;
    for(int test_i = 0; test_i < tests_nbr; test_i++){
        
        next_word(buffer);
        N = atoi(buffer);

        next_word(buffer);
        P = atoi(buffer);

        products_pres_buffer = malloc(P * sizeof(pression));

        usfull_info_tab = malloc(N * sizeof(struct client_usefull_info));

        for(int ni = 0; ni < N; ni++){

            for(int pi = 0; pi < P; pi++){
                next_word(buffer);
                products_pres_buffer[pi] = atoi(buffer);
            }

            usfull_info_tab[ni].nbr_clicks = nbr_click_per_client(products_pres_buffer, P, &usfull_info_tab[ni].min_pression, &usfull_info_tab[ni].max_pression);

        }

        free(products_pres_buffer);

        //trans table
        for(int i = 0; i < 4; i++){
            tans[i] = malloc(N*sizeof(pression));
        }
        for(int ni = 0; ni < N; ni++){

            if(ni==0){

                struct client_usefull_info c;
                c.max_pression = 0;
                c.min_pression = 0;

                compute_trans(c, usfull_info_tab[ni], tans, ni);

            }else{

                compute_trans(usfull_info_tab[ni-1], usfull_info_tab[ni], tans, ni);

            }
        }

        // price
        for (int ni = 0; ni < N; ni++){
            update_path(
                price,
                last_price,
                tans,
                ni,
                usfull_info_tab[ni]
            );
        }

        printf("Case #%d: %lld\n", test_i+1, my_min(price, 4));

        for(int i = 0; i < 4; i++){
            free(tans[i]);
        }


        free(usfull_info_tab);


    }
    
    free(buffer);
    free(tans);

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