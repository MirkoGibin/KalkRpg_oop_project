#ifndef MATHOP_H
#define MATHOP_H
#include<map>
#include<string>
#include<list>
#include<iostream>

namespace mathOp {

    using std::map; using std::string; using std::list;

    void doMultiplyOnMap(map<string, float>&, float&);

    list<string>* chiaviAmenoB(map<string, float>&, map<string, float>&);

    list<string>* chiaviAeB(map<string, float>&, map<string, float>&);


}
#endif // MATHOP_H
