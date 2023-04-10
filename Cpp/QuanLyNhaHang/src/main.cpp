/*
 * File: main.cpp
 * Author: Ngoc Nguyen
 * Date: 27/03/2023
 * Description: This is a main source file
 */
#include "../inc/Employee.h"
#include "../inc/Manager.h"
#include <iomanip>
    
//main view macros  
#define EXIT            0
#define MANAGER         1
#define EMPLOYEE        2

//manager macros
#define RETURN          0
#define SET_NUM_TABLE   1
#define ADD_ITEM        2
#define ADJ_ITEM        3
#define DEL_ITEM        4
#define LIST_ITEM       5

//Employee macros
#define TAKE_ORDER      1
#define SHOW_BILL       2
#define CHECK_OUT       3

//another macros
#define CONTINUE        1
#define NONE            -1
#define INVALID         -1
#define AVAILABLE       true
#define OCCUPIED        false
#define NOT_EMPTY       true
#define EMPTY           false

/*
 * Function: checkListtable
 * Description: check if the list of the tables is empty or not
 * Input: none
 * Output: 
 *     returns status of the list
 */
bool checkListTable()
{
    if (Manager::listOfTable.size() == 0)                                            
    {                                                                                
        cout << "No have the list of tables yet! Please ask your manager." << endl;
        return EMPTY;
    }
    else return NOT_EMPTY;
    
}

/*
 * Function: checkListItem
 * Description: check if the list of the items is empty or not
 * Input: none
 * Output: 
 *     returns status of the list
 */
bool checkListItem()
{
    if (Manager::listOfItem.size() == 0)                                            
    {                                                                                
        cout << "The list of items is empty! Please ask your manager." << endl;
        return EMPTY;
    }
    else return NOT_EMPTY;
    
}

/*
 * Function: isContinue
 * Description: check if the user want to continue this option or not
 * Input: 
 *     <1> option - option "return" or "continue"
 * Output: 
 *     returns the selection of user
 */
int isContinue(int option) {
    int key;
    do
    {
        cout << "0: Return\n";
        cout << "--> Your select: ";
        cin >> key;
        cin.ignore(256, '\n');
        //if the input key is invalid
        if(key != option)
        {
            cout << "Invalid select! Please select again." << endl;
        }
    } while (key != option);
    return key;
}

/*
 * Function: isContinue
 * Description: check if the user want to continue this option or not
 * Input: 
 *     <1> option1 - option "return" or "continue"
 *     <1> option2 - option "return" or "continue"
 * Output: 
 *     returns the selection of user
 */
int isContinue(int option1, int option2) {
    int key;
    do
    {
        cout << "1: Continue\n0: Return\n";
        cout << "--> Your select: ";
        cin >> key;
        cin.ignore(256, '\n');
        //if the input key is invalid
        if(key != option1 && key != option2)
        {
            cout << "Invalid select! Please select again." << endl;
        }
    } while (key != option1 && key != option2);
    return key;
}

