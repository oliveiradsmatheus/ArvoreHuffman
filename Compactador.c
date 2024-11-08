#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>
#include <windows.h>
#include "Headers\\Moldura.h"
#include "Headers\\Mensagem.h"
#include "Headers\\Huffman.h"
#include "Headers\\Pilha.h"

int main (void) {
	Floresta *F = NULL, *teste;
	Lista *L = NULL;

	char frase[500] = "amar e sonhar sonhar e viver viver e curtir curtir e amar cada um tera uma escolha cada um fara a escolha cada um escolhe a sua escolha levaremos um tempo para crescer levaremos um tempo para amadurecer levaremos um tempo para entender levaremos um tempo para envelhecer levaremos um tempo para morrer";
	printf("%s\n", frase);
	ProcuraPalavras(&L,frase);
	CriaFloresta(&F,L); // Cria uma Lista Ordenada pelas Frequências.
	ArvoreHuffman(&F);
	//PreOrdem(F->no);
	ExibeHorizontal(F->no);
	CodificaPalavras(L,F->no);
	ExibeLista(L); // Exibe a Lista de Palavras, número, código e suas Frequências.
	
	return 0;
}
