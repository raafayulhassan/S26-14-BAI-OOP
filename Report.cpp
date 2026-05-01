#include "Report.h"



Report::Report()
{

}



void Report::generateReport(Transaction transactions[], int transactionCount, Budget budgets[], int budgetCount)
{
    double totalTransactionAmount = 0;


    cout << "Financial Report" << endl;
    cout << "----------------" << endl;


    cout << "Transaction Summary" << endl;
    cout << "-------------------" << endl;


    for (int i = 0; i < transactionCount; i++)
    {
        totalTransactionAmount = totalTransactionAmount + transactions[i].getAmount();
    }


    cout << "Total Transactions: " << transactionCount << endl;
    cout << "Total Transaction Amount: " << totalTransactionAmount << endl;

    cout << endl;


    cout << "Budget Summary" << endl;
    cout << "--------------" << endl;


    for (int i = 0; i < budgetCount; i++)
    {
        budgets[i].display();
    }


    cout << "End of Report" << endl;
    cout << endl;
}