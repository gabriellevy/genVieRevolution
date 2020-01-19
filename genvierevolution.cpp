#include "genvierevolution.h"
#include "gen_vie/generateurnoeudsprobables.h"
#include "../destinLib/gestionnairecarac.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/perso.h"
#include "../destinLib/execeffet.h"
#include "../destinLib/lancerde.h"
#include "../destinLib/setcarac.h"
#include "../destinLib/choix.h"
#include "../destinLib/exechistoire.h"
#include "administratif/identite.h"
#include "gen_vie/jourapresjour.h"
#include "gen_vie/naissance.h"
#include "corps/pbsante.h"
#include "age.h"
#include "humain.h"

QString GenVieRevolution::AGE = "Age";

QString GenVieRevolution::EFFET_SELECTEUR_ID = "effetSelecteur";
QString GenVieRevolution::EVT_SELECTEUR_ID = "PrincipalSelecteur";
Evt* GenVieRevolution::EVT_SELECTEUR = nullptr;

GenVieRevolution::GenVieRevolution()
    :GenHistoire ("Youpi") {}

GenVieRevolution* GenVieRevolution::GetGenVieRevolution()
{
    return static_cast<GenVieRevolution*>(ME);
}

Hist* GenVieRevolution::GenererHistoire()
{
    GenHistoire::GenererHistoire();
    GenererDataUnivers();
    GenererPersos();
    GenererEvtsAccueil();
    GenererCaracs();
    GenererPrincipalSelectionneurDEffet();

    m_HistoireGeneree->m_ModeDeroulement = ModeDeroulement::Automatique;
    m_HistoireGeneree->m_MsDureeDefilement = GenVieRevolution::CHRONO;

    return m_HistoireGeneree;
}

void GenVieRevolution::GenererDataUnivers()
{

}

void GenVieRevolution::GenererPersos()
{
    QString nom = Identite::CreerPatronyme();
    Humain* perso = new Humain(nom);
    perso->InitialiserPerso();
    IPerso::AjouterPersoJouable(perso);
}

void GenVieRevolution::GenererCaracs()
{
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCarac(
                new Age(180)); // début à 15 ans (180)
}

void GenVieRevolution::GenererEvtsAccueil()
{
    this->AjouterEvt("Debut", "Génération du perso par les choix");
    Effet* effet1 = AjouterEffetNarration("", "");
    Naissance::GenererEffetNaissance(effet1);

    AjouterEffetGoToEvt(GenVieRevolution::EVT_SELECTEUR_ID, "finNaissance");
}

void GenVieRevolution::GenererEvtsDeBase(QVector<NoeudProbable*> &noeuds)
{
    Evt* evtRien = AjouterEvt("evtRien");
    Effet* effetRien = AjouterEffetNarration("Il ne se passe rien. => à régénérer");
    effetRien = TransformerEffetEnEffetMoisDeVie(effetRien);
    effetRien->m_CallbackDisplay = [] {
        Phrase phrase = JourApresJour::ExtrairePhrase();
        ExecHistoire::GetEffetActuel()->m_Texte = phrase.m_Texte;
        ExecHistoire::GetEffetActuel()->m_ImgPath = phrase.m_CheminImg;
        ExecHistoire::GetExecEffetActuel()->ChargerImage(phrase.m_CheminImg);
    };
    NoeudProbable* noeudEvtRien = new NoeudProbable(
                evtRien,
                new Condition(1, p_Relative));
    noeuds.push_back(noeudEvtRien);

    //GenererNoeuds<Metier>(m_GenerateurEvt, noeuds);
}

template<class T>
void GenVieRevolution::GenererNoeuds(GenEvt* genEvt, QVector<NoeudProbable*> &noeuds)
{
    int indexEvt = 0;
    GenerateurNoeudsProbables* evt = new T(indexEvt++);
    while ( evt->m_Nom != "") {

        Effet* effet = evt->GenererEffet(genEvt);

        Condition* cond = evt->m_ConditionSelecteurProba;

        NoeudProbable* noeud = new NoeudProbable(
                    effet,
                    cond);

        noeuds.push_back(noeud);

        evt = new T(indexEvt++);
    }
}

Effet* GenVieRevolution::TransformerEffetEnEffetMoisDeVie(Effet* effet)
{
    // ne se déclenche que si le personnage est encore en vie :
    effet->AjouterCondition(PbSante::C_SANTE, Comparateur::c_Different, PbSante::MORT);
    effet->m_MsChrono = GenVieRevolution::CHRONO;
    effet->m_GoToEvtId = "PrincipalSelecteur";
    effet->AjouterAjouteurACarac(GenVieRevolution::AGE, 1);
    //effet->AjouterAjouteurACarac(Crime::C_MOIS_PRISON, -1);
    return effet;
}


void GenVieRevolution::GenererPrincipalSelectionneurDEffet()
{
    GenVieRevolution::EVT_SELECTEUR = this->AjouterEvt(GenVieRevolution::EVT_SELECTEUR_ID, "Principal sélecteur");
    /*Effet* effetDebut = */AjouterEffetGoToEffet(GenVieRevolution::EFFET_SELECTEUR_ID, "effet_go_to_" + GenVieRevolution::EFFET_SELECTEUR_ID);
    // ce vector doit contenir tous les noeuds de base déclenchant des effets et événements à partir du cours normal de la vie
    // en dehors de lui les sélections de noeuds ne sont qu'à la création du personnage et quand un événement particulier est en cours d'exécution
    // à sa fin on doit avoir un goto qui ramène à cet événement/effet "sélecteur"
    QVector<NoeudProbable*> tousLesNoeudsDeBase;
    GenererEvtsDeBase(tousLesNoeudsDeBase);

    /*Effet* effetDebutBoucle = m_GenerateurEvt->AjouterEffetVide(GenVieHumain::EVT_SELECTEUR, GenVieHumain::EFFET_SELECTEUR_ID);
    effetDebutBoucle->m_Texte = "blablablabla";*/

    Effet* effetTestMort = m_GenerateurEvt->AjouterEffetVide(GenVieRevolution::EVT_SELECTEUR, GenVieRevolution::EFFET_SELECTEUR_ID);
    effetTestMort->m_GoToEffetId = "effetFinVie";
    effetTestMort->AjouterCondition(PbSante::C_SANTE, Comparateur::c_Egal, PbSante::MORT);

    /*Effet* effetDebutBoucle2 = m_GenerateurEvt->AjouterEffetVide(GenVieHumain::EVT_SELECTEUR, GenVieHumain::EFFET_SELECTEUR_ID + "hbjk");
    effetDebutBoucle2->m_Texte = "blablablabla2";*/

    Effet* effetSelecteur = m_GenerateurEvt->AjouterEffetSelecteurDEvt(
                tousLesNoeudsDeBase, GenVieRevolution::EFFET_SELECTEUR_ID + "_selecteur", "", GenVieRevolution::EVT_SELECTEUR);
    effetSelecteur->m_MsChrono = 1; // passé automatiquement

    Effet* effetFinVie = AjouterEffetNarration("Cette vie est terminée...", "", "effetFinVie", GenVieRevolution::EVT_SELECTEUR);
    effetFinVie->m_ChangeurPhaseDeroulement = PhaseDeroulement::epd_Fini;
}



