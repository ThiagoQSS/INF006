#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct no {
    int valor;
    struct no * esquerda;
    struct no * direita;
} No;

typedef struct {
    No * inicio;
} Raiz;


Raiz * initLista() 
{
    Raiz * arv = malloc(sizeof(Raiz));
    arv->inicio = NULL;
    return arv;
}


int inserirEmArv(Raiz * arv, int valor) //vai retornar o 
{
    No * novo = malloc(sizeof(No));
    novo->valor = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;

    if (arv->inicio == NULL) {
        arv->inicio = novo;
        return 0;
    }

    No * aux = arv->inicio;
    int keep = 1;
    while (keep)
    {
        if (valor > aux->valor) 
        {
            if(aux->direita != NULL) 
                aux = aux->direita;
            else {
                aux->direita = novo;
                keep = 0;
            }
        } 
        else if(valor < aux->valor) 
        {
            if(aux->esquerda != NULL) 
                aux = aux->esquerda;
            else {
                aux->esquerda = novo;
                keep = 0;
            }
        }
    }
}


int main () 
{

    system("cls||clear");

}