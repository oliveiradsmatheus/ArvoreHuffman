void Moldura(int CI, int LI, int CF, int LF, int CorT, int CorF)
{
	int i;

	textcolor(CorT);
	textbackground(CorF);
#ifdef __linux__
	gotoxy(LI, CI);
	printw("╔");
	gotoxy(LI, CF);
	printw("╗");
	gotoxy(LF, CI);
	printw("╚");
	gotoxy(LF, CF);
	printw("╝");
	for (i = CI + 1; i < CF; i++)
	{
		gotoxy(LI, i);
		printw("═");
		gotoxy(LF, i);
		printw("═");
	}
	for (i = LI + 1; i < LF; i++)
	{
		gotoxy(i, CI);
		printw("║");
		gotoxy(i, CF);
		printw("║");
	}
	refresh();
#else
	gotoxy(CI, LI);
	printf("%c", 201);
	gotoxy(CF, LI);
	printf("%c", 187);
	gotoxy(CI, LF);
	printf("%c", 200);
	gotoxy(CF, LF);
	printf("%c", 188);
	for (i = CI + 1; i < CF; i++)
	{
		gotoxy(i, LI);
		printf("%c", 205);
		gotoxy(i, LF);
		printf("%c", 205);
	}
	for (i = LI + 1; i < LF; i++)
	{
		gotoxy(CI, i);
		printf("%c", 186);
		gotoxy(CF, i);
		printf("%c", 186);
	}
#endif
	//textbackground(7);
	//textcolor(0);
}

void Fundo (int Cor) {
	int L=2;

	textbackground(Cor);
#ifdef __linux__
	while(L<50) {
		gotoxy(L,2);
		printw("                                                                                                                      ");
		L++;
	}
	refresh();
#else
	while(L<50) {
		gotoxy(2,L);
		printf("                                                                                                                      ");
		L++;
	}
#endif
}

void FundoQuadro(int CI, int LI, int CF, int LF, int Cor)
{
	int L = LI + 1, C = CI + 1;
	char linha[150] = "";

	while (CI < CF - 1)
	{
		strcat(linha, " ");
		CI++;
	}
	textbackground(Cor);
#ifdef __linux__
	while (L < LF)
	{
		gotoxy(L, C);
		printw("%s", linha);
		L++;
	}
	//refresh();
#else
	while (L < LF)
	{
		gotoxy(C, L);
		printf("%s", linha);
		L++;
	}
#endif
}

void Sombra(int CI, int LI, int CF, int LF, int CorF)
{
	int i;
	textbackground(CorF);
#ifdef __linux__
	for (i = LI; i < LF; i++)
	{
		gotoxy(i + 1, CF + 1);
		printw("  ");
	}
	for (i = CI; i < CF + 2; i++)
	{
		gotoxy(LF + 1, i + 1);
		printw(" ");
	}
	refresh();
#else
	for (i = LI; i < LF; i++)
	{
		gotoxy(CF + 1, i + 1);
		printf("  ");
	}
	for (i = CI; i < CF + 2; i++)
	{
		gotoxy(i + 1, LF + 1);
		printf(" ");
	}
#endif
	textbackground(7);
}

void Titulo(int CI, int CF, char *Titulo, int Linha)
{
	int pos = (CF + CI) / 2 - (strlen(Titulo) + 2) / 2;

	if (strlen(Titulo))
	{
		textbackground(0);
		textcolor(14);
#ifdef __linux__
		gotoxy(Linha, pos);
		printw(" %s ", Titulo);
		refresh();
#else
		gotoxy(pos, Linha);
		printf(" %s ", Titulo);
#endif
		textcolor(0);
		textbackground(7);
	}
}

void RetiraCursor(void)
{
#ifdef __linux__ // Para o devido funcionamento, importar a biblioteca curses.h
	curs_set(0);
#else
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
#endif
}

void LigaCursor(void)
{
#ifdef __linux__ // Para o devido funcionamento, importar a biblioteca curses.h
	curs_set(1);
#else
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = TRUE;
	SetConsoleCursorInfo(consoleHandle, &info);
#endif
}

void Dimensao(char *C, char *L)
{
	char linha[30];
#ifdef __linux__ // echo -ne '\e[8;25;80t']
	strcpy(linha, "printf '\e[8;");
	strcat(linha, L);
	strcat(linha, ";");
	strcat(linha, C);
	strcat(linha, "t'");
	system(linha);
	getch();
#else // "mode con cols=80 lines 25"
	strcpy(linha, "mode con cols=");
	strcat(linha, C);
	strcat(linha, " lines=");
	strcat(linha, L);
	system(linha);
#endif
}

void MolduraCompleta(void)
{
	FundoQuadro(1, 1, 80, 25, 3);
	Moldura(1, 1, 80, 25, 0, 3);
}

void LimpaLinha(int Num)
{
#ifdef __linux__
	gotoxy(Num, 2);
	printw("                                                                                                  ");
	refresh();
#else
	gotoxy(2, Num);
	printf("                                                                                                  ");
#endif
}

void LimpaTela(void)
{
	int i;

	for (i = 2; i < 48; i++)
		LimpaLinha(i);
}

void LinhaMoldura(int Linha, int CorF, int CorT)
{
	int i;
	textbackground(CorF);
	textbackground(CorT);
#ifdef __linux__
	gotoxy(Linha, 1);
	printw("%s", "╠");
	gotoxy(Linha, 100);
	printw("%s", "║");
	for (i = 2; i < 100; i++)
	{
		gotoxy(Linha, i);
		printw("%s", "═");
	}
	refresh();
#else
	gotoxy(1, Linha);
	printf("%c", 204);
	gotoxy(100, Linha);
	printf("%c", 185);
	for (i = 2; i < 100; i++)
	{
		gotoxy(i, Linha);
		printf("%c", 205);
	}
#endif
}

void ColunaMoldura(int LI, int LF, int Coluna, int CorF, int CorT)
{
	int i;

	textbackground(CorF);
	textbackground(CorT);
#ifdef __linux__
	gotoxy(LI, Coluna);
	printw("%s", "╦");
	gotoxy(LF, Coluna);
	printw("%s", "╩");
	for (i = LI + 1; i < LF; i++)
	{
		gotoxy(i, Coluna);
		printw("%s", "║");
	}
	refresh();
#else
	gotoxy(Coluna, LI);
	printf("%c", 203);
	gotoxy(Coluna, LF);
	printf("%c", 202);
	for (i = LI + 1; i < LF; i++)
	{
		gotoxy(Coluna, i);
		printf("%c", 186);
	}
#endif
}

void MolduraCod (void) {
	Fundo(11);
	Moldura(1,1,100,50,0,11);
}

void MolduraDecod (void) {
	Fundo(11);
	Moldura(1,1,110,50,0,11);
}

void ExibeTexto(int TamC, int Linha, int CorT, int CorF, char *texto, char *titulo)
{
	int CI = TamC / 2 - (strlen(texto) / 2 + 2), CF = TamC / 2 + (strlen(texto) / 2 + 2), LI = Linha - 1, LF = Linha + 1;

	Moldura(CI, LI, CF, LF, CorT, CorF);
	FundoQuadro(CI, LI, CF, LF, CorF);
	Sombra(CI, LI, CF, LF, 0);
	Titulo(CI, CF, titulo, LI);
	textcolor(CorT);
	textbackground(CorF);
#ifdef __linux__
	gotoxy(LI + 1, TamC / 2 - strlen(texto) / 2);
	printw("%s", texto);
	refresh();
#else
	gotoxy(TamC / 2 - strlen(texto) / 2, LI + 1);
	printf("%s", texto);
#endif
}
