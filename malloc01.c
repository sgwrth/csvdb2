#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAMELEN 25
#define FILMLEN 25
#define RATINGLEN 6

enum Db {
	Open = 'o',
	New = 'n'
};

enum Option {
	AddNewEntry = '1',
	ShowAllEntries = '2',
	EditEntry = '3',
	SaveAndQuit = '0'
};

enum OpenFile {
	Undefined = 'u',
	TryAgain = 't',
	CreateNew = 'c',
	Quit = 'q'
};

enum InsertPos {
	AtFront = 'f',
	AtBack = 'b'
};

typedef struct FemcharStruct Femchar;
struct FemcharStruct {
	char name[NAMELEN];
	char film[FILMLEN];
	int rating;
	Femchar *next;
};

char decideOnDb();
char pickOption(Femchar **);
void executeOption(char, Femchar **);
void clearBuffer(FILE *);
int isSetName(Femchar *);
int isSetFilm(Femchar *);
int isSetRating(Femchar *);
void askIfEnterNewValue(char *, char *);
void setFemcharName(Femchar *);
void setFemcharFilm(Femchar *);
void setFemcharRating(Femchar *);
void setFemcharData(Femchar *);
char enterAnother();
void insertFemcharAtFront(Femchar **);
void insertFemcharAtBack(Femchar **);
void printFemcharsAll(Femchar *);
void printFemchar(Femchar *);
enum InsertPos getInsertPos();
int getNumOfInserts();
void insertFemchar(Femchar **);
char *enterSearchStringName();
Femchar* selectFemchar(Femchar *);
char *getFilename();
void writeFemcharToFile(Femchar *); 
void writeFemcharsAllToFile(Femchar *);
FILE *openFileOrNull();
int readFemcharsFromFile(Femchar **);
void writeFromCharsIntoValue(char[], char[], int *);
void editFemchar(Femchar **);

/* ===== MAIN =============================================================== */

int main()
{
	Femchar *anfang = NULL;
	enum Db openOrNewDb = decideOnDb();
	if (openOrNewDb == Open)
		readFemcharsFromFile(&anfang);
	char option;
	do {
		option = pickOption(&anfang);
		executeOption(option, &anfang);
	} while (option != SaveAndQuit );
	return 0;
}

/* ----- Functions ---------------------------------------------------------- */

char decideOnDb()
{
	char openOrNewDb;
	do {
		printf("open existing DB or create new? enter [o]pen or [n]new: ");
		scanf("%c", &openOrNewDb);
		clearBuffer(stdin);
	} while (openOrNewDb != Open && openOrNewDb != New);
	return openOrNewDb;
}

char pickOption(Femchar **anf)
{
	char option;
	do {
		printf("***\n");
		printf("MENU\n");
		printf("What do you want to do?\n");
		printf("[1] add new entry\n");
		if (*anf != NULL) {
			printf("[2] show all entries\n");
			printf("[3] edit entry\n");
			printf("[0] save and quit\n");
		} else
			printf("[0] quit\n");
		printf("please enter: ");
		scanf("%c", &option);
		clearBuffer(stdin);
	} while (option != AddNewEntry
			&& option != ShowAllEntries
			&& option != EditEntry
			&& option != SaveAndQuit
	);
	return option;
}

void executeOption(char option, Femchar **anf)
{
	switch (option) {
		case AddNewEntry:
			insertFemchar(anf);
			break;
		case ShowAllEntries:
			printFemcharsAll(*anf);
			break;
		case EditEntry:
			editFemchar(anf);
			break;
		case SaveAndQuit:
			writeFemcharsAllToFile(*anf);
			break;
	}
}

void clearBuffer(FILE *fp) {
	int ch;
	while ((ch = fgetc(fp)) != EOF && ch != '\n')
		/* do nothing */ ;
}

int isSetName(Femchar *fem)
{
	int isSet = 0;
	if ((strncmp(fem->name, "[undefined]", sizeof("[undefined]")) != 0))
		isSet = 1;
	return isSet;
}

int isSetFilm(Femchar *fem)
{
	int isSet = 0;
	if ((strncmp(fem->film, "[undefined]", sizeof("[undefined]")) != 0))
		isSet = 1;
	return isSet;
}

int isSetRating(Femchar *fem)
{
	int isSet = 0;
	if (fem->rating != 0)
		isSet = 1;
	return isSet;
}

void askIfEnterNewValue(char *nameOfValue, char *editYesNo)
{
	do {
		printf("do you want to enter a new %s?  y / n: ", nameOfValue);
		scanf("%c", editYesNo);
		clearBuffer(stdin);
	} while (*editYesNo != 'y' && *editYesNo != 'n');
}

