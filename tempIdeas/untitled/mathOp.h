#ifndef MATHOP_H
#define MATHOP_H
#include<map>
#include<string>
#include<list>
#include<iostream>

namespace mathOp {

using std::map; using std::string; using std::list;

void doMultiplyOnMap(map<string, float>&, float&) {
    for(map<string, float>::const_iterator it= m.begin(); it!=m.end(); ++it) {
        m[it->first] = it->second * toMultiply; // percentuale di partecipazione della statistica sul mana
    }
}

list<string>* chiaviAmenoB(map<string, float>&, map<string, float>&) {
    list<string>* AmenoB=new list<string>();
    for(map<string, float>::const_iterator it=A.begin(); it!=A.end(); ++it)
        if(!B.count(it->first))
            AmenoB->push_back(it->first);
    return AmenoB;
}

    list<string>* chiaviAeB(map<string, float>&, map<string, float>&) {
        list<string>* AeB=new list<string>();
        for(map<string, float>::const_iterator it=A.begin(); it!=A.end(); ++it)
            if(B.count(it->first))
                AeB->push_back(it->first);
        return AeB;
    }

}
#endif // MATHOP_H
