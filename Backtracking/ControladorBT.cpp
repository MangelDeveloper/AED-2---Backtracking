#include "./ControladorBT.h"
#include <chrono>
#include <iostream>
#include <algorithm>

#define TAM_CONJUNTO 5

using namespace std;
using namespace std::chrono;


vector<ControladorBT::Caso> ControladorBT::leer_entrada() {
    vector<Caso> casos;

    //Lee el número de casos de prueba
    int N;
    cin >> N;
    casos.reserve(N);

    for (int i = 0; i < N; i++) {
        //Leemos el presupuesto disponible (M) y el número de prendas a comprar (C)
        int M,C;
        cin >> M >> C;

        Caso caso;
        caso.presupuesto = M;
        caso.num_prendas = C;

        //Creamos espacio suficiente para cada prenda
        caso.prendas.resize(C);
        for (int j = 0; j < C; j++) {
            //Leemos el número de modelos de dicha prenda (K)
            cin >> caso.prendas[j].num_modelos;

            const int num_modelos = caso.prendas[j].num_modelos;

            //Creamos espacio suficiente para cada modelo poner su correspondiente precio
            caso.prendas[j].precios.resize(num_modelos);
            for (int k = 0; k < num_modelos; k++) {
                //Leemos los precios de cada modelo de la prenda j
                cin >> caso.prendas[j].precios[k];
            }

            //Ordenamos los precios de mayor a menor de los modelos, para de esta manera obtener el valor máximo antes
            //Y de esta manera con la cota superior fiable podar antes.
            sort(caso.prendas[j].precios.begin(),caso.prendas[j].precios.end(),greater<int>());
        }

        //Calculamos el mínimo y máximo precio a gastar desde i hasta el final
        caso.max_restante.resize(C);
        caso.min_restante.resize(C);
        int last = C - 1;
        caso.max_restante[last] = caso.prendas[last].precios[0];
        caso.min_restante[last] = caso.prendas[last].precios.back();
        for (int k = last-1; k >= 0; k--) {
            caso.max_restante[k] = caso.prendas[k].precios[0] + caso.max_restante[k+1];
            caso.min_restante[k] = caso.prendas[k].precios.back() + caso.min_restante[k+1];
        }

        //Insertamos caso de prueba
        casos.push_back(move(caso));
    }

    //Devolvemos todos los casos de prueba
    return casos;
}