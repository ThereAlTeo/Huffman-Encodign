#define CLEAR system("cls")

/**
	Allo scopo di rendere piu' leggibile in codice, si scrive l'operazione una sola volta.
	Essa viene utilizzata varie volte e viene eseguita SOLAMENTE quando l'utente nel momento di una specifica
	scelta effettua un'operazione non prevista o indesiderata. E' seguita da una seconda scelta da parte dell'utente.
*/
void warning(char valore[]);

/**
	Funzione finale.
	Consente all'utente di leggere con piu' calma l'output.
*/
void endMethod();

/**
	Funzione eseguita quando si vogliono effettuare domande all'utente per comprendere quale comportamento deve avere il programma
*/
bool checkRequest(char valore[]);

/**

*/
char* returnWord(char valore[]);

/**

*/
int menuIniziale();
