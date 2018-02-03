public class OperationException extends Exception {
    public enum ecc {
        trasformazione,
        estrazione;
    };
    public OperationException(ecc tipo) {
        tipo_=tipo;
    }
    public String getErrore() {
        String errore =new String();
        switch (tipo_) {
            case trasformazione:
                errore="Impossibile trasformare dall'oggetto indicato: \\n il numero di statistiche dell'oggetto da trasformare non può essere minore del numero di statistiche dell'oggetto che si vuole ottenere.\"";
                break;
            case estrazione:
                errore="Impossibile estrarre dall'oggetto indicato. Le estrazioni possibili sono: \\n erba => unguento;\\n pietra => cristallo;\\n osso => amuleto";
                break;
        }
        return errore;
    }
    private ecc tipo_;
}
