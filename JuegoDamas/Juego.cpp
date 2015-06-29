#include <iostream>
#include <cstdlib>
#include <math.h>
#include "Juego.h"
#include <string.h>

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
//No le permite al jugador mover una pieza contraria.
if(jugador == IA){ dama = iaDama; peon = iaPeon;}else if(jugador == HUMANO){ dama = humanoDama; peon = humanoPeon;}
    
//Retorna falso si la casilla destino está ocupada.
if (tablero[mv.f2][mv.c2] != ' '){cout<<"La casilla destino está ocupada.\n";return false;}
    
//Retorna falso si la pieza a mover es vacio.
if (tablero[mv.f1][mv.c1] == ' '){cout<<"La pieza a mover no existe\n";return false;}
    
//Retorna falso si la pieza se está moviendo vertical u horizontalmente.
if (mv.c1 == mv.c2 || mv.f1 == mv.f2){cout<<"No puede mover las piezas ni vertical ni horizontalmente\n";return false;}
 
    //Reglas para peones
    if (tablero[mv.f1][mv.c1] == peon){
            
        //Retorna falso si un peon retrocede.    
        if ((jugador == IA && mv.f2 < mv.f1) || (jugador == HUMANO && mv.f2 > mv.f1)){cout<<"No puedes retroceder\n";return false;}
            
        //Retorna verdadero si se mueve solo una casilla.
        if((mv.f2 == mv.f1 + 1 || mv.f2 == mv.f1 - 1)&&(mv.c2 == mv.c1 + 1 || mv.c2 == mv.c1 - 1)){return true;}
        
        else{//Reglas para saltos con peones.           
        
            //Retorna falso si el peón no se esta moviendo exactamente dos filas.
            //(solo necesita que se cumpla una igualdad para NO retornar falso)
            if (mv.f2 != mv.f1 + 2 && mv.f2 != mv.f1 - 2){cout<<"No puedes moverte mas de dos filas \n";return false;}
        
            //Retorna falso si el peón no se esta moviendo exactamente dos columnas.
            //(solo necesita que se cumpla una igualdad para NO retornar falso)
            if (mv.c2 != mv.c1 + 2 && mv.c2 != mv.c1 - 2){cout<<"No puedes moverte mas de dos columnas\n";return false;}
        
            //Retorna falso si intenta saltar sin haber una pieza que se este saltando.
            if (mv.f2 > mv.f1 && mv.c2 > mv.c1)
            {if (tablero[mv.f2 - 1][mv.c2 - 1] == ' '){cout<<"No puedes moverte mas de una casillas sin saltar\n";return false;}}

            else if (mv.f2 > mv.f1 && mv.c2 < mv.c1)
            {if (tablero[mv.f2 - 1][mv.c2 + 1] == ' '){cout<<"No puedes moverte mas de una casillas sin saltar\n";return false;}}

            else if (mv.f2 < mv.f1 && mv.c2 > mv.c1)
            {if (tablero[mv.f2 + 1][mv.c2 - 1] == ' '){cout<<"No puedes moverte mas de una casillas sin saltar\n";return false;}}

            else if (mv.f2 < mv.f1 && mv.c2 < mv.c1)
            {if (tablero[mv.f2 + 1][mv.c2 + 1] == ' '){cout<<"No puedes moverte mas de una casillas sin saltar\n";return false;}}
        
            //Retorna falso si salta a uno de sus compañeros.
            if (mv.f2 > mv.f1 && mv.c2 > mv.c1)
            {if ((tablero[mv.f2 - 1][mv.c2 - 1] == dama) || (tablero[mv.f2 - 1][mv.c2 - 1] == peon)){cout<<"No puedes saltar a un compañero\n";return false;}}

            else if (mv.f2 > mv.f1 && mv.c2 < mv.c1)
            {if ((tablero[mv.f2 - 1][mv.c2 + 1] == dama) || (tablero[mv.f2 - 1][mv.c2 + 1] == peon)){cout<<"No puedes saltar a un compañero\n";return false;}}
        
            else if (mv.f2 < mv.f1 && mv.c2 > mv.c1)
            {if ((tablero[mv.f2 + 1][mv.c2 - 1] == dama) || (tablero[mv.f2 + 1][mv.c2 - 1] == peon)){cout<<"No puedes saltar a un compañero\n";return false;}}
         
            else if (mv.f2 < mv.f1 && mv.c2 < mv.c1)
            {if ((tablero[mv.f2 + 1][mv.c2 + 1] == dama) || (tablero[mv.f2 + 1][mv.c2 + 1] == peon)){cout<<"No puedes saltar a un compañero\n";return false;}}
        
            //Si no rompe las reglas, entonces el salto es legal.   
            salto = true; return true;
            }
        }

        
    //Reglas de saltos para damas
    if (tablero[mv.f1][mv.c1] == dama){
        
        int piezas = 0;//Numero de piezas en la diagonal.        
        
        //Retorna falso si no se mueve en una diagonal perfecta.
        if(abs(mv.f1 - mv.f2) != abs(mv.c1 - mv.c2)){cout<<"Debes moverte sobre una diagonal perfecta\n";return false;}        
        
        //Retorna verdadero si solo me muevo una casilla.
        if((abs(mv.f1 - mv.f2) == 1 && abs(mv.c1 - mv.c2) == 1)){return true;}        
        
        //Analiza el tipo de movimiento en el caso de dirigirse a la esquina inferior derecha.
        if(mv.f2 > mv.f1 && mv.c2 > mv.c1){
            
            int j = mv.c1 + 1;
           
            for(int i = mv.f1 + 1; i < mv.f2; i++) {
                
                if(tablero[i][j] != ' '){
                    //Cuenta el numero de piezas dentro de la diagonal.
                    piezas++;
                    //Retorna falso si salta a un compañero.
                if((tablero[i][j] == dama) || (tablero[i][j] == peon)){cout<<"No puedes saltar a un compañero\n"; return false;}
                
                }j++;
            }           
            //Retorna verdadero si es un movimiento sin salto.
            if(piezas == 0){return true;}
                    
            //retorna falso si salta a mas de un enemigo.
            if(piezas > 1){cout<<"No puedes saltar a más de un enemigo en un salto\n";return false;}
        }else 
        
        //Analiza el tipo de movimiento en el caso de dirigirse a la esquina inferior izquierda.
        if(mv.f2 > mv.f1 && mv.c2 < mv.c1){
            
            int j = mv.c1 - 1;
           
            for(int i = mv.f1 + 1; i < mv.f2; i++) {
                
                if(tablero[i][j] != ' '){
                    //Cuenta el numero de piezas dentro de la diagonal.
                    piezas++;
                    //Retorna falso si salta a un compañero.
                    if((tablero[i][j] == dama) || (tablero[i][j] == peon)){cout<<"No puedes saltar a un compañero\n"; return false;
                    }
                }
                j--;
            }           
            //Retorna verdadero si es un movimiento sin salto.
            if(piezas == 0){return true;}
            
            //retorna falso si salta a mas de un enemigo.
            if(piezas > 1){cout<<"No puedes saltar a más de un enemigo en un salto\n";return false;}
        }else
        
        //Analiza el tipo de movimiento en el caso de dirigirse a la esquina superior derecha.
        if(mv.f2 < mv.f1 && mv.c2 > mv.c1){
            
            int j = mv.c1 + 1;
           
            for(int i = mv.f1 - 1; i > mv.f2; i--) {
                
                if(tablero[i][j] != ' '){
                    //Cuenta el numero de piezas dentro de la diagonal.
                    piezas++;
                    //Retorna falso si salta a un compañero.
                    if((tablero[i][j] == dama) || (tablero[i][j] == peon)){cout<<"No puedes saltar a un compañero\n"; return false;
                    }
                }
                j++;
            }           
            //Retorna verdadero si es un movimiento sin salto.
            if(piezas == 0){return true;}
            
            //retorna falso si salta a mas de un enemigo.
            if(piezas > 1){cout<<"No puedes saltar a más de un enemigo en un salto\n";return false;}
        }else
        
        //Analiza el tipo de movimiento en el caso de dirigirse a la esquina superior izquierda.
        if(mv.f2 < mv.f1 && mv.c2 < mv.c1){
            
            int j = mv.c1 - 1;
           
            for(int i = mv.f1 - 1; i > mv.f2; i--) {
                
                if(tablero[i][j] != ' '){
                    //Cuenta el numero de piezas dentro de la diagonal.
                    piezas++;
                    //Retorna falso si salta a un compañero.
                    if((tablero[i][j] == dama) || (tablero[i][j] == peon)){cout<<"No puedes saltar a un compañero\n"; return false;}
                }j--;
            }           
            //Retorna verdadero si es un movimiento sin salto.
            if(piezas == 0){return true;}
            
            //retorna falso si salta a mas de un enemigo.
            if(piezas > 1){cout<<"No puedes saltar a más de un enemigo en un salto\n";return false;}
        }
    //Si no rompe las reglas, el salto es legal.
    salto = true; return true;        
    }
}

