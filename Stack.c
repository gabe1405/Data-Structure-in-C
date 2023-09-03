
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

FILE *arquivo_entrada;
FILE *arquivo_saida;

typedef struct{
  int vetor[20];
  int topo;
}pilha_esta;

typedef struct no_pilha_dina * ptr_dina;

typedef struct{
  int qtd_dina;
  ptr_dina topo;
}pilha_dina;

typedef struct no_pilha_dina{
  ptr_dina seguinte;
  int valor;
}pilha_dina_no;

void VerificaPilhaVazia(int quantidade){
  if(quantidade == 0){
    fprintf(arquivo_saida,"Pilha vazia\n");
    fclose(arquivo_entrada);
    fclose(arquivo_saida);
    exit(0);
  }
}

int NumeroValido(float x){
  if(fmod(x,2) != 1 && fmod(x,2) != 0){
    fprintf(arquivo_saida,"Os valores digitados devem ser inteiros e positivos");
    fclose(arquivo_entrada);
    fclose(arquivo_saida);
    exit(0);
  }else{
    if(x < 0){
      fprintf(arquivo_saida,"Os valores digitados devem ser inteiros e positivos");
      fclose(arquivo_entrada);
      fclose(arquivo_saida);
      exit(0);
    }
  }
  return (x);
}

void EmpilhaEsta(pilha_esta *pilha){
  pilha->topo = 0;
  while(fscanf(arquivo_entrada,"\n%d", &pilha->vetor[pilha->topo]) != EOF){
    NumeroValido (pilha->vetor[pilha->topo]);
    if(pilha->topo < 20){
  pilha->topo++;
}else{
  fprintf(arquivo_saida,"Pilha estatica passou de sua capacidade\n");
}
}
VerificaPilhaVazia(pilha->topo);
}

void DesempilhaEst(pilha_esta *pilha){
  int resto;
  int x = 0;
  int binario_esta[20];
  pilha->topo --;

  while(pilha->topo >= 0){
    x = 0;
    do{
      binario_esta[x] = pilha->vetor[pilha->topo] % 2;
      pilha->vetor[pilha->topo] /= 2;
      x++;
    }while(pilha->vetor[pilha->topo] > 0);
      x--;
      for(x; x >= 0; x--){
      fprintf(arquivo_saida, "%d",binario_esta[x]);
    }
    fputc('\n', arquivo_saida);
    pilha->topo--;
  }//while
}

void EmpilhaDina(pilha_dina * pilha){
  pilha->qtd_dina = 0;
  float valor_digit;
  ptr_dina sub;
  pilha->topo = NULL;
  while(fscanf(arquivo_entrada,"\n%d", &valor_digit) != EOF){
    NumeroValido(valor_digit);
    sub = (ptr_dina)malloc (sizeof(ptr_dina));
    pilha->qtd_dina++;
    sub->valor = valor_digit;
    sub->seguinte = pilha->topo;
    pilha->topo = sub;
}
VerificaPilhaVazia(pilha->qtd_dina);
}

void DesempilhaDina(pilha_dina * pilha){
  int x = 0;
  int valor_result;
  int binario_dina[60];
  ptr_dina sub;

  sub = pilha->topo;

  while(pilha->topo != NULL){
    x = 0;
    sub = pilha->topo;
    valor_result = sub->valor;
    pilha->topo = pilha->topo->seguinte;
    printf("%d\n",pilha->topo);
    do{
      binario_dina[x] = valor_result % 2;
      valor_result /= 2;
      x++;
    }while(valor_result > 0);
      x--;
      for(x; x >= 0; x--){
      fprintf(arquivo_saida, "%d",binario_dina[x]);
    }
    fputc('\n', arquivo_saida);
    free(sub);
  }//while
}

int main (int argc, char *argv[]){
  char tipo_pilha;
  char seg_char;
  pilha_esta pilhaes;
  pilha_dina pilhadi;
  arquivo_entrada = fopen("entrada.txt","r");
  arquivo_saida = fopen("saida.txt", "w");
  tipo_pilha = fgetc(arquivo_entrada);
  seg_char = fgetc(arquivo_entrada);

if(arquivo_entrada != NULL && arquivo_saida != NULL && argc != 3){
  if(seg_char == '\n'){
  switch(tipo_pilha){
    case 'e':
    case 'E':
    EmpilhaEsta(&pilhaes);
    DesempilhaEst(&pilhaes);
    //pilha estática
    break;
    case 'd':
    case 'D':
    EmpilhaDina(&pilhadi);
    DesempilhaDina(&pilhadi);
    break;
    default:
    fprintf(arquivo_saida,"Caracter invalido\n");

    break;
  }
}else{
  fprintf(arquivo_saida,"Arquivo de entrada com caracteres errados ou vazio");
}
}else{
  fprintf(arquivo_saida,"Erro ao abrir o(s) arquivo(s) ou numero de parametros invalidos");
}
  fclose(arquivo_entrada);
  fclose(arquivo_saida);
  return 0;
}
