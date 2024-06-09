//
//  Declaration_Manager.h
//  Deepmle
//
//  Created by Robin PETIT on 26/05/2024.
//

#ifndef Declaration_Manager_h
#define Declaration_Manager_h

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "./../../lexer.h"
#include "./../../traducteur.h"
struct DeclarationBuilder {
    char* start_dcl;
    char* type;
    char* name;
};
typedef struct DeclarationBuilder DeclarationBuilder;
struct VariableBuilder {
    DeclarationBuilder* dcl;
    char* start_vb;
    char* value;
};

struct FunctionBuilder {
    DeclarationBuilder* dcl;
    char* arg;
    char* body;
};
typedef struct FunctionBuilder FunctionBuilder;
typedef struct VariableBuilder VariableBuilder;

maillon* AssignValue (maillon* debut, DeclarationBuilder* dcl);
maillon* AssignSymbolDeclaration (maillon* maillon);
void BuildVariable (VariableBuilder* vb);
maillon* Declaration_Switcher (maillon* debut, DeclarationBuilder* dcl);
maillon* AssignArg (maillon* debut, DeclarationBuilder* dcl);
maillon* AssignBody (maillon* debut, FunctionBuilder* fb);
void BuildArg (FunctionBuilder* fb);
maillon* Affectation_Manager (maillon* debut);
#endif /* Declaration_Manager_h */
