#include <iostream>
#include <cstdlib>
#include <math.h>
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

char dama, peon;
if(jugador == IA){ dama = iaDama; peon = ia;}else{ dama = humanoDama; peon = humano;}
    
//Retorna falso si la casilla futura está ocupada.
if (tablero[mv.f2][mv.c2] != ' '){return false;}
    
//Retorna falso si el peón a mover es vacio.
if (tablero[mv.f1][mv.c1] == ' '){return false;}
    
//Retorna falso si la pieza se está moviendo vertical u horizontalmente.
if (mv.c1 == mv.c2 || mv.f1 == mv.f2){return false;}
    
//Chequea si el movimiento sin salto es legal.
    
    //Reglas para peones
    if (tablero[mv.f1][mv.c1] == peon){
            
        //Retorna falso si un peon retrocede.    
        if ((jugador == IA && mv.f2 < mv.f1) || (jugador == HUMANO && mv.f2 > mv.f1)){return false;}
            
        //Retorna verdadero si se mueve solo una casilla.
        if((mv.f2 == mv.f1 + 1 || mv.f2 == mv.f1 - 1)&&(mv.c2 == mv.c1 + 1 || mv.c2 == mv.c1 - 1)){return true;}
        
        else{//Reglas para saltos con peones.           
        
            //Retorna falso si el peón no se esta moviendo exactamente dos filas.
            //(solo necesita que se cumpla una igualdad para NO retornar falso)
            if (mv.f2 != mv.f1 + 2 && mv.f2 != mv.f1 - 2){return false;}
        
            //Retorna falso si el peón no se esta moviendo exactamente dos columnas.
            //(solo necesita que se cumpla una igualdad para NO retornar falso)
            if (mv.c2 != mv.c1 + 2 && mv.c2 != mv.c1 - 2){return false;}
        
            //Retorna falso si intenta saltar sin haber una pieza que se este saltando.
            if (mv.f2 > mv.f1 && mv.c2 > mv.c1)
            {if (tablero[mv.f2 - 1][mv.c2 - 1] == ' '){return false;}}

            else if (mv.f2 > mv.f1 && mv.c2 < mv.c1)
            {if (tablero[mv.f2 - 1][mv.c2 + 1] == ' '){return false;}}

            else if (mv.f2 < mv.f1 && mv.c2 > mv.c1)
            {if (tablero[mv.f2 + 1][mv.c2 - 1] == ' '){return false;}}

            else if (mv.f2 < mv.f1 && mv.c2 < mv.c1)
            {if (tablero[mv.f2 + 1][mv.c2 + 1] == ' '){return false;}}
        
            //Retorna falso si salta a uno de sus compañeros.
            if (mv.f2 > mv.f1 && mv.c2 > mv.c1)
            {if ((tablero[mv.f2 - 1][mv.c2 - 1] == dama) || (tablero[mv.f2 - 1][mv.c2 - 1] == peon)){return false;}}

            else if (mv.f2 > mv.f1 && mv.c2 < mv.c1)
            {if ((tablero[mv.f2 - 1][mv.c2 + 1] == dama) || (tablero[mv.f2 - 1][mv.c2 + 1] == peon)){return false;}}
        
            else if (mv.f2 < mv.f1 && mv.c2 > mv.c1)
            {if ((tablero[mv.f2 + 1][mv.c2 - 1] == dama) || (tablero[mv.f2 + 1][mv.c2 - 1] == peon)){return false;}}
         
            else if (mv.f2 < mv.f1 && mv.c2 < mv.c1)
            {if ((tablero[mv.f2 + 1][mv.c2 + 1] == dama) || (tablero[mv.f2 + 1][mv.c2 + 1] == peon)){return false;}}
        
            //Si no rompe las reglas, entonces el salto es legal.   
            salto = true; return true;
            }
        }
        
    //Reglas para damas
    if (tablero[mv.f1][mv.c1] == dama){
        
        int piezas = 0;//Numero de piezas en la diagonal.        
        
        //Retorna falso si no se mueve en una diagonal perfecta.
        if(abs(mv.f1 - mv.f2) != abs(mv.c1 - mv.c2)){return false;}        
        
        //Retorna verdadero si solo me muevo una casilla.
        if((abs(mv.f1 - mv.f2) == 1 && abs(mv.c1 - mv.c2) == 1)){return true;}        
        
        //Retorna falso si salta a uno de sus compañeros.
        if((tablero[mv.f2 - 1][mv.c2 - 1] == dama) || (tablero[mv.f2 - 1][mv.c2 - 1] == peon)){ return false;}   
        
        //Analiza el tipo de movimiento en el caso de dirigirse a la esquina inferior derecha.
        if(mv.f2 > mv.f1 && mv.c2 > mv.c1){
            
            int j = mv.c1 + 1;
           
            for(int i = mv.f1 + 1; i < mv.f2; i++) {
                
                if(tablero[i][j] != ' '){piezas++;}
                j++;
            }           
            //Retorna verdadero si es un movimiento sin salto.
            if(piezas == 0){return true;}
            
            //Retorna falso si no salta por una posicion a su enemigo.
            else if(tablero[mv.f2 - 1][mv.c2 - 1] == ' '){ return false;}
            
            //retorna falso si salta a mas de un enemigo.
            if(piezas > 1){return false;}
        }     
        
        //Analiza el tipo de movimiento en el caso de dirigirse a la esquina inferior izquierda.
        if(mv.f2 > mv.f1 && mv.c2 < mv.c1){
            
            int j = mv.c1 - 1;
           
            for(int i = mv.f1 + 1; i < mv.f2; i++) {
                
                if(tablero[i][j] != ' '){piezas++;}
                j--;
            }           
            //Retorna verdadero si es un movimiento sin salto.
            if(piezas == 0){return true;}
            
            //Retorna falso si no salta por una posicion a su enemigo.
            else if(tablero[mv.f2 - 1][mv.c2 + 1] == ' '){ return false;}
            
            //retorna falso si salta a mas de un enemigo.
            if(piezas > 1){return false;}
        }
        
        //Analiza el tipo de movimiento en el caso de dirigirse a la esquina superior derecha.
        if(mv.f2 < mv.f1 && mv.c2 > mv.c1){
            
            int j = mv.c1 + 1;
           
            for(int i = mv.f1 - 1; i < mv.f2; i--) {
                
                if(tablero[i][j] != ' '){piezas++;}
                j++;
            }           
            //Retorna verdadero si es un movimiento sin salto.
            if(piezas == 0){return true;}
            
            //Retorna falso si no salta por una posicion a su enemigo.
            else if(tablero[mv.f2 + 1][mv.c2 - 1] == ' '){ return false;}
            
            //retorna falso si salta a mas de un enemigo.
            if(piezas > 1){return false;}
        }
        
        //Analiza el tipo de movimiento en el caso de dirigirse a la esquina superior izquierda.
        if(mv.f2 < mv.f1 && mv.c2 < mv.c1){
            
            int j = mv.c1 - 1;
           
            for(int i = mv.f1 - 1; i < mv.f2; i--) {
                
                if(tablero[i][j] != ' '){piezas++;}
                j--;
            }           
            //Retorna verdadero si es un movimiento sin salto.
            if(piezas == 0){return true;}
            
            //Retorna falso si no salta por una posicion a su enemigo.
            else if(tablero[mv.f2 - 1][mv.c2 - 1] == ' '){ return false;}
            
            //retorna falso si salta a mas de un enemigo.
            if(piezas > 1){return false;}
        }
        
        //Si no rompe las reglas, el salto es legal.
        salto = true; return true;        
    }
}