/********************** MAIN FUNCTION **********************/
int main(int argc, char const *argv[])
{
    int key;                //input key for user
    Manager manager;        //a manager
    Employee employee;      //a employee

    do
    {
        cout << "\n=========> MAIN SCREEN <=========\n";
        cout << "\n1: Manager\n2: Employee\n0: Exit program\n--> Your select: ";
        cin >> key;             //select option
        cin.ignore(256, '\n');

        switch (key)
        {
        case MANAGER:                   //if select as manager
        {
            do
            {
                cout << "\n=========> MANAGER <=========\n";
                cout << "1: Set number of tables\n2: Add a new item\n3: Adjust info item\n";
                cout << "4: Delete item in the list\n5: List of items\n0: Return main view\n";
                cout << "--> Your select: ";
                cin >> key;
                cin.ignore(256, '\n');
                
                switch (key)
                {
                case RETURN:            //if select to return
                {
                    break;
                }
                case SET_NUM_TABLE:     //if select to set number of tables
                {
                    int numTable;
                    cout << "Enter number of tables: ";
                    cin >> numTable;                        //enter the number of tables
                    cin.ignore(256, '\n');
                    manager.setNumberOfTable(numTable);     //set the number of tables
                    break;
                }
                case ADD_ITEM:          //if select to add a new item
                {
                    int privateKey;
                    do
                    {
                        cout << "\n=========> ADD ITEM <=========\n";
                        string itemName;
                        double price;
                        cout << "Enter the name: ";         //enter the name of item
                        getline(cin, itemName);
                        cout << "Enter the price: ";        //enter the price of item
                        cin >> price;
                        cin.ignore(256, '\n');
                        manager.addItem(itemName, price);   //push the new item into the list

                        //Continue or not
                        privateKey = isContinue(RETURN, CONTINUE);
                    } while (privateKey == CONTINUE);
                    break;
                }
                case ADJ_ITEM:          //if select to adjust for an item
                {
                    int privateKey;
                    do
                    {
                        cout << "\n=========> ADJUST ITEM <=========\n";
                        if(checkListItem() == EMPTY) break;
                        int id;
                        cout << "Enter the item ID: ";
                        cin >> id;                          //enter the id of item you want to adjust
                        cin.ignore(256, '\n');
                        manager.adjustItem(id);

                        //Continue or not
                        privateKey = isContinue(RETURN, CONTINUE);
                    } while (privateKey == CONTINUE);
                    break;
                }
                case DEL_ITEM:          //if select to delete an item
                {
                    int privateKey;
                    do
                    {
                        cout << "\n=========> DELETE ITEM <=========\n";
                        if(checkListItem() == EMPTY) break;
                        int id;
                        cout << "Enter the item ID: ";      //enter the id of item you want to delete
                        cin >> id;
                        cin.ignore(256, '\n');
                        manager.deleteItem(id);             //delete the item

                        //Continue or not
                        privateKey = isContinue(RETURN, CONTINUE);
                    } while (privateKey == CONTINUE);
                    break;
                }
                case LIST_ITEM:         //if select to display the list of items
                {
                    cout << "\n=========> LIST OF ITEMS <=========\n";
                    if(checkListItem() == EMPTY) break;
                    manager.showListOfItem();               //display the list of the items
                    //Continue or not
                    isContinue(RETURN);
                    break;
                }
                default:
                    cout << "Invalid select! Please select again." << endl;
                    break;
                }
            } while (key != RETURN);
            key = -1;
            break;
        }
        case EMPLOYEE:                   //if select as employee
        {
            int tableNumber;
            do
            {
                cout << "\n=========> EMPLOYEE <=========\n";
                if(checkListTable() == EMPTY) break;
                if(checkListItem() == EMPTY) break;
                employee.mainScreen();                  //display main screen to choose a table 
                cout << "0: Return\nSelect table: ";
                cin >> tableNumber;                     //enter the table number to choose
                cin.ignore(256, '\n');

                //restrict table number input to invalid number
                if((tableNumber < 0) || (tableNumber > Manager::listOfTable.size())) 
                {
                    cout << "Invalid select! Please select again." << endl;
                }
                else if(tableNumber == 0) break;        //when you want to return the main screen
                else {                                  //if table number input is valid number
                    employee.selectTable(tableNumber);  //select that table
                    do
                    {
                        cout << "\n=========> TABLE " << tableNumber << " <=========\n";
                        cout << "1: Take order\n2: Show the list of ordered items\n3: Check out\n";
                        cout << "0: Return\n";
                        cout << "--> Your select: ";
                        cin >> key;                     //enter option
                        cin.ignore(256, '\n');

                        switch (key)
                        {
                        case RETURN:            //if select to return
                            break;
                        case TAKE_ORDER:        //if select to order
                        {
                            int privateKey;
                            do
                            {
                                cout << "\n=========> ORDER <=========\n";
                                int id, quantity;
                                cout << "Enter the item ID: ";
                                cin >> id;
                                cout << "Enter the quantity: ";
                                cin >> quantity;
                                cin.ignore(256, '\n');
                                employee.takeOrder(tableNumber, id, quantity);

                                //Continue or not
                                privateKey = isContinue(RETURN, CONTINUE);
                            } while (privateKey == CONTINUE);
                            break;
                        }
                        case SHOW_BILL:         //if select to display the list of ordered items
                        {
                            cout << "\n=========> SHOW ORDERED LIST <=========\n";
                            employee.showBill(tableNumber);
                            //Continue or not
                            isContinue(RETURN);
                            break;
                        }
                        case CHECK_OUT:         //if select to check out
                        {
                            cout << "\n=========> CHECK OUT <=========\n";
                            employee.checkOut(tableNumber);
                            key = RETURN;
                            break;
                        }
                        default:                //if select is invalid  
                            cout << "Invalid select! Please select again." << endl;
                            break;
                        }
                    } while (key != RETURN);
                }
            } while (tableNumber != 0);
            key = -1;
            break;
        }
        case EXIT:          //if select to exit the application 
            break;
        default:            //if select is invalid  
            cout << "Invalid select! Please select again." << endl;
            break;
        }
    } while (key != EXIT);

    return 0;
}
