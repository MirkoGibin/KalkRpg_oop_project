import javafx.util.Pair;

import java.util.*;

abstract public class Oggetto implements Cloneable {
    private Integer livello_;
    private Integer rarita_;
    private String spirito_;

/* parameters inside stats in Oggetto are:
 * spirito
 */
    private Map<String, Double> stats;

    //PRIVATE METHODS-------------------------------------------------------------------

    /**
     * @param m Makes side effects on m Map multiplying every stat with toMultiply
     * @param toMultiply parameters which is multiplied in every stat
     */
    private static void doMultiplyOnMap(Map<String, Double> m, Double toMultiply) {
        m.forEach((k,v)->
                m.put(k,v*toMultiply)
        );
    }

    /**
     *
     * @param A Map<String, Double>
     * @param B Map<String, Double>
     * @return List<String> with every key which is present in A but not in B
     */
    private static List<String> chiaviAmenoB(Map<String, Double> A, Map<String, Double> B) {
        List<String> a= new LinkedList<>(A.keySet());
        List<String> b=new LinkedList<>(B.keySet());
        a.removeAll(b);
        return a;
    }

    /**
     * @param A
     * @param B
     * @return Returns List<String> with every key which is present in A&B
     */
    private static List<String> chiaviAeB(Map<String, Double> A, Map<String, Double> B) {
        List<String> a= new LinkedList<>(A.keySet());
        List<String> b=new LinkedList<>(B.keySet());
        a.retainAll(b);
        return a;
    }

    //COSTRUTTORI------------------------------------------------------
    public Oggetto() {
        this(1, 1, 1.0);
    }

    /**
     *
     * @param livello
     * @param rarita
     * @param spirito Is put in stats
     */
    public Oggetto(Integer livello, Integer rarita, Double spirito) {
        livello_=livello;
        rarita_=rarita;
        spirito_= "Spirito";

        stats=new HashMap<>();

        stats.put(spirito_, spirito);
        sanitizeInput();
    }

    //METODI DI SET-------------------------------------------------
    public void setLivello(Integer livello) {
        livello_=livello;
    }
    public void setRarita(Integer rarita) {
        rarita_=rarita;
    }
    public void insertStat(String str, Double db) {
        stats.putIfAbsent(str, db);
    }
    public void incrementStat(String str, Double db) {
        stats.put(str, stats.get(str)+db);
    }
    public boolean modifyStat(String str, Double db) {
        boolean trovata=false;
        if(stats.containsKey(str)) {
            stats.put(str, db);
            trovata=true;
        }
        return trovata;
    }

    //METODI DI GET---------------------------------------------

    /**
     *
      * @return restituisce due parametri: il primo è quello a valore minimo, il secondo quello a valore massimo
     */
    public Pair<String, String> findMinMaxStat() {
        Double max =-1.0;
        Double min=Double.MAX_VALUE;

        String statMax =new String();
        String statMin = new String();

        int counter=0;

        for(Map.Entry<String, Double> entry : stats.entrySet()) {
            if (counter == 0) {
                statMax = statMin = entry.getKey();
                max = min = entry.getValue();
                counter++;
            } else {
                if (entry.getValue() > max) {
                    max = entry.getValue();
                    statMax = entry.getKey();
                } else {
                    if (entry.getValue() <= min) {
                        min = entry.getValue();
                        statMin = entry.getKey();
                    }
                }
            }
        }
        return new Pair<String, String>(statMin, statMax);
    }

    public Integer getLivello() {
        return livello_;
    }
    public Integer getRarita() {
        return rarita_;
    }
    public Double getValoreStat(String str) {
        return stats.get(str);
    }
    public Double getSpirito() {
        return getValoreStat(spirito_);
    }
    public List<String> getListaStats() {
        return new LinkedList<String>(stats.keySet());
    }
    public Double getSommaStats() {
        return stats
                .values()
                .stream()
                .mapToDouble(f->f)
                .sum();

        /*Double sum =0.0;
        for(Map.Entry<String, Double> entry : stats.entrySet())
            sum=sum+entry.getValue();
        return sum;
        */
    }
    public Double calcolaMana() {
        return getSommaStats()*getLivello();
    }

    //OPERAZIONI-----------------------------------------------
    public void normalizza() {
        Integer maxStat=150;
        Integer s= getLivello()*maxStat*stats.size();
        if(s <= calcolaMana()) {
            Double percentualeRiduzione=s/calcolaMana();
            doMultiplyOnMap(stats, percentualeRiduzione);
        }
    }

    public void sanitizeInput() {
        livello_=sanitizeLivRar(livello_);
        rarita_=sanitizeLivRar(rarita_);

        for(Map.Entry<String, Double> entry : stats.entrySet()) {
            if (entry.getValue() < 1) stats.put(entry.getKey(), 1.0);
            else if (entry.getValue() > 150) stats.put(entry.getKey(), 150.0);
        }
        if(getSommaStats() > 150.0*livello_*stats.size()) normalizza();
    }

