#include "customers.h"


int main()
{
    addDefaultCustomers();
    // loadCustomersFromFile();
    showLoginScreen();
    saveCustomersToFile(); // Save customers to file before exiting
    return 0;
}




// Function to save customers to a file







