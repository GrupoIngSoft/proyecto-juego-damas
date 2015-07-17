#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Juego.h"
#include <string.h>
#include <ctype.h>

using namespace std;

bool salto=false;//switch que avisa a las otras funciones que se realiza un salto.
bool mnsj_err=false;//switch que permite imprimir mensajes de error solo cuando el humano mueve.
bool ia=false;//switch para quitar mensajes no deseados cuando juega minimax.

Juego::Juego(){}

bool Juego::chequearMovimiento(Jugador jugador, Movimiento mv, char TABLERO[10][10]){ 

char dama, peon;
//No le permite al jugador mover una pieza contraria.
if(jugador == IA){ dama = iaDama; peon = iaPeon;}else if(jugador == HUMANO){ dama = humanoDama; peon = humanoPeon;}

if (mv.f1 < 0 || mv.f1 > 9 || mv.c1 < 0 || mv.c1 > 9){if(mnsj_err==true){cout<<"Parametros incorrectos.\n";}return false;}
        
//Retorna falso si la casilla destino está ocupada.
if (TABLERO[mv.f2][mv.c2] != ' '){if(mnsj_err==true){cout<<"La casilla destino está ocupada.\n";}return false;}
    
//Retorna falso si la pieza a mover es vacio.
if (TABLERO[mv.f1][mv.c1] == ' '){if(mnsj_err==true){cout<<"La pieza a mover no existe\n";}return false;}
    
//Retorna falso si la pieza se está moviendo vertical u horizontalmente.
if (mv.c1 == mv.c2 || mv.f1 == mv.f2){if(mnsj_err==true){cout<<"No puede mover las piezas ni vertical ni horizontalmente\n";}return false;}
 
    //Reglas para peones
    if (TABLERO[mv.f1][mv.c1] == peon){
            
        //Retorna falso si un peon retrocede.    
        if ((jugador == IA && mv.f2 < mv.f1) || (jugador == HUMANO && mv.f2 > mv.f1)){if(mnsj_err==true){cout<<"No puedes retroceder\n";}return false;}
            
        //Retorna verdadero si se mueve solo una casilla.
        if((mv.f2 == mv.f1 + 1 || mv.f2 == mv.f1 - 1)&&(mv.c2 == mv.c1 + 1 || mv.c2 == mv.c1 - 1)){return true;}
        
        else{//Reglas para saltos con peones.           
        
            //Retorna falso si el peón no se esta moviendo exactamente dos filas.
            //(solo necesita que se cumpla una igualdad para NO retornar falso)
            if (mv.f2 != mv.f1 + 2 && mv.f2 != mv.f1 - 2){if(mnsj_err==true){cout<<"No puedes moverte mas de dos filas \n";}return false;}
        
            //Retorna falso si el peón no se esta moviendo exactamente dos columnas.
            //(solo necesita que se cumpla una igualdad para NO retornar falso)
            if (mv.c2 != mv.c1 + 2 && mv.c2 != mv.c1 - 2){if(mnsj_err==true){cout<<"No puedes moverte mas de dos columnas\n";}return false;}
        
            //Retorna falso si intenta saltar sin haber una pieza que se este saltando.
            if (mv.f2 > mv.f1 && mv.c2 > mv.c1)
            {if (TABLERO[mv.f2 - 1][mv.c2 - 1] == ' '){if(mnsj_err==true){cout<<"No puedes moverte mas de una casillas sin saltar\n";}return false;}}

            else if (mv.f2 > mv.f1 && mv.c2 < mv.c1)
            {if (TABLERO[mv.f2 - 1][mv.c2 + 1] == ' '){if(mnsj_err==true){cout<<"No puedes moverte mas de una casillas sin saltar\n";}return false;}}

            else if (mv.f2 < mv.f1 && mv.c2 > mv.c1)
            {if (TABLERO[mv.f2 + 1][mv.c2 - 1] == ' '){if(mnsj_err==true){cout<<"No puedes moverte mas de una casillas sin saltar\n";}return false;}}

            else if (mv.f2 < mv.f1 && mv.c2 < mv.c1)
            {if (TABLERO[mv.f2 + 1][mv.c2 + 1] == ' '){if(mnsj_err==true){cout<<"No puedes moverte mas de una casillas sin saltar\n";}return false;}}
        
            //Retorna falso si salta a uno de sus compañeros.
            if (mv.f2 > mv.f1 && mv.c2 > mv.c1)
            {if ((TABLERO[mv.f2 - 1][mv.c2 - 1] == dama) || (TABLERO[mv.f2 - 1][mv.c2 - 1] == peon)){if(mnsj_err==true){cout<<"No puedes saltar a un compañero\n";}return false;}}

            else if (mv.f2 > mv.f1 && mv.c2 < mv.c1)
            {if ((TABLERO[mv.f2 - 1][mv.c2 + 1] == dama) || (TABLERO[mv.f2 - 1][mv.c2 + 1] == peon)){if(mnsj_err==true){cout<<"No puedes saltar a un compañero\n";}return false;}}
        
            else if (mv.f2 < mv.f1 && mv.c2 > mv.c1)
            {if ((TABLERO[mv.f2 + 1][mv.c2 - 1] == dama) || (TABLERO[mv.f2 + 1][mv.c2 - 1] == peon)){if(mnsj_err==true){cout<<"No puedes saltar a un compañero\n";}return false;}}
         
            else if (mv.f2 < mv.f1 && mv.c2 < mv.c1)
            {if ((TABLERO[mv.f2 + 1][mv.c2 + 1] == dama) || (TABLERO[mv.f2 + 1][mv.c2 + 1] == peon)){if(mnsj_err==true){cout<<"No puedes saltar a un compañero\n";}return false;}}
        
            //Si no rompe las reglas, entonces el salto es legal.   
            salto = true; return true;
            }
        }

        
    //Reglas de saltos para damas
    if (TABLERO[mv.f1][mv.c1] == dama){
        
        int piezas = 0;//Numero de piezas en la diagonal.        
        
        //Retorna falso si no se mueve en una diagonal perfecta.
        if(abs(mv.f1 - mv.f2) != abs(mv.c1 - mv.c2)){if(mnsj_err==true){cout<<"Debes moverte sobre una diagonal perfecta\n";}return false;}        
        
        //Retorna verdadero si solo me muevo una casilla.
        if((abs(mv.f1 - mv.f2) == 1 && abs(mv.c1 - mv.c2) == 1)){return true;}        
        
        //Analiza el tipo de movimiento en el caso de dirigirse a la esquina inferior derecha.
        if(mv.f2 > mv.f1 && mv.c2 > mv.c1){
            
            int j = mv.c1 + 1;
           
            for(int i = mv.f1 + 1; i < mv.f2; i++) {
                
                if(TABLERO[i][j] != ' '){
                    //Cuenta el numero de piezas dentro de la diagonal.
                    piezas++;
                    //Retorna falso si salta a un compañero.
                if((TABLERO[i][j] == dama) || (TABLERO[i][j] == peon)){if(mnsj_err==true){cout<<"No puedes saltar a un compañero\n";} return false;}
                
                }j++;
            }           
            //Retorna verdadero si es un movimiento sin salto.
            if(piezas == 0){return true;}
                    
            //retorna falso si salta a mas de un enemigo.
            if(piezas > 1){if(mnsj_err==true){cout<<"No puedes saltar a más de un enemigo en un salto\n";}return false;}
        }else 
        
        //Analiza el tipo de movimiento en el caso de dirigirse a la esquina inferior izquierda.
        if(mv.f2 > mv.f1 && mv.c2 < mv.c1){
            
            int j = mv.c1 - 1;
           
            for(int i = mv.f1 + 1; i < mv.f2; i++) {
                
                if(TABLERO[i][j] != ' '){
                    //Cuenta el numero de piezas dentro de la diagonal.
                    piezas++;
                    //Retorna falso si salta a un compañero.
                    if((TABLERO[i][j] == dama) || (TABLERO[i][j] == peon)){if(mnsj_err==true){cout<<"No puedes saltar a un compañero\n";} return false;
                    }
                }
                j--;
            }           
            //Retorna verdadero si es un movimiento sin salto.
            if(piezas == 0){return true;}
            
            //retorna falso si salta a mas de un enemigo.
            if(piezas > 1){if(mnsj_err==true){cout<<"No puedes saltar a más de un enemigo en un salto\n";}return false;}
        }else
        
        //Analiza el tipo de movimiento en el caso de dirigirse a la esquina superior derecha.
        if(mv.f2 < mv.f1 && mv.c2 > mv.c1){
            
            int j = mv.c1 + 1;
           
            for(int i = mv.f1 - 1; i > mv.f2; i--) {
                
                if(TABLERO[i][j] != ' '){
                    //Cuenta el numero de piezas dentro de la diagonal.
                    piezas++;
                    //Retorna falso si salta a un compañero.
                    if((TABLERO[i][j] == dama) || (TABLERO[i][j] == peon)){if(mnsj_err==true){cout<<"No puedes saltar a un compañero\n";} return false;
                    }
                }
                j++;
            }           
            //Retorna verdadero si es un movimiento sin salto.
            if(piezas == 0){return true;}
            
            //retorna falso si salta a mas de un enemigo.
            if(piezas > 1){if(mnsj_err==true){cout<<"No puedes saltar a más de un enemigo en un salto\n";}return false;}
        }else
        
        //Analiza el tipo de movimiento en el caso de dirigirse a la esquina superior izquierda.
        if(mv.f2 < mv.f1 && mv.c2 < mv.c1){
            
            int j = mv.c1 - 1;
           
            for(int i = mv.f1 - 1; i > mv.f2; i--) {
                
                if(TABLERO[i][j] != ' '){
                    //Cuenta el numero de piezas dentro de la diagonal.
                    piezas++;
                    //Retorna falso si salta a un compañero.
                    if((TABLERO[i][j] == dama) || (TABLERO[i][j] == peon)){if(mnsj_err==true){cout<<"No puedes saltar a un compañero\n";} return false;}
                }j--;
            }           
            //Retorna verdadero si es un movimiento sin salto.
            if(piezas == 0){return true;}
            
            //retorna falso si salta a mas de un enemigo.
            if(piezas > 1){if(mnsj_err==true){cout<<"No puedes saltar a más de un enemigo en un salto\n";}return false;}
        }
    //Si no rompe las reglas, el salto es legal.
    salto = true; return true;        
    }
}

