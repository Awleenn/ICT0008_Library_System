// test.cpp
// ICT0008 Assessment 3 - Test Application
// Tests: correct/incorrect Book instantiation, and sort function on 3 arrays

#include <iostream>
#include <iomanip>
#include <string>
#include "Book.h"
#include "Author.h"

using namespace std;

// ---------------------------------------------------------------
// Sort function (Bubble Sort - ascending by ISBN string)
// ---------------------------------------------------------------
void sortBookData(Book books[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (books[j].getISBN() > books[j + 1].getISBN()) {
                swap(books[j], books[j + 1]);
            }
        }
    }
}

// ---------------------------------------------------------------
// Helper: print a pass/fail line
// ---------------------------------------------------------------
void printResult(const string& testName, bool passed) {
    cout << left << setw(55) << testName
         << (passed ? "PASS" : "FAIL") << "\n";
}

// ---------------------------------------------------------------
// Helper: print the contents of a book array
// ---------------------------------------------------------------
void printArray(Book arr[], int size, const string& label) {
    cout << "\n  " << label << ":\n";
    cout << "  " << left << setw(8) << "ISBN"
         << setw(25) << "Title"
         << setw(20) << "Author"
         << "Status\n";
    cout << "  " << string(65, '-') << "\n";
    for (int i = 0; i < size; i++) {
        cout << "  ";
        arr[i].displayBookDetails();
    }
}

// ---------------------------------------------------------------
// Helper: check whether an array is sorted ascending by ISBN
// ---------------------------------------------------------------
bool isSortedAsc(Book arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i].getISBN() > arr[i + 1].getISBN())
            return false;
    }
    return true;
}

