#pragma once

#include <iostream>
#include <string>

using namespace std;



class Category
{

private:

    int categoryId;
    string categoryName;



public:

    Category();

    Category(int id, string name);



    void setCategoryId(int id);
    void setCategoryName(string name);



    int getCategoryId();
    string getCategoryName();



    void display();

};