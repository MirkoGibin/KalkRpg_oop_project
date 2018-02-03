import java.util.List;

public class Erba extends Oggetto {

    private String vitalita_ ;

    //COSTRUTTORI
    public Erba() {
        this(1,1,1.0,1.0);
    }

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
        return calcolaMana() / 2 + getValoreStat(vitalita_) * getRarita();
    }

    public void potenzia(Double mana, String parametro) {
        mana=sanitizeMana(mana);

        int divisore = 10;
        double incremento = mana / getLivello();

        if(getListaStats().contains(parametro)) {
            incrementStat(vitalita_, incremento * getRarita() / divisore);
            incrementStat(parametro, incremento);

            normalizza();
        }
        else
            potenzia(mana);

    }

    public void potenzia(Double mana) {
        mana=sanitizeMana(mana);

        int divisore = 10;
        double incremento = mana / getLivello();

        List<String> parametri = getListaStats();
        incremento = incremento / parametri.size();
        final double v = incremento;
        parametri.stream().forEach(s->incrementStat(s,v));

        normalizza();

    }

}
