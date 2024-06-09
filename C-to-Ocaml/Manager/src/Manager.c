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
        else if(start->lexeme == 'M' && strcmp(start->argument, "printf") == 0){
            Printf_Manager(start);
        }
        else if (start->lexeme == 'C'){
            BuildComment(start);
        }
        else if (start->lexeme == 'P' && strcmp(start->argument,"}")==0){
            Line_Writer(";;");
        }
        else if (start->lexeme == 'M' && strcmp(start->argument,"return")==0){
            start = easy_strings_jumper(start);
            Line_Writer(start->argument);
        }
        else if (start->lexeme == 'M' && strcmp(start->argument,"while")==0){
            While_Manager(start);
        }
        else if (start->lexeme == 'M' && strcmp(start->argument,"if")==0){
            Conditionnels_Manager(start);
        }
        else if (start->lexeme == 'M' && strcmp(start->argument,"for")==0){
            For_Manager(start);
        }
        start = start->suivant;
       // printf("Error : Impossible to analyse this line\n") ;
    }
}