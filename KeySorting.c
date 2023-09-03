#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *arquivo_entrada;
FILE *arquivo_saida;

//Não consegui fazer o arquivo ordenar, desculpa não entregar tudo.


typedef struct {
  char chave[3];
  char primeiroNome[16];
  char sobrenome[16];
  char nomeHeroi[16];
  char poder[16];
  char fraqueza[21];
  char cidade[21];
  char profissao[21];
} Heroi;

typedef struct {
  Heroi Dados;
  char chaveRRN[3];
} Array;

typedef struct {
  Array *vetor;
} Vet;

Array Separa(char *string) {
  Array dado;
  char* aux = strtok(string, "|\n");
  strcpy(dado.Dados.chave, aux);
  aux = strtok(NULL, "|\n");
  strcpy(dado.Dados.primeiroNome, aux);
  aux = strtok(NULL, "|\n");
  strcpy(dado.Dados.sobrenome, aux);
  aux = strtok(NULL, "|\n");
  strcpy(dado.Dados.nomeHeroi, aux);
  aux = strtok(NULL, "|\n");
  strcpy(dado.Dados.poder, aux);
  aux = strtok(NULL, "|\n");
  strcpy(dado.Dados.fraqueza, aux);
  aux = strtok(NULL, "|\n");
  strcpy(dado.Dados.cidade, aux);
  aux = strtok(NULL, "|\n");
  strcpy(dado.Dados.profissao, aux);
  return (dado);
}

void iniciaIndiceArquivo(Vet *Dinam, int cont) {
  Dinam->vetor = (Array*)malloc(cont * sizeof(Array));
  char string[150];
  Array info;
  char chave[3];
  int i = 0;

  fgets(string, 150, arquivo_entrada);
  printf("Leitura: %s\n", string);

  while(!feof(arquivo_entrada)) {
    if(fgets(string, 150, arquivo_entrada)!= NULL) {
      info = Separa(string);
      strcpy (info.chaveRRN, info.Dados.chave);
      Dinam->vetor[i] = info;
      i++;
    }
  }
  rewind(arquivo_entrada);
  return;
}

void Imprime(Vet *Dinam, int cont) {
  Array Valor;
  Heroi heroi;
  for(int i = 0; i < cont; i++) {
    Valor = Dinam->vetor[i];
    fprintf(arquivo_saida, "%s|", Valor.Dados.chave);
    fprintf(arquivo_saida, "%s|", Valor.Dados.primeiroNome);
    fprintf(arquivo_saida, "%s|", Valor.Dados.sobrenome);
    fprintf(arquivo_saida, "%s|", Valor.Dados.nomeHeroi);
    fprintf(arquivo_saida, "%s|", Valor.Dados.poder);
    fprintf(arquivo_saida, "%s|", Valor.Dados.fraqueza);
    fprintf(arquivo_saida, "%s|", Valor.Dados.cidade);
    fprintf(arquivo_saida, "%s|\n", Valor.Dados.profissao);
  }
}

void swap(char a[3], char b[3]){
  char aux[3];
  strcpy(a, aux);
  strcpy(b, a);
  strcpy(aux, b);
  return;
}

void MergeSort (int inicio, int meio, int fim, Vet *Dinam){
  char * vetoraux;
  vetoraux = malloc((fim - inicio) * sizeof(char));
  Array Valor;
  Array aux;
  int aux1 = inicio;
  int aux2 = meio + 1;
  int vet = 0;
  while (aux1 <= meio && aux2 <= fim){
    Valor = Dinam->vetor[aux1];
    aux = Dinam->vetor[aux2];
    if(strcmp(Valor.chaveRRN, aux.chaveRRN) <= 0){
      aux = Dinam->vetor[vet];
      strcpy(aux.chaveRRN, Valor.chaveRRN);
      aux1++;
      vet++;
    }else{
      Valor = Dinam->vetor[aux2];
      aux = Dinam->vetor[vet];
      strcpy(aux.chaveRRN, Valor.chaveRRN);;
      aux2++;
      vet++;
    }
  }
  if(aux1 == meio){
    while(aux2 <= fim){
      Valor = Dinam->vetor[aux1];
      aux = Dinam->vetor[vet];
      strcpy(Valor.chaveRRN, aux.chaveRRN);
      vet++;
      aux1++;
    }
  }else{
    while(aux1 <= meio){
      Valor = Dinam->vetor[aux2];
      aux = Dinam->vetor[vet];
      strcpy(Valor.chaveRRN, aux.chaveRRN);
      vet++;
      aux2++;
  }
}
    for(int i = inicio; i <= fim; i++){
      Valor = Dinam->vetor[i];
      aux = Dinam->vetor[i-inicio];
      strcpy(aux.chaveRRN, Valor.chaveRRN);;
    }
    free(vetoraux);
    return;
}

