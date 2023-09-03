
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

FILE *arquivo_entrada;
FILE *arquivo_saida;

typedef struct NoArv * PtrNoArv;

typedef struct{
  char Palavra_Chave[40];
  int Pagina[30];
  int contador;
}Texto;

typedef struct NoArv{
  PtrNoArv Direit;
  PtrNoArv Esquer;
  Texto livro;
}NoArv;

void inicializador(PtrNoArv * Arvore){
  (*Arvore) == NULL;
}

void Coloca_Arvore(char * Palavra_chave, PtrNoArv * Arvore){
  if((*Arvore) == NULL){
    (*Arvore) = (PtrNoArv)malloc(sizeof(NoArv));
    strcpy((*Arvore)->livro.Palavra_Chave, Palavra_chave);
    (*Arvore)->livro.contador = 0;
    (*Arvore)->Direit = NULL;
    (*Arvore)->Esquer = NULL;
    return;
  }

  if(strcmp((*Arvore)->livro.Palavra_Chave, Palavra_chave) == 0){
    fprintf(arquivo_saida,"Tem palavras repetidas\n");
    exit(0);
  }

  if(strcmp((*Arvore)->livro.Palavra_Chave, Palavra_chave) < 0){
    Coloca_Arvore(Palavra_chave, &(*Arvore)->Direit);
  }else{
    Coloca_Arvore(Palavra_chave, &(*Arvore)->Esquer);
  }
}

void Pega_palavras(char * palavra, PtrNoArv * Arvore){
char aux [150];
int valor_aux = 0;

for(int i = 0; i <= strlen(palavra); i++){
  if(palavra[i] == ',' || palavra[i] == '>'){
    aux[valor_aux] = '\0';
    Coloca_Arvore(aux, &*Arvore);
    valor_aux = 0;
  }else{
  aux[valor_aux] = tolower(palavra[i]);
  valor_aux ++;
  }
}
}

void Compara_palavras(PtrNoArv * Arvore, char * Palavra_texto, int Pag){
  if((*Arvore) == NULL){
    return;
  }
  int n = strlen(Palavra_texto);
  char Palavra [30];
  while(n >= 0){
    Palavra[n] = tolower(Palavra_texto[n]);
    n--;
  }
  if(strcmp(Palavra, (*Arvore)->livro.Palavra_Chave) < 0){
    Compara_palavras(&(*Arvore)->Esquer, Palavra_texto, Pag);
  }else{
    if(strcmp(Palavra, (*Arvore)->livro.Palavra_Chave) > 0){
      Compara_palavras(&(*Arvore)->Direit, Palavra_texto, Pag);
  }else{
      int x;
      x = (*Arvore)->livro.contador - 1;
      if((*Arvore)->livro.contador == 0 || (*Arvore)->livro.Pagina[x] != Pag){
    (*Arvore)->livro.Pagina[(*Arvore)->livro.contador] = Pag;
    (*Arvore)->livro.contador ++;
    return;
  }
  }
}
return;
}

void Pega_texto(PtrNoArv * Arvore){
  int Pag = 1;
  char Texto[150];
  char * palavras;
  fgets(Texto, 150, arquivo_entrada);
  Texto[strlen(Texto)] = '\0';
  while (fgets(Texto, 150, arquivo_entrada) != NULL){
    Texto[strlen(Texto)] = '\0';
    if(Texto[0] == '<'){
      Pag ++;
    }else{
    palavras = strtok (Texto,"< ,.-!'\"\n();");
  while (palavras != NULL){
    Compara_palavras(& *Arvore, palavras, Pag);
    palavras = strtok (NULL, "< ,.-!\'\"\n();");
  }
}
}
}

void Imprime_Paginas(PtrNoArv * Arvore){
  int n = 0;
  if((*Arvore) != NULL){
    Imprime_Paginas(&(*Arvore)->Esquer);
    fprintf(arquivo_saida,"%s",(*Arvore)->livro.Palavra_Chave);
    if((*Arvore)->livro.contador != 0){
    while(n < (*Arvore)->livro.contador){
    fprintf(arquivo_saida,",%d",(*Arvore)->livro.Pagina[n]);
    n++;
  }
}else{
  fprintf(arquivo_saida," (palavra nao encontrada)");
}
    fprintf(arquivo_saida,"\n");
    Imprime_Paginas(&(*Arvore)->Direit);
  }
  free(Arvore);
  return;
}

int main (int argc, char *argv[]){
  PtrNoArv Raiz = NULL;
  char str[100];
  arquivo_entrada = fopen("entrada6.txt","r");
  arquivo_saida = fopen("saida1.txt", "w");
  for(int i = 8; i > 0; i--){
  fgetc(arquivo_entrada);
}

  fgets(str,100,arquivo_entrada);
  str[strlen(str)] == '\0';
  if(strlen(str) > 1 && argc != 3){
  inicializador(&Raiz);
  Pega_palavras(str,&Raiz);
  Pega_texto(&Raiz);
  Imprime_Paginas(&Raiz);
}else{
  fprintf(arquivo_saida,"Erro");
}

  fclose(arquivo_entrada);
  fclose(arquivo_saida);

  return 0;
}
