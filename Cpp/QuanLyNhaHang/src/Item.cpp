/*
 * File: Item.cpp
 * Author: Ngoc Nguyen
 * Date: 27/03/2023
 * Description: This is a source file for class "Item"
 */

#include "../inc/Item.h"

//Initialize static variable id
int Item::count = 100;

/*
 * Constructor: Item
 * Description: Constructor of class "Item"
 * Input:
 * Output:
 */
Item::Item()
{
    //set id automatically when create a object of class "Item"
    this->id = count;
    ++count;
    //set default name and price
    name = "";
    price = 0;
}

/*
 * Method: setName
 * Description: set name of item
 * Input:
 * Output:
 */
void Item::setName(string name)
{
    //set name
    this->name = name;
}

/*
 * Method: setName
 * Description: set name of item
 * Input:
 * Output:
 */
void Item::setPrice(double price)
{
    //set price
    this->price = price;
}

/*
 * Method: getName
 * Description: get name of item
 * Input:
 * Output:
 *   returns name of item
 */
string Item::getName()
{
    return this->name;
}

/*
 * Method: getPrice
 * Description: get price of item
 * Input:
 * Output:
 *   returns price of item
 */
double Item::getPrice()
{
    return this->price;
}

/*
 * Method: getId
 * Description: get id of item
 * Input:
 * Output:
 *   returns id of item
 */
int Item::getId()
{
    return this->id;
}