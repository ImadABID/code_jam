#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#define MAX_STR 20

void next_word(char *word);

//-----

int sum_tab(char *tab, char size){
    int s = 0;

    for(char i = 0; i < size; i++){
        s+=tab[i];
    }

    return s;
}

//----


int main(){

    char buffer[MAX_STR];

    next_word(buffer);
    char tests_nbr = (char) atoi(buffer);

    char **trainning_session;       // w_type for eache w
    char **trainning_session_index; // relative to same type
    char nbr_exercies;
    char w_types_nbr;
    int w;

    for(char test_i = 0; test_i < tests_nbr; test_i++){
        
        next_word(buffer);
        nbr_exercies = (char) atoi(buffer);

        trainning_session = malloc(nbr_exercies*sizeof(char *));
        trainning_session_index = malloc(nbr_exercies*sizeof(char *));

        next_word(buffer);
        w_types_nbr = (char) atoi(buffer);

        char exerice_compressed_desc[w_types_nbr];

        int w_nbr;

        for(char exercise_i = 0; exercise_i<nbr_exercies; exercise_i++){
            
            // reading data
            for(char w_type_i = 0; w_type_i < w_types_nbr; w_type_i++){
                next_word(buffer);
                exerice_compressed_desc[w_type_i] = (char) atoi(buffer);
            }

            w_nbr = sum_tab(exerice_compressed_desc, w_types_nbr);
            trainning_session[exercise_i] = malloc(w_nbr * sizeof(char));
            trainning_session_index[exercise_i] = malloc(w_nbr * sizeof(char));


            w = 0;
            for(char w_type_i = 0; w_type_i < w_types_nbr; w_type_i++){
                for(int i=0; i < exerice_compressed_desc[w_type_i]; i++){
                    trainning_session[exercise_i][w] = w_type_i;
                    trainning_session_index[exercise_i][w] = i;
                    w++;
                }
            }

            
        }

        // -- process

        

        // process ---

        for(char exercise_i = 0; exercise_i<nbr_exercies; exercise_i++){
            free(trainning_session[exercise_i]);
        }
        free(trainning_session);
        

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