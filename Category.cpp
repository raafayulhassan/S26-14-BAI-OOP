#include "category.h"



Category::Category()
{
    categoryId = 0;
    categoryName = "not set";
}



Category::Category(int id, string name)
{
    categoryId = id;
    categoryName = name;
}



void Category::setCategoryId(int id)
{
    categoryId = id;
}



void Category::setCategoryName(string name)
{
    categoryName = name;
}



int Category::getCategoryId()
{
    return categoryId;
}



string Category::getCategoryName()
{
    return categoryName;
}



void Category::display()
{
    cout << "Category ID: " << categoryId << endl;
    cout << "Category Name: " << categoryName << endl;

    cout << endl;
}
