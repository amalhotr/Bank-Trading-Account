//
// Created by Ajeet Malhotra on 4/29/18.
//

#ifndef STOCKACCOUNT_H
#define STOCKACCOUNT_H
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "struct.h"
#include <ctime>
#include <iomanip>

using namespace std;

class stockaccount
{
public:
    stockaccount();

    void printPrice(string);
    void buyStock(Account&, string, int, double);
    void sellStock(Account&, string, int, double);
    void printPortfolio(Account&);
    void printTransactions(Account&);
    void menu(Account&);
private:

};
#endif

stockaccount::stockaccount()
{

}
void stockaccount::printPrice(string symbol)
{

    srand((unsigned int)time(NULL));
    int num = rand() % 4 + 1;
    string name = "stock" + to_string(num) + ".txt";

    ifstream file;
    file.open(name);

    string line;
    while (getline(file, line))
    {
        string delim = "\t";
        vector <string> tokens;
        string info;
        info = line;
        string substring;
        substring = line.substr(0, line.find(delim));

        if (substring.compare(symbol) == 0)
        {
            cout << info << endl;
            break;
        }
    }
    file.close();
}
void stockaccount::buyStock(Account& account, string symbol, int numShare, double price)
{
    cout << "\t\tSymbol = " << symbol << "\tNumber of Shares = " << numShare << "\tPrice per share = " << price << endl;
    Portfolio port;
    port.amount = numShare;
    port.price = price;
    port.symbol = symbol;
    port.total = price * numShare;

    srand((unsigned int)time(NULL));
    int num = rand() % 4 + 1;
    string name = "stock" + to_string(num) + ".txt";
    ifstream file;
    file.open(name);

    string line;
    while (getline(file, line))
    {
        string delim = "\t";
        vector <string> tokens;
        string stockInfo;
        stockInfo = line;
        string substring;
        substring = line.substr(0, line.find(delim));
        double stockPrice = stod(line.substr(line.rfind(delim) + 1, string::npos));

        if (substring.compare(symbol) == 0)
        {
            cout << stockInfo << endl;
            if (price >= stockPrice)
            {
                line = line.substr(line.find(delim) + 1, string::npos);
                string company = line.substr(0, line.find(delim));
                port.company = company;
                account.portfolioA.push_back(port);
                account.balance -= numShare * price;


                string ttime;
                time_t rawtime;
                struct tm*timeinfo;

                time(&rawtime);
                timeinfo = localtime(&rawtime);
                ttime = asctime(timeinfo);

                string line = "Buy\t" + symbol + "\t" + to_string(numShare) + "\t" + to_string(price) + "\t" + ttime + "\n";

                ofstream myfile;
                myfile.open("stock_transaction_history.txt", ios_base::app);
                myfile << line;
                myfile.close();
            }
            else
            {
                cout << "\nTransaction could not be completed." << endl;
            }
            break;
        }
    }
    file.close();
}


void stockaccount::sellStock(Account& account, string symbol, int numShare, double price)
{
    cout << "\tSymbol = " << symbol << "\tNumber of Shares = " << numShare << "\tPrice Per Share = " << price << endl;
    Portfolio sellPort;
    sellPort.amount = numShare;
    sellPort.price = price;
    sellPort.symbol = symbol;
    sellPort.total = (price * numShare);


    vector<Portfolio> portfolios = account.portfolioA;
    for (size_t j = 0; j < portfolios.size(); j++)
    {
        if (portfolios[j].symbol.compare(symbol) == 0)
        {
            if (portfolios[j].amount >= numShare)
            {
                srand((unsigned int)time(NULL));
                int num = rand() % 4 + 1;
                string name = "stock" + to_string(num) + ".txt";
                ifstream file;
                file.open(name);

                string line;
                while (getline(file, line))
                {
                    string delim = "\t";
                    vector <string> tokens;
                    string info;
                    info = line;
                    string substring;
                    substring = line.substr(0, line.find(delim));
                    double stockPrice = stod(line.substr(line.rfind(delim) + 1, string::npos));

                    if (substring.compare(symbol) == 0)
                    {
                        cout << info << endl;
                        if (price <= stockPrice)
                        {
                            if (portfolios[j].amount > numShare)
                            {
                                account.balance += numShare * price;
                                portfolios[j].amount = portfolios[j].amount - numShare;
                                portfolios[j].total = portfolios[j].amount * portfolios[j].price;
                                account.portfolioA[j] = portfolios[j];
                                time_t t = time(0);


                                string ttime;
                                time_t rawtime;
                                struct tm*timeinfo;

                                time(&rawtime);
                                timeinfo = localtime(&rawtime);
                                ttime = asctime(timeinfo);

                                string line = "Sell\t" + symbol + "\t" + to_string(numShare) + "\t" + to_string(price) + "\t" + ttime + "\n";

                                ofstream myfile;
                                myfile.open("stock_transaction_history.txt", ios_base::app);
                                myfile << line;
                                myfile.close();
                            }
                            else if (portfolios[j].amount = numShare) {
                                account.balance += numShare * price;

                                portfolios.erase(portfolios.begin() + j);
                                account.portfolioA = portfolios;
                                time_t t = time(0);


                                string ttime;
                                time_t rawtime;
                                struct tm*timeinfo;

                                time(&rawtime);
                                timeinfo = localtime(&rawtime);
                                ttime = asctime(timeinfo);

                                string line = "Sell\t" + symbol + "\t" + to_string(numShare) + "\t" + to_string(price) + "\t" + ttime + "\n";

                                ofstream myfile;
                                myfile.open("stock_transaction_history.txt", ios_base::app);
                                myfile << line;
                                myfile.close();
                            }
                        }
                        else
                        {
                            cout << "\nTransaction could not be completed" << endl;
                        }
                        break;
                    }
                }
                file.close();

            }
            else
            {
                cout << "Not enough shares" << endl;
            }
        }
        else
        {
            cout << "None of this stock" << endl;
        }
    }
}

