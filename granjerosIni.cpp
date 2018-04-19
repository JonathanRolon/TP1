#include "granjerosLib.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

void actualizarEstadoParcelas(char terreno[][TOPE_MATRIZ],char tiempoRecu[][TOPE_MATRIZ],
			         	      char tiempoCosechado[][TOPE_MATRIZ])
{
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			if(tiempoRecu[i][j]>0)
			{
				tiempoRecu[i][j]--;
			}
			else
			if(tiempoRecu[i][j]==0)
			{
				terreno[i][j]=VACIO;
			}
			if(tiempoCosechado[i][j]>0)
			{
				tiempoCosechado[i][j]--;
			}
		}
	}
}

void inicializar(char terreno[][TOPE_MATRIZ],char tiempoRecu[][TOPE_MATRIZ],
		         char tiempoCose[][TOPE_MATRIZ],bool terrenoRiego[][TOPE_MATRIZ],
				 Cultivo cultivos[],Jugador *unJugador)
{
	inicializarParcelas(terreno);
	inicializarParcelas(tiempoRecu);
	inicializarParcelas(tiempoCose);
	inicializarParcelasRiego(terrenoRiego);
	inicializarSemillas(cultivos);
	inicializarJugador(unJugador,cultivos);
}


void inicializarJugador(Jugador *unJugador,Cultivo cultivos[])
{
	unJugador->monedas=50;
	unJugador->tanqueAgua=0;
	unJugador->turnosJuego=10;
	for(int i=0;i<3;i++)
	{
		unJugador->semillas[i].unidadesSemilla=0;
		unJugador->semillas[i].nombre=cultivos[i].nombre;
	}
}

void inicializarParcelasRiego(bool terrenoRegado[][TOPE_MATRIZ])
{
	for(int i=0;i<TOPE_MATRIZ;i++)
	{
		for(int j=0;j<TOPE_MATRIZ;j++)
		{
			terrenoRegado[i][j]=false;
		}
	}
}

void inicializarSemillas(Cultivo cultivos[])
{
	char nombre;
	unsigned short precio,tiempoCosecha,tiempoRecup,rentabilidad;
	ifstream archivoCultivos( "cultivos.dat", ios::in);
	if (!archivoCultivos)
	{
		cout << "Error al intentar cargar cultivos" << endl;
		exit(1);
	}
	int i=0;
	//mientras no sea el fin de archivo lee un registro y guarda en vector de cultivos.
	while(!archivoCultivos.eof())
	{
		archivoCultivos>>nombre>>precio
		>>tiempoCosecha>>tiempoRecup>>rentabilidad;
		cultivos[i].nombre=nombre;
		cultivos[i].precioSemilla=precio;
		cultivos[i].tiempoCosecha=tiempoCosecha;
		cultivos[i].tiempoRecuperacion=tiempoRecup;
		cultivos[i].rentabilidad=rentabilidad;
		i++;
	}
	archivoCultivos.close();
}

void inicializarParcelas(char terreno[][TOPE_MATRIZ])
{
	for(int i=0;i<TOPE_MATRIZ;i++)
	{
		for(int j=0;j<TOPE_MATRIZ;j++)
		{
			terreno[i][j]=VACIO;
		}
	}
}


