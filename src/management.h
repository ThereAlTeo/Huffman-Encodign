#define CLEAR system("cls")
#define PRNT_NOT_ERROR warning("\n\nOPERAZIONE ESEGUITA CON SUCCESSO ")
#define PRNT_ERROR warning("\n\nOPERAZIONE NON ESEGUITA CON SUCCESSO ")
#define FREE_BUFFER while(getchar() != '\n')

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
	Funzione eseguita quando si vogliono effettuare domande all'utente per 
	comprendere quale comportamento deve avere il programma
*/
bool checkRequest(char valore[]);

/**
Input:
-valore: stringa di caratteri contenete una richiesta.
Output:
-stringa di caratteri contenente la risposta.
*/
char* returnWord(char valore[]);

/**
	Funzione.
	Viene visualizzato un menu' dal quale e' possibile selezionare l'azione da dover svolgere.
*/
int menuIniziale();
