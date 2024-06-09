//
//  Manager.c
//  Deepmle
//
//  Created by Robin PETIT on 26/05/2024.
//

#include "./../Headers/Manager.h"

//Fonction d'anayse de la liste chaîné
maillon* Line_Analyse (maillon* start){
    //On vérifie que 
    assert (start != NULL);
    while (start != NULL){
        if (start->lexeme=='T'){
            start = AssignSymbolDeclaration(start);
            
        }
        else if (start->lexeme == 'V')
        {
            start = Affectation_Manager(start);
        }
        else if(start->lexeme == 'M' && strcmp(start->argument, "printf") == 0){
            start = Printf_Manager(start);
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
            start = While_Manager(start);
        }
        else if (start->lexeme == 'M' && strcmp(start->argument,"if")==0){
            start = Conditionnels_Manager(start);
        }
        else if (start->lexeme == 'M' && strcmp(start->argument,"for")==0){
            start = For_Manager(start);
        }
        start = start->suivant;
       // printf("Error : Impossible to analyse this line\n") ;
    }
    return start;
}

maillon* Line_Analyse_Loop (maillon* start){
    assert (start != NULL);
    while (start != NULL){
        if (start->lexeme=='T'){
            start = AssignSymbolDeclaration(start);
            
        }
        else if (start->lexeme == 'V')
        {
            start = Affectation_Manager(start);
        }
        else if(start->lexeme == 'M' && strcmp(start->argument, "printf") == 0){
            Printf_Manager(start);
        }
        else if (start->lexeme == 'C'){
            BuildComment(start);
        }
        else if (start->lexeme == 'P' && strcmp(start->argument,"}")==0){
            start = start->suivant;
            start = easy_strings_jumper(start);
            return start;
        }
        else if (start->lexeme == 'M' && strcmp(start->argument,"return")==0){
            start = easy_strings_jumper(start);
            Line_Writer(start->argument);
        }
        else if (start->lexeme == 'M' && strcmp(start->argument,"while")==0){
            While_Manager(start);
        }
        else if (start->lexeme == 'M' && strcmp(start->argument,"if")==0){
            start = Conditionnels_Manager(start);
        }
        else if (start->lexeme == 'M' && strcmp(start->argument,"for")==0){
            For_Manager(start);
        }
        start = start->suivant;
       // printf("Error : Impossible to analyse this line\n") ;
    }
    return start;
}