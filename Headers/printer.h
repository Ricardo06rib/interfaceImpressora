#pragma once

#include "lista.h"

void imprimir_arquivo(const char *arquivo, const char *impressora);

void imprimir_txt_gdi(const char *arquivo, const char *impressora);
void imprimir_txt_raw(const char *arquivo, const char *impressora);
void imprimir_bmp_gdi(const char *arquivo, const char *impressora);

void impressoraFrentePTras(ListaDupla *l, const char *nomeImpressora);
void impressoraTrasPFrente(ListaDupla *l, const char *nomeImpressora);

//---------------------------
char* imprimir_frente(ListaDupla *l);
