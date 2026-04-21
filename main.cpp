#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Author Class
class Author {
private:
    string name;

public:
    Author() : name("") {}

    Author(string n) : name(n) {}

    void setName(string n) {
        name = n;
    }

    string getName() const {
        return name;
    }
};

// Book Class
class Book {
private:
    string title;
    Author author; // Now using Author class
    string isbn;
    bool isAvailable;
    string dateAdd;

public:
    Book() : title(""), author(), isbn(""), isAvailable(true), dateAdd("") {}

    void setBookDetails(string t, Author a, string i, string d, bool avail = true) {
        title = t;
        author = a;
        isbn = i;
        dateAdd = d;
        isAvailable = avail;
    }

    void displayBookDetails() const {
        cout << left << setw(10) << isbn
             << setw(25) << title
             << setw(20) << author.getName()
             << (isAvailable ? "Available" : "Borrowed") << endl;
    }

    bool borrowBook() {
        if (isAvailable) {
            isAvailable = false;
            return true;
        }
        return false;
    }

    void returnBook() {
        isAvailable = true;
    }

    string getISBN() const {
        return isbn;
    }
};

// Sorting function (Bubble Sort)
void sortBookData(Book books[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (books[j].getISBN() > books[j + 1].getISBN()) {
                swap(books[j], books[j + 1]);
            }
        }
    }
}

int main() {
    const int SIZE = 5;
    Book library[SIZE];

    // Create Author objects
    Author a1("Stanley Lippman");
    Author a2("Scott Meyers");
    Author a3("Robert Martin");
    Author a4("Fred Brooks");
    Author a5("Steve McConnell");

    // Assign books with Author objects
    library[0].setBookDetails("C++ Primer", a1, "105", "2024-01-01");
    library[1].setBookDetails("Effective C++", a2, "102", "2024-02-10");
    library[2].setBookDetails("Clean Code", a3, "101", "2024-03-15");
    library[3].setBookDetails("The Mythical Man-Month", a4, "104", "2024-04-20");
    library[4].setBookDetails("Code Complete", a5, "103", "2024-05-25");

    // Sort books by ISBN
    sortBookData(library, SIZE);

    string inputISBN;
    int action;

    cout << "Welcome to the Community Library System" << endl;
    cout << "---------------------------------------" << endl;

    while (true) {
        cout << "\nCurrent Library Collection:" << endl;
        cout << left << setw(10) << "ISBN" 
             << setw(25) << "Title" 
             << setw(20) << "Author" 
             << "Status" << endl;

        for (int i = 0; i < SIZE; i++) {
            library[i].displayBookDetails();
        }

        cout << "\nEnter ISBN (or '0' to exit): ";
        cin >> inputISBN;

        if (inputISBN == "0") {
            break;
        }

        bool found = false;

        for (int i = 0; i < SIZE; i++) {
            if (library[i].getISBN() == inputISBN) {
                found = true;

                cout << "Select Action: (1) Borrow (2) Return: ";
                cin >> action;

                if (action == 1) {
                    if (library[i].borrowBook()) {
                        cout << "Success: You have borrowed the book." << endl;
                    } else {
                        cout << "Error: This book is currently unavailable." << endl;
                    }
                } else if (action == 2) {
                    library[i].returnBook();
                    cout << "Success: Book returned." << endl;
                }
                break;
            }
        }

        if (!found) {
            cout << "Error: ISBN not found." << endl;
        }
    }

    cout << "System shutting down. Goodbye!" << endl;
    return 0;
}
