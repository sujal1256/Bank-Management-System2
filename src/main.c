#include "../Headers/admin.h"
#include "../Headers/customers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#define Sleep(x) usleep((x) * 1000)
#endif

void showLoginScreen()
{
    int choice;
    do
    {

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
        getchar(); 
        switch (choice)
        {
        case 1:
            printf("\nYou selected Admin.\n");
            handleAdminLogin();
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
    showLoginScreen();
    saveCustomersToFile(); 
    return 0;
}

