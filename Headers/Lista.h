#pragma once
#include <windows.h>

typedef struct no {
    char *arquivo;
    struct no *proximo;
    struct no *anterior;
} No;

typedef struct {
    No *inicio;
    No *fim;
} ListaDupla;

ListaDupla* criar_lista();
void inserir_inicio(ListaDupla *l, const char *arquivo);
void inserir_fim(ListaDupla *l, const char *arquivo);
int remover_item(ListaDupla *l, const char *arquivo);
int esta_vazia(ListaDupla *l);
void destruir_lista(ListaDupla *l);