void Juego::mover(Movimiento mv, char TABLERO[10][10]){
   
    if(salto == true){
        
        //Si juego con un peon, remueve la pieza capturada despues del salto.
        if( TABLERO[mv.f1][mv.c1] == iaPeon || TABLERO[mv.f1][mv.c1] == humanoPeon){
            
            if (mv.f2 > mv.f1 && mv.c2 > mv.c1){ cout<<"Se capturo la pieza "<<mv.f2 - 1<<" - "<<mv.c2 - 1<<" \n"; TABLERO[mv.f2 - 1][mv.c2 - 1] = ' ';
            }
            else if (mv.f2 > mv.f1 && mv.c2 < mv.c1){ cout<<"Se capturo la pieza "<<mv.f2 - 1<<" - "<<mv.c2 + 1<<" \n"; TABLERO[mv.f2 - 1][mv.c2 + 1] = ' ';
            }
            else if (mv.f2 < mv.f1 && mv.c2 > mv.c1){cout<<"Se capturo la pieza "<<mv.f2 + 1<<" - "<<mv.c2 - 1<<" \n"; TABLERO[mv.f2 + 1][mv.c2 - 1] = ' ';
            }
            else if (mv.f2 < mv.f1 && mv.c2 < mv.c1){cout<<"Se capturo la pieza "<<mv.f2 + 1<<" - "<<mv.c2 + 1<<" \n"; TABLERO[mv.f2 + 1][mv.c2 + 1] = ' ';
            }
        }
        
        //Si juego con una dama, remueve la pieza capturada despues del salto.
        if(TABLERO[mv.f1][mv.c1] == humanoDama  || TABLERO[mv.f1][mv.c1] == iaDama) {
            
            if(mv.f2 > mv.f1 && mv.c2 > mv.c1){
                
                int j = mv.c1 + 1;
           
                for(int i = mv.f1 + 1; i < mv.f2; i++) {
                
                    if(TABLERO[i][j] != ' '){TABLERO[i][j] = ' ';cout<<"Se capturo la pieza: ( "<<i<<" , "<<j<<" )\n";}
                j++;
                }
                           
            }else
            
            if(mv.f2 > mv.f1 && mv.c2 < mv.c1){
                
                int j = mv.c1 - 1;
           
                for(int i = mv.f1 + 1; i < mv.f2; i++) {
                
                    if(TABLERO[i][j] != ' '){TABLERO[i][j] = ' ';cout<<"Se capturo la pieza: ( "<<i<<" , "<<j<<" )\n";}
                j--;
                }
            }else
            
            if(mv.f2 < mv.f1 && mv.c2 < mv.c1){
                
                int j = mv.c1 - 1;
           
                for(int i = mv.f1 - 1; i > mv.f2; i--) {
                
                    if(TABLERO[i][j] != ' '){TABLERO[i][j] = ' ';cout<<"Se capturo la pieza: ( "<<i<<" , "<<j<<" )\n";}
                j--;
                }
            }else
                
            if(mv.f2 < mv.f1 && mv.c2 > mv.c1){
                
                int j = mv.c1 + 1;
           
                for(int i = mv.f1 - 1; i > mv.f2; i--) {
                
                    if(TABLERO[i][j] != ' '){TABLERO[i][j] = ' ';cout<<"Se capturo la pieza: ( "<<i<<" , "<<j<<" )\n";}
                j++;
                }
            }
        }
    }
    
    if(TABLERO[mv.f1][mv.c1] == humanoPeon || TABLERO[mv.f1][mv.c1] == humanoDama){//Funcion sopladita debe ser llamada antes de realizar los cambios,para asi evaluar incluso a una unica pieza que se mueva y no coma teniendo la oportunidad.
    
        if(salto == false){sopladita(mv,TABLERO);}//Si se realizo un salto, no llamar a la funcion sopladita.
        
    }
    
    // Borra la pieza en la posicion inicial y la escribe en la nueva posicion. 
    TABLERO[mv.f2][mv.c2] = TABLERO[mv.f1][mv.c1];
    TABLERO[mv.f1][mv.c1] = ' ';
    
    //Si un peon llega al otro extremo, se escribe una dama.
    for (int i = 0; i < 8; i++){
            
        if (TABLERO[0][i] == humanoPeon){ TABLERO[0][i] = humanoDama;}
        
        if (TABLERO[9][i] == iaPeon){ TABLERO[9][i] = iaDama;}
    }
    
    if(TABLERO[mv.f2][mv.c2] == humanoPeon || TABLERO[mv.f2][mv.c2] == humanoDama){
            
        if(salto == true){
            
            imprimirTablero(TABLERO);//imprimer el tablero despues de haber realizado un salto.
            multisalto(mv,TABLERO);//analiza la opcion de multisalto.
        }
    }
    
    salto = false;
}

