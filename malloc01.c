#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAMELEN 25
#define FILMLEN 25
#define RATINGLEN 6

typedef struct FemcharStruct Femchar;
struct FemcharStruct {
	char name[NAMELEN];
	char film[FILMLEN];
	int rating;
	Femchar *next;
};

void clearBuffer(FILE *);
void setFemcharName(Femchar *);
void setFemcharFilm(Femchar *);
void setFemcharRating(Femchar *);
void setFemcharData(Femchar *);
void insertFemcharAtFront(Femchar **);
void insertFemcharAtBack(Femchar **);
void printFemcharsAll(Femchar *);
void printFemchar(Femchar *);
char getInsertPos();
int getNumOfInserts();
void insertFemchar(Femchar **);
char *enterSearchStringName();
Femchar* selectFemchar(Femchar *);
char *getFilename();
void writeFemcharToFile(Femchar *); 
void writeFemcharsAllToFile(Femchar *);
void readFemcharsFromFile(Femchar **);
void writeFromCharsIntoValue(char[], char[], int *);

/* ===== MAIN =============================================================== */

void main()
{
	Femchar *anfang = NULL;
	//insertFemchar(&anfang);
	//printFemcharsAll(anfang);
	/* printFemchar(selectFemchar(anfang)); */
	/* selectFemchar(anfang); */

	/*
	FILE *fp;
	fp = fopen(getFilename(),"w+");
	int number = 9;
	fprintf(fp, "Hallo, hier fprintf.  %d\n", number);
	fputs("...und hier fputs.\n", fp);
	fclose(fp);
	*/
	
	//writeFemcharToFile(anfang);
	//writeFemcharsAllToFile(anfang);
	readFemcharsFromFile(&anfang);
	printFemcharsAll(anfang);
}


/* ----- Functions ---------------------------------------------------------- */

void clearBuffer(FILE *fp) {
	int ch;
	while ((ch = fgetc(fp)) != EOF && ch != '\n')
		/* do nothing */ ;
}

void setFemcharName(Femchar *fem)
{
	printf("Bitte Name eingeben: ");
	fgets(fem->name, sizeof(fem->name), stdin);
	fem->name[strcspn(fem->name, "\n")] = 0;
}

void setFemcharFilm(Femchar *fem)
{
	printf("Bitte Film eingeben: ");
	fgets(fem->film, sizeof(fem->name), stdin);
	fem->film[strcspn(fem->film, "\n")] = 0;
}

void setFemcharRating(Femchar *fem)
{
	int rating;
	printf("Bitte Rating eingeben: ");
	scanf("%d", &rating);
	clearBuffer(stdin);
	fem->rating = rating;
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

char getInsertPos()
{
	char pos;
	do {
		printf("Insert at [f]ront or [b]ack?  Please enter f or b: ");
		scanf("%c", &pos);
		clearBuffer(stdin);
	} while (pos != 'f' && pos != 'b');
	return pos;
}

int getNumOfInserts()
{
	int num;
	printf("How many entries?  Please enter: ");
	scanf("%d", &num);
	clearBuffer(stdin);
	return num;
}

void insertFemchar(Femchar **fem)
{
	char pos = getInsertPos();
	int num = getNumOfInserts();
	if (pos == 'f') {
		for (int i = 0; i < num; i++) {
			printf("### Enter Character [%d of %d] ###\n", i+1, num);
			insertFemcharAtFront(fem);
		}
	} else {
		for (int i = 0; i < num; i++) {
			printf("### Enter Character [%d of %d] ###\n", i+1, num);
			insertFemcharAtBack(fem);
		}
	}
}

char *enterSearchStringName()
{
	char *searchString = malloc(NAMELEN);
	printf("Enter search name: ");
	scanf("%s", searchString);
	clearBuffer(stdin);
	return searchString;
}

Femchar* selectFemchar(Femchar *fem)
{
	Femchar *selector = fem;
	char *searchName = enterSearchStringName();
	while (strcmp(selector->name, searchName) != 0)
		selector = selector->next;
	return selector;
}

char *getFilename()
{
	char *filename = malloc(12);
	//char filename[12];
	printf("enter filename (max. 12 characters): ");
	scanf("%s", filename);
	return filename;
}

void writeFemcharToFile(Femchar *fem)
{
	Femchar *selected = selectFemchar(fem);
	FILE *fp = fopen(getFilename(), "a");
	fprintf(fp, "\"%s\"", selected->name);
	fprintf(fp, ",");
	fprintf(fp, "\"%s\"", selected->film);
	fprintf(fp, ",");
	fprintf(fp, "%d", selected->rating);
	fprintf(fp, "\n");
	fclose(fp);
}

void writeFemcharsAllToFile(Femchar *fem)
{
	Femchar *selected = fem;
	if (selected != NULL) {
		FILE *fp = fopen(getFilename(), "a");
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

void readFemcharsFromFile(Femchar **anf)
{
	FILE *fp = fopen(getFilename(), "r");
	char ch;

	// start: reading line from csv

	char arrayFromChars[BUFSIZ];
	int i = 0;
	while ((ch = fgetc(fp)) != EOF && ch != '\n') {
		arrayFromChars[i] = ch;
		i++;
	}
	printf("arrayFromChars: %s\n", arrayFromChars);

	int j = 0;	/* starting pos of arrayFromChars to read from */

	char name[NAMELEN];
	writeFromCharsIntoValue(arrayFromChars, name, &j);
	printf("name: %s\n", name);

	char film[NAMELEN];
	writeFromCharsIntoValue(arrayFromChars, film, &j);
	printf("film: %s\n", film);

	char rating[RATINGLEN];
	writeFromCharsIntoValue(arrayFromChars, rating, &j);
	printf("rating: %s\n", rating);

	Femchar *newNode = malloc(sizeof(Femchar));
	strncpy(newNode->name, name, NAMELEN);
	strncpy(newNode->film, film, FILMLEN);
	newNode->rating = (int) *rating;

	*anf = newNode;
	newNode->next = NULL;

	// end: reading line from csv

	fclose(fp);
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
	*j += 1;	/* set pos for next value to be read from arrayFromChars */
}

void editFemchar(Femchar **fem)
{
}
