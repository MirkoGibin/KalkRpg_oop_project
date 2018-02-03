import java.util.List;

public class Cristallo extends Pietra {
    private String magia_;



    //CONSTRUCTORS
    public Cristallo() {
        super();
        magia_="Magia";
        insertStat(magia_, 1.0);
    }

    public Cristallo(Integer livello, Integer rarita, Double spirito, Double durezza, Double magia) {
        super(livello, rarita, spirito, durezza);
        magia_="Magia";
        insertStat(magia_,magia);
        sanitizeInput();
    }

    //METODI DI GET
    Double getMagia() {
        return getValoreStat(magia_);
    }

    public Cristallo clone() {
        return new Cristallo(getLivello(), getRarita(), getSpirito(), getDurezza(), getMagia());
    }

    @Override
    public void potenzia(Double mana) {
        Double incremento = mana*getLivello()*getRarita();
        Integer divisore=10;
        incrementStat(magia_, incremento*getRarita()/divisore);
        super.potenzia(mana);
    }


    @Override
    public void potenzia(Double mana, String parametro) {
        Double incremento = mana*getLivello()*getRarita();
        Integer divisore =1;

        if(parametro=="Spirito") {
            divisore=15;
            incrementStat(parametro, incremento/getMagia());
            incrementStat(magia_, incremento*getRarita()/divisore);
        }
        else {
            divisore=10;
            incrementStat(magia_, incremento*getRarita()/divisore);
            super.potenzia(mana, parametro);
        }
    }

    public void estraiDa(Oggetto oggetto) throws OperationException {
        if(oggetto.getClass().getName()=="Pietra") { //DA CONTROLLARE!!
            Pietra p=(Pietra)oggetto;

            if(p.getDurezza()>=10) {
                setLivello(p.getLivello());
                setRarita(p.getRarita());

                //List<String> s=getListaStats();
                Integer numeroStats = getListaStats().size();

                getListaStats().stream().forEach(s -> {
                    if (s == "Magia") incrementStat(s, (p.getSommaStats() - getSpirito()) / numeroStats);
                    else incrementStat(s, p.getValoreStat(s) * (numeroStats - 1) / numeroStats);
                });
            }
            else
                getListaStats().forEach(s->modifyStat(s,1.0));
        }
        else throw new OperationException(OperationException.ecc.estrazione);
    }

    @Override
    public Double ricicla() {
        return super.ricicla() + getMagia()*getRarita();
    }

    public void distribuisci(Oggetto obj) {
        Double val=getMagia()/2;
        if(getDurezza() < val +1) return;

        editDurezza(-val);
        Integer size=getListaStats().size();

        obj.getListaStats().stream().forEach(s->obj.incrementStat(s, val/size));
        obj.normalizza();
    }
}