void Juego::multisalto(Movimiento mv, char TABLERO[10][10]){ 
    
    salto=false;//devuelve la variable salto a su valor por defecto
    char resp[2];//guarda la respuesta si o no.
    mnsj_err=false;//no imprime mensajes de error.
    Movimiento aux;//guarda movimiento ingresado por el usuario.
    Movimiento copia_buena=mv;//guarda una copia del ultimo salto correcto para utilizarlo como argumento en la llamada recursiva
    
    cout<<"¿Desea continuar capturando?('si' o 'no')\n";
    cin>>resp;
    //No avanza hasta responder una de las dos opciones.
    while( strcmp("si",resp) != 0 && strcmp("no",resp) != 0 ){
        cout<<"¿Desea continuar capturando?('si' o 'no')\n";
        cin>>resp;
    }
    
    if(strcmp("no",resp) == 0){sopladita(mv,TABLERO);//Cuando termina de realizar multisaltos, soplara de ser posible.
    }else if(strcmp("si",resp) == 0){
    
            bool sw = false;
            
            cout << "Mover pieza: ("<<mv.f2 << " , "<<mv.c2 <<" ) \n";
            cout << "A la casilla: \n";
            cout << "Fila: ";
            cin >> aux.f2;
            cout << "Columna: ";
            cin >> aux.c2;
                
            aux.f1 = mv.f2; aux.c1 = mv.c2; //Guarda la posicion actual como origen del siguiente salto solicitado a evaluar.
            mnsj_err=true;
            if((chequearMovimiento(HUMANO, aux,TABLERO) == true) && (salto == true)){ sw = true;copia_buena=aux;}
            mnsj_err=false;
            
            if(sw==true){ 
                mover(aux,TABLERO);//Si el salto es legal, lo realiza, y llama nuevamente a multisalto.
            }else{cout<<"Movimiento ilegal. Por favor intente otra vez.\n";multisalto(copia_buena,TABLERO);}//En caso que no existan mas saltos, llama una vez mas a la funcion multisalto para darle la oportunidad de responder 'no'.
    } 
 }

