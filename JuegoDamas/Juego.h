/* 
 * File:   Juego.h
 * Author: cesar
 *
 * Created on 21 de junio de 2015, 15:53
 */

#include <iostream>
#include <cstdlib>
using namespace std;

const char humanoPeon = 'b';
const char iaPeon = 'n';
const char humanoDama = 'B';
const char iaDama = 'N';

enum Jugador{
    HUMANO,IA
};

struct Movimiento{
    int f1;//fila de origen.
    int f2;//fila de destino.
    int c1;//columna de origen.
    int c2;//columna de destino.
    int p; //guarda puntaje de la jugada en la funcion minimax.
};

class Juego{
    
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
    
    /*
    char tablero[10][10] =
    {
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ','n',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ','b',' ','b',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ','b',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    };
    */
public:
    
    Juego();
    void imprimirTablero(char tablero[10][10]);//
    void humanoMueve();//
    bool chequearGanador(Jugador, char tablero[10][10]);//
    bool chequearMovimiento(Jugador, Movimiento, char tablero[10][10]);//
    void mover(Movimiento, char tablero[10][10]);//
    void multisalto(Movimiento, char tablero[10][10]);//
    void sopladita(Movimiento,char tablero[10][10]);//
    int puntaje(Jugador,Movimiento,char tablero[10][10]);//
    bool profundidad(int pro);
    Movimiento minimax(char tablero[10][10]);//
    int min(char tablero[10][10],Movimiento mv, int pro);//
    int max(char tablero[10][10],Movimiento mv, int pro);//
    void jugar();//
    
};

#ifndef JUEGO_H
#define	JUEGO_H



#endif	/* JUEGO_H */

