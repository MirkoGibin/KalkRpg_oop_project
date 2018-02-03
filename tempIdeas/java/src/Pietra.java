import java.util.List;

public class Pietra extends Oggetto {
    /* parameters inside stats in Oggetto are:
     * spirito
     * attacco
     * durezza
     */

    private String durezza_;
    public Pietra() {
        this(1,1,1.0,1.0);
    }

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

    @Override
    public Pietra clone() {
        return new Pietra(getLivello(), getRarita(), getSpirito(), getDurezza());
    }

    public Double ricicla() {
        return calcolaMana()/2.0 + getValoreStat(durezza_)*getRarita();
    }

    public void potenzia(Double mana) {
        mana=sanitizeMana(mana);

        Integer divisore =5;
        Double incremento =mana/getLivello();
        incrementStat(durezza_,incremento*getRarita()/divisore);

        List<String> lista=getListaStats();

        incremento=incremento/lista.size();
        final Double d=incremento;
        lista.stream().forEach(s->incrementStat(s,d));
        normalizza();
    }
    
    public void potenzia(Double mana, String parametro) {
        if(getListaStats().contains(parametro)) {
            mana=sanitizeMana(mana);
            Integer divisore = 5;
            Double incremento = mana / getLivello();
            incrementStat(durezza_, incremento * getRarita() / divisore);
            incrementStat(parametro, incremento);
            normalizza();
        } else potenzia(mana);
    }
}
