#ifndef BACKTRACKING_AVANCERAPIDO_ALGORITMO_H
#define BACKTRACKING_AVANCERAPIDO_ALGORITMO_H

#include <optional>
#include <vector>
#include <limits>

using namespace std;

class Backtracking {
    public:
        struct Resultado {
            int voa;
            optional<vector<int>> soa;
        };

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

        //Backtracking aplicando criterio con poda
        static Resultado backtracking_con_poda(Caso caso);
        //Backtracking aplicando criterio sin poda
        static Resultado backtracking_sin_poda(Caso caso);

    private:
        //Genera nuevo nodo
        static void generar(int &nivel, int &dinero_gastado, vector<int> &s, vector<Prenda> &prendas);
        //Comprueba si es una solución mejor que la que tengo actualmente
        static bool solucion(int dinero_gastado, int M, int nivel, int n, int voa);
        //Comprueba si puedo seguir bajando o no (Con poda)
        static bool criterio_con_poda(int dinero_gastado, int nivel, int voa, vector<vector<bool>> &vistado, Caso &caso);
        //Comprueba si puedo seguir bajando o no (Sin poda)
        static bool criterio_sin_poda(int dinero_gastado, int nivel, Caso &caso);
        //Comprueba si tengo más nodos hermanos por comprobar
        static bool mas_hermanos(int num_modelos, int id_modelo_actual);
        //Retrocede en el árbol
        static void retroceder(int &nivel, int &dinero_gastado, vector<int> &s, vector<Prenda> &prendas);
};

#endif