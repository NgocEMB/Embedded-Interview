/*
 * File: Table.cpp
 * Author: Ngoc Nguyen
 * Date: 29/03/2023
 * Description: This is a source file for class "Table"
 */
#include "../inc/Table.h"
#include "../inc/Manager.h"
#include <iomanip>
#include <iostream>

#define AVAILABLE   true
#define OCCUPIED    false
#define NOT_EMPTY   true
#define EMPTY       false

#define HEADER_LIST_ITEM                                                           \
    do                                                                             \
    {                                                                              \
        cout << setw(5) << "ID" << setw(15) << "Name" << setw(15) << "Unit price"; \
        cout << setw(10) << "Quantity" << setw(10) << "Total" << endl;             \
    } while (0)

#define INFO_ITEM(dummyItem)                                                                      \
    do                                                                                            \
    {                                                                                             \
        cout << setw(5) << (int)dummyItem.first.getId() << setw(15) << dummyItem.first.getName(); \
        cout << setw(15) << dummyItem.first.getPrice() << setw(10) << dummyItem.second << endl;   \
        cout << setw(10) << (dummyItem.first.getPrice() * dummyItem.second) << endl;              \
    } while (0)

//Table number begins from 1
int Table::count = 1;

/*
 * Constructor: tABLE
 * Class: Table
 * Description: set status of table
 * Input: none
 */
Table::Table()
{
    // set available status for each object "table"
    this->status = AVAILABLE;
    vector<pair<int, pair<string, int>>> listOfOrderedItems(0);
    //Table number increases automatically and fixed
    this->tableNumber = count;
    ++count;
}

/*
 * Method: setStatus
 * Class: Table
 * Description: set status for a selected table
 * Access: public
 * Input:
 *     <1> status - desired status of a table
 * Output: none
 */
void Table::setStatus(bool status)
{
    this->status = status;
}

/*
 * Method: orderItem
 * Class: Table
 * Description: add a new item to the list of ordered items of each table
 * Access: public
 * Input:
 *     <1> item - oredred item
 * Output: none
 */
void Table::addItemToList(int id, string name, int quantity)
{
    for(auto &dummyData : listOfOrderedItems)
    {
        //Nếu món đã có trong danh sách được gọi trước đó, thì chỉ cần cộng thêm 
        //vào số lượng
        if(dummyData.first == id)
        {
            dummyData.second.second += quantity;
            return;
        }
    }
    listOfOrderedItems.push_back(make_pair(id, make_pair(name, quantity)));
}

void Table::deleteListOrdredItem()
{
    this->listOfOrderedItems.clear();
}

/*
 * Method: getStatus
 * Class: Table
 * Description: get current status of a table
 * Access: public
 * Input: none
 * Output:
 *     returns current status of a table
 */
bool Table::getStatus()
{
    return this->status;
}

/*
 * Method: getTableNumber
 * Class: Table
 * Description: get table number
 * Access: public
 * Input: none
 * Output:
 *     returns table number
 */
int Table::getTableNumber()
{
    return this->tableNumber;
}

/*
 * Method: getListOfOrderedItems
 * Class: Table
 * Description: get list Of Ordered Items
 * Access: public
 * Input: none
 * Output: none
 *     returns list Of Ordered Items
 */
vector<pair<int, pair<string, int>>> Table::getListOfOrderedItems()
{
    return this->listOfOrderedItems;
}