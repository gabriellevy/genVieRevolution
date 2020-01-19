#include "humain.h"
#include "genvierevolution.h"
#include "gen_vie/jourapresjour.h"

Humain* Humain::ME = nullptr;

Humain::Humain(QString nom):DPerso(nom, nom, nom, "")
{
    Humain::ME = this;
    m_JourApresJour = new JourApresJour();
}

Humain* Humain::GetHumainJoue()
{
    if ( Humain::ME == nullptr )
        Humain::ME = new Humain("inconnu ??");
    return ME;
}

int Humain::GetAge()
{
    return DPerso::GetValeurCaracAsInt(GenVieRevolution::AGE);
}

QString Humain::GetValeurCarac(QString id)
{
    return DPerso::GetValeurCarac(id);
}

int Humain::GetValeurCaracAsInt(QString id)
{
    // cas particuliers où on ne rend aps directement la valeur associée :
    /*if ( id == Combat::C_FORCE_COMBAT) {
        int val = 1; //humain de base

        // ici on pourra ajouter ou retirer des points selon les caracs du perso (space marine = +2 par exemple
        // cf échelle des Combat.h

        return val;
    }*/

    return DPerso::GetValeurCaracAsInt(id);
}

void Humain::ExecutionPostChangeCarac()
{
    m_JourApresJour->RafraichirPhrases();
}

