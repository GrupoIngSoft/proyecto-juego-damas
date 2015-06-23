/* 
 * File:   Juego.h
 * Author: cesar
 *
 * Created on 21 de junio de 2015, 15:53
 */

#include <iostream>
#include <cstdlib>
using namespace std;

const char humano = 'b';
const char ia = 'n';
const char humanoDama = 'B';
const char iaDama = 'N';

enum Jugador{
    HUMANO,IA
};

struct Movimiento{
    int f1;
    int f2;
    int c1;
    int c2;
};

class Juego{
    
    //char tablero[10][10];
        
    char tablero[10][10] =
    {
        {' ','n',' ','n',' ','n',' ','n',' ','n'},
        {'n',' ','n',' ','n',' ','n',' ','n',' '},
        {' ','n',' ','n',' ','n',' ','n',' ','n'},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {'b',' ','b',' ','b',' ','b',' ','b',' '},
        {' ','b',' ','b',' ','b',' ','b',' ','b'},
        {'b',' ','b',' ','b',' ','b',' ','b',' '},
    };
    
public:
    
    Juego();
    void imprimirTablero();
    void humanoMueve();
    bool chequearGanador(Jugador);
    bool chequearMovimiento();
    void mover(Movimiento);
    void saltar();
    bool juegoTerminado();
    void jugar();
    
};

#ifndef JUEGO_H
#define	JUEGO_H



#endif	/* JUEGO_H */

