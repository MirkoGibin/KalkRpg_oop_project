#include "memoryexception.h"

MemoryException::MemoryException(std::string str) : err(str) {}

std::string MemoryException::getError() const {
    if(err=="mv")
        return "La memoria e' vuota, non si possono leggere elementi";
}
