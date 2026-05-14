// ══════════════════════════════════════════════════════════════════
// INSTRUCCIONES PARA ALEJO
// Lee todo antes de empezar a codear. Está organizado por secciones.
// ══════════════════════════════════════════════════════════════════

// ─────────────────────────────────────────
// CONTEXTO GENERAL
// ─────────────────────────────────────────
// Este es un juego de exploración por cuartos en consola.
// El jugador se mueve con WASD. El mapa es una grilla de chars [12][23].
// 'P' = jugador, '#' = pared, '.' = piso, '?' = evento aleatorio,
// 'W' = well, 'C' = cooler, 'G' = seal (pentagrama)
// Los cuartos se guardan como .txt en ../data/Cuartos/
// El inventario del jugador se guarda en un .txt en ../data/inventario.txt

// ─────────────────────────────────────────
// SECCIÓN 1 — SISTEMA DE EVENTOS AL TOCAR '?'
// (Ve a la línea 468, donde está el if (mapa[nuevafila][nuevacolumna] == '?'))
// ─────────────────────────────────────────

// PASO 1: Guarda el estado actual ANTES de hacer cualquier cosa.
//   - Para guardar el mapa usa guardarMapa(), mirá cómo lo llama PonerPausa():
//       std::string archivoActual = "../data/Cuartos/Cuarto" + std::to_string(habitacion) + ".txt";
//       guardarMapa(archivoActual, mapa);
//   - Para guardar la posición del jugador simplemente guarda fila y columna en variables nuevas:
//       int filaGuardada = fila;
//       int columnaGuardada = columna;
//   - Vas a necesitar estas dos variables más adelante.

// PASO 2: Genera un resultado aleatorio con una función nueva llamada
//   generarEvento(). Esa función retorna un string con el resultado.
//   Usá rand() con los siguientes pesos de probabilidad:
//
//   ALTA probabilidad (70% del total, repartido entre estos 8 objetos):
//     "KeyCard", "LiquidMercury", "HolyCross", "Note1",
//     "Note2", "Coin", "ShotGun", "ShotGunAmmo"
//
//   MEDIA probabilidad (15% del total, repartido entre estas 3 interacciones):
//     "Well", "Cooler", "Seal"
//
//   BAJA probabilidad (15% del total, repartido entre estos):
//     "Monster"  <- (solo un tipo de monstruo, ver PASO 3 CASO C)
//
//   Implementación sugerida:
//     int r = rand() % 100;
//     if (r < 70)      { // objeto       }
//     else if (r < 85) { // interaccion  }
//     else             { // monstruo     }

// PASO 3: Según lo que retornó generarEvento(), hay TRES casos:

//   CASO A — Encontró un OBJETO (KeyCard, Coin, ShotGun, etc.)
//     1. Abrí la imagen del objeto con AbrirImagen(). Mirá la Sección 4 para saber
//        qué nombre pasarle según el objeto encontrado.
//     2. Llama LimpiarPantalla() — es una función que ya existe en el código.
//     3. Espera 1 segundo con: std::this_thread::sleep_for(std::chrono::seconds(1));
//     4. Imprime: "You have found a [nombre del objeto]!"
//     5. Imprime: "Press any key to continue..."
//     6. Espera que el jugador presione cualquier tecla con _getch()
//     7. Guarda el nombre del objeto en el inventario:
//        Abrí (o creá si no existe) ../data/inventario.txt con ofstream en modo append (ios::app)
//        y escribí una línea con el nombre del objeto.
//     8. En el mapa, reemplazá el '?' por '.' (el símbolo desaparece):
//        mapa[nuevafila][nuevacolumna] = '.';
//     9. Mové al jugador a donde estaba el '?':
//        mapa[nuevafila][nuevacolumna] = 'P';
//        mapa[fila][columna] = '.';
//        fila = nuevafila;
//        columna = nuevacolumna;
//    10. Llama mostrarMapa(mapa) para volver al cuarto.

