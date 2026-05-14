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
// 'W' = well, 'C' = cooler, 'S' = seal (pentagrama), 'D' = puerta bloqueada
// Los cuartos se guardan como .txt en ../data/Cuartos/
// El inventario del jugador se guarda en un .txt en ../data/inventario.txt
//
// REGLA GENERAL DE GUARDADO — MUY IMPORTANTE:
// En TODOS estos momentos, lo primero que hay que hacer es guardar el mapa
// actual y la posición del jugador ANTES de hacer cualquier otra cosa:
//   - Cuando el jugador toca un '?'
//   - Cuando el jugador toca una interacción ('W', 'C', 'G', 'D')
//   - Cuando el jugador abre el inventario con 'i'
//   - Cuando el jugador presiona pausa con 'm'
//   - Cuando el jugador cambia de cuarto (esto ya está implementado)
// Para guardar, siempre usá este bloque:
//   std::string archivoActual = "../data/Cuartos/Cuarto" + std::to_string(habitacion) + ".txt";
//   guardarMapa(archivoActual, mapa);
//   int filaGuardada = fila;
//   int columnaGuardada = columna;

// ─────────────────────────────────────────
// SECCIÓN 1 — SISTEMA DE EVENTOS AL TOCAR '?'
// (Ve a la línea 468, donde está el if (mapa[nuevafila][nuevacolumna] == '?'))
// ─────────────────────────────────────────

// PASO 1: Guarda el estado actual (ver REGLA GENERAL DE GUARDADO arriba).

// PASO 2: Genera un resultado aleatorio con una función nueva llamada
//   generarEvento(). Esa función retorna un string con el resultado.
//   Usá rand() con los siguientes pesos de probabilidad:
//
//   ALTA probabilidad (70% del total, repartido entre estos 8 objetos):
//     "KeyCard", "LiquidMercury", "HolyCross", "Note1",
//     "Note2", "Coin", "ShotGun", "ShotGunAmmo"
//
//   MEDIA probabilidad (20% del total, repartido entre estas 3 interacciones):
//     "Well", "Cooler", "Seal"
//
//   BAJA probabilidad (10%):
//     "Monster"
//
//_______________________________________________________________________________________________________________
//!!IMPORTANTISIMO!!, asegurate que si ya se encontro cierto objeto o cierta interaccion
//(puedes guardar la lista de objetos e interacciones en un vector tipo vector<char> encontrados;),
//no se repita otra vez, y si ya no hay mas objetos, que ahora la probabilidad de interacciones y mounstruos
//sea 60, 40 respectivamente. Si ya no hay mas interacciones pero hay mas objetos que la probabilidad entre
//objetos y mounstruos sea de 70, 30 respectivamente. Finalmente si no hay ninguna de las otras dos 
//que la probabilidad de mounstruos sea del 100%
//_______________________________________________________________________________________________________________
//
//   Implementación sugerida:
//     int r = rand() % 100;
//     if (r < 70)      { // objeto       }
//     else if (r < 85) { // interaccion  }
//     else             { // monstruo     }

// PASO 3: Según lo que retornó generarEvento(), hay TRES casos:

//   CASO A — Encontró un OBJETO (KeyCard, Coin, ShotGun, etc.)
//     1. Abrí la imagen del objeto con AbrirImagen() ANTES de limpiar pantalla.
//        Mirá la Sección 4 para saber qué nombre pasarle.
//        La imagen se abre en una ventana aparte, el juego sigue corriendo.
//     2. Llama LimpiarPantalla()
//     3. Espera 1 segundo: std::this_thread::sleep_for(std::chrono::seconds(1));
//     4. Imprime: "You found a [nombre del objeto]!"
//     5. Imprime: "It has been added to your inventory."
//     6. Guardá el objeto en inventario.txt con ofstream en modo ios::app
//     7. Esperá 2 segundos: std::this_thread::sleep_for(std::chrono::seconds(2));
//     8. Reemplazá el '?' por '.': mapa[nuevafila][nuevacolumna] = '.';
//     9. Volvé al jugador a filaGuardada/columnaGuardada:
//        mapa[filaGuardada][columnaGuardada] = 'P';
//        fila = filaGuardada; columna = columnaGuardada;
//    10. Guardá el mapa con guardarMapa()
//    11. Llama mostrarMapa(mapa)

