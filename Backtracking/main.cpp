#include <iostream>
#include "AlgoritmoBT.h"
#include <cmath>
#include <limits>

using namespace std;
int main() {
    vector <ControladorBT::Caso> casos = ControladorBT::leer_entrada();

    auto it_casos = casos.begin();

    while (it_casos != casos.end()) {
        ControladorBT::Caso caso = *it_casos;

        AlgoritmoBT::Resultado resultado = AlgoritmoBT::backtracking(caso);

        if (resultado.voa == numeric_limits<int>::min()) cout << "no solution" << endl;
        else cout << resultado.voa << endl;

        ++it_casos;
    }

    return 0;
}