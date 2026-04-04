#include "Controlador.h"

//Archivo de entrada versión extendida del problema
const string Controlador::INPUT_FILE = "../Entrada/Entrada_Backtracking.in";

//Archivo de entrada con test unitarios
const string Controlador::INPUT_TEST_FILE = "../Entrada/entrada_test.txt";
//Archivo de salida con test unitarios
const string Controlador::OUTPUT_TEST_FILE = "../Salida/salida_test.txt";

vector<Backtracking::Caso> Controlador::leer_entrada() {
    ifstream archivo (INPUT_FILE);
    vector<Backtracking::Caso> casos;

    if (!archivo) {
        cerr << "No se pudo abrir el archivo: " << INPUT_FILE << "\n";
        return casos;
    }

    //Lee el número de casos de prueba
    int N;
    archivo >> N;
    casos.reserve(N);

    for (int i = 0; i < N; i++) {
        //Leemos el presupuesto disponible (M) y el número de prendas a comprar (C)
        int M,C;
        archivo >> M >> C;

        Backtracking::Caso caso;
        caso.presupuesto = M;
        caso.num_prendas = C;

        //Creamos espacio suficiente para cada prenda
        caso.prendas.resize(C);
        for (int j = 0; j < C; j++) {
            //Leemos el número de modelos de dicha prenda (K)
            archivo >> caso.prendas[j].num_modelos;

            const int num_modelos = caso.prendas[j].num_modelos;

            //Creamos espacio suficiente para cada modelo poner su correspondiente precio
            caso.prendas[j].precios.resize(num_modelos);
            for (int k = 0; k < num_modelos; k++) {
                //Leemos los precios de cada modelo de la prenda j
                archivo >> caso.prendas[j].precios[k];
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

    //Cerramos conexión con el archivo que hemos leido
    archivo.close();
    //Devolvemos todos los casos de prueba
    return casos;
}

double Controlador::print_solucion_con_poda() {
    vector <Backtracking::Caso> casos = leer_entrada();

    auto it_casos = casos.begin();

    auto start = high_resolution_clock::now();
    while (it_casos != casos.end()) {
        Backtracking::Caso caso = *it_casos;

        Backtracking::Resultado resultado = Backtracking::backtracking_con_poda(caso);

        if (resultado.voa == numeric_limits<int>::min()) cout << "no solution" << endl;
        else cout << resultado.voa << endl;

        ++it_casos;
    }

    auto end = high_resolution_clock::now();

    //Duración del tiempo del algoritmo con poda
    return duration<double>(end - start).count();
}

double Controlador::print_solucion_sin_poda() {
    vector <Backtracking::Caso> casos = leer_entrada();
    auto it_casos = casos.begin();

    auto start = high_resolution_clock::now();
    while (it_casos != casos.end()) {
        Backtracking::Caso caso = *it_casos;

        Backtracking::Resultado resultado = Backtracking::backtracking_sin_poda(caso);

        if (resultado.voa == numeric_limits<int>::min()) cout << "no solution" << endl;
        else cout << resultado.voa << endl;

        ++it_casos;
    }
    auto end = high_resolution_clock::now();

    //Duración del tiempo del algoritmo sin poda
    return duration<double>(end - start).count();
}


/*
void ControladorBT::generar_datos_aleatorios() {
    srand(time(nullptr));
    ofstream outFichero (INPUT_FILE);

    unordered_set<char> conjunto = generar_conjunto_aleatorio();

    int longitudes [] = {5, 10, 20, 50, 100, 1000};
    for (int longitud : longitudes) {
        string cadena = generar_cadena_aleatoria(longitud,conjunto);
        outFichero << cadena << endl;

        for (char c : conjunto) {
            outFichero << c;
        }
        outFichero << endl;
    }
    outFichero.close();
}


void ControladorBT::test_oraculo() {
    ifstream inFichero (INPUT_FILE);
    ofstream outFichero (OUTPUT_FILE);

    string cadena;
    while (inFichero >> cadena) {
        outFichero << "Entrada: '" << cadena << "'" << endl;
        outFichero << "Tamaño entrada: '" << cadena.size() << "'" << endl;
        unordered_set<char> conjunto = leer_conjunto(inFichero);
        outFichero << "Conjunto: { ";
        for (char c : conjunto) {
            outFichero << c << " ";
        }
        outFichero << "}" << endl;

        Backtracking_con_poda::Resultado oraculo = Algoritmo::iterativo(conjunto,cadena,0,cadena.size()-1);
        Backtracking_sin_poda::Resultado resultado = Algoritmo::divide_y_venceras(conjunto,cadena,0,cadena.size()-1);

        outFichero << "Salida esperada (Iterativo):" << endl;
        mostrar_resultado(oraculo,outFichero);

        outFichero << "Resultado (DyV):" << endl;
        mostrar_resultado(resultado,outFichero);

        outFichero << endl;
    }
    inFichero.close();
    outFichero.close();
}

void ControladorBT::test_tiempo(bool peor) {
    ofstream outFichero (OUTPUT_FILE);
    outFichero << "i0,i1,i2,i3,i4,i5,i6,i7,i8,i9,i10" << endl;
    cout << "Terminado encabecado." << endl;

    unordered_set<char> conjunto;
    const char conjuntoReferencia [] = {'a','b','c','d','e'};
    for (int i = 0; i < TAM_CONJUNTO; i++) {
        conjunto.insert(conjuntoReferencia[i]);
    }

    for (int fila = 0; fila < 11; fila++) {
        for (int col = 0; col < 11; col++) {
            string cadena = "";
            int tamEntrada  = 1000*pow(2,col);
            if (peor) {
                //El peor caso es que la cadena n-4 subcadenas que
                //cumplan la condicion de tener todas las letras del
                //conjunto. Ya que tiene que ir realizando el merge de los resultados.
                int letraConjunto = 0;
                for (int z = 0; z < tamEntrada; z++) {
                    cadena += conjuntoReferencia[letraConjunto];
                    letraConjunto = (letraConjunto+1)%TAM_CONJUNTO;
                }

            }else {
                //El mejor caso es que la cadena nunca cumpla la condición.
                //Ya que al hacer el merge de los resultados no tiene que hacer nada.
                for (int z = 0; z < tamEntrada; z++) {
                    cadena += 'z';
                }
            }

            //Simulamos y medimos los tiempos de ejecución.
            auto empezar = steady_clock::now();
            Algoritmo::Resultado resultado = Algoritmo::divide_y_venceras(conjunto,cadena,0,cadena.size()-1);
            auto terminar = steady_clock::now();
            auto duracion = duration_cast<microseconds>(terminar - empezar);

            //Obtenemos los datos en microsegundos.
            outFichero << duracion.count();

            //Cerramos fila.
            if (col != 10) {
                outFichero  << ",";
            }else {
                outFichero << endl;
            }
        }
        cout << "Terminado fila " << fila << "." << endl;
    }
        outFichero.close();
}
*/