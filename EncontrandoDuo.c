/*
Problema: Encontrando Duo

Descrição:

Dado uma entrada de usuários que indicam outros usuários como parceiros em um jogo, essas indicações podem ser representadas como grafos.
De acordo com essa representação, a saída deve ser os elementos nesse grafo ordenados de forma crescente de forma que todos sejam parte de um grafo fortemente conexo, ou seja, se indicam entre si.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*ORDENACAO EM HEAP*/
void Troca(int *vetor,int i,int i2){
    int aux;
    aux=vetor[i2];
    vetor[i2]=vetor[i];
    vetor[i]=aux;
}
int heap(int *vetor,int i_pai,int n){
    if(2*(i_pai+1)<n){
        if(vetor[i_pai]<=vetor[2*(i_pai+1)-1])
            return 0;
        if(vetor[i_pai]<=vetor[2*(i_pai+1)])
            return 0;
    }
    else if(2*(i_pai+1)-1<n){
        if(vetor[i_pai]<=vetor[2*(i_pai+1)-1])
            return 0;
    }
    return 1;
}
void Refaz(int *vetor,int inicio,int n){
    int i=inicio;
    while((heap(vetor,i,n)==0)){
        if((2*(i+1)<n)&&(vetor[2*(i+1)-1]>vetor[2*(i+1)])){
            Troca(vetor,i,2*(i+1)-1);
            i=2*(i+1)-1;
        }
        else if((2*(i+1)<n)&&(vetor[2*(i+1)-1]<=vetor[2*(i+1)])){
            Troca(vetor,i,2*(i+1));
            i=2*(i+1);
        }
        else{
            Troca(vetor,i,2*(i+1)-1);
            i=2*(i+1)-1;
        }
    }
}
void Constroi(int *vetor,int n){
    int i;
    for(i=n/2-1;i>=0;i--){
        if(heap(vetor,i,n)==0){
            Refaz(vetor,i,n);
        }
    }
}
void ord_Heapsort(int *vetor,int n){
    int restante;
    Constroi(vetor,n);
    restante=n;
    while(restante>1){
        Troca(vetor,0,restante-1);
        Refaz(vetor,0,restante-1);
        restante--;
    }
}
/*FIM DA ORDENACAO EM HEAP*/

typedef struct Selement *Telement;
typedef struct Selement{
    int qalcanca;
    int aponta;
}Element;

void elimina(Telement vet, int i){
    int j;
    int ant;
    vet[i].qalcanca = 0;
    ant = i;
    j = vet[i].aponta;
    vet[ant].aponta = -1;
    while(true){
        if(j==-1){
            return;
        }
        else if(vet[j].qalcanca>=2){
            vet[j].qalcanca--;
            return;
        }
        vet[j].qalcanca = 0;
        ant = j;
        j = vet[j].aponta;
        vet[ant].aponta = -1;
    }
}

int caminho_nao_explorado(Telement vet, int i, bool *map_exp){
    int j, t=1;
    j = vet[i].aponta;
    map_exp[i] = true;
    while(j!=i){
        if(map_exp[j]||j==-1)
            return (-1);
        map_exp[j] = true;
        j = vet[j].aponta;
        t++;
    }
    return t;
}
void concatena_ciclo(Telement vet, int i, int tam, int *resp, int *max_tam){
    int k = i;
    int j;
    for(j=0;j<tam;j++){
        resp[*max_tam] = k+1;
        *max_tam = *max_tam + 1;
        k = vet[k].aponta;
    }
}
void imprime_resp(int *resp, int n){
    int i;
    printf("%d", resp[0]);
    for(i=1;i<n;i++){
        printf(" %d", resp[i]);
    }
}

void problem(Telement vet, int n){
    int i, j;
    int max_tam=0, max_i=-1, tam;
    bool *map_exp = (bool*)malloc(n*sizeof(bool));
    int *resp = (int*)malloc(n*sizeof(int));
    for(i=0;i<n;i++){
        map_exp[i] = false;
    }
    for(i=0;i<n;i++){
        if(vet[i].qalcanca==0){
            elimina(vet, i);
            map_exp[i] = true;
        }
    }
    for(i=0;i<n;i++){
        if(map_exp[i]==false){
            tam = caminho_nao_explorado(vet, i, map_exp);
            if(tam!=-1){
                concatena_ciclo(vet, i, tam, resp, &max_tam);
            }
        }
    }
    ord_Heapsort(resp, max_tam);
    imprime_resp(resp, max_tam);
}

int main(){
    int n, i, usuario, aponta;
    Telement vet;
    bool *map_indica;
    scanf("%d", &n);
    vet = (Telement)malloc(n*sizeof(Element));
    map_indica = (bool*)malloc(n*sizeof(bool));
    for(i=0;i<n;i++){
        vet[i].qalcanca = 0;
        vet[i].aponta = -1;
        map_indica[i] = false;
    }
    for(i=0;i<n;i++){
        scanf("%d %d", &usuario, &aponta);
        if(map_indica[usuario-1]==false){
            vet[aponta-1].qalcanca++;
            vet[usuario-1].aponta = aponta-1;
            map_indica[usuario-1] = true;
        }
    }
    problem(vet, n);
    return 0;
}