//   CASO B — Encontró una INTERACCIÓN (Well, Cooler, Seal)
//     1. Llama LimpiarPantalla()
//     2. Espera 1 segundo
//     3. Imprime según cuál encontró:
//        - Well  -> "You found a well!"
//        - Cooler -> "You found a cooler!"
//        - Seal  -> "You found a pentagram!"
//     4. Imprime: "Press any key to continue..."
//     5. Espera _getch()
//     6. En el mapa, reemplazá el '?' por el char de la interacción:
//        Well -> 'W',  Cooler -> 'C',  Seal -> 'G'
//     7. El jugador VUELVE a filaGuardada y columnaGuardada (NO se mueve al '?')
//        mapa[fila][columna] = 'P';  <- jugador vuelve a donde estaba
//     8. Llama mostrarMapa(mapa)

//   CASO C — Encontró un MONSTRUO
//     1. Elige aleatoriamente una imagen de monstruo de esta lista con rand():
//        "../data/3D/monster1.png"
//        "../data/3D/monster2.png"
//        "../data/3D/monster3.png"
//        (ponele los nombres que quieras a los archivos, solo asegurate que coincidan)
//        Abrila con AbrirImagen() — mirá Sección 4 para ver cómo funciona.
//     2. Llama LimpiarPantalla()
//     3. Espera 1 segundo
//     4. Imprime: "A monster appeared!"
//     5. Imprime: "Press any key to continue..."
//     6. Espera _getch()
//     7. El jugador VUELVE a filaGuardada y columnaGuardada (igual que en CASO B)
//     8. El '?' desaparece: mapa[nuevafila][nuevacolumna] = '.';
//     9. Llama mostrarMapa(mapa)

// ─────────────────────────────────────────
// SECCIÓN 2 — INTERACTUAR CON W, C, G (Well, Cooler, Pentagrama)
// ─────────────────────────────────────────

// Cuando el jugador camina sobre 'W', 'C' o 'G', hacé lo siguiente:
//   1. Guardá el mapa y la posición del jugador igual que en PASO 1 de Sección 1:
//       std::string archivoActual = "../data/Cuartos/Cuarto" + std::to_string(habitacion) + ".txt";
//       guardarMapa(archivoActual, mapa);
//       int filaGuardada = fila;
//       int columnaGuardada = columna;
//   2. Llama LimpiarPantalla()
//   3. Imprime: "Select an object to use here:"
//   4. Abrí ../data/inventario.txt con ifstream y mostrá cada línea (cada objeto del inventario)
//   5. Esperá que el jugador escriba el nombre de un objeto y presione Enter:
//      std::string objeto;
//      std::cin >> objeto;
//   6. Verificá si ese objeto es válido para esa interacción:
//
//      'W' (Well):
//        - Si objeto == "Coin" -> eliminar Coin del inventario, agregar "KeyMold"
//          Mostrar: "You dropped the coin in the well. You received a KeyMold!"
//
//      'C' (Cooler):
//        - Pedile al jugador DOS objetos separados por espacio:
//          std::string obj1, obj2;
//          std::cin >> obj1 >> obj2;
//        - Si obj1 == "KeyMold" y obj2 == "LiquidMercury" (o al revés):
//          eliminar ambos del inventario, agregar "MetalKey"
//          Mostrar: "You used the KeyMold and LiquidMercury. You received a MetalKey!"
//
//      'G' (Pentagrama):
//        - Si objeto == "HolyCross" -> eliminar HolyCross, agregar "HolyBible"
//          Mostrar: "You placed the cross on the seal. You received the HolyBible!"
//
//   7. Si el objeto no es válido: imprimí "Nothing happened."
//   8. En cualquier caso: esperá _getch(), llamá LimpiarPantalla(), mostrá el mapa
//      con el jugador en filaGuardada y columnaGuardada

//   CÓMO ELIMINAR UN OBJETO DEL INVENTARIO:
//   Leé todas las líneas de inventario.txt a un vector<string>, saltea la línea
//   que coincida con el objeto a eliminar, y reescribí el archivo completo sin ella:
//
//     std::vector<std::string> items;
//     std::ifstream fin("../data/inventario.txt");
//     std::string linea;
//     while (std::getline(fin, linea)) items.push_back(linea);
//     fin.close();
//
//     std::ofstream fout("../data/inventario.txt");
//     for (int i = 0; i < items.size(); i++) {
//         if (items[i] != "NombreAEliminar") fout << items[i] << "\n";
//     }

// ─────────────────────────────────────────
// SECCIÓN 3 — SISTEMA DE COMBINACIÓN (tecla 'i' en el mapa)
// ─────────────────────────────────────────

