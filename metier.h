#ifndef METIER_H
#define METIER_H

#include <QString>
#include <QMap>
#include "gen_vie/generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;

class Metier : public GenerateurNoeudsProbables
{
public:
    Metier(int indexEvt);

    static QMap<QString, Metier*> METIERS;

    static Condition* AjouterConditionSiAMetier();
    static Condition* AjouterConditionSiACeMetier(QString metier);
    static Condition* AjouterConditionSiAPasMetier();

    static QString C_METIER;
    // valeurs de métiers :
    static QString PAYSAN;

};

#endif // METIER_H
