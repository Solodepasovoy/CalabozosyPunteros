// ─────────────────────────────────────────
// PENDIENTE PARA ALEJO
// ─────────────────────────────────────────

// ── 1. EVENTO AL TOCAR '?' ──────────────────────────────────────
// En movimiento(), donde dice if (mapa[nuevafila][nuevacolumna] == '?'):
// Reemplazá el Monstruo() directo por una función generarEvento() que:
//   - Guarde el mapa y posición (archivoActual, filaGuardada, columnaGuardada)
//   - Con rand() % 100 decida si fue objeto (0-69), interacción (70-84) o monstruo (85-99)
//   - Si fue OBJETO:
//       AbrirImagen("keycard") / ("coin") / ("shotgun") etc según cuál tocó
//       LimpiarPantalla()
//       Imprimí "You found a X!" y "It has been added to your inventory."
//       Guardá en ../data/inventario.txt con ofstream en modo ios::app
//       Esperá 2 segundos, borrá el '?', volvé al jugador a filaGuardada/columnaGuardada
//       guardarMapa(), mostrarMapa()
//   - Si fue INTERACCIÓN (Well/Cooler/Seal):
//       AbrirImagen("well") / ("cooler") / ("seal")
//       LimpiarPantalla()
//       Imprimí "You found a well!" etc
//       Imprimí "Press any key to continue..." y esperá _getch()
//       Reemplazá '?' por 'W' / 'C' / 'G' en el mapa
//       Volvé al jugador a filaGuardada/columnaGuardada
//       guardarMapa(), mostrarMapa()
//   - Si fue MONSTRUO:
//       AbrirImagen("monster1") / ("monster2") / ("monster3") — aleatorio
//       LimpiarPantalla()
//       Imprimí "A monster appeared!" y "Press any key to continue..."
//       Esperá _getch(), borrá '?', volvé al jugador a filaGuardada/columnaGuardada
//       guardarMapa(), mostrarMapa()
//       Llamá Monstruo(mapa, habitacion, fila, columna)

// ── 2. INTERACTUAR CON 'W', 'C', 'G' ───────────────────────────
// En movimiento(), agregá estos casos ANTES del swap del jugador:
//   if (mapa[nuevafila][nuevacolumna] == 'W') { ... }
//   if (mapa[nuevafila][nuevacolumna] == 'C') { ... }
//   if (mapa[nuevafila][nuevacolumna] == 'G') { ... }
// Cada uno debe:
//   Guardar mapa y posición
//   LimpiarPantalla()
//   Imprimí "Select an object to use here:" y "(Press 'b' to go back to the map)"
//   Mostrá el inventario leyendo ../data/inventario.txt línea por línea con ifstream
//   Leer std::string objeto con std::cin >> objeto
//   Si objeto == "b": LimpiarPantalla(), mostrarMapa(mapa), continue
//   Verificar si el objeto es válido para esa interacción:
//     'W': objeto válido = "Coin" → eliminarlo, agregar "KeyMold", reemplazar 'W' por '.'
//     'C': objeto válido = "MetalKey" → eliminarlo, reemplazar 'C' por '.'
//     'G': objeto válido = "HolyCross" → eliminarlo, agregar "HolyBible", reemplazar 'G' por '.'
//   Si inválido: LimpiarPantalla(), "Invalid object. Nothing happened.", 1 segundo, mostrarMapa()
//   Si válido: guardarMapa(), LimpiarPantalla(), volver al jugador, mostrarMapa()
// Para eliminar un objeto del inventario usá el método de leer todo en vector,
// reescribir sin ese elemento (ver instrucciones originales)

// ── 3. INVENTARIO CON TECLA 'i' ─────────────────────────────────
// En movimiento(), agregá: if (tecla == 'i') { ... }
//   Guardar mapa y posición
//   LimpiarPantalla()
//   Imprimí "INVENTORY — What do you want to combine?"
//   Imprimí "(Press 'b' to go back to the map)"
//   Mostrá el inventario leyendo ../data/inventario.txt con ifstream
//   Leer std::string obj1 con std::cin >> obj1
//   Si obj1 == "b": LimpiarPantalla(), mostrarMapa(mapa), continue
//   Leer std::string obj2 con std::cin >> obj2
//   Verificar combinación:
//     "KeyMold" + "LiquidMercury" (cualquier orden) → eliminar ambos, agregar "MetalKey"
//     Imprimí "You combined KeyMold and LiquidMercury. You received a MetalKey!"
//   Si inválida: LimpiarPantalla(), "Invalid combination.", 1 segundo, mostrarMapa()
//   Si válida: 1 segundo, LimpiarPantalla(), mostrarMapa()

