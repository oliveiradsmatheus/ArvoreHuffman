struct bits
{
	unsigned char b7 : 1; // bit menos significativo
	unsigned char b6 : 1;
	unsigned char b5 : 1;
	unsigned char b4 : 1;
	unsigned char b3 : 1;
	unsigned char b2 : 1;
	unsigned char b1 : 1;
	unsigned char b0 : 1; // bit mais significativo
};

union byte
{
	struct bits bi;
	unsigned char num;
};
typedef union byte Byte;

struct tree
{
	int num;
	struct tree *esq, *dir;
};
typedef struct tree Tree;

struct tabela
{
	char palavra[30], codigo[8];
	int num, freq;
};
typedef struct tabela Tab;

char Folha(Tree *no)
{
	if (!no->esq && !no->dir)
		return 1;
	return 0;
}

Tree *CriaNo(int num)
{
	Tree *NC = (Tree *)malloc(sizeof(Tree));

	NC->dir = NC->esq = NULL;
	NC->num = num;

	return NC;
}

void CriaArvore(Tree **raiz)
{
	Tree *aux;
#ifdef __linux__
	FILE *arq = fopen("Data/tabela.dat", "rb");
#else
	FILE *arq = fopen("Data\\tabela.dat", "rb");
#endif
	Tab T;
	int i;

	if (!arq)
		ExibeTexto(100, 4, 0, 7, "ARQUIVO NAO ENCONTRADO", "ERRO:");
	else
	{
		*raiz = CriaNo(-1);
		fread(&T, sizeof(Tab), 1, arq);
		while (!feof(arq))
		{
			aux = *raiz;
			i = 0;
			while (i < strlen(T.codigo) - 1)
			{
				if (T.codigo[i] - '0' == 0)
					if (aux->esq)
						aux = aux->esq;
					else
					{
						aux->esq = CriaNo(-1);
						aux = aux->esq;
					}
				else if (aux->dir)
					aux = aux->dir;
				else
				{
					aux->dir = CriaNo(-1);
					aux = aux->dir;
				}
				i++;
			}
			if (T.codigo[i] - '0' == 0)
				aux->esq = CriaNo(T.num);
			else
				aux->dir = CriaNo(T.num);
			fread(&T, sizeof(Tab), 1, arq);
		}
		fclose(arq);
	}
}

void LeFrase(char *frase)
{
#ifdef __linux__
	FILE *arq = fopen("Data/frase.dat", "rb");
#else
	FILE *arq = fopen("Data\\frase.dat", "rb");
#endif
	Byte B;
	char Byte[8];
	int i = 0;

	if (!arq)
		ExibeTexto(100, 4, 0, 7, "ARQUIVO NAO ENCONTRADO", "ERRO:");
	else
	{
		fread(&B, sizeof(char), 1, arq);
		while (!feof(arq))
		{
			frase[i] = B.bi.b0 + '0';
			frase[i + 1] = B.bi.b1 + '0';
			frase[i + 2] = B.bi.b2 + '0';
			frase[i + 3] = B.bi.b3 + '0';
			frase[i + 4] = B.bi.b4 + '0';
			frase[i + 5] = B.bi.b5 + '0';
			frase[i + 6] = B.bi.b6 + '0';
			frase[i + 7] = B.bi.b7 + '0';
			i += 8;
			fread(&B, sizeof(char), 1, arq);
		}
		fclose(arq);
	}
}