void Merge(Vet* Dinam,int inicio, int fim){
  int meio = (inicio + fim)/2;
  if(inicio < fim){
    Merge(Dinam, inicio, meio);
    Merge(Dinam, meio + 1, fim);
    MergeSort(inicio, meio, fim, Dinam);
  }
  return;
}

void MergeSortRev (int inicio, int meio, int fim, Vet *Dinam){
  char * vetoraux;
  vetoraux = malloc((fim - inicio) * sizeof(char));
  Array Valor;
  Array aux;
  int aux1 = inicio;
  int aux2 = meio + 1;
  int vet = 0;
  while (aux1 <= meio && aux2 <= fim){
    Valor = Dinam->vetor[aux1];
    aux = Dinam->vetor[aux2];
    if(strcmp(Valor.chaveRRN, aux.chaveRRN) <= 0){
      aux = Dinam->vetor[vet];
      strcpy(aux.chaveRRN, Valor.chaveRRN);
      aux1++;
      vet++;
    }else{
      Valor = Dinam->vetor[aux2];
      aux = Dinam->vetor[vet];
      strcpy(aux.chaveRRN, Valor.chaveRRN);;
      aux2++;
      vet++;
    }
  }
  if(aux1 == meio){
    while(aux2 <= fim){
      Valor = Dinam->vetor[aux1];
      aux = Dinam->vetor[vet];
      strcpy(Valor.chaveRRN, aux.chaveRRN);
      vet++;
      aux1++;
    }
  }else{
    while(aux1 <= meio){
      Valor = Dinam->vetor[aux2];
      aux = Dinam->vetor[vet];
      strcpy(Valor.chaveRRN, aux.chaveRRN);
      vet++;
      aux2++;
  }
}
    for(int i = inicio; i <= fim; i++){
      Valor = Dinam->vetor[i];
      aux = Dinam->vetor[i-inicio];
      strcpy(aux.chaveRRN, Valor.chaveRRN);;
    }
    free(vetoraux);
    return;
}

void MergeRev(Vet* Dinam,int inicio, int fim){
  int meio = (inicio + fim)/2;
  if(inicio < fim){
    MergeRev(Dinam, inicio, meio);
    MergeRev(Dinam, meio + 1, fim);
    MergeSortRev(inicio, meio, fim, Dinam);
  }
  return;
}

void Insertion(Vet *Dinam, int cont){
  char aux[3];
  int j;
  Array Valor;
  for(int i = 0; i < cont; i++){
    Valor = Dinam->vetor[i];
    strcpy(Valor.chaveRRN, aux);
    j = i - 1;
    while(j >= 0 &&  strcmp(aux, Valor.chaveRRN) < 0){
      Dinam->vetor[j+1] = Dinam->vetor[j];
      j--;
    }
    Valor = Dinam->vetor[j+1];
    strcpy(aux, Valor.chaveRRN);
  }
  Imprime(Dinam, cont);
  return;
}

void InsertionRev(Vet *Dinam, int cont){
  char aux[3];
  int j;
  Array Valor;
  for(int i = 0; i < cont; i++){
    Valor = Dinam->vetor[i];
    strcpy(aux, Valor.chaveRRN);
    j = i - 1;
    while(j >= 0 &&  strcmp(aux, Valor.chaveRRN) > 0){
      Dinam->vetor[j+1] = Dinam->vetor[j];
      j--;
    }
    Valor = Dinam->vetor[j+1];
    strcpy(aux, Valor.chaveRRN);
  }
  Imprime(Dinam, cont);
  return;
}

int divide (Vet* Dinam, int inicio, int fim){
  Array Valor;
  Array aux;
  int esquerda = inicio;
  int direita = fim;
  Valor = Dinam->vetor[inicio];
  char pivo[3];
  strcpy(Valor.chaveRRN, pivo);
  while(esquerda <= direita){
    Valor = Dinam->vetor[esquerda];
    while(strcmp(Valor.chaveRRN, pivo) <= 0 && esquerda <= fim){
       esquerda++;
    }
    Valor = Dinam->vetor[direita];
    while(strcmp(pivo, Valor.chaveRRN) > 0 && direita >= inicio){
       direita--;
    }
    if(esquerda < direita){
      aux = Dinam->vetor[direita];
      Valor = Dinam->vetor[esquerda];
      swap(Valor.chaveRRN, aux.chaveRRN);
}
}
  aux = Dinam->vetor[direita];
  Valor = Dinam->vetor[esquerda];
  swap(Valor.chaveRRN, aux.chaveRRN);
  return(direita);
}

void Quick(int fim, int inicio, Vet* Dinam){
  if (inicio < fim - 1){
  int pivo = divide(Dinam, inicio, fim - 1);
  Quick(fim, pivo-1, Dinam);
  Quick(pivo+1, fim, Dinam);
  }
}

