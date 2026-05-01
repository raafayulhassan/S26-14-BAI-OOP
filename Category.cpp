#include "Category.h"
/*
    int categoryId;
    string categoryName;*/
Category::Category() {
    categoryId = 0;
    categoryName = "";
}

Category::Category(int id, string name) {
    this->categoryId = id;
    this->categoryName = name;
}
void Category::setCategoryId(int id) {
    categoryId = id;
}
void Category::setCategoryName(string name) {
    categoryName = name;
}



int Category::getCategoryId() {
    return categoryId;
}
string Category::getCategoryName() {
    return categoryName;
}



void Category::display() {
    cout << "Category Id: " << categoryId << endl;
    cout << "Category Name: " << categoryName << endl;
}