void setFemcharName(Femchar *fem)
{
	int isSet = isSetName(fem);
	if (isSet == 1) {
		printf("current name: %s\n", fem->name);
		char editYesNo;
		char *nameOfValue = malloc(sizeof("name"));
		strcpy(nameOfValue, "name");
		askIfEnterNewValue(nameOfValue, &editYesNo);
		free(nameOfValue);
		if (editYesNo == 'y') {
			printf("Bitte Name eingeben: ");
			fgets(fem->name, sizeof(fem->name), stdin);
			fem->name[strcspn(fem->name, "\n")] = 0;
		}
	} else {
		printf("Bitte Name eingeben: ");
		fgets(fem->name, sizeof(fem->name), stdin);
		fem->name[strcspn(fem->name, "\n")] = 0;
	}
}

void setFemcharFilm(Femchar *fem)
{
	int isSet = isSetFilm(fem);
	if (isSet == 1) {
		printf("current film: %s\n", fem->film);
		char editYesNo;
		char *nameOfValue = malloc(sizeof("film"));
		strcpy(nameOfValue, "film");
		askIfEnterNewValue(nameOfValue, &editYesNo);
		free(nameOfValue);
		if (editYesNo == 'y') {
			printf("Bitte Film eingeben: ");
			fgets(fem->film, sizeof(fem->film), stdin);
			fem->film[strcspn(fem->film, "\n")] = 0;
		}
	} else {
		printf("Bitte Film eingeben: ");
		fgets(fem->film, sizeof(fem->film), stdin);
		fem->film[strcspn(fem->film, "\n")] = 0;
	}
}

void setFemcharRating(Femchar *fem)
{
	int isSet = isSetRating(fem);
	if (isSet == 1) {
		printf("current rating: %d\n", fem->rating);
		char editYesNo;
		do {
			printf("do you want to enter a new rating?  y / n: ");
			scanf("%c", &editYesNo);
			clearBuffer(stdin);
		} while (editYesNo != 'y' && editYesNo != 'n');
		if (editYesNo == 'y') {
			int rating;
			printf("Bitte Rating eingeben: ");
			scanf("%d", &rating);
			clearBuffer(stdin);
			fem->rating = rating;
		}
	} else {
		int rating;
		printf("Bitte Rating eingeben: ");
		scanf("%d", &rating);
		clearBuffer(stdin);
		fem->rating = rating;
	}
}

void setFemcharData(Femchar *fem)
{
	setFemcharName(fem);
	setFemcharFilm(fem);
	setFemcharRating(fem);
}

void insertFemcharAtFront(Femchar **anf)
{
	Femchar *temp = malloc(sizeof(Femchar));
	setFemcharData(temp);
	temp->next = *anf;
	*anf = temp;
}

void insertFemcharAtBack(Femchar **anf)
{
	Femchar *new = malloc(sizeof(Femchar));
	strncpy(new->name, "[undefined]", NAMELEN);
	strncpy(new->film, "[undefined]", FILMLEN);
	new->rating = 0;
	Femchar *helper;
	helper = *anf;
	/* noch kein Eintrag vorhanden (*anf == NULL) */
	if (*anf == NULL)
		*anf = new;
	/* schon min. ein Eintrag vorhanden */
	else {
		while (helper->next != NULL)
			helper = helper->next;
		helper->next = new;
	}
	setFemcharData(new);
	new->next = NULL;
}

void printFemcharsAll(Femchar *fem)
{
	if (fem != NULL) {
		printf("NAME                     |FILM                     |RATING\n");
		printf("-------------------------|-------------------------|------\n");
		do {
			printf("%-25s|", fem->name);
			printf("%-25s|", fem->film);
			printf("%6d\n", fem->rating);
			fem = fem->next;
		}
		while (fem != NULL);
		printf("\n");
	}
}

void printFemchar(Femchar *fem)
{
	printf("NAME                     |FILM                     |RATING\n");
	printf("-------------------------|-------------------------|------\n");
	printf("%-25s|", fem->name);
	printf("%-25s|", fem->film);
	printf("%6d\n", fem->rating);
	printf("\n");
}

enum InsertPos getInsertPos()
{
	char pos;
	do {
		printf("Insert at [f]ront or [b]ack?  Please enter f or b: ");
		scanf("%c", &pos);
		clearBuffer(stdin);
	} while (pos != 'f' && pos != 'b');
	if (pos == 'f')
		return AtFront;
	return AtBack;
}

char enterAnother()
{
	char enterAnother;
	do {
		printf("do you want to add another character? [y] or [n]: ");
		scanf("%c", &enterAnother);
		clearBuffer(stdin);
	} while (enterAnother != 'y' && enterAnother != 'n');
	return enterAnother;
}

void insertFemchar(Femchar **fem)
{
	enum InsertPos pos = getInsertPos();
	char enterAnotherEntry = 'u';
	if (pos == AtFront ) {
		do {
			printf("### Enter Character\n");
			insertFemcharAtFront(fem);
			enterAnotherEntry = enterAnother();
		} while (enterAnotherEntry != 'n');
	} else {
		do {
			printf("### Enter Character\n");
			insertFemcharAtBack(fem);
			enterAnotherEntry = enterAnother();
		} while (enterAnotherEntry != 'n');
	}
}

