/*
Problema: Padrões em DNA

Descrição:

Esse algoritmo trabalha em cima de uma entrada que é uma sequência de DNA de tamanho máximo 2000 com mutações existentes em "n" posições também indicadas pela entrada.
Utilizando programação dinânica, esse algoritmo procura a sequência de DNA palíndroma contígua com um número máximo de mutações.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TAM 2000

char entrada[TAM];
bool mutados[TAM];

typedef struct{
  int tam;
  int mutados;
}MemElem;

MemElem mem[TAM][TAM];

int lps_mutados(int n){
  int i, j;
  int x=n-1, y=n-1;
  MemElem melhor;
  for(i=n-1;i>=0;i--){
    for(j=i;j<n;j++){
      melhor.tam = -1;
      melhor.mutados = -1;
      if(i==j){
        melhor.tam = 1;
        if(mutados[i])
          melhor.mutados = 1;
        else
          melhor.mutados = 0;
      }
      else if((i==j-1)&&(entrada[i]==entrada[j])){
        melhor.tam = 2;
        if(mutados[i]){
          if(mutados[j])
            melhor.mutados = 2;
          else
            melhor.mutados = 1;
        }
        else
          melhor.mutados = 0;
      }
      else{
        if(entrada[i]==entrada[j]){
          melhor.tam = 2 + mem[i+1][j-1].tam;
          if(mutados[i]){
            if(mutados[j])
              melhor.mutados = 2 + mem[i+1][j-1].mutados;
            else
              melhor.mutados = 1 + mem[i+1][j-1].mutados;
          }
          else if(mutados[j])
            melhor.mutados = 1 + mem[i+1][j-1].mutados;
          else
            melhor.mutados = mem[i+1][j-1].mutados;
        }
        if((mem[i+1][j].mutados > mem[i][j-1].mutados)||((mem[i+1][j].mutados == mem[i][j-1].mutados)&&(mem[i+1][j].tam >= mem[i][j-1].tam))){
          if((mem[i+1][j].mutados > melhor.mutados)||((mem[i+1][j].mutados == melhor.mutados)&&(mem[i+1][j].tam > melhor.tam))){
            melhor.mutados = mem[i+1][j].mutados;
            melhor.tam = mem[i+1][j].tam;
          }
        }
        else{
          if((mem[i][j-1].mutados > melhor.mutados)||((mem[i][j-1].mutados == melhor.mutados)&&(mem[i][j-1].tam >= melhor.tam))){
            melhor.mutados = mem[i][j-1].mutados;
            melhor.tam = mem[i][j-1].tam;
          }
        }
      }
      mem[i][j].tam = melhor.tam;
      mem[i][j].mutados = melhor.mutados;
      if((melhor.mutados > mem[x][y].mutados)||((melhor.mutados==mem[x][y].mutados)&&(melhor.tam >= mem[x][y].tam)))
        x = i;
        y = j;
    }
  }
  return mem[x][y].tam;
}

int main(){
  int i, j, n, pos;
  char c;
  int len_entrada;

  scanf("%s", entrada);
  len_entrada = strlen(entrada);

  for(i=0;i<TAM;i++){
    for(j=0;j<TAM;j++){
      mem[i][j].tam = -1;
      mem[i][j].mutados = -1;
    }
    mutados[i] = false;
  }
  scanf("%d", &n);
  for(i=0;i<n;i++){
    scanf("%d", &pos);
    if(pos<=len_entrada)
      mutados[pos-1] = true;
  }
  printf("%d", lps_mutados(len_entrada));
  return 0;
}
