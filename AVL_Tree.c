
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

//Não tive muito tempo para trabalhar nesse código

FILE *arquivo_entrada;
FILE *arquivo_saida;

typedef struct NoArvAVL * PtrNoArvAVL;

typedef struct{
  int altura;
  int valor;
}Dados;

typedef struct NoArvAVL{
  PtrNoArvAVL Direit;
  PtrNoArvAVL Esquer;
  Dados Valores;
}NoArvAVL;

void inicializador(PtrNoArvAVL * Arvore){
  (*Arvore) == NULL;
}

int TamanhoAVL(PtrNoArvAVL Arvore){
  if(Arvore == NULL) {
   return (0);
 } else {
   return (Arvore->Valores.altura);
 }
}

int TamanhoAtuliza (PtrNoArvAVL Esquer, PtrNoArvAVL Direit) {
    int esq = TamanhoAVL (Esquer);
    int dir = TamanhoAVL (Direit);
    if ( esq > dir ){
        return (esq + 1);
    }else{
        return (dir + 1);
      }
}

void RotacaoSimDir(PtrNoArvAVL * Arvore){
  PtrNoArvAVL u = (*Arvore)->Direit;
  (*Arvore)->Direit = u->Esquer;
  u->Esquer = (*Arvore);
  u->Valores.altura = TamanhoAtuliza(u->Esquer, u->Direit);
}

void RotacaoSimEsq(PtrNoArvAVL * Arvore){
  PtrNoArvAVL u = (*Arvore)->Esquer;
  (*Arvore)->Esquer = u->Direit;
  u->Direit = (*Arvore);
  u->Valores.altura = TamanhoAtuliza(u->Esquer, u->Direit);
}

void RotacaoDupDir(PtrNoArvAVL * Arvore){
  PtrNoArvAVL u = (*Arvore)->Direit;
  PtrNoArvAVL v = u->Esquer;
  (*Arvore)->Direit = v->Esquer;
  u->Esquer = v->Direit;
  v->Esquer = (*Arvore);
  v->Direit = u;
  u->Valores.altura = TamanhoAtuliza(u->Esquer, u->Direit);
  v->Valores.altura = TamanhoAtuliza(v->Esquer, v->Direit);
  (*Arvore) = v;
}

void RotacaoDupEsq(PtrNoArvAVL * Arvore){
  PtrNoArvAVL u = (*Arvore)->Esquer;
  PtrNoArvAVL v = u->Direit;
  (*Arvore)->Direit = v->Esquer;
  u->Direit = v->Esquer;
  (*Arvore)->Esquer = v->Direit;
  v->Esquer = u;
  v->Direit = (*Arvore);
  u->Valores.altura = TamanhoAtuliza(u->Esquer, u->Direit);
  v->Valores.altura = TamanhoAtuliza(u->Esquer, u->Direit);
}

void VerificaRot(PtrNoArvAVL * Arvore,int alt_direit,int alt_esquer){

    if(alt_esquer > alt_direit) {
      PtrNoArvAVL verifica = (*Arvore)->Esquer;
      int verifica_alt_direit = TamanhoAVL(verifica->Direit);
      int verifica_alt_esquer = TamanhoAVL(verifica->Esquer);
      if(verifica_alt_esquer > verifica_alt_direit) {
        RotacaoSimDir(&(*Arvore));
      }else{
        RotacaoDupDir(&(*Arvore));
      }
  }else{
      PtrNoArvAVL verifica = (*Arvore)->Direit;
      int verifica_alt_direit = TamanhoAVL(verifica->Direit);
      int verifica_alt_esquer = TamanhoAVL(verifica->Esquer);
      if(verifica_alt_direit > verifica_alt_esquer){
        RotacaoSimEsq(&(*Arvore));
      }else{
        RotacaoDupEsq(&(*Arvore));
      }
    }
  }

