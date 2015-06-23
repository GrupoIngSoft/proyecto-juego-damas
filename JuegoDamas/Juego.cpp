#include <iostream>
#include <cstdlib>
#include "Juego.h"

using namespace std;

bool salto=false;

Juego::Juego(){
       
    /*
    for(int i = 0; i < 10; i++) {
		for(int j = 0; j < 10; j++) {
			tablero[i][j] = '-';
		}
	}
    */  
}


bool Juego::chequearMovimiento(Jugador jugador, Movimiento mv){ 
   
    //Chequea si el movimiento sin salto es legal.
    
        //chequea si un peon retrocede.
            if (tablero[mv.f1][mv.c1] != iaDama && tablero[mv.f1][mv.c1] != humanoDama)
            {
            if ((jugador == IA && mv.f2 < mv.f1) || (jugador == HUMANO && mv.f2 > mv.f1)){salto = false; return false;}
            }
    
        //chequea si la casilla futura está ocupada.
            if (tablero[mv.f2][mv.c2] != ' '){salto = false; return false;}
    
        //chequea si el peón a mover es vacio.
            if (tablero[mv.f1][mv.c1] == ' '){salto = false; return false;}
    
        //chequea si la pieza se está moviendo vertical u horizontalmente.
            if (mv.c1 == mv.c2 || mv.f1 == mv.f2){salto = false; return false;}
    
        //chequea si el peón se mueve en más de una casilla.
            if ((mv.c2 > mv.c1 + 1 || mv.c2 < mv.c1 - 1) && (mv.f2 == mv.f1 +1 || mv.f2 == mv.f1 - 1)) {salto = false; return false;}
    
    //chequea si el peón esta saltando.
        if (mv.f2 > mv.f1 + 1 || mv.f2 < mv.f1 - 1){
            
            char dama, peon;
            if(jugador == IA){ dama = iaDama; peon = ia;}else{ dama = humanoDama; peon = humano;}
        
        //chequea si el peón esta saltando muy lejos.
            if (mv.f2 > mv.f1 + 2 || mv.f2 < mv.f1 - 2){salto = false; return false;}
        
        //chequea si el peón se esta moviendo más allá de dos columnas.
            if (mv.c2 != mv.c1 + 2 && mv.c2 != mv.c1 - 2){salto = false; return false;}
        
        //chequea si el peón se está moviendo sobre otra pieza.
            if (mv.f2 > mv.f1 && mv.c2 > mv.c1)
            {if (tablero[mv.f2 - 1][mv.c2 - 1] == ' '){salto = false; return false;}}

            else if (mv.f2 > mv.f1 && mv.c2 < mv.c1)
            {if (tablero[mv.f2 - 1][mv.c2 + 1] == ' '){salto = false; return false;}}

            else if (mv.f2 < mv.f1 && mv.c2 > mv.c1)
            {if (tablero[mv.f2 + 1][mv.c2 - 1] == ' '){salto = false; return false;}}

            else if (mv.f2 < mv.f1 && mv.c2 < mv.c1)
            {if (tablero[mv.f2 + 1][mv.c2 + 1] == ' '){salto = false; return false;}}
        
        //Chequear si salta a uno de sus compañeros.
            if (mv.f2 > mv.f1 && mv.c2 > mv.c1)
            {if ((tablero[mv.f2 - 1][mv.c2 - 1] == dama) || (tablero[mv.f2 - 1][mv.c2 - 1] == peon)){salto = false; return false;}}

            else if (mv.f2 > mv.f1 && mv.c2 < mv.c1)
            {if ((tablero[mv.f2 - 1][mv.c2 + 1] == dama) || (tablero[mv.f2 - 1][mv.c2 + 1] == peon)){salto = false; return false;}}
        
            else if (mv.f2 < mv.f1 && mv.c2 > mv.c1)
            {if ((tablero[mv.f2 + 1][mv.c2 - 1] == dama) || (tablero[mv.f2 + 1][mv.c2 - 1] == peon)){salto = false; return false;}}
         
            else if (mv.f2 < mv.f1 && mv.c2 < mv.c1)
            {if ((tablero[mv.f2 + 1][mv.c2 + 1] == dama) || (tablero[mv.f2 + 1][mv.c2 + 1] == peon)){salto = false; return false;}}
        
        //Si rompe las reglas, entonces el salto es legal.   
        salto = true; return true;
    // Si no cumple las reglas, entonces el salto es ilegal, pero el movimiento legal.    
    }else salto = false; return true;
}

