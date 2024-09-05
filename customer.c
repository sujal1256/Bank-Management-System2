#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>
#include <math.h>

#define MAX_CUSTOMERS 100
#define MAX_ACCOUNTS_PER_CUSTOMER 2
#define MAX_TRANSACTIONS 100
#define MAX_LOANS 2                   // Maximum number of loans a customer can have
#define BANK_ANNUAL_INTEREST_RATE 5.0 // Bank's annual interest rate in percent

// Structure to store Loan details
struct Loan
{
    float amount;     // Principal loan amount
    int timeSpan;     // Time span in years
    float monthlyEMI; // Monthly EMI
};

struct BankAccount
{
    int accountNumber;
    double balance;
    int customerID;                       // Link to the customer
    float transactions[MAX_TRANSACTIONS]; // Positive for deposit, negative for withdrawal
    int transactionCount;
    int pin;
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
    char password[100];
};

struct Customer customers[MAX_CUSTOMERS];
int customerCount = 0;

struct BankAccount bankAccounts[MAX_CUSTOMERS * MAX_ACCOUNTS_PER_CUSTOMER];
int bankAccountCount = 0;
int accountNumberCounter = 10000; // Global counter for new account numbers

int deletedAccountNumbers[MAX_CUSTOMERS * MAX_ACCOUNTS_PER_CUSTOMER];
int deletedCount = 0;

int deletedAccountNumbers[MAX_CUSTOMERS * MAX_ACCOUNTS_PER_CUSTOMER];

int getNextAccountNumber()
{
    if (deletedCount > 0)
    {
        // Reuse a deleted account number
        return deletedAccountNumbers[--deletedCount];
    }
    else
    {
        // Use a new account number
        return accountNumberCounter++;
    }
}

void createBankAccount(int customerID, float amount, int pin)
{
    if (amount < 1000)
    {
        printf("\nMinimum 1000 is required as an initial deposit for creating a bank account");
        return;
    }
    Sleep(600);

    if (bankAccountCount < MAX_CUSTOMERS * MAX_ACCOUNTS_PER_CUSTOMER)
    {
        struct BankAccount newAccount;

        newAccount.accountNumber = getNextAccountNumber(); // Get a unique account number
        newAccount.balance = (double)amount;
        newAccount.customerID = customerID;
        newAccount.transactionCount = 0; // Initialize transaction count
        newAccount.pin = pin;
        newAccount.transactions[newAccount.transactionCount++] = amount;

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

// Function to save customers to a file
void saveCustomersToFile()
{
    FILE *file = fopen("customers.txt", "w"); // Open file in text write mode
    if (file == NULL)
    {
        printf("\nError opening file for saving customers.\n");
        return;
    }

    fprintf(file, "Customer Count: %d\n\n", customerCount);

    for (int i = 0; i < customerCount; i++)
    {
        fprintf(file, "\nCustomer ID: %d\n", customers[i].customerID);
        fprintf(file, "Name: %s\n", customers[i].name);
        fprintf(file, "Phone Number: %s\n", customers[i].phoneNumber);
        fprintf(file, "Aadhar Number: %s\n", customers[i].aadharNumber);
        fprintf(file, "Profession: %s\n", customers[i].profession);
        fprintf(file, "Income: %.2f\n", customers[i].income);
        fprintf(file, "Age: %d\n", customers[i].age);
        fprintf(file, "Loans: %d\n", customers[i].loanCount);

        for (int j = 0; j < customers[i].loanCount; j++)
        {
            fprintf(file, "\tLoan %d - Amount: %.2f, Time Span: %d years, Monthly EMI: %.2f\n",
                    j + 1, customers[i].loans[j].amount, customers[i].loans[j].timeSpan, customers[i].loans[j].monthlyEMI);
        }

        // Print bank accounts
        fprintf(file, "Accounts: %d\n", MAX_ACCOUNTS_PER_CUSTOMER);
        for (int k = 0; k < bankAccountCount; k++)
        {
            if (bankAccounts[k].customerID == customers[i].customerID)
            {
                fprintf(file, "\tAccount %d - Account Number: %d, Balance: %.2f, Transaction Count: %d\n",
                        k + 1, bankAccounts[k].accountNumber, bankAccounts[k].balance, bankAccounts[k].transactionCount);

                // Print transactions
                for (int t = 0; t < bankAccounts[k].transactionCount; t++)
                {
                    fprintf(file, "\t\tTransaction %d: %.2f\n", t + 1, bankAccounts[k].transactions[t]);
                }
            }
        }

        fprintf(file, "\n");
    }

    fclose(file);
    printf("\nCustomers saved to file successfully in human-readable format.\n");
}

// Function to create a bank account
void deleteBankAccount(int customerID)
{
    int accountNumber;
    printf("Enter account number you want to delete: ");
    scanf("%d", &accountNumber);
    getchar();
    char ask_for_confirmation;
    printf("Are you sure you want to delete %d account?\n(y/n): ");
    scanf("%c", &ask_for_confirmation);

    if (ask_for_confirmation == 'y' || ask_for_confirmation == 'Y')
    {

        for (int i = 0; i < bankAccountCount; i++)
        {
            if (bankAccounts[i].customerID == customerID && bankAccounts[i].accountNumber == accountNumber)
            {

                // Add the account number to the list of deleted numbers
                deletedAccountNumbers[deletedCount++] = bankAccounts[i].accountNumber;

                // Remove the account by shifting all subsequent accounts down
                for (int j = i; j < bankAccountCount - 1; j++)
                {
                    bankAccounts[j] = bankAccounts[j + 1];
                }
                bankAccountCount--;

                printf("\nBank account with Account Number: %d deleted successfully!\n", accountNumber);
                return;
            }
        }
        printf("\nAccount Number: %d not found.\n", accountNumber);
    }
}

void showAllTransactions(int customerID, int accountNumber)
{

    // printf("Enter Account Number: ");
    // scanf("%d", &accountNumber);

    // Search for the account with matching customer ID
    for (int i = 0; i < bankAccountCount; i++)
    {
        if (bankAccounts[i].accountNumber == accountNumber && bankAccounts[i].customerID == customerID)
        {

            // Check if the entered PIN matches the account's PIN
            printf("\nAll Transactions for Account Number: %d\n", accountNumber);

            // Check if there are any transactions
            if (bankAccounts[i].transactionCount == 0)
            {
                printf("No transactions available.\n");
                return;
            }

            // Print all transactions
            for (int j = 0; j < bankAccounts[i].transactionCount; j++)
            {
                if (bankAccounts[i].transactions[j] < 0)
                {
                    printf("-%.2f (Withdrawal)\n", -(float)bankAccounts[i].transactions[j]);
                }
                else
                {
                    printf("+%.2f (Deposit)\n", (float)bankAccounts[i].transactions[j]);
                }
            }
            return;
        }
    }
    printf("\nAccount not found\n");
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
                bankAccounts[i].transactions[bankAccounts[i].transactionCount] = (amount); // Convert to integer to avoid floating point issues
                bankAccounts[i].transactionCount++;
            }

            printf("\nDeposited %.2f to Account Number: %d\n", amount, accountNumber);
            printf("New Balance: %.2f\n", bankAccounts[i].balance);
            return;
        }
    }
    printf("\nAccount not found.\n");
}

