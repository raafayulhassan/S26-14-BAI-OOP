#pragma once

#include <iostream>

#include "Transaction.h"
#include "Budget.h"

using namespace std;



class Report
{

public:

    Report();



    void generateReport(Transaction transactions[], int transactionCount, Budget budgets[], int budgetCount);

};