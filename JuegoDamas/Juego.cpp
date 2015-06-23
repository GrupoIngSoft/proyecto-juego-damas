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


bool Juego::chequearMovimiento(){ 
    
    // Aqui van todas las raglas de damas.
    // Estamos trabajando para usted...
    return true; 
}

void Juego::mover(Movimiento mv)
{
       tablero[mv.f2][mv.c2] = tablero[mv.f1][mv.c1];
       tablero[mv.f1][mv.c1] = ' ';
    
       if (salto == true){saltar();}

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
    
        while (mv.f1 < 0 || mv.f1 > 9 || mv.c1 < 0 || mv.c1 > 9){ //error del usuario al ingresar los parametros
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
    
        sw = chequearMovimiento();

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
			//Movimiento IAmueve = minimax(tablero);
			//tablero[AImueve.x][AImueve.y] = ia;
			if(chequearGanador(IA)) cout << "La maquina ha ganado!" << endl;
			turno++;
			imprimirTablero();
		}
	}
}

void Juego::saltar(){
    //Estamos trabajando para usted...
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