void Juego::mover(Movimiento mv)
{
       tablero[mv.f2][mv.c2] = tablero[mv.f1][mv.c1];
       tablero[mv.f1][mv.c1] = ' ';
    
       if (salto == true){saltar(mv);}

}

void Juego::humanoMueve() {
    
    Movimiento mv;
    bool sw = false;
    
    while(sw==false){

    cout << "Mover pieza\n";
    cout << "Fila: ";
    cin >> mv.f1;
    cout << "Columna: ";
    cin >> mv.c1;
        // Chequea si el usuario se equivoca al ingresar el movimiento.
        while (mv.f1 < 0 || mv.f1 > 9 || mv.c1 < 0 || mv.c1 > 9){ 
        cout << "Ingresar numeros entre 0 y 9.\n";
        cout << "Mover pieza:\n";
        cout << "Fila: ";
        cin >> mv.f1;
        cout << "Columna: ";
        cin >> mv.c1;
        }
    
    cout << "A la casilla:\n";
    cout << "Fila: ";
    cin >> mv.f2;
    cout << "Columna: ";
    cin >> mv.c2;
    
        while (mv.f2 < 0 || mv.f2 > 9 || mv.c2 < 0 || mv.c2 > 9){
        cout << "Ingresar numeros entre 0 y 9.\n";
        cout << "A la casilla\n";
        cout << "Fila: ";
        cin >> mv.f2;
        cout << "Columna: ";
        cin >> mv.c2;
        }
    
        sw = chequearMovimiento(HUMANO, mv);

        if(sw==false){ cout<<"Movimiento ilegal. Por favor intente otra vez.\n";
        }else{ mover(mv); }
                        
    }
       
}

void Juego::jugar(){
    
	int turno = 0;
        
	imprimirTablero();
        
	while(!chequearGanador(HUMANO) && !chequearGanador(IA)) {
		
		if(turno % 2 == 0) {
			humanoMueve();
			if(chequearGanador(HUMANO)) cout << "El humano ha ganado!" << endl;
			turno++;
			imprimirTablero();
		} else {
			cout << endl << "Movimiento del computador:" << endl;
			//Movimiento hecho por la IA. Estamos trabajando para usted...
			if(chequearGanador(IA)) cout << "La maquina ha ganado!" << endl;
			turno++;
			imprimirTablero();
		}
	}
}

void Juego::saltar(Movimiento mv){
    //remueve la pieza despues del salto.
    if (mv.f2 > mv.f1 && mv.c2 > mv.c1)
    {
        tablero[mv.f2 - 1][mv.c2 - 1] = ' ';
    }
    else if (mv.f2 > mv.f1 && mv.c2 < mv.c1)
    {
        tablero[mv.f2 - 1][mv.c2 + 1] = ' ';
    }
    else if (mv.f2 < mv.f1 && mv.c2 > mv.c1)
    {
        tablero[mv.f2 + 1][mv.c2 - 1] = ' ';
    }
    else if (mv.f2 < mv.f1 && mv.c2 < mv.c1)
    {
        tablero[mv.f2 + 1][mv.c2 + 1] = ' ';
    }
}

bool Juego::chequearGanador(Jugador){
    
    //Estamos trabajando para usted...
}

void Juego::imprimirTablero(){
    
    	cout << "    0     1     2     3     4     5     6     7     8     9  \n";
	cout << " ------------------------------------------------------------";
        for(int i = 0; i < 10; i++) {
		cout << '\n' << i << "|";
		for(int j = 0; j < 10; j++) {
			cout << "  " << tablero[i][j] << " " << " |";
		}
	}
	cout << '\n' << " ------------------------------------------------------------" << '\n';

}

bool Juego::juegoTerminado(){
    //Estamos trabajando para usted...
}


