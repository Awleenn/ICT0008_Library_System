#include "Author.h"

Author::Author() : name("") {}

Author::Author(string n) : name(n) {}

void Author::setName(string n) {
    name = n;
}

string Author::getName() const {
    return name;
}
