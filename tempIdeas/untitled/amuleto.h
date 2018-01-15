#ifndef AMULETO_H
#define AMULETO_H

#include"osso.h"
#include"cristallo.h"
#include"unguento.h"

class Amuleto : public Osso {
private:
    /* parameters inside stats in Amuleto:
     * spirito
     * attacco
     * difesa
     * fortuna
     */

public:
    Amuleto(int livello,
            int rarita,
            float spirito,
            float attacco,
            float difesa,
            float fortuna) : Osso(livello,rarita,spirito,attacco,difesa) {
        insertStat("fortuna", fortuna);
    }
    float getFortuna() const {
        return getValoreStat("fortuna");
    }

    float ricicla() {

    }

    void ottieniDa(Cristallo* cristallo) {

    }

    void ottieniDa(Unguento* unguento) {

    }

    void EstraiDa(Osso* osso) {
        if(dynamic_cast<Osso*>(osso)) {

        } else {
            //lancia eccezione per parametro illegale
        }
    }
};

#endif // AMULETO_H
