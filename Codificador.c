#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __linux__
#include <locale.h>
#include "Headers/conio_linux.h"
#include "Headers/Moldura.h"
#include "Headers/HuffmanCod.h"
#include "Headers/Pilha.h"
#else
#include <conio2.h>
#include <windows.h>
#include "Headers\\Moldura.h"
#include "Headers\\HuffmanCod.h"
#include "Headers\\Pilha.h"
#endif

void ExibeFrase(char *frase)
{
	int i, l = 3, c = 6, linhas = strlen(frase) / 40;

	Moldura(c, l, 94, l + linhas, 0, 7);
	FundoQuadro(c, l, 94, l + linhas, 7);
	Sombra(c, l, 94, l + linhas, 0);
	c += 2;
	l += 2;
	i = 0;
#ifdef __linux__
	while (i < strlen(frase))
	{
		gotoxy(l, c);
		printw("%c", frase[i]);
		i++;
		c++;
		if (c == 93)
		{
			c = 8;
			l++;
		}
	}
	refresh();
#else
	while (i < strlen(frase))
	{
		gotoxy(c, l);
		printf("%c", frase[i]);
		i++;
		c++;
		if (c == 93)
		{
			c = 8;
			l++;
		}
	}
#endif
	Titulo(1, 100, "FRASE:", 3);
}

void ExibeArvore(Tree *raiz)
{
	Dimensao("146", "28");
	Moldura(1, 1, 146, 28, 0, 11);
	FundoQuadro(1, 1, 146, 28, 11);
	Moldura(4, 3, 142, 14, 0, 7);
	FundoQuadro(4, 3, 142, 14, 7);
	Sombra(4, 3, 142, 14, 0);
	Titulo(1, 150, "ARVORE DE HUFFMAN:", 3);
	ExibeVertical(raiz, 2, 5);
}

void MsgFim(void)
{
	Dimensao("80", "30");
	Moldura(1, 1, 80, 30, 0, 11);
	FundoQuadro(1, 1, 80, 30, 11);

	ExibeTexto(80, 4, 0, 7, "TRABALHO BIMESTRAL - ESTRUTURAS DE DADOS II", "");
	ExibeTexto(80, 9, 0, 14, "CODIFICADOR DE STRINGS UTILIZANDO ARVORE DE HUFFMAN", "");
	ExibeTexto(80, 14, 0, 7, "102421080 - MATHEUS OLIVEIRA DA SILVA", "");
	ExibeTexto(80, 26, 0, 7, "PROF. DR. FRANCISCO ASSIS DA SILVA", "");
}

int main(void) // Compilar no Linux com gcc Codificador.c -o cod -lcurses
{
	Floresta *F = NULL, *teste;
	Lista *L = NULL;
	Byte B;
	char TxtCod[150] = "", texto[200] = "amar e morrer cada um fara a sua escolha e levaremos um tempo para entender", frase[500] = "amar e sonhar sonhar e viver viver e curtir curtir e amar cada um tera uma escolha cada um fara a escolha cada um escolhe a sua escolha levaremos um tempo para crescer levaremos um tempo para amadurecer levaremos um tempo para entender levaremos um tempo para envelhecer levaremos um tempo para morrer";

#ifdef __linux__
	setlocale(LC_ALL, "");
	initconio();
#endif
	RetiraCursor();		   // Retira o Cursor do Programa-
	Dimensao("100", "50"); // Dimensiona a Tela
	MolduraCod();
#ifdef _WIN32
	SetConsoleTitle("Codificador de Strings");
#endif

	ProcuraPalavras(&L, frase);
	CriaFloresta(&F, L); // Cria uma Lista Ordenada pelas Frequ�ncias.
	ArvoreHuffman(&F);
	CodificaPalavras(L, F->no);
	GravaTabela(L);
	CodificaTexto(texto, L, TxtCod);
	GravaCodigo(TxtCod);

	ExibeFrase(frase);
	ExibeTabela(L); // Exibe a Lista de Palavras, n�mero, c�digo e suas Frequ�ncias.
	getch();

	ExibeArvore(F->no);
	ExibeTexto(146, 18, 0, 7, texto, "TEXTO:");
	ExibeTexto(146, 24, 0, 7, TxtCod, "TEXTO CODIFICADO:");
	gotoxy(2, 2);
	getch();

	MsgFim();
	getch();
#ifdef __linux__
	endconio();
#endif
	return 0;
}
