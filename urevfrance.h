#ifndef UREVFRANCE_H
#define UREVFRANCE_H

#include "../destinLib/univers.h"


class URevFrance : public Univers
{
    Q_OBJECT

public:
    explicit URevFrance(ModeAffichage modeAffichage = ModeAffichage::ema_Jeu,
             QWidget *parent = nullptr);

    // noms d'aventures
    static QString VIE_HUMAIN;
};

#endif // UREVFRANCE_H
