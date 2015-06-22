/* 
 * File:   Juego.h
 * Author: cesar
 *
 * Created on 21 de junio de 2015, 15:53
 */

#include <iostream>
#include <cstdlib>
using namespace std;

enum Jugador{
    Humano,IA
};

struct move{
    int x;
    int y;
};

class Juego{
    
    char tablero[10][10];
    
public:
    
    Juego();
    void imprimirTablero();
    bool chequearGanador(Jugador);
    bool juegoTerminado();
    void jugar();
    
    
};

#ifndef JUEGO_H
#define	JUEGO_H



#endif	/* JUEGO_H */

