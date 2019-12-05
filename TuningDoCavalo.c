/*
Problema: Tuning do cavalo

Descrição:

Esse algoritmo trabalho em cima de um tabuleiro com no máximo tamanho igual a 10x10 e configurações indicadas nas entradas que mostram, para cada linha, o índice de "início" no vetor para se colocar "quantidade" posições a partir dele.
Dado essa entrada, e conhecendo o movimento que um cavalo pode fazer em um tabuleiro de xadrez, esse algoritmo explora as posições por backtracking que o cavalo consegue chegar nesse tabuleiro e mostra como saída a quantidade de posições que ele não consegue chegar.
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TAM 10

void backtrack(bool entrada[TAM][TAM], int i, int j, int *q_elementos){
      int q, q_atual;
      if(i>=10||j>=10||i<0||j<0)
              return;
      else if(entrada[i][j]==false)
              return;
      else{
              q_atual = *q_elementos - 1;
              entrada[i][j] = false;
              q = q_atual;
              backtrack(entrada, i+1, j+2, &q);
              if(q<*q_elementos)
                *q_elementos = q;
              q = q_atual;
              backtrack(entrada, i+1, j-2, &q);
              if(q<*q_elementos)
                *q_elementos = q;
              q = q_atual;
              backtrack(entrada, i-1, j+2, &q);
              if(q<*q_elementos)
                *q_elementos = q;
              q = q_atual;
              backtrack(entrada, i-1, j-2, &q);
              if(q<*q_elementos)
                *q_elementos = q;
              q = q_atual;
              backtrack(entrada, i+2, j+1, &q);
              if(q<*q_elementos)
                *q_elementos = q;
              q = q_atual;
              backtrack(entrada, i+2, j-1, &q);
              if(q<*q_elementos)
                *q_elementos = q;
              q = q_atual;
              backtrack(entrada, i-2, j+1, &q);
              if(q<*q_elementos)
                *q_elementos = q;
              q = q_atual;
              backtrack(entrada, i-2, j-1, &q);
              if(q<*q_elementos)
                *q_elementos = q;
              entrada[i][j] = true;
      }
}

int main(void) {
        bool entrada[TAM][TAM];
        int i, j, n, q_elementos=0;
        int inicio, quantidade;
        for(i=0;i<TAM;i++){
                for(j=0;j<TAM;j++){
                        entrada[i][j] = false;
                }
        }
        scanf("%d", &n);
        for(i=0;i<n;i++){
                scanf("%d %d", &inicio, &quantidade);
                q_elementos = q_elementos + quantidade;
                for(j=inicio;j<inicio+quantidade;j++){
                        entrada[i][j] = true;
                }
        }
        backtrack(entrada, 0, 0, &q_elementos);
        printf("%d", q_elementos);
        return 0;
}
