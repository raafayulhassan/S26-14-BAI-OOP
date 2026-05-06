#pragma once

#include <iostream>

#include "transaction.h"
#include "budget.h"

using namespace std;



class Report
{

public:

    Report();



    void generateReport(Transaction transactions[], int transactionCount, Budget budgets[], int budgetCount);

};
