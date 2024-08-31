#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>
#include <math.h>

#define MAX_CUSTOMERS 100
#define MAX_ACCOUNTS_PER_CUSTOMER 2
#define MAX_TRANSACTIONS 100
#define MAX_LOANS 10                  // Maximum number of loans a customer can have
#define BANK_ANNUAL_INTEREST_RATE 5.0 // Bank's annual interest rate in percent
#define WIDTH 40

// Structures
struct Loan
{
    float amount;     // Principal loan amount
    int timeSpan;     // Time span in years
    float monthlyEMI; // Monthly EMI
};

struct BankAccount
{
    int accountNumber;
    float balance;
    int customerID;                     // Link to the customer
    int transactions[MAX_TRANSACTIONS]; // Positive for deposit, negative for withdrawal
    int transactionCount;
};

struct Customer
{
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
void createBankAccount(int customerID, int amount, int pin);
void showMenu();
void showLoginScreen();
void printAllCustomersAndAccounts();
void depositMoney(int accountNumber, float amount);
void withdrawMoney(int accountNumber, float amount);
void applyForLoan(int customerID, float loanAmount, int timeSpan);
void customerPortal(int customerID);
void viewCustomerDetails(int customerID);
void viewCustomerAccounts(int customerID);
void handleDeposit(int customerID);
void handleWithdrawal(int customerID);
void handleLoanApplication(int customerID);
void addDefaultCustomers();

int main()
{
    addDefaultCustomers();

    showLoginScreen();
    return 0;
}

// Function to create a customer
void createCustomer(char name[], char phoneNumber[], char aadharNumber[], char profession[], float income, int age)
{
    Sleep(600);
    if (customerCount < MAX_CUSTOMERS)
    {
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

        // 1000 for fresh account, made for customers
        // and PIN will also me Customer ID for now FIXME:
        createBankAccount(newCustomer.customerID, 1000, newCustomer.customerID);
    }
    else
    {
        printf("\nCannot create more customers. Maximum limit reached.\n");
    }
}
void addDefaultCustomers()
{
    createCustomer("John Doe", "1234567890", "1234-5678-9012", "Engineer", 60000.0, 30);
    createCustomer("Jane Smith", "0987654321", "9876-5432-1098", "Doctor", 80000.0, 35);
    createCustomer("Alice Johnson", "1112233445", "1111-2233-4455", "Teacher", 50000.0, 28);
    createCustomer("Bob Brown", "2223344556", "2222-3344-5566", "Artist", 40000.0, 40);
}

// Function to create a bank account
void createBankAccount(int customerID, int amount, int pin)
{
    Sleep(600);
    if (bankAccountCount < MAX_CUSTOMERS * MAX_ACCOUNTS_PER_CUSTOMER)
    {
        struct BankAccount newAccount;

        newAccount.accountNumber = 10000 + bankAccountCount;
        newAccount.balance = (float)amount;
        newAccount.customerID = customerID;
        newAccount.transactionCount = 0; // Initialize transaction count

        bankAccounts[bankAccountCount] = newAccount;
        bankAccountCount++;

        printf("\nBank account created successfully!\n");
        printf("Account Number: %d\n", newAccount.accountNumber);
    }
    else
    {
        printf("\nCannot create more accounts. Maximum limit reached.\n");
    }
}

// Function to deposit money into a bank account
void depositMoney(int accountNumber, float amount)
{
    Sleep(600);
    for (int i = 0; i < bankAccountCount; i++)
    {
        if (bankAccounts[i].accountNumber == accountNumber)
        {
            bankAccounts[i].balance += amount;

            // Record the transaction
            if (bankAccounts[i].transactionCount < MAX_TRANSACTIONS)
            {
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
void withdrawMoney(int accountNumber, float amount)
{
    Sleep(600);
    for (int i = 0; i < bankAccountCount; i++)
    {
        if (bankAccounts[i].accountNumber == accountNumber)
        {
            if (bankAccounts[i].balance >= amount)
            {
                bankAccounts[i].balance -= amount;

                // Record the transaction
                if (bankAccounts[i].transactionCount < MAX_TRANSACTIONS)
                {
                    bankAccounts[i].transactions[bankAccounts[i].transactionCount] = -(int)(amount * 100); // Convert to integer to avoid floating point issues
                    bankAccounts[i].transactionCount++;
                }

                printf("\nWithdrew %.2f from Account Number: %d\n", amount, accountNumber);
                printf("New Balance: %.2f\n", bankAccounts[i].balance);
            }
            else
            {
                printf("\nInsufficient balance.\n");
            }
            return;
        }
    }
    printf("\nAccount not found.\n");
}

// Function to apply for a loan
void applyForLoan(int customerID, float loanAmount, int timeSpan)
{
    // Find the customer
    for (int i = 0; i < customerCount; i++)
    {
        if (customers[i].customerID == customerID)
        {
            // Check if customer can take the loan
            float monthlyInterestRate = BANK_ANNUAL_INTEREST_RATE / 12 / 100;
            int totalMonths = timeSpan * 12;
            float monthlyEMI = (loanAmount * monthlyInterestRate * pow(1 + monthlyInterestRate, totalMonths)) / (pow(1 + monthlyInterestRate, totalMonths) - 1);

            if (monthlyEMI > customers[i].income / 2)
            {
                printf("\nLoan application declined. EMI (%.2f) is more than half of your income (%.2f).\n", monthlyEMI, customers[i].income / 2);
                return;
            }

            // Check if the customer has space for more loans
            if (customers[i].loanCount < MAX_LOANS)
            {
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
            }
            else
            {
                printf("\nLoan application declined. Maximum loan limit reached.\n");
                return;
            }
        }
    }
    printf("\nCustomer not found.\n");
}

// Function to print all customers and their accounts
void printAllCustomersAndAccounts()
{
    Sleep(600);
    printf("\nList of Customers and their Accounts:\n");
    for (int i = 0; i < customerCount; i++)
    {
        struct Customer *cust = &customers[i];
        printf("Customer ID: %d\n", cust->customerID);
        printf("Name: %s\n", cust->name);
        printf("Phone Number: %s\n", cust->phoneNumber);
        printf("Aadhar Number: %s\n", cust->aadharNumber);
        printf("Profession: %s\n", cust->profession);
        printf("Income: %.2f\n", cust->income);
        printf("Age: %d\n", cust->age);

        // Print loans
        if (cust->loanCount > 0)
        {
            printf("Loans:\n");
            for (int j = 0; j < cust->loanCount; j++)
            {
                struct Loan *loan = &cust->loans[j];
                printf("  Loan Amount: %.2f\n", loan->amount);
                printf("  Time Span: %d years\n", loan->timeSpan);
                printf("  Monthly EMI: %.2f\n", loan->monthlyEMI);
            }
        }
        else
        {
            printf("No Loans\n");
        }

        // Print accounts
        printf("Bank Accounts:\n");
        for (int k = 0; k < bankAccountCount; k++)
        {
            if (bankAccounts[k].customerID == cust->customerID)
            {
                printf("  Account Number: %d\n", bankAccounts[k].accountNumber);
                printf("  Balance: %.2f\n", bankAccounts[k].balance);
            }
        }
        printf("\n");
    }
}

// Function to show the login screen
// int sleep()
void showLoginScreen()
{
    int choice;
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
        break;
    case 2:
    {
        printf("\nYou selected Customer.\n");

        if (customerCount == 0)
        {
            printf("\nNo customers found. Please create a customer first.\n");
            break;
        }

        int customerID;
        int customerIndex = -1;
        printf("Enter your Customer ID: ");
        scanf("%d", &customerID);
        getchar(); // Clear newline character

        // Check if the customer exists and find the index
        for (int i = 0; i < customerCount; i++)
        {
            if (customers[i].customerID == customerID)
            {
                customerIndex = i;
                break;
            }
        }

        if (customerIndex == -1)
        {
            printf("\nNo customer found with the entered ID.\n");
            showLoginScreen(); // Call the login screen function
            break;
        }
        else
        {
            // Check if the customer has a bank account
            int hasAccount = 0;
            for (int i = 0; i < bankAccountCount; i++)
            {
                if (bankAccounts[i].customerID == customerID)
                {
                    hasAccount = 1;
                    break;
                }
            }

            if (!hasAccount)
            {
                printf("\nNo bank account found for this customer. Please create an account first.\n");
                createBankAccount(customerID, 1000, customerID);
            }

            // Call customer portal function if account exists or after creating a new account
            customerPortal(customerID);
        }
        break;
    }
    case 3:
        printf("\nCreate New Customer.\n");

        char name[50];
        char phoneNumber[15];
        char aadharNumber[20];
        char profession[30];
        float income;
        int age;

        printf("Enter Name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0; // Remove newline character

        printf("Enter Phone Number: ");
        fgets(phoneNumber, sizeof(phoneNumber), stdin);
        phoneNumber[strcspn(phoneNumber, "\n")] = 0; // Remove newline character

        printf("Enter Aadhar Number: ");
        fgets(aadharNumber, sizeof(aadharNumber), stdin);
        aadharNumber[strcspn(aadharNumber, "\n")] = 0; // Remove newline character

        printf("Enter Profession: ");
        fgets(profession, sizeof(profession), stdin);
        profession[strcspn(profession, "\n")] = 0; // Remove newline character

        printf("Enter Income: ");
        scanf("%f", &income);

        printf("Enter Age: ");
        scanf("%d", &age);
        getchar(); // Clear newline character

        createCustomer(name, phoneNumber, aadharNumber, profession, income, age);
        break;
    case 4:
        printf("\nExiting...\n");
        break;
    default:
        printf("\nInvalid choice.\n");
        showLoginScreen();
        break;
    }
}

// Function to show the customer portal
void customerPortal(int customerID)
{
    Sleep(800);
    sleep(0.9);
    int choice;
    // FIXME: Add Create Bank Account feature,
    // FIXME: do not run an commands like deposit money or withdraw money if the person has 0 accounts
    // FIXME: Add show Loans option
    //
    do
    {
        printf("\n\n==============================\n");
        printf("        Customer Portal        \n");
        printf("==============================\n");
        printf("1. View My Details\n");
        printf("2. View My Accounts\n");
        printf("3. Create a Bank Account\n");
        printf("4. Deposit Money\n");
        printf("5. Withdraw Money\n");
        printf("6. Apply for a Loan\n");
        printf("7. Get Back to Login Screen\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline character from input buffer

        int amount, pin;

        switch (choice)
        {
        case 1:
            viewCustomerDetails(customerID);
            Sleep(1000);
            break;
        case 2:
            viewCustomerAccounts(customerID);
            Sleep(1000);
            break;
        case 3:
            printf("Enter Amount of First Deposit: ");
            scanf("%d", &amount);
            printf("Make a new PIN: ");
            scanf("%d", &pin);
            createBankAccount(customerID, amount, pin);
            Sleep(1000);
            break;
        case 4:
            handleDeposit(customerID);
            Sleep(1000);
            break;
        case 5:
            handleWithdrawal(customerID);
            Sleep(1000);
            break;
        case 6:
            handleLoanApplication(customerID);
            Sleep(1000);
            break;
        case 7:
            showLoginScreen();
            Sleep(1000);
            break;
        case 8:
            printf("\nExiting Customer Portal...\n");
            Sleep(1000);
            break;
        default:
            printf("\nInvalid choice. Please try again.\n");
            Sleep(1000);
            break;
        }
    } while (choice != 7);
}

// Function to view customer details
void viewCustomerDetails(int customerID)
{
    Sleep(800);
    for (int i = 0; i < customerCount; i++)
    {
        if (customers[i].customerID == customerID)
        {
            printf("\n\nCustomer ID: %d\n", customers[i].customerID);
            printf("Name: %s\n", customers[i].name);
            printf("Phone Number: %s\n", customers[i].phoneNumber);
            printf("Aadhar Number: %s\n", customers[i].aadharNumber);
            printf("Profession: %s\n", customers[i].profession);
            printf("Income: %.2f\n", customers[i].income);
            printf("Age: %d\n", customers[i].age);
            return;
        }
    }
    printf("\nCustomer not found.\n");
}

// Function to view customer accounts
void viewCustomerAccounts(int customerID)
{
    Sleep(600);
    printf("\nBank Accounts:\n");
    int found = 0;
    for (int i = 0; i < bankAccountCount; i++)
    {
        if (bankAccounts[i].customerID == customerID)
        {
            printf("\n  Account Number: %d\n", bankAccounts[i].accountNumber);
            printf("  Balance: %.2f\n", bankAccounts[i].balance);
            found = 1;
        }
    }
    if (!found)
    {
        printf("No accounts found for this customer.\n");
    }
}

// Function to handle deposit
void handleDeposit(int customerID)
{
    Sleep(600);
    int accountNumber;
    float amount;

    printf("Enter your Account Number: ");
    scanf("%d", &accountNumber);
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);

    depositMoney(accountNumber, amount);
}

// Function to handle withdrawal
void handleWithdrawal(int customerID)
{
    int accountNumber;
    float amount;

    printf("Enter your Account Number: ");
    scanf("%d", &accountNumber);

    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    withdrawMoney(accountNumber, amount);
}

// Function to handle loan application
void handleLoanApplication(int customerID)
{
    float loanAmount;
    int timeSpan;

    printf("Enter loan amount: ");
    scanf("%f", &loanAmount);
    printf("Enter time span (in years): ");
    scanf("%d", &timeSpan);

    applyForLoan(customerID, loanAmount, timeSpan);
}
void printCentered(const char *text)
{
    int len = strlen(text);
    int pad = (WIDTH - len) / 2;
    printf("%*s%s%*s\n", pad, "", text, pad, "");
}