void Juego::mover(Movimiento mv){
    
    if(salto == true){
        
        //Si juego con un peon, remueve la pieza capturada despues del salto.
        if( tablero[mv.f1][mv.c1] == iaPeon || tablero[mv.f1][mv.c1] == humanoPeon){
            
            if (mv.f2 > mv.f1 && mv.c2 > mv.c1){ cout<<"Se capturo la pieza "<<mv.f2 - 1<<" - "<<mv.c2 - 1<<" \n";tablero[mv.f2 - 1][mv.c2 - 1] = ' ';
            }
            else if (mv.f2 > mv.f1 && mv.c2 < mv.c1){ cout<<"Se capturo la pieza "<<mv.f2 - 1<<" - "<<mv.c2 + 1<<" \n"; tablero[mv.f2 - 1][mv.c2 + 1] = ' ';
            }
            else if (mv.f2 < mv.f1 && mv.c2 > mv.c1){cout<<"Se capturo la pieza "<<mv.f2 + 1<<" - "<<mv.c2 - 1<<" \n"; tablero[mv.f2 + 1][mv.c2 - 1] = ' ';
            }
            else if (mv.f2 < mv.f1 && mv.c2 < mv.c1){cout<<"Se capturo la pieza "<<mv.f2 + 1<<" - "<<mv.c2 + 1<<" \n"; tablero[mv.f2 + 1][mv.c2 + 1] = ' ';
            }
        }
        
        //Si juego con una dama, remueve la pieza capturada despues del salto.
        if(tablero[mv.f1][mv.c1] == humanoDama  || tablero[mv.f1][mv.c1] == iaDama) {
            
            if(mv.f2 > mv.f1 && mv.c2 > mv.c1){
                
                int j = mv.c1 + 1;
           
                for(int i = mv.f1 + 1; i < mv.f2; i++) {
                
                    if(tablero[i][j] != ' '){tablero[i][j] = ' ';cout<<"Se capturo la pieza: ( "<<i<<" , "<<j<<" )\n";}
                j++;
                }
                           
            }else
            
            if(mv.f2 > mv.f1 && mv.c2 < mv.c1){
                
                int j = mv.c1 - 1;
           
                for(int i = mv.f1 + 1; i < mv.f2; i++) {
                
                    if(tablero[i][j] != ' '){tablero[i][j] = ' ';cout<<"Se capturo la pieza: ( "<<i<<" , "<<j<<" )\n";}
                j--;
                }
            }else
            
            if(mv.f2 < mv.f1 && mv.c2 < mv.c1){
                
                int j = mv.c1 - 1;
           
                for(int i = mv.f1 - 1; i > mv.f2; i--) {
                
                    if(tablero[i][j] != ' '){tablero[i][j] = ' ';cout<<"Se capturo la pieza: ( "<<i<<" , "<<j<<" )\n";}
                j--;
                }
            }else
                
            if(mv.f2 < mv.f1 && mv.c2 > mv.c1){
                
                int j = mv.c1 + 1;
           
                for(int i = mv.f1 - 1; i > mv.f2; i--) {
                
                    if(tablero[i][j] != ' '){tablero[i][j] = ' ';cout<<"Se capturo la pieza: ( "<<i<<" , "<<j<<" )\n";}
                j++;
                }
            }
        }
    }
    
    // Borra la pieza en la posicion inicial y la escribe en la nueva posicion. 
    tablero[mv.f2][mv.c2] = tablero[mv.f1][mv.c1];
    tablero[mv.f1][mv.c1] = ' ';
    
    
    
    if(salto == false){sopladita(mv);}//Si se realizo un salto, no llamar a la funcion sopladita.
    
    
    
    if(salto == true){multisalto(mv);}//analiza la opcion de multisalto.
    salto = false;
       
    //Si un peon llega al otro extremo, se escribe una dama.
    for (int i = 0; i < 8; i++){
            
        if (tablero[0][i] == humanoPeon){ tablero[0][i] = humanoDama;}
        
        if (tablero[9][i] == iaPeon){ tablero[9][i] = iaDama;}
    }
    
}