// ── 4. PUERTA BLOQUEADA 'D' ──────────────────────────────────────
// En movimiento(), agregá: if (mapa[nuevafila][nuevacolumna] == 'D') { ... }
//   Guardar mapa y posición
//   AbrirImagen("door")  ← usa esta función, abre en ventana aparte
//   LimpiarPantalla()
//   Imprimí "The door is locked."
//   Imprimí "Select an object to use:" y "(Press 'b' to go back to the map)"
//   Mostrá el inventario con ifstream
//   Leer std::string objeto con std::cin >> objeto
//   Si objeto == "b": LimpiarPantalla(), mostrarMapa(mapa), continue
//   Si objeto == "MetalKey":
//     Imprimí "The door opened!"
//     Eliminar "MetalKey" del inventario
//     Reemplazar 'D' por '.' en el mapa
//     guardarMapa(), LimpiarPantalla(), volver jugador, mostrarMapa()
//   Si inválido: LimpiarPantalla(), "Invalid object. This doesn't work here."
//     1 segundo, volver jugador, guardarMapa(), mostrarMapa()



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

struct ImagesMonstruos{
    std::string B = "boss.png";
    std::string a = "monster1.png";
    std::string b = "monster2.png";
    std::string c = "monster3.png";
    std::string d = "monster4.png";
    std::string e = "monster5.png";
    std::string f = "monster6.png";
};

struct ImagesObjetos{
    std::string ammo = "Ammo.png";
    std::string coin = "Coin.png";
    std::string holyCross = "HolyCross.png";
    std::string keyCard = "KeyCard.png";
    std::string liquidMercury = "LiquidMercury.png";
    std::string shotGun = "ShotGun.png";
    std::string note1 = "Note1.png";
    std::string note2 = "Note2.png";
};

