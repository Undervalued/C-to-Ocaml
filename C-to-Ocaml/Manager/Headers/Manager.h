//
//  Manager.h
//  Deepmle
//
//  Created by Robin PETIT on 26/05/2024.
//

#ifndef Manager_h
#define Manager_h

#include <stdio.h>
#include <assert.h>
#include "./../../lexer.h" //importe les fonctions du fichier lexer.c
#include "Declaration_Manager.h"
#include "Comment_Manager.h"
#include "Printf_Manager.h"
#include "While_Manager.h"
#include "For_Manager.h"
#include "Conditionnels_Manager.h"
void Line_Analyse (maillon* start);
void Line_Analyse_2 (maillon* start);
#endif /* Manager_h */