int inputPIN()
{
    int pin;
    printf("Enter PIN: ");
    scanf("%d", &pin);
    return pin;
}

// Function to withdraw money from a bank account
void withdrawMoney(int accountNumber, float amount)
{
    Sleep(600);
    for (int i = 0; i < bankAccountCount; i++)
    {
        if (bankAccounts[i].accountNumber == accountNumber)
        {
            // Prompt for the PIN
            int inputPin = inputPIN();

            // Check if the PIN is correct
            if (bankAccounts[i].pin != inputPin)
            {
                printf("\nIncorrect PIN. Cannot proceed with the withdrawal.\n");
                return;
            }

            // Check if the account has sufficient balance
            if (bankAccounts[i].balance >= amount)
            {
                bankAccounts[i].balance -= amount;

                // Record the transaction
                if (bankAccounts[i].transactionCount < MAX_TRANSACTIONS)
                {
                    bankAccounts[i].transactions[bankAccounts[i].transactionCount] = -(amount); // Convert to integer to avoid floating point issues
                    bankAccounts[i].transactionCount++;
                }

                printf("\nWithdrawn %.2f from Account Number: %d\n", amount, accountNumber);
                printf("New Balance: %.2f\n", bankAccounts[i].balance);
            }
            else
            {
                printf("\nInsufficient balance in Account Number: %d\n", accountNumber);
            }
            return;
        }
    }
    printf("\nAccount not found.\n");
}

