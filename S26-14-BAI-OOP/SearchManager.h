#pragma once

#include <iostream>

#include "Transaction.h"

using namespace std;


class SearchManager
{

public:

    SearchManager();



    void searchByCategory
    (
        Transaction transactions[],
        int size,
        string categoryName
    );


    void searchByDate
    (
        Transaction transactions[],
        int size,
        string date
    );


    void searchByAmount
    (
        Transaction transactions[],
        int size,
        double amount
    );

};