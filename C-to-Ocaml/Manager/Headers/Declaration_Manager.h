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
#include "lexer.h"
#include "traducteur.h"
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
typedef struct VariableBuilder VariableBuilder;

void AssignValue (maillon* debut, DeclarationBuilder* dcl);
DeclarationBuilder* AssignSymbolDeclaration (maillon* maillon);
void BuildVariable (VariableBuilder* vb);
int Declaration_Switcher (maillon* debut, DeclarationBuilder* dcl);
#endif /* Declaration_Manager_h */
