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


Raiz * initArv() 
{
    Raiz * arv = malloc(sizeof(Raiz));
    arv->inicio = NULL;
    return arv;
}


int inserirEmArv(Raiz * arv, int valor) //vai retornar a altura
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
    int altura = 0;
    
    while (1)
    {
        altura++;
        if (valor > aux->valor) 
        {
            if(aux->direita != NULL) 
                aux = aux->direita;
            else {
                aux->direita = novo;
                return altura;
            }
        } 
        else if(valor < aux->valor) 
        {
            if(aux->esquerda != NULL) 
                aux = aux->esquerda;
            else {
                aux->esquerda = novo;
                return altura;
            }
        }
    }
}


int main () 
{
    system("cls||clear");

    Raiz * arvore = initArv(); 

    printf("%d\n", inserirEmArv(arvore, 5));
    printf("%d\n", inserirEmArv(arvore, 8));
    printf("%d\n", inserirEmArv(arvore, -1));
    printf("%d\n", inserirEmArv(arvore, 4));
    printf("%d\n", inserirEmArv(arvore, 6));
    printf("%d\n", inserirEmArv(arvore, 9));
    printf("%d\n", inserirEmArv(arvore, 11));
    printf("%d\n", inserirEmArv(arvore, 15));


}