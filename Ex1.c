#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int TempoMinutos(int *totalMinutos, int *Minutos, int *Horas){
  *Horas = *totalMinutos / 60;//calcula o tempo que será dado em horas
  *Minutos =  (*totalMinutos) - (*Horas) * 60;//calcula os minutos baseado no tempo em horas anterior
  printf("Tempo em horas e minutos: %d:%d\n",*Horas, *Minutos);
  return 0;
}

int main(){

  int totalMinutos;
  int Horas, Minutos;

  printf("Digite aqui uma quantidade de tempo em minutos: ");
  scanf("%d", &totalMinutos);

  TempoMinutos(&totalMinutos, &Minutos, &Horas);

  return 0;
}