// Cuando el jugador presiona 'i' mientras está en el mapa:
//   1. Llama LimpiarPantalla()
//   2. Imprime: "What do you want to combine?"
//   3. Mostrá el inventario (leé ../data/inventario.txt línea por línea con ifstream)
//   4. Pedí input: el jugador escribe DOS nombres separados por espacio
//      std::string obj1, obj2;
//      std::cin >> obj1 >> obj2;
//   5. Verificá si esa combinación es válida:
//      - "KeyMold" + "LiquidMercury" (en cualquier orden) -> resultado: "MetalKey"
//        Usá if/else if para que sea fácil agregar más combinaciones después.
//   6. Si es válida:
//      - Eliminá ambos objetos del inventario (usá el método de la Sección 2)
//      - Agregá el nuevo objeto con ofstream en modo ios::app
//      - Mostrá: "You combined [obj1] and [obj2]. You received [resultado]!"
//   7. Si no es válida: mostrá "These items cannot be combined."
//   8. Esperá _getch(), llamá LimpiarPantalla(), mostrá el mapa con mostrarMapa(mapa)

// ─────────────────────────────────────────
// SECCIÓN 4 — FUNCIÓN AbrirImagen (ya existe, solo modificala)
// ─────────────────────────────────────────

// La función AbrirImagen() ya está definida en el código. Modificala para que reciba
// un string con el nombre del archivo como parámetro:
//   void AbrirImagen(std::string nombreImagen)
//
// Que abra: "../data/3D/" + nombreImagen + ".png"
// Mirá cómo está implementada actualmente con #ifdef para Windows/Linux/Mac,
// solo reemplazá el path fijo por el dinámico.
//
// Llamala así según lo que encontró el jugador:
//   - "KeyCard"      -> AbrirImagen("keycard")
//   - "Coin"         -> AbrirImagen("coin")
//   - "ShotGun"      -> AbrirImagen("shotgun")
//   - "LiquidMercury"-> AbrirImagen("mercury")
//   - "HolyCross"    -> AbrirImagen("cross")
//   - "Note1"        -> AbrirImagen("note1")
//   - "Note2"        -> AbrirImagen("note2")
//   - "ShotGunAmmo"  -> AbrirImagen("ammo")
//   - "Well"         -> AbrirImagen("well")
//   - "Cooler"       -> AbrirImagen("cooler")
//   - "Seal"         -> AbrirImagen("seal")
//   - Monstruo       -> AbrirImagen("monster1") o "monster2" o "monster3" (aleatorio con rand())
// Los objetos KeyMold, MetalKey y HolyBible NO tienen imagen porque se obtienen
// a través de interacciones, no de '?'.

// ─────────────────────────────────────────
// NOTAS FINALES
// ─────────────────────────────────────────
// - Para el sleep de 1 segundo usá:
//   std::this_thread::sleep_for(std::chrono::seconds(1));
//   (ya está incluido <thread> y <chrono> en funciones.h)
// - Para limpiar pantalla usá LimpiarPantalla() que ya existe.
// - Para guardar mapa y posición mirá cómo lo hace PonerPausa() en el código.
// - Para eliminar objetos del inventario usá el método explicado en Sección 2.
// - Cualquier duda preguntame — Tomás.



#include "funciones.h"

struct CinematicasMovibles {
    std::string C2 = "../data/Cinematicas/imagen2";
    std::string C25 = "../data/Cinematicas/imagen25";
    std::string C3 = "../data/Cinematicas/imagen3";
    std::string C35 = "../data/Cinematicas/imagen35";
    std::string C4 = "../data/Cinematicas/imagen4";
    std::string C45 = "../data/Cinematicas/imagen45";
    std::string C5 = "../data/Cinematicas/imagen5";
    std::string C55 = "../data/Cinematicas/imagen55";
    std::string C6 = "../data/Cinematicas/imagen6";
    std::string C65 = "../data/Cinematicas/imagen65";
};

struct Conexion {
    int habitacionOrigen;
    char puerta;
    std::string archivoDestino;
    int nuevaFila;
    int nuevaColumna;
    int habitacionDestino;
};

