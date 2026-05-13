#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <thread>
#include <chrono>

void LimpiarPantalla();
void cargarMapa(const std::string& archivo, char mapa[12][23]);
void mostrarMapa(char mapa[12][23]);
void movimiento();