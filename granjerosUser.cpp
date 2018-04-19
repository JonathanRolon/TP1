#include "granjerosLib.h"
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;


void mostrarInicio(){
	cout << "********************" << endl
		 << "GRANJEROS 2018 v1.0!" << endl
		 << "********************" << endl;
}

void menuOpciones(Jugador *unJugador,bool *juegoNuevo,bool *finJuego,Cultivo cultivos[],
				  char tiempoRecu[][TOPE_MATRIZ],char terreno[][TOPE_MATRIZ],
				  char tiempoCosecha[][TOPE_MATRIZ],
				  bool terrenoRiego[][TOPE_MATRIZ])
{

	string opMenu;
	bool ingresoBien=false;
	while(!ingresoBien)
	{
		cout<<endl;
		cout<<"!!!Menu principal!!!:"<<endl<<"Elija una opcion"<<endl;
		cout<<"1.Ir a la tienda"<<endl<<"2.Sembrar semilla"<<endl
			<<"3.Regar mis cultivos"<<endl<<"4.Cosechar"<<endl
			<<"5.Pasar al siguiente turno"<<endl
			<<"6.Quitar juego"<<endl;
		cin>>opMenu;
		unsigned opcion=atoi(opMenu.c_str());
		switch(opcion)
		{
		case(1):tiendaSemillas(unJugador,cultivos);break;
		case(2):sembrar(unJugador,terreno,cultivos,tiempoRecu,tiempoCosecha);break;
		case(3):regar(terreno,unJugador,terrenoRiego);break;
		case(4):cosechar(terreno,tiempoRecu,unJugador,cultivos,tiempoCosecha);break;
		case(5):definirSecadosPodridos(terreno,terrenoRiego,tiempoRecu,
				                       cultivos,tiempoCosecha);
		        definirTurno(unJugador,juegoNuevo,terreno,tiempoCosecha,
		        		     tiempoRecu,terrenoRiego);
			    actualizarEstadoParcelas(terreno,tiempoRecu,tiempoCosecha);
				break;
		case(6):salir(finJuego);break;
		default:cout<<"No se ingreso una opcion valida"<<endl;
		}
		if(validarOpcion(opMenu))
		{
			ingresoBien=true;
		}
	}
}

void mostrarEstadoJuego(char terreno[][TOPE_MATRIZ],Jugador *unJugador)
{
	cout<<"Estado Jugador!"<<endl
		<<"Turnos restantes: "<<unJugador->turnosJuego<<endl
		<<"Monedas: "<<unJugador->monedas<<endl
		<<"Unidades de Agua: "<<unJugador->tanqueAgua<<endl;
	for(int i=0;i<3;i++)
	{
		cout<<"Cantidad de semillas de cultivo "<<unJugador->semillas[i].nombre<<": "
			<<unJugador->semillas[i].unidadesSemilla<<endl;
	}
	cout<<endl;
	mostrarTerreno(terreno);
}

void mostrarGananciaTotal(Jugador unJugador)
{
	if(unJugador.monedas>50)
	{
		cout<<"Felicitaciones!!! gano: "<<unJugador.monedas-50<<" monedas."<<endl
			<<"Cantidad total: "<<unJugador.monedas<<endl;
	}
	else
	if(unJugador.monedas==50)
	{
		cout<<"Usted no gano monedas adicionales. Cantidad de monedas: "
			<<unJugador.monedas<<endl;
	}
	else
	{
		cout<<"Usted perdio!!!.Monedas: "<<unJugador.monedas<<endl;
	}
	cout<<endl;
}

void mostrarCultivos(Cultivo cultivos[])
{
	cout<<"Cultivos:"<<endl;
	for(int i=0;i<3;i++)
	{
		cout<<cultivos[i].nombre<<endl;
	}
}

string pedirCultivo()
{
	string opcionIng;
	cout<<"Ingrese el nombre del cultivo."<<endl;
	cin>>opcionIng;
	return opcionIng;
}

void mostrarTerreno(char terreno[][TOPE_MATRIZ])
{
	cout<<"----------------"<<endl;
	cout<<"Estado del terreno:"<<endl;
	for(int i=0;i<TOPE_MATRIZ;i++)
	{
		for(int j=0;j<TOPE_MATRIZ;j++)
		{
			cout<<" "<<terreno[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"----------------"<<endl;
}

void verPosicionElegida(char terreno[][TOPE_MATRIZ],string fil, string col){
	unsigned short fila=atoi(fil.c_str()),columna=atoi(col.c_str());
	if(terreno[fila-1][columna-1]==PODRIDO || terreno[fila-1][columna-1]==RECUPERACION){
		cout<<"El terreno esta podrido o en recuperacion. Intente luego."<<endl;
	}
	else
	if(terreno[fila-1][columna-1]==VACIO)
	{
	    cout<<"Esa region esta vacia..."<<endl;
	}
    else
    {
	    cout<<"Se ingreso una posicion por fuera del terreno."<<endl;
	}



}


