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
    printf("%-3s %-20s %-30s %-12s %s \n\n", "Id", "Full Name", "Email Address", "Passport No", "Date Of Birth");
    
    struct PassportSRT passport;
    FILE* fs = fopen("Data.dat", "rb");

    if (fs == NULL) {
        printf(RED "************************** PASSPORT NOT FOUND! ************************** \n" RESET);
        return;
    }

    while (fread(&passport, sizeof(passport), 1, fs)) {
        printf("%-3d %-20s %-30s %-12d %s \n", passport.id, passport.name, passport.email, passport.passport_no, passport.expiry_date);
    }
    fclose(fs);
    footerMenu(1);
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
        printf("Enter Your Name: ");
        gets(passport.name, sizeof(passport.name), stdin);

        printf("Enter Your Email: ");
        gets(passport.email, sizeof(passport.email), stdin);

        printf("Enter Your Date Of Birth (DD-MM-YYYY): ");
        gets(passport.expiry_date, sizeof(passport.expiry_date), stdin);

        passport.passport_no = PASSPORT_NO_START + passport.id;

        fwrite(&passport, sizeof(passport), 1, fs);
        fclose(fs);
    }

    system("clear");
    printf(GRN "Successfully created passport.\n" RESET);
    navigator(1);
}

void deletePassport() {
    int passport_id;
    bool found = false;
    struct PassportSRT passport;

    FILE *fs = fopen("Data.dat", "rb");
    if (fs == NULL) {
        printf(RED "************************** PASSPORT DATA NOT FOUND! ************************** \n" RESET);
        footerMenu(1);
        return;
    }

    FILE *temp = fopen("Temp.dat", "wb");
    if (temp == NULL) {
        printf(RED "Something went wrong.\n" RESET);
        fclose(fs);
        footerMenu(1);
        return;
    }

    printf("Enter Passport ID to delete: ");
    scanf("%d", &passport_id);
    getchar();

    while (fread(&passport, sizeof(passport), 1, fs)) {
        if (passport.id == passport_id) {
            found = true;
            printf(GRN "Passport with ID %d deleted successfully.\n" RESET, passport_id);
        } else {
            fwrite(&passport, sizeof(passport), 1, temp);
        }
    }

    fclose(fs);
    fclose(temp);

    if (!found) {
        printf(RED "Passport ID %d not found.\n" RESET, passport_id);
        remove("Temp.dat");
    } else {
        remove("Data.dat");
        rename("Temp.dat", "Data.dat");
    }

    footerMenu(1);
}


void mainMenu() {
    printf("1. List of all passports.\n");
    printf("2. Create a new passport.\n");
    printf("3. Delete a passport.\n\n");

    printf("**** Please choose a menu. **** \n\n");

    int choice = getChoiceInput();

    if (choice >= 1 && choice <= 3) {
        navigator(choice);
    } else {
        printf(RED "Your entered option was wrong. Please read carefully and try again.\n\n" RESET);
        mainMenu();
    }
}

void footerMenu(int call_from) {
    printf("\n\n------------------------------------------------------------------------------------ \n");
    printf(WHT "0. Backt to main menu.      ");
    printf("1. List of all passports.      ");
    printf("2. Create a new passport.      ");
    printf("3. Delete a passport.      \n" RESET);

    int choice = getChoiceInput();

    if (choice >= 0 && choice <= 3) {
        navigator(choice);
    } else {
        printf(RED "Your entered option was wrong. Please read carefully and try again.\n\n" RESET);
        navigator(call_from);
    }
}