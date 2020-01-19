#ifndef GENVIEREVOLUTION_H
#define GENVIEREVOLUTION_H

#include "../destinLib/genhistoire.h"

namespace Ui {
class GenVieRevolution;
}

class GenVieRevolution : public GenHistoire
{
public:
    GenVieRevolution();

    virtual Hist* GenererHistoire();

    static GenVieRevolution* GetGenVieRevolution();

    const static int CHRONO = 5000; // nombre de ms entre chaque effet

    // caracs :
    static QString AGE;

    // evts important :
    static QString EFFET_SELECTEUR_ID;
    static QString EVT_SELECTEUR_ID;
    static Evt* EVT_SELECTEUR;
    static Effet* TransformerEffetEnEffetMoisDeVie(Effet* effet);

protected:
    // génère toutes les caracs qui peuvent être visualisées par le joueur (d'autres caracs peuvent être générées et invisibles n'importe quand dans l'aventure)
    virtual void GenererCaracs();
    virtual void GenererPersos();
    void GenererDataUnivers();
    /**
     * T doit hériter de GenerateurNoeudsProbables
     */
    template<class T >static void GenererNoeuds(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds);


private:
    // génération des événement et effets de base
    void GenererEvtsAccueil();
    void GenererEvtsDeBase(QVector<NoeudProbable*> &noeuds);
    void GenererPrincipalSelectionneurDEffet();
 //  cet effet représente à lui seul un mois complet de vie, il veiilit de le personnage

};

#endif // GENVIEREVOLUTION_H
