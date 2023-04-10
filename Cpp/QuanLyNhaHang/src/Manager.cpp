/*
 * File: Manager.cpp
 * Author: Ngoc Nguyen
 * Date: 27/03/2023
 * Description: This is a source file for class "Manager"
 */

#include <iostream>
#include <iomanip>
#include "../inc/Manager.h"

#define NOT_EMPTY           true
#define EMPTY               false

#define HEADER_LIST_ITEM                                                              \
    do                                                                                \
    {                                                                                 \
        cout << setw(5) << "ID" << setw(10) << "Name" << setw(10) << "Price" << endl; \
    } while (0)

#define INFO_ITEM(dummyItem)                                                            \
    do                                                                                  \
    {                                                                                   \
        cout << setw(5) << (int)dummyItem.getId() << setw(10) << dummyItem.getName();   \
        cout << setw(10) << dummyItem.getPrice() << endl;                               \
    } while (0)

// Initialize static variables = 0
vector<Table> Manager::listOfTable(0);
vector<Item> Manager::listOfItem(0);

/*
 * Method: setNumberOfTable
 * Description: set number of table
 * Input:
 *   const int setNumberOfTable - number of desired table to set
 * Output:
 *   number of table
 */
void Manager::setNumberOfTable(const int desiredNumberOfTable)
{
    // this->numberOfTable = desiredNumberOfTable;
    //add each table to the list of tables
    for (int i = 0; i < desiredNumberOfTable; i++)
    {
        Table table;
        this->listOfTable.push_back(table);
    }
    
}

/*
 * Method: addItem
 * Description: add a new item to the list of items
 * Input:
 *   const string nameOfItem - name of the new item
 *   const double price - price of the new item
 * Output:
 *   A new item added to the list of items
 */
void Manager::addItem(const string nameOfItem, const double price)
{
    // Create a new item with name and price
    Item newItem;
    newItem.setName(nameOfItem);
    newItem.setPrice(price);
    // add the item to the list of items
    this->listOfItem.push_back(newItem);
}

/*
 * Method: adjustItem
 * Description: adjust a item in the list of items
 * Input:
 *   const int id - id of the item which want to adjust
 * Output:
 *   returns status EMPTY/NOT_EMPLY of the list of items
 */
void Manager::adjustItem(const int id)
{
    // Find out the id in the list of items
    for (Item &dummyItem : this->listOfItem)
    {
        // if see
        if (dummyItem.getId() == id)
        {
            string name;
            double price;
            cout << "\t\t\tCURRENT INFO ITEM" << endl;
            HEADER_LIST_ITEM;
            INFO_ITEM(dummyItem);
            cout << "Enter the new name: ";
            getline(cin, name);
            cout << "Enter the new price: ";
            cin >> price;
            cin.ignore(255, '\n');
            dummyItem.setName(name);
            dummyItem.setPrice(price);
            return;
        }
    }
    // if not see
    cout << "ID not found !" << endl;
}

/*
 * Method: deleteItem
 * Description: deleteItem a item in the list of items
 * Input:
 *   const int id - id of the item which want to delete
 * Output:
 *   returns status EMPTY/NOT_EMPLY of the list of items
 */
void Manager::deleteItem(const int id)
{
    // Find out the id in the list of items
    int index = 0;
    for (Item dummyItem : this->listOfItem)
    {
        // if see
        if (dummyItem.getId() == id)
        {
            cout << "Deleting ..." << endl;
            this->listOfItem.erase(listOfItem.begin() + index);
            cout << "Deleted !" << endl;
            return;
        }
        ++index;
    }
    // if not see
    cout << "ID not found !" << endl;
}

/*
 * Method: showListOfItem
 * Description: show list of items
 * Input:
 * Output:
 *   returns status EMPTY/NOT_EMPLY of the list of items
 */
void Manager::showListOfItem()
{
    // print information items
    HEADER_LIST_ITEM;
    for (Item dummyItem : this->listOfItem)
    {
        INFO_ITEM(dummyItem);
    }
}