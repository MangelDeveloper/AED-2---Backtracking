#ifndef BACKTRACKING_AVANCERAPIDO_CONTROLADOR_H
#define BACKTRACKING_AVANCERAPIDO_CONTROLADOR_H

#include "../Algoritmos/Backtracking.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

class Controlador {
public:



    //Archivo de entrada versión extendida
    static const string INPUT_FILE;

    //Archivo de entrada con test unitarios
    static const string INPUT_TEST_FILE;
    //Archivo de salida con test unitarios
    static const string OUTPUT_TEST_FILE;


    static vector<Backtracking::Caso> leer_entrada();
    static double print_solucion_con_poda();
    static double print_solucion_sin_poda();
    static void generar_datos_aleatorios();
    static void test_oraculo();
};

#endif