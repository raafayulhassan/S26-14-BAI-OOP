#include<Category.h>
/*
    int categoryId;
    string categoryName;*/
Category() {
    categoryId = 0;
    categoryName = "";
}

Category(int id, string name) {
    this->categoryId = id;
    this->categoryName = name;
}