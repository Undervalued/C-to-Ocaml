

#include "./../Headers/Printf_Manager.h"

void Printf_Manager(maillon* debut){
    // On suppose que l'utilisateur a 2 neurones et n'ecrit pas " printf         () "
    // Mais on ne fait pas confiance a l'utilisateur et donc on saute les espaces.
    debut = easy_strings_jumper(debut); // on saute la (
    char ligne[256] = "Printf.printf ";
    int compteur_parentheses = 0;
    while ( !(debut->lexeme == 'P' && strcmp(debut->argument, ";") == 0))
    {
        printf("%s\n", ligne);
        if(compteur_parentheses != 0){
            
            if(debut->lexeme != 'V' && debut->lexeme != 'S'){
                strcat(ligne, debut->argument);
            }
            if(debut->lexeme == 'P' && strcmp(debut->argument, ")") == 0){
                compteur_parentheses-=1;
                strcat(ligne, " ");
            }
        }
        printf("%c\n", debut->lexeme);
        printf("%s\n", debut->argument);
        if(debut->lexeme == 'S'){
            strcat(ligne, debut->argument);
            strcat(ligne, " ");
        }
        else if(debut->lexeme == 'V'){
            strcat(ligne, "!");
            strcat(ligne, debut->argument);
            strcat(ligne, " ");
        }
        else if(debut->lexeme == 'P' && strcmp(debut->argument, "(") == 0){
            strcat(ligne, debut->argument);
            compteur_parentheses += 1;
        }
        debut = debut -> suivant;
    }
    printf("%s\n", ligne);
    Line_Writer(ligne);
}