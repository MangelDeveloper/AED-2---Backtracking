#ifndef BACKTRACKING_AVANCERAPIDO_CONTROLADOR_H
#define BACKTRACKING_AVANCERAPIDO_CONTROLADOR_H

#include <unordered_set>
#include <fstream>
#include <vector>
using namespace std;

class ControladorBT {
public:
    static const string INPUT_FILE;
    static const string OUTPUT_FILE;

    struct Prenda {
        int num_modelos;
        vector<int> precios;
    };

    struct Caso {
        int presupuesto;
        int num_prendas;
        vector<Prenda> prendas;
        vector<int> max_restante;
        vector<int> min_restante;
    };

    static vector<Caso> leer_entrada();
};

#endif