struct Objetos {
    std::string card = "KeyCard";
    std::string mold = "KeyMold";
    std::string liquid = "LiquidMercury";
    std::string cross = "HolyCross";
    std::string bible = "HolyBible";
    std::string notea = "Note1";
    std::string noteb = "Note2";
    std::string coin = "Coin";
    std::string shot = "ShotGun";
    std::string ammo = "ShotGunAmmo";
    std::string key = "MetalKey";
};

struct Interacciones {
    char well = 'W';
    char cooler = 'C';
    char seal = 'S';
};

// tabla con las 15 conexiones
Conexion conexiones[] = {
    {1, '2', "../data/Cuartos/Cuarto2.txt",  5,  1, 2},
    {1, '4', "../data/Cuartos/Cuarto4.txt",  1, 11, 4},
    {2, '1', "../data/Cuartos/Cuarto1.txt",  5, 21, 1},
    {2, '3', "../data/Cuartos/Cuarto3.txt",  1,  1, 3},
    {2, '5', "../data/Cuartos/Cuarto5.txt",  1,  11, 5},
    {3, '2', "../data/Cuartos/Cuarto2.txt",  1, 21, 2},
    {3, '6', "../data/Cuartos/Cuarto6.txt",  1, 11, 6},
    {4, '1', "../data/Cuartos/Cuarto1.txt", 10, 11, 1},
    {4, '5', "../data/Cuartos/Cuarto5.txt",  4,  1, 5},
    {5, '4', "../data/Cuartos/Cuarto4.txt",  5, 21, 4},
    {5, '2', "../data/Cuartos/Cuarto2.txt", 10, 11, 2},
    {5, '6', "../data/Cuartos/Cuarto6.txt",  4,  1, 6},
    {5, '7', "../data/Cuartos/Cuarto7.txt",  1, 11, 7},
    {6, '5', "../data/Cuartos/Cuarto5.txt",  4,  21, 5},
    {6, '3', "../data/Cuartos/Cuarto3.txt", 10, 11, 3},
};

int totalConexiones = 15;

// ────────────────────────────────────────-


void LimpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void CargarCinematica(const std::string& archivo, char arr[100][100]){

    std::ifstream file(archivo);

    if (!file.is_open()) {
        std::cout << "Error al abrir mapa\n";
        return;
    }
    bool out = false;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            file.get(arr[i][j]);
            if (arr[i][j] == '\n') break;
            if (arr[i][j] == '~'){
                out = true;
            }
        }
        if (out == true) break;
    }

    file.close();

}

void MostrarCinematica(char arr[100][100]) {
    LimpiarPantalla();
    std::cout.flush();
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            if (arr[i][j] == '~') return;
            if (arr[i][j] == '\0') break;
            std::cout << arr[i][j];
        }
        std::cout << "\n";
    }
    std::cout.flush();
}

void Cinematicas(){
    std::string arr[] = {
        "../data/Cinematicas/Imagen1.txt",
        "../data/Cinematicas/Imagen15.txt",
        "../data/Cinematicas/Imagen2.txt",
        "../data/Cinematicas/Imagen25.txt",
        "../data/Cinematicas/Imagen3.txt",
        "../data/Cinematicas/Imagen35.txt",
        "../data/Cinematicas/Imagen4.txt",
        "../data/Cinematicas/Imagen45.txt",
        "../data/Cinematicas/Imagen5.txt",
        "../data/Cinematicas/Imagen55.txt",
        "../data/Cinematicas/imagen6.txt",
        "../data/Cinematicas/imagen65.txt",
        "../data/Cinematicas/Imagen7.txt",
        "../data/Cinematicas/Imagen75.txt",
    };

    std::string* p = arr;

    for (int i = 0; i < 13; i += 2) {

        for (int t = 0; t < 11; t++) {

            char cine1[100][100] = {};
            CargarCinematica(*(p + i), cine1);
            MostrarCinematica(cine1);
            std::this_thread::sleep_for(std::chrono::milliseconds(800));

            char cine2[100][100] = {};
            CargarCinematica(*(p + i + 1), cine2);
            MostrarCinematica(cine2);
            std::this_thread::sleep_for(std::chrono::milliseconds(800));
        }
    }
}

void AbrirImagen(){

    #if defined(_WIN32) || defined(_WIN64)

        //system("start imagen");

    #elif defined(__linux__)

        //system("xdg-open imagen");

    #elif defined(__APPLE__) || defined(__MACH__)

        //system("open imagen");

    #endif
}

