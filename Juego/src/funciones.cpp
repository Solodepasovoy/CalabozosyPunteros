// Alejo, necesito que me hagas estas mecánicas para el sistema del mapa:
//
// 1. Sistema de inventario al presionar `i` dentro del mapa.
//    Debe abrir un menú donde se vean los objetos que tengo,
//    cuántos tengo y cuál estoy seleccionando.
//
// 2. Sistema para combinar objetos desde el inventario.
//    Cuando combine dos objetos válidos, se deben eliminar los dos
//    del inventario y crear uno nuevo.
//
// 3. Sistema de eventos random al presionar `?` en el mapa.
//    No siempre debe salir monstruo:
//    45% probabilidad objeto
//    30% probabilidad interaccion
//    25% probabilidad monstruo
//
// 4. Si sale un objeto, debe abrirse la imagen del objeto con su nombre
//    (`Nombre.png`) usando la función adecuada,
//    y ese objeto debe agregarse al inventario.
//
// 5. Si sale una interaccion, debe abrirse la imagen de la interaccion
//    y ese `?` del mapa debe convertirse en la inicial de la interaccion.
//    Luego, si el jugador vuelve a tocar esa casilla,
//    debe abrirse una pantalla para usar un objeto del inventario
//    sobre esa interaccion.
//    Si funciona, esa casilla se convierte en `.` y se entrega un nuevo objeto.
//    El objeto usado debe desaparecer del inventario.
//
// 6. Si el jugador encuentra una casilla `D`,
//    debe abrirse la imagen de la puerta y dejarme usar objetos desde el inventario.
//    En esa puerta se deben usar 4 cosas.
//
// 7. También necesito que en la puerta se pueda colocar un código.
//
// Lista de objetos:
// Ammo, Coin, KeyCard, KeyMold, Note1, Note2, HolyCross, LiquidMercury, ShotGun, Key, LoadedShotGun.
//
// Cómo se consiguen:
// - KeyMold se obtiene al usar Coin en el Well.
// - LiquidMercury se obtiene al usar HolyCross en la interaccion Seal.
// - Key se obtiene al mezclar LiquidMercury con KeyMold y usarlo en la interaccion Cooler.
// - LoadedShotGun se obtiene al combinar ShotGun con Ammo.
//
// Interacciones:
// - `C` = Cooler
// - `S` = Seal
// - `W` = Well
// - `D` = Puerta
//
// Cuando ya tenga todo para la puerta, esa casilla debe cambiarse a `.`.
//
// Te dejo también cómo está referenciado todo en el código para que lo integres sin romper la estructura actual.


#include "funciones.h"

struct CinematicasMovibles {
    std::string C2 = "../data/Cinematicas/Imagen2";
    std::string C25 = "../data/Cinematicas/Imagen25";
    std::string C3 = "../data/Cinematicas/Imagen3";
    std::string C35 = "../data/Cinematicas/Imagen35";
    std::string C4 = "../data/Cinematicas/Imagen4";
    std::string C45 = "../data/Cinematicas/Imagen45";
    std::string C5 = "../data/Cinematicas/Imagen5";
    std::string C55 = "../data/Cinematicas/Imagen55";
    std::string C6 = "../data/Cinematicas/Imagen6";
    std::string C65 = "../data/Cinematicas/Imagen65";
};