void Juego::sopladita(Movimiento mv, char TABLERO[10][10]){
    
    mnsj_err=false;//cuando se llama a la funcion sopladita, todavia no ha terminado la funcion humano mueve, por lo tanto mnsj_err es true cuando entra en esta funcion.
    
    Movimiento aux,origen,peon,dama;
    origen.f1 = -1; origen.c1= -1;
    peon.f1 = -1; peon.c1= -1;
    dama.f1 = -1; dama.c1= -1;
    
    bool sw = false;//Si ya capturo una dama, no sigue capurando mas.
    bool cap = false;//Si ya capturo una pieza, no sigue capturando mas.
        
    for(int i = 0; i < 10; i++){//Busca en toda la matriz.
        
        for(int j = 0; j < 10; j++) {
                    
            if(TABLERO[i][j] == humanoPeon ){//Analiza solo a los peones.
                        
                if((cap == true)){}else{//Analiza a todos los peones.
                        
                        //if(j > 1 && j < 8 && i > 1 && i < 8){
                        
                        aux.c1 = j; aux.f1 = i; aux.c2 = aux.c1 + 2; aux.f2 = aux.f1 - 2;//Analiza si exite posible captura por la derecha.
                    
                        if(chequearMovimiento(HUMANO, aux,TABLERO) == true && salto == true){
                            
                            if(i==mv.f2 && j==mv.c2){origen.f1=i;origen.c1=j;cap=true;}else{peon.f1 = i; peon.c1= j;}
                            
                        }else{
                        aux.c1 = j; aux.f1 = i; aux.c2 = aux.c1 - 2; aux.f2 = aux.f1 - 2;//Analiza si existe posible capturapor la izquierda.
                    
                            if(chequearMovimiento(HUMANO, aux,TABLERO) == true && salto == true){
                            
                            if(i==mv.f2 && j==mv.c2){origen.f1=i;origen.c1=j;cap=true;}else{peon.f1 = i; peon.c1= j;}
                            
                            }
                        }
                        //}
                }
                        
            }
        }
    }
        
    for(int i = 0; i < 10; i++) {//Busca en toda la matriz.
        
        for(int j = 0; j < 10; j++) {
                    
            if(TABLERO[i][j] == humanoDama){//Analiza solo a las damas.
                    
                if((cap == true)){}else{//Analiza a todas las damas.
                
                    if(cap == false){//Busca un peon o dama enemiga dentro de la diagonal inferior derecha.
                    
                        int c = j + 1, f = i + 1;//Toma a la casilla siguiente como primera casila a analizar.
                    
                        aux.f1 = i; aux.c1 = j;//Guarda la pieza como origen del movimiento
                                               
                        while(c < 9 && f < 9){//Limita la busqueda hasta la penultima casilla del borde del tablero.
                        
                        if((TABLERO[f][c] == iaPeon) || (TABLERO[f][c] == iaDama)){//Guarda la casilla siguiente como la casilla destino.
                            aux.f2 = f + 1; aux.c2 = c + 1; 
                        
                            if((chequearMovimiento(HUMANO, aux,TABLERO) == true) && (salto == true)){
                                
                                if(i==mv.f2 && j==mv.c2){origen.f1=i;origen.c1=j;cap=true;}else{dama.f1 = i; dama.c1= j;}
                                
                            }
                        }
                        c++;f++;
                        }
                    }
                    
                    if(cap == false){//Busca un peon o dama enemiga dentro de la diagonal inferior izquierda.
                    
                        int c = j - 1, f = i + 1;//Toma a la casilla siguiente como primera casilla a analizar.
                    
                        aux.f1 = i; aux.c1 = j;//Guarda la pieza como origen del movimiento
                                               
                        while(c > 0 && f < 9){//Limita la busqueda hasta la penultima casilla del borde del tablero.
                        
                        if((TABLERO[f][c] == iaPeon) || (TABLERO[f][c] == iaDama)){//Guarda la casilla siguiente como la casilla destino.
                            aux.f2 = f + 1; aux.c2 = c - 1; 
                        
                            if((chequearMovimiento(HUMANO, aux,TABLERO) == true) && (salto == true)){
                                
                                if(i==mv.f2 && j==mv.c2){origen.f1=i;origen.c1=j;cap=true;}else{dama.f1 = i; dama.c1= j;}
                                
                            }
                        }
                        c--;f++;
                        }
                    
                    }
                    
                    if(cap == false){//Busca un peon o dama enemiga dentro de la diagonal superior izquierda.
                    
                        int c = j - 1, f = i - 1;//Toma a la casilla siguiente como primera casilla a analizar.
                    
                        aux.f1 = i; aux.c1 = j;//Guarda la pieza como origen del movimiento
                                               
                        while(c > 0 && f > 0){//Limita la busqueda hasta la penultima casilla del borde del tablero.
                        
                        if((TABLERO[f][c] == iaPeon) || (TABLERO[f][c] == iaDama)){//Guarda la casilla siguiente como la casilla destino.
                            aux.f2 = f - 1; aux.c2 = c - 1; 
                        
                            if((chequearMovimiento(HUMANO, aux,TABLERO) == true) && (salto == true)){
                                
                                if(i==mv.f2 && j==mv.c2){origen.f1=i;origen.c1=j;cap=true;}else{dama.f1 = i; dama.c1= j;}
                                
                            }
                        }
                        c--;f--;
                        }
                    }
                    
                    if(cap == false){//Busca un peon o dama enemiga dentro de la diagonal superior derecha.
                    
                        int c = j + 1, f = i - 1;//Toma a la casilla siguiente como primera casilla a analizar.
                    
                        aux.f1 = i; aux.c1 = j;//Guarda la pieza como origen del movimiento.
                                               
                        while(c < 9 && f > 0){//Limita la busqueda hasta la penultima casilla del borde del tablero.
                        
                        if((TABLERO[f][c] == iaPeon) || (TABLERO[f][c] == iaDama)){//Guarda la casilla siguiente como la casilla destino.
                            aux.f2 = f - 1; aux.c2 = c + 1; 
                        
                            if((chequearMovimiento(HUMANO, aux,TABLERO) == true) && (salto == true)){
                                
                                if(i==mv.f2 && j==mv.c2){origen.f1=i;origen.c1=j;cap=true;}else{dama.f1 = i; dama.c1= j;}
                                
                            }
                        }
                        c++;f--;
                        }
                    
                    }
                    
                }
            }
        }
    }
    if(origen.f1 != -1 && origen.c1 != -1){
        
        TABLERO[origen.f1][origen.c1] = ' '; if(ia==false){cout<<"Se le ha soplado la pieza: ( "<<origen.f1<<" , "<<origen.c1<<" )\n";}
        
    }else if(dama.f1 != -1 && dama.c1 != -1){
        
        TABLERO[dama.f1][dama.c1] = ' '; if(ia==false){cout<<"Se le ha soplado la pieza: ( "<<dama.f1<<" , "<<dama.c1<<" )\n";}
        
    }else if(peon.f1 != -1 && peon.c1 != -1){
        
        TABLERO[peon.f1][peon.c1] = ' '; if(ia==false){cout<<"Se le ha soplado la pieza: ( "<<peon.f1<<" , "<<peon.c1<<" )\n";}
        
    }
    
    salto=false;//Regresa al valor de salto por defecto.
}

