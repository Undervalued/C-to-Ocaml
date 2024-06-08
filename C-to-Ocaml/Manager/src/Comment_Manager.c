//
//  Comment_Manager.c
//  C-to-Ocaml
//
//  Created by Robin PETIT on 09/06/2024.
//

#include "Comment_Manager.h"

void BuildComment (maillon* debut){
    assert(debut->lexeme='C');
    char line[500] = "";
    strcat(line, "(*");
    strcat(line, debut->argument);
    strcat(line, "*)");
    Line_Writer(line);
}
