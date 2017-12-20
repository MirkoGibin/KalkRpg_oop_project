#include"mathOp.h"
#include<list>
#include<string>

using std::list; using std::string;

void mathOp::doMultiplyOnMap(map<string, float>& m, float& toMultiply) {
    for(map<string, float>::const_iterator it= m.begin(); it!=m.end(); ++it) {
        m[it->first] = it->second * toMultiply; // percentuale di partecipazione della statistica sul mana
    }
}

list<string>* mathOp::chiaviAmenoB(map<string, float>& A, map<string, float>& B) {
    list<string>* AmenoB=new list<string>();
    for(map<string, float>::const_iterator it=A.begin(); it!=A.end(); ++it)
        if(!B.count(it->first))
            AmenoB->push_back(it->first);
    return AmenoB;
}

list<string>* mathOp::chiaviAeB(map<string, float>& A, map<string, float>& B) {
    list<string>* AeB=new list<string>();
    for(map<string, float>::const_iterator it=A.begin(); it!=A.end(); ++it)
        if(B.count(it->first))
            AeB->push_back(it->first);
    return AeB;
}