//   CASO B — Encontró una INTERACCIÓN (Well, Cooler, Seal)
//     PRIMERA VEZ que se toca el '?':
//     1. Abrí la imagen: AbrirImagen("well") / AbrirImagen("cooler") / AbrirImagen("seal")
//     2. Llama LimpiarPantalla()
//     3. Espera 1 segundo
//     4. Imprime: "You found a well!" / "You found a cooler!" / "You found a pentagram!"
//     5. Imprime: "Press any key to continue..."
//     6. Espera _getch()
//     7. Reemplazá el '?' por el char de la interacción:
//        Well -> 'W',  Cooler -> 'C',  Seal -> 'G'
//     8. Volvé al jugador a filaGuardada/columnaGuardada
//     9. Guardá el mapa con guardarMapa()
//    10. Llama mostrarMapa(mapa)
//
//     SEGUNDA VEZ — cuando el jugador camina sobre 'W', 'C' o 'G' (ver Sección 2).

//   CASO C — Encontró un MONSTRUO
//     1. Abrí imagen aleatoria: AbrirImagen("monster" + std::to_string(rand() % 3 + 1))
//     2. Llama LimpiarPantalla()
//     3. Espera 1 segundo
//     4. Imprime: "A monster appeared!"
//     5. Imprime: "Press any key to continue..."
//     6. Espera _getch()
//     7. Reemplazá el '?' por '.': mapa[nuevafila][nuevacolumna] = '.';
//     8. Volvé al jugador a filaGuardada/columnaGuardada
//     9. Guardá el mapa con guardarMapa()
//    10. Llama mostrarMapa(mapa)
//    11. Llama Monstruo() — ya existe y maneja todo el combate.

// ─────────────────────────────────────────
// SECCIÓN 2 — INTERACTUAR CON W, C, G (Well, Cooler, Pentagrama)
// ─────────────────────────────────────────

// Cuando el jugador camina sobre 'W', 'C' o 'G':
//   1. Guardá el estado actual (ver REGLA GENERAL DE GUARDADO arriba).
//   2. Llama LimpiarPantalla()
//   3. Imprime: "Select an object to use here:"
//   4. Imprime: "(Press 'b' to go back to the map)"
//   5. Mostrá el inventario (leé inventario.txt línea por línea con ifstream)
//   6. Esperá input del jugador:
//      std::string objeto;
//      std::cin >> objeto;
//      - Si objeto == "b": LimpiarPantalla(), mostrarMapa(mapa), return  <- vuelve al mapa
//   7. Verificá si ese objeto es válido para esa interacción.
//      IMPORTANTE: las interacciones NO generan objetos directamente.
//      El jugador debe haber combinado los objetos necesarios ANTES (ver Sección 3).
//      Lo que hace la interacción es consumir el objeto correcto ya combinado:
//
//      'W' (Well):
//        - Objeto válido: "Coin"
//          Eliminá "Coin" del inventario, agregá "KeyMold"
//          Mostrar: "You dropped the coin in the well. You received a KeyMold!"
//          Reemplazá 'W' por '.': mapa[nuevafila][nuevacolumna] = '.';
//
//      'C' (Cooler):
//        - Objeto válido: "MetalKey" (que se obtiene combinando KeyMold + LiquidMercury)
//          Eliminá "MetalKey" del inventario
//          Mostrar: "You used the MetalKey in the cooler. The cooler is now open!"
//          Reemplazá 'C' por '.': mapa[nuevafila][nuevacolumna] = '.';
//        - NOTA: el jugador primero debe haber combinado KeyMold + LiquidMercury
//          en el inventario (tecla 'i') para obtener el MetalKey. Ver Sección 3.
//
//      'G' (Pentagrama):
//        - Objeto válido: "HolyCross"
//          Eliminá "HolyCross" del inventario, agregá "HolyBible"
//          Mostrar: "You placed the cross on the seal. You received the HolyBible!"
//          Reemplazá 'G' por '.': mapa[nuevafila][nuevacolumna] = '.';
//
//   8. Si el objeto no es válido o la combinación no funciona:
//      LimpiarPantalla()
//      Imprimí: "Invalid object. Nothing happened."
//      Esperá 1 segundo
//      Volvé al jugador a filaGuardada/columnaGuardada
//      Guardá el mapa, mostrarMapa(mapa), return
//   9. Si fue válido: guardá el mapa con guardarMapa(), LimpiarPantalla(),
//      volvé al jugador a filaGuardada/columnaGuardada, mostrarMapa(mapa)

