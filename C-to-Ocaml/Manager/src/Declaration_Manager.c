//
//  Declaration_Manager.c
//  Deepmle
//
//  Created by Robin PETIT on 26/05/2024.
//

#include "Declaration_Manager.h"

DeclarationBuilder* AssignSymbolDeclaration (maillon* debut){
    DeclarationBuilder* dcl = malloc(sizeof(DeclarationBuilder));
    dcl->start_dcl = "let";
    assert(debut->lexeme == 'T');
    dcl->type = debut->argument;
    debut = easy_strings_jumper(debut);
    assert(debut->lexeme == 'V');
    dcl->name = debut->argument;
    debut = easy_strings_jumper(debut);
    Declaration_Switcher(debut, dcl);
    return 0;
}

int Declaration_Switcher (maillon* debut, DeclarationBuilder* dcl){
    printf("lexeme :%c",debut->lexeme);
    if (debut->lexeme == 'E'){
        printf("\ntest1\n");
        AssignValue(debut, dcl);
    };
    return 0;
}

void AssignValue (maillon* debut, DeclarationBuilder* dcl){
    debut = easy_strings_jumper(debut->suivant);
    VariableBuilder* vb = malloc(sizeof(VariableBuilder));
    vb->dcl = dcl;
    //TODO gérer les int qqchose = "string"
    vb->start_vb = "ref";
    vb->value = malloc(50*sizeof(char));
    while (debut->argument != ';' && debut->lexeme != 'P'){
        if(debut->lexeme == 'V'){
            strcat(vb->value, "!");
            strcat(vb->value, debut->argument);
        }
        else{
            strcat(vb->value, debut->argument);
        }
        debut = debut->suivant;
    }
    printf("\n test2 \n");
    BuildVariable(vb);
}

void BuildVariable (VariableBuilder* vb){
    char line[20] = "";
    strcat(line, vb->dcl->start_dcl);
    printf("dcl : %s",vb->dcl->start_dcl);
    strcat(line, " ");
    strcat(line, vb->dcl->name);
    strcat(line, " = ");
    strcat(line,vb->start_vb);
    strcat(line, "(");
    strcat(line, vb->value);
    strcat(line, ")");
    printf("Line : %s\n",line);
    Line_Writer(line);
}
