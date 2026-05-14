#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <thread>
#include <chrono>
#include <vector>

void LimpiarPantalla();
void Cinematicas();
void cargarMapa(const std::string& archivo, char mapa[12][23]);
void mostrarMapa(char mapa[12][23]);
void movimiento();
void guardarMapa(const std::string& archivo, char mapa[12][23]);
void ResetearCuartos();
void PonerPausa(char mapa[12][23], int habitacion, int fila, int columna);
void Correr(int vida);
void Monstruo(int vidaP);
void Fight();
void Flee();
