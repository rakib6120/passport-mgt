#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "passport.h"

// Starting of the program.
int main() {
    mainMenu();
    return 0;
}

int getChoiceInput() {
    int choice;
    scanf("%d", &choice);
    getchar();
    system("clear");
    return choice;
}

void passportList() {
    printf("%-3s %-20s %-20s %-12s %s \n\n", "Id", "Full Name", "Email Address", "Passport No", "Date Of Birth");
    
    struct PassportSRT passport;
    FILE* fs = fopen("Data.dat", "rb");

    if (fs == NULL) {
        printf(RED "************************** PASSPORT NOT FOUND! ************************* \n" RESET);
        return;
    }

    while (fread(&passport, sizeof(passport), 1, fs)) {
        char expiry_date_str[26];
        ctime_r(&passport.expiry_date, expiry_date_str);
        printf("%-3d %-20s %-20s %-12d %s \n", passport.id, passport.name, passport.email, passport.passport_no, expiry_date_str);
    }
    fclose(fs);    
}

void createPassport() {
    struct PassportSRT passport;
    FILE* fs = fopen("Data.dat", "rb");

    if (fs == NULL) {
        passport.id = 1;
    } else {
        fseek(fs, -sizeof(passport), SEEK_END);
        if (fread(&passport, sizeof(passport), 1, fs) == 1) {
            passport.id += 1;
        } else {
            passport.id = 1;
        }
        fclose(fs);
    }

    fs = fopen("Data.dat", "ab");

    if (fs == NULL) {
        printf(RED "Error opening file.\n" RESET);
    } else {
        struct Date dob;
        printf("Enter Your Name: ");
        gets(passport.name, sizeof(passport.passport_no), stdin);

        printf("Enter Your Email: ");
        gets(passport.email, sizeof(passport.passport_no), stdin);

        printf("Enter Your Date Of Birth (DD-MM-YYYY): ");
        scanf("%d-%d-%d", &dob.day, &dob.month, &dob.year);

        passport.passport_no = PASSPORT_NO_START + passport.id;

        fwrite(&passport, sizeof(passport), 1, fs);
        fclose(fs);
    }

    printf("Create passport.\n");
}



void mainMenu() {
    printf("1. List of all passports.\n");
    printf("2. Create a new passport.\n\n");
    printf("**** Please choose a menu. **** \n\n");

    int choice = getChoiceInput();

    if (choice >= 1 && choice <= 2) {
        navigator(choice);
    } else {
        printf(RED "Your entered option was wrong. Please read carefully and try again.\n\n" RESET);
        mainMenu();
    }
}