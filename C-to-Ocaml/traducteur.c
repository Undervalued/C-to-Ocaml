#include "traducteur.h"
FILE* input;
FILE* output;
int main(void){
    input = fopen("/Users/robin/Workspace_Developpement/XCode/C-to-Ocaml/C-to-Ocaml/main.c","r");
    output = fopen("/Users/robin/Workspace_Developpement/XCode/C-to-Ocaml/C-to-Ocaml/s.ml", "w+");
    maillon* lex = lexeur(input);
    lex = lex->suivant;
    affiche_liste(lex);
    Line_Analyse(lex);
    //write_list(lex);
    fclose(input);
    fclose(output);
}

void Line_Writer(char* line){
    
    fprintf(output, "%s;;\n",line);
};
