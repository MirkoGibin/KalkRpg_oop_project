/* Vogliamo normalizzare un valore che assieme agli altri eccede il mana disponibile
 * per il livello in cui si trova l'oggetto.
 * Prende come parametri per valore:
 *  value: valore da normalizzare
 *  sum: somma delle stats, escluse il livello stesso
 *  toMana: valore di Mana che vogliamo raggiungere.
 */

double normalizza(double value, double sum, double toMana) {
    return value*toMana/sum;
}
