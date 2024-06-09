#include "traducteur.h"
FILE* input;
FILE* output;
int main(int argc, char argv[]){
    char nom = argv[1];
    input = fopen(argv[1],"r");
    output = fopen("%s.ml", "w+",nom);
    maillon* lex = lexeur(input);
    lex = lex->suivant;
   // affiche_liste(lex);
    Line_Analyse(lex);
    //write_list(lex);
    fclose(input);
    fclose(output);
}

void Line_Writer(char* line){
    fprintf(output, "%s;;\n",line);
};

void Line_Writer(char* line){
    printf("%s\n",line);
    fprintf(output, "%s\n",line);
};
