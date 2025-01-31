#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define TAM 10000


typedef struct no {
    int valor;
    int altura;
    struct no * esquerda;
    struct no * direita;
    struct no * parent;
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


int inserirEmArv(Raiz * arv, int valor) //vai retornar se ocorreu a inserção
{
    No * novo = malloc(sizeof(No));
    novo->valor = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    novo->parent = NULL;

    if (arv->inicio == NULL) {
        arv->inicio = novo;
        return 1;
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
                novo->parent = aux;
                novo->altura = altura;
                return 1;
            }
        } 
        else if(valor < aux->valor)
        {
            if(aux->esquerda != NULL) 
                aux = aux->esquerda;
            else {
                aux->esquerda = novo;
                novo->parent = aux;
                novo->altura = altura;
                return 1;
            }
        } else
            return 0;
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
    No * parent;
    if(aux->direita != NULL) {
        aux = aux->direita;
        while (aux->esquerda)
            aux = aux->esquerda;
        return aux;
    } 
    else if (aux->parent != NULL){
        parent = aux->parent;
        while(parent->direita == aux) {
            aux = parent;
            parent = aux->parent;
        }
        return parent;
    }
    else
        return NULL;
}


No * buscarMinimo(Raiz * arv) 
{
    No * aux = arv->inicio;
    while(aux->esquerda)
        aux = aux->esquerda;
    return aux;
}


int somarSubArvore(No * galho) 
{
    if (galho == NULL)
        return 0;
    int valor = galho->valor;
    if (galho->direita == NULL)
        return valor + somarSubArvore(galho->esquerda);
    if (galho->esquerda == NULL)
        return valor + somarSubArvore(galho->direita);
    if (galho->direita == NULL && galho->esquerda == NULL) 
        return valor;
    return valor + somarSubArvore(galho->esquerda) + somarSubArvore(galho->direita);
}


int calcularDiffEsqDir(No * galho) {
    if (galho->direita == NULL && galho->esquerda == NULL) 
        return 0;
    if (galho->esquerda == NULL)
        return 0 - somarSubArvore(galho->direita);
    if (galho->direita == NULL)
        return somarSubArvore(galho->esquerda);
    return somarSubArvore(galho->direita) - somarSubArvore(galho->esquerda);
}


int main() 
{

    system("clear||cls");

    Raiz * arvore = initArv();

    
}
