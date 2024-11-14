struct bits {
	unsigned char b7:1; // bit menos significativo
	unsigned char b6:1;
	unsigned char b5:1;
	unsigned char b4:1;
	unsigned char b3:1;
	unsigned char b2:1;
	unsigned char b1:1;
	unsigned char b0:1; // bit mais significativo
};

union byte {
	struct bits bi;
	unsigned char num;
};
typedef union byte Byte;

struct tree {
	int freq;
	char num;
	struct tree *esq, *dir;
};
typedef struct tree Tree;

struct floresta {
	Tree *no;
	struct floresta *prox;
};
typedef struct floresta Floresta;

struct tabela {
	char palavra[30], codigo[8];
	int num, freq;
};
typedef struct tabela Tab;

struct lista {
	Tab Tab;
	struct lista *prox;
};
typedef struct lista Lista;

Lista *NovaCaixa (Tab T) {
	Lista *NC = (Lista*)malloc(sizeof(Lista));

	strcpy(NC->Tab.palavra,T.palavra);
	strcpy(NC->Tab.codigo,T.codigo);
	NC->Tab.num = T.num;
	NC->Tab.freq = T.freq;
	NC->prox = NULL;

	return NC;
}

char Folha (Tree *no) {
	if(!no->esq && !no->dir)
		return 1;
	return 0;
}

int QtdeEsquerda (Tree *raiz) {
	int cont = 0;

	if(raiz)
		while(raiz->esq) {
			raiz = raiz->esq;
			cont++;
		}

	return cont;
}

int QtdeDireita (Tree *raiz) {
	int cont = 0;

	if(raiz)
		while(raiz->dir) {
			raiz = raiz->dir;
			cont++;
		}

	return cont;
}

void QtdeFilhos (Tree *raiz, int *cont) {
	if(raiz) {
		if(raiz->esq) {
			(*cont)++;
			QtdeFilhos(raiz->esq,&*cont);
		}
		if(raiz->dir) {
			(*cont)++;
			QtdeFilhos(raiz->dir,&*cont);
		}
	}
}

void ExibeVertical (Tree *raiz, int c, int l) {
	int i, filhos = 0, QtdeEsq = 0, QtdeDir = 0;

	if(raiz) {
		if(raiz->esq) {
			filhos = 1;
			QtdeFilhos(raiz->esq,&filhos);
		}
		c+=filhos;

		gotoxy(c*3,l);
		printf("(%d)\n",raiz->freq,c);
		ExibeVertical(raiz->esq,c-filhos,l+1);
		ExibeVertical(raiz->dir,c+1,l+1);
	}
}

void ExibeHorizontal (Tree *raiz) {
	int i;
	static int n=-1;

	if(raiz) {
		n++;
		ExibeHorizontal(raiz->dir);
		for(i=0; i<5*n; i++)
			printf(" ");
		printf("(%d)\n", raiz->freq);
		ExibeHorizontal(raiz->esq);
		n--;
	}
}

void ExibeLista (Lista *L) {
	while(L) {
		printf("<%s - [%d] - %d - %s>\n", L->Tab.codigo, L->Tab.num, L->Tab.freq, L->Tab.palavra);
		L = L->prox;
	}
}

char BuscaRecorrencia (Lista *L, char *palavra) {
	while(L && strcmp(L->Tab.palavra,palavra))
		L = L->prox;
	if(L)
		return 1;
	return 0;
}

void SomaFreq (Lista *L, char *palavra) {
	while(L && strcmp(L->Tab.palavra,palavra))
		L = L->prox;
	L->Tab.freq++;
}

void InsereLista (Lista **L, Tab T) {
	Lista *Nova, *aux;

	if(!*L) {
		Nova = NovaCaixa(T);
		*L = Nova;
	} else {
		aux = *L;
		while(aux->prox && strcmp(aux->Tab.palavra,T.palavra))
			aux = aux->prox;
		Nova = NovaCaixa(T);
		aux->prox = Nova;
	}
}

Tree *CriaNoTab (Tab T) {
	Tree *NC = (Tree*)malloc(sizeof(Tree));

	NC->dir = NC->esq = NULL;
	NC->num = T.num;
	NC->freq = T.freq;

	return NC;
}

Tree *CopiaNo (Tree *T) {
	Tree *NC = (Tree*)malloc(sizeof(Tree));

	NC->dir = T->dir;
	NC->esq = T->esq;
	NC->num = T->num;
	NC->freq = T->freq;

	return NC;
}

Floresta *NovaArvore (Tree *T) {
	Floresta *NC = (Floresta*)malloc(sizeof(Floresta));

	NC->no = T;
	NC->prox = NULL;

	return NC;
}

void InsereFloresta (Floresta **F, Tree *T) {
	Floresta *aux, *Novo = NovaArvore(T);

	if(!*F)
		*F = Novo;
	else {
		if(Novo->no->freq <= (*F)->no->freq) {
			Novo->prox = *F;
			*F = Novo;
		} else {
			aux = *F;
			while(aux->prox && Novo->no->freq > aux->prox->no->freq)
				aux = aux->prox;
			Novo->prox = aux->prox;
			aux->prox = Novo;
		}
	}
}

