#include <iostream>
#include <iomanip>
#include "Book.h"

using namespace std;

Book::Book() : title(""), author(), isbn(""), isAvailable(true), dateAdd("") {}

void Book::setBookDetails(string t, const Author& a, string i, string d, bool avail) {
    title = t;
    author = a;
    isbn = i;
    dateAdd = d;
    isAvailable = avail;
}

void Book::displayBookDetails() const {
    cout << left << setw(10) << isbn
         << setw(25) << title
         << setw(20) << author.getName()
         << (isAvailable ? "Available" : "Borrowed") << endl;
}

bool Book::borrowBook() {
    if (isAvailable) {
        isAvailable = false;
        return true;
    }
    return false;
}

void Book::returnBook() {
    isAvailable = true;
}

string Book::getISBN() const {
    return isbn;
}
