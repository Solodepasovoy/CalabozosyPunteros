#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <thread>
#include <chrono>
#include <atomic>
#include <cstdlib>

extern int VidaJugador;
extern int ObjetosRequeridosPuerta;
void LimpiarPantalla();
void Cinematicas();
void CargarCinematica(const std::string& archivo, char arr[100][100]);
void MostrarCinematica(char arr[100][100]);
void cargarMapa(const std::string& archivo, char mapa[12][23]);
void guardarMapa(const std::string& archivo, char mapa[12][23]);
void mostrarMapa(char mapa[12][23]);
bool VerificarObjetoEnInventario(const char* objeto);
void eliminarDeInventario(const char* objeto);
void mostrarInventarioEnPantalla();
void eliminarInventario();
void AbrirImagen(std::string archivo);
void movimiento();
void ResetearCuartos();
void PonerPausa(char mapa[12][23], int habitacion);
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
void generarEvento(char mapa[12][23], int& habitacion, int& fila, int& columna, int nuevafila, int nuevacolumna);
void interactuarConW(char mapa[12][23], int& habitacion, int& fila, int& columna, int nuevafila, int nuevacolumna);
void interactuarConC(char mapa[12][23], int& habitacion, int& fila, int& columna, int nuevafila, int nuevacolumna);
void interactuarConS(char mapa[12][23], int& habitacion, int& fila, int& columna, int nuevafila, int nuevacolumna);
void interactuarConD(char mapa[12][23], int& habitacion, int& fila, int& columna, int nuevafila, int nuevacolumna);