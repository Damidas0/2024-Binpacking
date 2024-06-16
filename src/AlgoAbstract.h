#pragma once
#include "Ennonce.h"
#include "Solution.h"

class AlgoAbstract {
public:
    Ennonce m_enonce;
    Solution m_solution;

    AlgoAbstract(Ennonce enonce) : m_enonce(enonce) {}
    virtual void run() = 0;
    virtual ~AlgoAbstract() = default;

    /**
     * @brief Met à jour l'ennonce et réinitialise les paramètres de l'algorithme en fonction de ce nouvel énoncé
     * @brief fonction qui sera redéfinie dans les classes filles si besoin
     */
    virtual void updateEnnonce(Ennonce enonce) {
        m_enonce = enonce;
    }


};