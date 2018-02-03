import java.util.List;

public class Unguento extends Erba {
    private String energia_;

    //CONSTRUCTORS
    public Unguento() {
        super();
        energia_="Energia";
        insertStat(energia_, 1.0);
    }

    public Unguento(Integer livello, Integer rarita, Double spirito, Double vitalita, Double energia) {
        super(livello, rarita, spirito, vitalita);
        energia_="Energia";
        insertStat(energia_,energia);
        sanitizeInput();
    }

    //METODI DI GET

    public Double getEnergia() {
        return getValoreStat(energia_);
    }

    //METODI DI SET

    public Unguento clone() {
        return new Unguento(getLivello(), getRarita(), getSpirito(), getVitalita(), getEnergia());
    }

    //OPERAZIONI

    public void potenzia(Double mana, String parametro) {

        int divisore;

        if(getRarita() > 6)
            divisore = 9;
        else
            divisore = 12;

        incrementStat(energia_, mana * getLivello() * getRarita() / divisore);
        super.potenzia(mana, parametro);
    }

    public void potenzia(Double mana) {
        
        int divisore = 10;
        double incremento = mana / getLivello();

        List<String> parametri = getListaStats();
        incremento = incremento / parametri.size();
        parametri.stream().forEach(s->incrementStat(s,incremento));

        normalizza();

    }




}
