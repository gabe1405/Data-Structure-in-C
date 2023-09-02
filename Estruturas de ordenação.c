#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>


FILE *arquivo_entrada;
FILE *arquivo_saida;
FILE *arquivo_operacoes;
FILE *arquivo_temp;

typedef struct{
  int codigo[3];
  char nome[30];
  int idade[2];
  char profissao[30];
  char genero[1];
}

void Imprime(int n, int *vetor, int contador, clock_t tempo){
  for(int i = 0; i < n; i++){
    fprintf(arquivo_saida, " %d", vetor [i]);
  }
  fprintf(arquivo_saida,", %d comp,",contador);
  fprintf(arquivo_saida," %ld\n",tempo);
}


void swap(int *a, int *b){
  int aux = *a;
  *a = *b;
  *b =aux;
  return;
}


int BubbleSort(int n, int *vetor, int cont){
  int verifica = 0;
  cont = 0;
  while(verifica == 0){
    verifica = 1;
    for(int i = 0; i < n - 1; i++){
      if(vetor[i] > vetor[1+i]){
        swap(&vetor[i], &vetor[1+i]);
        verifica = 0;
      }
      cont++;
    }
  }
  cont++;
  return(cont);
}

int SelectionSort(int n, int *vetor, int cont){//ok
  int menor;
   for(int i = 0; i < n; i++){
     menor = i;
     for(int l = i; l < n; l++){
       if(vetor[l] < vetor[menor]){
         menor = l;
       }
       cont++;
     }
     if(vetor[i] != vetor[menor]){
       swap(&vetor[menor], &vetor[i]);
     }
   }
   cont++;
  return(cont);
}

int InsertionSort(int n, int *vetor, int cont){
  int aux;
  int j;
  for(int i = 0; i < n; i++){
    aux = vetor[i];
    j = i - 1;
    while(j >= 0 &&  aux < vetor[j]){
      vetor[j+1] = vetor[j];
      j--;
      cont++;
    }
    vetor[j+1] = aux;
  }
  cont++;
  return(cont);
}

int divide (int * vetor, int inicio, int fim, int cont){
  int esquerda = inicio;
  int direita = fim;
  int pivo = vetor[inicio];
  while(esquerda < direita){
    while(vetor[esquerda] <= pivo && esquerda <= fim){
       esquerda++;
       cont++;
    }
    while(vetor[direita] > pivo && direita >= inicio){
       direita--;
       cont++;
    }
    if(esquerda < direita){
     cont++;
     swap(&vetor[esquerda], &vetor[direita]);
}
}
  swap(&vetor[direita], &vetor[inicio]);
  return (direita);
}

void QuickSort(int inicio, int fim, int *vetor, int cont){
  if (inicio < fim - 1){
  int pivo = divide(&(*vetor), inicio, fim - 1, cont);
  QuickSort(inicio, pivo-1, &(*vetor), cont);
  QuickSort(pivo+1, fim, &(*vetor), cont);
}
}

int Merge (int inicio, int meio, int fim, int *vetor, int cont){
  int * vetoraux;
  vetoraux = malloc((fim - inicio) * sizeof(int));
  cont = 0;
  int aux1 = inicio;
  int aux2 = meio + 1;
  int vet = 0;
  while (aux1 <= meio && aux2 <= fim){
    if(vetor[aux1] <= vetor[aux2]){
      vetoraux[vet] = vetor[aux1];
      aux1++;
      vet++;
    }else{
      vetoraux[vet] = vetor[aux2];
      aux2++;
      vet++;
    }
    cont++;
  }
  if(aux1 == meio){
    while(aux2 <= fim){
      vetoraux[vet] = vetor[aux1];
      vet++;
      aux1++;
    }
  }else{
    while(aux1 <= meio){
      vetoraux[vet] = vetor[aux2];
      vet++;
      aux2++;
  }
}
    for(int i = inicio; i <= fim; i++){
      vetor[i] = vetoraux[i - inicio];
    }
    free(vetoraux);
    return(cont);
}

int MergeSort(int inicio, int fim, int *vetor, int cont){
  int meio = (inicio + fim)/2;
  if(inicio < fim){
    MergeSort(inicio, meio, vetor, cont);
    MergeSort(meio + 1, fim, vetor, cont);
    cont = Merge(inicio, meio, fim, vetor, cont);
  }
  return(cont);
}

void CriaHeap (int * vetor, int i, int f, int cont){
   int aux = vetor[i];
   int j = i * 2 + 1;
   while(j <= f){
     if(j < f){
       if(vetor[j] < vetor[j+1]){
         j = j + 1;
       }
       cont++;
     }
     if(aux < vetor[j]){
       vetor[i] = vetor[j];
       i = j;
       j = 2 * i + 1;
     }else{
       j = f + 1;
     }
     cont++;
   }
   vetor[i] = aux;
}

void HeapSort(int * vetor, int n, int cont){
  int i;
  for(i = (n - 1)/2; i >= 0; i--){
    CriaHeap(*(&vetor), i, n-1, cont);
  }
  for(i = n-1; i >= 1; i--){
    swap(&vetor[0], &vetor[i]);
    CriaHeap(*(&vetor), 0, i-1, cont);
  }
}

int main (int argc, char *argv[]){
  arquivo_entrada = fopen("entrada.txt","r");
  arquivo_operacoes = fopen("op.txt","r");
  arquivo_temp = fopen("temp.txt","w");
  arquivo_saida = fopen("saida.txt","w");

  float n;
  char let;//tipo se ordenação
  int *vetor;
  int j = 0;
  char tipo;
  int aux;
  fscanf(arquivo_entrada,"%f\n", &n);
  vetor = malloc(n * sizeof(int));
    int ver = (int)n;//quantidade de valores a serem ordenados
    if(arquivo_entrada != NULL && arquivo_saida != NULL && argc == 3){
    if (ver == n){
      while((let = fgetc(arquivo_entrada)) != EOF){
      if(j == 0){
      tipo = let;
    }
      j++;
    }
    if(j <= 2){
      switch(tipo){
      case 'd':
      aux = n;
      for(int i = 0; i < n; i++){
        vetor[i] = aux;
        aux--;
      }
      CasoDecre(ver, vetor);
      break;
      case 'c':
      for(int i = 0; i < n; i++){
        vetor[i] = i+1;
      }
      CasoCresc(ver, vetor);
      break;
      case 'r':
      for(int i = 0; i < n; i++){
        vetor[i] = rand()%32000;
    }
      CasoAleat(ver, vetor);
      break;
      default:
      fprintf(arquivo_saida,"Formato invalido\n");
      break;
    }
    }else{
      fprintf(arquivo_saida,"Formato invalido\n");
    }
    }else{
      fprintf(arquivo_saida,"Formato invalido\n");
    }
  }else{
    fprintf(arquivo_saida,"Problema ao abrir o arquivo\n");
  }

  free(vetor);
  fclose(arquivo_entrada);
  fclose(arquivo_saida);
  fclose(arquivo_operacoes);
  fclose(arquivo_temp);

  return 0;
}
