/*
Problema: A nova Escala do Jazz

Descrição:

De acordo com as entradas as seguintes entradas em sequência: quantidade de escalas; quantidade de acordes, e posições de cada acorde em um círculo de tamanho igual ao tamanho da escala.
Esse algoritmo descobre se é possível organizar essas notas de forma que exista apenas uma delas em cada sudvisão de tamanho igual à "escala/acordes" nesse círculo
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool condicao(int *pos, int *fdiv, int *sdiv, int i){
    if(fdiv[i] < sdiv[i]){
        return false;
    }
    if(fdiv[i]==sdiv[i] && sdiv[i]==pos[i]){
        return false;
    }
    if(sdiv[i] < pos[i]){
        return false;
    }
    return true;
}

bool corrige(int *fdiv, int *sdiv, int t_div, int i, int acordes, int escala){
    int cont=0;
    if(i==acordes-1){
        if(sdiv[0] - t_div < 0){
            if(escala + sdiv[0] - t_div < sdiv[acordes-1]){
                sdiv[acordes-1] = escala + sdiv[0] - t_div;
                cont++;
            }
        }
        if(fdiv[0] - t_div < 0){
            if(escala + fdiv[0] - t_div > fdiv[acordes-1]){
                fdiv[acordes-1] = escala + fdiv[0] - t_div;
                cont++;
            }
        }
    }
    else{
        if(sdiv[i+1] - t_div < sdiv[i]){
            sdiv[i] = sdiv[i+1] - t_div;
            cont++;
        }
        if(fdiv[i+1] - t_div > fdiv[i]){
            fdiv[i] = fdiv[i+1] - t_div;
            cont++;
        }
    }
    if(cont!=0)
        return true;
    else
        return false;
}

bool problem(int t_div, int acordes, int escala){
    int *pos = malloc(acordes*sizeof(int));
    int *fdiv = malloc(acordes*sizeof(int));
    int *sdiv = malloc(acordes*sizeof(int));
    int i, j, first;
    bool lixo;

    scanf("%d", &first);
    pos[0] = 0;
    fdiv[0] = 0;
    for(i=1; i<acordes; i++){
        scanf("%d", &pos[i]);
        pos[i] = pos[i] - first;
        sdiv[i-1] = pos[i];
        fdiv[i] = pos[i];
    }
    sdiv[acordes-1] = escala;

    lixo = corrige(fdiv, sdiv, t_div, acordes-1, acordes, escala);
    if(condicao(pos, sdiv, fdiv, acordes-1)==false)
        return false;
    i=acordes-2;
    do{
        j=i;
        while(corrige(fdiv, sdiv, t_div, j, acordes, escala)){
            if(condicao(pos, sdiv, fdiv, j)==false)
                return false;
            j--;
            if(j<0)
                j = acordes-1;
        }
        i--;
    }while(i>=0);
    return true;
}

int main(){
    int escala, acordes;
    scanf("%d %d", &escala, &acordes);
    if(problem(escala/acordes, acordes, escala))
        printf("S");
    else
        printf("N");
    return 0;
}