void Juego::multisalto(Movimiento mv){
    
    Movimiento izq, der;//Guarda los posibles movimientos para peones.
    Movimiento iizq,ider,sizq,sder;//Guarda los posibles movimientos para famas.
    bool i = false, d = false;//Guarda si hay posibilidad de saltar por derecha y/o izquierda.
    bool ii = false, id = false, si = false,sd = false;//Guarda si hay posibilidad de saltar por cualquiera de las diagonales.
    Movimiento aux;//guarda movimiento ingresado por el usuario.
    char respuesta[10]; 
    
    if(tablero[mv.f2][mv.c2] == humanoPeon ){//Multisalto moviendo un peon.
                   
            der.c1 = mv.c2; der.f1 = mv.f2; der.c2 = der.c1 + 2; der.f2 = der.f1 - 2;
         
                if(chequearMovimiento(HUMANO, der) == true && salto == true){ d = true;}
        
            izq.c1 = mv.c2; izq.f1 = mv.f2; izq.c2 = izq.c1 - 2; izq.f2 = izq.f1 - 2;
         
                if(chequearMovimiento(HUMANO, izq) == true && salto == true){ i = true;}
        
        if(d == true && i == true){ 
            imprimirTablero();//Imprime tablero actualizado.
            cout<<"¿Desea continuar capturando por la 'izquierda' o 'derecha'?\n";       
            cin>>respuesta;
            //No avanza hasta responder una de las dos opciones.
            while( strcmp("izquierda",respuesta) != 0 && strcmp("derecha",respuesta) != 0 ){
            cout<<"¿Desea continuar capturando por la 'izquierda' o 'derecha'?\n";       
            cin>>respuesta;
            }
            if(strcmp("izquierda",respuesta) == 0){mover(izq);}
            if(strcmp("derecha",respuesta) == 0){mover(der);}
        
        }else if(d == true){ mover(der);}
         else if(i == true){ mover(izq);}
    }else
    
    if(tablero[mv.f2][mv.c2] == humanoDama ){//Multisalto moviendo una dama.
        
        //Busca un peon o dama enemiga dentro de la DIAGONAL INFERIOR DERECHA.
        int f, c;            
        f = mv.f2 + 1; c = mv.c2 + 1;//Toma a la casilla siguiente como primera casila a analizar.
                    
        ider.f1 = mv.f2; ider.c1 = mv.c2;//Guarda la pieza como origen del movimiento
                                               
        while(f < 9 && c < 9){//Limita la busqueda hasta la penultima casilla del borde del tablero.
                        
            if((tablero[f][c] == iaPeon) || (tablero[f][c] == iaDama)){//Guarda la casilla siguiente como la casilla destino.
                
                ider.f2 = f + 1; ider.c2 = c + 1; 
                        
                if((chequearMovimiento(HUMANO, ider) == true) && (salto == true)){ id = true;}
            }
        c++;f++;
        }
        
        //Busca un peon o dama enemiga dentro de la DIAGONAL INFERIOR IZQUIERDA.
        
        f = mv.f2 + 1;  c = mv.c2 - 1;//Toma a la casilla siguiente como primera casila a analizar.
        
        iizq.f1 = mv.f2; iizq.c1 = mv.c2;//Guarda la pieza como origen del movimiento
                                               
        while(f < 9 && c > 0){//Limita la busqueda hasta la penultima casilla del borde del tablero.
                        
            if((tablero[f][c] == iaPeon) || (tablero[f][c] == iaDama)){//Guarda la casilla siguiente como la casilla destino.
                
                iizq.f2 = f + 1; iizq.c2 = c - 1; 
                        
                if((chequearMovimiento(HUMANO, iizq) == true) && (salto == true)){ ii = true;}
            }
        c--;f++;
        }
        
        //Busca un peon o dama enemiga dentro de la DIAGONAL SUPERIOR DERECHA.
        
        f = mv.f2 - 1;  c = mv.c2 + 1;//Toma a la casilla siguiente como primera casila a analizar.
        
        sder.f1 = mv.f2; sder.c1 = mv.c2;//Guarda la pieza como origen del movimiento
                                               
        while(f > 0 && c < 9){//Limita la busqueda hasta la penultima casilla del borde del tablero.
                        
            if((tablero[f][c] == iaPeon) || (tablero[f][c] == iaDama)){//Guarda la casilla siguiente como la casilla destino.
                
                sder.f2 = f - 1; sder.c2 = c + 1; 
                        
                if((chequearMovimiento(HUMANO, sder) == true) && (salto == true)){ sd = true;}
            }
        c++;f--;
        }
        
        //Busca un peon o dama enemiga dentro de la DIAGONAL SUPERIOR IZQUIERDA.
        
        f = mv.f2 - 1;  c = mv.c2 - 1;//Toma a la casilla siguiente como primera casila a analizar.
        
        sizq.f1 = mv.f2; sizq.c1 = mv.c2;//Guarda la pieza como origen del movimiento
                                               
        while(f > 0 && c > 0){//Limita la busqueda hasta la penultima casilla del borde del tablero.
                        
            if((tablero[f][c] == iaPeon) || (tablero[f][c] == iaDama)){//Guarda la casilla siguiente como la casilla destino.
                
                sizq.f2 = f - 1; sizq.c2 = c - 1; 
                        
                if((chequearMovimiento(HUMANO, sizq) == true) && (salto == true)){ si = true;}
            }
        c--;f--;
        }
            
        
        if(id == true || ii == true || si == true || sd == true){ 
            
            imprimirTablero();//Imprime tablero actualizado.
            
            bool sw = false;
            
            cout <<"Debe realizar un salto!\n";
            cout << "Mover pieza: ("<<mv.f2 << " , "<<mv.c2 <<" ) \n";
            cout << "A la casilla: \n";
            cout << "Fila: ";
            cin >> aux.f2;
            cout << "Columna: ";
            cin >> aux.c2;
                
            aux.f1 = mv.f2; aux.c1 = mv.c2; //Guarda la posicion actual como origen del siguiente salto solicitado a evaluar.
                
            while(sw == false){
            cout << "aqui!!!";    
                while (aux.f2 < 0 || aux.f2 > 9 || aux.c2 < 0 || aux.c2 > 9){ //Es necesario pedir al usuario en que casilla desea caer despues de unn salto.
            
                cout <<"Debe realizar un salto!\n";
                cout << "Mover pieza: ("<<mv.f2 << " , "<<mv.c2 <<" ) \n";
                cout << "A la casilla: \n";
                cout << "Fila: ";
                cin >> aux.f2;
                cout << "Columna: ";
                cin >> aux.c2;
                }
                               
                if((chequearMovimiento(HUMANO, aux) == true) && (salto == true)){ sw = true;}
            
            }mover(aux);
        }
        
    }
}

