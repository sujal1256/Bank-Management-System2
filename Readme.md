# Bank Management System

## Overview

The **Bank Management System** is a C-based application designed to manage banking operations, including creating and managing customer accounts, handling deposits and withdrawals, viewing transaction histories, and applying for loans. The system also includes functionalities for admin management.

## Features

### Customer Management
- Create new customer profiles.
- View customer details.
- Manage customer accounts.

### Bank Account Management
- Create new bank accounts.
- Delete existing bank accounts.
- Handle deposits and withdrawals with PIN verification.

### Loan Management
- Apply for loans with real-time EMI calculations.
- Manage multiple loans per customer with limits.

### Transaction Management
- Record transactions for deposits and withdrawals.
- View transaction history for each account.

### Admin Functionalities
- View all bank accounts.
- View all transactions.
- Manage loans.

## File Structure

- **`main.c`**: The main source file containing the implementation of all functionalities including admin functionalities.
- **`admin.c`**: Source file for admin-specific functionalities.
- **`admin.h`**: Header file for declaring admin-specific functions.
- **`customers.txt`**: A file that stores customer data.
- **`Makefile`**: A file to manage the build process, including compiling `main.c` and `admin.c`.

## Build and Run

### Clean Unwanted Files

To clean all the unwanted files (bin and build folder), use the following command:

```bash
make clean
```

To build the project, use the following command:
```
make
```

To run the project, use the following command:
```
make run
```
