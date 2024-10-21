#ifndef PASSPORT_H
#include <time.h>

#define PASSPORT_H
#define PASSPORT_NO_START 100000000000

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

struct Date {
    int day;
    int month;
    int year;
};

struct PassportSRT {
    int id;
    char name[50];
    char email[50];
    int passport_no;
    char expiry_date[10];
};

int getChoiceInput();
void mainMenu();
void footerMenu(int call_from);
void passportList();
void createPassport();
void deletePassport();
void searchPassport();
void viewPassportDetails(struct PassportSRT passport);

void navigator(int choice) {
    switch (choice) {
        case 0:
            mainMenu();
            break;
        case 1:
            passportList();
            break;
        case 2:
            createPassport();
            break;
        case 3:
            deletePassport();
            break;
        case 4:
            searchPassport();
            break;
    }
}

#endif