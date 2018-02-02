#ifndef MATHOP_H
#define MATHOP_H
#include<map>
#include<string>
#include<list>

namespace mathOp {

using std::map; using std::string; using std::list;

void doMultiplyOnMap(map<string, double>&, double&);

list<string> chiaviAmenoB(map<string, double>&, map<string, double>&);

list<string> chiaviAeB(map<string, double>&, map<string, double>&);

}
#endif // MATHOP_H