struct ImagesInteracciones{
    std::string puerta = "puerta.png";
    std::string seal = "Seal.png";
    std::string c = "C.png";
    std::string w = "W.png";
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

int VidaJugador = 100;

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

void AbrirImagen(std::string archivo){

    std::string paralinux = "xdg-open ../data/3D/" + archivo;
    std::string paramac = "open ../data/3D/" + archivo;
    std::string parawin = "start ..\\data\\3D\\" + archivo;


    #if defined(_WIN32) || defined(_WIN64)
        
        system(parawin.c_str());

    #elif defined(__linux__)

        system(paralinux.c_str());

    #elif defined(__APPLE__) || defined(__MACH__)

        system(paramac.c_str());

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

    if (VidaJugador <= 0){
        Morir();
        return;
    } 
    
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
            mapa[nuevafila][nuevacolumna] = '.';
            Monstruo(mapa, habitacion, fila, columna);
            continue;
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

void JugadorCara(){
    if (VidaJugador >= 75){
        std::cout << "    .-----------.  \n";
        std::cout << "   /   ,_,_,_,  \\ \n";
        std::cout << "  |   /       \\  |\n";
        std::cout << "  |  |  ¬   ¬  |  |\n";
        std::cout << "  |  |  o   o  |  |\n";
        std::cout << "  |  |    _    |  |\n";
        std::cout << "  |  |   ___   |  |\n";
        std::cout << "  |  \\_______/   |\n";
        std::cout << "  |               |\n";
        std::cout << "   \\            /\n";
        std::cout << "    '-----------'  \n";
    } else if(VidaJugador >= 40 && VidaJugador < 75){
        std::cout << "    .-----------.  \n";
        std::cout << "   /   ,_,_,_,  \\ \n";
        std::cout << "  |   /  / \\ \\  |\n";
        std::cout << "  |  |  '   '  |  |\n";
        std::cout << "  |  |  °   /\\|  |\n";
        std::cout << "  |  |    _    |  |\n";
        std::cout << "  |  |   ___   |  |\n";
        std::cout << "  |  \\_______/   |\n";
        std::cout << "  |               |\n";
        std::cout << "  \\             / \n";
        std::cout << "    '-----------'  \n";
    } else if (VidaJugador > 0 && VidaJugador < 40){
        std::cout << "    .-----------.  \n";
        std::cout << "   /   ,_,_,_,  \\ \n";
        std::cout << "  |   /  x x \\   |\n";
        std::cout << "  |  |  .   -  |  |\n";
        std::cout << "  |  |    _    |  |\n";
        std::cout << "  |  |  _____  |  |\n";
        std::cout << "  |  \\_______/   |\n";
        std::cout << "  |               |\n";
        std::cout << "  \\             / \n";
        std::cout << "    '-----------'  \n";
    } else if (VidaJugador <= 0){
        std::cout << "    .-----------.  \n";
        std::cout << "   /   ,_,_,_,  \\ \n";
        std::cout << "  |   /  x x  \\  |\n";
        std::cout << "  |  |  X   X  |  |\n";
        std::cout << "  |  |  |   |  |  |\n";
        std::cout << "  |  |  |   |  |  |\n";
        std::cout << "  |  \\_|___|_/   |\n";
        std::cout << "  |     |   |     |\n";
        std::cout << "  \\    |   |    / \n";
        std::cout << "    '---|---|---'  \n";
        std::cout << "        |   |      \n";
        std::cout << "        |   |      \n";
    }
}

void CorrerASCI(){
    LimpiarPantalla();
    std::cout << "               ~~~~~~~~~~~~~~~                \n";
    std::cout << "              /               \\              \n";
    std::cout << "              |  [ 0 ] [ 0 ]  |               \n";
    std::cout << "              |       ^       |               \n";
    std::cout << "              |    _______    |               \n";
    std::cout << "              |   /   0   \\  |               \n";
    std::cout << "              |  |   OOO   |  |               \n";
    std::cout << "              |  | OOOOOOO |  |               \n";
    std::cout << "  | | | |     |  |OOOOOOOOO|  |     | | | |   \n";
    std::cout << "  | | | |     |  \\ OOOOO /   |     | | | |   \n";
    std::cout << " /| | | |     |   \\_____/    |     | | | |\\ \n";
    std::cout << "| | | | |     |               |     | | | | | \n";
    std::cout << "| |_| |_|     |  \\_______/   |     |_| |_| | \n";
    std::cout << "|   ___        \\             /       ___   | \n";
    std::cout << " \\_____\\     ~~~~~~~~~~~~~~~        /_____/ \n";
    std::cout << "                                              \n";
    std::cout << "              PRESS SPACE FAST!               \n";
    }

void Correr(char mapa[12][23], int& habitacion, int& fila, int& columna) {
    CorrerASCI();
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));

    if (!_kbhit() || _getch() != ' ') {
        LimpiarPantalla();
        VidaJugador  = VidaJugador - 30;
        Fight();
        return;
    }

    int tiempoTotal = 0;

    while (tiempoTotal < 10000) {
        CorrerASCI();
        std::this_thread::sleep_for(std::chrono::milliseconds(400));

        if (!_kbhit() || _getch() != ' ') {
            LimpiarPantalla();
            VidaJugador = VidaJugador - 30;
            Fight();
            return;
        }

        tiempoTotal += 400;
    }

    LimpiarPantalla();
    int r = rand() % 100;
    if (r < 60) {
        Fight();
        return;
    } else {
        Flee(mapa, habitacion, fila, columna);
        return;
    }
}

void Fight(){
    
}

void Rendirse(char mapa[12][23], int& habitacion, int& fila, int& columna){
    int r = rand() % 100;
    if (r < 50){
        VidaJugador = 0;
        Morir();
    } else {
        Suerte(mapa, habitacion, fila, columna);
    }
}