void Juego::sopladita(Movimiento mv){
    
    Movimiento aux;
    bool sw = false;//Si ya capturo una dama, no sigue capurando mas.
    bool cap = false;//Si ya capturo una pieza, no sigue capturando mas.
    
    for(int i = 0; i < 10; i++) {//Busca en toda la matriz.
        
        for(int j = 0; j < 10; j++) {
                    
            if(tablero[i][j] == humanoDama){//Analiza solo a las damas.
                    
                if( ((i == mv.f2) && (j == mv.c2)) || (cap == true)){}else{//Analiza a todas las damas excepto la que se movio.
                
                    if(cap == false){//Busca un peon o dama enemiga dentro de la diagonal inferior derecha.
                    
                        int c = j + 1, f = i + 1;//Toma a la casilla siguiente como primera casila a analizar.
                    
                        aux.f1 = i; aux.c1 = j;//Guarda la pieza como origen del movimiento
                                               
                        while(c < 9 && f < 9){//Limita la busqueda hasta la penultima casilla del borde del tablero.
                        
                        if((tablero[f][c] == iaPeon) || (tablero[f][c] == iaDama)){//Guarda la casilla siguiente como la casilla destino.
                            aux.f2 = f + 1; aux.c2 = c + 1; 
                        
                            if((chequearMovimiento(HUMANO, aux) == true) && (salto == true)){ 
                            tablero[i][j] = ' ';cout<<"Se le ha soplado la pieza: ( "<<i<<" , "<<j<<" )\n"; sw = true; cap = true;}
                        }
                        c++;f++;
                        }
                    
                    }
                    
                    if(cap == false){//Busca un peon o dama enemiga dentro de la diagonal inferior izquierda.
                    
                        int c = j - 1, f = i + 1;//Toma a la casilla siguiente como primera casilla a analizar.
                    
                        aux.f1 = i; aux.c1 = j;//Guarda la pieza como origen del movimiento
                                               
                        while(c > 0 && f < 9){//Limita la busqueda hasta la penultima casilla del borde del tablero.
                        
                        if((tablero[f][c] == iaPeon) || (tablero[f][c] == iaDama)){//Guarda la casilla siguiente como la casilla destino.
                            aux.f2 = f + 1; aux.c2 = c - 1; 
                        
                            if((chequearMovimiento(HUMANO, aux) == true) && (salto == true)){ 
                            tablero[i][j] = ' ';cout<<"Se le ha soplado la pieza: ( "<<i<<" , "<<j<<" )\n"; sw = true; cap = true;}
                        }
                        c--;f++;
                        }
                    
                    }
                    
                    if(cap == false){//Busca un peon o dama enemiga dentro de la diagonal superior izquierda.
                    
                        int c = j - 1, f = i - 1;//Toma a la casilla siguiente como primera casilla a analizar.
                    
                        aux.f1 = i; aux.c1 = j;//Guarda la pieza como origen del movimiento
                                               
                        while(c > 0 && f > 0){//Limita la busqueda hasta la penultima casilla del borde del tablero.
                        
                        if((tablero[f][c] == iaPeon) || (tablero[f][c] == iaDama)){//Guarda la casilla siguiente como la casilla destino.
                            aux.f2 = f - 1; aux.c2 = c - 1; 
                        
                            if((chequearMovimiento(HUMANO, aux) == true) && (salto == true)){ 
                            tablero[i][j] = ' ';cout<<"Se le ha soplado la pieza: ( "<<i<<" , "<<j<<" )\n"; sw = true; cap = true;}
                        }
                        c--;f--;
                        }
                    
                    }
                    
                    if(cap == false){//Busca un peon o dama enemiga dentro de la diagonal superior derecha.
                    
                        int c = j + 1, f = i - 1;//Toma a la casilla siguiente como primera casilla a analizar.
                    
                        aux.f1 = i; aux.c1 = j;//Guarda la pieza como origen del movimiento.
                                               
                        while(c < 9 && f > 0){//Limita la busqueda hasta la penultima casilla del borde del tablero.
                        
                        if((tablero[f][c] == iaPeon) || (tablero[f][c] == iaDama)){//Guarda la casilla siguiente como la casilla destino.
                            aux.f2 = f - 1; aux.c2 = c + 1; 
                        
                            if((chequearMovimiento(HUMANO, aux) == true) && (salto == true)){ 
                            tablero[i][j] = ' ';cout<<"Se le ha soplado la pieza: ( "<<i<<" , "<<j<<" )\n"; sw = true; cap = true;}
                        }
                        c++;f--;
                        }
                    
                    }
                    
                }
            }
        }
    }
    if(sw == false){//Busca peones en caso de no haber encontrado damas primeramente.
        
        for(int i = 0; i < 10; i++){//Busca en toda la matriz.
        
        for(int j = 0; j < 10; j++) {
                    
            if(tablero[i][j] == humanoPeon ){//Analiza solo a los peones.
                        
                if( (i == mv.f2) && (j == mv.c2) || (cap == true)){}else{//Analiza a todos los peones excepto al que se movio.
                        
                        aux.c1 = j; aux.f1 = i; aux.c2 = aux.c1 + 2; aux.f2 = aux.f1 - 2;//Analiza si exite posible captura por la derecha.
                    
                        if(chequearMovimiento(HUMANO, aux) == true && salto == true){
                            tablero[i][j] = ' ';cout<<"Se le ha soplado la pieza: ( "<<i<<" , "<<j<<" )\n";cap = true;
                        }else{
                        aux.c1 = j; aux.f1 = i; aux.c2 = aux.c1 - 2; aux.f2 = aux.f1 - 2;//Analiza si existe posible capturapor la izquierda.
                    
                        if(chequearMovimiento(HUMANO, aux) == true && salto == true){
                            tablero[i][j] = ' ';cout<<"Se le ha soplado la pieza: ( "<<i<<" , "<<j<<" )\n"; cap = true;
                        }
                        }
                }
                        
            }
        }
        }
    }
}

