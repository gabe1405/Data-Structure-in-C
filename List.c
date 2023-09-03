#include <stdio.h>
#include <stdlib.h>
#include <string.h>


FILE * arquivo_entrada;
FILE * arquivo_saida;

typedef struct{
  int id;
  char resto[200];
}cliente;

typedef struct Nolista * ptrNolista;

typedef struct Nolista{
  cliente valores;
  ptrNolista proximo;
  ptrNolista anterior;
}Nolista;

typedef struct{
  ptrNolista inicio;
  ptrNolista fim;
  int contador;
}Lista_medica;

void inicializador(Lista_medica *lista){
  lista->inicio = NULL;
  lista->fim = NULL;
  lista->contador = 0;
}

char insereNumeros (Lista_medica *lista, cliente* dados, char valor){
  while(valor == '{'){
    ptrNolista novo = (ptrNolista)malloc(sizeof(Nolista));
    fscanf(arquivo_entrada,"%d",&dados->id);
    fgets (dados->resto, 50, arquivo_entrada);
    dados->resto[strlen(dados->resto)] = '\0';
    valor = fgetc(arquivo_entrada);
    strcpy(novo->valores.resto, dados->resto);
    novo->valores.id = dados->id;
    if(lista->contador == 0 || (dados->id < lista->inicio->valores.id)){//condição para saber se inserimos o elemento no inicio da lista->inicio
      if(lista->contador > 0){//aqui coloca o primeiro valor na lista para o fim
        ptrNolista dup;
        dup = lista->fim;
      while(dup->anterior != NULL && dados->id < dup->anterior->valores.id){
        dup = dup->anterior;
      }
      novo->anterior = dup->anterior;
      dup->anterior = novo;
    }else{//quando não é o primeiro elemento da lista colocamos o fim ligado ao primeiro termo do inicio como o ultimo do fim
      novo->anterior = lista->fim;
      lista->fim = novo;
    }
      novo->proximo = lista->inicio;
      lista->inicio = novo;
    }else{//caso o elemento seja inserido no meio da lista->inicio
      ptrNolista outro_ptr = lista->fim;
      if(dados->id > lista->fim->valores.id){//caso o elemento a ser inserido seja maior que o primeiro do fim
        novo->anterior = lista->fim;
        lista->fim = novo;
      }else{//se não for maior que o primeiro do fim percorremos a lista e inserimos
          while(outro_ptr->anterior != NULL && dados->id < outro_ptr->anterior->valores.id){
          outro_ptr = outro_ptr->anterior;
      }
      novo->anterior = outro_ptr->anterior;
      outro_ptr->anterior = novo;
  }
  outro_ptr = lista->inicio;
  while(outro_ptr->proximo != NULL && dados->id >= outro_ptr->proximo->valores.id){
  outro_ptr = outro_ptr->proximo;
}
  novo->proximo = outro_ptr->proximo;
  outro_ptr->proximo = novo;
}
  lista->contador++;
}
return(valor);
}

void EstaVazia(Lista_medica *lista){
  if(lista->inicio == NULL){//caso a lista esteja vazia
   fprintf(arquivo_saida,"Erro");
   fclose(arquivo_entrada);
   fclose(arquivo_saida);
   exit(0);
 }
 return;
}

void crescente(Lista_medica *lista,cliente *dados){//organiza em ordem crescente
  ptrNolista cresce;
  ptrNolista decresce;
  while(cresce != NULL){
    fprintf(arquivo_saida,"{%d%s",cresce->valores.id,cresce->valores.resto);
    cresce = cresce->proximo;
  }
  free(cresce);
  free(decresce);
  return;
}

void decrescente(Lista_medica *lista,cliente *dados){//organiza em ordem decrescente
  ptrNolista decresce;
  ptrNolista cresce;
  decresce = lista->fim;
  cresce = lista->inicio;
  while(decresce != NULL){
    fprintf(arquivo_saida,"{%d%s",decresce->valores.id,decresce->valores.resto);
    decresce = decresce->anterior;
  }
  free(decresce);
  free(cresce);
  return;
}

void pesquisa(Lista_medica *lista,int valor){//pesquisa valores digitados
   ptrNolista pesquisa;
   pesquisa = lista->inicio;
   while(pesquisa != NULL && valor > pesquisa->valores.id){
     pesquisa = pesquisa->proximo;
   }
   if(pesquisa->valores.id != valor){
     fprintf(arquivo_saida,"Erro: Número não encontrado");
   }else{
     fprintf(arquivo_saida,"{%d%s",pesquisa->valores.id, pesquisa->valores.resto);
   }
   free(pesquisa);
   return;
}

int main (int argc, char argv[]){
  char identificador;
  arquivo_entrada = fopen("entrada.txt","r");
  arquivo_saida = fopen("saida.txt", "w");
  Lista_medica lista;
  cliente dados;
  identificador = fgetc(arquivo_entrada);

  if(identificador == '{' && argc != 3 && arquivo_entrada != NULL && arquivo_saida != NULL){
    inicializador (&lista);
    identificador = insereNumeros (&lista,&dados,identificador);
    if(identificador == '1'){//cresce
      crescente(&lista,&dados);
    }else{
    if(identificador == '2'){//decresce
      decrescente(&lista,&dados);
    }else{
    if(identificador == '3'){//pesquisa
      int x;
      fscanf(arquivo_entrada,"%d",&x);
      pesquisa(&lista,x);
    }else{//caso o valor digitado não seja 1, 2 ou 3
      fprintf(arquivo_saida,"Erro");
    }
  }
}
}else{
  fprintf(arquivo_saida,"Erro");
}

  fclose(arquivo_entrada);
  fclose(arquivo_saida);
  return 0;
}
