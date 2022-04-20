#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#define MAX_STR 120

void next_word(char *word);


int main(){

    char buffer[MAX_STR];
    char output[2*MAX_STR];

    next_word(buffer);

    int tests_nbr = atoi(buffer);

    for(int test_i = 0; test_i < tests_nbr; test_i++){
        
        next_word(buffer);

        int in_i = 0;
        int out_i = 0;
        int ii;
        while(1){

            if(buffer[in_i+1] == '\0'){
                output[out_i] = buffer[in_i];
                output[out_i+1] = '\0'; 
                break;
            }

            ii = in_i+1;
            while(buffer[in_i] == buffer[ii]){
                ii++;
                if(buffer[ii] == '\0'){
                    ii = in_i; // do nothing
                    break;
                }
            }

            if(buffer[in_i] < buffer[ii]){
                
                output[out_i] = buffer[in_i];
                output[out_i+1] = buffer[in_i];
                out_i += 2;
            }else{
                output[out_i] = buffer[in_i];
                out_i++;
            }

            in_i++;
        }

        printf("Case #%d: %s\n", test_i+1, output);

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