void Juego::humanoMueve(){
    
    mnsj_err=true;
    
    Movimiento mv;
    bool sw = false;
    char f1,f2,c1,c2;
    
    while(sw==false){

    cout << "Mover pieza\n";
    cout << "Fila: ";
    cin >> f1;
    mv.f1=(int)(f1-48);    
    cout << "Columna: ";
    cin >> c1;
    mv.c1=(int)(c1-48);
   
    // Chequea si el usuario se equivoca al ingresar el movimiento.
        while (mv.f1 < 0 || mv.f1 > 9 || mv.c1 < 0 || mv.c1 > 9 ){ 
        cout << "Ingresar numeros entre 0 y 9.\n";
        cout << "Mover pieza:\n";
        cout << "Fila: ";
        cin >> f1;
        mv.f1=(int)(f1-48);    
        cout << "Columna: ";
        cin >> c1;
        mv.c1=(int)(c1-48);
        }
    
    cout << "A la casilla:\n";
    cout << "Fila: ";
    cin >> f2;
    mv.f2=(int)(f2-48); 
    cout << "Columna: ";
    cin >> c2;
    mv.c2=(int)(c2-48); 
    
        while (mv.f2 < 0 || mv.f2 > 9 || mv.c2 < 0 || mv.c2 > 9){
        cout << "Ingresar numeros entre 0 y 9.\n";
        cout << "A la casilla\n";
        cout << "Fila: ";
        cin >> f2;
        mv.f2=(int)(f2-48); 
        cout << "Columna: ";
        cin >> c2;
        mv.c2=(int)(c2-48); 
        }
    
        sw = chequearMovimiento(HUMANO, mv,tablero);

        if(sw==false){ cout<<"Movimiento ilegal. Por favor intente otra vez.\n";
        }else{
            system("clear");
            cout<<"***************************************************************"<<endl;
            cout<<"=> El humano ha movido la pieza:("<<mv.f1<< "," <<mv.c1<< ") a la posicion ("<<mv.f2<<","<<mv.c2<<")\n";
            
            mover(mv, tablero); 
        }
    }
    
    mnsj_err=false;
       
}

void Juego::jugar(){
    
	int turno = 0;
        cout<<"***************************************************************"<<endl;
	imprimirTablero(tablero);
        cout<<"***************************************************************"<<endl;
        
	while(!chequearGanador(HUMANO,tablero) && !chequearGanador(IA,tablero)) {
           
            
		if(turno % 2 == 0) {
                        cout << endl << "TURNO DEL HUMANO:" << endl;
			
                        humanoMueve();
                        
			if(chequearGanador(HUMANO,tablero) == true){ cout << "El humano ha ganado!" << endl;}
			turno++;
                        
		} else {
                        
                        ia=true;
			
			Movimiento IAmovi = minimax(tablero);//Despues de llamar a minimax, salto es igual a false.(esto se debe a que cada vez que se llama a la funcion puntaje, se debe devolver el valor de salto a 'false' para que esto no interfiera con los siguientes analisis)
                        cout<<"=> La maquina ha movido la pieza:("<<IAmovi.f1<<","<<IAmovi.c1<<") a la posicion ("<<IAmovi.f2<<","<<IAmovi.c2<<")\n";
                        cout<<"***************************************************************"<<endl;
                        chequearMovimiento(IA,IAmovi,tablero);//con esto volvemos el valor de salto a true en caso de ser salto, para que eliminar la pieza en caso de salto al llamar a la funcion mover.
                        
                        if(salto == true){mover(IAmovi,tablero);salto=false;}else{mover(IAmovi,tablero);}
                        
                        if(chequearGanador(IA,tablero) == true){ cout << "La maquina ha ganado!" << endl;}
			turno++;
                        imprimirTablero(tablero);
                        cout<<"***************************************************************"<<endl;
                        ia=false;
		}
	}
}

bool Juego::chequearGanador(Jugador jugador, char TABLERO[10][10]){
    
        int piezas = 0;
        //Retorna verdadero si solo hay un tipo de piezas sobre el tablero
        if(jugador == HUMANO){
                    
            for(int i = 0; i < 10; i++) {
	
                for(int j = 0; j < 10; j++) { if((TABLERO[i][j] == iaPeon) || (TABLERO[i][j] == iaDama)){piezas++;} }
            }
        
        }else if(jugador == IA){
        
            for(int i = 0; i < 10; i++) {
		for(int j = 0; j < 10; j++) { if((TABLERO[i][j] == humanoPeon) || (TABLERO[i][j] == humanoDama)){piezas++;} }
            }
        }
                       
        if(piezas > 0){return false;}else return true;
        
        //Implementar triunfo por bloqueo.
}

void Juego::imprimirTablero(char tableros[10][10]){
        
        cout<<"***************************************************************"<<endl;
    	cout << "    0     1     2     3     4     5     6     7     8     9  \n";
	cout << " ------------------------------------------------------------";
        for(int i = 0; i < 10; i++) {
		cout << '\n' << i << "|";
		for(int j = 0; j < 10; j++) {
			cout << "  " << tableros[i][j] << " " << " |";
		}
                cout <<"\n"<< " ------------------------------------------------------------";
	}
        cout<<endl;
	//cout << '\n' << " ------------------------------------------------------------" << '\n';

}

