#include "Alert.h"



Alert::Alert()
{
    message = "No alert.";
}



void Alert::checkBudget(Budget b)
{
    if (b.getUsedAmount() > b.getLimitAmount())
    {
        message = "Alert! Budget limit exceeded for category: " + b.getCategoryName();
    }
    else if (b.getUsedAmount() == b.getLimitAmount())
    {
        message = "Warning! Budget limit reached for category: " + b.getCategoryName();
    }
    else
    {
        message = "Budget is still safe for category: " + b.getCategoryName();
    }
}



void Alert::showAlert()
{
    cout << message << endl;
}