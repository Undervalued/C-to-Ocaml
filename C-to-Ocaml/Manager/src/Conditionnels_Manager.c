#include "Conditionnels_Manager.h"

void Conditionnels_Manager(maillon* start){
    char condition[512] = "";
    bool concat_then = false;
    if(strcmp(start->argument, "if") == 0){
        bool concat_then = true;
    }
    strcat(condition, start->argument); // On met le mot if ou else
    start = start->suivant; // On saute le mot cle
    // On lit la condition qu'est dans la parenthese.
    while (!(start->lexeme == 'P' && strcmp(start->argument, "{") == 0))
    {
        if(start->lexeme == 'V'){
            strcat(condition, "!");
            strcat(condition, start->argument);
        }
        else if(start->lexeme == 'B'){
            if(strcmp(start->argument, "!=") == 0){
                strcat(condition, "<>");
            }
            else if(strcmp(start->argument, "==") == 0){
                strcat(condition, "=");
            }else{
                strcat(condition, start->argument);
            }

        }else{
            strcat(condition, start->argument);
        }
        start = start -> suivant;
    }
    if(concat_then){
        strcat(condition, " then");
    }
    strcat(condition, "\nBEGIN\n");
    Line_Writer(condition); // on ecrit la ligne while (conditions) do 
    // printf("%s", condition);

    int crochets = 1;
    // On parcourt le contennu du if, et une fois qu'on a fini on ecrit END;;
    while (crochets > 0){
        if((start->lexeme == 'P' && strcmp(start->argument, "{") == 0)){
            crochets+=1;
        }
        else if((start->lexeme == 'P' && strcmp(start->argument, "}") == 0)){
            crochets-=1;
        }else{
            Line_Analyse(start);
            // printf("%s", start->argument);
        }
        start = start -> suivant;
    }
    Line_Writer("END\n");
    // printf("END\n");

}
