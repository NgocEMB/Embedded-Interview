/*
 * File: Manager.h
 * Author: Ngoc Nguyen
 * Date: 27/03/2023
 * Description: This is a header file for class "Manager"
 */
#pragma once

#include <string>
#include <vector>
#include "Item.h"
#include "Table.h"

using namespace std;

class Manager
{
private:
    // int numberOfTable;
public:
    // Manager();
    //shared database between manager and employee
    static vector<Table> listOfTable;
    static vector<Item> listOfItem;
    //methods
    void setNumberOfTable(const int desiredNumberOfTable);
    void addItem(const string nameOfItem, const double price);
    void adjustItem(const int id);
    void deleteItem(const int id);
    void showListOfItem();
};