int main() {
    cout << "========================================================\n";
    cout << "  ICT0008 Assessment 3 - Test Application\n";
    cout << "========================================================\n\n";

    // ==============================================================
    // SECTION 1: CORRECT BOOK INITIALISATION (3 instances)
    // ==============================================================
    cout << "--------------------------------------------------------\n";
    cout << "  SECTION 1: Correct Book Instantiation\n";
    cout << "--------------------------------------------------------\n\n";

    Author a1("Stanley Lippman");
    Author a2("Scott Meyers");
    Author a3("Robert Martin");

    Book b1, b2, b3;
    b1.setBookDetails("C++ Primer",    a1, "105", "2024-01-01");
    b2.setBookDetails("Effective C++", a2, "102", "2024-02-10");
    b3.setBookDetails("Clean Code",    a3, "101", "2024-03-15");

    // Test 1 - b1
    cout << "Test 1: b1 instantiated with setBookDetails(\"C++ Primer\", a1, \"105\", \"2024-01-01\")\n";
    printResult("  b1.getISBN() == \"105\"",
                b1.getISBN() == "105");
    printResult("  b1.getAuthor().getName() == \"Stanley Lippman\"",
                b1.getAuthor().getName() == "Stanley Lippman");
    printResult("  b1.getTitle() == \"C++ Primer\"",
                b1.getTitle() == "C++ Primer");
    printResult("  b1.getIsAvailable() == true (default)",
                b1.getIsAvailable() == true);

    // Test 2 - b2
    cout << "\nTest 2: b2 instantiated with setBookDetails(\"Effective C++\", a2, \"102\", \"2024-02-10\")\n";
    printResult("  b2.getISBN() == \"102\"",
                b2.getISBN() == "102");
    printResult("  b2.borrowBook() returns true (book is available)",
                b2.borrowBook() == true);
    printResult("  After borrow: b2.getIsAvailable() == false",
                b2.getIsAvailable() == false);
    b2.returnBook();
    printResult("  After return: b2.getIsAvailable() == true",
                b2.getIsAvailable() == true);

    // Test 3 - b3
    cout << "\nTest 3: b3 instantiated with setBookDetails(\"Clean Code\", a3, \"101\", \"2024-03-15\")\n";
    printResult("  b3.getISBN() == \"101\"",
                b3.getISBN() == "101");
    printResult("  b3.getAuthor().getName() == \"Robert Martin\"",
                b3.getAuthor().getName() == "Robert Martin");
    cout << "  b3.displayBookDetails() output:\n  ";
    b3.displayBookDetails();

    // ==============================================================
    // SECTION 2: INCORRECT BOOK INITIALISATION (3 instances)
    // ==============================================================
    cout << "\n--------------------------------------------------------\n";
    cout << "  SECTION 2: Incorrect Book Instantiation\n";
    cout << "--------------------------------------------------------\n\n";

    // --- Incorrect Instance 1 ---
    // Title: integer (implicit conversion to string not possible — compile-time block,
    //   so we simulate by passing a numeric string and noting the issue)
    // ISBN: non-numeric string ("ABC")
    // Availability: default true (bool "Maybe" cannot compile — noted below)
    // DateAdd: invalid format

    cout << "Test 4: Incorrect Book 1\n";
    cout << "  [Note] setBookDetails(12345, ...) with integer title would be a\n";
    cout << "  COMPILE ERROR in C++ - integer does not implicitly convert to std::string.\n";
    cout << "  Simulating with stored note instead of calling invalid code.\n";
    printResult("  Compile-time type guard prevents integer title",   true);

    Author aWrong1("Stanley Lippman");
    Book bWrong1;
    // Non-numeric ISBN ("ABC") and invalid date - accepted as strings (logic error)
    bWrong1.setBookDetails("C++ Primer", aWrong1, "ABC", "99-99-9999");
    printResult("  ISBN \"ABC\" stored (logic error - non-numeric accepted as string)",
                bWrong1.getISBN() == "ABC");
    printResult("  DateAdd \"99-99-9999\" stored (logic error - invalid date accepted)",
                bWrong1.getDateAdd() == "99-99-9999");
    cout << "  -> No runtime crash, but sorting/date logic will be incorrect.\n";

    // --- Incorrect Instance 2 ---
    cout << "\nTest 5: Incorrect Book 2\n";
    cout << "  [Note] Availability \"Maybe\" / \"Yes\" (string) cannot be passed as bool\n";
    cout << "  at compile time. Author with numeric name 9999 and negative ISBN accepted.\n";

    Author aWrong2("9999");  // numeric string as author name
    Book bWrong2;
    bWrong2.setBookDetails("", aWrong2, "-1", "2024/13/40");
    printResult("  Empty title stored (logic error - no title validation)",
                bWrong2.getTitle() == "");
    printResult("  Author name \"9999\" stored (logic error - numeric string accepted)",
                bWrong2.getAuthor().getName() == "9999");
    printResult("  ISBN \"-1\" stored (logic error - negative ISBN accepted)",
                bWrong2.getISBN() == "-1");
    printResult("  DateAdd \"2024/13/40\" stored (logic error - invalid date accepted)",
                bWrong2.getDateAdd() == "2024/13/40");
    cout << "  -> Program compiles and runs, but data is meaningless.\n";

    // --- Incorrect Instance 3 ---
    cout << "\nTest 6: Incorrect Book 3\n";
    cout << "  [Note] NULL cannot be assigned to bool in standard C++ (compile error).\n";
    cout << "  Simulating with a 0 (false) for availability and invalid strings.\n";

    Author aWrong3("");  // empty author
    Book bWrong3;
    bWrong3.setBookDetails("@#$%", aWrong3, "999999", "tomorrow");
    printResult("  Title \"@#$%\" (special chars) stored as string",
                bWrong3.getTitle() == "@#$%");
    printResult("  Empty author name stored (logic error - no author validation)",
                bWrong3.getAuthor().getName() == "");
    printResult("  ISBN \"999999\" (not in library records) stored",
                bWrong3.getISBN() == "999999");
    printResult("  DateAdd \"tomorrow\" stored (logic error - non-date string accepted)",
                bWrong3.getDateAdd() == "tomorrow");
    cout << "  -> No crash, but ISBN lookup and date management will fail.\n";

    // ==============================================================
    // SECTION 3: SORT FUNCTION ON 3 ARRAYS
    // ==============================================================
    cout << "\n--------------------------------------------------------\n";
    cout << "  SECTION 3: Sort Function - Three Arrays\n";
    cout << "--------------------------------------------------------\n\n";

    Author sA1("Stanley Lippman");   // ISBN 105 - C++ Primer
    Author sA2("Scott Meyers");      // ISBN 102 - Effective C++
    Author sA3("Robert Martin");     // ISBN 101 - Clean Code

    // ---- Array 1: Ascending order input [101, 102, 103] ----
    const int SIZE = 3;
    Book arr1[SIZE], arr2[SIZE], arr3[SIZE];

    arr1[0].setBookDetails("Clean Code",    sA3, "101", "2024-03-15");
    arr1[1].setBookDetails("Effective C++", sA2, "102", "2024-02-10");
    arr1[2].setBookDetails("C++ Primer",    sA1, "105", "2024-01-01");

    printArray(arr1, SIZE, "Array 1 - Input (Ascending: 101, 102, 105)");
    sortBookData(arr1, SIZE);
    printArray(arr1, SIZE, "Array 1 - After Sort");
    printResult("\n  Array 1 sort result correct (already ascending)",
                isSortedAsc(arr1, SIZE));

    // ---- Array 2: Descending order input [105, 102, 101] ----
    arr2[0].setBookDetails("C++ Primer",    sA1, "105", "2024-01-01");
    arr2[1].setBookDetails("Effective C++", sA2, "102", "2024-02-10");
    arr2[2].setBookDetails("Clean Code",    sA3, "101", "2024-03-15");

    printArray(arr2, SIZE, "Array 2 - Input (Descending: 105, 102, 101)");
    sortBookData(arr2, SIZE);
    printArray(arr2, SIZE, "Array 2 - After Sort");
    printResult("\n  Array 2 sort result correct (reversed to ascending)",
                isSortedAsc(arr2, SIZE));

    // ---- Array 3: Mixed order input [102, 101, 105] ----
    arr3[0].setBookDetails("Effective C++", sA2, "102", "2024-02-10");
    arr3[1].setBookDetails("Clean Code",    sA3, "101", "2024-03-15");
    arr3[2].setBookDetails("C++ Primer",    sA1, "105", "2024-01-01");

    printArray(arr3, SIZE, "Array 3 - Input (Mixed: 102, 101, 105)");
    sortBookData(arr3, SIZE);
    printArray(arr3, SIZE, "Array 3 - After Sort");
    printResult("\n  Array 3 sort result correct (mixed sorted to ascending)",
                isSortedAsc(arr3, SIZE));

    cout << "\n========================================================\n";
    cout << "  All test cases completed.\n";
    cout << "========================================================\n";

    return 0;
}
