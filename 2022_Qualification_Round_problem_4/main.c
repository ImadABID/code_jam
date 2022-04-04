#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#define MAX_STR 16

void next_word(char *word);

// --- tab

void print_tab(int *test, int test_size){
    for(int ele_i = 0; ele_i < test_size; ele_i++){
        printf("%d ", test[ele_i]);
    }
    printf("\n");
}

int tab_min(int *tab, int size){
    int min = tab[0];
    int min_index = 0;

    for(int i = 1; i < size; i++){
        if(min > tab[i]){
            min = tab[i];
            min_index = i;
        }
    }

    return min_index;
}

int llint_tab_min(long long int *tab, int size){
    long long int min = tab[0];
    int min_index = 0;

    for(int i = 1; i < size; i++){
        if(min > tab[i]){
            min = tab[i];
            min_index = i;
        }
    }

    return min_index;
}

void sort_fusion(int *tab, int size, int *mirror_tab, int *mirror_tab_index);

void sort_fusion(int *tab, int size, int *mirror_tab, int *mirror_tab_index){

    if(size == 1){
        return ;
    }

    int m = size / 2;

    int *tab1 = tab;
    int *mtab1 = mirror_tab;
    int *mitab1 = mirror_tab_index;
    int tab1_size = m;
    

    int *tab2 = tab+m;
    int *mtab2 = mirror_tab+m;
    int *mitab2 = mirror_tab_index+m;
    int tab2_size = size-m;
    
    sort_fusion(tab1, tab1_size, mtab1, mitab1);
    sort_fusion(tab2, tab2_size, mtab2, mitab2);

    int tmp_tab[size];
    int tmp_mtab[size];
    int tmp_mitab[size];

    int tab1_i = 0;
    int tab2_i = 0;
    for(int i=0; i < size; i++){
        
        if(tab1_i >= tab1_size){
            tmp_tab[i] = tab2[tab2_i];
            tmp_mtab[i] = mtab2[tab2_i];
            tmp_mitab[i] = mitab2[tab2_i];
            tab2_i++;
            continue;
        }

        if(tab2_i >= tab2_size){
            tmp_tab[i] = tab1[tab1_i];
            tmp_mtab[i] = mtab1[tab1_i];
            tmp_mitab[i] = mitab1[tab1_i];
            tab1_i++;
            continue;
        }

        if(tab1[tab1_i] < tab2[tab2_i]){
            tmp_tab[i] = tab1[tab1_i];
            tmp_mtab[i] = mtab1[tab1_i];
            tmp_mitab[i] = mitab1[tab1_i];
            tab1_i++;
        }else{
            tmp_tab[i] = tab2[tab2_i];
            tmp_mtab[i] = mtab2[tab2_i];
            tmp_mitab[i] = mitab2[tab2_i];
            tab2_i++;
        }
    }

    memcpy(tab, tmp_tab, size*sizeof(int));
    memcpy(mirror_tab, tmp_mtab, size*sizeof(int));
    memcpy(mirror_tab_index, tmp_mitab, size*sizeof(int));
}


struct tab_map{
    int val;
    int rep_nbr;
    int start_index;
};

struct tab_map *sorted_tab_map(int *tab, int tab_size, int *map_size){

    struct tab_map tmp_tb[tab_size];
    int tmp_tb_curs = 0;

    int val = tab[0];
    int comp = 1;
    int last_index = 0;
    for(int i = 1; i < tab_size; i++){
        if(tab[i] != val){

            tmp_tb[tmp_tb_curs].val = val;
            tmp_tb[tmp_tb_curs].rep_nbr = comp;
            tmp_tb[tmp_tb_curs].start_index = last_index;
            tmp_tb_curs++;

            val++;

            while(val != tab[i]){

                tmp_tb[tmp_tb_curs].val = val;
                tmp_tb[tmp_tb_curs].rep_nbr = 0;
                tmp_tb[tmp_tb_curs].start_index = -1;
                tmp_tb_curs++;

                val++;

            }

            comp = 1;
            last_index = i;

        }else{
            comp++;
        }
    }

    tmp_tb[tmp_tb_curs].val = val;
    tmp_tb[tmp_tb_curs].rep_nbr = comp;
    tmp_tb[tmp_tb_curs].start_index = last_index;
    tmp_tb_curs++;

    struct tab_map *tb = malloc(tmp_tb_curs*sizeof(struct tab_map));
    memcpy(tb, tmp_tb, tmp_tb_curs*sizeof(struct tab_map));

    *map_size = tmp_tb_curs;
    return tb;
}

// ---

// --- Tree

struct tree {

    int index;
    int fun_factor;

    struct tree **sub_trees;
    int sub_trees_size;
};

struct tree *create_tree(
    int index,
    int *modules_fun_fac,
    int *modules_fun_fac_index,
    int tabs_size,
    struct tab_map *module_attached_map,
    int map_size
){

    struct tree *t = malloc(sizeof(struct tree *));

    t->index = index;

    for(int i = 0; i < tabs_size; i++){
        if(modules_fun_fac_index[i] == index){
            t->fun_factor = modules_fun_fac[i];
            break;
        }
    }



    if(index < map_size){

        t->sub_trees_size = module_attached_map[index].rep_nbr;

        if(module_attached_map[index].rep_nbr == 0){
            t->sub_trees = NULL;
        }else{

            t->sub_trees = malloc(module_attached_map[index].rep_nbr*sizeof(struct tree *));

            for(int i = 0; i < module_attached_map[index].rep_nbr; i++){
                (t->sub_trees)[i] = create_tree(
                    modules_fun_fac_index[module_attached_map[index].start_index+i],
                    modules_fun_fac,
                    modules_fun_fac_index,
                    tabs_size,
                    module_attached_map,
                    map_size
                );
            }

        }

    }else{
        t->sub_trees_size = 0;
        t->sub_trees = NULL;
    }

    return t;

}

