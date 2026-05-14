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
void AbrirImagen(std::string archivo);
void movimiento();
void guardarMapa(const std::string& archivo, char mapa[12][23]);
void ResetearCuartos();
void PonerPausa(char mapa[12][23], int habitacion, int fila, int columna);
void Correr(char mapa[12][23], int& habitacion, int& fila, int& columna);
void Monstruo(char mapa[12][23], int& habitacion, int& fila, int& columna);
void Fight();
void Flee(char mapa[12][23], int& habitacion, int& fila, int& columna);
void JugadorCara();
void CorrerASCI();
void Rendirse(char mapa[12][23], int& habitacion, int& fila, int& columna);
void Morir();
void Suerte(char mapa[12][23], int& habitacion, int& fila, int& columna);
