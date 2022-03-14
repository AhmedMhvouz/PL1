#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
using namespace std;


/* Declare the struct of Books & global variables*/
struct books{
    unsigned int ID;
    char name[50];
    unsigned int quantity;
};
unsigned int nOfBooks;
FILE *fptr;


/*function's prototype*/
void handler();
int linesCounter();
void otherOperation();
void insBook(books book[]);
void delBook(books[]);
void recursiveID(books book[], unsigned int);
void BinarySearch(books book[]);
void sortByName(books book[]);
void displayBooksUnsorted(books book[]);


/*main function*/
int main()
{
    nOfBooks = linesCounter();
    struct books book[nOfBooks];

    /*put data in their variables*/
    fptr=fopen("library.txt","r");
    if (fptr != NULL)
    {
        unsigned int i=0;
        while(i<nOfBooks)
           {
               fscanf(fptr, "%d%d", &book[i].ID, &book[i].quantity);
               fgets(book[i].name, 50, fptr);
               unsigned int n = strlen(book[i].name);
               book[i].name[n-1] = '\0';
               i++;
           }
    }
    fclose(fptr);

/*See options*/
    printf("books are %d\n", nOfBooks);
    char userMenu;
    puts("Choices are:-\n");
    puts("1- Insert a book");
    puts("2- Delete a book");
    puts("3- Search a book by ID");
    puts("4- Search a book by name");
    puts("5- Display all books sorted by name");
    puts("6- Display all books unsorted");
    printf("\nEnter the number of your choice ");
    userMenu = getchar();
    getchar();
    switch(userMenu)
    {
        case '1':
            insBook(book);
            break;
        case '2':
            delBook(book);
            break;
        case '3':
            unsigned int searchID;
            printf("Enter ID to search the book ");
            scanf("%d", &searchID);
            getchar();
            if (nOfBooks < 1)
            {
                puts("There are no books to search");
            }
            else
                recursiveID(book, searchID);
            break;
        case '4':
            BinarySearch(book);
            break;
        case '5':
            sortByName(book);
            for (unsigned int i=0; i<nOfBooks; i++)
                printf("\n%d\t\t%d\t\t%s\n", book[i].ID, book[i].quantity, book[i].name);
            break;
        case '6':
            displayBooksUnsorted(book);
            break;
        default:
            puts("\nUnavailable number\a\n");
    }
    otherOperation();
    return 0;
}


/*Restart program*/
void handler()
{
    system("CLS");
    main();
}


/*count lines*/
int linesCounter()
{
    unsigned int lines =0; char c;
    fptr = fopen("library.txt", "r");
    if (fptr != NULL)
    {
        // Extract characters from file and store in character c
        for (c = getc(fptr); c != EOF; c = getc(fptr))
            if (c == '\n') // Increment count if this character is newline
                lines = lines + 1;
    }
    fclose(fptr);
    return lines;
}


/*fun. to Ask if to do another operation*/
void otherOperation()
{
    char newOperation;
    printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
    printf("\nDo another operation?\tY <yes> or N <no>\t");
    newOperation = getchar();
    if (newOperation == 'Y' || newOperation == 'y')
        {
            getchar();
            printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
            handler();
        }
    else
        {
            printf("Thanks, bye\n");
            printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
            exit(1);
        }
}


/*fun. to Insert a book*/
void insBook(books book[])
{
    fptr = fopen("library.txt", "a");
    if (fptr != NULL){
            unsigned int ID; char name[50]; unsigned int quantity;
            puts("\nInsert the book");
                    printf("ID: ");         scanf("%d", &ID);
                    getchar();
                    printf("Name: ");       gets(name);
                    printf("Quantity: ");   scanf("%d", &quantity);
                    getchar();
            unsigned int flag=0;
            for (unsigned int i=0; i<nOfBooks; i++)
            {
                if (ID == book[i].ID)
                    flag++;
            }
            if (flag == 0)
            {
                fprintf (fptr, "%d\t%d%s\n", ID, quantity, name);
                puts("saved\n");
            }
            else
                puts("ID can't be added, already exists.\n");
    	}
   	 fclose(fptr);
}