void showCustomerDetails(int customerID)
{
    Sleep(600);
    for (int i = 0; i < customerCount; i++)
    {
        if (customers[i].customerID == customerID)
        {
            printf("\nCustomer Details:\n");
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

void viewCustomerAccounts(int customerID)
{
    Sleep(600);
    int found = 0;
    for (int i = 0; i < bankAccountCount; i++)
    {
        if (bankAccounts[i].customerID == customerID)
        {
            if (found == 0)
            {
                printf("\nBank Accounts for Customer ID: %d\n", customerID);
            }
            found = 1;
            printf("Account Number: %d\n", bankAccounts[i].accountNumber);
            printf("Balance: %.2f\n", bankAccounts[i].balance);
            showAllTransactions(customerID, bankAccounts[i].accountNumber);
            printf("-------------------------\n");
        }
    }
    if (found == 0)
    {
        printf("\nNo accounts found for this customer.\n");
    }
}

void handleDeposit(int customerID)
{
    int accountNumber;
    float amount;

    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);

    printf("Enter Amount to Deposit: ");
    scanf("%f", &amount);

    depositMoney(accountNumber, amount);
}

void handleWithdrawal(int customerID)
{
    int accountNumber;
    float amount;

    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);

    printf("Enter Amount to Withdraw: ");
    scanf("%f", &amount);

    withdrawMoney(accountNumber, amount);
}

void printAllCustomersAndAccounts()
{
    printf("\nAll Customers and their Accounts:\n");
    for (int i = 0; i < customerCount; i++)
    {
        printf("Customer ID: %d, Name: %s\n", customers[i].customerID, customers[i].name);
        viewCustomerAccounts(customers[i].customerID);
    }
}

void applyForLoan(int customerID, float loanAmount, int timeSpan)
{
    Sleep(600);
    for (int i = 0; i < customerCount; i++)
    {
        if (customers[i].customerID == customerID)
        {
            if (customers[i].loanCount < MAX_LOANS)
            {
                struct Loan newLoan;
                newLoan.amount = loanAmount;
                newLoan.timeSpan = timeSpan;
                newLoan.monthlyEMI = (loanAmount * BANK_ANNUAL_INTEREST_RATE / 100) / (12 * timeSpan);

                if (newLoan.monthlyEMI > customers[i].income * 0.5)
                {
                    printf("\nLoan cannot be approved. EMI exceeds 50%% of your monthly income.\n");
                    return;
                }

                customers[i].loans[customers[i].loanCount] = newLoan;
                customers[i].loanCount++;

                printf("\nLoan approved successfully!\n");
                printf("Loan Amount: %.2f\n", newLoan.amount);
                printf("Monthly EMI: %.2f\n", newLoan.monthlyEMI);
                printf("Time Span: %d years\n", timeSpan);
            }
            else
            {
                printf("\nCannot apply for more loans. Maximum limit reached.\n");
            }
            return;
        }
    }
    printf("\nCustomer not found.\n");
}

void handleLoanApplication(int customerID)
{
    float loanAmount;
    int timeSpan;

    printf("Enter Loan Amount: ");
    scanf("%f", &loanAmount);

    printf("Enter Time Span (in years): ");
    scanf("%d", &timeSpan);

    applyForLoan(customerID, loanAmount, timeSpan);
}

void customerPortal(int customerID)
{
    Sleep(600);
    int choice;
    do
    {
        printf("\nCustomer Portal for Customer ID: %d\n", customerID);
        printf("1. View Customer Details\n");
        printf("2. View Bank Accounts\n");
        printf("3. Create a Bank Account\n");
        printf("4. Deposit Money\n");
        printf("5. Withdraw Money\n");
        printf("6. Apply for Loan\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        int amount;
        switch (choice)
        {
        case 1:
            showCustomerDetails(customerID);
            break;
        case 2:
            viewCustomerAccounts(customerID);
            break;
        case 3:
            printf("Enter initial deposit: ");
            scanf("%d", &amount);
            createBankAccount(customerID, amount, customerID);
            break;
        case 4:
            deleteBankAccount(customerID);
            break;
        case 5:
            handleDeposit(customerID);
            break;
        case 6:
            handleWithdrawal(customerID);
            break;
        case 7:
            handleLoanApplication(customerID);
            break;
        case 8:
            printf("\nExiting Customer Portal.\n");
            break;
        default:
            printf("\nInvalid choice. Please try again.\n");
        }
    } while (choice != 8);
}

int handleCustomerLogin()
{
    if (customerCount == 0)
    {
        printf("\nNo customers found. Please create a customer first.\n");
        return 0;
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
        // showLoginScreen(); // Call the login screen function
        return -1;
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
    return 0;
}
void handleCustomerSignup()
{
    char name[50], phoneNumber[15], aadharNumber[20], profession[30];
    float income = 0;
    int age = 0;

    getchar();
    printf("Enter Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; // Remove newline character if present

    printf("Enter Phone Number: ");
    fgets(phoneNumber, sizeof(phoneNumber), stdin);
    phoneNumber[strcspn(phoneNumber, "\n")] = 0; // Remove newline character if present

    printf("Enter Aadhar Number: ");
    fgets(aadharNumber, sizeof(aadharNumber), stdin);
    aadharNumber[strcspn(aadharNumber, "\n")] = 0; // Remove newline character if present

    printf("Enter Profession: ");
    fgets(profession, sizeof(profession), stdin);
    profession[strcspn(profession, "\n")] = 0; // Remove newline character if present

    printf("Enter Income: ");
    scanf("%f", &income);
    getchar(); // Consume the newline character after scanf

    printf("Enter Age: ");
    scanf("%d", &age);
    getchar(); // Consume the newline character after scanf

    createCustomer(name, phoneNumber, aadharNumber, profession, income, age);
}