char *enterSearchStringName()
{
	char *searchString = malloc(NAMELEN);
	printf("Enter search name: ");
	fgets(searchString, NAMELEN, stdin);
	
	// delete '\n' am Stringende:
	char *tempString = malloc(NAMELEN);
	// garbage values im tempString entfernen:
	memset(tempString, 0, NAMELEN);
	strncpy(tempString, searchString, strlen(searchString) - 1);

	free(searchString);
	return tempString;
}

Femchar* selectFemchar(Femchar *fem)
{
	Femchar *selector = fem;
	char *searchName = enterSearchStringName();
	while (strcmp(selector->name, searchName) != 0) {
		if (selector->next == NULL) {
			return NULL;
		}
		selector = selector->next;
	}
	return selector;
}

char *getFilename()
{
	char *filename = malloc(12);
	printf("enter filename (max. 12 characters): ");
	scanf("%s", filename);
	clearBuffer(stdin);
	return filename;
}

void writeFemcharToFile(Femchar *fem)
{
	Femchar *selected = selectFemchar(fem);
	if (selected != NULL) {
		FILE *fp = fopen(getFilename(), "a");
		fprintf(fp, "\"%s\"", selected->name);
		fprintf(fp, ",");
		fprintf(fp, "\"%s\"", selected->film);
		fprintf(fp, ",");
		fprintf(fp, "%d", selected->rating);
		fprintf(fp, "\n");
		fclose(fp);
	} else
		printf("no matching femchar found.\n");
}

void writeFemcharsAllToFile(Femchar *fem)
{
	Femchar *selected = fem;
	if (selected != NULL) {
		FILE *fp = fopen(getFilename(), "w");
		do {
			fprintf(fp, "\"%s\"", selected->name);
			fprintf(fp, ",");
			fprintf(fp, "\"%s\"", selected->film);
			fprintf(fp, ",");
			fprintf(fp, "\"%d\"", selected->rating);
			fprintf(fp, "\n");
			selected = selected->next;
		} while (selected != NULL); 
	fclose(fp);
	}
}

FILE *openFileOrNull()
{	
	FILE *fp = fopen(getFilename(), "r");
	while (fp == NULL) {
		printf("error: file not found\n");
		char tryAgainOrQuit = Undefined;
		while (tryAgainOrQuit != TryAgain
				&& tryAgainOrQuit != CreateNew 
				&& tryAgainOrQuit != Quit) {
			printf("[t]ry again\n"),
			printf("[c]reate a new db\n");
			printf("[q]uit the program?\n");
			printf("enter: ");
			scanf("%c", &tryAgainOrQuit);
			clearBuffer(stdin);
		}
		if (tryAgainOrQuit == CreateNew)
			return NULL;
		else if (tryAgainOrQuit == Quit)
			exit(0);
		fp = fopen(getFilename(), "r");
	}
	return fp;
}

int readFemcharsFromFile(Femchar **anf)
{
	FILE *fp = openFileOrNull();
	if (fp == NULL)
		return 0;
	char ch;
	char arrayFromChars[BUFSIZ];
	int i = 0;
	while ((ch = fgetc(fp)) != EOF) {
		arrayFromChars[i] = ch;
		i++;
	}
	printf("%s", arrayFromChars);

	int m = 0;
	do {
		char arrayFromCharsToLine[BUFSIZ];
		memset(arrayFromCharsToLine, 0, BUFSIZ);
		int n = 0;
		while ((ch = arrayFromChars[m]) && ch != '\n') {
			arrayFromCharsToLine[n] = ch;
			m++;
			n++;
		}
		m++;	/* am Zeilenende: auf naechste Zeile wechseln */
		int j = 0;	/* start pos of arrayFromCharsToLine to read from */

		char name[NAMELEN];
		writeFromCharsIntoValue(arrayFromCharsToLine, name, &j);
		char film[NAMELEN];
		writeFromCharsIntoValue(arrayFromCharsToLine, film, &j);
		char rating[RATINGLEN];
		writeFromCharsIntoValue(arrayFromCharsToLine, rating, &j);

		Femchar *newNode = malloc(sizeof(Femchar));
		strncpy(newNode->name, name, NAMELEN);
		strncpy(newNode->film, film, FILMLEN);
		int temp = atoi(rating);
		newNode->rating = temp;

		memset(name, 0, NAMELEN);
		memset(film, 0, FILMLEN);
		memset(rating, 0, RATINGLEN);

		newNode->next = *anf;
		*anf = newNode;
	} while (arrayFromChars[m] != '\0');
	fclose(fp);
	return 0;
}

void writeFromCharsIntoValue(char chars[], char value[], int *j)
{
	int k = 0;
	while (chars[*j] != ',' && chars[*j] != '\0') {
		if (chars[*j] != '"') {
			value[k] = chars[*j];
			k++;
		}
		*j += 1;
	}
	*j += 1;	/* pos for next value to be read from arrayFromChars */
}

void editFemchar(Femchar **fem)
{
	Femchar *editThis = selectFemchar(*fem);
	if (editThis != NULL)
		setFemcharData(editThis);
	else
		printf("no matching femchar found.\n");
}
