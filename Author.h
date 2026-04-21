#ifndef AUTHOR_H
#define AUTHOR_H

#include <string>
using namespace std;

class Author {
private:
    string name;

public:
    Author();
    Author(string n);

    void setName(string n);
    string getName() const;
};

#endif
