#ifndef HUMAIN_H
#define HUMAIN_H

#include "../destinLib/gestionnairecarac.h"

class JourApresJour;

class Humain : public DPerso
{
    static Humain* ME;
public:
    Humain(QString nom);

    JourApresJour* m_JourApresJour;

    static Humain* GetHumainJoue();

    int GetAge();

    virtual QString GetValeurCarac(QString id);
    virtual int GetValeurCaracAsInt(QString id);
    virtual void ExecutionPostChangeCarac();
};

#endif // HUMAIN_H
