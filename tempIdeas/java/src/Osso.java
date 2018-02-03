public class Osso extends Oggetto {
    /* parameters inside stats in Pietra are:
     * spirito
     * attacco
     * difesa
     */
    private String attacco_;
    private String difesa_;


    //COSTRUTTORI
    public Osso() {
        this(1,1,1.0,1.0,1.0);
    }

    public Osso(Integer livello, Integer rarita, Double spirito, Double attacco, Double difesa) {
        super(livello, rarita, spirito);
        attacco_="Attacco";
        difesa_="Difesa";
        insertStat(attacco_, attacco);
        insertStat(difesa_, difesa);
        sanitizeInput();
    }

    public Double getAttacco() {
        return getValoreStat(attacco_);
    }
    public Double getDifesa() {
        return getValoreStat(difesa_);
    }

    @Override
    public Osso clone() {
        return new Osso(getLivello(), getRarita(), getSpirito(), getAttacco(), getDifesa());
    }

    public Double ricicla() {
        return calcolaMana()/2 + (getAttacco()+getDifesa())/ 2 * getRarita();
    }

    @Override
    public void potenzia(Double mana) {
        Double incremento=mana/(getLivello()*getListaStats().size());
        getListaStats().stream().forEach(s->incrementStat(s, incremento));

        Integer divisore =5;
        incrementStat(attacco_, incremento*getRarita()/(2*divisore));
        incrementStat(difesa_, incremento*getRarita()/(2*divisore));
        normalizza();
    }

    @Override
    public void potenzia(Double mana, String parametro) {
        Double incremento=mana/getLivello();
        Integer divisore =5;
        incrementStat(parametro,incremento);
        incrementStat(attacco_, incremento*getRarita()/(2*divisore));
        incrementStat(difesa_, incremento*getRarita()/(2*divisore));
        normalizza();
    }


}
