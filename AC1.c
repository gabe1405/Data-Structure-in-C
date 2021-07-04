#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define LIM 20//a pilha estatica terá um limite de 20 numeros no arquivo de entrada

typedef struct{
  int topo;
  int vetor[LIM];
  int qntd_esta;
}pilha_estatica;

FILE *arquivo_entrada;
FILE *arquivo_saida;

void empilhaPilhaEsta(pilha_estatica *pilha){
  pilha->topo = 0;
  pilha->qntd_esta = 0;
  while(fscanf(arquivo_entrada,"\n%d", &pilha->vetor[pilha->topo]) != EOF){//escaneia o arquivo até o final
    if(pilha->vetor[pilha->topo] >= 0){//valores negativos serão considerados invalidos
    if(pilha->topo < 20){
  pilha->topo++;
  pilha->qntd_esta++;
}else{
  printf("Pilha esta cheia");
}//else
}else{
  printf("Valor negativo e invalido\n");
  exit(0);
}//else
}//while
}//empilha

void VerificaPilhaEsta(pilha_estatica *pilha){
  if(pilha->qntd_esta == 0){
    printf("Pilha vazia\n");
    return;
  }
}

void Desempilha_Bin_est(pilha_estatica *pilha){
  int resto;
  int x = 0;
  int binario_esta[20];//colocara os binarios em ordem correta
  pilha->topo --;//tira um para que comece o vetor no local correto

  while(pilha->topo >= 0){
    x = 0;
    do{//calcula os binarios
      binario_esta[x] = pilha->vetor[pilha->topo] % 2;
      pilha->vetor[pilha->topo] /= 2;
      x++;
    }while(pilha->vetor[pilha->topo] > 0);
      x--;
      for(x; x >= 0; x--){//inverte os resultados do numero binario
      fprintf(arquivo_saida, "%d",binario_esta[x]);//imprime o numero binario no arquivo de saida
    }
    fputc('\n', arquivo_saida);//pula uma linha no arquivo de saida
    pilha->topo--;
  }//while
}

typedef struct no_pilha_dinamica * ptr_dinam;

typedef struct{
  int qntd_dina;
  ptr_dinam top;
}pilha_dinamica;

typedef struct no_pilha_dinamica{
  ptr_dinam seguinte;
  int valor;
}pilha_dinamica_no;



void empilhaPilhaDina(pilha_dinamica * pilha){
  pilha->qntd_dina = 0;
  int valor_digit;
  ptr_dinam sub;
  pilha->top = NULL;
  while(fscanf(arquivo_entrada,"\n%d", &valor_digit) != EOF){
    if(valor_digit >= 0){
    sub = (ptr_dinam)malloc (sizeof(ptr_dinam));
    pilha->qntd_dina++;
    sub->valor = valor_digit;
    sub->seguinte = pilha->top;
    pilha->top = sub;
  }else{//caso o valor pego não seja positivo
    printf("Valor negativo e invalido\n");
    exit(0);
   }
  }
}

void VerificaPilhaDina(pilha_dinamica *pilha){
  if(pilha->qntd_dina == 0){
    printf("Pilha vazia\n");
    return;
  }
}

void desempilha_Bin_Dina(pilha_dinamica * pilha){
  int x = 0;
  int valor_result;
  int binario_dina[20];
  ptr_dinam sub;

  sub = pilha->top;

  while(pilha->top != NULL){
    x = 0;
    sub = pilha->top;
    valor_result = sub->valor;
    pilha->top = pilha->top->seguinte;
    printf("%d\n",valor_result);
    do{//calcula os valores binarios
      binario_dina[x] = valor_result % 2;
      valor_result /= 2;
      x++;
    }while(valor_result > 0);
      x--;
      for(x; x >= 0; x--){//inverte os valores binarios
      fprintf(arquivo_saida, "%d",binario_dina[x]);
    }
    fputc('\n', arquivo_saida);
  }//while
  free(sub);
}

int main (int argc, char *argv[]){
  char tipo_leitura;
  char seg_char;
  pilha_estatica pilhae;
  pilha_dinamica pilhad;
  int compara;
  arquivo_entrada = fopen("entrada.txt","r");
  arquivo_saida = fopen("saida.txt", "w");
  tipo_leitura = fgetc(arquivo_entrada);//coleta o primeiro caracter da linha
  seg_char = fgetc(arquivo_entrada);//pega o segundo caracter da linha

if(arquivo_entrada != NULL && arquivo_saida != NULL){//caso haja algum erro ao abrir um dos arquivos
  if(seg_char == '\n'){//confirma se tem apenas um caracter na primeira linha
  switch(tipo_leitura){
    case 'e':
    case 'E':
    printf("Pilha estatica\n");
    empilhaPilhaEsta(&pilhae);
    VerificaPilhaEsta(&pilhae);
    Desempilha_Bin_est(&pilhae);
    //pilha estática
    break;
    case 'd':
    case 'D':
    printf("Pilha dinamica\n");
    empilhaPilhaDina(&pilhad);
    VerificaPilhaDina(&pilhad);
    desempilha_Bin_Dina(&pilhad);
    //pilha dinamica
    break;
    default:
    printf("O primeiro caracter e invalido\n");
    break;
  }
}else{
  printf("Caracter invalido ou faltou informacoes");
}
}else{
  printf("Erro ao abrir o(s) arquivo(s)");
}

  fclose(arquivo_entrada);
  fclose(arquivo_saida);
  return 0;
}