bool Juego::profundidad(int pro){   
    // pro = 1: Si tiene la oportunidad para saltar lo hara, pero no evitara que saltes.
    // pro = 2: Tomara la oportunidad de saltar y evitara que saltes si es evidente, pero con buenos movimiento le puedes ganar.
    // pro = 3: De aqui en adelante se vuelve mas inteligente .
    if(pro == 5){ return true;
    }else{return false;} 
}

Movimiento Juego::minimax(char IAtablero[10][10]){
    
    int mejorPuntaje = 1001; //  si o si me guarda la primera jugada.
    Movimiento mejorJugada; mejorJugada.p = 1000; // va guardando el mejor movimiento y puntaje
    Movimiento mejorMovi; //Mejor movimiento a retornar.
    Movimiento mv; //Variable para enviar posiciones a evaluar.
    
    char copiaTablero[10][10]; //tablero auxiliar.
    
    for(int i = 0; i < 10; i++){//crea una copia del original
	for(int j = 0; j < 10; j++){
        copiaTablero[i][j] = IAtablero[i][j];}}
    
    for(int i = 0; i < 10; i++){
	for(int j = 0; j < 10; j++){
            
            if(IAtablero[i][j] == iaPeon){ //Evalua todos los movimientos con peones.
                
                int puntaje;
                
                mv.c1 = j; mv.f1 = i; //El origen del movimiento a evaluar es la posicion del peon encontrado. 
                
                mv.c2 = j + 2; mv.f2 = i + 2;//COORDENADAS PARA COMPROBAR SALTO POR LA DERECHA.
                                
                    if(mv.f1 < 8 && mv.c1 < 8 && chequearMovimiento(IA, mv,IAtablero) == true && salto == true){ //Evalua primero el salto, de no ser posible hacer un movimiento simple.
                    
                        salto=false;//devuelve el valor de salto a defecto.
                        
                        puntaje = max(IAtablero,mv,1);//Llama a la funcion recursiva para obtener un puntaje. 
                        
                        for(int i = 0; i < 10; i++){for(int j = 0; j < 10; j++){IAtablero[i][j] = copiaTablero[i][j];}}//devuelve el valor del original.
                        
                        if(puntaje < mejorJugada.p){//Si el puntaje obtenido es mejor que el actual mejor, actualiza el mejor puntaje y movimiento.
                        
                            mejorJugada.p = puntaje; mejorJugada.f1 = mv.f1; mejorJugada.c1 = mv.c1;mejorJugada.f2 = mv.f2; mejorJugada.c2 = mv.c2;
                        }
                        
                    }else{//evalua un movimiento simple solo si no existe la posibilidad de saltar,ya que saltar es obligatorio.
                 
                mv.c2 = j + 1; mv.f2 = i + 1;//COORDENADAS PARA COMPROBAR MOVIMIENTO POR LA DERECHA.
                                    
                    if(mv.f1 < 9 && mv.c1 < 9 && chequearMovimiento(IA, mv,IAtablero) == true ){ 
                       
                        
                        
                        puntaje = max(IAtablero,mv,1);
                        
                        
                        
                        
                        for(int i = 0; i < 10; i++){for(int j = 0; j < 10; j++){IAtablero[i][j] = copiaTablero[i][j];}}//devuelve el valor del original.
                        
                        if(puntaje < mejorJugada.p){
                                      
                            mejorJugada.p = puntaje;mejorJugada.f1 = mv.f1; mejorJugada.c1 = mv.c1;mejorJugada.f2 = mv.f2; mejorJugada.c2 = mv.c2;
                        } 
                    }
                    
                    }
                
                mv.c2 = j - 2; mv.f2 = i + 2;//COORDENADAS PARA COMPROBAR SALTO POR LA IZQUIERDA.
                              
                    if(mv.f1 < 8 && mv.c1 > 1 && chequearMovimiento(IA, mv,IAtablero) == true && salto == true){//Evalua primero el salto, de no ser posible hacer un movimiento simple.
                    
                        salto=false;//devuelve el valor de salto a defecto.
                        
                        puntaje = max(IAtablero,mv,1);
                        
                        for(int i = 0; i < 10; i++){for(int j = 0; j < 10; j++){IAtablero[i][j] = copiaTablero[i][j];}}//devuelve el valor del original.
                                    
                        if(puntaje < mejorJugada.p){
                        
                            mejorJugada.p = puntaje; mejorJugada.f1 = mv.f1; mejorJugada.c1 = mv.c1;mejorJugada.f2 = mv.f2; mejorJugada.c2 = mv.c2;
                        }
                        
                        
                    
                    }else{//evalua un movimiento simple solo si no existe la posibilidad de saltar,ya que saltar es obligatorio.
                    
                mv.c2 = j - 1; mv.f2 = i + 1;//COORDENADAS PARA COMPROBAR MOVIMIENTO POR LA IZQUIERDA.
  
                
                    if(mv.f1 < 9 && mv.c1 > 0 && chequearMovimiento(IA, mv,IAtablero) == true ){ 
                        
                        puntaje = max(IAtablero,mv,1);
                        
                        for(int i = 0; i < 10; i++){for(int j = 0; j < 10; j++){IAtablero[i][j] = copiaTablero[i][j];}}//devuelve el valor del original.
                                            
                        if(puntaje < mejorJugada.p){
                            
                            mejorJugada.p = puntaje; mejorJugada.f1 = mv.f1; mejorJugada.c1 = mv.c1;mejorJugada.f2 = mv.f2; mejorJugada.c2 = mv.c2;
                        }
                    }
                    
                    }
                
                if(mejorJugada.p < mejorPuntaje) {//Guarda el mejor movimiento entre sus cuatro posibilidades entre todos los peones.
		
                    mejorPuntaje = mejorJugada.p;
                    mejorMovi.f1 = mejorJugada.f1;
                    mejorMovi.c1 = mejorJugada.c1;
                    mejorMovi.f2 = mejorJugada.f2;
                    mejorMovi.c2 = mejorJugada.c2;
                                        
		}
                                                           
            }
        }
    }
    
    return mejorMovi;
    
}

