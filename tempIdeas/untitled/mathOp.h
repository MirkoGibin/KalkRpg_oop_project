#ifndef MATHOP_H
#define MATHOP_H
#include<map>
#include<string>
#include<list>

namespace mathOp {

using std::map; using std::string; using std::list;

void doMultiplyOnMap(map<string, float>&m, float&toMultiply);

list<string> chiaviAmenoB(map<string, float>& A, map<string, float>& B);

list<string> chiaviAeB(map<string, float>& A, map<string, float>& B);

}
#endif // MATHOP_H
