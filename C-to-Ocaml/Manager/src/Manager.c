//
//  Manager.c
//  Deepmle
//
//  Created by Robin PETIT on 26/05/2024.
//

#include "Manager.h"


void Line_Analyse (maillon* start){
    assert (start != NULL);
    while (start != NULL){
        printf("lex1 : %c\n",start->lexeme);
        if (start->lexeme=='T'){
            AssignSymbolDeclaration(start);
            
        }
        else if (start->lexeme == 'V'){
            
        }
        start = start->suivant;
        printf("Error : Impossible to analyse this line\n") ;
    }
}
