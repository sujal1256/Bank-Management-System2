#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_CUSTOMERS 100
#define MAX_ACCOUNTS_PER_CUSTOMER 2
#define MAX_TRANSACTIONS 100
#define MAX_LOANS 10 // Maximum number of loans a customer can have
#define BANK_ANNUAL_INTEREST_RATE 5.0 // Bank's annual interest rate in percent

// Structures
struct Loan {
    float amount;       // Principal loan amount
    int timeSpan;       // Time span in years
    float monthlyEMI;   // Monthly EMI
};

struct BankAccount {
    int accountNumber;
    float balance;
    int customerID; // Link to the customer
    int transactions[MAX_TRANSACTIONS]; // Positive for deposit, negative for withdrawal
    int transactionCount;
};

struct Customer {
    char name[50];
    char phoneNumber[15];
    char aadharNumber[20];
    char profession[30];
    float income;
    int age;
    int customerID;
    struct Loan loans[MAX_LOANS];
    int loanCount;
};

struct Customer customers[MAX_CUSTOMERS];
int customerCount = 0;

struct BankAccount bankAccounts[MAX_CUSTOMERS * MAX_ACCOUNTS_PER_CUSTOMER];
int bankAccountCount = 0;

// Function declarations
void createCustomer(char name[], char phoneNumber[], char aadharNumber[], char profession[], float income, int age);
void createBankAccount(int customerID);
void showMenu();
void showLoginScreen();
void printAllCustomersAndAccounts();
void depositMoney(int accountNumber, float amount);
void withdrawMoney(int accountNumber, float amount);
void applyForLoan(int customerID, float loanAmount, int timeSpan);

int main() {
    showLoginScreen();
    return 0;
}

// Function to create a customer
void createCustomer(char name[], char phoneNumber[], char aadharNumber[], char profession[], float income, int age) {
    if (customerCount < MAX_CUSTOMERS) {
        struct Customer newCustomer;

        strcpy(newCustomer.name, name);
        strcpy(newCustomer.phoneNumber, phoneNumber);
        strcpy(newCustomer.aadharNumber, aadharNumber);
        strcpy(newCustomer.profession, profession); 
        newCustomer.income = income;
        newCustomer.age = age;
        newCustomer.customerID = 1000 + customerCount;
        newCustomer.loanCount = 0; // Initialize loan count

        customers[customerCount] = newCustomer;
        customerCount++;

        printf("\nCustomer created successfully!\n");
        printf("Customer ID: %d\n", newCustomer.customerID);
    } else {
        printf("\nCannot create more customers. Maximum limit reached.\n");
    }
}

// Function to create a bank account
void createBankAccount(int customerID) {
    if (bankAccountCount < MAX_CUSTOMERS * MAX_ACCOUNTS_PER_CUSTOMER) {
        struct BankAccount newAccount;

        newAccount.accountNumber = 10000 + bankAccountCount;
        newAccount.balance = 0.0;
        newAccount.customerID = customerID;
        newAccount.transactionCount = 0; // Initialize transaction count

        bankAccounts[bankAccountCount] = newAccount;
        bankAccountCount++;

        printf("\nBank account created successfully!\n");
        printf("Account Number: %d\n", newAccount.accountNumber);
    } else {
        printf("\nCannot create more accounts. Maximum limit reached.\n");
    }
}

// Function to deposit money into a bank account
void depositMoney(int accountNumber, float amount) {
    for (int i = 0; i < bankAccountCount; i++) {
        if (bankAccounts[i].accountNumber == accountNumber) {
            bankAccounts[i].balance += amount;
            
            // Record the transaction
            if (bankAccounts[i].transactionCount < MAX_TRANSACTIONS) {
                bankAccounts[i].transactions[bankAccounts[i].transactionCount] = (int)(amount * 100); // Convert to integer to avoid floating point issues
                bankAccounts[i].transactionCount++;
            }
            
            printf("\nDeposited %.2f to Account Number: %d\n", amount, accountNumber);
            printf("New Balance: %.2f\n", bankAccounts[i].balance);
            return;
        }
    }
    printf("\nAccount not found.\n");
}

// Function to withdraw money from a bank account
void withdrawMoney(int accountNumber, float amount) {
    for (int i = 0; i < bankAccountCount; i++) {
        if (bankAccounts[i].accountNumber == accountNumber) {
            if (bankAccounts[i].balance >= amount) {
                bankAccounts[i].balance -= amount;
                
                // Record the transaction
                if (bankAccounts[i].transactionCount < MAX_TRANSACTIONS) {
                    bankAccounts[i].transactions[bankAccounts[i].transactionCount] = -(int)(amount * 100); // Convert to integer to avoid floating point issues
                    bankAccounts[i].transactionCount++;
                }
                
                printf("\nWithdrew %.2f from Account Number: %d\n", amount, accountNumber);
                printf("New Balance: %.2f\n", bankAccounts[i].balance);
            } else {
                printf("\nInsufficient balance.\n");
            }
            return;
        }
    }
    printf("\nAccount not found.\n");
}

