#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Não consegui fazer o código como foi pedido, ele nõo funciona e não aparece nada ao executar o
programa */

FILE *arquivo_entrada;
FILE *arquivo_saida;
FILE *arquivo_operacoes;
FILE *arquivo_temp;

typedef struct{
    char id[3];
    char nome[30];
    char idade[2];
    char profissao[30];
    char genero[1];
    char telefone[9];
}Professor;

typedef struct Nolista * ptrNolista;

typedef struct Nolista{
  Professor Dados;
  ptrNolista proximo;
  ptrNolista anterior;
}Nolista;

typedef struct{
  ptrNolista inicio;
  ptrNolista fim;
  int contador;
}Lista_Professor;

void inicializador(Lista_Professor *lista){
  lista->inicio = NULL;
  lista->fim = NULL;
  lista->contador = 0;
}

void insereProfessor (FILE *arq, Lista_Professor *lista, Professor* dados, int top){
    ptrNolista novo = (ptrNolista)malloc(sizeof(Nolista));
    char cond[86];
    int aux;
    int letra = 0;
    fscanf(arq, "size=86 top=%d\n",&top);
    while(fgets(cond, 86, arq) != NULL){
      while(cond[letra] != '|'){
      novo->Dados.id[letra] = cond[letra];
      letra++;
    }

    letra ++;
    aux = 0;
    while(cond[letra] != '|'){
    novo->Dados.nome[aux] = cond[letra];
    letra++;
    aux++;
  }

    aux = 0;
    letra ++;
    while(cond[letra] != '|'){
    novo->Dados.genero[aux] = cond[letra];
    letra++;
    aux++;
  }

    aux = 0;
    letra ++;
    while(cond[letra] != '|'){
    novo->Dados.idade[aux] = cond[letra];
    letra++;
    aux++;
  }

    aux = 0;
    letra ++;
    while(cond[letra] != ',' && cond[letra] != '|'){
    novo->Dados.profissao[aux] = cond[letra];
    letra++;
    aux++;
  }

    aux = 0;
    letra ++;
    while(cond[letra] != '|'){
    novo->Dados.telefone[aux] = cond[letra];
    letra++;
    aux++;
  }
    ptrNolista outro_ptr = lista->fim;
    if(lista->contador == 0){
      novo->anterior = lista->fim;
      lista->fim = novo;
      novo->proximo = lista->inicio;
      lista->inicio = novo;
      lista->contador++;
    }else{
      novo->anterior = lista->fim;
      lista->fim = novo;
      novo->anterior = outro_ptr->anterior;
      outro_ptr->anterior = novo;
      lista->contador++;
  }
  outro_ptr = lista->inicio;
  novo->proximo = outro_ptr->proximo;
  outro_ptr->proximo = novo;
}
}

void RemoveProfessor(Lista_Professor *lista, char said[], int cont_Remov, int top){
  ptrNolista pesquisa;
  pesquisa = lista->inicio;
  while(pesquisa != NULL && strcmp(pesquisa->Dados.id, said) == 0){
    pesquisa = pesquisa->proximo;
  }
  if(strcmp(pesquisa->Dados.id, said) == 0 && cont_Remov == -1){
    pesquisa->Dados.id[0] = '*';
    pesquisa->Dados.id[1] = '-';
    pesquisa->Dados.id[2] = '1';
    top++;
    cont_Remov += 2;
  }else{
    if(strcmp(pesquisa->Dados.id, said) == 0){
     pesquisa->Dados.id[0] = '*';
     pesquisa->Dados.id[1] = cont_Remov + '0';
     pesquisa->Dados.id[2] = '|';
     cont_Remov ++;
     top++;
    }
  }
  free(pesquisa);
  return;
}

