//
//  Declaration_Manager.c
//  Deepmle
//
//  Created by Robin PETIT on 26/05/2024.
//

#include "./../Headers/Declaration_Manager.h"

maillon* AssignSymbolDeclaration (maillon* debut){
    DeclarationBuilder* dcl = malloc(sizeof(DeclarationBuilder));
    dcl->start_dcl = "let";
    assert(debut->lexeme == 'T');
    dcl->type = debut->argument;
    debut = easy_strings_jumper(debut);
    printf ("lexeme : %c, Argument : %s\n",debut->lexeme,debut->argument);
    assert(debut->lexeme == 'V');
    dcl->name = debut->argument;
    debut = easy_strings_jumper(debut);
    debut = Declaration_Switcher(debut, dcl);
    return debut;
}

maillon* Declaration_Switcher (maillon* debut, DeclarationBuilder* dcl){
    if (debut->lexeme == 'E'){
        debut = AssignValue(debut, dcl);
    };
    if (debut->lexeme == 'P' && strcmp(debut->argument, "(") == 0){
        debut = AssignArg(debut, dcl);
    };
    return debut;
}

maillon* AssignValue (maillon* debut, DeclarationBuilder* dcl){
    debut = easy_strings_jumper(debut->suivant);
    VariableBuilder* vb = malloc(sizeof(VariableBuilder));
    vb->dcl = dcl;
    vb->start_vb = "ref";
    vb->value = malloc(50*sizeof(char));
    while (strcmp(debut->argument,";") != 0 && debut->lexeme != 'P'){
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
    return debut;
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

maillon* AssignArg (maillon* debut, DeclarationBuilder* dcl){
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
    strcat(fb->arg, " = ");
    BuildArg(fb);
    debut = AssignBody(debut, fb);
    return debut;
}

maillon* AssignBody (maillon* debut, FunctionBuilder* fb){
    debut = easy_strings_jumper(debut->suivant);
    debut = Line_Analyse_Loop(debut);
    Line_Writer(";;");
    return debut;
}

void BuildArg (FunctionBuilder* fb){
    char* line = malloc(50*sizeof(char));
    strcat(line, fb->dcl->start_dcl);
    strcat(line, " ");
    strcat(line, fb->dcl->name);
    strcat(line, " ");
    strcat(line, fb->arg);
    Line_Writer(line);
    free(line);
}

maillon* Affectation_Manager (maillon* debut){
    assert(debut->lexeme == 'V');
    printf("lexeme : %c | Argument : %s",debut->lexeme,debut->argument);
    char line[256] = "";
    strcat(line, debut->argument);
    debut = easy_strings_jumper(debut->suivant);
    strcat(line, " := ");
    debut = debut->suivant;
    debut = easy_strings_jumper(debut);
    while (strcmp(debut->argument, ";") != 0){
        if(debut->lexeme == 'V'){
            strcat(line, "!");
            strcat(line, debut->argument);
        }
        else{
            strcat(line, debut->argument);
        }
        debut = debut->suivant;
    }
    Line_Writer(line);
    debut = easy_strings_jumper(debut);
    return debut;
}