void Juego::humanoMueve(){
    
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
                        cout << endl << "Movimiento del humano:" << endl;
			humanoMueve();
			if(chequearGanador(HUMANO) == true){ cout << "El humano ha ganado!" << endl;}
			turno++;
			imprimirTablero();
		} else {
			cout << endl << "Movimiento del computador:" << endl;
			//Movimiento hecho por la IA. Estamos trabajando para usted...
			if(chequearGanador(IA) == true){ cout << "La maquina ha ganado!" << endl;}
			turno++;
			imprimirTablero();
		}
	}
}

bool Juego::chequearGanador(Jugador jugador){
    
        int piezas = 0;
        //Retorna verdadero si solo hay un tipo de piezas sobre el tablero
        if(jugador == HUMANO){
                    
            for(int i = 0; i < 10; i++) {
	
                for(int j = 0; j < 10; j++) { if((tablero[i][j] == iaPeon) || (tablero[i][j] == iaDama)){piezas++;} }
            }
        
        }else if(jugador == IA){
        
            for(int i = 0; i < 10; i++) {
		for(int j = 0; j < 10; j++) { if((tablero[i][j] == humanoPeon) || (tablero[i][j] == humanoDama)){piezas++;} }
            }
        }
                       
        if(piezas > 0){return false;}else return true;
}

void Juego::imprimirTablero(){
    
    	cout << "    0     1     2     3     4     5     6     7     8     9  \n";
	cout << " ------------------------------------------------------------";
        for(int i = 0; i < 10; i++) {
		cout << '\n' << i << "|";
		for(int j = 0; j < 10; j++) {
			cout << "  " << tablero[i][j] << " " << " |";
		}
                cout <<"\n"<< " ------------------------------------------------------------";
	}
	cout << '\n' << " ------------------------------------------------------------" << '\n';

}