bool Coloca_Arvore(int valor, PtrNoArvAVL * Arvore){
  if((*Arvore) == NULL){
    (*Arvore) = (PtrNoArvAVL)malloc(sizeof(NoArvAVL));
    (*Arvore)->Valores.valor = valor;
    (*Arvore)->Direit = NULL;
    (*Arvore)->Esquer = NULL;
    (*Arvore)->Valores.altura = 1;
  }
  if(valor == (*Arvore)->Valores.valor){
    fprintf(arquivo_saida,"Tem palavras repetidas\n");
    exit(0);
  }
  bool verifica;
  if(valor < (*Arvore)->Valores.valor){
    verifica = Coloca_Arvore(valor, &(*Arvore)->Direit);
  }else{
    verifica = Coloca_Arvore(valor, &(*Arvore)->Esquer);
  }
  int alt_esquer = TamanhoAVL((*Arvore)->Esquer);
  int alt_direit = TamanhoAVL((*Arvore)->Direit);
  if(!verifica) {
    return (false);
  }

  if((alt_direit - alt_esquer) == +2 || (alt_direit - alt_esquer) == -2) {
    VerificaRot(&(*Arvore),alt_direit,alt_esquer);
  }
  return(true);
}

void Numeros(PtrNoArvAVL * Arvore){
char aux [30];
int valor_aux = 0;
char * separa;
int valor;
char aux2[5];
fgets(aux,30,arquivo_entrada);
separa = strtok(aux, ",\n");

while(separa != NULL){
  valor = atoi(separa);
  Coloca_Arvore(valor,&(*Arvore));
  separa = strtok(NULL, ",\n");
}
return;
}

  void retira_esq(char *remover,PtrNoArvAVL * Arvore,int contador){//aqui era para retirar valores de dentro da arvore a partir da esquerda
    if(Arvore == NULL){
      return;
    }else{
      if(contador = 0){
        contador++;
        retira_esq(remover,&(*Arvore)->Esquer,contador);
      }
      if((*Arvore)->Direit == NULL){
        retira_esq(remover,&(*Arvore)->Esquer,contador);
      }else{
        retira_esq(remover,&(*Arvore)->Direit,contador);
      }
    }
  }

  void retira_dir(char *remover,PtrNoArvAVL * Arvore,int contador){//aqui era para retirar valores de dentro da arvore a partir da dieita
    if(Arvore == NULL){
      return;
    }else{
      if(contador = 0){
        contador++;
        retira_esq(remover,&(*Arvore)->Esquer,contador);
      }
      if((*Arvore)->Direit == NULL){
        retira_esq(remover,&(*Arvore)->Esquer,contador);
      }else{
        retira_esq(remover,&(*Arvore)->Direit,contador);
      }
    }
  }

  void imprime(PtrNoArvAVL * Arvore){
    //Não sei como implementa o tipo de impressão desejado
  }

int main (int argc, char *argv[]){
  arquivo_entrada = fopen(argv[0],"r");
  arquivo_saida = fopen(argv[1], "w");
  PtrNoArvAVL Raiz;
  char modo;
  char remover[30];
  char * aux;
  int remocao;
  int contador = 0;

  if(argc == 3){
  inicializador(&Raiz);
  Numeros(&Raiz);
  fgets(remover,30,arquivo_entrada);
  modo = fgetc(arquivo_entrada);
  switch(modo){
  case 'e':
  imprime(&Raiz);
  aux = strtok(remover, ",\n");
  while(remover != NULL){
    remocao = atoi(aux);
    retira_esq(remover,&Raiz,contador);
    aux = strtok(NULL, ",\n");
  }
  imprime(&Raiz);
  case 'd':
  imprime(&Raiz);
  aux = strtok(remover, ",\n");
  while(remover != NULL){
    remocao = atoi(aux);
    retira_dir(remover,&Raiz,contador);
    aux = strtok(NULL, ",\n");
  }
  imprime(&Raiz);
  default:
  fprintf(arquivo_saida,"Erro\n");
}
}else{
  fprintf(arquivo_saida,"Erro\n");
}

  fclose(arquivo_entrada);
  fclose(arquivo_saida);

  return 0;
}
