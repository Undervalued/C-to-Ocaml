

#include "Printf_Manager.h"

void Printf_Manager(maillon* maillons){
    // On suppose que l'utilisateur a 2 neurones et n'ecrit pas " printf         () "
    // Mais on ne fait pas confiance a l'utilisateur et donc on saute les espaces.
    maillons = easy_strings_jumper(maillons->suivant->suivant); // on saute la (
    char ligne[256] = "Printf.printf ";
    int compteur_parentheses = 0;
    while ( !(maillons->lexeme == 'P' && strcmp(maillons->argument, ";") == 0))
    {
        printf("%s\n", ligne);
        if(compteur_parentheses != 0){
            
            if(maillons->lexeme != 'V' && maillons->lexeme != 'S'){
                strcat(ligne, maillons->argument);
            }
            if(maillons->lexeme == 'P' && strcmp(maillons->argument, ")") == 0){
                compteur_parentheses-=1;
                strcat(ligne, " ");
            }
        }
        if(maillons->lexeme == 'S'){
            strcat(ligne, maillons->argument);
            strcat(ligne, " ");
        }
        else if(maillons->lexeme == 'V'){
            strcat(ligne, "!");
            strcat(ligne, maillons->argument);
            strcat(ligne, " ");
        }
        else if(maillons->lexeme == 'P' && strcmp(maillons->argument, "(") == 0){
            strcat(ligne, maillons->argument);
            compteur_parentheses += 1;
        }
        maillons = maillons -> suivant;
    }
    strcat(ligne, ";");
    printf("%s\n", ligne);
    Line_Writer(ligne);
}
