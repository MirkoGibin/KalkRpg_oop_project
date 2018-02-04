import java.util.List;

public class Cristallo extends Pietra {
    private String magia_;



    //CONSTRUCTORS
    public Cristallo() {
        this(1,1,1.0,1.0,1.0);
    }

    public Cristallo(Integer livello, Integer rarita, Double spirito, Double durezza, Double magia) {
        super(livello, rarita, spirito, durezza);
        magia_="Magia";
        insertStat(magia_,magia);

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
        mana=sanitizeMana(mana);
        Double incremento = mana*getLivello()*getRarita();
        Integer divisore=10;
        incrementStat(magia_, incremento*getRarita()/divisore);
        super.potenzia(mana);
        normalizza();
    }


    @Override
    public void potenzia(Double mana, String parametro) {
        if(getListaStats().contains(parametro)) {
            mana = sanitizeMana(mana);
            Double incremento = mana * getLivello() * getRarita();
            Integer divisore = 1;

            if (parametro == "Spirito") {
                divisore = 15;
                incrementStat(parametro, incremento / getMagia());
                incrementStat(magia_, incremento * getRarita() / divisore);
            } else {
                divisore = 10;
                incrementStat(magia_, incremento * getRarita() / divisore);
                super.potenzia(mana, parametro);
            }
            normalizza();
        } else {
            this.potenzia(mana);
        }
    }

    public void estraiDa(Oggetto oggetto) throws OperationException {
        try {
            if(oggetto instanceof Cristallo) throw new OperationException(OperationException.ecc.estrazione);
            Pietra p = (Pietra) oggetto;

            if (p.getDurezza() >= 10) {
                setLivello(p.getLivello());
                setRarita(p.getRarita());

                List<String> s=getListaStats();
                Integer numeroStats = s.size();
                final Double sommaStats = p.getSommaStats();

                s.stream().forEach(f -> {
                    if (f == magia_) incrementStat(f, (sommaStats - p.getSpirito()) / numeroStats);
                    else incrementStat(f, p.getValoreStat(f) * (numeroStats - 1) / numeroStats);
                });
            } else
                getListaStats().forEach(s -> modifyStat(s, 1.0));
        } catch (ClassCastException e) {
            throw new OperationException(OperationException.ecc.estrazione);
        }
    }

    @Override
    public Double ricicla() {
        return super.ricicla() + getMagia()*getRarita();
    }

    public void distribuisci(Oggetto obj) {
        Double val=getMagia()/2;
        if(getDurezza() < val +1) return;

        editDurezza(-val);

        List<String> lista=obj.getListaStats();
        Integer size=lista.size();

        lista
                .stream()
                .forEach(s->
                        obj.incrementStat(s, val/size)
                );
        obj.normalizza();
    }
}