struct ImagesMonstruos{
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

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

// ─── Música / Audio (Windows) ───────────────────────────────────────────────
void reproducir(const std::string& archivo) {
    std::string ruta = archivo;
    for (char& c : ruta) if (c == '/') c = '\\';
    // SND_ASYNC hace que suene de fondo sin congelar el juego
    PlaySoundA(ruta.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
}

void parar_todos() {
    PlaySoundA(NULL, NULL, 0); // Detiene cualquier sonido reproduciéndose con PlaySound
}

#elif defined(__APPLE__)
// ─── Música / Audio (Mac) ───────────────────────────────────────────────────
void reproducir(const std::string& archivo) { 
    system(("afplay \"" + archivo + "\" >/dev/null 2>&1 &").c_str()); 
}
void parar_todos() { 
    system("killall afplay 2>/dev/null"); 
}

#else
// ─── Música / Audio (Linux) ─────────────────────────────────────────────────
void reproducir(const std::string& archivo) { 
    system(("aplay \"" + archivo + "\" >/dev/null 2>&1 &").c_str()); 
}
void parar_todos() { 
    system("killall aplay 2>/dev/null"); 
}
#endif

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
    reproducir("../data/Sonidos/CinematicasSonido.wav");

    for (int i = 0; i < 14; i += 2) {

        for (int t = 0; t < 11; t++) {

            if (_kbhit()) {
                char tecla = _getch();
                if (tecla == 'e') {
                    parar_todos();
                    LimpiarPantalla();
                    return;
                }
            }

            char cine1[100][100] = {};
            CargarCinematica(*(p + i), cine1);
            MostrarCinematica(cine1);
            std::this_thread::sleep_for(std::chrono::milliseconds(800));

            if (_kbhit()) {
                char tecla = _getch();
                if (tecla == 'e') {
                    parar_todos();
                    LimpiarPantalla();
                    return;
                }
            }

            char cine2[100][100] = {};
            CargarCinematica(*(p + i + 1), cine2);
            MostrarCinematica(cine2);
            std::this_thread::sleep_for(std::chrono::milliseconds(800));
        }
    }
    parar_todos();
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
    reproducir("../data/Sonidos/horror.wav");
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
        
        if (mapa[nuevafila][nuevacolumna] == '#'){
            continue;
        }
        
        

        //Instrucciones aqui:
        //Tienes que poner que cuando el personaje toca un ? (ya te lo puse aqui abajo) pasen 3 cosas.
        if (mapa[nuevafila][nuevacolumna] == '?'){
            mapa[nuevafila][nuevacolumna] = '.';
        LimpiarPantalla();
        reproducir("../data/Sonidos/Flash.wav");
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "***********************\n";
        std::cout << "***********************\n";
        std::cout << "***********************\n";
        std::cout << "***********************\n";
        std::cout << "***********************\n";
        std::cout << "*********flash*********\n";
        std::cout << "***********************\n";
        std::cout << "***********************\n";
        std::cout << "***********************\n";
        std::cout << "***********************\n";
        std::cout << "***********************\n";
        std::cout << "***********************\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        //agrega aca las probabilidades de monstruo, interaccion o objeto.
            Monstruo(mapa, habitacion, fila, columna);
            continue;
        }

        if (mapa[nuevafila][nuevacolumna] == 'B'){
                mapa[nuevafila][nuevacolumna] = '.';
                LimpiarPantalla();
                Boss();
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
                reproducir("../data/Sonidos/horror.wav");
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
    if (VidaJugador >= 70){
        std::cout << "\n";
    std::cout << "             ..,,;;;;;;,,,,\n";
    std::cout << "       .,;'';;,..,;;;,,,,,.''';;,..\n";
    std::cout << "    ,,''                    '';;;;,;''\n";
    std::cout << "   ;'    ,;@@;'  ,@@;, @@, ';;;@@;,;';.\n";
    std::cout << "  ''  ,;@@@@@'  ;@@@@; ''    ;;@@@@@;;;;\n";
    std::cout << "     ;;@@@@@;    '''     .,,;;;@@@@@@@;;;\n";
    std::cout << "    ;;@@@@@@;           , ';;;@@@@@@@@;;;.\n";
    std::cout << "     '';@@@@@,.  ,   .   ',;;;@@@@@@;;;;;;\n";
    std::cout << "        .   '';;;;;;;;;,;;;;@@@@@;;' ,.:;'\n";
    std::cout << "          ''..,,     ''''    '  .,;'\n";
    std::cout << "               ''''''::''''''''\n";
        std::cout << "\n";
        std::cout << "\n";
    } else if(VidaJugador >= 40 && VidaJugador < 70){
        std::cout << "\n";
    std::cout << "             ..,,;;;;;;,,,,\n";
    std::cout << "       .,;'';;,..,;;;,,,,,.''';;,..\n";
    std::cout << "    ,,'',,;;;;,,;;,,,,,;;;;;;;'';;''\n";
    std::cout << "   ;',;;;,;,,;';;,;,,,,,,,;;;;;;,;';.\n";
    std::cout << "  '';,,;,;;,,';;;;;;;;;;,,,,;;;;;;;;;;;\n";
    std::cout << "   ';;;@@@@@;    '''     .,,;;;@@@@@@@;;;\n";
    std::cout << "    ;;@@@@@@;           , ';;;@@@@@@@@;;;.\n";
    std::cout << "     '';@@@@@,.  ,   .   ',;;;@@@@@@;;;;;;\n";
    std::cout << "        .   '';;;;;;;;;,;;;;@@@@@;;' ,.:;'\n";
    std::cout << "          ''..,,     ''''    '  .,;'\n";
    std::cout << "               ''''''::''''''''\n";
        std::cout << "\n";
    } else if (VidaJugador > 0 && VidaJugador < 40){
        std::cout << "\n";
    std::cout << "             ..,,;;;;;;,,,,\n";
    std::cout << "       .,;'';;,..,;;;,,,,,.''';;,..\n";
    std::cout << "    ,,'',,;;;;,,;;,,,,,;;;;;;;'';;''\n";
    std::cout << "   ;',;;;,;,,;';;,;,;;,;;,;;;;;;,;';.\n";
    std::cout << "  '';,,;,;;,,';;;;;;;;;;,,,,;;;;;;;;;;;\n";
    std::cout << "   ';;;;,;;;;,;;;;;;;;,;,;,,;;;;;;;;;;;;;\n";
    std::cout << "    ;;,,;;;,;;;,,,;;;;;;,;';;;;;;;;;,;;;;.\n";
    std::cout << "     '';@@@@@,.  ,   .   ',;;;@@@@@@;;;;;;\n";
    std::cout << "        .   '';;;;;;;;;,;;;;@@@@@;;' ,.:;'\n";
    std::cout << "          ''..,,     ''''    '  .,;'\n";
    std::cout << "               ''''''::''''''''\n";
        std::cout << "\n";
    }
}

void MonstruoCara(){
    std::cout <<"                          ####                          \n";
    std::cout <<"                    .-@@@@@@@@@@@@@@-.                  \n";
    std::cout <<"                 .-@@@@@@@@@@@@@@@@@@@@-.               \n";
    std::cout <<"               .@@@@@@@@@@@@@@@@@@@@@@@@@@.             \n";
    std::cout <<"              @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@            \n";
    std::cout <<"             @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@           \n";
    std::cout <<"             @@@@@@@@XX@@@@@@@@@@@@@@XX@@@@@           \n";
    std::cout <<"             XX   .().      @@@@@@   () ..XX       \n";
    std::cout <<"                        .@@@@@@.                       \n";
    std::cout <<"             @@@@@@@@@  @@@@@@@@  @@@@@@@@@            \n";
    std::cout <<"              @@@@@@@@   @@@@@@   @@@@@@@@             \n";
    std::cout <<"               @@@@@@     @@@@     @@@@@@              \n";
    std::cout <<"               .@@@@        ##        @@@@             \n";
    std::cout <<"                 XX##              ##XX                \n";
    std::cout <<"                       ########                      \n";
    std::cout <<"                     __    ##                         \n";
    std::cout <<"                       \\____                         \n";
    std::cout <<"\n";
    std::cout <<"                        ...                           \n";
    std::cout <<"                         /|\\                          \n";
    std::cout <<"                        /###\\                         \n";
    std::cout <<"                      @@@ /#\\ @@@                     \n";
}

void CorrerASCI(int num){
    LimpiarPantalla();
    std::cout << "          .                                                      .\n";
    std::cout << "        .n                   .                 .                  n.\n";
    std::cout << "  .   .dP                  dP                   9b                 9b.    .\n";
    std::cout << " 4    qXb         .       dX                     Xb       .        dXp     t\n";
    std::cout << "dX.    9Xb      .dXb    __                         __    dXb.     dXP     .Xb\n";
    std::cout << "9XXb._       _.dXXXXb dXXXXbo.                 .odXXXXb dXXXXb._       _.dXXP\n";
    std::cout << " 9XXXXXXXXXXXXXXXXXXXVXXXXXXXXOo.           .oOXXXXXXXXVXXXXXXXXXXXXXXXXXXXP\n";
    std::cout << "  `9XXXXXXXXXXXXXXXXXXXXX'~   ~`OOO8b   d8OOO'~   ~`XXXXXXXXXXXXXXXXXXXXXP'\n";
    std::cout << "    `9XXXXXXXXXXXP' `9XX' (      ) `98v8P' (      ) `XXP' `9XXXXXXXXXXXP'\n";
    std::cout << "        ~~~~~~~       9X.          .db|db.          .XP       ~~~~~~~\n";
    std::cout << "                        )b.  .dbo.dP'`v'`9b.odb.  .dX(\n";
    std::cout << "                      ,dXXXXXXXXXXXb     dXXXXXXXXXXXb.\n";
    std::cout << "                     dXXXXXXXXXXXP'   .   `9XXXXXXXXXXXb\n";
    std::cout << "                    dXXXXXXXXXXXXb   d|b   dXXXXXXXXXXXXb\n";
    std::cout << "                    9XXb'   `XXXXXb.dX|Xb.dXXXXX'   `dXXP\n";
    std::cout << "                     `'      9XXXXXX(   )XXXXXXP      `'\n";
    std::cout << "                              XXXX X.`v'.X XXXX\n";
    std::cout << "                              XP^X'`b   d'`X^XX\n";
    std::cout << "                              X. 9  `   '  P )X\n";
    std::cout << "                              `b  `       '  d'\n";
    std::cout << "                               `             '\n";
    std::cout << "\n";
    std:: cout << "\n";
    std::cout << "                               `             '\n";
    std::cout << "                              `b  `       '  d'\n";
    std::cout << "                              X. 9  `   '  P )X\n";
    std::cout << "                              XP^X'`b   d'`X^XX\n";
    std::cout << "\n";
    std::cout << "         !!!!!!!!!!!!!!!!!PRESIONA EL NUMERO " << num << "\n";
    }

void Correr(char mapa[12][23], int& habitacion, int& fila, int& columna) {
    std::cout << "Instrucciones:\n";
    std::cout << "\n";
    std::cout << "Va a aparecer el fantasma en pantalla y te va a aparecer el numero que debes presionar para correr,\n";
    std::cout << "\n";
    std::cout << "Tienes entre 1 a 2.5 segundos para presionar este numero,\n";
    std::cout << "\n";
    std::cout << "Si no presionas este numero a tiempo, te quitaran 25 puntos de vida y te tocara pelear con el fantasma,\n";
    std::cout << "\n";
    std::cout << "Si logras poner todas las letras que salgan por 10 segundos, vas a escapar o te tocara pelear\n";
    std::cout << "\n";
    std::cout << "Presiona la tecla 'a' para empezar\n";
    char tecla;
    do { tecla = _getch(); } while (tecla != 'a');
    reproducir("../data/Sonidos/correr.wav");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    int tiempoTotal = 0;
    int vidaM = rand() % 31 + 10;

    while (tiempoTotal < 10000) {
        int n = rand() % 10;
        int numero = rand() % (1300 - 1000 + 1) + 1000;

        CorrerASCI(n);
        std::this_thread::sleep_for(std::chrono::milliseconds(numero));

        if (!_kbhit() || _getch() != (n + '0')) {
            LimpiarPantalla();
            VidaJugador -= 25;
            Ataque();
            std::this_thread::sleep_for(std::chrono::milliseconds(1600));
            Fight(mapa, habitacion, fila, columna, vidaM, 10);
            return;
        }
        tiempoTotal += numero;
    }

    int r = rand() % 100;
    if (r < 50) Fight(mapa, habitacion, fila, columna, vidaM, 10);
    else        Flee(mapa, habitacion, fila, columna);
}

void PelearImagenenA(){
    LimpiarPantalla();
    std::cout << "88888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n";
    std::cout << "88.._|      | `-.  | `.  -_-_ _-_  _-  _- -_ --_-_ _-_  _-  _  .'|   |.'|     |  _..88\n";
    std::cout << "88   `-.._  |    |`!  |`.  -_ -__ -_ _- _-_--_ -__ -_ _- _-  .'  |.;'   |   _.!-'|  88\n";
    std::cout << "88      | `-!._  |  `;!  ;. ______________________________ ,'| .-' |   _!.i'     |  88\n";
    std::cout << "88..__  |     |`-!._ | `.| |                              ||. '|  _!.;'   |     _|..88\n";
    std::cout << "88   |`` ..__ |    |` ;.| i|                              |'| _!-|   |   _|..-|'    88\n";
    std::cout << "88   |      |``--..|_ | `;!|                              |.'j   |_..!-'|     |     88\n";
    std::cout << "88   |      |    |   |`-,!_|                              ||.!-;'  |    |     |     88\n";
    std::cout << "88___|______|____!.,.!,.!,!|                              |,!,.!.,.!..__|_____|_____88\n";
    std::cout << "88      |     |    |  |  | |                              || |   |   |    |      |  88\n";
    std::cout << "88      |     |    |..!-;'i|                              | |`-..|   |    |      |  88\n";
    std::cout << "88      |    _!.-j'  | _!, |                              ||!._|  `i-!.._ |      |  88\n";
    std::cout << "88     _!.-'|    | _. |  !;|                              |`.| `-._|    |``-.._  |  88\n";
    std::cout << "88..-i'     |  _.''|  !-| !|                              |.|`-. | ``._ |     |`` ..88\n";
    std::cout << "88   |      |.|    |.|  !| |                              ||`. |`!   | ` .    |     88\n";
    std::cout << "88   |  _.-'  |  .'  |.' |/|                              |! |`!  `,.|    |-._|     88\n";
    std::cout << "88  _! '|     !.'|  .'| .'||                              | \\|  `. | `._  |  `-._  88\n";
    std::cout << "88-'    |   .'   |.|  |/| /                                \\|`.  |`!    |.|     |`-88\n";
    std::cout << "88      |_.'|   .' | .' |/                                  \\  \\ |  `.   | `._ |  88\n";
    std::cout << "88     .'   | .'   |/|  /                                    \\ `! |   |`. | `.  |  88\n";
    std::cout << "88  _.'     !'|   .' | /                                      \\  `|   |  `|   `.|  88\n";
    std::cout << "88888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n";
}


void PelearImagenenB(){
    LimpiarPantalla();
    std::cout << "88888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n";
    std::cout << "88.._|      | `-.  | `.  -_-_ _-_  _-  _- -_ --_-_ _-_  _-  _  .'|   |.'|     |  _..88\n";
    std::cout << "88   `-.._  |    |`!  |`.  -_ -__ -_ _- _-_--_ -__ -_ _- _-  .'  |.;'   |   _.!-'|  88\n";
    std::cout << "88      | `-!._  |  `;!  ;. ______________________________ ,'| .-' |   _!.i'     |  88\n";
    std::cout << "88..__  |     |`-!._ | `.| |                              ||. '|  _!.;'   |     _|..88\n";
    std::cout << "88   |`` ..__ |    |` ;.| i|                              |'| _!-|   |   _|..-|'    88\n";
    std::cout << "88   |      |``--..|_ | `;!|        ,--.     ,--.         |.'j   |_..!-'|     |     88\n";
    std::cout << "88   |      |    |   |`-,!_|       (    )   (    )        ||.!-;'  |    |     |     88\n";
    std::cout << "88___|______|____!.,.!,.!,!|        `--'     `--'         |,!,.!.,.!..__|_____|_____88\n";
    std::cout << "88      |     |    |  |  | |                              || |   |   |    |      |  88\n";
    std::cout << "88      |     |    |..!-;'i|                              | |`-..|   |    |      |  88\n";
    std::cout << "88      |    _!.-j'  | _!, |           `-.__.'            ||!._|  `i-!.._ |      |  88\n";
    std::cout << "88     _!.-'|    | _. |  !;|                              |`.| `-._|    |``-.._  |  88\n";
    std::cout << "88..-i'     |  _.''|  !-| !|                              |.|`-. | ``._ |     |`` ..88\n";
    std::cout << "88   |      |.|    |.|  !| |                              ||`. |`!   | ` .    |     88\n";
    std::cout << "88   |  _.-'  |  .'  |.' |/|                              |! |`!  `,.|    |-._|     88\n";
    std::cout << "88  _! '|     !.'|  .'| .'||                              | \\|  `. | `._  |  `-._  88\n";
    std::cout << "88-'    |   .'   |.|  |/| /                                \\|`.  |`!    |.|     |`-88\n";
    std::cout << "88      |_.'|   .' | .' |/                                  \\  \\ |  `.   | `._ |  88\n";
    std::cout << "88     .'   | .'   |/|  /                                    \\ `! |   |`. | `.  |  88\n";
    std::cout << "88  _.'     !'|   .' | /                                      \\  `|   |  `|   `.|  88\n";
    std::cout << "88888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n";
}

void PelearImagenC(){
    LimpiarPantalla();
    std::cout << "888888888888888888888888888888888888888888888888888888888888888888888888888888888\n";
    std::cout << "88              @@@@@@@@@@@v.   \"-.'0 @@@m1vc<  't@@@@@@@@@@@@@@              88\n";
    std::cout << "88              @@@@@@@@@@Bx.   Y#wYq @@@bQ@@@>  ;L@@@@@@@@@@@@@@              88\n";
    std::cout << "88              @@@@@@@@@@0^  () ,!Z @@@M|  <'() )#@@@@@@@@@@@@@@              88\n";
    std::cout << "88              @@@@@@@@@@C.      'vB @@@@&).>hk` `Q@@@@@@@@@@@@@              88\n";
    std::cout << "88              @@@@@@@@@#1   p%@@@@W~&@@@     Bz  C@@@@@@@@@@@@@              88\n";
    std::cout << "88              @@@@@@@@@&j   '%@@@q>\"&& @@@@@@#^  UB@@@@@@@@@@@              88\n";
    std::cout << "88              @@@@@@@@@Bz      ,uY]a@@@@@@@@@i   UB@@@@@@@@@@@@              88\n";
    std::cout << "88              @@@@@@@@@@L'       jMi lp@@@@@8    C@@@@@@@@@@@@@              88\n";
    std::cout << "88              @@@@@@@@@@d<            !#@@@@<   <d@@@@@@@@@@@@@              88\n";
    std::cout << "88              @@@@@@@@@@@v'    ..     la@@@u    n@@@@@@@@@@@@@@              88\n";
    std::cout << "88              @@@@@@@@@@@0l     '     la@@@l   :L@@@@@@@@@@@@@@              88\n";
    std::cout << "88              @@@@@@@@@@@@|     .     i&@@).   (@@@@@@@@@@@@@@@              88\n";
    std::cout << "88              @@@@@@@@@@@@Q;    |B{   _@@M+   >a@@@@@@@@@@@@@@@              88\n";
    std::cout << "88              @@@@@@@@@@@@@_     v/i ^&@B|    _@@@@@@@@@@@@@@@@              88\n";
    std::cout << "88              @@@@@@@@@@@@@Q^    'QBB  W/    `z@@@@@@@@@@@@@@@@              88\n";
    std::cout << "88              @@@@@@@@@@@@@W:                ;@@@@@@@@@@@@@@@@@              88\n";
    std::cout << "88              @@@@@@@@@@@@@@-                f@@@@@@@@@@@@@@@@@              88\n";
    std::cout << "88              @@@@@@@@@@@@@@q               .B@@@@@@@@@@@@@@@@@              88\n";
    std::cout << "88              @@@@@@@@@@@@@@B               |@@@@@@@@@@@@@@@@@@              88\n";
    std::cout << "888888888888888888888888888888888888888888888888888888888888888888888888888888888\n";
}

void Susto(){
    LimpiarPantalla();
    std::cout << "                          ...----....\n";
    std::cout << "                    ..-:\"''         ''\"-..'\n";
    std::cout << "                 .-'                      '-.\n";
    std::cout << "               .'              .     .       '.\n";
    std::cout << "             .'   .          .    .      .    .''.\n";
    std::cout << "           .'  .    .       .   .   .     .   . ..:\n";
    std::cout << "         .' .   . .  .       .   .   ..  .   . ....::\n";
    std::cout << "        ..   .   .      .  .    .     .  ..  . ....:IA.\n";
    std::cout << "       .:  .   .    .    .  .  .    .. .  .. .. ....:IA.\n";
    std::cout << "      .: .   .   ..   .    .     . . .. . ... ....:.:VHA.\n";
    std::cout << "      '..  .  .. .   .       .  . .. . .. . .....:.::IHHB.\n";
    std::cout << "     .:. .  . .  . .   .  .  . . . ...:.:... .......:HIHMM.\n";
    std::cout << "    .:.... .   . .\".:.\"'.. .   .  . .:.:.:II;,. .. ..:IHIMMA\n";
    std::cout << "    ':.:..  ..::IHHHHHI::. . .  ...:.::::.,,,. . ....VIMMHM\n";
    std::cout << "   .:::I. .AHHHHHHHHHHAI::. .:...,:IIHHHHHHMMMHHL:. . VMMMM\n";
    std::cout << "  .:.:V.:IVHHHHHHHMHMHHH::..\":\" .:HIHHHHHHHHHHHHHMHHA. .VMMM.\n";
    std::cout << "  :..V.:IVHHHHHMMHHHHHHHB... . .:VPHHMHHHMMHHHHHHHHHAI.:VMMI\n";
    std::cout << "  ::V..:VIHHHHHHMMMHHHHHH. .   .I\":IIMHHMMHHHHHHHHHHHAPI:WMM\n";
    std::cout << "  ::\". .:.HHHHHHHHMMHHHHHI.  . .:..I:MHMMHHHHHHHHHMHV:':H:WM\n";
    std::cout << "  :: . :.::IIHHHHHHMMHHHHV  .ABA.:.:IMHMHMMMHMHHHHV:'. .IHWW\n";
    std::cout << "  '.  ..:..:.:IHHHHHMMHV\" .AVMHMA.:.'VHMMMMHHHHHV:' .  :IHWV\n";
    std::cout << "   :.  .:...\":\".:.:TPP\"   .AVMMHMMA.:. \"VMMHHHP.:... .. :IVAI\n";
    std::cout << "  .:.   '... .:\"\".   .   ..HMMMHMMMA::. .\"VHHI:::....  .:IHW'\n";
    std::cout << "  ...  .  . ..:IIPPIH: ..HMMMI.MMMV:I:.  .:ILLH:.. ...:I:IM\n";
    std::cout << ": .   .'\"' .:.V\". .. .  :HMMM:IMMMI::I. ..:HHIIPPHI::'.P:HM.\n";
    std::cout << ":.  .  .  .. ..:.. .    :AMMM IMMMM..:...:IV\":T::I::\".:IHIMA\n";
    std::cout << "'V:.. .. . .. .  .  .   'VMMV..VMMV :....:V:.:..:....::IHHHMH\n";
    std::cout << "  \"IHH:.II:.. .:. .  . . . \" :HB\"\" . . ..PI:.::.:::..:IHHMMV\"\n";
    std::cout << "   :IP\"\"HHII:.  .  .    . . .'V:. . . ..:IH:.:.::IHIHHMMMMM\"\n";
    std::cout << "   :V:. VIMA:I..  .     .  . .. . .  .:.I:I:..:IHHHHMMHHMMM\n";
    std::cout << "   :\"VI:.VWMA::. .:      .   .. .:. ..:.I::.:IVHHHMMMHMMMMI\n";
    std::cout << "   :.\"VIIHHMMA:.  .   .   .:  .:.. . .:.II:I:AMMMMMMHMMMMMI\n";
    std::cout << "   :..VIHIHMMMI...::.,:.,:!\"I:!\"I!\"I!\"V:AI:VAMMMMMMHMMMMMM'\n";
    std::cout << "   ':.:HIHIMHHA:\"!!\"I.:AXXXVVXXXXXXXA:.\"HPHIMMMMHHMHMMMMMV\n";
    std::cout << "     V:H:I:MA:W'I :AXXXIXII:IIIISSSSSSXXA.I.VMMMHMHMMMMMM\n";
    std::cout << "       'I::IVA ASSSSXSSSSBBSBMBSSSSSSBBMMMBS.VVMMHIMM'\"\n";
    std::cout << "        I:: VPAIMSSSSSSSSSBSSSMMBSSSBBMMMMXXI:MMHIMMI\n";
    std::cout << "       .I::. \"H:XIIXBBMMMMMMMMMMMMMMMMMBXIXXMMPHIIMM'\n";
    std::cout << "       :::I.  ':XSSXXIIIIXSSBMBSSXXXIIIXXSMMAMI:.IMM\n";
    std::cout << "       :::I:.  .VSSSSSISISISSSBII:ISSSSBMMB:MI:..:MM\n";
    std::cout << "       ::.I:.  ':\".SSSSSSSISISSXIIXSSSSBMMB:AHI:..MMM.\n";
    std::cout << "       ::.I:. . ..:\"BBSSSSSSSSSSSSBBBMMMB:AHHI::.HMMI\n";
    std::cout << "       :..::.  . ..::\":BBBBBSSBBBMMMB:MMMMHHII::IHHMI\n";
    std::cout << "       ':.I:... ....:IHHHHHMMMMMMMMMMMMMMMHHIIIIHMMV\"\n";
    std::cout << "         \"V:. ..:...:.IHHHMMMMMMMMMMMMMMMMHHHMHHMHP'\n";
    std::cout << "          ':. .:::.:.::III::IHHHHMMMMMHMHMMHHHHM\"\n";
    std::cout << "            \"::....::.:::..:..::IIIIIHHHHMMMHHMV\"\n";
    std::cout << "              \"::.::.. .. .  ...:::IIHHMMMMHMV\"\n";
    std::cout << "                \"V::... . .I::IHHMMV\"'\n";
    std::cout << "                  '\"VHVHHHAHHHHMMV:\"\n";
}

void Ataque(){ 
    reproducir("../data/Sonidos/PlayerDamage.wav");
    LimpiarPantalla();
    std::cout << "88888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n";
    std::cout << "88888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n";
    std::cout << "88888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n";
    std::cout << "88888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n";
    std::cout << "88888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n";
    std::cout << "88888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n";
    std::cout << "88888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n";
    std::cout << "88888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n";
    std::cout << "88888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n";
    std::cout << "88888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n";
    std::cout << "88888888888888888888Vida Restante:"<<VidaJugador<<" 888888888888888888888888888888888888888888888888\n";
    std::cout << "88888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n";
    std::cout << "88888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n";
    std::cout << "88888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n";
    std::cout << "88888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n";
    std::cout << "88888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n";
    std::cout << "88888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n";
    std::cout << "88888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n";
    std::cout << "88888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n";
    std::cout << "88888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n";
    std::cout << "88888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n";
    std::cout << "88888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n";
}

void SinVer(int vidaJugador, int vidaenemigo, int flashes){
    LimpiarPantalla();
    std::cout << "88888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n";
    std::cout << "88                                                                                  88\n";
    std::cout << "88                                                                                  88\n";
    std::cout << "88                                                                                  88\n";
    std::cout << "88                                                                                  88\n";
    std::cout << "88                                                                                  88\n";
    std::cout << "88                                                                                  88\n";
    std::cout << "88                                                                                  88\n";
    std::cout << "88                                                                                  88\n";
    std::cout << "88                                                                                  88\n";
    std::cout << "88                                                                                  88\n";
    std::cout << "88                                                                                  88\n";
    std::cout << "88                                                                                  88\n";
    std::cout << "88                                                                                  88\n";
    std::cout << "88                                                                                  88\n";
    std::cout << "88                                                                                  88\n";
    std::cout << "88                  N# de Flashes: "<< flashes << "                                              88\n";
    std::cout << "88                                                                                  88\n";
    std::cout << "88                  Vida del jugador: "<< vidaJugador << "                                        88\n";
    std::cout << "88                                                                                  88\n";
    std::cout << "88                  Vida del enemigo: "<< vidaenemigo << "                                        88\n";
    std::cout << "88                                                                                  88\n";
    std::cout << "88888888888888888888888888888888888888888888888888888888888888888888888888888888888888\n";
}

void Fight(char mapa[12][23], int& habitacion, int& fila, int& columna, int& vidaenemigo, int maximosflashes) {
    LimpiarPantalla();
    std::cout << "VAS A PELEAR CONTRA EL FANTASMA!\n";
    std::cout << "\n";
    std::cout << "INSTRUCCIONES:\n";
    std::cout << "\n";
    std::cout << "Presiona 'f' para usar el flash de la camara y ver en la oscuridad.\n";
    std::cout << "\n";
    std::cout << "El fantasma tiene tres estados, pasivo, activo y agresivo. \n";
    std::cout << "\n";
    std::cout << "Si alumbras y ves un pasillo vacio, el fantasma esta en estado pasivo, si ves una cara a lo lejos esta en estado activo\n";
    std::cout << "\n";
    std::cout << "Si ves ya la cara del fantasma completamente, debes presionar 'g' apenas alumbres para ahuyentarlo, tienes muy poco tiempo\n";
    std::cout << "\n";
    std::cout << "Si no lo haces a tiempo el fantasma te atacará, si presionas 'g' cuando no debes, tambien te atacara\n";
    std::cout << "\n";
    std::cout << "Solo puedes alumbrar 10 veces maximo, si lo haces mas te quedaras sin flashes, el fantasma te quitara 35 de vida y se ira\n";
    std::cout << "\n";
    std::cout << "Presiona 'a' para comenzar, suerte...\n";

    int flashes = 0;
    char tecla;
    do { tecla = _getch(); } while (tecla != 'a');

    std::atomic<int>  estado(1);
    std::atomic<bool> enCombate(true);
    std::atomic<bool> ataqueAutomatico(false);
    std::thread estadoThread([&]() {
        while (enCombate.load()) {
            int tp  = (rand() % 9  + 7)  * 1000;
            int ta  = (rand() % 5  + 4)  * 1000;
            int tag = (rand() % 3  + 4)  * 1000;

            estado.store(1);
            for (int i = 0; i < tp / 50 && enCombate.load(); i++)
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            if (!enCombate.load()) break;

            estado.store(2);
            for (int i = 0; i < ta / 50 && enCombate.load(); i++)
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            if (!enCombate.load()) break;

            estado.store(3);
            for (int i = 0; i < tag / 50 && enCombate.load(); i++)
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            if (!enCombate.load()) break;

            if (estado.load() == 3) {
                ataqueAutomatico.store(true);
            }
        }
    });

    SinVer(VidaJugador, vidaenemigo, flashes);

    while (enCombate.load()) {
    if (ataqueAutomatico.load()) {
            ataqueAutomatico.store(false);
            Ataque();
            VidaJugador -= 10;
            std::this_thread::sleep_for(std::chrono::milliseconds(800));
            if (VidaJugador <= 0) {
                enCombate.store(false);
                estadoThread.join();
                Morir();
                return;
            }
            SinVer(VidaJugador, vidaenemigo, flashes);
        }

        if (!_kbhit()) { std::this_thread::sleep_for(std::chrono::milliseconds(10)); continue; }

        char t = _getch();

        if (flashes > maximosflashes){
            enCombate.store(false);
            estadoThread.join();

            VidaJugador -= 35;

            if (VidaJugador <= 0){
                Morir();
                return;
            }

            LimpiarPantalla();
            std::cout << "Usaste demasiado el flash... el fantasma te ataco y desaparecio.\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));

            Suerte(mapa, habitacion, fila, columna);
            return;
        }

        if (t == 'f') {
            reproducir("../data/Sonidos/Flash.wav");
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            flashes++;
            int estadoActual = estado.load();

            if      (estadoActual == 1) PelearImagenenA();
            else if (estadoActual == 2) PelearImagenenB();
            else if (estadoActual == 3) PelearImagenC();
            else                        SinVer(VidaJugador, vidaenemigo, flashes);

            bool gPresionado = false;
            auto inicio = std::chrono::steady_clock::now();
            while (std::chrono::steady_clock::now() - inicio < std::chrono::seconds(1)) {
                if (_kbhit()) { char t2 = _getch(); if (t2 == 'g') { gPresionado = true; break; } }
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }

            if (gPresionado) {
                if (estadoActual == 1 || estadoActual == 2) {
                    Ataque();
                    VidaJugador -= 10;
                    std::this_thread::sleep_for(std::chrono::milliseconds(800));
                    estado.store(1);
                    if (VidaJugador <= 0) {
                        enCombate.store(false);
                        estadoThread.join();
                        Morir();
                        return;
                    }
                } else if (estadoActual == 3) {
                    reproducir("../data/Sonidos/MonsterDamage.wav");
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    Susto();
                    vidaenemigo -= 10;
                    std::this_thread::sleep_for(std::chrono::milliseconds(600));
                    estado.store(1);
                    if (vidaenemigo <= 0) {
                        enCombate.store(false);
                        estadoThread.join();
                        LimpiarPantalla();
                        std::cout << "Derrotaste al fantasma!\n";
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                        Suerte(mapa, habitacion, fila, columna);
                        return;
                    }
                }
            }
            SinVer(VidaJugador, vidaenemigo, flashes);
        }
    }
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
    parar_todos();
    reproducir("../data/Sonidos/muerte.wav");
    LimpiarPantalla();
    std::cout << "GAME OVER; Haz Muerto\n";
    std::cout << "\n";
    std::cout << "                      :::!~!!!!!:.\n";
    std::cout << "                  .xUHWH!! !!?M88WHX:.\n";
    std::cout << "                .X*#M@$!!  !X!M$$$$$$WWx:.\n";
    std::cout << "               :!!!!!!?H! :!$!$$$$$$$$$$8X:\n";
    std::cout << "              !!~  ~:~!! :~!$!#$$$$$$$$$$8X:\n";
    std::cout << "             :!~::!H!<   ~.U$X!?R$$$$$$$$MM!\n";
    std::cout << "             ~!~!!!!~~ .:XW$$$U!!?$$$$$$RMM!\n";
    std::cout << "               !:~~~ .:!M\"T#$$$$WX??#MRRMMM!\n";
    std::cout << "               ~?WuxiW*`   `\"#$$$$8!!!!!!!!!\n";
    std::cout << "             :X- M$$$$       `\"T#$T~!8$WUXU~\n";
    std::cout << "            :%`  ~#$$$m:        ~!~ ?$$$$$$\n";
    std::cout << "          :!`.-   ~T$$$$8xx.  .xWW- ~\"\"##*\"\n";
    std::cout << ".....   -~~:<` !    ~?T#$$@@W@*?$$      /`\n";
    std::cout << "W$@@M!!! .!~~ !!     .:XUW$W!~ `\"~:    :\n";
    std::cout << "#\"~~`.:x%`!!  !H:   !WM$$$$Ti.: .!WUn+!`\n";
    std::cout << ":::~:!!`:X~ .: ?H.!u \"$$$B$$$!W:U!T$$M~\n";
    std::cout << ".~~   :X@!.-~   ?@WTWo(\"*$$$W$TH$! `\n";
    std::cout << "Wi.~!X$?!-~    : ?$$$B$Wu(\"**$RM!\n";
    std::cout << "$R@i.~~ !     :   ~$$$$$B$$en:``\n";
    std::cout << "?MXT@Wx.~    :     ~\"##*$$$$M~\n";
    VidaJugador = 100;
    ResetearCuartos();
    exit(0);
}

void Suerte(char mapa[12][23], int& habitacion, int& fila, int& columna) {
    std::string archivoActual =
        "../data/Cuartos/Cuarto" + std::to_string(habitacion) + ".txt";

    LimpiarPantalla();
    parar_todos();
    reproducir("../data/Sonidos/horror.wav");
    std::cout << "El fantasma ya no esta...\n";
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

    habitacion = conexiones[indice].habitacionDestino;
    fila       = 1;
    columna    = 1;

    LimpiarPantalla();
    parar_todos();
    reproducir("../data/Sonidos/horror.wav");
    std::cout << "You managed to flee!\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    LimpiarPantalla();
    mostrarMapa(mapa);
}

void Monstruo(char mapa[12][23], int &habitacion, int& fila, int& columna){
    if (VidaJugador <= 0){
        Morir();
        return;
    }
    ImagesMonstruos img;
    std::string lista[] = {img.a, img.b, img.c, img.d, img.e, img.f};
    std::string imagen = lista[rand() % 6];

    std::string archivoActual = "../data/Cuartos/Cuarto" + std::to_string(habitacion) + ".txt";
    guardarMapa(archivoActual, mapa);
    LimpiarPantalla();
    AbrirImagen(imagen);
    std::cout << "You have found a Ghost!\n";
    reproducir("../data/Sonidos/MonstruoOst.wav");
    std::this_thread::sleep_for(std::chrono::seconds(2));
    LimpiarPantalla();
    int vidaM = rand() % 31 + 10;
    std::cout << "Vida del fantasma: " << vidaM << "\n";
    std::cout << "\n";
    std::cout << "                |_______Entidad________|\n";
    std::cout << "\n";
    MonstruoCara();
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "Player's life: " << VidaJugador << "\n";
    std::cout << "\n";
    std::cout << "              |_______Jugador________|\n";
    std::cout << "\n";
    JugadorCara();
    std::cout << "\n";
    std::cout << "\n";
    std::cout << "Opciones: |  Correr  |  Pelear  |  Pedir Misericorida  |\n";
    std::cout << "Presiona r para correr, f para pelear y b para pedir misericordia\n";
    
    while (true)
    {
        char tecla = _getch();
        if (tecla == 'r'){
            Correr(mapa, habitacion, fila, columna);
            return;
        } else if (tecla == 'f'){
            Fight(mapa, habitacion, fila, columna, vidaM, 10);
            return;
        } else if (tecla == 'b'){
            Rendirse(mapa, habitacion, fila, columna);
            return;
        }


    }
}

int faseActual = 1;

void ControlSonidoPorFase(int fase) {
    if (fase == 2 || fase == 3) {
        parar_todos();
    }
}

void Boss(){
    std::cout << "Es una sorpresa que hayas llegado hasta aqui humano, pero hasta aqui llegas\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "Yo fui el que desaparecio a todos los fantasmas con los que te has encontrado en este hotel\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "Hubiera sido feliz, sino fuera porque esos espiritus en vez de ascender, buscaron venganza\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "Ahora estoy atrapado con ellos y la unica forma de salir de aqui es usando tu cuerpo\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "Porfavor..DEJAME USARTE!!!!!!!!\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << ".";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << ".";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << ".";
    std::this_thread::sleep_for(std::chrono::seconds(3));
    reproducir("../data/Sonidos/correr.wav");
    AbrirImagen("boss.png");
    LimpiarPantalla();
    
    std::cout << "INSTRUCCIONES FINALES\n";
    std::cout << "\n";

    std::cout << "El jefe tiene 3 fases.\n";
    std::cout << "Cada vez que te golpee, cambiara de fase.\n";
    std::cout << "Sobrevive lo suficiente... y comenzara la batalla final.\n";
    std::cout << "\n";

    std::cout << "FASE 1 - NO DEJES DE MOVERTE\n";
    std::cout << "Si escuchas musica, corre presionando C.\n";
    std::cout << "Cuando la musica se detenga, presiona P para quedarte quieto.\n";
    std::cout << "\n";
    std::cout << "Si te mueves cuando debes parar... o te detienes cuando debes correr...\n";
    std::cout << "perderas vida.\n";
    std::cout << "\n";

    std::cout << "FASE 2 - REPITE EXACTAMENTE\n";
    std::cout << "El jefe mostrara palabras en pantalla.\n";
    std::cout << "Debes escribirlas exactamente igual y presionar ENTER.\n";
    std::cout << "\n";
    std::cout << "Mayusculas, simbolos y letras deben ser identicos.\n";
    std::cout << "Un error te costara vida.\n";
    std::cout << "\n";

    std::cout << "FASE 3 - SIGUE EL LATIDO\n";
    std::cout << "Veras un corazon en pantalla.\n";
    std::cout << "Cada vez que lata, debes presionar L antes de que deje de latir.\n";
    std::cout << "\n";
    std::cout << "Si fallas el ritmo... perderas vida.\n";
    std::cout << "\n";

    std::cout << "Final -\n";
    std::cout << "Sobrevive por 7 minutos, el jefe se cansara, luego usa tu escopeta para rematarlo\n";
    std::cout << "\n";
    std::cout << "Derrotalo... libera a las almas... y escapa.\n";
    std::cout << "\n";
    std::cout << "No falles. Esta es tu ultima oportunidad.\n";
    std::cout << "Presiona 'a' cuando estes listo.\n";

    char tecla;
    do { tecla = _getch(); } while (tecla != 'a');

    LimpiarPantalla();

    ElegirFase();

}

void ElegirFase() {

    int tiempoTotal = 8 * 60;
    auto inicio = std::chrono::steady_clock::now();

    while (true) {
        auto ahora = std::chrono::steady_clock::now();
        int segundosPasados = std::chrono::duration_cast<std::chrono::seconds>(ahora - inicio).count();

        if (segundosPasados >= tiempoTotal) {
            FinalBueno();
            return;
        }

        int nuevaFase = rand() % 3 + 1; 
        bool faseSobrevivida = false;

        switch (nuevaFase) {
            case 1: faseSobrevivida = Fase1(); break;
            case 2: faseSobrevivida = Fase2(); break;
            case 3: faseSobrevivida = Fase3(); break;
        }

        if (!faseSobrevivida) {
            std::cout << "\n¡El jefe cambio de fase por el golpe!\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            LimpiarPantalla();
        }
    }
}

bool Fase1() {
    LimpiarPantalla();
    std::cout << "Cuidado con la musica :)\n";

    int tiempoTotal = rand() % (40 - 30 + 1) + 30;
    auto inicio = std::chrono::steady_clock::now();

    while (true){
        auto ahora = std::chrono::steady_clock::now();
        auto segundosPasados = std::chrono::duration_cast<std::chrono::seconds>(ahora - inicio).count();

        if (segundosPasados >= tiempoTotal) {
            std::cout << "Fase terminada\n";
            return true;
        }

        reproducir("../data/Sonidos/Dance.wav");

        bool presionoC = false;
        auto tiempoC = std::chrono::steady_clock::now();

        while (true) {

            auto actual = std::chrono::steady_clock::now();
            double tiempoPasado = std::chrono::duration<double>(actual - tiempoC).count();

            if (_kbhit()) {
                char tecla = _getch();

                if (tecla == 'c' || tecla == 'C') {
                    presionoC = true;
                    break;
                }
            }

            if (tiempoPasado >= 4.0) {
                break;
            }
        }

        if (!presionoC) {
            parar_todos();
            QuitarVidaBoss();
            return false;
        }
        int espera1 = rand() % (15 - 8 + 1) + 8;
        std::this_thread::sleep_for(std::chrono::seconds(espera1));

        parar_todos();

        bool presionoP = false;
        auto tiempoP = std::chrono::steady_clock::now();

        while (true) {

            auto actual = std::chrono::steady_clock::now();
            double tiempoPasado = std::chrono::duration<double>(actual - tiempoP).count();

            if (_kbhit()) {
                char tecla = _getch();

                if (tecla == 'p' || tecla == 'P') {
                    presionoP = true;
                    break;
                }
            }

            if (tiempoPasado >= 0.5) {
                break;
            }
        }

        if (!presionoP) {
            parar_todos();
            QuitarVidaBoss();
            return false;
        }

        int espera2 = rand() % (10 - 5 + 1) + 5;
        std::this_thread::sleep_for(std::chrono::seconds(espera2));
    }
}

bool Fase2() {
    faseActual = 2;
    ControlSonidoPorFase(faseActual);
    std::cout << "Escribe igual que yo!\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::string palabras[] = {
        "S1N",
        "H3ll",
        "JuDg3M3nT",
        "S4cr1f1cE",
        "D4mN3d",
        "3T3rn4L"
    };

    int tiempoTotal = rand() % (30 - 20 + 1) + 20;

    auto inicioFase = std::chrono::steady_clock::now();

    while (true) {

        auto ahora = std::chrono::steady_clock::now();

        int segundosPasados = std::chrono::duration_cast<std::chrono::seconds>(
            ahora - inicioFase
        ).count();

        if (segundosPasados >= tiempoTotal) {
            std::cout << "Sobreviviste la fase.\n";
            return true;
        }

        LimpiarPantalla();

        std::string palabraActual = palabras[rand() % 6];
        std::cout << palabraActual << "\n";

        int tiempoRespuesta = rand() % (10 - 6 + 1) + 6;

        auto inicioRespuesta = std::chrono::steady_clock::now();

        std::string input = "";
        bool tiempoAgotado = false;

        while (true) {
            auto ahoraResp = std::chrono::steady_clock::now();
            int tiempoPasado = std::chrono::duration_cast<std::chrono::seconds>(
                ahoraResp - inicioRespuesta).count();

            if (tiempoPasado >= tiempoRespuesta) {
                tiempoAgotado = true;
                break;
            }

            if (_kbhit()) {
                char tecla = _getch();
                if (tecla != '\r') {
                    input += tecla;
                    std::cout << tecla;
                }
                if (input == palabraActual) break;  // ← coincide → siguiente palabra
            }
        }

        if (tiempoAgotado || input != palabraActual) {
            QuitarVidaBoss();
            return false;
        }
    }
}

bool Fase3() {
    faseActual = 3;
    ControlSonidoPorFase(faseActual);
    parar_todos();
    
    int tiempoTotal = rand() % (17 - 10 + 1) + 10;
    std::chrono::steady_clock::time_point inicioFase = std::chrono::steady_clock::now();
    
    LimpiarPantalla();
    std::cout << "Presiona L cuando el corazon bombee (se agrande)\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));

    while (true) {
        std::chrono::steady_clock::time_point ahora = std::chrono::steady_clock::now();
        int tiempoPasado = std::chrono::duration_cast<std::chrono::seconds>(ahora - inicioFase).count();

        if (tiempoPasado >= tiempoTotal) {
            return true;
        }

        LimpiarPantalla();
        std::cout << "           .@@@@@.   .@@@@@.\n";
        std::cout << "           @@@@@@@:.:@@@@@@@\n";
        std::cout << "           @@@@:':@@@:':@@@@\n";
        std::cout << "           '@@@:  '@'  :@@@'\n";
        std::cout << "            '@@@.  '  .@@@'\n";
        std::cout << "             '@@@.   .@@@'\n";
        std::cout << "              '@@@. .@@@'\n";
        std::cout << "                \"@@.@@\"\n";
        std::cout << "                 \"@@@\"\n";
        std::cout << "                  '@'\n";

        bool presionoMal = false;
        std::chrono::steady_clock::time_point inicioPequeno = std::chrono::steady_clock::now();

        while (true) {
            std::chrono::steady_clock::time_point actual = std::chrono::steady_clock::now();
            double tiempoVentana = std::chrono::duration_cast<std::chrono::milliseconds>(actual - inicioPequeno).count() / 1000.0;

            if (tiempoVentana >= 1.0) { // Duración del corazón pequeño
                break;
            }

            if (_kbhit()) {
                char tecla = _getch();
                if (tecla == 'l' || tecla == 'L') {
                    presionoMal = true;
                    break;
                }
            }
        }

        if (presionoMal) {
            QuitarVidaBoss();
            return false; 
        }

        LimpiarPantalla();
        std::cout << "          ......       ......\n";
        std::cout << "        .:oOOOOo:.   .:oOOOOo:.\n";
        std::cout << "      .:oOO:'':Oo:. .:oO:'':OOo:.\n";
        std::cout << "     .:oO:'    ':Oo:oO:'    ':Oo:.\n";
        std::cout << "     :oO:        ':O:'        :Oo:\n";
        std::cout << "     :oO:          '          :Oo:\n";
        std::cout << "     ':oO:                   :Oo:'\n";
        std::cout << "      ':oO:                 :Oo:'\n";
        std::cout << "        ':oO.             .Oo:'\n";
        std::cout << "          ':oO.         .Oo:'\n";
        std::cout << "            ':oO.     .Oo:'\n";
        std::cout << "              ':oO. .Oo:'\n";
        std::cout << "                'oO:Oo'\n";
        std::cout << "                 'oOo'\n";
        std::cout << "                  'o'\n";

        bool presionoBien = false;
        std::chrono::steady_clock::time_point inicioGrande = std::chrono::steady_clock::now();

        while (true) {
            std::chrono::steady_clock::time_point actual = std::chrono::steady_clock::now();
            double tiempoVentana = std::chrono::duration_cast<std::chrono::milliseconds>(actual - inicioGrande).count() / 1000.0;

            if (tiempoVentana >= 0.5) { // Duración del corazón grande
                break;
            }

            if (_kbhit()) {
                char tecla = _getch();
                if (tecla == 'l' || tecla == 'L') {
                    presionoBien = true;
                    break;
                }
            }
        }

        if (!presionoBien) {
            QuitarVidaBoss();
            return false;
        }
    }
}

void QuitarVidaBoss() {
    parar_todos();
    if (VidaJugador > 75)          VidaJugador -= 25;
    else if (VidaJugador > 50)     VidaJugador -= 15;
    else if (VidaJugador > 25)     VidaJugador -= 8;
    else                           VidaJugador -= 5;

    Ataque();
    std::this_thread::sleep_for(std::chrono::seconds(1));

    if (VidaJugador <= 0) {
        FinalMalo();
        return;
    }
}

void FinalBueno(){
    parar_todos();
    reproducir("../data/Sonidos/goodending.wav");
    LimpiarPantalla();

    std::cout << "El jefe se agoto, aprovechaste la situación y le pegaste varios escopetazos en la cara\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(4));

    std::cout << "El último escopetazo sono, y el jefe desapareció en la oscuridad como si nunca hubiera existido.\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(4));

    std::cout << "Las cadenas del lugar se rompieron una a una, y los espiritus atrapados comenzaron a liberarse, elevandose en silencio hacia la luz.\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(4));

    std::cout << "El tormento finalmente se detuvo\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(4));

    std::cout << "Una pared se derrumbo, era tu via de escape\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(4));

    std::cout << "Esta vez… había salida.\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(4));

    std::cout << "---\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(4));

    std::cout << "Regresaste a casa.\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(4));

    std::cout << "Tu familia te abrazó sin preguntar nada, como si el tiempo perdido no importara mas.\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(4));

    std::cout << "Solo importaba que habías vuelto.\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(4));
    std::cout << "---\n\n";
    std::cout << "Días despues subiste las fotos a internet.\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(4));

    std::cout << "Nadie creyó la historia al principio.\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(4));

    std::cout << "Pero tu historia comenzo a viralizarse.\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(4));

    std::cout << "Y tu nombre empezo a repetirse en todas partes.\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(4));
    std::cout << "---\n\n";
    std::cout << "Habías sobrevivido.\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(4));

    std::cout << "Y el mundo entero lo supo.\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(4));

    std::cout << "                                                                                                  .88888.                     888888ba   \n";
    std::cout << "                                                                                                 d8'   `88                    88    `8b  \n";
    std::cout << "                                                                                                 88        .d8888b. .d8888b.  88     88  \n";
    std::cout << "                                                                                                 88   YP88 88'  `88 88'  `88  88     88  \n";
    std::cout << "                                                                                                 Y8.   .88 88.  .88 88.  .88  88    .8P  \n";
    std::cout << "                                                                                                  `88888P' `88888P' `88888P'  8888888P'  \n";
    std::cout <<"\n";
    std::cout << "                                                                                888888888  88888888   888888ba    8888888888  88888888    .d88888b  \n";
    std::cout << "                                                                                88         88    88   88    `8b       88      88    88   d8'   `8b \n";
    std::cout << "                                                                                88aaaa     88`   88   88     88       88      88    88   88         \n";
    std::cout << "                                                                                88         88    88   88     88       88      88    88   88   YP88  \n";
    std::cout << "                                                                                88         88    88   88    .8P       88      88    88   Y8.   .88  \n";
    std::cout << "                                                                                888888888  88    88   8888888P'   8888888888  88    88    `88888'   \n";
    std::cout <<"\n";
    std::cout <<"\n";
    std::cout << R"(                                                                                                                          .`^`.  ..'.                                                                                       )" << "\n";
    std::cout << R"(                                                                                                             ";lI,'     .``'   ';<~i`                                                                                       )" << "\n";
    std::cout << R"(                                                                                                                .^:;,'         .>?!`                                                                                        )" << "\n";
    std::cout << R"(                                                                                                                    '^"'       "i:.                                                                                         )" << "\n";
    std::cout << R"(                                .'`^"""",,,,"^``'.                                                                 .....      .^`..''.                                              ......                                  )" << "\n";
    std::cout << R"(                            .`^,I!i!ll!!!!!!lI:^^```'.                                   ......               .^:I!i>>il;,"^``'```'"!!I,^'                                 '^":I!i><>>>i!!I;,^",,^.                          )" << "\n";
    std::cout << R"(                          '^,,^";IllllI;II;:II,`''`````'.                    .       .'^:;Illll;^   .      '";li<+-----+<>i!ii<_--_+~<ilI;:^.                          ."l<~+~~_--?????-__~~~iI^'`:lI^.                      )" << "\n";
    std::cout << R"(                        '^":I"''``"",;III;:;I"""","""^^`''.            .`":::,""^^^`''^,;II;;;IlI:""' .'.'";l!>~_-???-_+~<<>><~___+~<>i!!lI;,'                        ,l><<~++++____++++~~~+++~<!,. "i!,`                    )" << "\n";
    std::cout << R"(                      .^,::::`       .^;lI;I:`^",,,""^```'..          ``^,;I;l!;::;II;;;i>!I;IIllI:,"`. ',I!!i>+_-_+~~~>lIlll!>>>il;:,,""^^":,^.                    'I!iiii><~+___+~<<<~<~~++++~>!;^.'il,^.                  )" << "\n";
    std::cout << R"(                      ^,::;:^.      '^^,;II:"``'.'`'..'```..         ''`;II,"IIIII;,""""^``^`'''..''^,:::;li><~++>,'.     ..':i>i!,   .....'"::"'                  `!>l;::Ii<~++__~>i!IIl!<+~+<>i!llI;II;"'                  )" << "\n";
    std::cout << R"(                    .^""",,`         '^^``^^^^.        '`'.         .'.^Il;,;;,"^`'.....      .`""^^^"""",;><+_+<>l,^`'    '^^,Illl,''..''`^"",,"'                `!l`     ^!<~~<,.       .,><<>!l!!ll;:,"^.                 )" << "\n";
    std::cout << R"(                 .'`^^^,,:,.           . .             '..        .'   ..^,"`''.....         .`""""^"""^^''I<~<<<iI"'       .'`";;`         '^"""^'               ,:       .;<~<"           `ii!I;;;;;::,"^`                 )" << "\n";
    std::cout << R"(                '``",,;I;;:^.    ..    .              ......     `'.`''..'''```^^^`'.       ..         '`''`i<iii,.           .^"`            `""^`.              ""       'l_~>`           .;;:,,,,,,,,,,"^'                )" << "\n";
    std::cout << R"(               '`^",;:;>!><i!lI,.'^^.               ..           ''``'.      .'^,,,`''            ..    .''';!!!:.            `:,`             `^^`'             ',l`'^::,^";l!!,           ^::,:,,,,,::;;IlI:`              )" << "\n";
    std::cout << R"(                ...`^"i>>>><++__~!^....  .  ..     '`                .'``''              ..                 ^;;:`            ':!>i,.          .'``''            .^;;.^,,,,^``"IllI,,,,:,,,:IllIIlIIIlllll!ll;;,`             )" << "\n";
    std::cout << R"(                     .''.  .`";II;:l~~<!I:,:II;:"`""'                                                       .`";;Il!I^.    `:!!I<_<l"`'.....'''````'         ."l<-{)?ilIl>+[{{}[?_~<il!>~~~<>>iii!lII;;;;:,,""^'            )" << "\n";
    std::cout << R"(                              .''..^,:::;!!I;I;::"`..                                                     ..',:,"^``^:I!!!!IIli~~+~~>!;,"^````````'.       '!?}{1))))){}}}{{{{1))1}?_~l;l<~~>i!i!!l;:,",,"^``.             )" << "\n";
    std::cout << R"(  ........                             .`"^^"",,"^`''                                     '^,,:;;IlllI;:"`.  '``^,:;I;:"^``''"i++++++~>i!I,^``````'.       l?]}{{[?-?-_??][}}}{{[?_>!l;,,;llIIIII;:,"^^^``''.               )" << "\n";
    std::cout << R"(`'''''''````^"^^,;`                              .. .          `"""'.                `,l~_-_~<>i;,><:.'^""^.              ."l><~_?+>i!l;:,"^``````'^,,,""""I>~~<>i!I:,i~++---_+>l;:::,,"^""",,,,,"^``'''....                )" << "\n";
    std::cout << R"(""",,,,,,,"`^":;;Il,.                                          ;!!l;;:,^'.'.       ^!!i+?---+~~;..`'  ..'..`.    ''"iI.                     .... ."!iiiiii!;^'....    .'''``'.   .'```'.....   ...''.....'`",,,,,,,,"""^^^^)" << "\n";
    std::cout << R"(ll!!!!!!l;"'.'''`^^^.                                         "I:,"```'...''      .,!!Il<>l!~__I.        .'`"' '"",II,.                          'li><>>>>I,,`                      .`",^''         ..`````,l!!!!!!!!llllIII)" << "\n";
    std::cout << R"(>>>>>><<>ii,.                                               `I><iI,"",,,"`'.       .`,,:":li>>I,^'       .'''.''        .                       ';IIIIIlll:,:,`       .'``        .`",,"`..       .`^^`'''^;i>>>>>>iiiiii!!!)" << "\n";
    std::cout << R"(i>><<>>><<<>I`.                                           ."liiil;,^'..                 .^,,"^.           ''                     ..''..       .''''''''''`^",,,"^^^^",:::,^.    .'`````^","^````^^^``..  ."Illl!!!!iiiiii!!i)" << "\n";
    std::cout << R"(i>>>>>>><>>>i!:`.                                                                                         `'          '",,:;:,^``^^^^^^`````````";ll!!!iiiI"`''....'''.''``'   ....      .......        .`^"""""""""""""",,))" << "\n";
    std::cout << R"(><<<>>>>>>><>iii!!llllllI::,,,,,,,",,,,,,,,"",,,,,,,,,,,:;I!lI;,"``''''''''````````^``..                  .  .....'`^",,:::;l!!iiii>>>>>iiiiii>>>ii>>>>>>>>ii!!lII;:::,,,""""^^^```'``````````^^",::;;;;;;;IIIIIIllllllll!!!)" << "\n";
    std::cout << R"(<<<<<<>>>><<~<>>>>><<<>>>>>i>>><<<<~~<<<<<>>i>>><<<<<<<<<<<<>ii>>>>>>>ii>>>>>>><>>>>><i!i!I;;;:,""^^^^^^^""""",,:;!!!!i>>>>>>><<<<<<<>><<<<<>><<<<<<<<>>><<<<<<>>>>>>>>>>>>>>>>>>iiiii>>>>>i>>iii>>>><<<<<>>>>>>>>>iii>>>>>)" << "\n";
    std::cout << R"(>>>>>>>>>>><<<>>>><<<<<<><<<<<<<<<<<>>>>>>>>>>>>>>>>>>><<<<<<>><<<<<<<<>>><<<<<<<<<<>>>>>>>>>>>><<<<>>>iiiiiiiii>>>>>>>>>>>>>>>><<<<>>>>>>>>>>><<<<<>>>><<<>>>>>>>>>>>>>>>>>>>>>>>>>i>>>>>>>>>>>>>>>>><<<<>>>>>ii>iiiii>iiii)" << "\n";
    std::cout << R"(iiiiiiiiiiiiiiiii>>>>>>>>>>><<<<<<>>><<<<>>>>><<<<>>>><<<<>>>><<>><>>>>>><<<<<>>><<<<>>>>>><<>>>>>>>>>>>>>><>>>>>>><<>>>>>>>>>>>><<>>>>>><>><<>>>><<>><<<<>>>>>>>>>>>>iii>>>>i!!iiiii>>iiiii>>>>>iiiiiiiiiiiiiiii!!!!!!ii!!!)" << "\n";
    std::cout << R"(IIIIIlllllllll!!!!!!!!!!!!!!!!!!!!!!iiiiiiiiiii!!iiiiiiiiiiiiiii!!!iiiii>>>>>>ii>>>iiii>>>>iiii>>>>>>>>iiii>>>iiiii>>>>>>>>>>>>iiiiiiii>>>>>>>>>ii>iii!!!iiiiiiiii!!!!!l!!!!!!!!!!!!l!lll!llll!ii!!!!llllIlllllllIlllIIIIII;)" << "\n";
    std::cout << R"(""",,,,,,:::::::::::::::::;;;;;;;;;IIIIIIIIIIIIIIIIIIIIIIllllllIIIIIIl!lllllllll!!!!!!!!lllllllIIlllllllll!!ll!!!!!!!!!!!!!lllllllllllllllllllllllllllllllllIIIIlIIIIIIIIIIIIIIII;;;;;;:;;:::::;;;;;;;::::::::,,,""""""""")" << "\n";
    std::cout << "\n";
    std::cout << "Presione la tecla a para abandonar el juego\n";
    char tecla;

    do {
        tecla = _getch();
    } while (tecla != 'a');
    

    VidaJugador = 100;
    ResetearCuartos();
    exit(0);
}

void FinalMalo(){
    parar_todos();
    reproducir("../data/Sonidos/muerte.wav");
    LimpiarPantalla();
    std::cout << "El jefe toma control total de tu cuerpo...\n\n";
    std::cout << "El te poseyo...\n\n";
    std::cout << "Ya no eres tu quien actua, solo un espectador atrapado dentro de tu mente...\n\n";
    std::cout << "Ves como destruye todo lo que amas delante de tus ojos...\n\n";
    std::cout << "Tu cuerpo se mueve sin tu permiso, guiado por una voluntad oscura...\n\n";
    std::cout << "Los gritos se apagan lentamente mientras todo cae en desesperación...\n\n";
    std::cout << "Y tú permaneces consciente, sin poder hacer nada para detenerlo...\n\n";
    std::cout << "\n";
    std::cout << "X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X\n";
    std::cout << "|                           ,,'``````````````',,                            |\n";
    std::cout << "X                        ,'`                   `',                          X\n";
    std::cout << "|                      ,'                         ',                        |\n";
    std::cout << "X                    ,'          ;       ;          ',                      X\n";
    std::cout << "|       (           ;             ;     ;             ;     (               |\n";
    std::cout << "X        )         ;              ;     ;              ;     )              X\n";
    std::cout << "|       (         ;                ;   ;                ;   (               |\n";
    std::cout << "X        )    ;   ;    ,,'```',,,   ; ;   ,,,'```',,    ;   ;               X\n";
    std::cout << "|       (    ; ',;   '`          `',   ,'`          `'   ;,' ;              |\n";
    std::cout << "X        )  ; ;`,`',  _--~~~~--__   ' '   __--~~~~--_  ,'`,'; ;     )       X\n";
    std::cout << "|       (    ; `,' ; :  /       \\~~-___-~~/       \\  : ; ',' ;     (      |\n";
    std::cout << "X  )     )   )',  ;   -_\\  o    /  '   '  \\    o  /_-   ;  ,'       )   ( X\n";
    std::cout << "| (     (   (   `;      ~-____--~'       '~--____-~      ;'  )     (     )  |\n";
    std::cout << "X  )     )   )   ;            ,`;,,,   ,,,;',            ;  (       )   (   X\n";
    std::cout << "| (     (   (  .  ;        ,'`  (__ '_' __)  `',        ;  . )     (     )  |\n";
    std::cout << "X  )     \\/ ,\".). ';    ,'`        ~~ ~~        `',    ;  .(\".), \\/  )  X\n";
    std::cout << "| (   , ,'|// / (/ ,;  '        _--~~-~~--_        '  ;, \\)    \\|', ,    )|\n";
    std::cout << "X ,)  , \\/ \\|  \\\\,/  ;;       ,; |_| | |_| ;,       ;;  \\\\//  |/ \\/ ,X\n";
    std::cout << "|\",   .| \\_ |\\/ |#\\_/;       ;_| : `~'~' : |_;       ;\\_/#| \\/| _/ |. |\n";
    std::cout << "X#(,'  )  \\\\\\#\\ \\##/)#;     :/       \\/   :     ;#(\\##/ /#///  (     X\n";
    std::cout << "|| ) | \\ |/ /#/ |#( \\; ;     :               ;     ; ;/ )#| \\#\\ \\| / | |\n";
    std::cout << "X\\ |.\\\\ |\\_/#| /#),,`   ;   /\\_     _/\\.;     ;   `,,(#\\ |#\\_/|     X\n";
    std::cout << "| \\\\_/# |#\\##/,,'`       ;     ~~--|~|~|--~~     ;       `',,\\##/#| #\\_|\n";
    std::cout << "X  ##/#  #,,'`            ;        ~~~~~        ;            `',,#  #\\##  /X\n";
    std::cout << "|####@,,'`                 `',               ,'`                 `',,@####| |\n";
    std::cout << "X#,,'`                        `',         ,'`                        `',,###X\n";
    std::cout << "|'  spb                          ~~-----~~                               `' |\n";
    std::cout << "X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X\n";
    std::cout << "\n";
    std::cout << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(15));
    reproducir("../data/Sonidos/badending.wav");
    LimpiarPantalla();
    std::cout << "Las almas no encontraron descanso...\n\n";
    std::cout << "Quedaron atrapadas en los pasillos interminables del hotel, repitiendo sus ultimos pasos una y otra vez...\n\n";
    std::cout << "Susurros vacios recorren las paredes, como si el lugar mismo estuviera vivo...\n\n";
    std::cout << "Incluso los disfraces usados para alegrar a los niños ahora están corrompidos...\n\n";
    std::cout << "Las mascaras sonríen sin vida, pero dentro de ellas algo aun observa...\n\n";
    std::cout << "Cada vez que el hotel se queda en silencio, se escuchan risas apagadas desde lo profundo...\n\n";
    std::cout << "No son recuerdos... son almas atrapadas, incapaces de escapar de este lugar...\n\n";
    std::cout << "Y el hotel sigue abandonado... como si nada hubiera pasado...\n\n";
    std::this_thread::sleep_for(std::chrono::seconds(15));
    std::cout << "\n";
    std::cout << "                                                                                                    888888ba  .d888888  888888ba  \n";
    std::cout << "                                                                                                    88    `8b d8'    88 88    `8b \n";
    std::cout << "                                                                                                    88aaaa8P' 88aaaaa88 88     88 \n";
    std::cout << "                                                                                                    88    `8b 88     88 88     88 \n";
    std::cout << "                                                                                                    88    .8P 88     88 88    .8P \n";
    std::cout << "                                                                                                    88888888' 88     88 8888888P' \n";
    std::cout << "\n";
    std::cout << "                                                                                888888888  88888888   888888ba    8888888888  88888888    .d88888b  \n";
    std::cout << "                                                                                88         88    88   88    `8b       88      88    88   d8'   `8b \n";
    std::cout << "                                                                                88aaaa     88`   88   88     88       88      88    88   88         \n";
    std::cout << "                                                                                88         88    88   88     88       88      88    88   88   YP88  \n";
    std::cout << "                                                                                88         88    88   88    .8P       88      88    88   Y8.   .88  \n";
    std::cout << "                                                                                888888888  88    88   8888888P'   8888888888  88    88    `88888'   \n";
    std::cout << "\n";
    std::cout << "\n";
    std::cout << R"(                                                                                                                          ';I'   .`'                                                                                        )" << "\n";
    std::cout << R"(                                                                                                            ^><l^.      ^,'   .;~~~"                                                                                        )" << "\n";
    std::cout << R"(                                                                                                               'l>I`   '.      !?-:                                                                                         )" << "\n";
    std::cout << R"(                                                                                                                  `!;'         >],                                                                                          )" << "\n";
    std::cout << R"(                                                                                                                    ':"       '<`                                                                                           )" << "\n";
    std::cout << R"(                                 ..'^":,,,""""`'.                                                                             I'...                                                                                         )" << "\n";
    std::cout << R"(                              '",:!!!i>>>>iil;:"""""'                                                          .";;!!I;,'.       ..II:'                    ..                 '"IlllI:;;I!!"'.                              )" << "\n";
    std::cout << R"(                            `^'^":llII!!::l!lll"`..`^^^.                               .`:::II,              ";I!>_-++~ilI;lll!l;;!>il;I:`             ^,::::;:,"'      .;>>~~-]][?_-?+<<!ll<\t_l'                          )" << "\n";
    std::cout << R"(                          ."";:^"lIlIll;:lI",I"^'`'`^``''.                  ....   .''^,,:;lllII"   ,     .,Il>~+-???]-+~<>ii~-[]?+_~>!lI:,'.i{C1v"  `,:;>})-~>l;:".  :l++~+~++_-?-]?-+--<_+i!_~i(>I`                       )" << "\n";
    std::cout << R"(                         '""Il`  .`,,,IIl;:"I,"",":,"`"``'..            `;I;,`^"^"'..'^,;lI,;;liI::`.:>I;,ll!i~_?]?_?_<~<<!>>+?_+~~>ii!lIl;""f'OlM*`.,;-a#zWWC]+>;:^`l><~>~~~+_-+_~~<~>i+_++~<i>] >_l:`                     )" << "\n";
    std::cout << R"(                        ^:,::;        "l!l,;;^."","",,^''`..          .:`,I!lll:,;l<!,:I_?i!l!llllI".   ':I!li~_?-~~!~~<>><i!>~!<~<!I;:",,::"^?jU*[/`:Iuaw#@@hB?+>;:!i!i>>>~~--?_]____?-+__~~~~>;.]~<:^`                    )" << "\n";
    std::cout << R"(                       `^:"",:`         I!I;"":,^":^'''''''.          ^ :I:::l!I!:;"^;II::"`"",;,"";;I"':;l!>><~+<il^,^`.,`.l><il`....     ":"^j,.. `::~_[*BB08_+>l~i!i!!!>~_-]{1()(((1}?--_~<i!lI~t+l,`.                   )" << "\n";
    std::cout << R"(                      .:;:II;^:l~+?+"";::I!<ii!!ilI;:,```'.          ``"IlI,`l;I;I;:,"^`'',^. .`""^'",:;:I!><<++>:         .^l~<<<;IllllI:^^:;"`     ";l<+?-?[_~iI~~>}-,"l~_]1\///fxfttf||1?_+!!Ill;II:^`                   )" << "\n";
    std::cout << R"(                     ."""^^"li:<-_~ii!"";Ii_-?????-_~l;:"'.         `^;IliI"I;:,^..       '":I!><<>iill;^"i<>__~ii:```.'..``^;<+_][?][{{~il;^,:^'    ',::l><~<iI;i_(x+j" .~])|//fnJqqU/({)|)?~!liilI;;""^.                  )" << "\n";
    std::cout << R"(                   .`^^^^;;;>:!<_;)?<+':I~-?})/vff)}]_~!;` .       `';`..`,"^      ..   ':;!~-]{11{}]?_>l^">i+><<!!"~" `    ;l<?[1kWZ|]??v{!I^""`.     `,,:::::,"l\u>t?)l^i{|tfn%8M@@8b&f)1([+!;;;I;;:""`'                  )" << "\n";
    std::cout << R"(                 '^`^:^,I:II:~i>"[!__`,;<_?)ZB%YBB8L)[?~l:'.      ``^..'''`"",:,^'^`   `:l~-[}|XYf|{}}[-~l,i<<ii!<>.       .:!_?)v)u/j%n[-]Yl,^^''              ';|<:)_rc;>1\tfb@&h@@8a@w({1]>I"^,,,,,,:,"`                 )" << "\n";
    std::cout << R"(                '''^;,";I;,"`^,, .<". ";~-}CBap@@B%L#{]_>I^      `:,,'`..... .``^^`.`.':l+?[)U**@@bBm|{}?~;!>iii<l        '':i?}}QB@@#(a}]_)z:^^`'              `I|< `)n?([|tjfd@&h@@%MBY11}-il:,,,",,;;!>!I`               )" << "\n";
    std::cout << R"(                `^^,"I,l~>++<i!i"     ";~?}|0d@@@*pBB1[_>;^      ";^`''      ..;:     `;<-[1CBBL@@#%@#(}}-!l!llIcz^      ''':i][{LB@@h|o}?_>UI`^`'.   .     .. .";[~",I~;l>[)/fJ@Wk@@%MBY11}-il:,,,",,;;!>!I`               )" << "\n";
    std::cout << R"(                ...'`,;i++_------~;.  ':i+]{)*@@qb@BC{]_>:'         ..`^'.            `;<[{)JBBo8@oW@Bt{[_>;;;;"XZY!     ``.,i_{1cvffL%n]-_!)I'``'.:!^''!^  I[x(:I"'";":,"ii[)\jfdh%8CZ|\(1[+il!lIl!!Iiil;;:,.              )" << "\n";
    std::cout << R"(                     .";,...':i>i!!;i+~~><-]1(\\xaZt{]_<I,.                           `;i_[)|W@@d@8&@B/{]+!:",""l~\[i^  ... !+<?){rJY\]?_+li:'''`'.        .':>:>-<  ^.. ,-]}1()(|\tjrj/\(}_~ilI;I;;I;:;;,,"^'              )" << "\n";
    std::cout << R"(                              .";,`^!><>>>~-?[{{{}]?-~i;,'                            .,l+?}(b@@bB@dMc)[-+I:`,;IIll"'..^_^l!<~!?][[?----+!I,'.'```.        .l]{1|///([{))(\((((\///){1(|1?-_>>>i!l;:,:,,"^^^'               )" << "\n";
    std::cout << R"(                                .  .'^"^,l<>>~+~+_~>l;:^                               ':l+?[{/jUQz|({]-~l:'^,"^`' `",li!!lI,!++_--_~<!I;"''''''''        "]1{{)1{}){]]}}[]]{1|()}[[_!i~+_<il!l!l;:,,"",^``'                )" << "\n";
    std::cout << R"(                                   .    .""^^,;Ill;"^.                                  ':I<_?}{)((){}[_l:.  '^,l<_>>!,^'.  .!++_+++<>ii!"'''`'''..''.. .`+?[})1]?_?+_]]]]?]}{{]-~!l;,",!lIlllI;,,"^^^`''..                 )" << "\n";
    std::cout << R"(...........''''''`^.,?:"^.                 .......' ..          ''.                    ^>-?___???_++<I:,"l'                ^<+_}\{+~<<>!I;"'''`''.^^^^'``"<-[]-_>>>i<~-?][][?-~l;:;:,,`"",Il;I::^^`'''...''                  )" << "\n";
    std::cout << R"(''''''''''```":;;I>I><.'}l.  ^`                   . .          ';Il,"^^.            "<~+][[?+<~i^l_I'.^l:'`.           .,`",::,,""^``'... .'```'.`I;;IlIIl:I;;;;,'  ^!!!i>>i:^'^,,,"^`'```'`'``'''....  ``'''.........      )" << "\n";
    std::cout << R"(""",:;;;:::,'`^,:;IlI.                                         ,>>llII:,^'`'       ;~I<-----~+_. ..       .`    `^^-{,xJLLCCJJQQLCJf    "'..     ,>i!>>>>!:.                     .'..         ....    '``";;;;;;:;::,,,,,"^)" << "\n";
    std::cout << R"(lll!!llIl!I`...'`^"^^.                                        `!'`'...  .'`.      .liI:;~!;>+?-'        ..'',  ",":"'. ;xnunnvvuxjj|   .1`      .ili<!>~i:,:            ii,  '....`">l>+,          .^^`'',lllll!llllllIIIIlI)" << "\n";
    std::cout << R"(!!>>ii><<>!!"       ..                               ...     '<<i;   .':,^^        ':;;;::;>+~l:,.       ...`""'    .  ';"l<>([~i;'^'   :.     '~<ii>>><<::;^         .'         .:;;,:,^l_?<;`  .""`'..`l>>>iii!!!!!!!!!!!l)" << "\n";
    std::cout << R"(<>>>><<<<>>>i^                                     ^:I'    .;>++~~+>I:"`....         .``^;ii!:`'.        ...      .     ^",:Ii>+]{}}})\f}'   .'`````^``^"",;;:^   .`":;;^      .'`^^^",:;I!:`.'`^"^`'.. ^iiiiiiiii!!i!!!!i>i)" << "\n";
    std::cout << R"(!ii<<>>ii><<>i:'                                .:ll;^.  .'";:;I,.                       .'..             ".           ':"^``'.''```'`^``'..   .......''''^,,,"",,::,,"",`    '``'''''^,,""""^```'.    ';lllllllll!!!!!!iiii)" << "\n";
    std::cout << R"(!ii>>ii><<>iiil,.                             .i-_i,,I;:,^.                                              .^          "_[[{)){[?-[[-[}[??-+-_~!`';!><>i>>>:.       .....^``.  ..                       ;~~~>!!l:::,"^``^``^:)" << "\n";
    std::cout << R"(<<<>iiii>>iiiil!!!!lII;;;,^`'''''......''''''`^,;IllI^''`":lil:"`'                                .                 .^^``'`;!l!!!!!<<>ii<>illi>ii>ii>ii<>>i!II;,""^^'.   ....           ..''`^",,:,,,,,"""""",::::;;;;Illll!)" << "\n";
    std::cout << R"(>><<>>>>>ii<~~>i>><<<><<<>>ii><<<<<>~~~<~+~<ii>>><<<>>>><<<>i!!!Il!ll!!!lIli>>i!i>-_~>I,,;l,,' '`    .''````````^liii!!><>i>>><~<<~>i>>>i><>i><>iii<>i>>><~<>>~<>>>>>>><><iii!!!lllllll!><++~~~<~~<<<<>iiii<>>iiii>><>i>>>>!)" << "\n";
    std::cout << R"(~<<<>i>>>>><<~<>iii>>>ii>i>i!!iiii>~<>><>>ii>>>i>~<>>>>>>i>><>!><>>i><<>i<~>>>><<>>>><i>~>!i><>i!llllI;;;;;;IIlll!i!!i>>iii><<<~~>><>>>>>><>i<~<><<<><>i~~>>+~i><>i>>>>>i>>iii>><<ii<~~<>iii>i!!!ii><~~~<<><>i><illiiiiii>>i)" << "\n";
    std::cout << R"(i!!iiii>ii><<<<>>ii<<<<<>>~~<<<>><<<>i!i>>>>>><>i!!>>ii>~<<~~<>><<~~<>>>><>>><~>><<>>i!i<~<ii>i<~~<<<<<>i><>>>>>i><>>>><<<>>>iii>~<>iii!ii>i>><<<>>>i!><>iiiii>>>>i<ii>>>ii><<>iiiii>ii!i>ii>>><>>>><<>i>>>>i!!!iiii>>iii!!l)" << "\n";
    std::cout << R"(iiiii>>>iiii!iiii!!>>>>>>iii<>>~+<>ii>><<>i<>><~~<>>>><<<>>>>>>>>>><>>>i>>~~<>>><><>>>>ii><~~<iii!!i>ii><>>i!!!><<<<<<>i!><>ii>><<>i!i<>><<><<>>i>ii<~~<<<i><<>>>>>iiii>>>>!!!iiii>>i>>ii>>>>>!!!iii>ii!ii!!iii!!!ll!i!!ill!)" << "\n";
    std::cout << R"(ilIIIll!!l!i!l!!!ii>ill!!!iii>>iii>>>>>>>iii!i>>!!!!ii>>iiiii>iiiiiiii>>>>>><<ii>iii!!i>>>i>i!i<<>i><>>>>i><<>ii>><~>i!i>>>i!i><>><>ii><>>iii>ii><<>iiii>>>>ii>i!!iii!l!i>!!!!l!i>iii!ll!i!l!>i!!!l!illl!!!!iilllllIllllII;;)" << "\n";
    std::cout << R"(::;;::;;;I;;II;;IIIllIIIIIIIllIIIIIlll!!iill!ill!ii!!ll!lll!ii!i!!l!i!l!>i!i>iiii>ii>ii>>i!!!!!i!!!ii!ll!!i>i!ll!!!i>ii>i!i>>!!!!!!!iiiiiii>>ii!!!!!ll!!!!lll!!!!llIIIllllll!!!llI;;IllIIIIIIIIllllII;;;;I;;I;;;;II;::::,,,)" << "\n";
    std::cout << R"(^^``^","^^""""""""",,,,:,",,",:;;::;;:;II;:;;;I;;;;;;IIII;;IIII;;;;;;IIIIIllI;IIIIIlllllIII;;IllI;;IllIl!llIlIIl!ll!lIIlllIIlIlllI;IIIIIIIIIIIIIIllI;I;;IIIlI;;;III;;;;;I;::;;;:;;:;;;;::::,,,,:::,,:,,""",,,"""""""^^^^^``^)" << "\n";
    std::cout << "\n";
    std::cout << "Presione la tecla a para abandonar el juego\n";
    char tecla;

    do {
        tecla = _getch();
    } while (tecla != 'a');

    VidaJugador = 100;
    ResetearCuartos();
    exit(0);
}