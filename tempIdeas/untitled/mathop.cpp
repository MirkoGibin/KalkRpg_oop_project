#ifndef MATHOP_CPP
#define MATHOP_CPP
#include"mathOp.h"
#include<list>
#include<map>
#include<string>

using std::list; using std::map; using std::string;

void mathOp::doMultiplyOnMap(map<std::__cxx11::string, double> &m, double &toMultiply) {
    for(map<string, double>::const_iterator it= m.begin(); it!=m.end(); ++it) {
        m[it->first] = it->second * toMultiply; // percentuale di partecipazione della statistica sul mana
    }
}

list<std::__cxx11::string> mathOp::chiaviAmenoB(map<std::__cxx11::string, double> &A, map<std::__cxx11::string, double> &B) {
    list<string> AmenoB;
    for(map<string, double>::const_iterator it=A.begin(); it!=A.end(); ++it)
        if(!B.count(it->first))
            AmenoB.push_back(it->first);
    return AmenoB;
}

list<std::__cxx11::string> mathOp::chiaviAeB(map<std::__cxx11::string, double> &A, map<std::__cxx11::string, double> &B) {
    list<string> AeB;
    for(map<string, double>::const_iterator it=A.begin(); it!=A.end(); ++it)
        if(B.count(it->first))
            AeB.push_back(it->first);
    return AeB;
}

#endif //MATHOP_CPP
