#include <iostream>
#include "account.h"
#include "bankaccount.h"
#include "stockaccount.h"
#include "struct.h"

Account account;
int main() {
    bankaccount bAccount;
    stockaccount sAccount;

    bool active = true;
    char test[256];
    string line;
    int input = 0;
    while (active)
    {
        cout << "Please select an amount to access" << endl
             << "\t1. Stock Portfolio Account" << endl
             << "\t2. Bank Account" << endl
             << "\t3. Exit" << endl
             << "\tYour Selection: ";

        cin.getline(test, 256);
        input = atoi(test);

        switch (input)
        {
            case 1:
                sAccount.menu(account);
                break;
            case 2:
                bAccount.menu(account);
                break;
            case 3:
                active = false;
                break;
            default:
                cout << "\n\tInvalid entry. Re-enter input: \n " << endl;
                break;
        }
    }
    return 0;
}