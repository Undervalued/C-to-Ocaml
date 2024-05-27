#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h" 


struct variables {
    char* nom; // le nom de la variable
    char* valeur;  // sa valeur
};
typedef struct variables variables;

struct boucle {
    char* cond;
    char* inst;
};
typedef struct boucle boucle;

// Inutile, puisque on va changer la facon dont on va ecrire le fichier....
maillon* easy_strings_jumper(maillon* depart, FILE* output){
    while(depart->lexeme == 'P' && (strcmp(depart->argument, " ") == 0 || strcmp(depart->argument, "\n") == 0)){
        // fprintf(output, "%s",depart->argument);
        depart = depart->suivant;
    }
    return depart;
}

void write_variable(variables* v, FILE* output){
    fprintf(output, "let %s = ref (%s) in\n", v->nom, v->valeur);
};

void rewrite_variable(variables* v, FILE* output){
    fprintf(output, "%s := (%s);\n", v->nom, v->valeur);
};

void commentaire_manager(maillon* m, FILE* output){
    char* afficher = m->argument;
    fprintf(output, "(*%s*)\n", afficher);
};

void write_boucle(boucle* b, FILE* output){
    fprintf(output, "while %s do %s done\n", b->cond, b->inst);
};

maillon* boucle_manager(maillon* m, FILE* output){
    boucle* bou = malloc(sizeof(boucle));
    m = m->suivant;
    char conditionnel[20] = "";
    char instruction[20] = "";
    while (strcmp(m->argument, "{") != 0){
        if (m->lexeme == 'V'){
            strcat(conditionnel, "!");
            strcat(conditionnel, m->argument);
        }
        else {
            strcat(conditionnel, m->argument);
        }
        m = m->suivant;
    }
    while (strcmp(m->argument, "}") != 0){
        if (m->lexeme == 'V'){
            strcat(instruction, "!");
            strcat(instruction, m->argument);
        }
        else {
            strcat(instruction, m->argument);
        }
        m = m->suivant;
    }
    bou->cond = conditionnel;
    bou->inst = instruction;
    return m;
}



//
// Manque a gerer: x = x+2; (C) -> x := !x + 2;; (OCaml) IE la modification des valeurs.
maillon* variable_manager(maillon* depart, FILE* output){
    variables* var = malloc(sizeof(variables));
    var->nom = depart->argument;
    depart = depart-> suivant;
    char valeur_v[20] = "";

    while(strcmp(depart->argument, "=") != 0){
        // Empty for now... in case of needing it...
        // On va jusqu'au debut de l'assignation de la valeur de la variable
        depart = depart->suivant;
    }
    depart = depart->suivant;
    while(strcmp(depart->argument, ";") != 0){
        if(depart->lexeme == 'V'){
            strcat(valeur_v, "!");
            strcat(valeur_v, depart->argument);
        }
        else{
            strcat(valeur_v, depart->argument);
        }
        depart = depart->suivant;
    }
    var->valeur = valeur_v;
    write_variable(var, output);
    return depart;
    
}

maillon* old_variable_manager(maillon* depart, FILE* output){
    variables* var = malloc(sizeof(variables));
    var->nom = depart->argument;
    depart = depart-> suivant;
    char valeur_v[20] = "";
    


    while(strcmp(depart->argument, "=") != 0){
        // Empty for now... in case of needing it...
        // On va jusqu'au debut de l'assignation de la valeur de la variable
        depart = depart->suivant;
    }
    depart = depart->suivant;
    while(strcmp(depart->argument, ";") != 0){
        if(depart->lexeme == 'V'){
            strcat(valeur_v, "!");
            strcat(valeur_v, depart->argument);
        }
        else{
            strcat(valeur_v, depart->argument);
        }
        depart = depart->suivant;
    }
    var->valeur = valeur_v;
    rewrite_variable(var, output);
    return depart;
    
}


/* void maincode(){
    FILE* input = fopen("s.c", "r");
    FILE* output = fopen("d.ml", "a");

    maillon* maillons = lexeur(input);
    // affiche_liste(maillons);

    while (maillons != NULL){
        if(maillons->lexeme == 'T'){
            while(maillons->lexeme != 'V' || maillons->lexeme != 'M'){
                maillons = maillons -> suivant;
            }
            if(maillons->lexeme == 'V'){
                // Detection d'assignation d'une variable
                maillon* maillon2 = easy_strings_jumper(maillons->suivant, output);
                if(strcmp(maillon2->argument, "=") == 0){
                    maillons = variable_manager(maillons, output);
                }
            }
            else{
                continue;
            }

        }
        if(maillons->lexeme == 'V'){
            // Detection d'assignation d'une variable
            maillon* maillon2 = easy_strings_jumper(maillons->suivant, output);
            if(strcmp(maillon2->argument, "=") == 0){
                maillons = old_variable_manager(maillons, output);
            }
        }

        maillons = maillons -> suivant;

    }

    fclose(input);
    fclose(output);
}; */

int main(){

    FILE* input = fopen("s.c", "r");
    FILE* output = fopen("d.ml", "w+");

    maillon* maillons = lexeur(input);
    affiche_liste(maillons);

    while (maillons->lexeme != 'A'){
        maillons = maillons -> suivant;
    }

    maillons = maillons -> suivant;

    while (maillons != NULL){
        if(maillons->lexeme == 'C'){
            commentaire_manager(maillons, output);
        }
        else if(maillons->lexeme == 'T'){
            while(maillons->lexeme != 'V'){
                maillons = maillons -> suivant;
            }
            // Detection d'assignation d'une variable
            maillon* maillon = easy_strings_jumper(maillons->suivant, output);
            if(strcmp(maillon->argument, "=") == 0){
                maillons = variable_manager(maillons, output);
            }
        } 

        
        else if(maillons->lexeme == 'V'){
            // Detection de réassignation d'une variable
            maillon* maillon = easy_strings_jumper(maillons->suivant, output);
            if(strcmp(maillon->argument, "=") == 0){
                maillons = old_variable_manager(maillons, output);
            }
        }

        else if(maillons->lexeme == 'M'){
            if (maillons->argument == "main"){
                maillons = boucle_manager(maillons, output);
            }
        }

    maillons = maillons -> suivant;

    }

    fclose(input);
    fclose(output);
    
    // printf("%c %s", maillons->suivant->lexeme, maillons->suivant->argument);



    //printf("Hello, World!");
}
