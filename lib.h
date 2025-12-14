#pragma once

#define TAMANHO 300

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct no{

    char* arquivo;
    struct no* proximo;
    struct no* anterior;

} No;

typedef struct listaDupla {

    No* inicio;
    No* fim;

} ListaDupla;


ListaDupla* criar_lista();

void destruir_lista(ListaDupla *l);

void inserir_inicio(ListaDupla *l, char *arquivo);

void inserir_fim(ListaDupla *l, char *arquivo);

int remover_item(ListaDupla *l, char *arquivo);

int esta_vazia(ListaDupla *l);

void imprimir_frente(ListaDupla *l);

void imprimir_tras(ListaDupla *l);

void imprimir(char *arquivo, char nomeImpressora);

//-------------------------------------------------------------------//

void impressoraTrasPFrente(ListaDupla *l, char nomeImpressora);

void impressoraFrentePTras(ListaDupla *l, char nomeImpressora);
