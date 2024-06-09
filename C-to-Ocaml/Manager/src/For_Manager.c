
#include "./../Headers/For_Manager.h"


void For_Manager(maillon* start){
    start = start->suivant; // On saute le mot cle for
    char condition[512] = "while";
    bool can_exit = 0;
    // for(a;b;c)
    // (1) On declare a
    // (2) On cree la boucle while avec la condition b
    // (3) On effectue la "commande" c dans la boucle while a chaque passage 

    // Ici dans cette boucle (ecrite sous overdose de caffeine)
    // Ce qu'on fait c'est tout simplement parcourir la parenthese avec les parametres du for
    // et effectuer les etapes (1) (2) (3) 
    int compteur = 0;
    while (!(start->lexeme == 'P' && strcmp(start->argument, ")") == 0)){
        if(start->lexeme == 'T'){
            easy_strings_jumper(start);
            AssignSymbolDeclaration(start); // (1)
        }
        else if(start->lexeme == 'P' && strcmp(start->argument, ";") == 0){
            compteur+=1;
        }
        else if(start->lexeme == 'V'){
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
        if(compteur == 1){
            strcat(condition, ") do\n");
            compteur+=1;
        }
        start = start -> suivant;
    }
    strcat(condition, ";\n");
    Line_Writer(condition);
    int crochets = 1;
    start = start -> suivant; // on saute la ) qu'est reste de la boucle d'avans
    Line_Analyse_Loop(start);
    Line_Writer("done;;\n");
}