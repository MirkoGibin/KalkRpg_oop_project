#ifndef MEMORYEXCEPTION_H
#define MEMORYEXCEPTION_H
#include<iostream>
#include<string>
using std::string;

class MemoryException {
private:
    string err;
public:
    MemoryException(string str);

    string getError() const;
};

#endif // MEMORYEXCEPTION_H
