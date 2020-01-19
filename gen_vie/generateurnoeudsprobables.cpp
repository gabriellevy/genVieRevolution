#include "generateurnoeudsprobables.h"
#include "../destinLib/effet.h"
#include "../destinLib/evt.h"
#include "../destinLib/genevt.h"
#include "urevfrance.h"
#include "genvierevolution.h"
#include "metier.h"
#include "../destinLib/effet.h"

GenerateurNoeudsProbables::GenerateurNoeudsProbables(int indexEvt){}


Effet* GenerateurNoeudsProbables::GenererEffet(GenEvt* genEvt)
{
    Effet* effet = nullptr;

    // système de création d'effets de base :
    effet = genEvt->AjouterEffetNarration(
        m_Description,
        m_Image,
        "evt_monde_ruche_" + m_Nom, GenVieRevolution::EVT_SELECTEUR);
    effet->m_GoToEffetId = GenVieRevolution::EFFET_SELECTEUR_ID;
    effet = GenVieRevolution::TransformerEffetEnEffetMoisDeVie(effet);
    effet->m_Conditions = m_Conditions;
    effet->m_CallbackDisplay = m_CallbackDisplay;

    // modificateurs de carac :
    QMapIterator<QString, QString> it(m_ModificateursCaracs);
    while ( it.hasNext()) {
        it.next();
        effet->AjouterChangeurDeCarac(it.key(), it.value());
    }
    QMapIterator<QString, int> itInc(m_IncrementeursCaracs);
    while ( itInc.hasNext()) {
        itInc.next();
        effet->AjouterAjouteurACarac(itInc.key(), itInc.value());
    }

    return effet;
}