//   CÓMO ELIMINAR UN OBJETO DEL INVENTARIO:
//     std::vector<std::string> items;
//     std::ifstream fin("../data/inventario.txt");
//     std::string linea;
//     while (std::getline(fin, linea)) items.push_back(linea);
//     fin.close();
//     std::ofstream fout("../data/inventario.txt");
//     for (int i = 0; i < items.size(); i++) {
//         if (items[i] != "NombreAEliminar") fout << items[i] << "\n";
//     }

// ─────────────────────────────────────────
// SECCIÓN 3 — SISTEMA DE COMBINACIÓN (tecla 'i' en el mapa)
// ─────────────────────────────────────────

// Cuando el jugador presiona 'i' mientras está en el mapa:
//   1. Guardá el estado actual (ver REGLA GENERAL DE GUARDADO arriba).
//   2. Llama LimpiarPantalla()
//   3. Imprime: "INVENTORY — What do you want to combine?"
//   4. Imprime: "(Press 'b' to go back to the map)"
//   5. Mostrá el inventario (leé inventario.txt línea por línea con ifstream)
//   6. Pedí input: el jugador escribe DOS nombres separados por espacio,
//      o 'b' para volver:
//      std::string obj1;
//      std::cin >> obj1;
//      - Si obj1 == "b": LimpiarPantalla(), mostrarMapa(mapa), return
//      std::string obj2;
//      std::cin >> obj2;
//   7. Verificá si esa combinación es válida.
//      Combinaciones posibles (usá if/else if para poder agregar más fácil):
//      - "KeyMold" + "LiquidMercury" (en cualquier orden) -> resultado: "MetalKey"
//        Eliminá ambos del inventario, agregá "MetalKey"
//        Mostrar: "You combined KeyMold and LiquidMercury. You received a MetalKey!"
//   8. Si la combinación NO es válida:
//      LimpiarPantalla()
//      Imprimí: "Invalid combination. Those items cannot be combined."
//      Esperá 1 segundo
//      LimpiarPantalla(), mostrarMapa(mapa), return
//   9. Si fue válida: esperá 1 segundo, LimpiarPantalla(), mostrarMapa(mapa)

// ─────────────────────────────────────────
// SECCIÓN 4 — FUNCIÓN AbrirImagen (ya existe, solo modificala)
// ─────────────────────────────────────────

// Modificala para que reciba un string con el nombre del archivo:
//   void AbrirImagen(std::string nombreImagen)
// Que abra: "../data/3D/" + nombreImagen + ".png"
//
// Usala así:
//   - "KeyCard"       -> AbrirImagen("keycard")
//   - "Coin"          -> AbrirImagen("coin")
//   - "ShotGun"       -> AbrirImagen("shotgun")
//   - "LiquidMercury" -> AbrirImagen("mercury")
//   - "HolyCross"     -> AbrirImagen("cross")
//   - "Note1"         -> AbrirImagen("note1")
//   - "Note2"         -> AbrirImagen("note2")
//   - "ShotGunAmmo"   -> AbrirImagen("ammo")
//   - "Well"          -> AbrirImagen("well")
//   - "Cooler"        -> AbrirImagen("cooler")
//   - "Seal"          -> AbrirImagen("seal")
//   - "Door"          -> AbrirImagen("door")
//   - Monstruo        -> AbrirImagen("monster" + std::to_string(rand() % 3 + 1))
// Los objetos KeyMold, MetalKey y HolyBible NO tienen imagen.

// ─────────────────────────────────────────
// SECCIÓN 5 — PUERTA BLOQUEADA 'D'
// ─────────────────────────────────────────