void free_tree(struct tree *t){
    for(int i = 0; i < t->sub_trees_size; i++){
        free_tree((t->sub_trees)[i]);
    }
    free(t->sub_trees);
    free(t);
}

void print_tree(struct tree *t){
    printf("(index = %d, fun_factor = %d)", t->index, t->fun_factor);
    if(t->sub_trees_size > 0){
        printf("{");
        for(int i = 0; i < t->sub_trees_size; i++){
            print_tree(t->sub_trees[i]);
            printf(",");
        }
        printf("}");
    }
}

void compute_tree_score(struct tree *t, long long int *potentiel_score, long long int *confirmed_score){

    if(t->sub_trees_size == 0){
        *confirmed_score = 0 ;
        *potentiel_score = t->fun_factor;
        return;
    }

    *confirmed_score = 0;

    long long int confirmed_score_tmp, potentiel_score_tmp;

    long long int sub_potentiel_score[t->sub_trees_size];

    for(int i = 0; i < t->sub_trees_size; i++){
        
        compute_tree_score(t->sub_trees[i], &potentiel_score_tmp, &confirmed_score_tmp);

        // printf(" * computing subtree %d: p_score = %lld, c_score = %lld,\n", (t->sub_trees[i])->fun_factor, potentiel_score_tmp, confirmed_score_tmp);
        
        *confirmed_score += confirmed_score_tmp;
        sub_potentiel_score[i] = potentiel_score_tmp;
        
    }

    int min_pot_score_index = llint_tab_min(sub_potentiel_score, t->sub_trees_size);

    
    long long int last_p_score = sub_potentiel_score[min_pot_score_index];
    if(last_p_score > t->fun_factor){
        *potentiel_score = last_p_score;
    }else{
        *potentiel_score = t->fun_factor;
    }

    for(int i = 0; i < t->sub_trees_size; i++){
        if(i != min_pot_score_index){
            *confirmed_score += sub_potentiel_score[i];
        }
    }

}


// ---



int main(){

    char *buffer = malloc(sizeof(char)*MAX_STR);

    next_word(buffer);

    int tests_nbr = atoi(buffer);

    int trees_nbr;
    struct tree **trees;
    
    int modules_nbr;
    int *modules_fun_fac;
    int *modules_fun_fac_index;
    int *modules_attache;

    for(int test_i = 0; test_i < tests_nbr; test_i++){
        
        next_word(buffer);
        modules_nbr = atoi(buffer);

        modules_fun_fac = malloc(modules_nbr*sizeof(int));
        modules_fun_fac_index = malloc(modules_nbr*sizeof(int));
        modules_attache = malloc(modules_nbr*sizeof(int));

        for(int i = 0; i<modules_nbr; i++){

            next_word(buffer);
            modules_fun_fac[i] = atoi(buffer);

            modules_fun_fac_index[i] = i+1;
        }
        for(int i = 0; i<modules_nbr; i++){
            next_word(buffer);
            modules_attache[i] = atoi(buffer);
        }

       

        sort_fusion(modules_attache, modules_nbr, modules_fun_fac, modules_fun_fac_index);

        int map_size;
        struct tab_map * map = sorted_tab_map(modules_attache, modules_nbr, &map_size);

        long long int score = 0;
        long long int p_score, c_score;
        trees_nbr = map[0].rep_nbr;
        trees = malloc(map[0].rep_nbr*sizeof(struct tree));
        for(int i = 0; i < trees_nbr; i++){
            trees[i] = create_tree(
                modules_fun_fac_index[map[0].start_index+i],
                modules_fun_fac,
                modules_fun_fac_index,
                modules_nbr,
                map,
                map_size
            );

            // print_tree(trees[i]);
            // printf("\n");

            
            compute_tree_score(trees[i], &p_score, &c_score);
            // printf("computing subtree %d: p_score = %lld, c_score = %lld,\n", (trees[i])->fun_factor, p_score, c_score);

            score += p_score+c_score;

        }

        printf("Case #%d: %lld\n", test_i+1, score);
        

        
        for(int i = 0; i < trees_nbr; i++){
            free_tree(trees[i]);
        }
        free(trees);


        free(map);

        free(modules_fun_fac);
        free(modules_fun_fac_index);
        free(modules_attache);

    }

    // int tab[6];
    // tab[0] = 1;
    // tab[1] = 0;
    // tab[2] = 2;
    // tab[3] = 2;
    // tab[4] = 0;
    // tab[5] = 2;

    // int mtab[6];
    // mtab[0] = 10;
    // mtab[1] = 15;
    // mtab[2] = 6;
    // mtab[3] = 942;
    // mtab[4] = 46;
    // mtab[5] = 827;

    // print_tab(tab, 6);
    // print_tab(mtab, 6);

    // sort_fusion(tab, 6, mtab);

    // print_tab(tab, 6);
    // print_tab(mtab, 6);

    // int tm_size;
    // struct tab_map *tm = sorted_tab_map(tab, 6, &tm_size);

    // printf("tm_size = %d\n", tm_size);
    // for(int i = 0; i < tm_size; i++){
    //     printf("%d of %d\n", tm[i].rep_nbr, tm[i].val);
    // }
    
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