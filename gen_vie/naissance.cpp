#include "naissance.h"
#include "../destinLib/aleatoire.h"
#include "genvierevolution.h"
#include "metier.h"

Effet* Naissance::GenererEffetNaissance(Effet* effetNarrationVide)
{
    effetNarrationVide->m_GoToEffetId = "finNaissance";

    // 2. détermination classe sociale :
    /*QString classeSocialeStr = ClasseSociale::GetClasseSocialeAleatoire(planete->m_TypePlanete);
    effetNarrationVide->AjouterChangeurDeCarac(ClasseSociale::C_CLASSE_SOCIALE, classeSocialeStr);

    // 2b. détermination de la zone d'habitation (sur sa planète)
    if ( planete->m_TypePlanete == Planete::PLANETE_RUCHE) {
        MondeRuche::AssignerCaracsDeNaissance(classeSocialeStr, effetNarrationVide);
    }

    // 4. détermination si psyker
    QString nivPsyker = Psyker::GetNiveauPsykerNaissance();
    effetNarrationVide->AjouterChangeurDeCarac(Psyker::C_PSYKER, nivPsyker);*/

    return effetNarrationVide;
}
