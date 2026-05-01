#include "Income.h"
/*string source;
    string income;*/
Income::Income() {
    source = "";
    incomeType = "";
}
Income::Income(int i, double a, string d, string des, string c, string s, string it)
    : Transaction(i, a, d, des, c)
{
    source = s;
    incomeType = it;
}
void Income::setSource(string s) {
    source = s;
}

string Income::getSource() {
    return source;
}

void Income::addIncome() {

}
void Income::updateIncome() {

}

void Income::display() {

}