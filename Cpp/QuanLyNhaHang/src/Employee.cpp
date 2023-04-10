/*
 * File: Employee.cpp
 * Author: Ngoc Nguyen
 * Date: 27/03/2023
 * Description: This is a source file for class "Employee"
 */
#include "../inc/Employee.h"
#include "../inc/Manager.h"
#include <iostream>
#include <iomanip>

#define AVAILABLE   true
#define OCCUPIED    false
#define NOT_EMPTY   true
#define EMPTY       false
#define PAID        1
#define UNPAID      2

#define HEADER_LIST_ITEM                                                         \
    do                                                                           \
    {                                                                            \
        cout << setw(5) << "ID" << setw(10) << "Name" << setw(10) << "Quantity"; \
        cout << setw(10) << "Amount" << endl;                                    \
    } while (0)

#define INFO_ITEM(dummyItem)                                                           \
    do                                                                                 \
    {                                                                                  \
        cout << setw(5) << (int)dummyItem.first << setw(10) << dummyItem.second.first; \
        cout << setw(10) << dummyItem.second.second;                                   \
        cout << setw(10) << itemTotalCost << endl;                                     \
    } while (0)

/*
 * Method: mainScreen
 * Class: Employee
 * Description: display list of tables and each table status
 * Access: public
 * Input: none
 * Output: none
 */
void Employee::mainScreen()
{
    //display list of tables
    for(int i = 1; i <= Manager::listOfTable.size(); ++i)
    {
        if(i == 1) cout << "Table : |";
        cout << " " << setw(3) << i << " |";
    }
    cout << endl;
    //display status of each table
    for(int i = 1; i <= Manager::listOfTable.size(); ++i)
    {
        if(i == 1) cout << "Status: |";
        if(Manager::listOfTable[i-1].getStatus() == AVAILABLE)
        {
            cout << "    " << " |";
        }
        else {
            cout << "  x " << " |";
        }
    }
    cout << endl;
}

/*
 * Method: selectTable
 * Class: Employee
 * Description: set status "OCCUPIED" for the table
 * Access: public
 * Input: 
 *     <1> tableNumber - selected table number
 * Output: none
 */
void Employee::selectTable(int tableNumber)
{
    // go through each element in the list of table
    for (auto &dummyTable : Manager::listOfTable)
    {
        if (dummyTable.getTableNumber() == tableNumber)
        {
            if (dummyTable.getStatus() == AVAILABLE)
            {
                dummyTable.setStatus(OCCUPIED);
                cout << "Selected table " << dummyTable.getTableNumber() << endl;
                return;
            }
        }
    }
    // when not find table number valid
    cout << "Invalid table number!" << endl;
}

/*
 * Method: takeOrder
 * Class: Employee
 * Description: save selected item into the list of ordered items of the table
 * Access: public
 * Input: 
 *     <1> table number - table number
 *     <2> itemID - item id
 *     <3> quantity - quantity of the item
 * Output: none
 */
void Employee::takeOrder(int tableNumber, int itemID, int quantity)
{
    // go through each element in the list of table
    for (auto &dummyTable : Manager::listOfTable)
    {
        if (dummyTable.getTableNumber() == tableNumber)
        {
            for (auto dummyItem : Manager::listOfItem)
            {
                //check if id is valid or not
                if (itemID == dummyItem.getId())
                {
                    //push informations of the item into the list
                    string itemName = dummyItem.getName();
                    dummyTable.addItemToList(itemID, itemName, quantity);
                    return;
                }
            }
            // when not find table number valid
            cout << "Invalid item ID!" << endl;
            return;
        }
    }
    // when not find table number valid
    cout << "Invalid table number!" << endl;
}

/*
 * Method: showBill
 * Class: Employee
 * Description: display the list of the ordered item with each item's total price
 * Access: public
 * Input: 
 *     <1> tableNumber - table number
 * Output: none
 */
void Employee::showBill(int tableNumber)
{
    // go through each element in the list of table
    for (auto dummyTable : Manager::listOfTable)
    {
        if (dummyTable.getTableNumber() == tableNumber)
        {
            //Check if this table is ordered yet
            if(dummyTable.getListOfOrderedItems().size() == EMPTY) {
                cout << "The table have not ordered yet!" << endl;
                return;
            }
            //the list of the ordered item with each item's total price
            HEADER_LIST_ITEM;
            for (auto dummyItem : dummyTable.getListOfOrderedItems())
            {
                double itemTotalCost = Manager::listOfItem[dummyItem.first - 100].getPrice() * dummyItem.second.second;
                INFO_ITEM(dummyItem);
            }
            return;
        }
    }
    // when not find table number valid
    cout << "Invalid table number!" << endl;
}

/*
 * Method: checkOut
 * Class: Employee
 * Description: display the list of the ordered item with each item's total price and total cost of the table
 * Access: public
 * Input: 
 *     <1> tableNumber - table number
 * Output: none
 */
void Employee::checkOut(int tableNumber)
{
    // go through each element in the list of table
    for (auto dummyTable : Manager::listOfTable)
    {
        if (dummyTable.getTableNumber() == tableNumber)
        {
            //Check if this table is ordered yet
            if(dummyTable.getListOfOrderedItems().size() == EMPTY) {
                cout << "The table have not ordered yet!" << endl;
                return;
            }
            int isPaid = UNPAID;
            double totalBill = 0;

            //display the list of the ordered item with each item's total price
            HEADER_LIST_ITEM;
            for (auto dummyItem : dummyTable.getListOfOrderedItems())
            {
                double itemTotalCost = Manager::listOfItem[dummyItem.first - 100].getPrice() * dummyItem.second.second;
                totalBill += itemTotalCost;
                INFO_ITEM(dummyItem);
            }

            //display the total cost of the table
            do
            {
                cout << "______________________TOTAL COST: " << totalBill << endl;
                cout << "1: Paid\n2: Unpaid\n";
                cout << "--> Your select: ";
                cin >> isPaid;
                cin.ignore(256, '\n');
                //select to paid or unpaid
                if(isPaid != UNPAID && isPaid != PAID)
                {
                    cout << "Invalid select! Please select again." << endl;
                }
            } while (isPaid != UNPAID && isPaid != PAID);

            //if paid, set status "AVAILABLE" for the table and delete the list of the ordered item of the table
            if(isPaid == PAID)
            {
                Manager::listOfTable[tableNumber - 1].setStatus(AVAILABLE);
                Manager::listOfTable[tableNumber - 1].deleteListOrdredItem();
            }
            return;
        }
    }
    // when not find table number valid
    cout << "Invalid table number!" << endl;
}