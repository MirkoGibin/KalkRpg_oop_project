import java.util.List;

public class Amuleto extends Osso {
    private String fortuna_;

    /* parameters inside stats in Amuleto:
     * Spirito
     * Attacco
     * Difesa
     * Fortuna
     */
    //COSTRUTTORI
    public Amuleto() {
        this(1, 1, 1.0,1.0,1.0,1.0);
    }

    public Amuleto(Integer livello, Integer rarita, Double spirito, Double attacco, Double difesa, Double fortuna) {
        super(livello, rarita,spirito,attacco,difesa);
        fortuna_="Fortuna";
        insertStat(fortuna_, fortuna);

    }

    //METODI
    public Double getFortuna() {
        return getValoreStat(fortuna_);
    }

    @Override
    public Amuleto clone() {
        return new Amuleto(getLivello(),getRarita(),getSpirito(),getAttacco(),getDifesa(),getFortuna());
    }

    @Override
    public Double ricicla() {
        return super.ricicla() + getFortuna()*getRarita();
    }

    @Override
    public void potenzia(Double mana) {
        mana=sanitizeMana(mana);
        Integer divisore=1;

        if(getRarita() > 6 && getLivello() > 6)
            divisore=10;
        else divisore=15;

        incrementStat(fortuna_, mana*getLivello()*getRarita()/divisore);
        super.potenzia(mana);
    }

    @Override
    public void potenzia(Double mana, String parametro) {
        if(getListaStats().contains(parametro)) {
            mana = sanitizeMana(mana);
            Integer divisore = 1;

            if (getRarita() > 6 && getLivello() > 6)
                divisore = 10;
            else divisore = 15;

            incrementStat(fortuna_, mana * getLivello() * getRarita() / divisore);
            super.potenzia(mana, parametro);
        } else this.potenzia(mana);
    }

    public void estraiDa(Oggetto oggetto) throws  OperationException {
        try {
            if(oggetto instanceof Amuleto) throw new OperationException(OperationException.ecc.estrazione);
            Osso o=(Osso) oggetto;

            setLivello(o.getLivello());
            setRarita(o.getRarita());
            List<String> s=getListaStats();
            Integer numeroStats=s.size();

            s.stream().forEach(f-> {
                if(f==fortuna_) incrementStat(f, o.getSommaStats()/numeroStats);
                else incrementStat(f, o.getValoreStat(f)*(numeroStats-1)/numeroStats);
            });

        } catch(ClassCastException e) {
            throw new OperationException(OperationException.ecc.estrazione);
        }
    }

    public Oggetto duplica(Oggetto obj) {
        List<String> parametri=obj.getListaStats();
        Double val=obj.getSommaStats()/parametri.size();

        Oggetto newObj=obj.clone();

        if(getFortuna()<val +1) {
            modifyStat(fortuna_, 1.0);
            parametri
                    .stream()
                    .forEach(f -> newObj.modifyStat(f, 1.0)
                    );
        } else {
            incrementStat(fortuna_, -val);
            if(getRarita()<5)
            parametri
                    .stream()
                    .filter(s->newObj.getValoreStat(s) > val/2)
                    .forEach(s->newObj.modifyStat(s, val/2)
                    );
        }
        return newObj;
    }



}
