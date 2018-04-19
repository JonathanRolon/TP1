#include <string>
#include "granjerosLib.h"
#include <cstdlib>
#include <iostream>
using namespace std;

bool validarOpcion(string opMenu)
{
	bool opcionValida=false;
    char num='1';
    if(opMenu.length()==1)
    {
		int i=0;
		while(i<6 && opcionValida==false)
		{
			if(num==opMenu[0])
			{
				opcionValida=true;
			}
			num++;
			i++;
		}
    }
	return opcionValida;
}

bool validarCultivo(string cultivo,Cultivo cultivos[])
{
	bool cultivoValido=false;
	if(cultivo.length()==1)
	{
		int i=0;
		while(!cultivoValido && i<3)
		{
			if(cultivo[0]==cultivos[i].nombre)
			{
				cultivoValido=true;
			}
			i++;
		}
	}
	return cultivoValido;
}

bool posicionValida(string fila, string columna, char terreno[][TOPE_MATRIZ],
		            bool cosechando,bool regando)
{
	bool posVal=true;
	unsigned fil=atoi(fila.c_str()),col=atoi(columna.c_str());

	if((fil>=1 && fil<=5) && (col>=1 && col<=5))
	{
		if(terreno[fil-1][col-1]!=VACIO && !cosechando && !regando)
		{
			posVal=false;
		}
		else
		if(cosechando && !regando)
		{
			char parcela=terreno[fil-1][col-1];
			if(parcela==PODRIDO || parcela==VACIO || parcela==RECUPERACION)
			{
				posVal=false;
			}
		}
	}
	else
	{
		posVal=false;
	}
	return posVal;
}

bool validarCant(string cantidad,Jugador *unJugador,Cultivo cultivos[],unsigned tipoCultivo)
{
	bool cantidadValida=false;
	unsigned cant=atoi(cantidad.c_str());
	if(cant>=1 && cant<=MAX_SEMILLAS)
	{
		 if(unJugador->monedas>=(cant*(cultivos[tipoCultivo].precioSemilla)))
		 {
			 cantidadValida=true;
		 }
	}
	return cantidadValida;
}


bool cosechable(char tiempoCosecha[][TOPE_MATRIZ],unsigned short fila,
		        unsigned short columna)
{
	bool esCosechable=false;
	if(tiempoCosecha[fila-1][columna-1]==0)
	{
		esCosechable=true;
	}
	return esCosechable;
}
