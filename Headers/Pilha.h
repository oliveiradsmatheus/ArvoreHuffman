struct pilha {
	Tree *elem;
	struct pilha *prox;
};
typedef struct pilha Pilha;

struct pilhastr {
	char elem[8];
	struct pilhastr *prox;
};
typedef struct pilhastr PilhaStr;

void init (Pilha **P) {
	*P = NULL;
}

void initS (PilhaStr **P) {
	*P = NULL;
}

void push (Pilha **P, Tree *no) {
	Pilha *Novo = (Pilha*)malloc(sizeof(Pilha));

	Novo->elem = no;
	Novo->prox = *P;
	*P = Novo;
}

void pushS (PilhaStr **P, char *elem) {
	PilhaStr *Novo = (PilhaStr*)malloc(sizeof(PilhaStr));

	strcpy(Novo->elem,elem);
	Novo->prox = *P;
	*P = Novo;
}

void pop (Pilha **P, Tree **no) {
	Pilha *del = *P;

	*no = (*P)->elem;
	*P = (*P)->prox;
	free(del);
}

void popS (PilhaStr **P, char *elem) {
	PilhaStr *del = *P;

	strcpy(elem,(*P)->elem);
	*P = (*P)->prox;
	free(del);
}

char isEmpty (Pilha *P) {
	return P == NULL;
}

char isEmptyS (PilhaStr *P) {
	return P == NULL;
}

void PreOrdem (Tree *raiz) {
	Pilha *P;

	init(&P);
	push(&P,raiz);
	while(!isEmpty(P)) {
		pop(&P,&raiz);
		if(EhFolha(raiz))
			printf("[%d]\t",raiz->freq);
		else {
			if(raiz->dir)
				push(&P,raiz->dir);
			if(raiz->esq)
				push(&P,raiz->esq);
		}
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
		printf("([%d]: %d)\n",raiz->num, raiz->freq);
		ExibeHorizontal(raiz->esq);
		n--;
	}
}

void CodificaPalavras (Lista *L, Tree *raiz) {
	Pilha *P;
	PilhaStr *PS;
	Lista *aux;
	char codigo[8] = "";

	init(&P);
	initS(&PS);
	push(&P,raiz);
	pushS(&PS,codigo);
	while(!isEmpty(P)) {
		pop(&P,&raiz);
		popS(&PS,codigo);
		if(EhFolha(raiz)) {
			aux = L;
			while(aux && aux->Tab.num != raiz->num)
				aux = aux->prox;
			strcpy(aux->Tab.codigo,codigo);
		} else {
			if(raiz->dir) {
				strcat(codigo,"1");
				push(&P,raiz->dir);
				pushS(&PS,codigo);
				codigo[strlen(codigo)-1] = '\0';
			}
			if(raiz->esq) {
				strcat(codigo,"0");
				push(&P,raiz->esq);
				pushS(&PS,codigo);
			}
		}
	}
}