int Juego::max(char IAtablero[10][10], Movimiento mvAnterior,int pro) {
    
    if(profundidad(pro) || (chequearMovimiento(IA, mvAnterior,IAtablero) == true && salto == true)){salto = false; return puntaje(IA,mvAnterior,IAtablero);}//Si se alcanza la profundidad o si se termina el juego, retorna el puntaje del movimiento anterior en el tablero.
    
    mover(mvAnterior,IAtablero);// Aplica los cambios para trabajar con un tablero actualizado.

    int mejorPuntaje = -1001; //  si o si me guarda la primera jugada.
    Movimiento mejorJugada; mejorJugada.p = -1000; // va guardando el mejor movimiento y puntaje
    Movimiento mejorMovi; //Mejor movimiento a retornar.
    Movimiento mv; //Variable para enviar posiciones a evaluar.
    
    char copiaTablero[10][10]; //tablero auxiliar.
    
    for(int i = 0; i < 10; i++){//crea una copia del original
	for(int j = 0; j < 10; j++){
        copiaTablero[i][j] = IAtablero[i][j];}}
    
    for(int i = 0; i < 10; i++){
	for(int j = 0; j < 10; j++){
            
            if(IAtablero[i][j] == humanoPeon){ //Evalua todos los movimientos con peones.
                
                int puntaje; //Guarda los puntajes de los cuatro movimientos posibles con peones.
                            
                mv.c1 = j; mv.f1 = i; //El origen del movimiento a evaluar es la posicion del peon encontrado. 
                
                mv.c2 = j + 2; mv.f2 = i - 2;//COORDENADAS PARA COMPROBAR SALTO POR LA DERECHA.
                                
                    if(mv.f1 > 1 && mv.c1 < 8 && chequearMovimiento(HUMANO, mv,IAtablero) == true && salto == true){ //Evalua primero el salto, de no ser posible hacer un movimiento simple.
                    
                        salto=false;//devuelve el valor de salto a defecto.
                        
                        puntaje = min(IAtablero,mv,pro + 1);//Llama a la funcion recursiva para obtener un puntaje. 
                        
                        for(int i = 0; i < 10; i++){for(int j = 0; j < 10; j++){IAtablero[i][j] = copiaTablero[i][j];}}//devuelve el valor del original.
                        
                        if(puntaje > mejorJugada.p){//Si el puntaje obtenido es mejor que el actual mejor, actualiza el mejor puntaje y movimiento.
                        
                            mejorJugada.p = puntaje; mejorJugada.f1 = mv.f1; mejorJugada.c1 = mv.c1;mejorJugada.f2 = mv.f2; mejorJugada.c2 = mv.c2;
                        }
                    }else{//evalua un movimiento simple solo si no existe la posibilidad de saltar,ya que saltar es obligatorio.
                 
                mv.c2 = j + 1; mv.f2 = i - 1;//COORDENADAS PARA COMPROBAR MOVIMIENTO POR LA DERECHA.
                                    
                    if(mv.f1 > 0 && mv.c1 < 9 && chequearMovimiento(HUMANO, mv,IAtablero) == true ){ 
                        
                        puntaje = min(IAtablero,mv,pro + 1);
                        
                        for(int i = 0; i < 10; i++){for(int j = 0; j < 10; j++){IAtablero[i][j] = copiaTablero[i][j];}}//devuelve el valor del original.
                        
                        if(puntaje > mejorJugada.p){
                                      
                            mejorJugada.p = puntaje;mejorJugada.f1 = mv.f1; mejorJugada.c1 = mv.c1;mejorJugada.f2 = mv.f2; mejorJugada.c2 = mv.c2;
                        } 
                    }
                    }
                
                mv.c2 = j - 2; mv.f2 = i - 2;//COORDENADAS PARA COMPROBAR SALTO POR LA IZQUIERDA.
                              
                    if(mv.f1 > 1 && mv.c1 > 1 && chequearMovimiento(HUMANO, mv,IAtablero) == true && salto == true){//Evalua primero el salto, de no ser posible hacer un movimiento simple.
                    
                        salto=false;//devuelve el valor de salto a defecto.
                        
                        puntaje = min(IAtablero,mv,pro + 1);
                        
                        for(int i = 0; i < 10; i++){for(int j = 0; j < 10; j++){IAtablero[i][j] = copiaTablero[i][j];}}//devuelve el valor del original.
                                    
                        if(puntaje > mejorJugada.p){
                        
                            mejorJugada.p = puntaje; mejorJugada.f1 = mv.f1; mejorJugada.c1 = mv.c1;mejorJugada.f2 = mv.f2; mejorJugada.c2 = mv.c2;
                        }
                    }else{//evalua un movimiento simple solo si no existe la posibilidad de saltar,ya que saltar es obligatorio.
                    
                mv.c2 = j - 1; mv.f2 = i - 1;//COORDENADAS PARA COMPROBAR MOVIMIENTO POR LA IZQUIERDA.
                                    
                    if(mv.f1 > 0 && mv.c1 > 0 && chequearMovimiento(HUMANO, mv,IAtablero) == true ){ 
                        
                        puntaje = min(IAtablero,mv,pro + 1);
                        
                        for(int i = 0; i < 10; i++){for(int j = 0; j < 10; j++){IAtablero[i][j] = copiaTablero[i][j];}}//devuelve el valor del original.
                                            
                        if(puntaje > mejorJugada.p){
                            
                            mejorJugada.p = puntaje; mejorJugada.f1 = mv.f1; mejorJugada.c1 = mv.c1;mejorJugada.f2 = mv.f2; mejorJugada.c2 = mv.c2;
                        }
                    }
                    }
                
                if(mejorJugada.p > mejorPuntaje) {//Guarda el mejor puntaje entre sus cuatro posibilidades entre todos los peones.
		
                    mejorPuntaje = mejorJugada.p;
                
                }
            }
        }
    }
    return mejorPuntaje;
}

