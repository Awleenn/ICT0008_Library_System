#include <iostream>
#include <iomanip>
#include <algorithm>
#include "Book.h"

using namespace std;

// Sorting function
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

    Author a1("Stanley Lippman");
    Author a2("Scott Meyers");
    Author a3("Robert Martin");
    Author a4("Fred Brooks");
    Author a5("Steve McConnell");

    library[0].setBookDetails("C++ Primer", a1, "105", "2024-01-01");
    library[1].setBookDetails("Effective C++", a2, "102", "2024-02-10");
    library[2].setBookDetails("Clean Code", a3, "101", "2024-03-15");
    library[3].setBookDetails("The Mythical Man-Month", a4, "104", "2024-04-20");
    library[4].setBookDetails("Code Complete", a5, "103", "2024-05-25");

    sortBookData(library, SIZE);

    string inputISBN;
    int action;

    cout << "Welcome to the Community Library System\n";

    while (true) {
        cout << "\nISBN      Title                    Author              Status\n";

        for (int i = 0; i < SIZE; i++) {
            library[i].displayBookDetails();
        }

        cout << "\nEnter ISBN (or '0' to exit): ";
        cin >> inputISBN;

        if (inputISBN == "0") break;

        bool found = false;

        for (int i = 0; i < SIZE; i++) {
            if (library[i].getISBN() == inputISBN) {
                found = true;

                cout << "Select Action: (1) Borrow (2) Return: ";
                cin >> action;

                if (action == 1) {
                    if (!library[i].borrowBook())
                        cout << "Error: Book unavailable\n";
                } else if (action == 2) {
                    library[i].returnBook();
                }
                break;
            }
        }

        if (!found) cout << "Error: ISBN not found\n";
    }

    return 0;
}
