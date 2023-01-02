// creiamo la classe dei razionali

// andiamo a controllare se la macro è già stata definita
#ifndef __rational_hpp__ // se non l'ho importato
#define __rational_hpp__

/**
 *  Una classe naive per i razionali
*/
class rational
{
    int num;     //!< numeratore
    int denom;   //!< denominatore

    public:


    
        /**
         *  Il costruttore vuoto
        */
        rational();

        // dato un num intero vogliamo essere in grado di scrivere un razionale
        /**
         *  Costruttore da intero
         *  @param value è il valore intero che vogliamo trasformare
        */
        rational(const int value);
        
        // ho bisogno anche di un costruttore che dato num e denom mi costruisce il razionale corrispondente
        /**
         *  Costruttore da intero
         *  @param numerator è il numeratore del razionale
         *  @param denominator è il denominatore del razionale
        */
        rational(const int numerator, const int denominator);

        // dato un razionale potremmo voler sapere qual'è il suo num e denom
        /**
         *  Ottieni il numeratore
         *  @return il numeratore del razionale
        */
        inline const int& numerator() const // uso inline visto che è solo 1 riga di codice
        {
            return num;
        }
        /**
         *  Ottieni il denominatore
         *  @return il denominatore del razionale
        */
        inline const int& denominator() const
        {
            return denom;
        }

        /**********************************************************************************/
        /** // siccome è friend puo accedere ai membri privati dellla classe
         * Legge un razionale da uno stream
         * @param is è lo stream di input
         * @param a è il razionale da leggere
         * @return il riferimento allo stream di input
        */
        friend std::istream& operator>>(std::istream& is, const rational& a);
        
        // metto l'operatore somma come friend cosi puo accedere ai membri
        friend rational operator + (rational&& a, const rational& b);

        // faccio direttamente questo per il caso in cui && sia il secondo razionale
        inline friend rational operator + (const rational& a, rational&& b)
        {
            std::cout << "Prova2 " << std::endl;
            return std::move(b) + a; // con move trasforma b in un Rvalue cosi usa la funzione di sopra!
        }
        
        // nel caso lo siano entrambi
        inline friend rational operator + (rational&& a, rational&& b)
        {
            std::cout << "Prova3 " << std::endl;
            return std::move(a) + b; // MOVE MI TRASFORMA UN LVALUE IN RVALUE
        }
        
};

// adesso vediamo di quali operatori abbiamo bisogno
/**
 *  Somma 2 razionali
 * @param a è un razionale
 * @param b è un razionale
 * @return la somma di a e b
*/
rational operator + (const rational& a, const rational& b);

/**
 *  Sottrazione 2 razionali
 * @param a è un razionale
 * @param b è un razionale
 * @return la sottrazione di a e b
*/
rational operator - (const rational& a, const rational& b);

/**
 *  Prodotto tra 2 razionali
 * @param a è un razionale
 * @param b è un razionale
 * @return il prodotto di a e b
*/
rational operator * (const rational& a, const rational& b);

/**
 *  Divisione di 2 razionali
 * @param a è un razionale
 * @param b è un razionale
 * @return la divisione di a per b
*/
rational operator / (const rational& a, const rational& b);

//rational operator + (rational&& a, const rational& b);

// ultimi operatori che ci servono sono operatori di input da tastiera e output su schermo
/**
 * Stampa un razionale su uno stream
 * @param os è lo stream di output
 * @param a è il razionale da stampare
 * @return il riferimento allo stream di output
*/
std::ostream& operator << (std::ostream& os, const rational& a);

// per l'input
/** // sicocme è friend puo accedere ai membri pribvati dellla classe
 * Legge un razionale da uno stream
 * @param is è lo stream di input
 * @param a è il razionale da leggere
 * @return il riferimento allo stream di input
*/
std::istream& operator >> (std::istream& is, const rational& a);

#endif // __rational_hpp__

// le definizioni di questi metodi le definisco nel sorgente rational.cpp