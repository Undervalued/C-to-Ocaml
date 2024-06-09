#include "./../Headers/While_Manager.h"

maillon* While_Manager(maillon* start){
    start = start->suivant; // On saute le mot cle while
    char condition[512] = "while ";
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
    strcat(condition, " do\n");
    Line_Writer(condition); // on ecrit la ligne while (conditions) do 
    // On parcourt le contennu de la boucle, et une fois qu'on a fini on ecrit done;;
    start = Line_Analyse_Loop (start);
    Line_Writer("done;;");
    return start;
}