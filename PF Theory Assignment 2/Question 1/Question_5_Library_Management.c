#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 5
#define MAX_TITLE 50
#define MAX_BORROWED 3

void displayMenu(void);
void registerMember(char name[], int *studentID, int *memberType);
void displayBooks(int bookIDs[], char bookTitles[][50],
                  int availableCopies[], int totalBooks);
void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[],
                int totalBooks, int borrowedBookIDs[], int *borrowedCount,
                int memberType);
float returnBook(int bookIDs[], int availableCopies[], int totalBooks,
                 int borrowedBookIDs[], int *borrowedCount, int memberType,
                 float *totalFine);
void displayMemberRecord(char name[], int studentID, int memberType,
                         int borrowedBookIDs[], int borrowedCount,
                         float totalFine, float fineAfterWaiver);

void displayMenu(void)
{
    printf("\n===== University Library Management System =====\n");
    printf("1. Register Member\n");
    printf("2. Display Available Books\n");
    printf("3. Borrow a Book\n");
    printf("4. Return a Book\n");
    printf("5. Display Member Record\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

void registerMember(char name[], int *studentID, int *memberType)
{
    int type;

    printf("Enter member name: ");
    scanf(" %49[^\n]", name);

    printf("Enter student ID: ");
    scanf("%d", studentID);

    do {
        printf("Membership type (1 = Student, 2 = Faculty): ");
        scanf("%d", &type);

        if (type != 1 && type != 2)
            printf("Invalid membership type. Please try again.\n");
    } while (type != 1 && type != 2);

    *memberType = type;
    printf("Member registered successfully.\n");
}

void displayBooks(int bookIDs[], char bookTitles[][50],
                  int availableCopies[], int totalBooks)
{
    int i;

    printf("\n%-10s %-30s %s\n", "Book ID", "Title", "Available Copies");
    printf("----------------------------------------------------------\n");

    for (i = 0; i < totalBooks; i++) {
        printf("%-10d %-30s %d\n",
               bookIDs[i], bookTitles[i], availableCopies[i]);
    }
}

void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[],
                int totalBooks, int borrowedBookIDs[], int *borrowedCount,
                int memberType)
{
    int id, i, found = -1;

    if (*borrowedCount >= MAX_BORROWED) {
        printf("You cannot borrow more than three books at a time.\n");
        return;
    }

    printf("Enter book ID to borrow: ");
    scanf("%d", &id);

    for (i = 0; i < totalBooks; i++) {
        if (bookIDs[i] == id) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Invalid book ID.\n");
        return;
    }

    if (availableCopies[found] <= 0) {
        printf("No copies of this book are currently available.\n");
        return;
    }

    borrowedBookIDs[*borrowedCount] = id;
    (*borrowedCount)++;
    availableCopies[found]--;

    printf("Book \"%s\" borrowed successfully.\n", bookTitles[found]);
    printf("Permitted borrowing period: %d days.\n",
           memberType == 1 ? 14 : 30);
}

float returnBook(int bookIDs[], int availableCopies[], int totalBooks,
                 int borrowedBookIDs[], int *borrowedCount, int memberType,
                 float *totalFine)
{
    int id, daysKept, i, j, foundBook = -1, foundBorrowed = -1;
    int allowedDays = (memberType == 1) ? 14 : 30;
    float fine = 0.0f, fineBeforeWaiver = 0.0f;
    char code[20];

    printf("Enter book ID to return: ");
    scanf("%d", &id);

    for (i = 0; i < *borrowedCount; i++) {
        if (borrowedBookIDs[i] == id) {
            foundBorrowed = i;
            break;
        }
    }

    if (foundBorrowed == -1) {
        printf("You have not borrowed this book.\n");
        return 0.0f;
    }

    for (i = 0; i < totalBooks; i++) {
        if (bookIDs[i] == id) {
            foundBook = i;
            break;
        }
    }

    printf("Enter actual number of days the book was kept: ");
    scanf("%d", &daysKept);

    while (daysKept <= 0) {
        printf("Days must be positive. Enter again: ");
        scanf("%d", &daysKept);
    }

    if (daysKept > allowedDays) {
        int extraDays = daysKept - allowedDays;
        fine = (memberType == 1) ? extraDays * 20.0f : extraDays * 10.0f;

        printf("Late fine before waiver: Rs. %.2f\n", fine);
        printf("Enter membership code for 50%% waiver (or NONE): ");
        scanf("%19s", code);

        if (strcmp(code, "LIB2026") == 0) {
            fine *= 0.5f;
            printf("Correct code. A 50%% waiver has been applied.\n");
        } else {
            printf("Code incorrect. No waiver applied.\n");
        }
    } else {
        printf("Book returned on time. No fine charged.\n");
    }

    if (foundBook != -1)
        availableCopies[foundBook]++;

    *totalFine += fineBeforeWaiver;

    for (j = foundBorrowed; j < *borrowedCount - 1; j++)
        borrowedBookIDs[j] = borrowedBookIDs[j + 1];

    (*borrowedCount)--;

    printf("Book returned successfully. Fine payable for this return: Rs. %.2f\n",
           fine);
    return fine;
}

void displayMemberRecord(char name[], int studentID, int memberType,
                         int borrowedBookIDs[], int borrowedCount,
                         float totalFine, float fineAfterWaiver)
{
    int i;

    printf("\n========== Member Record ==========\n");
    printf("Name: %s\n", name);
    printf("Student ID: %d\n", studentID);
    printf("Membership type: %s\n",
           memberType == 1 ? "Student" :
           memberType == 2 ? "Faculty" : "Not registered");

    printf("Currently borrowed book IDs: ");
    if (borrowedCount == 0) {
        printf("None");
    } else {
        for (i = 0; i < borrowedCount; i++)
            printf("%d ", borrowedBookIDs[i]);
    }

    printf("\nTotal fine before waivers: Rs. %.2f\n", totalFine);
    printf("Final fine payable after waivers: Rs. %.2f\n", fineAfterWaiver);
    printf("===================================\n");
}

int main(void)
{
    int bookIDs[MAX_BOOKS] = {101, 102, 103, 104, 105};
    char bookTitles[MAX_BOOKS][50] = {
        "C Programming",
        "Data Structures",
        "Database Systems",
        "Operating Systems",
        "Computer Networks"
    };
    int availableCopies[MAX_BOOKS] = {3, 2, 4, 2, 3};

    char name[50] = "";
    int studentID = 0, memberType = 0;
    int borrowedBookIDs[MAX_BORROWED] = {0};
    int borrowedCount = 0;
    float totalFineBeforeWaiver = 0.0f;
    float totalFineAfterWaiver = 0.0f;
    float finePayable;
    int choice;

    do {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Program terminated.\n");
            return 1;
        }

        switch (choice) {
            case 1:
                registerMember(name, &studentID, &memberType);
                break;

            case 2:
                displayBooks(bookIDs, bookTitles, availableCopies, MAX_BOOKS);
                break;

            case 3:
                if (memberType == 0) {
                    printf("Please register a member first.\n");
                } else {
                    borrowBook(bookIDs, bookTitles, availableCopies, MAX_BOOKS,
                               borrowedBookIDs, &borrowedCount, memberType);
                }
                break;

            case 4:
                if (memberType == 0) {
                    printf("Please register a member first.\n");
                } else {
                    finePayable = returnBook(bookIDs, availableCopies, MAX_BOOKS,
                                             borrowedBookIDs, &borrowedCount,
                                             memberType, &totalFineBeforeWaiver);
                    totalFineAfterWaiver += finePayable;

                }
                break;

            case 5:
                displayMemberRecord(name, studentID, memberType,
                                    borrowedBookIDs, borrowedCount,
                                    totalFineBeforeWaiver, totalFineAfterWaiver);
                break;

            case 6:
                printf("Exiting Library Management System. Goodbye!\n");
                break;

            default:
                printf("Invalid menu choice. Please select 1 to 6.\n");
        }
    } while (choice != 6);

    return 0;
}
