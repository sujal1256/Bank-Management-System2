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

