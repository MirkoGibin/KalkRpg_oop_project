import java.util.HashMap;
import java.util.Map;

public class Oggetto implements Cloneable {
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

    spirito_="Spirito";

    stats=new HashMap<>();

    stats.put(spirito_, spirito);
}
    
}
