#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define TAM 1000
#define TAM_NOME 1000
#define TAM_STRING 10000

//strcpy(pilha1->pilha[x], "seilaporra"); 

typedef struct Base {
    char pilha[TAM][TAM_NOME];
    int topo;
} Base;



Base * createStack() 
{
    Base * novaPilha = malloc(sizeof(Base));
    novaPilha->topo = 0;

    return novaPilha;
}



void push(Base * pilha, char nome[]) 
{
    if(pilha->topo < TAM){
        strcpy(pilha->pilha[pilha->topo], nome);
        pilha->topo++;
    }
    else
        printf("Erro: Sem espaço");
}



char * pop(Base * pilha) 
{
    pilha->topo--;
    return pilha->pilha[pilha->topo];
}



char * getTopData (Base * pilha) 
{
    return pilha->pilha[pilha->topo - 1];
}



int stackEmpty(Base * pilha) {
    if (pilha->topo == 0)
        return 1;
    else
        return 0;
}



void juntarPilha(Base * pilha, Base * reserva, FILE * saida) 
{
    while (reserva->topo > 0) {
        fprintf(saida, " push-%s", getTopData(reserva));
        push(pilha, pop(reserva));
    }
}



void inserirEmOrdem(Base * pilha, Base * reserva, char nome[], FILE * saida)
{
    int toBreakLine = 0;
    int popCont = 0;
    int index = 0;
    int troca = 1;

    for (int i = 0; nome[i]; i++)
        if(nome[i] == '\n') {
            nome[i] = '\0';
            toBreakLine = 1;
            break;
        }
    //

    if(pilha->topo == 0) {
        push(pilha, nome);
        fprintf(saida, "push-%s", nome);
    }
    else 
    {
        while (troca) {
            troca = 0;
            index = 0;
            if (pilha->topo != 0) {    
                while (pilha->pilha[pilha->topo - 1][index] == nome[index] && nome[index] != '\0' && pilha->pilha[pilha->topo - 1][index] != '\0')
                    index++;
                if (pilha->pilha[pilha->topo - 1][index] > nome[index]) {
                    push(reserva, pop(pilha));
                    popCont++;
                    troca = 1;
                }
            }
        }

        push(pilha, nome);
        if (popCont > 0)
            fprintf(saida, " %dx-pop", popCont);
        //
        fprintf(saida, " push-%s", nome);
        //
        juntarPilha(pilha, reserva, saida);
    }

    if(toBreakLine)
        fprintf(saida, "\n");
}




void imprimirPilha(Base * pilha) {
    for (int i = pilha->topo - 1; i >= 0; i--)
        puts(pilha->pilha[i]);        
}




int main () 
{
    system("cls||clear");

    FILE * entrada;
    FILE * saida;

    char string[TAM_STRING];
    char separador[] = " ";
    char * chunk;

    entrada = fopen("L1Q2.in", "r");
    saida = fopen("L1Q2.out", "w");
    
    if (entrada == NULL || saida == NULL) {
        printf("Erro ao abrir arquivos!");
        return 0;
    }
    //

    while (fgets(string, TAM_STRING, entrada)) 
    {

        string[strcspn(string, '\n')] = '\0';
        string[strcspn(string, '\r')] = '\0';

        Base * pilha = createStack();
        Base * reserva = createStack();

        chunk = strtok(string, separador);

        while (chunk != NULL)
        {
            inserirEmOrdem(pilha, reserva, chunk, saida);

            chunk = strtok(NULL, separador);
        }
        
        imprimirPilha(pilha);
        printf("\n------------------------------------------\n");
    }

    fclose(entrada);
    fclose(saida);
}