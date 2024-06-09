//
//  Manager.c
//  Deepmle
//
//  Created by Robin PETIT on 26/05/2024.
//

#include "./../Headers/Manager.h"

//Fonction d'anayse de la liste chaîné
void Line_Analyse (maillon* start){
    //On vérifie que 
    assert (start != NULL);
    while (start != NULL){
        if (start->lexeme=='T'){
            AssignSymbolDeclaration(start);
            
        }
        else if (start->lexeme == 'V'){
            
        }
        else if (start->lexeme == 'C'){
            BuildComment(start);
        }
        start = start->suivant;
        printf("Error : Impossible to analyse this line\n") ;
    }
}
