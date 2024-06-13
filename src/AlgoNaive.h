#include "AlgoAbstract.h"
#include "Ennonce.h"
#include "Solution.h"

class AlgoNaive: public AlgoAbstract {
public:
    AlgoNaive(Ennonce enonce) : AlgoAbstract(enonce) {}
    void run() override;
};