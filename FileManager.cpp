#include "FileManager.h"



FileManager::FileManager()
{

}



void FileManager::saveTransactions(Transaction transactions[], int size)
{
    ofstream file;

    file.open("transactions.txt");


    for (int i = 0; i < size; i++)
    {
        file << transactions[i].getId() << endl;
        file << transactions[i].getAmount() << endl;
        file << transactions[i].getDate() << endl;
        file << transactions[i].getDescription() << endl;
        file << transactions[i].getCategoryName() << endl;
    }


    file.close();

    cout << "Transactions saved successfully." << endl;
}



void FileManager::loadTransactions(Transaction transactions[], int& size, int capacity)
{
    ifstream file;

    file.open("transactions.txt");


    size = 0;


    int id;
    double amount;
    string date;
    string description;
    string categoryName;


    for (int i = 0; i < capacity; i++)
    {
        if (file >> id)
        {
            file >> amount;

            file.ignore();

            getline(file, date);
            getline(file, description);
            getline(file, categoryName);


            Transaction temp(id, amount, date, description, categoryName);

            transactions[size] = temp;

            size++;
        }
    }


    file.close();

    cout << "Transactions loaded successfully." << endl;
}



void FileManager::saveBudgets(Budget budgets[], int size)
{
    ofstream file;

    file.open("budgets.txt");


    for (int i = 0; i < size; i++)
    {
        file << budgets[i].getBudgetId() << endl;
        file << budgets[i].getCategoryName() << endl;
        file << budgets[i].getLimitAmount() << endl;
        file << budgets[i].getUsedAmount() << endl;
    }


    file.close();

    cout << "Budgets saved successfully." << endl;
}



void FileManager::loadBudgets(Budget budgets[], int& size, int capacity)
{
    ifstream file;

    file.open("budgets.txt");


    size = 0;


    int budgetId;
    string categoryName;
    double limitAmount;
    double usedAmount;


    for (int i = 0; i < capacity; i++)
    {
        if (file >> budgetId)
        {
            file.ignore();

            getline(file, categoryName);

            file >> limitAmount;
            file >> usedAmount;


            Budget temp(budgetId, categoryName, limitAmount, usedAmount);

            budgets[size] = temp;

            size++;
        }
    }


    file.close();

    cout << "Budgets loaded successfully." << endl;
}