void CriaFloresta (Floresta **F, Lista *L) {
	Tree *Novo;
	while(L) {
		Novo = CriaNoTab(L->Tab);
		InsereFloresta(&*F,Novo);
		L = L->prox;
	}
}

void ArvoreHuffman (Floresta **F) {
	Tree *Novo;
	Floresta *pri, *seg;

	while((*F)->prox) {
		Novo = (Tree*)malloc(sizeof(Tree));
		pri = *F;
		seg = (*F)->prox;
		Novo->esq = pri->no;
		Novo->dir = seg->no;
		Novo->num = -1;
		Novo->freq = pri->no->freq + seg->no->freq;
		*F = (*F)->prox->prox;
		free(pri);
		free(seg);
		InsereFloresta(&*F,Novo);
	}
}

void GravaTabela (Lista *L) {
	FILE *Arq = fopen("Data\\tabela.dat","wb");
	Tab R;
	while(L) {
		R = L->Tab;
		fwrite(&R,sizeof(Tab),1,Arq);
		L = L->prox;
	}
	fclose(Arq);
}

void BuscaCodigo (char *palavra, Lista *L, char *codigo) {
	while(L && strcmp(palavra,L->Tab.palavra))
		L = L->prox;
	if(L)
		strcpy(codigo,L->Tab.codigo);
}

void CorrigeTamanho (char *codigo) {
	int resto = strlen(codigo) % 8, qtde = 0;

	if(resto)
		qtde = 8-resto;
	while(qtde--)
		strcat(codigo,"0");
}

void LeFrase (char *frase) {
	FILE *arq = fopen("Data\\frase.dat","rb");
	Byte B;
	char Byte[8];
	int i=0;


	if(!arq)
		ExibeTexto(100,4,0,7,"ARQUIVO NAO ENCONTRADO","ERRO:");
	else {
		fread(&B,sizeof(char),1,arq);
		while(!feof(arq)) {
			frase[i] = B.bi.b0 + '0';
			frase[i+1] = B.bi.b1 + '0';
			frase[i+2] = B.bi.b2 + '0';
			frase[i+3] = B.bi.b3 + '0';
			frase[i+4] = B.bi.b4 + '0';
			frase[i+5] = B.bi.b5 + '0';
			frase[i+6] = B.bi.b6 + '0';
			frase[i+7] = B.bi.b7 + '0';
			i+=8;
			fread(&B,sizeof(char),1,arq);
		}
		fclose(arq);
	}
}

void LeTabela (Lista **L) {
	FILE *arq = fopen("Data\\tabela.dat","rb");
	Tab T;
	if(!arq)
		ExibeTexto(100,8,0,7,"ARQUIVO NAO ENCONTRADO","ERRO:");
	else {
		fread(&T,sizeof(Tab),1,arq);
		while(!feof(arq)) {
			InsereLista(&*L,T);
			fread(&T,sizeof(Tab),1,arq);
		}
		fclose(arq);
	}
}

void ExibeTabela(Lista *L) {
	int l = 18, c = 6;

	Moldura(c,l,104,l+25,0,7);
	FundoQuadro(c,l,104,l+25,7);
	Sombra(c,l,104,l+25,0);
	ColunaMoldura(l,l+25,25,0,7);
	ColunaMoldura(l,l+25,60,0,7);
	ColunaMoldura(l,l+25,77,0,7);

	ExibeTexto(110,14,0,7,"TABELA DE FREQUENCIA DAS PALAVRAS","");

	Titulo(6,25,"CODIGO:",18);
	Titulo(25,60,"PALAVRA:",18);
	Titulo(60,77,"FREQUENCIA:",18);
	Titulo(77,95,"NUMERO:",18);

	c+=2;
	l+=2;
	while(L) {
		gotoxy(((c+25)/2)-strlen(L->Tab.codigo)/2,l);
		printf("%s",L->Tab.codigo);
		gotoxy(((25+60)/2)-strlen(L->Tab.palavra)/2,l);
		printf("%s",L->Tab.palavra);
		gotoxy((60+77)/2,l);
		printf("%d",L->Tab.freq);
		gotoxy((77+105)/2,l);
		printf("%d",L->Tab.num);
		l++;
		L = L->prox;
	}

	ExibeTexto(110,47,0,14,"PRESSIONE QUALQUER TECLA PARA CONTINUAR","");
}

void BuscaPalavra (Lista *L, int num, char *palavra) {
	while(L && L->Tab.num != num)
		L = L->prox;
	if(L)
		strcpy(palavra,L->Tab.palavra);
}

void DecodificaFrase (Tree *raiz,Lista *L, char *cod, char *frase) {
	Tree *aux = raiz;
	Lista *auxL;
	char palavra[30];
	int i=0;

	while (i<strlen(cod)) {
		if(Folha(aux)) {
			BuscaPalavra(L,aux->num,palavra);
			strcat(frase,palavra);
			aux = raiz;
		} else {
			if(cod[i] == '0')
				aux = aux->esq;
			else
				aux = aux->dir;
			i++;
		}
	}
}