    static Double sanitizeMana(Double mana) {
        if(mana>60000.0) mana=6000.0;
        else if(mana<1) mana=1.0;
        return mana;
    }

    static Integer sanitizeLivRar(Integer l) {
        if(l<1) l=1;
        else if(l>10) l=10;
        return l;
    }


    /**
     * Detta A mappa dell'oggetto di invocazione, B mappa del parametro:
     * Delle statistiche condivise tra A e B, fa la media.
     * Delle statistiche particolari di B, fa la somma e la divide per il numero di statistiche particolari di A
     * Fa la media della somma tra le statistiche particolari di A e la somma divisa precedentemente.
     *
     * @param o object we want to combine with the parameter we invoked
     */
    void combina(Oggetto o) {
        Map<String, Double> invoMap = new HashMap<String, Double>(stats);
        Map<String, Double> paraMap = new HashMap<String, Double>(o.stats);

        Double multiInv=getLivello()/calcolaMana();
        Double multiPara=o.getLivello()/o.calcolaMana();

        doMultiplyOnMap(invoMap, multiInv);
        doMultiplyOnMap(paraMap, multiPara);;

        List<String> invoMENOpara=chiaviAmenoB(invoMap, paraMap);
        List<String> paraMENOinvo=chiaviAmenoB(paraMap, invoMap);
        List<String> paraEinvo=chiaviAeB(invoMap, paraMap);

        paraEinvo.stream().forEach(s->invoMap.put(s,(invoMap.get(s) + paraMap.get(s))/2));
        Double daDistribuire=paraMENOinvo.stream().mapToDouble(paraMap::get).sum()/invoMENOpara.size();

        invoMENOpara.stream().forEach(s->invoMap.put(s,(invoMap.get(s) + daDistribuire)/2));

        stats.forEach((k,v)->
            stats.put(k, stats.get(k) * getLivello() + invoMap.get(k) * o.calcolaMana())
        );
        normalizza();
    }

    public void trasformaDa(Oggetto o) throws OperationException {
        if(getListaStats().size() > o.getListaStats().size()) throw new OperationException(OperationException.ecc.trasformazione);

        setLivello(o.getLivello());
        setRarita(o.getRarita());
        List<String> parametri=o.getListaStats();

        //DA VEDERE SE FUNZIONA
        Double val = parametri
                .stream()
                .filter(s->!modifyStat(s, o.getValoreStat(s)/2))
                .mapToDouble(s->o.getValoreStat(s))
                .sum();

       /* Double val =0.0;
        for(String s : parametri) {
            if(!modifyStat(s, o.getValoreStat(s)/2))
                val=val+o.getValoreStat(s);

        }*/
        parametri.clear();

        if(val > 0) {
            stats.forEach((k,v) -> {
                if (v == 1.0) parametri.add(k);
            });
        }
        Integer par=parametri.size();
        if(par>0){
            val=val/par;
            final Double d = val;
            parametri.forEach(k ->
                    modifyStat(k, d*getRarita())
            );
        }
        normalizza();
    }

    public void crea(Double mana, Integer livello, Integer rarita, String statistica) {
        livello=sanitizeLivRar(livello);
        rarita=sanitizeLivRar(rarita);
        mana=sanitizeMana(mana);

        setLivello(livello);
        setRarita(rarita);

        List<String> parametri = getListaStats();
        Double sumStats=mana/(livello*rarita);

        if(parametri.contains(statistica)) {
            if(sumStats < 2) sumStats=2.0;
            modifyStat(statistica, sumStats/2);
            sumStats=sumStats/2;
            parametri.remove(statistica);
        }

        sumStats=sumStats/parametri.size();
        if(sumStats < 1) sumStats = 1.0;

        final Double s=sumStats;
        parametri.forEach(k ->
            modifyStat(k,s)
        );

        normalizza();
    }

    public void crea(Double mana, Integer livello, Integer rarita) {
        crea(mana, livello, rarita, "");
    }

    @Override
    public String toString() {
        String s = getClass().getName() + ":" +
                "\nLivello: \t" + livello_.toString() +
                "\nRarità: \t" + rarita_.toString() + "\n";

        for (Map.Entry<String, Double> entry : stats.entrySet()) {
            s = s + entry.getKey() + ": \t" + entry.getValue().toString() + " \n";
        }
        s = s + "\n";

        return s;
    }

    //ABSTRACT METHODS
    abstract public Double ricicla();
    abstract public void potenzia(Double mana, String parametro);
    abstract public void potenzia(Double mana);

    /**
     *
     * @return clone
     */
    @Override
    abstract public Oggetto clone();

}
