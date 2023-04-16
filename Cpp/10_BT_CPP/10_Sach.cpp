#include <iostream>
#include <math.h>
#include <vector>
#include <string.h>

using namespace std;

class Book {
private:
    char* name;
    char* author;
    int year;
    int quantity;
public:
    Book(char* name, char* author, int year, int quantity);
    char* getName();
    char* getAuthor();
    int getYear();
    int getQuantity();
    void setQuantity(int quan);
};

Book::Book(char* name, char* author, int year, int quantity) {
    this->name = name;
    this->author = author;
    this->year = year;
    this->quantity = quantity;
}

char* Book::getName() {
    return name;
}

char* Book::getAuthor() {
    return author;
}

int Book::getYear() {
    return year;
}

int Book::getQuantity() {
    return quantity;
}

void Book::setQuantity(int quan) {
    quantity = quan;
}

class List {
private:
    vector<Book> list;
public:
    void addBook(Book item);
    void borrowBook(char* name);
    void returnBook(char* name);
    void printList();
};

void List::addBook(Book item) {
    list.push_back(item);
}

void List::borrowBook(char name[]) {
    for(auto &temp : list) {
        if(strcmp(temp.getName(), name) == 0) {
            if(temp.getQuantity() > 0) {
                temp.setQuantity(temp.getQuantity() - 1);
                cout << "Da muon!" << endl;
                return;
            }
            else {
                cout << "Da het sach!" << endl;
                return;
            }
        }
    }
    cout << "Ten sach khong dung!" << endl;
    return;
}
void List::returnBook(char* name) {
    for(auto &temp : list) {
        if(strcmp(temp.getName(), name) == 0) {
            temp.setQuantity(temp.getQuantity() + 1);
            cout << "Da tra!" << endl;
            return;
        }
    }
    cout << "Ten sach khong dung!" << endl;
    return;
}

void List::printList() {
    printf("%20s%20s%8s%5s\n", "Ten sach", "Ten tac gia", "Nam XB", "Slg");
    for(auto temp : list) {
        printf("%20s%20s%8d%5d\n", temp.getName(), temp.getAuthor(), temp.getYear(), temp.getQuantity());
    }
}

int main() {
    Book toan("Toan", "Nguyen Van Ngoc", 1998, 10);
    Book tv("Tieng viet", "Nguyen Van Hoang", 2000, 8);
    Book ta("Ly", "Nguyen Van Tung", 2007, 5);
    List lib;
    
    lib.addBook(toan);
    lib.addBook(tv);
    lib.addBook(ta);

    lib.printList();
    lib.borrowBook("Toan");
    lib.borrowBook("Ly");
    lib.printList();
    lib.returnBook("Toan");
    lib.printList();

    return 0;
}