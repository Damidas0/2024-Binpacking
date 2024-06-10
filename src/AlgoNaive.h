#include "AlgoAbstract.h"


class AlgoNaive: public AlgoAbstract {
public:
    AlgoNaive(Ennonce enonce) : AlgoAbstract(enonce) {}
    void run() override;
};