// Function to apply for a loan
void applyForLoan(int customerID, float loanAmount, int timeSpan) {
    // Find the customer
    for (int i = 0; i < customerCount; i++) {
        if (customers[i].customerID == customerID) {
            // Check if customer can take the loan
            float monthlyInterestRate = BANK_ANNUAL_INTEREST_RATE / 12 / 100;
            int totalMonths = timeSpan * 12;
            float monthlyEMI = (loanAmount * monthlyInterestRate * pow(1 + monthlyInterestRate, totalMonths)) / (pow(1 + monthlyInterestRate, totalMonths) - 1);
            
            if (monthlyEMI > customers[i].income / 2) {
                printf("\nLoan application declined. EMI (%.2f) is more than half of your income (%.2f).\n", monthlyEMI, customers[i].income / 2);
                return;
            }

            // Check if the customer has space for more loans
            if (customers[i].loanCount < MAX_LOANS) {
                struct Loan newLoan;
                newLoan.amount = loanAmount;
                newLoan.timeSpan = timeSpan;
                newLoan.monthlyEMI = monthlyEMI;

                customers[i].loans[customers[i].loanCount] = newLoan;
                customers[i].loanCount++;

                printf("\nLoan application approved!\n");
                printf("Loan Amount: %.2f\n", loanAmount);
                printf("Time Span: %d years\n", timeSpan);
                printf("Monthly EMI: %.2f\n", monthlyEMI);
                return;
            } else {
                printf("\nLoan application declined. Maximum loan limit reached.\n");
                return;
            }
        }
    }
    printf("\nCustomer not found.\n");
}

// Function to print all customers and their accounts
void printAllCustomersAndAccounts() {
    printf("\nList of Customers and their Accounts:\n");
    for (int i = 0; i < customerCount; i++) {
        struct Customer *cust = &customers[i];
        printf("Customer ID: %d\n", cust->customerID);
        printf("Name: %s\n", cust->name);
        printf("Phone Number: %s\n", cust->phoneNumber);
        printf("Aadhar Number: %s\n", cust->aadharNumber);
        printf("Profession: %s\n", cust->profession);
        printf("Income: %.2f\n", cust->income);
        printf("Age: %d\n", cust->age);
        
        // Print loans
        if (cust->loanCount > 0) {
            printf("Loans:\n");
            for (int j = 0; j < cust->loanCount; j++) {
                struct Loan *loan = &cust->loans[j];
                printf("  Loan Amount: %.2f\n", loan->amount);
                printf("  Time Span: %d years\n", loan->timeSpan);
                printf("  Monthly EMI: %.2f\n", loan->monthlyEMI);
            }
        } else {
            printf("No Loans\n");
        }
        
        // Print accounts
        printf("Bank Accounts:\n");
        for (int k = 0; k < bankAccountCount; k++) {
            if (bankAccounts[k].customerID == cust->customerID) {
                printf("  Account Number: %d\n", bankAccounts[k].accountNumber);
                printf("  Balance: %.2f\n", bankAccounts[k].balance);
            }
        }
        printf("\n");
    }
}

// Function to show the login screen
void showLoginScreen() {
    int choice;

    printf("=====================================\n");
    printf("  Welcome to Bank Management System  \n");
    printf("=====================================\n");
    printf("Please select an option:\n");
    printf("1. Admin\n");
    printf("2. Customer\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();  // Clear newline character from input buffer

    switch (choice) {
    case 1:
        printf("\nYou selected Admin.\n");
        // Call the function for Admin login or admin operations
        break;
    case 2:
        printf("\nYou selected Customer.\n");
        // Creating sample customers
        createCustomer("John Doe", "1234567890", "1234-5678-9012", "Engineer", 50000.0, 30);

        // Creating sample bank accounts
        createBankAccount(1000);  // For John Doe
        createBankAccount(1000);  // Another account for John Doe

        printAllCustomersAndAccounts();

        // Example transactions
        depositMoney(10000, 500.0);
        withdrawMoney(10001, 200.0);

        printAllCustomersAndAccounts();

        // Applying for a loan
        applyForLoan(1000, 150000.0, 5); // Apply for a 5-year loan of 150000.0
        applyForLoan(1000, 15000000.0, 5); // Apply for a 5-year loan of 150000.0

        printAllCustomersAndAccounts();

        break;
    case 3:
        printf("\nExiting...\n");
        break;
    default:
        printf("\nInvalid choice.\n");
        break;
    }
}