int Juego::min(char IAtablero[10][10],Movimiento mvAnterior,int pro) {
 
    if(profundidad(pro) || (chequearMovimiento(HUMANO, mvAnterior,IAtablero) == true && salto == true)){ salto = false; return puntaje(HUMANO, mvAnterior,IAtablero);}//Calcula el puntaje del movimiento en el tablero.
    
    mover(mvAnterior,IAtablero);
    
    int mejorPuntaje = 1001; //  si o si me guarda la primera jugada.
    Movimiento mejorJugada; mejorJugada.p = 1000; // va guardando el mejor movimiento y puntaje
    Movimiento mejorMovi; //Mejor movimiento a retornar.
    Movimiento mv; //Variable para enviar posiciones a evaluar.
    
    char copiaTablero[10][10]; //tablero auxiliar.
    
    for(int i = 0; i < 10; i++){//crea una copia del original
	for(int j = 0; j < 10; j++){
        copiaTablero[i][j] = IAtablero[i][j];}}
    
    for(int i = 0; i < 10; i++){
	for(int j = 0; j < 10; j++){
            
            if(IAtablero[i][j] == iaPeon){ //Evalua todos los movimientos con peones.
                
                int puntaje;
                
                mv.c1 = j; mv.f1 = i; //El origen del movimiento a evaluar es la posicion del peon encontrado. 
                
                mv.c2 = j + 2; mv.f2 = i + 2;//COORDENADAS PARA COMPROBAR SALTO POR LA DERECHA.
                                
                    if(mv.f1 < 8 && mv.c1 < 8 && chequearMovimiento(IA, mv,IAtablero) == true && salto == true){ //Evalua primero el salto, de no ser posible hacer un movimiento simple.
                    
                        salto=false;//devuelve el valor de salto a defecto.
                        
                        puntaje = max(IAtablero,mv,pro + 1);//Llama a la funcion recursiva para obtener un puntaje. 
                        
                        for(int i = 0; i < 10; i++){for(int j = 0; j < 10; j++){IAtablero[i][j] = copiaTablero[i][j];}}//devuelve el valor del original.
                        
                        if(puntaje < mejorJugada.p){//Si el puntaje obtenido es mejor que el actual mejor, actualiza el mejor puntaje y movimiento.
                        
                            mejorJugada.p = puntaje; mejorJugada.f1 = mv.f1; mejorJugada.c1 = mv.c1;mejorJugada.f2 = mv.f2; mejorJugada.c2 = mv.c2;
                        }
                        
                    }else{//evalua un movimiento simple solo si no existe la posibilidad de saltar,ya que saltar es obligatorio.
                 
                mv.c2 = j + 1; mv.f2 = i + 1;//COORDENADAS PARA COMPROBAR MOVIMIENTO POR LA DERECHA.
                                    
                    if(mv.f1 < 9 && mv.c1 < 9 && chequearMovimiento(IA, mv,IAtablero) == true ){ 
                       
                        
                        
                        puntaje = max(IAtablero,mv,pro + 1);
                        
                        
                        
                        
                        for(int i = 0; i < 10; i++){for(int j = 0; j < 10; j++){IAtablero[i][j] = copiaTablero[i][j];}}//devuelve el valor del original.
                        
                        if(puntaje < mejorJugada.p){
                                      
                            mejorJugada.p = puntaje;mejorJugada.f1 = mv.f1; mejorJugada.c1 = mv.c1;mejorJugada.f2 = mv.f2; mejorJugada.c2 = mv.c2;
                        } 
                    }
                    
                    }
                
                mv.c2 = j - 2; mv.f2 = i + 2;//COORDENADAS PARA COMPROBAR SALTO POR LA IZQUIERDA.
                              
                    if(mv.f1 < 8 && mv.c1 > 1 && chequearMovimiento(IA, mv,IAtablero) == true && salto == true){//Evalua primero el salto, de no ser posible hacer un movimiento simple.
                    
                        salto=false;//devuelve el valor de salto a defecto.
                        
                        puntaje = max(IAtablero,mv,pro + 1);
                        
                        for(int i = 0; i < 10; i++){for(int j = 0; j < 10; j++){IAtablero[i][j] = copiaTablero[i][j];}}//devuelve el valor del original.
                                    
                        if(puntaje < mejorJugada.p){
                        
                            mejorJugada.p = puntaje; mejorJugada.f1 = mv.f1; mejorJugada.c1 = mv.c1;mejorJugada.f2 = mv.f2; mejorJugada.c2 = mv.c2;
                        }
                        
                        
                    
                    }else{//evalua un movimiento simple solo si no existe la posibilidad de saltar,ya que saltar es obligatorio.
                    
                mv.c2 = j - 1; mv.f2 = i + 1;//COORDENADAS PARA COMPROBAR MOVIMIENTO POR LA IZQUIERDA.
  
                
                    if(mv.f1 < 9 && mv.c1 > 0 && chequearMovimiento(IA, mv,IAtablero) == true ){ 
                        
                        puntaje = max(IAtablero,mv,pro + 1);
                        
                        for(int i = 0; i < 10; i++){for(int j = 0; j < 10; j++){IAtablero[i][j] = copiaTablero[i][j];}}//devuelve el valor del original.
                                            
                        if(puntaje < mejorJugada.p){
                            
                            mejorJugada.p = puntaje; mejorJugada.f1 = mv.f1; mejorJugada.c1 = mv.c1;mejorJugada.f2 = mv.f2; mejorJugada.c2 = mv.c2;
                        }
                    }
                    
                    }
                
                if(mejorJugada.p < mejorPuntaje) {//Guarda el mejor movimiento entre sus cuatro posibilidades entre todos los peones.
		
                    mejorPuntaje = mejorJugada.p;
                }
                                                           
            }
        }
    }
    
    return mejorPuntaje;
}

int Juego::puntaje(Jugador jugador, Movimiento mv,char TABLERO[10][10]){
    
    if(jugador == HUMANO){
        
        if(chequearMovimiento(HUMANO,mv,TABLERO) == true && salto == true) {salto=false; return 10; }
        
    }else if(jugador == IA){
        
        if(chequearMovimiento(IA,mv,TABLERO) == true && salto == true) {salto=false; return -10; }
    
    }else return 0;
}


