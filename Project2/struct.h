//
// Created by Ajeet Malhotra on 4/29/18.
//
#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

struct Portfolio {

    int amount;
    double price;
    double total;
    string symbol;
    string company;
};

struct Account
{
    double balance = 10000;
    vector<Portfolio> portfolioA;
};

#endif //PROJECT2_STRUCT_H
