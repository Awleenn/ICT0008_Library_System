#ifndef BOOK_H
#define BOOK_H

#include <string>
#include "Author.h"
using namespace std;

class Book {
private:
    string title;
    Author author;
    string isbn;
    bool isAvailable;
    string dateAdd;

public:
    Book();

    void setBookDetails(string t, const Author& a, string i, string d, bool avail = true);
    void displayBookDetails() const;
    bool borrowBook();
    void returnBook();
    string getISBN() const;
};

#endif
