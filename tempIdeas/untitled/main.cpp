#include <iostream>
#include"oggetto.h"
#include"pietra.h"
#include"cristallo.h"

using namespace std;

int main() {

    Pietra* pie=new Pietra(1,20,0, 15, 50);
    Cristallo* cri=new Cristallo(5, 10, 0, 40, 2, 90);
    pie->combina(dynamic_cast<Oggetto*>(cri));

    cout<<pie->getDurezza()<<" "<<pie->getSpirito()<<" ";


}