void stockaccount::printPortfolio(Account& account)
{
    vector<Portfolio> port = account.portfolioA;
    cout << "\tCash Balance = " << account.balance << endl;
    double totalbal = 0;
    for (size_t i = 0; i < port.size(); i++)
    {
        cout << "\tSymbol = " << port[i].symbol << "\tNumber of Shares = " << port[i].amount << "\tPrice per Share = " << port[i].price << "\tCompany Name = " << port[i].company << "\tTotal = " << port[i].total << endl;
        totalbal += port[i].total;
    }
    cout << "\tTotal Portfolio Value =  " << account.balance + totalbal << endl;
}

void stockaccount::printTransactions(Account& account)
{
    ifstream file("stock_transaction_history.txt");
    string line;
    cout << "Action\tSymbol\tShare\tPrice\t\tTime" << endl;
    while (getline(file, line))
        cout << fixed << setprecision(2) << setfill('0') << line << endl;
    file.close();
}

void stockaccount::menu(Account& account)
{
    bool flag = true;
    int selection = 0;
    char test[256];

    while (flag)
    {
        cout << "\nPlease select an option" << endl
             << "\t1. Display current price for a stock symbol" << endl
             << "\t2. Buy stock" << endl
             << "\t3. Sell stock" << endl
             << "\t4. Display current portfolio" << endl
             << "\t5. Display transaction history" << endl
             << "\t6. Return to previous menu" << endl;

        cout << "\tYour selection: ";

        cin.getline(test, 256);
        cout << "Balance = " << account.balance << endl;
        selection = atoi(test);

        switch (selection)
        {
            case 1:
            {
                cout << "\n\tEnter stock symbol for checking price: ";
                char input[256];
                cin.getline(input, 256);
                string symbol(input);
                printPrice(symbol);
                break;
            }
            case 2:
            {
                cout << "\n\tEnter buy options" << endl;
                string line;
                getline(cin, line);
                string delim = " ";
                string symbol;

                int numShares;
                double price;
                for (int i = 0; i < 3; i++)
                {
                    if (i == 0)
                    {
                        symbol = line.substr(0, line.find(delim));
                    }
                    else if (i == 1)
                    {
                        numShares = stoi(line.substr(0, line.find(delim)));
                    }
                    else if (i == 2)
                    {

                        price = stod(line);
                    }
                    line = line.substr(line.find(delim) + 1, string::npos);
                }

                buyStock(account, symbol, numShares, price);
                break;
            }
            case 3:
            {
                cout << "\n\tEnter selling options" << endl;
                string line;
                getline(cin, line);


                string symbol;
                string delim = " ";


                int numShares;
                double price;
                for (int i = 0; i < 3; i++)
                {
                    if (i == 0)
                    {
                        symbol = line.substr(0, line.find(delim));
                    }
                    else if (i == 1)
                    {
                        numShares = stoi(line.substr(0, line.find(delim)));
                    }
                    else if (i == 2)
                    {
                        price = stod(line);
                    }
                    line = line.substr(line.find(delim) + 1, string::npos);
                }
                sellStock(account, symbol, numShares, price);
                break;
            }
            case 4:
                printPortfolio(account);
                break;
            case 5:
                printTransactions(account);
                break;
            case 6:
                flag = false;
                break;
            default:
                cout << "\n\tInvalid input. Please enter an option." << endl;
                break;
        }
    }
}







