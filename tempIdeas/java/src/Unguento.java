import javafx.util.Pair;

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
    @Override
    public Unguento clone() {
        return new Unguento(getLivello(), getRarita(), getSpirito(), getVitalita(), getEnergia());
    }

    //OPERAZIONI
    @Override
    public void potenzia(Double mana, String parametro) {

        int divisore;

        if(getRarita() > 6)
            divisore = 9;
        else
            divisore = 12;

        incrementStat(energia_, mana * getLivello() * getRarita() / divisore);
        super.potenzia(mana, parametro);
    }

    @Override
    public void potenzia(Double mana) {
        potenzia(mana, "");
    }

    public void estraiDa(Oggetto oggetto) throws OperationException {
        try {
            if(oggetto instanceof Unguento) throw new OperationException(OperationException.ecc.estrazione);

            Erba e = (Erba) oggetto;

            setLivello(oggetto.getLivello());
            setRarita(oggetto.getRarita());

            List<String> s = getListaStats();
            int numeroStat = s.size();

            s.stream().forEach( f -> {
                        if (f == energia_) {
                            double val = oggetto.getSommaStats() / numeroStat;
                            if (val < 1) val = 1;
                            modifyStat(f, val);
                        } else if (getRarita() > 7)
                            modifyStat(f, oggetto.getValoreStat(f));
                        else {
                            double val = oggetto.getValoreStat(f) * (numeroStat - 1) / numeroStat;
                            if (val < 1) val = 1;
                            modifyStat(f, val);
                        }
                    }
            );
        } catch (ClassCastException e) {
            throw new OperationException(OperationException.ecc.estrazione);
        }
    }

    @Override
    public Double ricicla() {
        return super.ricicla() + getValoreStat(energia_) * getRarita();
    }

    public void ripara(Oggetto obj) {

        Pair<String, String> minmax = obj.findMinMaxStat();

        double maxValue = obj.getValoreStat(minmax.getValue());
        double diff = maxValue - obj.getValoreStat(minmax.getKey());

        if(getValoreStat(energia_) < diff + 1) {
            return;
        }

        incrementStat(energia_, -diff);

        if(getRarita() > 7) {
            List<String> parametri = obj.getListaStats();

            parametri.stream().forEach( f ->
                obj.modifyStat(f, maxValue)
            );
        }
        else {
            obj.modifyStat(minmax.getKey(), maxValue);
        }
        obj.normalizza();
    }

}
