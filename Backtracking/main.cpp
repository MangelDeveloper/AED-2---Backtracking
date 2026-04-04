#include <iostream>
#include "Controlador/Controlador.h"

using namespace std;
int main() {
    double tiempo_poda = Controlador::print_solucion_con_poda();
    double tiempo_sin_poda = Controlador::print_solucion_sin_poda();

    cout << "Tiempo con poda: " << tiempo_poda << " segundos."<< endl;
    cout << "Tiempo sin poda: " << tiempo_sin_poda << " segundos." << endl;

    return 0;
}