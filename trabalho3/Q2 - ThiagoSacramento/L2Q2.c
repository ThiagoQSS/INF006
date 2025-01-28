#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define TAM 10000

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
        } else
            break;
    }
}

No * buscarElemento(Raiz * arv, int valor) 
{
    No * aux = arv->inicio;
    while(aux != NULL) {
        if(valor > aux->valor)
            aux = aux->direita;
        else if (valor < aux->valor)
            aux = aux->esquerda;
        else
            return aux;
    }
    printf("Buscar elemento: Null\n");
    return NULL;
}


No * buscarSucessorimediato(No * elemento) 
{
    if(elemento == NULL)
        return NULL;
    No * aux = elemento;
    if(aux->direita == NULL) {
        printf("Direita nula");
        return NULL;
    }
    aux = aux->direita;
    while (aux->esquerda)
        aux = aux->esquerda;
    return aux;
}


int main() 
{

    system("clear||cls");

    Raiz * arvore = initArv();
    inserirEmArv(arvore, 5);
    inserirEmArv(arvore, 7);
    inserirEmArv(arvore, 3);
    inserirEmArv(arvore, 9);
    inserirEmArv(arvore, 12);
    inserirEmArv(arvore, 4);


    printf("%d\n", buscarSucessorimediato(buscarElemento(arvore, 4))->valor);

}
