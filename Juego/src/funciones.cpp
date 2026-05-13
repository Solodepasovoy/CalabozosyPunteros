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
// 'W' = well, 'C' = cooler, 'S' = seal (pentagrama)
// Los cuartos se guardan como .txt en ../data/Cuartos/
// El inventario del jugador se guarda en un .txt en ../data/

// ─────────────────────────────────────────
// SECCIÓN 1 — SISTEMA DE EVENTOS AL TOCAR '?'
// (Ve a la línea 313, donde está el if (mapa[nuevafila][nuevacolumna] == '?'))
// ─────────────────────────────────────────

// PASO 1: Antes de mostrar nada, guarda el estado actual.
//   - Llama guardarMapa() con el archivo del cuarto actual.
//   - Guarda la fila y columna actual del jugador en variables
//     (ej: filaGuardada, columnaGuardada). Las vas a necesitar después.

// PASO 2: Genera un resultado aleatorio con una función nueva llamada
//   generarEvento(). Esa función retorna un string con el resultado.
//   Usá rand() con los siguientes pesos de probabilidad:
//
//   ALTA probabilidad (70% del total, repartido entre estos):
//     "KeyCard", "LiquidMercury", "HolyCross", "Note1",
//     "Note2", "Coin", "ShotGun", "ShotGunAmmo"
//
//   MEDIA probabilidad (20% del total, repartido entre estos):
//     "Well", "Cooler", "Seal"
//
//   BAJA probabilidad (10% del total, repartido entre estos):
//     "Monster1", "Monster2"  <- (ponle el nombre que quieras al monstruo)
//
//   Sugerencia de implementación:
//     int r = rand() % 100;
//     if (r < 70) { // objeto } else if (r < 90) { // interaccion } else { // monstruo }

// PASO 3: Según lo que retornó generarEvento(), hay DOS casos:

//   CASO A — Encontró un OBJETO (KeyCard, Coin, ShotGun, etc.)
//     1. Llama LimpiarPantalla()
//     2. Imprime: "You have found a [nombre del objeto]!"
//     3. Imprime: "Press 'a' to continue..."
//     4. Espera que el jugador presione 'a' con _getch()
//     5. Guarda el nombre del objeto en el inventario:
//        Abrí (o creá si no existe) ../data/inventario.txt con ofstream en modo append (ios::app)
//        y escribí una línea con el nombre del objeto.
//     6. En el mapa, reemplazá el '?' por '.' (el símbolo desaparece)
//     7. Mové al jugador a la posición donde estaba el '?'
//        (es decir, mapa[nuevafila][nuevacolumna] = 'P', mapa[fila][columna] = '.')
//     8. Llama mostrarMapa() para volver al cuarto

//   CASO B — Encontró una INTERACCIÓN (Well, Cooler, Seal)
//     1. Llama LimpiarPantalla()
//     2. Imprime: "You found a [Well / Cooler / Pentagram]!"
//     3. Imprime: "Press 'a' to continue..."
//     4. Espera 'a' con _getch()
//     5. En el mapa, reemplazá el '?' por el char de la interacción:
//        Well -> 'W',  Cooler -> 'C',  Seal -> 'G'  (usá 'G' para pentagrama/seal)
//     6. El jugador VUELVE a la posición guardada en PASO 1
//        (NO se mueve a donde estaba el '?')
//     7. Llama mostrarMapa()

// ─────────────────────────────────────────
// SECCIÓN 2 — INTERACTUAR CON W, C, G (Well, Cooler, Pentagrama)
// ─────────────────────────────────────────

// Cuando el jugador camina sobre 'W', 'C' o 'G', hacé lo siguiente:
//   1. Guardá el mapa y la posición del jugador (igual que en PASO 1)
//   2. Llama LimpiarPantalla()
//   3. Imprime: "Select an object to use here:"
//   4. Abrí ../data/inventario.txt con ifstream y mostrá cada línea (cada objeto)
//   5. Esperá que el jugador escriba el nombre de un objeto y presione Enter (usá getline o cin)
//   6. Verificá si ese objeto es válido para esa interacción:
//
//      'W' (Well):
//        - Si el jugador usa "Coin" -> eliminar Coin del inventario, agregar "KeyMold"
//          Mostrar: "You dropped the coin in the well. You received a KeyMold!"
//
//      'C' (Cooler):
//        - Si el jugador tiene "KeyMold" Y "LiquidMercury" en inventario
//          y escribe ambos -> eliminarlos, agregar "MetalKey"
//          Mostrar: "You used the KeyMold and LiquidMercury. You received a MetalKey!"
//        - Nota: para esta interacción pedile al jugador que escriba los dos objetos
//          separados por espacio (ej: "KeyMold LiquidMercury")
//
//      'G' (Pentagrama/Seal):
//        - Si el jugador usa "HolyCross" -> eliminar HolyCross, agregar "HolyBible"
//          Mostrar: "You placed the cross on the seal. You received the HolyBible!"
//
//   7. Si el objeto no es válido: imprimí "Nothing happened." y volvé al mapa
//   8. En cualquier caso: esperá 'a', limpiar pantalla, mostrar mapa con posición guardada

