#include "jourapresjour.h"
#include "../destinLib/aleatoire.h"
#include "humain.h"
#include "metier.h"
#include "genvierevolution.h"

QVector<Phrase> JourApresJour::PHRASES = {};

JourApresJour::JourApresJour(){}

void JourApresJour::RafraichirPhrasesSelonMetier(QString typePlanete, QString classeSociale, QString metier, int nbMoisVoyage)
{

}

void JourApresJour::RafraichirPhrases()
{
    JourApresJour::PHRASES.clear();

    Humain* humain = Humain::GetHumainJoue();
    // extraire les critères qui influent sur les textes/événements possibles :
    QString metier = humain->GetValeurCarac(Metier::C_METIER);

    if ( PHRASES.length() == 0 )
        JourApresJour::PHRASES.push_back(
                    Phrase("Il ne se passe rien."));
}

Phrase JourApresJour::ExtrairePhrase()
{
    if ( JourApresJour::PHRASES.length() < 1 )
        Humain::GetHumainJoue()->m_JourApresJour->RafraichirPhrases();

    return JourApresJour::PHRASES[Aleatoire::GetAl()->EntierInferieurA(PHRASES.length())];
}
