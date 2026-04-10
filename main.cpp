#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class Book {
private:
    string title, author, isbn, dateAdd;
    bool availability;

public:
    Book(string t, string a, string i, string d) 
        : title(t), author(a), isbn(i), dateAdd(d), availability(true) {}

    string getISBN() const { return isbn; }
    bool isAvailable() const { return availability; }
    
    void borrowBook() { availability = false; }
    
    void displayBookDetails() const {
        cout << "ISBN: " << isbn << " | Title: " << title 
             << " | Author: " << author 
             << " | Status: " << (availability ? "Available" : "Borrowed") << endl;
    }
};

bool compareBooks(const Book& a, const Book& b) {
    return a.getISBN() < b.getISBN();
}

int main() {
    vector<Book> library;
    library.push_back(Book("C++ Basics", "John Smith", "105", "2024-01-01"));
    library.push_back(Book("OOP Design", "Jane Doe", "102", "2024-02-10"));
    library.push_back(Book("Data Structures", "Alan Turing", "101", "2024-03-15"));
    library.push_back(Book("Advanced C++", "Bjarne S.", "104", "2024-04-20"));
    library.push_back(Book("Logic Pro", "Grace Hopper", "103", "2024-05-05"));

    // Sort by ISBN
    sort(library.begin(), library.end(), compareBooks);

    string input;
    while (true) {
        cout << "\n--- Current Library Collection ---\n";
        for (const auto& b : library) b.displayBookDetails();

        cout << "\nEnter ISBN to borrow (0 to exit): ";
        cin >> input;

        if (input == "0") break;

        bool found = false;
        for (auto& b : library) {
            if (b.getISBN() == input) {
                found = true;
                if (b.isAvailable()) {
                    b.borrowBook();
                    cout << "SUCCESS: You have borrowed the book.\n";
                } else {
                    cout << "ERROR: This book is already borrowed.\n";
                }
                break;
            }
        }
        if (!found) cout << "ERROR: Book with ISBN " << input << " not found.\n";
    }
    return 0;
}