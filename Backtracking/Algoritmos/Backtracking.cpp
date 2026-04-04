#include "Backtracking.h"

using Solucion = optional<vector<int>>;

Backtracking::Resultado Backtracking::backtracking_con_poda(Caso caso) {
    //Número de niveles máximo del árbol
    const int n = caso.num_prendas;
    //Vector solución
    vector s(n,-1);
    //Dinero usado actualmente
    int dinero_gastado = 0;
    //Nivel actual en el que me encuentro
    int nivel = 0;
    //Dinero máximo a gastar
    const int M = caso.presupuesto;
    //Las prendas de vestir
    vector<Prenda> &prendas = caso.prendas;
    //Iniciamos el voa a -infinito
    int voa = numeric_limits<int>::min();
    //Solución óptima actual
    Solucion soa;
    //Memoización para detectar duplicidad de árbol que ya hemos recorrido previamente
    vector<vector<bool>> visitado(n, vector<bool>(M+1,false));
    //Booleano que indica si hemos llegado al máximo valor de voa, es decir, cuando voa == M
    bool is_best_solucion = false;

    while (nivel != -1 && !is_best_solucion) {
        //Generar un nodo hermano
        generar(nivel, dinero_gastado, s, prendas);

        //Si encuentro una solución mejor que voa, guardamos soa y voa
        if (solucion(dinero_gastado, M, nivel, n, voa)) {
            soa = s;
            voa = dinero_gastado;

            if (voa == M) is_best_solucion = true;
        }

        if (!is_best_solucion) {
            //Si podríamos llegar a una solución mejor, seguimos bajando
            if (criterio_con_poda(dinero_gastado, nivel, voa, visitado, caso)) nivel++;
            else {
                //Si no, retrocedo hasta encontrar un nodo con más hermanos
                while (nivel >= 0 && !mas_hermanos(prendas[nivel].num_modelos , s[nivel])) {
                    retroceder(nivel, dinero_gastado, s, prendas);
                }
            }
        }
    }

    return {voa, soa};
}

Backtracking::Resultado Backtracking::backtracking_sin_poda(Caso caso) {
    //Número de niveles máximo del árbol
    const int n = caso.num_prendas;
    //Vector solución
    vector s(n,-1);
    //Dinero usado actualmente
    int dinero_gastado = 0;
    //Nivel actual en el que me encuentro
    int nivel = 0;
    //Dinero máximo a gastar
    const int M = caso.presupuesto;
    //Las prendas de vestir
    vector<Prenda>& prendas = caso.prendas;
    //Iniciamos el voa a -infinito
    int voa = numeric_limits<int>::min();
    //Solución óptima actual
    Solucion soa;

    while (nivel != -1) {
        //Generar un nodo hermano
        generar(nivel, dinero_gastado, s, prendas);

        //Si encuentro una solución mejor que voa, guardamos soa y voa
        if (solucion(dinero_gastado, M, nivel, n, voa)) {
            soa = s;
            voa = dinero_gastado;
        }

        //Si podríamos llegar a una solución mejor, seguimos bajando
        if (criterio_sin_poda(dinero_gastado, nivel, caso)) nivel++;
        else {
            //Si no, retrocedo hasta encontrar un nodo con más hermanos
            while (nivel >= 0 && !mas_hermanos(prendas[nivel].num_modelos , s[nivel])) {
                retroceder(nivel, dinero_gastado, s, prendas);
            }
        }
    }

    return {voa, soa};
}

void Backtracking::generar(int &nivel, int &dinero_gastado, vector<int> &s, vector<Prenda> &prendas) {
    //NOTA: Recordemos que cada nivel es una prenda, por tanto, nivel_actual contiene el índice de la prenda
    //que estamos analizando. Aún nos queda por saber que modelo elegir
    int &modelo_actual = s[nivel];

    if (modelo_actual != -1)
        dinero_gastado -= prendas[nivel].precios[modelo_actual];

    modelo_actual++;

    // Si nos pasamos del número de modelos, no sumamos nada
    dinero_gastado += prendas[nivel].precios[modelo_actual];
}

bool Backtracking::solucion(const int dinero_gastado, const int M, const int nivel, const int n, const int voa) {
    return dinero_gastado <= M && nivel == n-1 && dinero_gastado > voa;
}

//1er poda - dinero_gastado > M , no tiene caso seguir si superamos M
//2a poda - max_total <= voa, si incluso escogiendo los modelos más caros de cada prenda que nos queda no superamos voa
//3a poda - min_total > M, si incluso escogiendo los modelos más baratos superamos M
bool Backtracking::criterio_con_poda(const int dinero_gastado, const int nivel, const int voa, vector<vector<bool>> &visitado, Caso &caso) {
    if (nivel >= caso.num_prendas - 1 || dinero_gastado > caso.presupuesto) return false;

    if (visitado[nivel][dinero_gastado]) return false;
    visitado[nivel][dinero_gastado] = true;

    // Cota mínima posible desde el nivel actual hasta el final
    int min_total = dinero_gastado + caso.min_restante[nivel+1];
    // Cota máxima posible desde el nivel actual hasta el final
    int max_total = dinero_gastado + caso.max_restante[nivel+1];

    if (max_total <= voa) return false;

    return min_total <= caso.presupuesto;
}

bool Backtracking::criterio_sin_poda(const int dinero_gastado, const int nivel, Caso &caso) {
    return nivel < caso.num_prendas - 1 && dinero_gastado <= caso.presupuesto;
}

bool Backtracking::mas_hermanos(const int num_modelos, const int id_modelo_actual) {
    //Es id_modelo_actual+1 porque en s lo inicializamos todos a -1
    return id_modelo_actual+1 < num_modelos;
}

void Backtracking::retroceder(int &nivel, int &dinero_gastado, vector<int> &s, vector<Prenda> &prendas) {
    int &modelo_actual = s[nivel];
    dinero_gastado -= prendas[nivel].precios[modelo_actual];
    modelo_actual = -1;
    --nivel;
}
