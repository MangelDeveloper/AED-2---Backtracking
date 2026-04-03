#include "AlgoritmoBT.h"
#include <optional>
#include <limits>

using Solucion = optional<vector<int>>;
//Backtracking
AlgoritmoBT::Resultado AlgoritmoBT::backtracking(ControladorBT::Caso caso) {
    //Inicialización
    //Número de niveles máximo del árbol
    int n = caso.num_prendas;
    //Vector solución
    vector s(n,-1);
    //Dinero usado actualmente
    int dinero_gastado = 0;
    //Nivel actual en el que me encuentro
    int nivel_actual = 0;
    //Dinero máximo a gastar
    int M = caso.presupuesto;
    //Las prendas de vestir
    vector<ControladorBT::Prenda>& prendas = caso.prendas;
    //Iniciamos el voa a -infinito
    int voa = numeric_limits<int>::min();
    //Solución óptima actual
    Solucion soa;
    //Memoización
    vector<vector<bool>> visitado(n, vector<bool>(M+1,false));

    while (nivel_actual != -1) {
        //Generar un nodo hermano
        generar(nivel_actual, dinero_gastado, s, prendas);

        //Si encuentro una solución mejor que voa, guardamos soa y voa
        if (solucion(dinero_gastado, M, nivel_actual, n, voa)) {
            soa = s;
            voa = dinero_gastado;
        }

        //Si podríamos llegar a una solución mejor, seguimos bajando
        if (criterio(dinero_gastado, M, nivel_actual, n, voa, caso.max_restante, caso.min_restante, visitado)) nivel_actual++;
        else {
            //Si no, retrocedo hasta encontrar un nodo con más hermanos
            while (nivel_actual >= 0 && !mas_hermanos(prendas[nivel_actual].num_modelos , s[nivel_actual])) {
                retroceder(nivel_actual, dinero_gastado, s, prendas);
            }
        }
    }

    return {voa, soa};
}



void AlgoritmoBT::generar(int &nivel_actual, int &dinero_gastado,vector<int> &s, vector<ControladorBT::Prenda> &prendas) {
    //NOTA: Recordemos que cada nivel es una prenda, por tanto, nivel_actual contiene el índice de la prenda
    //que estamos analizando. Aún nos queda por saber que modelo elegir
    int &modelo_actual = s[nivel_actual];
    if (modelo_actual != -1)
        dinero_gastado -= prendas[nivel_actual].precios[modelo_actual];

    modelo_actual++;
    // Si nos pasamos del número de modelos, no sumamos nada
    dinero_gastado += prendas[nivel_actual].precios[modelo_actual];
}

bool AlgoritmoBT::solucion(const int dinero_gastado, const int M, const int nivel_actual, const int n, const int voa) {
    return dinero_gastado <= M && nivel_actual == n-1 && dinero_gastado > voa;
}

//1er poda - dinero_gastado > M , no tiene caso seguir si superamos M
//2a poda - max_total <= voa, si incluso escogiendo los modelos más caros de cada prenda que nos queda no superamos voa
//3a poda - min_total > M, si incluso escogiendo los modelos más baratos superamos M
//4a poda - si dicho árbol ya lo hemos visitado y lo hemos calculado previamente
bool AlgoritmoBT::criterio(const int dinero_gastado, const int M, const int nivel_actual, const int n, const int voa, vector<int> &max_restante, vector<int> &min_restante, vector<vector<bool>> &visitado) {
    if (nivel_actual >= n - 1 || dinero_gastado > M) return false;

    if (visitado[nivel_actual][dinero_gastado]) return false;
    visitado[nivel_actual][dinero_gastado] = true;

    // Cota mínima posible desde el nivel actual hasta el final
    int min_total = dinero_gastado + min_restante[nivel_actual+1];
    // Cota máxima posible desde el nivel actual hasta el final
    int max_total = dinero_gastado + max_restante[nivel_actual+1];

    if (max_total <= voa) return false;

    return min_total <= M;
}

bool AlgoritmoBT::mas_hermanos(const int num_modelos, const int id_modelo_actual) {
    //Es id_modelo_actual+1 porque en s lo inicializamos todos a -1
    return id_modelo_actual+1 < num_modelos;
}

void AlgoritmoBT::retroceder(int &nivel_actual, int &dinero_gastado, vector<int> &s, vector<ControladorBT::Prenda> &prendas) {
    int &modelo_actual = s[nivel_actual];
    dinero_gastado -= prendas[nivel_actual].precios[modelo_actual];
    modelo_actual = -1;
    --nivel_actual;
}