void Juego::mover(Movimiento mv){
    
    if(salto == true){
        //remueve la pieza despues del salto.
    
        if (mv.f2 > mv.f1 && mv.c2 > mv.c1){ tablero[mv.f2 - 1][mv.c2 - 1] = ' ';
        }
        else if (mv.f2 > mv.f1 && mv.c2 < mv.c1){ tablero[mv.f2 - 1][mv.c2 + 1] = ' ';
        }
        else if (mv.f2 < mv.f1 && mv.c2 > mv.c1){ tablero[mv.f2 + 1][mv.c2 - 1] = ' ';
        }
        else if (mv.f2 < mv.f1 && mv.c2 < mv.c1){ tablero[mv.f2 + 1][mv.c2 + 1] = ' ';
        }
        salto = false;
    }
    
    // Borra la pieza en la posicion inicial y la escribe en la nueva posicion. 
    tablero[mv.f2][mv.c2] = tablero[mv.f1][mv.c1];
    tablero[mv.f1][mv.c1] = ' ';
       
    //Si un peon llega al otro extremo, se escribe una dama.
    for (int i = 0; i < 8; i++){
            
        if (tablero[0][i] == humano){ tablero[0][i] = humanoDama;}
        
        if (tablero[9][i] == ia){ tablero[9][i] = iaDama;}
    }
    
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

bool Juego::chequearGanador(Jugador){
    
    return false;
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


