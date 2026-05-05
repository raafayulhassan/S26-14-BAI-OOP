#pragma once

#include <iostream>
#include <string>

#include "budget.h"

using namespace std;



class Alert
{

private:

    string message;



public:

    Alert();



    void checkBudget(Budget b);

    void showAlert();

};
