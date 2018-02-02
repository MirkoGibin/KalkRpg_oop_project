#ifndef MATHOP_H
#define MATHOP_H
#include<map>
#include<string>
#include<list>

namespace mathOp {

using std::map; using std::string; using std::list;

void doMultiplyOnMap(map<string, double>&m, double&toMultiply);

list<string> chiaviAmenoB(map<string, double>& A, map<string, double>& B);

list<string> chiaviAeB(map<string, double>& A, map<string, double>& B);

}
#endif // MATHOP_H
