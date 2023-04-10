/*
 * File: Employee.h
 * Author: Ngoc Nguyen
 * Date: 27/03/2023
 * Description: This is a header file for class "Employee"
 */
#pragma once

class Employee
{
private:
public:
    void mainScreen();
    void selectTable(int tableNumber);
    void takeOrder(int tableNumber, int itemID, int quantity);
    void showBill(int tableNumber);
    void checkOut(int tableNumber);
};