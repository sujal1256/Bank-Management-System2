# Bank Management System

## Overview

The **Bank Management System** is a C-based application designed to manage banking operations, including creating and managing customer accounts, handling deposits and withdrawals, viewing transaction histories, and applying for loans. The system provides a user-friendly interface to manage various banking activities.

## Features

- **Customer Management:**
  - Create new customer profiles.
  - View customer details.
  - Manage customer accounts.

- **Bank Account Management:**
  - Create new bank accounts.
  - Delete existing bank accounts.
  - Handle deposits and withdrawals with PIN verification.

- **Loan Management:**
  - Apply for loans with real-time EMI calculations.
  - Manage multiple loans per customer with limits.

- **Transaction Management:**
  - Record transactions for deposits and withdrawals.
  - View transaction history for each account.

## File Structure

- **`main.c`**: The main source file containing the implementation of all functionalities.
- **`customers.txt`**: A file that stores customer data in a human-readable format for persistence.

## Start the Project

To clean all the unwanted and executable files use the following command:

```bash
make clean
```
To run the project use the following command:
```bash
gcc -o bank_management_system main.c
```
