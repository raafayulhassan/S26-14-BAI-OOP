#include "report.h"



Report::Report()
{

}



void Report::generateReport(Transaction transactions[], int transactionCount, Budget budgets[], int budgetCount)
{
    double totalIncome = 0;
    double totalExpense = 0;


    cout << "Financial Report" << endl;
    cout << "----------------" << endl;


    for (int i = 0; i < transactionCount; i++)
    {
        if (transactions[i].getTransactionType() == "Income")
        {
            totalIncome = totalIncome + transactions[i].getAmount();
        }
        else if (transactions[i].getTransactionType() == "Expense")
        {
            totalExpense = totalExpense + transactions[i].getAmount();
        }
    }


    cout << "Total Income: " << totalIncome << endl;
    cout << "Total Expense: " << totalExpense << endl;
    cout << "Balance: " << totalIncome - totalExpense << endl;

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