void Morir(){
    LimpiarPantalla();
    std::cout << "GAME OVER; HAZ MUERTO\n";
    std::cout << "           ______\n";
    std::cout << "        .-\"      \"-.\n";
    std::cout << "       /            \\\n";
    std::cout << "      |              |\n";
    std::cout << "      |,  .-.  .-.  ,|\n";
    std::cout << "      | )(__/  \\__)( |\n";
    std::cout << "      |/     /\\     \\|\n";
    std::cout << "      (_     ^^     _)\n";
    std::cout << "       \\__|IIIIII|__/\n";
    std::cout << "        | \\IIIIII/ |\n";
    std::cout << "        \\          /\n";
    std::cout << "         `--------`\n";
    exit(0);
}

void Suerte(char mapa[12][23], int& habitacion, int& fila, int& columna) {
    std::string archivoActual = "../data/Cuartos/Cuarto" + std::to_string(habitacion) + ".txt";
    guardarMapa(archivoActual, mapa);

    LimpiarPantalla();
    std::cout << "The ghost let you go...\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));

    mapa[fila][columna] = 'P';
    guardarMapa(archivoActual, mapa);
    mostrarMapa(mapa);
}

void Flee(char (mapa)[12][23], int& habitacion, int& fila, int& columna){

    mapa[fila][columna] = '.';
    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 23; j++)
            if (mapa[i][j] == 'P') { mapa[i][j] = '.'; break; }

    std::string archivoActual = "../data/Cuartos/Cuarto" + std::to_string(habitacion) + ".txt";
    guardarMapa(archivoActual, mapa);

    int indice;
    do { indice = rand() % totalConexiones; }
    while (conexiones[indice].habitacionDestino == 7);

    cargarMapa(conexiones[indice].archivoDestino, mapa);
    mapa[1][1] = 'P';
    guardarMapa(conexiones[indice].archivoDestino, mapa);

    // Actualiza las vars de movimiento() directamente por referencia
    habitacion = conexiones[indice].habitacionDestino;
    fila       = 1;
    columna    = 1;

    LimpiarPantalla();
    std::cout << "You managed to flee!\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    LimpiarPantalla();
    mostrarMapa(mapa);
    // Al retornar, movimiento() ya tiene mapa/fila/columna/habitacion correctos
}

void Monstruo(char mapa[12][23], int &habitacion, int& fila, int& columna){
    if (VidaJugador <= 0){
        Morir();
        return;
    } 
    ImagesMonstruos img;
    std::string lista[] = {img.B, img.a, img.b, img.c, img.d, img.e, img.f};
    std::string imagen = lista[rand() % 7];

    std::string archivoActual = "../data/Cuartos/Cuarto" + std::to_string(habitacion) + ".txt";
    guardarMapa(archivoActual, mapa);
    LimpiarPantalla();
    AbrirImagen(imagen);
    std::cout << "You have found a Ghost!\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    int vidaM = rand() % 31 + 10;
    LimpiarPantalla();
    std::cout << "Ghost's life: " << vidaM << ": ";
    for (int i = 0; i < vidaM/10; i++) std::cout << "-";
    std::cout << "\n";
    std::cout << "|_______Entity________|";
    std::cout << "\n";
    std::cout << "    ----------     \n";
    std::cout << "   /          \\   \n";
    std::cout << "  |   ()  ()   |   \n";
    std::cout << "  |            |   \n";
    std::cout << "  |  \\____/   |   \n";
    std::cout << "  \\           /   \n";
    std::cout << "   '----------'    \n";
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "Player's life: " << VidaJugador << ": ";
    for (int i = 0; i < VidaJugador/10; i++) std::cout << "-";
    std::cout << "\n";
    std::cout << "|_______Player________|";
    std::cout << "\n";
    JugadorCara();
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "Options: |  Run Away  |  Fight  |  Beg For Mercy  |\n";
    std::cout << "Press r to run away, f to fight and b to beg for mercy\n";
    
    while (true)
    {
        char tecla = _getch();
        if (tecla == 'r'){
            Correr(mapa, habitacion, fila, columna);
            return;
        } else if (tecla == 'f'){
            Fight();
            return;
        } else if (tecla == 'b'){
            Rendirse(mapa, habitacion, fila, columna);
            return;
        }


    }
}