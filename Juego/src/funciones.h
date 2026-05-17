#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <thread>
#include <chrono>
#include <vector>
#include <atomic>
#include <cstdlib>

void LimpiarPantalla();
void Cinematicas();
void cargarMapa(const std::string& archivo, char mapa[12][23]);
void guardarMapa(const std::string& archivo, char mapa[12][23]);
void mostrarMapa(char mapa[12][23]);
void AbrirImagen(std::string archivo);
void movimiento();
void ResetearCuartos();
void PonerPausa(char mapa[12][23], int habitacion, int fila, int columna);
void Monstruo(char mapa[12][23], int& habitacion, int& fila, int& columna);
void Correr(char mapa[12][23], int& habitacion, int& fila, int& columna);
void Fight(char mapa[12][23], int& habitacion, int& fila, int& columna, int& vidaenemigo, int maximosflashes);
void Flee(char mapa[12][23], int& habitacion, int& fila, int& columna);
void Rendirse(char mapa[12][23], int& habitacion, int& fila, int& columna);
void Suerte(char mapa[12][23], int& habitacion, int& fila, int& columna);
void Morir();
void Ataque();
void JugadorCara();
void CorrerASCI(int num);
void SinVer(int vidaJugador, int vidaenemigo, int flashes);
void PelearImagenC();
void PelearImagenenB();
void PelearImagenenA();
void Susto();
void reproducir(const std::string& archivo);
void parar_todos();
void Boss();
void ElegirFase();
bool Fase1();
bool Fase2();
bool Fase3();
void ControlSonidoPorFase(int fase);
void FinalMalo();
void QuitarVidaBoss();
void FinalBueno();