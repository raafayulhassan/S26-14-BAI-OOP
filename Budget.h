#pragma once

#include <iostream>
#include <string>

using namespace std;



class Budget
{

private:

    int budgetId;
    string categoryName;
    double limitAmount;
    double usedAmount;



public:

    Budget();

    Budget(int id, string c, double limit, double used);



    void setBudgetId(int id);
    void setCategoryName(string c);
    void setLimitAmount(double limit);
    void setUsedAmount(double used);



    int getBudgetId();
    string getCategoryName();
    double getLimitAmount();
    double getUsedAmount();



    void display();

};