// Cuando el jugador camina sobre 'D':
//   1. Guardá el estado actual (ver REGLA GENERAL DE GUARDADO arriba).
//   2. Abrí la imagen: AbrirImagen("door")
//   3. Llama LimpiarPantalla()
//   4. Imprime: "The door is locked."
//   5. Imprime: "Select an object to use:"
//   6. Imprime: "(Press 'b' to go back to the map)"
//   7. Mostrá el inventario (leé inventario.txt línea por línea)
//   8. Esperá input:
//      std::string objeto;
//      std::cin >> objeto;
//      - Si objeto == "b": LimpiarPantalla(), mostrarMapa(mapa), return
//   9. Verificá si el objeto abre la puerta:
//      - Si objeto == "MetalKey":
//          Mostrar: "The door opened!"
//          Eliminá "MetalKey" del inventario
//          Reemplazá 'D' por '.': mapa[nuevafila][nuevacolumna] = '.';
//          NO se genera ningún objeto nuevo.
//      - Si el objeto no es válido:
//          LimpiarPantalla()
//          Imprimí: "Invalid object. This doesn't work here."
//          Esperá 1 segundo
//          Volvé al jugador a filaGuardada/columnaGuardada
//          Guardá el mapa, mostrarMapa(mapa), return
//  10. Si fue válido: guardá el mapa, LimpiarPantalla(),
//      volvé al jugador a filaGuardada/columnaGuardada, mostrarMapa(mapa)

// ─────────────────────────────────────────
// SECCIÓN 6 — FUNCIÓN Flee() — HUIR DEL MONSTRUO
// ─────────────────────────────────────────

// La función Flee() ya existe pero está vacía. Completala así:
//   1. Eliminá la 'P' del cuarto actual y guardá el mapa sin el jugador:
//        mapa[filaGuardada][columnaGuardada] = '.';
//        guardarMapa(archivoActual, mapa);
//      IMPORTANTE: si no hacés esto, el cuarto anterior queda con una 'P' fantasma.
//   2. Elegí una conexión aleatoria EXCLUYENDO habitacionDestino == 7:
//        int indice;
//        do { indice = rand() % totalConexiones; }
//        while (conexiones[indice].habitacionDestino == 7);
//   3. Cargá el cuarto destino:
//        char mapa[12][23];
//        cargarMapa(conexiones[indice].archivoDestino, mapa);
//   4. Poné al jugador en la posición de esa conexión:
//        mapa[conexiones[indice].nuevaFila][conexiones[indice].nuevaColumna] = 'P';
//   5. Guardá ese cuarto: guardarMapa(conexiones[indice].archivoDestino, mapa);
//   6. LimpiarPantalla()
//   7. Imprime: "You managed to flee!"
//   8. Esperá 1 segundo
//   9. mostrarMapa(mapa)

// ─────────────────────────────────────────
// NOTAS FINALES
// ─────────────────────────────────────────
// - SIEMPRE guardá mapa y posición al inicio de cada evento (ver REGLA GENERAL).
// - Para sleep: std::this_thread::sleep_for(std::chrono::seconds(1));
// - Para volver al mapa desde inventario o interacción: el jugador escribe 'b'.
// - Si un objeto o combinación es inválido: LimpiarPantalla(), mensaje de error,
//   1 segundo de espera, volver a filaGuardada/columnaGuardada, mostrarMapa().
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

void Correr() {
    CorrerASCI();
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));

    if (!_kbhit() || _getch() != ' ') {
        LimpiarPantalla();
        VidaJugador  = VidaJugador - 30;
        Monstruo();
    }

    int tiempoTotal = 0;

    while (tiempoTotal < 10000) {
        CorrerASCI();
        std::this_thread::sleep_for(std::chrono::milliseconds(400));

        if (!_kbhit() || _getch() != ' ') {
            LimpiarPantalla();
            VidaJugador = VidaJugador - 30;
            Monstruo();
        }

        tiempoTotal += 400;
    }

    LimpiarPantalla();
    int r = rand() % 100;
    if (r < 60) {
        Fight();
    } else {
        Flee();
    }
}

void Fight(){

}

void Flee(){

}

void Monstruo(){
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
            Correr();
            return;
        } else if (tecla == 'f'){
            Fight();
            return;
        } else if (tecla == 'b'){
            break;
        }


    }
}