int divideRev (Vet* Dinam, int inicio, int fim){
  Array Valor;
  Array aux;
  int esquerda = inicio;
  int direita = fim;
  Valor = Dinam->vetor[inicio];
  char pivo[3];
  strcpy(Valor.chaveRRN, pivo);
  while(esquerda <= direita){
    Valor = Dinam->vetor[esquerda];
    while(strcmp(Valor.chaveRRN, pivo) <= 0 && esquerda <= fim){
       esquerda++;
    }
    Valor = Dinam->vetor[direita];
    while(strcmp(pivo, Valor.chaveRRN) > 0 && direita >= inicio){
       direita--;
    }
    if(esquerda > direita){
      aux = Dinam->vetor[direita];
      Valor = Dinam->vetor[esquerda];
      swap(Valor.chaveRRN, aux.chaveRRN);
}
}
  aux = Dinam->vetor[direita];
  Valor = Dinam->vetor[esquerda];
  swap(Valor.chaveRRN, aux.chaveRRN);
  return(direita);
}

void QuickRev(int fim, int inicio, Vet* Dinam){
  if (inicio < fim - 1){
  int pivo = divideRev(Dinam, inicio, fim - 1);
  QuickRev(fim, pivo-1, Dinam);
  QuickRev(pivo+1, fim, Dinam);
  }
  Imprime(Dinam, fim);
}

void CriaHeap (Vet *Dinam, int i, int f, int cont){
   Array Valor;
   Array aux2;
   Valor = Dinam->vetor[i];
   char aux[3];
   strcpy(Valor.chaveRRN, aux);
   int j = i * 2 + 1;
   while(j <= f){
     if(j < f){
       Valor = Dinam->vetor[j];
       aux2 = Dinam->vetor[j+1];
       if(strcmp(Valor.chaveRRN, aux2.chaveRRN) < 0){
         j = j + 1;
       }
       cont++;
     }
     Valor = Dinam->vetor[j];
     if(strcmp(aux, Valor.chaveRRN) < 0){
       strcpy(Valor.chaveRRN, aux);
       i = j;
       j = 2 * i + 1;
     }else{
       j = f + 1;
     }
   }
   Valor = Dinam->vetor[i];
   strcpy(aux, Valor.chaveRRN);
}

void Heap(Vet *Dinam, int cont){
  int i;
  Array Valor;
  Array aux;
  int n = cont;
  for(i = (n - 1)/2; i >= 0; i--){
    CriaHeap(Dinam, i, n-1, cont);
  }
  for(i = n-1; i >= 1; i--){
    aux = Dinam->vetor[0];
    Valor = Dinam->vetor[i];
    swap(aux.chaveRRN, Valor.chaveRRN);
    CriaHeap(Dinam, 0, i-1, cont);
  }
  Imprime(Dinam, cont);
}

/*void HeapRev(){

}*/

int main(int argc, char * argv[]) {
  Vet dados;
  int size;
  int top;
  int qtd;
  char sort;
  char order;
  arquivo_entrada = fopen("entrada.txt", "r");
  arquivo_saida = fopen("saida.txt", "w");
  if(arquivo_entrada != NULL && arquivo_saida != NULL && argc != 3){
  fseek(arquivo_entrada, 0, SEEK_SET);
  fscanf(arquivo_entrada, "SIZE=%d TOP=%d QTDE=%d SORT=%c ORDER=%c\n", &size, &top, &qtd, &sort, &order);
  fseek(arquivo_entrada, 0, SEEK_SET);
  iniciaIndiceArquivo(&dados, qtd);
  if(order == 'c' || order == 'C'){
    switch(sort){
      case 'M':
      case 'm':
      Merge(&dados, 0, qtd);
      break;

      case 'I':
      case 'i':
      Insertion(&dados, qtd);
      break;

      case 'Q':
      case 'q':
      Quick(qtd, 0, &dados);
      break;

      case 'H':
      case 'h':
      Heap(&dados, qtd);
      break;

      default:
      fprintf(arquivo_saida, "Formato de ordenacao invalida\n");
    }
  }else{
    if(order == 'd' || order == 'D'){
      switch(sort){
        case 'M':
        case 'm':
        MergeRev(&dados, 0 ,qtd);
        break;

        case 'I':
        case 'i':
        InsertionRev(&dados, qtd);
        break;

        case 'Q':
        case 'q':
        QuickRev(qtd, 0, &dados);
        break;

        case 'H':
        case 'h':
        /*HeapRev(&dados);*/
        break;

        default:
        fprintf(arquivo_saida, "Formato de ordenacao invalida\n");
      }
    }else{
      fprintf(arquivo_saida, "Formato invalido");
    }
  }
}else{
fprintf(arquivo_saida, "Problema ao abrir ");
}

fclose(arquivo_entrada);
fclose(arquivo_saida);
  return 0;
}



















//----------------------------
//----------------------------
