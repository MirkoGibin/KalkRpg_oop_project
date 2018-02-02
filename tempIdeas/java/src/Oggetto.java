import javafx.util.Pair;

import java.util.HashMap;
import java.util.Map;

abstract public class Oggetto implements Cloneable {
private Integer livello_;
private Integer rarita_;

private String spirito_;

/* parameters inside stats in Oggetto are:
 * spirito
 */

private Map<String, Double> stats;

public Oggetto(Integer livello, Integer rarita, Double spirito) {
    livello_=livello;
    rarita_=rarita;
    spirito_= "Spirito";

    stats=new HashMap<>();

    stats.put(spirito_, spirito);
    //normalizza
}

//METODI DI SET-------------------------------------------------
public void setlivello(Integer livello) {
    livello_=livello;
}
public void setRarita(Integer rarita) {
    rarita_=rarita;
}
public void insertStat(String str, Double db) {
    stats.putIfAbsent(str, db);
}
public void incrementStat(String str, Double db) {
    Double ris=stats.get(str);
    ris+=db;
    stats.put(str, db);
}
public boolean modifyStat(String str, Double db) {
    boolean trovata=false;
    if(stats.containsValue(str)) {
        stats.put(str, db);
        trovata=true;
    }
    return trovata;
}

//METODI DI GET---------------------------------------------
    public Pair<String, String> findMaxStat() {
    Double max =-1.0;
    Double min=Double.MAX_VALUE;

    String statMax =new String();
    String statMin = new String();

    for(Map.Entry<String, Double> entry : stats.entrySet()) {
        if(entry.getValue() > max) {
            max=entry.getValue();
            statMax=entry.getKey();
        }
        else {
            if(entry.getValue()<=min) {
                min=entry.getValue();
                statMin=entry.getKey();
            }
        }
    }
    return new Pair<String, String>(statMin, statMax);
    }
}