// ─────────────────────────────────────────
// SECCIÓN 3 — SISTEMA DE COMBINACIÓN (tecla 'i' en el mapa)
// ─────────────────────────────────────────

// Cuando el jugador presiona 'i' mientras está en el mapa:
//   1. Llama LimpiarPantalla()
//   2. Imprime: "What do you want to combine?"
//   3. Mostrá el inventario (leé ../data/inventario.txt línea por línea)
//   4. Pedí input: el jugador escribe DOS nombres separados por espacio
//      Ej: "KeyMold LiquidMercury"
//   5. Verificá si esa combinación es válida. Las combinaciones posibles son:
//      (Por ahora solo hay una, pero hacé el sistema extensible con if/else if)
//      - "KeyMold" + "LiquidMercury" -> resultado: "MetalKey"
//        (Nota: esta combinación igual necesita la Cooler para funcionar,
//         decidí vos si la combinación sola alcanza o si es solo via Cooler)
//   6. Si es válida:
//      - Eliminá ambos objetos del inventario (leé todas las líneas, salteá las que coincidan,
//        reescribí el archivo sin ellas)
//      - Agregá el nuevo objeto con ofstream en modo append
//      - Mostrá: "You combined [obj1] and [obj2]. You received [resultado]!"
//   7. Si no es válida: mostrá "These items cannot be combined."
//   8. Esperá 'a', limpiar pantalla, volvé al mapa con la posición guardada

// ─────────────────────────────────────────
// SECCIÓN 4 — ABRIR IMÁGENES (función AbrirImagen ya existe, solo modificala)
// ─────────────────────────────────────────

// La función AbrirImagen() ya está definida abajo. Modificala para que reciba
// un string con el nombre de la imagen como parámetro:
//   void AbrirImagen(std::string nombreImagen)
//
// Y que abra ../data/3D/[nombreImagen].png
//
// Llamala así cuando corresponda:
//   - Si encontró "KeyCard"     -> AbrirImagen("keycard")
//   - Si encontró "Well"        -> AbrirImagen("well")
//   - Si encontró "Coin"        -> AbrirImagen("coin")
//   - Si encontró "ShotGun"     -> AbrirImagen("shotgun")
//   - etc. (ponele el nombre que le hayas dado al archivo .png)
// Los objetos que NO tienen imagen propia (KeyMold, MetalKey, HolyBible)
// son porque se obtienen a través de interacciones, no de '?', así que no necesitan imagen.

// ─────────────────────────────────────────
// NOTAS FINALES
// ─────────────────────────────────────────
// - Si el jugador NO está en el mapa (ej: está en una pantalla de evento),
//   ignorá completamente las teclas WASD. Usá una variable bool enMapa = true/false
//   y solo procesá movimiento si enMapa == true.
// - Para eliminar objetos del inventario: leé todas las líneas del .txt a un vector<string>,
//   usá un for para saltear la línea que querés borrar, y reescribí el archivo completo.
// - Cualquier duda preguntame — Tomás.



#include "funciones.h"

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
    {6, '5', "../data/Cuartos/Cuarto5.txt",  1,  4, 5},
    {6, '3', "../data/Cuartos/Cuarto3.txt", 10, 11, 3},
};

int totalConexiones = 15;

// ─────────────────────────────────────────


void LimpiarPantalla() {

#ifdef _WIN32
    system("cls");
#else
    std::cout << "\033[2J\033[H";
#endif

}

void AbrirImagen(){

    #if defined(_WIN32) || defined(_WIN64)

        system("start ../data/3D/imagen.png");

    #elif defined(__linux__)

        system("xdg-open ../data/3D/imagen.png");

    #elif defined(__APPLE__) || defined(__MACH__)

        system("open ../data/3D/imagen.png");

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

                // borra jugador del mapa actual
                mapa[fila][columna] = '.';

                std::string archivoActual = "../data/Cuartos/Cuarto" + std::to_string(habitacion) + ".txt";
                guardarMapa(archivoActual, mapa);

                // carga nuevo cuarto
                cargarMapa(conexiones[i].archivoDestino, mapa);

                // actualiza posicion y habitacion
                fila       = conexiones[i].nuevaFila;
                columna    = conexiones[i].nuevaColumna;
                habitacion = conexiones[i].habitacionDestino;

                // pone jugador en nueva posicion
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