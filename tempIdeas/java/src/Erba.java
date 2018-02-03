public class Erba extends Oggetto {
    String vitalita_ ;

    public Erba(Integer livello, Integer rarita, Double spirito, Double vitalita) {
        super(livello,rarita, spirito);
        vitalita_="Vitalità";
        insertStat(vitalita_, vitalita);
        sanitizeInput();
    }

    //METODI DI GET

    public Double getVitalita() {
        return getValoreStat(vitalita_);
    }

    //METODI DI SET
    public Erba clone() {
        return new Erba(getLivello(), getRarita(), getSpirito(), getVitalita());
    }

    //OPERAZIONI

    public Double ricicla() {
        return calcolaMana() / 2 *getValoreStat(vitalita_) * getRarita();
    }

    public void potenzia(Double mana, String parametro) {

        int divisore = 10;
        double incremento = mana / getLivello();

        incrementStat(vitalita_, incremento * getRarita() / divisore);
        incrementStat(parametro, incremento);

        normalizza();
    }

    public void potenzia(Double mana) {
        int divisore = 10;
        double incremento = mana / getLivello();

        List<String> parametri = getListaStats();
        incremento = incremento / parametri.

    }






}
