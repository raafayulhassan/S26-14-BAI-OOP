#include "Budget.h"



Budget::Budget()
{
    budgetId = 0;
    categoryName = "not set";
    limitAmount = 0;
    usedAmount = 0;
}



Budget::Budget(int id, string c, double limit, double used)
{
    budgetId = id;
    categoryName = c;
    limitAmount = limit;
    usedAmount = used;
}



void Budget::setBudgetId(int id)
{
    budgetId = id;
}



void Budget::setCategoryName(string c)
{
    categoryName = c;
}



void Budget::setLimitAmount(double limit)
{
    limitAmount = limit;
}



void Budget::setUsedAmount(double used)
{
    usedAmount = used;
}



int Budget::getBudgetId()
{
    return budgetId;
}



string Budget::getCategoryName()
{
    return categoryName;
}



double Budget::getLimitAmount()
{
    return limitAmount;
}



double Budget::getUsedAmount()
{
    return usedAmount;
}



void Budget::display()
{
    cout << "Budget ID: " << budgetId << endl;
    cout << "Category: " << categoryName << endl;
    cout << "Limit Amount: " << limitAmount << endl;
    cout << "Used Amount: " << usedAmount << endl;
    cout << "Remaining Amount: " << limitAmount - usedAmount << endl;

    cout << endl;
}