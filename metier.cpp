#include "metier.h"
#include "../destinLib/effet.h"
#include "../destinLib/evt.h"
#include "../destinLib/genevt.h"
#include "../destinLib/selectionneurdenoeud.h"
#include "urevfrance.h"
#include "genvierevolution.h"
#include "humain.h"

QString Metier::C_METIER = "Métier";
// valeurs de métiers :
QString Metier::PAYSAN = "Paysan";

QMap<QString, Metier*> Metier::METIERS;

Metier::Metier(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    double tmpFavoriseur = 0.0; // valeur servant à tester => à mettre à 0 pour un test final
    switch (indexEvt) {
    case 0 : {
        m_Nom = Metier::PAYSAN;
        m_ConditionSelecteurProba = new Condition(0.1 - tmpFavoriseur, p_Relative);
    }break;
    }

    if ( m_Description == "" ) {
        m_Description = "Vous êtes maintenant " +
                        m_Nom;
        m_Description += ".";
    }
    m_ModificateursCaracs[C_METIER] = m_Nom;

    m_Conditions.push_back(Metier::AjouterConditionSiAPasMetier());
    //m_Conditions.push_back(Crime::AjouterConditionSiLibre());

    METIERS[m_Nom] = this;
}

Condition* Metier::AjouterConditionSiACeMetier(QString metier)
{
    Condition* cond = new Condition(Metier::C_METIER, metier, Comparateur::c_Egal);
    return cond;
}

Condition* Metier::AjouterConditionSiAMetier()
{
    Condition* cond = new Condition(Metier::C_METIER, "", Comparateur::c_Different);
    return cond;
}

Condition* Metier::AjouterConditionSiAPasMetier()
{
    Condition* cond = new Condition(Metier::C_METIER, "", Comparateur::c_Egal);
    return cond;
}

