#include<Expense.h>
/*string paymentMethod;
string expenseType
String Notes*/
Expense() {
	expenseType = "";
	paymentMethod = "";
	notes = "";
}
Expense(int i, double a, string d, string des, string c, string p, string e, string n) {
	this->paymentMethod = p;
	this->expenseType = e;
	this->notes = n;
}