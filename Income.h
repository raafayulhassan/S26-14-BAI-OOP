#pragma once

#include "transaction.h"



class Income : public Transaction
{

private:

    string source;



public:

    Income();

    Income(int i, double a, string d, string des, string c, string s);



    void setSource(string s);

    string getSource();



    void display();

};
