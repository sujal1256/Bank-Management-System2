#ifndef CUSTOMER_H
#define CUSTOMER_H

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

// Declare the variables as extern
extern struct Customer customers[];
extern int customerCount;
extern struct BankAccount bankAccounts[];
extern int bankAccountCount;
extern int accountNumberCounter;
extern int deletedAccountNumbers[];
extern int deletedCount;

#endif // CUSTOMER_H

int getNextAccountNumber();

void createBankAccount(int customerID, float amount, int pin);

void createCustomer(char name[], char phoneNumber[], char aadharNumber[], char profession[], float income, int age);

void addDefaultCustomers();

void saveCustomersToFile();

void deleteBankAccount(int customerID);

void showAllTransactions(int customerID, int accountNumber);

void depositMoney(int accountNumber, float amount);

int inputPIN();

void withdrawMoney(int accountNumber, float amount);

void showCustomerDetails(int customerID);

void viewCustomerAccounts(int customerID);

void customerPortal(int customerID);

void printAllCustomersAndAccounts();

void showLoginScreen();

void handleDeposit(int customerID);

void handleWithdrawal(int customerID);

void handleLoanApplication(int customerID);

void applyForLoan(int customerID, float loanAmount, int timeSpan);


int handleCustomerLogin();

void handleCustomerSignup();
