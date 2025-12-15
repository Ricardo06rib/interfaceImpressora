#include "headers/lista.h"
#include <stdlib.h>
#include <string.h>

ListaDupla* criar_lista() {
    ListaDupla *l = malloc(sizeof(ListaDupla));
    l->inicio = l->fim = NULL;
    return l;
}

int esta_vazia(ListaDupla *l) {
    return !l || !l->inicio;
}

void destruir_lista(ListaDupla *l) {
    while (!esta_vazia(l))
        remover_item(l, l->inicio->arquivo);
    free(l);
}

void inserir_inicio(ListaDupla *l, const char *a) {
    No *n = malloc(sizeof(No));
    n->arquivo = _strdup(a);
    n->anterior = NULL;
    n->proximo = l->inicio;
    if (l->inicio) l->inicio->anterior = n;
    else l->fim = n;
    l->inicio = n;
}

void inserir_fim(ListaDupla *l, const char *a) {
    if (!l->fim) inserir_inicio(l,a);
    else {
        No *n = malloc(sizeof(No));
        n->arquivo = _strdup(a);
        n->proximo = NULL;
        n->anterior = l->fim;
        l->fim->proximo = n;
        l->fim = n;
    }
}

int remover_item(ListaDupla *l, const char *a) {
    if(l->inicio == NULL) return 0;
    No *n = l->inicio;
    while (n) {
        if (!strcmp(n->arquivo,a)) {
            if (n->anterior) n->anterior->proximo = n->proximo;
            else l->inicio = n->proximo;
            if (n->proximo) n->proximo->anterior = n->anterior;
            else l->fim = n->anterior;
            free(n->arquivo);
            free(n);
            return 1;
        }
        n = n->proximo;
    }
    return 0;
}