void cargarMapa(const std::string& archivo, char mapa[12][23]) {

    std::ifstream file(archivo);

    if (!file.is_open()) {
        std::cout << "Error al abrir mapa\n";
        return;
    }

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 23; j++) {
            file.get(mapa[i][j]);
        }
        file.ignore();
    }

    file.close();
}

void guardarMapa(const std::string& archivo, char mapa[12][23]) {
    std::ofstream file(archivo);

    if (!file.is_open()) {
        std::cout << "Error al guardar mapa\n";
        return;
    }

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 23; j++) {
            file << mapa[i][j]; 
        }
        file << "\n";
    }

    file.close();
}

void mostrarMapa(char mapa[12][23]) {

    LimpiarPantalla();

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 23; j++) {
            std::cout << mapa[i][j];
        }
        std::cout << "\n";
    }
}

void movimiento() {
    
    char mapa[12][23];
    int habitacion = 1;
    int fila = 1;
    int columna = 1;

    cargarMapa("../data/Cuartos/Cuarto1.txt", mapa);
    mostrarMapa(mapa);

    while (true) {

        char tecla = _getch();

        int nuevafila = fila;
        int nuevacolumna = columna;

        if (tecla == 'm') {
            PonerPausa(mapa, habitacion, fila, columna);
            continue;
        }
        if (tecla == 'd') {
            nuevacolumna = columna+1;
        }else if (tecla == 'a'){
            nuevacolumna = columna-1;
        } else if (tecla == 'w'){
            nuevafila = fila -1;
        } else if (tecla == 's'){
            nuevafila = fila+1;
        }
        
        if (mapa[nuevafila][nuevacolumna] == '#') continue;
        //Instrucciones aqui:
        //Tienes que poner que cuando el personaje toca un ? (ya te lo puse aqui abajo) pasen 3 cosas.
        if (mapa[nuevafila][nuevacolumna] == '?'){

        }
        char celdaDestino = mapa[nuevafila][nuevacolumna];
        bool cambio = false;
        
        for (int i = 0; i < totalConexiones; i++) {
            if ((conexiones[i].habitacionOrigen == habitacion) &&
                (conexiones[i].puerta == celdaDestino)) {

                mapa[fila][columna] = '.';

                std::string archivoActual = "../data/Cuartos/Cuarto" + std::to_string(habitacion) + ".txt";
                guardarMapa(archivoActual, mapa);

                cargarMapa(conexiones[i].archivoDestino, mapa);

                fila       = conexiones[i].nuevaFila;
                columna    = conexiones[i].nuevaColumna;
                habitacion = conexiones[i].habitacionDestino;

                mapa[fila][columna] = 'P';

                mostrarMapa(mapa);
                cambio = true;
                break;
            }
        }

        if (cambio) continue;

        char temp = mapa[nuevafila][nuevacolumna];
        mapa[nuevafila][nuevacolumna] = mapa[fila][columna];
        mapa[fila][columna] = temp;

        fila = nuevafila;
        columna  = nuevacolumna;

        mostrarMapa(mapa);
    }

}

void ResetearCuartos(){
    for (int i = 1; i <= 7; i++) {
        std::string origen = "../data/CuartosOriginales/Cuarto" + std::to_string(i) + ".txt";
        std::string destino = "../data/Cuartos/Cuarto" + std::to_string(i) + ".txt";

        std::ifstream src(origen);
        std::ofstream dst(destino);

        for (char c; src.get(c);) {
            dst << c;
        }
    }
}

void PonerPausa(char mapa[12][23], int habitacion, int fila, int columna){
    std::string archivoActual = "../data/Cuartos/Cuarto" + std::to_string(habitacion) + ".txt";
    guardarMapa(archivoActual, mapa);

    LimpiarPantalla();
    std::cout <<"PAUSE\n";
    std::cout <<"Press 'j' to continue playing or press 's' to exit\n";
    std::cout <<"Warning, if you choose to exit now your progress will not be saved!\n";

    while (true) {
        char tecla = _getch();
        if (tecla == 'j') {
            mostrarMapa(mapa);
            return;
        } else if (tecla == 's') {
            ResetearCuartos();
            exit(0);
        }
    }
}