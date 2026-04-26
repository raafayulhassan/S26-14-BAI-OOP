#include "SearchManager.h"



SearchManager::SearchManager()
{

}



void SearchManager::searchByCategory(Transaction transactions[], int size, string categoryName)
{
    bool found = false;


    cout << "Search By Category" << endl;
   


    for (int i = 0; i < size; i++)
    {
        if (transactions[i].getCategoryName() == categoryName)
        {
            transactions[i].display();

            found = true;
        }
    }


    if (found == false)
    {
        cout << "No transaction found in this category." << endl;
    }
}



void SearchManager::searchByDate(Transaction transactions[], int size, string date)
{
    bool found = false;


    cout << "Search By Date" << endl;



    for (int i = 0; i < size; i++)
    {
        if (transactions[i].getDate() == date)
        {
            transactions[i].display();

            found = true;
        }
    }


    if (found == false)
    {
        cout << "No transaction found on this date." << endl;
    }
}



void SearchManager::searchByAmount(Transaction transactions[], int size, double amount)
{
    bool found = false;


    cout << "Search By Amount" << endl;
 


    for (int i = 0; i < size; i++)
    {
        if (transactions[i].getAmount() == amount)
        {
            transactions[i].display();

            found = true;
        }
    }


    if (found == false)
    {
        cout << "No transaction found with this amount." << endl;
    }
}