void ExibeTabela(void)
{
#ifdef __linux__
	FILE *arq = fopen("Data/tabela.dat", "rb");
#else
	FILE *arq = fopen("Data\\tabela.dat", "rb");
#endif
	Tab Reg;
	int l = 18, c = 6;

	if (!arq)
		ExibeTexto(100, 4, 0, 7, "ARQUIVO NAO ENCONTRADO", "ERRO:");
	{

		Moldura(c, l, 104, l + 25, 0, 7);
		FundoQuadro(c, l, 104, l + 25, 7);
		Sombra(c, l, 104, l + 25, 0);
		ColunaMoldura(l, l + 25, 25, 0, 7);
		ColunaMoldura(l, l + 25, 60, 0, 7);
		ColunaMoldura(l, l + 25, 77, 0, 7);

		ExibeTexto(110, 14, 0, 7, "TABELA DE FREQUENCIA DAS PALAVRAS", "");

		Titulo(6, 25, "CODIGO:", 18);
		Titulo(25, 60, "PALAVRA:", 18);
		Titulo(60, 77, "FREQUENCIA:", 18);
		Titulo(77, 95, "NUMERO:", 18);

		c += 2;
		l += 2;

		fread(&Reg, sizeof(Tab), 1, arq);
#ifdef __linux__
		while (!feof(arq))
		{
			gotoxy(l, ((c + 25) / 2) - strlen(Reg.codigo) / 2);
			printw("%s", Reg.codigo);
			gotoxy(l, ((25 + 60) / 2) - strlen(Reg.palavra) / 2);
			printw("\" %s \"", Reg.palavra);
			gotoxy(l, (60 + 77) / 2);
			printw("%d", Reg.freq);
			gotoxy(l, (77 + 105) / 2);
			printw("%d", Reg.num);
			l++;
			fread(&Reg, sizeof(Tab), 1, arq);
		}
		refresh();
#else
		while (!feof(arq))
		{
			gotoxy(((c + 25) / 2) - strlen(Reg.codigo) / 2, l);
			printf("%s", Reg.codigo);
			gotoxy(((25 + 60) / 2) - strlen(Reg.palavra) / 2, l);
			printf("\" %s \"", Reg.palavra);
			gotoxy((60 + 77) / 2, l);
			printf("%d", Reg.freq);
			gotoxy((77 + 105) / 2, l);
			printf("%d", Reg.num);
			l++;
			fread(&Reg, sizeof(Tab), 1, arq);
		}
#endif
		fclose(arq);
	}

	ExibeTexto(110, 47, 0, 14, "PRESSIONE QUALQUER TECLA PARA CONTINUAR", "");
}

int BuscaPalavra(FILE *arq, int num)
{
	Tab Reg;

	rewind(arq);
	fread(&Reg, sizeof(Tab), 1, arq);
	while (!feof(arq) && Reg.num != num)
		fread(&Reg, sizeof(Tab), 1, arq);

	if (!feof(arq))
		return ftell(arq) - sizeof(Tab);
	return -1;
}

void DecodificaFrase(Tree *raiz, char *cod, char *frase)
{
#ifdef __linux__
	FILE *arq = fopen("Data/tabela.dat", "rb");
#else
	FILE *arq = fopen("Data\\tabela.dat", "rb");
#endif
	Tree *aux = raiz;
	Tab T;
	char palavra[30];
	int i = 0, pos;

	if (!arq)
		ExibeTexto(100, 4, 0, 7, "ARQUIVO NAO ENCONTRADO", "ERRO:");
	else
	{
		while (i < strlen(cod))
		{
			if (Folha(aux))
			{
				pos = BuscaPalavra(arq, aux->num);
				if (pos != -1)
				{
					fseek(arq, pos, 0);
					fread(&T, sizeof(Tab), 1, arq);
					strcat(frase, T.palavra);
					aux = raiz;
				}
			}
			else
			{
				if (cod[i] == '0')
					aux = aux->esq;
				else
					aux = aux->dir;
				i++;
			}
		}
		fclose(arq);
	}
}

void QtdeFilhos(Tree *raiz, int *cont)
{
	if (raiz)
	{
		if (raiz->esq)
		{
			(*cont)++;
			QtdeFilhos(raiz->esq, &*cont);
		}
		if (raiz->dir)
		{
			(*cont)++;
			QtdeFilhos(raiz->dir, &*cont);
		}
	}
}

void ExibeVertical(Tree *raiz, int c, int l)
{
	int filhos = 0, QtdeEsq = 0, QtdeDir = 0;

	if (raiz)
	{
		if (raiz->esq)
		{
			filhos = 1;
			QtdeFilhos(raiz->esq, &filhos);
		}
		c += filhos;

#ifdef __linux__
		gotoxy(l, c * 3);
		if (Folha(raiz))
		{
			textcolor(0);
			printw("(%d)", raiz->num);
		}
		else
		{
			textcolor(8);
			printw("(%d)", raiz->num);
		}
		refresh();
#else
		gotoxy(c * 3, l);
		if (Folha(raiz))
		{
			textcolor(0);
			printf("(%d)", raiz->num);
		}
		else
		{
			textcolor(8);
			printf("(%d)", raiz->num);
		}
#endif
		ExibeVertical(raiz->esq, c - filhos, l + 1);
		ExibeVertical(raiz->dir, c + 1, l + 1);
	}
}

void ExibeArvore(Tree *raiz)
{
	Dimensao("146","17");
	Moldura(1, 1, 146, 17, 0, 11);
	FundoQuadro(1, 1, 146, 17, 11);
	Moldura(4, 3, 142, 14, 0, 7);
	FundoQuadro(4, 3, 142, 14, 7);
	Sombra(4, 3, 142, 14, 0);
	Titulo(1, 150, "ARVORE DE HUFFMAN:", 3);
	ExibeVertical(raiz, 2, 5);
}
