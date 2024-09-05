#include "customers.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void showAllCustomers();
void showBankAccountDetails(int accountNumber);
void showAllAccounts();
void showLoans(int customerID);
void showTransactions(int accountNumber);
void handleAdminLogin();

void adminPortal()
{
    Sleep(600);
    int choice;
    do
    {
        printf("\nAdmin Portal\n");
        printf("1. View All Customers\n");
        printf("2. View All Bank Accounts\n");
        printf("3. Add New Customer\n");
        printf("4. Delete Customer\n");
        printf("5. View Customer Loans\n");
        printf("6. View Bank Account Transactions of an Account\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        int customerID;
        int accountNumber;

        switch (choice)
        {
        case 1:
            showAllCustomers();
            break;
        case 2:
            showAllAccounts();
            break;
        case 3:
            handleCustomerSignup();
            break;
        case 4:
            printf("Enter Customer ID to view loans: ");
            scanf("%d", &customerID);
            showLoans(customerID);
            break;
        case 5:
            printf("Enter Bank Account Number to view transactions: ");
            scanf("%d", &accountNumber);
            showTransactions(accountNumber);
            break;
        case 6:
            printf("\nExiting Admin Portal.\n");
            break;
        default:
            printf("\nInvalid choice. Please try again.\n");
        }
    } while (choice != 6);
}

void showAllCustomers()
{
    Sleep(600);
    if (customerCount == 0)
    {
        printf("\nNo customers found.\n");
        return;
    }

    printf("\nAll Customers:\n");
    for (int i = 0; i < customerCount; i++)
    {
        printf("\nCustomer ID: %d\n", customers[i].customerID);
        showCustomerDetails(customers[i].customerID);
    }
}

void showBankAccountDetails(int accountNumber)
{
    for (int i = 0; i < bankAccountCount; i++)
    {
        if (bankAccounts[i].accountNumber == accountNumber)
        {
            printf("Account Number: %d\n", bankAccounts[i].accountNumber);
            printf("Balance: %.2f\n", bankAccounts[i].balance);
            printf("Accout Owner: %d\n", bankAccounts[i].customerID);
            printf("Number of Transactions: %d\n", bankAccounts[i].transactionCount);
            printf("Transactions:\n");
            for (int j = 0; j < bankAccounts[i].transactionCount; j++)
            {
                printf("  %.2f\n", bankAccounts[i].transactions[j]);
            }
            printf("PIN: %d\n", bankAccounts[i].pin);
            return;
        }
    }
    printf("\nBank account not found.\n");
}

void showAllAccounts()
{
    Sleep(600);

    if (bankAccountCount == 0)
    {
        printf("\nNo bank accounts found.\n");
        return;
    }

    printf("\nAll Bank Accounts:\n");

    for (int i = 0; i < customerCount; i++)
    {
        int foundAccount = 0;
        printf("\nCustomer ID: %d\n", customers[i].customerID);
        printf("Customer Name: %s\n", customers[i].name);

        // Loop through all bank accounts to find those belonging to the current customer
        for (int j = 0; j < bankAccountCount; j++)
        {
            if (bankAccounts[j].customerID == customers[i].customerID)
            {
                if (!foundAccount)
                {
                    printf("Bank Accounts:\n");
                    foundAccount = 1;
                }
                printf("  Account Number: %d\n", bankAccounts[j].accountNumber);
                printf("  Balance: %.2f\n", bankAccounts[j].balance);
                printf("  Number of Transactions: %d\n", bankAccounts[j].transactionCount);
            }
        }

        if (!foundAccount)
        {
            printf("  No bank accounts found for this customer.\n");
        }
    }
}

// Function to display loan details for a specific customer
void showLoans(int customerID)
{
    Sleep(600);
    int found = 0;

    // Search for the customer with the given ID
    for (int i = 0; i < customerCount; i++)
    {
        if (customers[i].customerID == customerID)
        {
            found = 1;

            // Check if the customer has any loans
            if (customers[i].loanCount == 0)
            {
                printf("\nCustomer ID: %d has no loans.\n", customerID);
                return;
            }

            // Display loan details
            printf("\nLoans for Customer ID: %d\n", customerID);
            for (int j = 0; j < customers[i].loanCount; j++)
            {
                printf("\nLoan %d:\n", j + 1);
                printf("  Amount: %.2f\n", customers[i].loans[j].amount);
                printf("  Time Span (years): %d\n", customers[i].loans[j].timeSpan);
                printf("  Monthly EMI: %.2f\n", customers[i].loans[j].monthlyEMI);
            }
            return;
        }
    }

    // If customer with given ID is not found
    if (!found)
    {
        printf("\nCustomer with ID: %d not found.\n", customerID);
    }
}

// Function to display transactions for a specific bank account
void showTransactions(int accountNumber)
{
    Sleep(600);
    int found = 0;

    // Search for the bank account with the given account number
    for (int i = 0; i < bankAccountCount; i++)
    {
        if (bankAccounts[i].accountNumber == accountNumber)
        {
            found = 1;

            // Check if the account has any transactions
            if (bankAccounts[i].transactionCount == 0)
            {
                printf("\nBank Account Number: %d has no transactions.\n", accountNumber);
                return;
            }

            // Display transaction details
            printf("\nTransactions for Bank Account Number: %d\n", accountNumber);
            for (int j = 0; j < bankAccounts[i].transactionCount; j++)
            {
                printf("  Transaction %d: %.2f\n", j + 1, bankAccounts[i].transactions[j]);
            }
            return;
        }
    }

    // If account with given number is not found
    if (!found)
    {
        printf("\nBank Account Number: %d not found.\n", accountNumber);
    }
}

// void handleAdminLogin()
// {
// }

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
        printf("3. Create New Customer\n");
        printf("4. Exit\n");
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
            printf("\nCreate New Customer.\n");
            handleCustomerSignup();
            break;
        case 4:
            printf("\nExiting...\n");
            break;
        default:
            printf("\nInvalid choice.\n");
            showLoginScreen();
            break;
        }
    } while (choice != 4);
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
