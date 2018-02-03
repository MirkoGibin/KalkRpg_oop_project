public class Pietra extends Oggetto {
    /* parameters inside stats in Oggetto are:
     * spirito
     * attacco
     * durezza
     */

    private String durezza_;

    public Pietra(Integer livello, Integer rarita, Double spirito, Double durezza) {
        super(livello,rarita, spirito);
        durezza_="Durezza";
        insertStat(durezza_, durezza);
        sanitizeInput();
    }

    //METODI DI GET------------------------------
    Double getDurezza() {
        return getValoreStat(durezza_);
    }
    //METODI DI SET------------------------------
    void editDurezza(Double val) {
        incrementStat(durezza_,val);
    }


    public Pietra clone() {
        return new Pietra(getLivello(), getRarita(), getSpirito(), getDurezza());
    }

    public Double ricicla() {
        return calcolaMana()/2.0 + getValoreStat(durezza_)*getRarita();
    }
    public void potenzia(Double mana, String parametro) {
        //da implementare
    }

}
