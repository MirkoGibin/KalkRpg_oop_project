#ifndef MEMORYEXCEPTION_H
#define MEMORYEXCEPTION_H
#include<iostream>
#include<string>
using std::string;

class MemoryException {
private:
    string err;
public:
    MemoryException(string str) : err(str) {}

    string getError() const {
        if(err=="mv")
            return "La memoria e' vuota, non si possono leggere elementi";
    }
};

#endif // MEMORYEXCEPTION_H
