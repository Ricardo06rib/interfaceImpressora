#include "lib.h"

ListaDupla *criar_lista()
{
    ListaDupla *l = (ListaDupla *)malloc(sizeof(ListaDupla));

    if (l == NULL)
    {
        printf("Erro de alocação");
        return NULL;
    }

    l->inicio = NULL;
    l->fim = NULL;

    return l;
}

void destruir_lista(ListaDupla *l)
{
    if (l == NULL || esta_vazia(l)) return;

    No *atual = l->fim;

    while (atual != NULL)
    {
        No *anterior = atual->anterior;
 
        free(atual->arquivo);
        free(atual);

        atual = anterior;
    }

    free(l);
}

void inserir_inicio(ListaDupla *l, char *arquivo)
{
    if (l == NULL)
    {
        printf("Lista não existe");
        return;
    }

    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL)
    {
        printf("Erro de alocação \n");
        return;
    }

    novo->arquivo = (char *)malloc(strlen(arquivo) + 1);
    strcpy(novo->arquivo, arquivo);
    novo->anterior = NULL;
    novo->proximo = l->inicio;

    if (l->inicio == NULL)
    {
        l->inicio = novo;
        l->fim = novo;
        return;
    }

    l->inicio->anterior = novo;
    l->inicio = novo;
}

void inserir_fim(ListaDupla *l, char *arquivo)
{
    if (l == NULL)
        return;

    if (l->fim == NULL)
    {
        inserir_inicio(l, arquivo);
        return;
    }
    No *novo = (No *)malloc(sizeof(No));

    if (novo == NULL)
    {
        printf("Erro de alocação \n");
        return;
    }

    novo->arquivo = arquivo;
    novo->proximo = NULL;
    novo->anterior = l->fim;

    l->fim->proximo = novo;
    l->fim = novo;
}
int remover_item(ListaDupla *l, char *arquivo)
{
    if (l == NULL || esta_vazia(l))
        return 0;

    No *novo = l->inicio;

    while (novo != NULL)
    {
        if (strcmp(novo->arquivo, arquivo) == 0)
        {
            if (novo->anterior != NULL)
            {
                novo->anterior->proximo = novo->proximo;
            }
            else
            {
                l->inicio = novo->proximo;
            }

            if (novo->proximo != NULL)
            {
                novo->proximo->anterior = novo->anterior;
            }
            else
            {
                l->fim = novo->anterior;
            }

            free(novo);
            return 1;
        }
        novo = novo->proximo;
    }
    return 0;
}

int esta_vazia(ListaDupla *l)
{
    return l->inicio == NULL;
}

void imprimir_frente(ListaDupla *l)
{
    if (l == NULL || esta_vazia(l))
    {
        printf("\nLista vazia ou não existe");
        return;
    }
    No *novo = l->inicio;
    while (novo != NULL)
    {
        printf("path: |%s|", novo->arquivo);
        novo = novo->proximo;
    }
}

void imprimir_tras(ListaDupla *l)
{
    if (l == NULL || esta_vazia(l))
    {
        printf("\nLista vazia ou não existe");
        return;
    }

    No *final = l->fim;
    printf("\n");
    while (final != NULL)
    {
        printf("path: |%s|\n", final->arquivo);
        final = final->anterior;
    }
}

//-----------------------------------------------------------------------

void imprimir(char *arquivo, char nomeImpressora)
{

    // invocando inicio de comando em terminal
    char cmd[600];
    // executando comando em terminal para usar impressora
    sprintf(cmd, "notepad /pt \"%s\" \"%s\"", arquivo, nomeImpressora);
    printf("\n");
    printf("%s", cmd);
    system(cmd);
}
