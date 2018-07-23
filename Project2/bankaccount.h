//
// Created by Ajeet Malhotra on 4/29/18.
//


#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string>
#include "struct.h"
#include <ctime>
#include <fstream>

using namespace std;

class bankaccount
{
public:
    bankaccount();
    void printPortfolio(Account&);
    void printTransactions(Account&);
    void menu(Account&);
    void deposit(Account&, double);
    void withdraw(Account&, double);


private:

};
#endif

void bankaccount::printPortfolio(Account& account)
{
    vector<Portfolio> portfolioA = account.portfolioA;
    cout << "\tCash Balance " << account.balance << endl;
    double totalbal=0;
    cout<< "\tSymbol"<<"\t\t"<<"Company"<<"\t\t\t\t\tNumber"<<"\t\tPrice"<<"\t\tTotal"<<endl;
    for (size_t i = 0; i < portfolioA.size(); i++)
    {
        cout << "\t"<<portfolioA[i].symbol << "\t\t" << portfolioA[i].company << "\t\t" << portfolioA[i].amount << "\t\t" << portfolioA[i].price << "\t\t" << portfolioA[i].total << endl;
        totalbal += portfolioA[i].total;

    }

    cout << "\tTotal portfolio value =  " << account.balance + totalbal << endl;


}

void bankaccount::printTransactions(Account& account)
{

    ifstream file("bank_transaction_history.txt");
    string line;
    cout << "Action\t\tAmount\tCash Balance\tDate\tTime" << endl;
    while (getline(file, line))
        cout << line << endl;
    file.close();

}

bankaccount::bankaccount()
{

}

void bankaccount::menu(Account& account)
{
    bool active= true;
    int input;
    char in[256];
    while (active)
    {
        cout << "\nPlease select an option" << endl
             << "\t1. View account balance" << endl
             << "\t2. Deposit money" << endl
             << "\t3. Withdraw money" << endl
             << "\t4. Display transaction history" << endl
             << "\t5. Return to previous menu" << endl
             << "\tYour selection: ";


        cin.getline(in, 256);

        input = atoi(in);

        switch (input)
        {
            case 1:
                printPortfolio(account);
                break;
            case 2:
            {
                string line;
                double amount;
                cout << "\n\t Deposit Account: " << endl;
                getline(cin, line);
                amount = stod(line);
                deposit(account, amount);
                break;
            }
            case 3:
            {
                string line;
                double amount;
                cout << "\n\t Withdraw Amount: " << endl;
                getline(cin, line);
                amount = stod(line);
                withdraw(account, amount);
                break;
            }
            case 4:
                printTransactions(account);
                break;
            case 5:
                active = false;
                break;
            default:
                cout << "\n\t Invalid. Re-Enter Input: " << endl;
                break;
        }
    }
}


void bankaccount::deposit(Account& account, double amt)
{
    cout << "\t\t Amount = " << amt << endl;
    account.balance += amt;
    time_t t = time(0);

    struct tm now;


    string ttime;
    time_t rawtime;
    struct tm*timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    ttime = asctime(timeinfo);


    string line = "Deposit\t" + to_string(amt) + "\t" + to_string(account.balance) + "\t" +  ttime + "\n";

    ofstream myfile;
    myfile.open("bank_transaction_history.txt", ios_base::app);
    myfile << line;
    myfile.close();

    printPortfolio(account);
}

void bankaccount::withdraw(Account& account, double amt)
{
    cout << "\\t\t Amount = " << amt << endl;
    account.balance -= amt;



    string ttime;
    time_t rawtime;
    struct tm*timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    ttime = asctime(timeinfo);

    string line = "Withdraw\t" + to_string(amt) + "\t" + to_string(account.balance) + "\t" + ttime + "\n";

    ofstream myfile;
    myfile.open("bank_transaction_history.txt", ios_base::app);
    myfile << line;
    myfile.close();

    printPortfolio(account);

}


