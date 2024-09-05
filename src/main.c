#include "../Headers/admin.h"
#include "../Headers/customers.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void showLoginScreen()
{
    int choice;
    do
    {
        /* code */

        Sleep(600);
        printf("\n\n=====================================\n");
        printf("  Welcome to Bank Management System  \n");
        printf("=====================================\n");
        printf("Please select an option:\n");
        printf("1. Admin\n");
        printf("2. Customer\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline character from input buffer

        switch (choice)
        {
        case 1:
            printf("\nYou selected Admin.\n");
            // Call the function for Admin login or admin operations
            adminPortal();
            break;
        case 2:
        {
            printf("\nYou selected Customer.\n");
            int a = handleCustomerLogin(1);

            break;
        }
        case 3:
            printf("\nExiting...\n");
            break;
        default:
            printf("\nInvalid choice.\n");
            showLoginScreen();
            break;
        }
    } while (choice != 3);
}

int main()
{
    addDefaultCustomers();
    // loadCustomersFromFile();
    showLoginScreen();
    saveCustomersToFile(); // Save customers to file before exiting
    return 0;
}

// Function to save customers to a file