void Imprime_Paginas(Lista_Professor *lista, int top, char matriz[100][88]){
  ptrNolista imprime;
  imprime = lista->inicio;
  while(imprime != NULL){
  fprintf(arquivo_temp, "size=86 top=%d\n", top);
  fprintf(arquivo_temp, "%s|", imprime->Dados.id);
  fprintf(arquivo_temp, "%s|", imprime->Dados.nome);
  fprintf(arquivo_temp, "%s|", imprime->Dados.genero);
  fprintf(arquivo_temp, "%s|", imprime->Dados.idade);
  fprintf(arquivo_temp, "%s|", imprime->Dados.profissao);
  fprintf(arquivo_temp, "%s|", imprime->Dados.telefone);
  imprime = imprime->proximo;
}

  for(int i = 0; i < 100; i++){
    for(int j = 2; j < 100; j++){
      fprintf(arquivo_temp, "%c", matriz[i][j]);
    }
    fprintf(arquivo_temp, "\n");
  }

  imprime = lista->inicio;
  while(imprime != NULL){
    if(imprime->Dados.id[0] != '*'){
      fprintf(arquivo_temp, "size=86 top=-1\n");
      fprintf(arquivo_saida, "%s|", imprime->Dados.id);
      fprintf(arquivo_saida, "%s|", imprime->Dados.nome);
      fprintf(arquivo_saida, "%s|", imprime->Dados.genero);
      fprintf(arquivo_saida, "%s|", imprime->Dados.idade);
      fprintf(arquivo_saida, "%s|", imprime->Dados.profissao);
      fprintf(arquivo_saida, "%s|\n", imprime->Dados.telefone);
    }
   imprime = imprime->proximo;
  }

  for(int i = 0; i < 100; i++){
    for(int j = 2; j < 88; j++){
      fprintf(arquivo_saida, "%c", matriz[i][j]);
    }
    fprintf(arquivo_saida, "\n");
  }

  free(imprime);
}

void Destroi(Lista_Professor *lista){
  ptrNolista Dest;
  Dest = lista->inicio;
  ptrNolista proximo;
  while (Dest != NULL) {
    proximo = Dest->proximo;
    free(Dest);
    Dest = proximo;
  }
  lista = NULL;
}

int main (int argc, char *argv[]){
  arquivo_entrada = fopen(argv[0],"r");
  arquivo_operacoes = fopen(argv[1],"r");
  arquivo_temp = fopen(argv[2],"w");
  arquivo_saida = fopen(argv[3],"w");
  char str_aux[86];
  char n;
  char Reg [86];
  char said[3];
  int cont_Remov = -1;
  int top;
  Lista_Professor lista;
  int cont = 0;
  int i = 0;
  char string [100][88];
  Professor dados;
  if(fgets(Reg, 86, arquivo_entrada) != NULL){
    if(arquivo_entrada != NULL && arquivo_saida != NULL && argc == 5){
      inicializador (&lista);
      insereProfessor (arquivo_entrada, &lista, &dados, top);

      while(fgets(str_aux, 86, arquivo_operacoes) != NULL){
      n = str_aux[0];

      switch(n){
      case 'i':
        for(int j = 2; j < 88; j++){
          if(str_aux[j] != ','){
            string[i][j] = str_aux[j];
          }else{
            if(cont == 1){
              while(j < 36){
                string[i][j] = ' ';
                j++;
              }
            }
            if(cont == 2){
              while(j < 39){
                string[i][j] = ' ';
                j++;
              }
              if(cont == 3){
                while(j < 70){
                  string[i][j] = ' ';
                  j++;
                }
            }
            string[i][j] = '|';
            cont++;
          }
        }
        }
        i++;
      break;

      case 'd':
      for(int i = 0; i < 3; i++){
        said[i] = Reg[i];
      }
      RemoveProfessor(&lista, said, cont_Remov, top);
      break;

      default:
      Destroi(&lista);
      remove(argv[0]);
      fprintf(arquivo_saida,"ERRO\n");
      fclose(arquivo_entrada);
      fclose(arquivo_saida);
      fclose(arquivo_operacoes);
      fclose(arquivo_temp);
      return 0;
  }
  }
  Imprime_Paginas(&lista, top, string);
  Destroi(&lista);
  remove(argv[0]);
}else{
    fprintf(arquivo_saida,"Problema ao abrir o arquivo\n");
  }
}else{
  fprintf(arquivo_saida,"ERRO\n");
}

  fclose(arquivo_entrada);
  fclose(arquivo_saida);
  fclose(arquivo_operacoes);
  fclose(arquivo_temp);

  return 0;
}
