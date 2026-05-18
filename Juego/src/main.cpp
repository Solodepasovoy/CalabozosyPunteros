#include "funciones.h"

int main() {
    srand(time(0));
    VidaJugador = 100;
    ResetearCuartos();
    eliminarInventario();
    Cinematicas();
    movimiento();
    return 0;
}