#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Book Class Definition [cite: 18]
class Book {
private:
    // Attributes [cite: 19-24]
    string title;
    string author;
    string isbn;
    bool isAvailable;
    string dateAdd;

public:
    // Default constructor
    Book() : title(""), author(""), isbn(""), isAvailable(true), dateAdd("") {}

    // setBookDetails method [cite: 28]
    void setBookDetails(string t, string a, string i, string d, bool avail = true) {
        title = t;
        author = a;
        isbn = i;
        dateAdd = d;
        isAvailable = avail;
    }

    // displayBookDetails method [cite: 29]
    void displayBookDetails() const {
        cout << left << setw(10) << isbn 
             << setw(25) << title 
             << setw(20) << author 
             << (isAvailable ? "Available" : "Borrowed") << endl;
    }

    // borrowBook method [cite: 30, 33]
    bool borrowBook() {
        if (isAvailable) {
            isAvailable = false;
            return true;
        }
        return false; // Validates availability before borrowing [cite: 33]
    }

    // returnBook method [cite: 31]
    void returnBook() {
        isAvailable = true;
    }

    // sortBookData method (Sorting by ISBN) 
    string getISBN() const { return isbn; }
};

// Global sort function for the array 
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
    // Task 2: Implementation [cite: 42, 43]
    // Initialize an array with 5 books [cite: 35]
    const int SIZE = 5;
    Book library[SIZE];

    library[0].setBookDetails("C++ Primer", "Stanley Lippman", "105", "2024-01-01");
    library[1].setBookDetails("Effective C++", "Scott Meyers", "102", "2024-02-10");
    library[2].setBookDetails("Clean Code", "Robert Martin", "101", "2024-03-15");
    library[3].setBookDetails("The Mythical Man-Month", "Fred Brooks", "104", "2024-04-20");
    library[4].setBookDetails("Code Complete", "Steve McConnell", "103", "2024-05-25");

    // Sort the book data by ISBN 
    sortBookData(library, SIZE);

    string inputISBN;
    int action;

    cout << "Welcome to the Community Library System" << endl;
    cout << "---------------------------------------" << endl;

    // Main Application Loop [cite: 34-37]
    while (true) {
        cout << "\nCurrent Library Collection:" << endl;
        cout << left << setw(10) << "ISBN" << setw(25) << "Title" << setw(20) << "Author" << "Status" << endl;
        for (int i = 0; i < SIZE; i++) {
            library[i].displayBookDetails();
        }

        // Prompt user for ISBN [cite: 35]
        cout << "\nEnter ISBN (or '0' to exit): ";
        cin >> inputISBN;

        // Program terminates when user enters "0" 
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
                        // Error message if unavailable [cite: 36]
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