/*fun. to Delete a book*/
void delBook (books book[])
{
    unsigned int delID; // store ID to delete.
    unsigned int flag=0; // check if the ID doesn't exist.
    printf("\nEnter ID to delete the book ");
    scanf("%d", &delID);
    getchar();
    for (unsigned int i=0; delID != book[i].ID; i++)
        {
            if (i == nOfBooks) break;
            flag++;
        }
    if (flag == nOfBooks) //if doesn't exist
            puts("This ID doesn't exist");
    else //if exist
    {
         fptr = fopen("C:\\library.txt", "w");
        for (unsigned int i=0; i<nOfBooks; i++)
            {
                if (delID != book[i].ID)
                {
                    fprintf (fptr, "%d\t%d%s\n", book[i].ID, book[i].quantity, book[i].name);
                }
            }
            fclose(fptr);
            puts("The book was deleted and data saved");
    }
}


/*fun to recursiveIdSearch*/
void recursiveID(books book[], unsigned int key)
{
    unsigned int flag=0;

    for (unsigned int i=0; key != book[i].ID; i++)
        {
            flag++;
            if (i == nOfBooks) break;
        }
    if (flag > nOfBooks) //if doesn't exist
    {
        //puts("\nThis ID doesn't exist\n");
        puts("\nNot found\n");
        otherOperation();
    }
    if(key == book[nOfBooks].ID) { // Base case - found
        printf("\nName: %s\tID: %d\tQuantity: %d\n", book[nOfBooks].name, book[nOfBooks].ID, book[nOfBooks].quantity);
        otherOperation();

    }
    // Recursive case
    nOfBooks-=1;
    recursiveID(book, key);
}


/*BinarySearch*/
void BinarySearch(books book[])
{
    sortByName(book); //sort books by name to use binary search

    unsigned int low = 0;
    unsigned int high = nOfBooks;
    unsigned int middle;
    char name[50];
    printf("Enter the book's name to search ");
    gets(name);
    while( low <= high )
    {
        middle = (low + high) / 2;
        if( strcmp(book[middle].name, name) == 0)
        {
            printf("\nName: %s\tID: %d\tQuantity: %d\n", book[middle].name, book[middle].ID, book[middle].quantity);
            otherOperation();
        }
        else if ( name[0] < book[middle].name[0] )
        {
            high = middle - 1;
        }
        else if ( name[0] > book[middle].name[0] )
        {
            low = middle + 1;
        }
    }//end while
    puts("Name not found");
    otherOperation();
}


/*Sort books By Name*/
void sortByName(books book[])
{
    unsigned int IdTemp=0, QuantityTemp=0; char NameTemp[50];
    for (unsigned int i=0; i<nOfBooks; i++)
        {
            if (strcmp(book[i].name, book[i+1].name) == 1)
            {
                IdTemp = book[i].ID;                book[i].ID = book[i+1].ID;              book[i+1].ID = IdTemp;
                QuantityTemp = book[i].quantity;    book[i].quantity = book[i+1].quantity;  book[i+1].quantity = QuantityTemp;
                strcpy(NameTemp, book[i].name);     strcpy(book[i].name, book[i+1].name);   strcpy(book[i+1].name, NameTemp);
            }
        }
}


/*Display books as entered without sorting*/
void displayBooksUnsorted(books book[])
{
    puts("Available books are:-\n");
    puts("ID\t\tQuantity\tName\n------\t\t--------  \t-----");
    for (unsigned int i=0; i<nOfBooks; i++)
        {
            printf("%d\t\t%d\t\t%s\n", book[i].ID, book[i].quantity, book[i].name);
            if (i == nOfBooks)
                printf("\n");
        }
}
