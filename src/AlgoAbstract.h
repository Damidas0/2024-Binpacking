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
    
};