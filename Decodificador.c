#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __linux__
#include <locale.h>
#include "Headers/conio_linux.h"
#include "Headers/Moldura.h"
#include "Headers/HuffmanDecod.h"
#else
#include <conio2.h>
#include <windows.h>
#include "Headers\\Moldura.h"
#include "Headers\\HuffmanDecod.h"
#endif

void MsgFim(void)
{
	Dimensao("80", "30");
	Moldura(1, 1, 80, 30, 0, 11);
	FundoQuadro(1, 1, 80, 30, 11);

	ExibeTexto(80, 4, 0, 7, "TRABALHO BIMESTRAL - ESTRUTURAS DE DADOS II", "");
	ExibeTexto(80, 9, 0, 14, "DECODIFICADOR DE STRINGS UTILIZANDO ARVORE DE HUFFMAN", "");
	ExibeTexto(80, 14, 0, 7, "102421080 - MATHEUS OLIVEIRA DA SILVA", "");
	ExibeTexto(80, 26, 0, 7, "PROF. DR. FRANCISCO ASSIS DA SILVA", "");
}

int main(void) // Compilar no Linux com gcc Decodificador.c -o decod -lcurses
{
	Tree *T = NULL;
	char TxtCod[150] = "", frase[150] = "";

#ifdef __linux__
	setlocale(LC_ALL, "");
	initconio();
#endif
	RetiraCursor();
	Dimensao("110", "50");
	MolduraDecod();
#ifdef _WIN32
	SetConsoleTitle("Decodificador de Strings");
#endif

	LeFrase(TxtCod);
	CriaArvore(&T);
	DecodificaFrase(T, TxtCod, frase);

	ExibeTabela();
	ExibeTexto(110, 4, 0, 7, TxtCod, "FRASE");
	ExibeTexto(110, 9, 0, 14, frase, "FRASE DECODIFICADA");
	getch();

	ExibeArvore(T);
	getch();

	MsgFim();
	getch();
#ifdef __linux__
	endconio();
#endif
}
