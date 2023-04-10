/*
 * File: Table.h
 * Author: Ngoc Nguyen
 * Date: 29/03/2023
 * Description: This is a header file for class "Table"
 */
#pragma once

#include <vector>
#include <iostream>

using namespace std;

class Table
{
private:
    int tableNumber;
    bool status;
    vector<pair<int, pair<string, int>>> listOfOrderedItems;  //{id, name, quantity}
public:
    static int count;
    Table();
    //setter
    void setStatus(bool status);
    void addItemToList(int id, string name, int quantity);
    void deleteListOrdredItem();
    //getter
    bool getStatus();
    vector<pair<int, pair<string, int>>> getListOfOrderedItems();
    int getTableNumber();
};