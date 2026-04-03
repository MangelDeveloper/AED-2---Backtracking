#ifndef BACKTRACKING_AVANCERAPIDO_ALGORITMO_H
#define BACKTRACKING_AVANCERAPIDO_ALGORITMO_H

#include <optional>
#include "ControladorBT.h"

using namespace std;

class AlgoritmoBT {
    private:
        //Genera nuevo nodo
        static void generar(int &nivel_actual, int &dinero_gastado, vector<int> &s, vector<ControladorBT::Prenda> &prendas);
        //Comprueba si es una solución mejor que la que tengo actualmente
        static bool solucion(int dinero_gastado, int M, int nivel_actual, int n, int voa);
        //Comprueba si puedo seguir bajando o no
        static bool criterio(int dinero_gastado, int M, int nivel_actual, int n, int voa, vector<int> &max_restante, vector<int> &min_restante, vector<vector<bool>> &vistado);
        //Comprueba si tengo más nodos hermanos por comprobar
        static bool mas_hermanos(int num_modelos, int id_modelo_actual);
        //Retrocede en el árbol
        static void retroceder(int &nivel_actual, int &dinero_gastado, vector<int> &s, vector<ControladorBT::Prenda> &prendas);

    public:
        struct Resultado {
            int voa;
            optional<vector<int>> soa;
        };

        static Resultado backtracking(ControladorBT::Caso caso);
};

#endif