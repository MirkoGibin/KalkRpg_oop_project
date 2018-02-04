public class Use {

    public static void main(String args[]) {
        // creazione erba erba1 in base al solo mana, livello e rarità
        System.out.println("creazione erba erba1 in base al solo mana, livello e rarità \nerba1:");
        Erba erba1 = new Erba();
        erba1.crea(600.0, 3, 2);
        System.out.println(erba1);
        System.out.println("==========================================");

        // creazione erba erba2 in base a mana, livello, rarità, parametro
        System.out.println("creazione erba erba2 in base a mana, livello, rarità, parametro\nerba2:");
        Erba erba2 = new Erba();
        erba2.crea(6000.0, 3, 2, "Spirito");
        System.out.println(erba2);
        System.out.println("==========================================");

        //creazione amuleto a1 in base a mana, livello, rarità e parametro
        System.out.println("creazione amuleto a1 in base a mana, livello, rarità e parametro\na1:");
        Amuleto a1 = new Amuleto();
        a1.crea(6000.0, 5, 7, "Fortuna");
        System.out.println(a1);
        System.out.println("==========================================");

        //creazione amuleto a2 con mana > 6000, livello >10, rarità < 1
        System.out.println("creazione amuleto a2 con mana > 6000, livello >10, rarità < 1 \na2:");
        Amuleto a2 = new Amuleto();
        a2.crea(7000.0, 11, -1);
        System.out.println(a2);
        System.out.println("==========================================");

        //combinazione di erba1 e a1 precedenti
        System.out.println("combinazione di erba1 e a1 precedenti con side effect su erba1");
        erba1.combina(a1);
        System.out.println(erba1);
        System.out.println("==========================================");

        //combinazione di a2 e erba2
        System.out.println("combinazione di a2 e erba2 con side effect su a2");
        a2.combina(erba2);
        System.out.println(a2);
        System.out.println("==========================================");

        //trasformarmazione di oggetto Erba erba2 in oggetto Amuleto a3 (con eccezione)
        System.out.println("trasformarmazione di oggetto Erba erba2 in oggetto Amuleto a3 (con eccezione)");
        Amuleto a3 = new Amuleto();
        try {
            a3.trasformaDa(erba2);
            System.out.println(a3);
        } catch (OperationException x) {
            System.out.println(x.getErrore() + "\n");
        }
        System.out.println("==========================================");

        //trasformazione di amuleto a3 in un cristallo c1
        System.out.println("trasformazione di amuleto a2 in un cristallo c1");
        Cristallo c1 = new Cristallo();
        a3 = new Amuleto(10, 1, 150.0, 146.0, 146.0, 146.0);
        try {
            c1.trasformaDa(a3);
            System.out.println(c1);
        } catch (OperationException x) {
            System.out.println(x.getErrore());
        }
        System.out.println("==========================================");

        //duplico, tramite amuleto a4 con rarità 7, il cristallo c1, creando c2.
        System.out.println("duplico, tramite amuleto a4 con rarità 7, il cristallo c1, creando c2");
        c1 = new Cristallo(3, 4, 30.0, 56.0, 78.0);
        Amuleto a4 = new Amuleto(3, 7, 120.0, 100.0, 75.0, 85.0);
        Cristallo c2 = (Cristallo) a4.duplica(c1);
        System.out.println("Nuovo cristallo c2:\n" + c2 + "Vecchio cristallo c1\n" + c1 + "Amuleto a4\n" + a4);
        System.out.println("==========================================");

        //duplico, tramite amuleto a4 con tutto a 1, il cristallo c1 con tutto a 1, creando c2.
        System.out.println("duplico, tramite amuleto a4 con tutto a 1, il cristallo c1 con tutto a 1, creando c2");
        c1 = new Cristallo();
        a4 = new Amuleto();
        c2 = (Cristallo) a4.duplica(c1);
        System.out.println("Nuovo cristallo c2:\n" + c2 + "Vecchio cristallo c1\n" + c1 + "Amuleto a4\n" + a4);
        System.out.println("==========================================");

        //duplico, tramite amuleto a4 con fortuna a 1, il cristallo c1 con tutto al massimo, creando c2.
        System.out.println("duplico, tramite amuleto a4 con tutto a 1, il cristallo c1 con tutto a 1, creando c2");
        c1 = new Cristallo(10, 10, 150.0, 150.0, 150.0);
        a4 = new Amuleto();
        c2 = (Cristallo) a4.duplica(c1);
        System.out.println("Nuovo cristallo c2:\n" + c2 + "Vecchio cristallo c1\n" + c1 + "Amuleto a4\n" + a4);
        System.out.println("==========================================");

        //riciclo cristallo c2
        System.out.println("riciclo cristallo c2");
        System.out.println(c2);
        System.out.println("Mana: " + c2.ricicla());
        System.out.println("==========================================");

        //riciclo amuleto a4
        System.out.println("riciclo amuleto a4");
        a4 = new Amuleto(3, 7, 120.0, 100.0, 75.0, 85.0);
        System.out.println(a4);
        System.out.println("Mana: " + a4.ricicla());
        System.out.println("==========================================");

        //potenziamento dell'osso op, erba ep, pietra pp, con mana 3700 e senza parametri(o parametri errati / inesistenti)
        System.out.println("potenziamento dell'osso op, erba ep, pietra pp, con mana 3700 e senza parametri(o parametri errati / inesistenti)");
        Osso op = new Osso(4, 5, 70.0, 122.0, 134.0);
        Erba ep = new Erba(4, 5, 70.0, 122.0);
        Pietra pp = new Pietra(4, 5, 70.0, 122.0);
        System.out.println("Prima: \n" + op);
        op.potenzia(3700.0);
        System.out.println("Dopo: \n" + op);
        System.out.println("Prima: \n" + ep);
        ep.potenzia(3700.0);
        System.out.println("Dopo: \n" + ep);
        System.out.println("Prima: \n" + pp);
        pp.potenzia(3700.0, "banana");
        System.out.println("Dopo: \n" + pp);
        System.out.println("==========================================");

        //potenziamento dell'osso op, erba ep, pietra pp, con mana 3700 e parametri)
        System.out.println("potenziamento dell'osso op, erba ep, pietra pp, con mana 3700 e parametri");
        op = new Osso(4, 5, 70.0, 122.0, 134.0);
        ep = new Erba(4, 5, 70.0, 122.0);
        pp = new Pietra(4, 5, 70.0, 122.0);
        System.out.println("Prima: \n" + op);
        op.potenzia(3700.0, "Attacco");
        System.out.println("Dopo: \n" + op);
        System.out.println("Prima: \n" + ep);
        ep.potenzia(3700.0, "Vitalità");
        System.out.println("Dopo: \n" + ep);
        System.out.println("Prima: \n" + pp);
        pp.potenzia(3700.0, "Durezza");
        System.out.println("Dopo: \n" + pp);
        System.out.println("==========================================");

        //potenziamento dell'amuleto op, unguento ep, cristallo pp, cont mana 3700 e senza parametri(o parametri sbagliati)
        System.out.println("potenziamento dell'unguento op, cristallo ep, amuleto pp, cont mana 3700 e senza parametri(o parametri sbagliati");
        op = new Amuleto(4, 5, 70.0, 122.0, 134.0, 54.0);
        ep = new Unguento(4, 5, 70.0, 122.0, 98.0);
        pp = new Cristallo(4, 5, 70.0, 122.0, 65.0);
        System.out.println("Prima: \n" + op);
        op.potenzia(3700.0);
        System.out.println("Dopo: \n" + op);
        System.out.println("Prima: \n" + ep);
        ep.potenzia(3700.0);
        System.out.println("Dopo: \n" + ep);
        System.out.println("Prima: \n" + pp);
        pp.potenzia(3700.0);
        System.out.println("Dopo: \n" + pp);
        System.out.println("==========================================");

        //potenziamento dell'amuleto op (rarità > 6, livello > 6), unguento ep (rarità > 6, livello > 6), con mana 3700 e senza parametri(o parametri sbagliati)
        System.out.println("potenziamento dell'amuleto op (rarità > 6, livello > 6), unguento ep (rarità > 6, livello > 6), con mana 3700 e senza parametri(o parametri sbagliati)");
        op = new Amuleto(7, 7, 70.0, 122.0, 134.0, 54.0);
        ep = new Unguento(7, 7, 70.0, 122.0, 98.0);
        System.out.println("Prima: \n" + op);
        op.potenzia(3700.0);
        System.out.println("Dopo: \n" + op);
        System.out.println("Prima: \n" + ep);
        ep.potenzia(3700.0);
        System.out.println("Dopo: \n" + ep);
        System.out.println("==========================================");

        //potenziamento dell'amuleto op (rarità > 6, livello > 6), unguento ep (rarità > 6, livello > 6), con mana 3700 e con parametri)
        System.out.println("potenziamento dell'amuleto op (rarità > 6, livello > 6), unguento ep (rarità > 6, livello > 6), con mana 3700 e senza parametri(o parametri sbagliati)");
        op = new Amuleto(7, 7, 70.0, 122.0, 134.0, 54.0);
        ep = new Unguento(7, 7, 70.0, 122.0, 98.0);
        System.out.println("Prima: \n" + op);
        op.potenzia(3700.0, "Attacco");
        System.out.println("Dopo: \n" + op);
        System.out.println("Prima: \n" + ep);
        ep.potenzia(3700.0, "Energia");
        System.out.println("Dopo: \n" + ep);
        System.out.println("==========================================");

        //potenziamento del cristallo op con parametro = spirito
        System.out.println("potenziamento del cristallo op con parametro = spirito");
        pp = new Cristallo(4, 5, 70.0, 122.0, 65.0);
        System.out.println("Prima: \n" + pp);
        pp.potenzia(3700.0, "Spirito");
        System.out.println("Dopo: \n" + pp);

        //potenziamento del cristallo op con parametro != spirito
        System.out.println("potenziamento del cristallo op con parametro != spirito");
        pp = new Cristallo(4, 5, 70.0, 122.0, 65.0);
        System.out.println("Prima: \n" + pp);
        pp.potenzia(3700.0, "Durezza");
        System.out.println("Dopo: \n" + pp);
        System.out.println("==========================================");

        //distribuire un cristallo cd ad un amuleto ad
        System.out.println("distribuire un cristallo cd ad un amuleto ad");
        Cristallo cd = new Cristallo(8, 3, 111.0, 100.0, 80.0);
        Amuleto ad = new Amuleto(4, 3, 45.0, 79.0, 29.0, 100.0);
        System.out.println("Prima: \n" + cd);
        System.out.println("Prima: \n" + ad);
        cd.distribuisci(ad);
        System.out.println("Dopo: \n" + cd);
        System.out.println("Dopo: \n" + ad);
        System.out.println("==========================================");

        //distribuire un cristallo cd (con durezza scarsa) ad un amuleto ad
        System.out.println("distribuire un cristallo cd ad un amuleto ad");
        cd = new Cristallo(8, 3, 111.0, 10.0, 138.0);
        ad = new Amuleto(4, 3, 45.0, 79.0, 29.0, 100.0);
        System.out.println("Prima: \n" + cd);
        System.out.println("Prima: \n" + ad);
        cd.distribuisci(ad);
        System.out.println("Dopo: \n" + cd);
        System.out.println("Dopo: \n" + ad);
        System.out.println("==========================================");

        //riparare con un unguento er con rarita > 7 una pietra pr
        System.out.println("riparare con un unguento er con rarita > 7 una amuleto ar");
        Unguento er = new Unguento(8, 8, 111.0, 100.0, 138.0);
        Amuleto ar = new Amuleto(4, 3, 45.0, 79.0, 29.0, 100.0);
        System.out.println("Prima: \n" + er);
        System.out.println("Prima: \n" + ar);
        er.ripara(ar);
        System.out.println("Dopo: \n" + er);
        System.out.println("Dopo: \n" + ar);
        System.out.println("==========================================");

        //riparare con un unguento er con rarita < 7 una pietra pr
        System.out.println("riparare con un unguento er con rarita < 7 una pietra pr");
        er = new Unguento(8, 5, 111.0, 100.0, 138.0);
        ar = new Amuleto(4, 3, 45.0, 79.0, 29.0, 100.0);
        System.out.println("Prima: \n" + er);
        System.out.println("Prima: \n" + ar);
        er.ripara(ar);
        System.out.println("Dopo: \n" + er);
        System.out.println("Dopo: \n" + ar);
        System.out.println("==========================================");

        //estrarre un unguento da un erba con rarità > 7
        System.out.println("estrarre un unguento da un erba con rarità > 7");
        Unguento ue = new Unguento();
        try{
            ue.estraiDa(new Erba(2,8,45.0,78.0));
        } catch(OperationException x) {
            System.out.println(x.getErrore());
        }
        System.out.println(ue);
        System.out.println("==========================================");

        //estrarre un unguento da un erba con rarità < 7
        System.out.println("estrarre un unguento da un erba con rarità < 7");
        ue = new Unguento();
        try{
            ue.estraiDa(new Erba(2,4,45.0,78.0));
        } catch(OperationException x) {
            System.out.println(x.getErrore());
        }
        System.out.println(ue);
        System.out.println("==========================================");

        //estrarre un cristallo da una pietra con durezza < 10
        System.out.println("estrarre un cristallo da una pietra con durezza < 10");
        Cristallo ce = new Cristallo();
        try{
            ce.estraiDa(new Pietra(2, 5, 5.0, 7.0));
        } catch(OperationException x) {
            System.out.println(x.getErrore());
        }
        System.out.println(ce);
        System.out.println("==========================================");

        //estrarre un cristallo da una pietra con durezza > 10
        System.out.println("estrarre un cristallo da una pietra con durezza > 10");
        ce = new Cristallo();
        try{
            ce.estraiDa(new Pietra(2, 5, 5.0, 77.0));
        } catch(OperationException x) {
            System.out.println(x.getErrore());
        }
        System.out.println(ce);
        System.out.println("==========================================");

        //estrarre un amuleto da un osso
        System.out.println("estrarre un amuleto da un osso");
        Amuleto ae = new Amuleto();
        try{
            ae.estraiDa(new Osso(2,4,45.0,78.0, 64.0));
        } catch(OperationException x) {
            System.out.println(x.getErrore());
        }
        System.out.println(ae);
        System.out.println("==========================================");

        //esempio di estrazione non possibile: amuleto estratto da erba
        System.out.println("esempio di estrazione non possibile");
        ae = new Amuleto();
        try{
            ae.estraiDa(new Erba(2,4,45.0,78.0));
        } catch(OperationException x) {
            System.out.println(x.getErrore());
        }

        //esempio di estrazione non possibile: amuleto estratto da amuleto
        System.out.println("esempio di estrazione non possibile");
        ae = new Amuleto();
        try{
            ae.estraiDa(new Amuleto(2,4,45.0,78.0, 14.0, 66.0));
        } catch(OperationException x) {
            System.out.println(x.getErrore());
        }
    }
}
