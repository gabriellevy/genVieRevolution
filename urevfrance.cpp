#include "urevfrance.h"
#include "ui_univers.h"
#include "genvierevolution.h"

QString URevFrance::VIE_HUMAIN = "Vie d'un humain";

URevFrance::URevFrance(ModeAffichage modeAffichage,
                       QWidget *parent)
        : Univers(parent, modeAffichage)
{
        //this->AppliquerTheme(QColor(54, 46, 43));
        this->AppliquerTheme(QColor(100, 90, 80));

        m_GensHistoire[URevFrance::VIE_HUMAIN] = new GenVieRevolution();
}
