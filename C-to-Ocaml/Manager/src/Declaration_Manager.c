//
//  Declaration_Manager.c
//  Deepmle
//
//  Created by Robin PETIT on 26/05/2024.
//

#include "./../Headers/Declaration_Manager.h"

int AssignSymbolDeclaration (maillon* debut){
    DeclarationBuilder* dcl = malloc(sizeof(DeclarationBuilder));
    dcl->start_dcl = "let";
    assert(debut->lexeme == 'T');
    dcl->type = debut->argument;
    debut = easy_strings_jumper(debut);
    printf ("lexeme : %c, Argument : %s\n",debut->lexeme,debut->argument);
    assert(debut->lexeme == 'V');
    dcl->name = debut->argument;
    debut = easy_strings_jumper(debut);
    Declaration_Switcher(debut, dcl);
    return 0;
}

int Declaration_Switcher (maillon* debut, DeclarationBuilder* dcl){
    Debogage : printf("lexeme :%c, Argument :%s\n",debut->lexeme,debut->argument);
    if (debut->lexeme == 'E'){
        AssignValue(debut, dcl);
    };
    if (debut->lexeme == 'P' && strcmp(debut->argument, "(") == 0){
        AssignArg(debut, dcl);
    };
    return 0;
}

void AssignValue (maillon* debut, DeclarationBuilder* dcl){
    debut = easy_strings_jumper(debut->suivant);
    VariableBuilder* vb = malloc(sizeof(VariableBuilder));
    vb->dcl = dcl;
    vb->start_vb = "ref";
    vb->value = malloc(50*sizeof(char));
    while (strcmp(debut->argument,";") == 0 && debut->lexeme != 'P'){
        if(debut->lexeme == 'V'){
            strcat(vb->value, "!");
            strcat(vb->value, debut->argument);
        }
        else{
            strcat(vb->value, debut->argument);
        }
        debut = debut->suivant;
    }
    BuildVariable(vb);
}

void BuildVariable (VariableBuilder* vb){
    char line[20] = "";
    strcat(line, vb->dcl->start_dcl);
    strcat(line, " ");
    strcat(line, vb->dcl->name);
    strcat(line, " = ");
    strcat(line,vb->start_vb);
    strcat(line, "(");
    strcat(line, vb->value);
    strcat(line, ");;");
    Line_Writer(line);
}

void AssignArg (maillon* debut, DeclarationBuilder* dcl){
    FunctionBuilder* fb = malloc(sizeof(FunctionBuilder));
    fb->dcl = dcl;
    debut = easy_strings_jumper(debut->suivant);
    fb->arg = malloc(50*sizeof(char));
    while (strcmp(debut->argument, ")") != 0){
        if(debut->lexeme == 'V'){
            strcat(fb->arg, debut->argument);
        }
        else if (strcmp(debut->argument, ",") == 0){
            strcat(fb->arg, " ");
        }
        debut = debut->suivant;
    }
    printf("lexeme : %c\n",debut->lexeme);
    printf("arg : %s\n",fb->arg);
    strcat(fb->arg, " = ");
    BuildArg(fb);
    AssignBody(debut, fb);
}

void AssignBody (maillon* debut, FunctionBuilder* fb){
    debut = easy_strings_jumper(debut->suivant);
}

void BuildArg (FunctionBuilder* fb){
    char* line = malloc(50*sizeof(char));
    strcat(line, fb->dcl->start_dcl);
    strcat(line, " ");
    strcat(line, fb->dcl->name);
    strcat(line, " ");
    strcat(line, fb->arg);
    printf("line : %s\n",line);
    Line_Writer(line);
    free(line);
}
