#include <iostream>
#include <cstdlib>
#include <fstream>
#include "granjerosLib.h"

using namespace std;

void jugarPartida()
{
	Jugador unJugador;
	Cultivo cultivos[3];
	bool juegoNuevo=true,juegoTerminado=false;
	char terreno[TOPE_MATRIZ][TOPE_MATRIZ];
	char tiempoRecu[TOPE_MATRIZ][TOPE_MATRIZ];
	char tiempoCosecha[TOPE_MATRIZ][TOPE_MATRIZ];
	bool terrenoRegado[TOPE_MATRIZ][TOPE_MATRIZ];
	while(!juegoTerminado)
	{
		if(juegoNuevo)
		{
			mostrarInicio();
			inicializar(terreno,tiempoRecu,tiempoCosecha,terrenoRegado,
					    cultivos,&unJugador);
			cout<<endl;
			juegoNuevo=false;
			arrojarDado(&unJugador);
		}
		menuOpciones(&unJugador,&juegoNuevo,&juegoTerminado,cultivos,
				     tiempoRecu,terreno,tiempoCosecha,terrenoRegado);
	}
	cout<<"Hasta la proxima .Gracias por jugar :D"<<endl<<"Desarrollador: 100137"<<endl;

}

void definirTurno(Jugador *unJugador,bool *juegoNuevo,char terreno[][TOPE_MATRIZ],
		          char tiempoRecu[][TOPE_MATRIZ],char tiempoCose[][TOPE_MATRIZ],
				  bool terrenoRiego[][TOPE_MATRIZ]){
	if(unJugador->turnosJuego>1)
	{
		(unJugador->turnosJuego)--;
		inicializarParcelasRiego(terrenoRiego);
		mostrarEstadoJuego(terreno,unJugador);
		arrojarDado(unJugador);
	}
	else
	{
		cout<<"Juego terminado."<<endl;
		mostrarGananciaTotal(*unJugador);
		(*juegoNuevo)=true;
	}
}

void definirSecadosPodridos(char terreno[][TOPE_MATRIZ],bool terrenoRegado[][TOPE_MATRIZ],
				    		char tiempoRecuperacion[][TOPE_MATRIZ], Cultivo cultivos[],
							char tiempoCosecha[][TOPE_MATRIZ])
{
	for(int i=0;i<TOPE_MATRIZ;i++)
	{
		for(int j=0;j<TOPE_MATRIZ;j++)
		{
			for(int tipoCultivo=0;tipoCultivo<3;tipoCultivo++)
			{
				if(terreno[i][j]==cultivos[tipoCultivo].nombre)
				{
					if(!terrenoRegado[i][j] && tiempoCosecha[i][j]!=0)
					{
						terreno[i][j]=RECUPERACION;
						tiempoRecuperacion[i][j]
						=cultivos[tipoCultivo].tiempoRecuperacion;
					}
					else
					if(tiempoCosecha[i][j]==0)
					{
						if(terreno[i][j]=='C')
						{
							terreno[i][j]=VACIO;
						}
						else
						{
							terreno[i][j]=PODRIDO;
							tiempoRecuperacion[i][j]=1;
						}
					}
				}
			}
		}
	}
}

void modificarTerrenoRegado(bool matrizRegado[][TOPE_MATRIZ],unsigned short fila,
							unsigned short columna)
{
	matrizRegado[fila-1][columna-1]=true;
}

void modificarTiempoCose(char tiempoCosecha[][TOPE_MATRIZ],unsigned short fila,
						 unsigned short columna,unsigned short tipoCultivo,
						 Cultivo cultivos[])
{
	tiempoCosecha[fila-1][columna-1]=cultivos[tipoCultivo].tiempoCosecha;
}

void plantar(char terreno[][TOPE_MATRIZ],Jugador *unJugador,unsigned short tipoCultivo,
			char tiempoCosecha[][TOPE_MATRIZ],Cultivo cultivos[], bool *posicionOk)
{
	string fil,col;
	cout<<"Ingrese la posicion en la que desea plantar"<<endl;
	cout<<"Ingrese fila"<<endl;
	cin>>fil;
	cout<<"Ingrese columna"<<endl;
	cin>>col;
	bool cosechando=false,regando=false;
	if(posicionValida(fil,col,terreno,cosechando,regando))
	{
		unsigned short fila=atoi(fil.c_str()),columna=atoi(col.c_str());
		unJugador->semillas[tipoCultivo].unidadesSemilla--;
		terreno[fila-1][columna-1]=unJugador->semillas[tipoCultivo].nombre;
		*posicionOk=true;
		modificarTiempoCose(tiempoCosecha,fila,columna,tipoCultivo,cultivos);
		cout<<"Se ha sembrado con exito!"<<endl;
	}
	else
	{
		unsigned short fila=atoi(fil.c_str()),columna=atoi(col.c_str());
		if(terreno[fila-1][columna-1]!=VACIO)
		{
			cout<<"No se puede plantar en esa posicion."<<endl;
		}
		else
		{
			cout<<"Se ingreso una posicion por fuera del terreno"<<endl;
		}
	}
}

void sembrar(Jugador *unJugador,char terreno[][TOPE_MATRIZ],Cultivo cultivos[],
		     char tiempoRecu[][TOPE_MATRIZ],char tiempoCosecha[][TOPE_MATRIZ])
{
	string seguirSembrando="S";
	while(seguirSembrando=="S")
	{
		mostrarCultivos(cultivos);
		string cultivo=pedirCultivo();
		bool posicionOk=false;
		unsigned short tipoCultivo=buscarTipoCultivo(cultivo,cultivos);
		if(validarCultivo(cultivo,cultivos)
		   && unJugador->semillas[tipoCultivo].unidadesSemilla>0)
		{
			string fil,col;
			while(!posicionOk)
			{
				plantar(terreno,unJugador,tipoCultivo,tiempoCosecha,cultivos,&posicionOk);
			}
		}
		else
		{
			cout<<"Ingreso un cultivo inexistente o no posee semillas."<<endl;
		}
			cout<<"Desea seguir sembrando?S/N"<<endl;
			cin>>seguirSembrando;
	}
}

void riego(bool *posValida,char terreno[][TOPE_MATRIZ],Jugador *unJugador,
		    bool matrizRegado[][TOPE_MATRIZ],string fil,string col)
{
	*posValida=true;
	unsigned fila=atoi(fil.c_str()),columna=atoi(col.c_str());
	cout<<"Regando..."<<endl;
	char parcela=terreno[fila-1][columna-1];
	if(parcela=='A' || parcela=='B' || parcela=='C')
	{
		cout<<"El cultivo: "<<parcela<<" ha sido regado con exito"<<endl;
		unJugador->tanqueAgua--;
		modificarTerrenoRegado(matrizRegado,fila,columna);
	}
	else
	if(parcela==RECUPERACION)
	{
		cout<<"Parcela en recuperacion, intente en el siguiente turno"<<endl;
	}
	else
	{
		cout<<"......No paso nada"<<endl;
		modificarTerrenoRegado(matrizRegado,fila,columna);
		unJugador->tanqueAgua--;
	}
}

void regar(char terreno[][TOPE_MATRIZ], Jugador *unJugador,
		   bool matrizRegado[][TOPE_MATRIZ])
{
	string fil,col;
	bool posValida=false;
	if(unJugador->tanqueAgua>=1)
	{
		while(!posValida)
		{
			cout<<"Ingrese la posicion donde desea regar."<<endl;
			cout<<"Ingrese fila."<<endl;
			cin>>fil;
			cout<<"Ingrese columna."<<endl;
			cin>>col;
			bool regando=true,cosechando=false;
			if(posicionValida(fil,col,terreno,cosechando,regando)
			   && unJugador->tanqueAgua>0)
			{
				riego(&posValida,terreno,unJugador,matrizRegado,fil,col);
			}
			else
			{
				cout<<"Ingreso una posicion no valida o su tanque esta vacio."<<endl;
			}
		}
	}
	else
	{
		cout<<"No posee unidades de riego"<<endl;
	}
}

void aumentarGanancia(Jugador *unJugador,unsigned short tipoCultivo, Cultivo cultivos[])
{
	if(unJugador->monedas+cultivos[tipoCultivo].rentabilidad<=MAX_MONEDAS)
	{
		unJugador->monedas+=cultivos[tipoCultivo].rentabilidad;
	}
	else
	{
		unJugador->monedas=MAX_MONEDAS;
	}
}

void modificarTiempoRecu(char terreno[][TOPE_MATRIZ],char tiempoRecu[][TOPE_MATRIZ],
		                 unsigned short fila,unsigned short columna,Cultivo cultivos[],
						 unsigned short tipoCultivo)
{
	if(cultivos[tipoCultivo].tiempoRecuperacion>0)
	{
		tiempoRecu[fila-1][columna-1]=(cultivos[tipoCultivo].tiempoRecuperacion-1);
		terreno[fila-1][columna-1]=RECUPERACION;
	}
	else
	{
		terreno[fila-1][columna-1]=VACIO;
	}
}


void cosecho(string fil, string col,char terreno[][TOPE_MATRIZ],Jugador *unJugador,
		     char tiempoCosecha[][TOPE_MATRIZ],Cultivo cultivos[],
			 char tiempoRecu[][TOPE_MATRIZ])
{
	bool cosechando=true,regando=false;
	string cultivo;
	if(posicionValida(fil,col,terreno,cosechando,regando))
	{
		unsigned short fila=atoi(fil.c_str()),columna=atoi(col.c_str());
		if(cosechable(tiempoCosecha,fila,columna))
		{
			cultivo=terreno[fila-1][columna-1];
			int tipoCultivo=buscarTipoCultivo(cultivo,cultivos);
			aumentarGanancia(unJugador,tipoCultivo,cultivos);
			modificarTiempoRecu(terreno,tiempoRecu,fila,columna,cultivos,tipoCultivo);
			cout<<"Se ha cosechado con exito el cultivo: "<<cultivo<<endl
				<<"Monedas ganadas: "<<cultivos[tipoCultivo].rentabilidad<<endl;
		}
		else
		{
			cout<<"Aun no es tiempo de cosechar el cultivo: "
				<<terreno[fila-1][columna-1]<< endl <<"Tiempo restante de cosecha: "
				<<(int)tiempoCosecha[fila-1][columna-1]<<" turnos"<<endl;
		}
	}
	else
	{
		verPosicionElegida(terreno,fil,col);
	}
}

void cosechar(char terreno[][TOPE_MATRIZ],char tiempoRecu[][TOPE_MATRIZ],
		      Jugador *unJugador,Cultivo cultivos[],char tiempoCosecha[][TOPE_MATRIZ])
{
    string fil,col,opcion="S";
	while(opcion=="S")
	{
		cout<<"Ingrese la posicion donde cosechara"<<endl;
		cout<<"Ingrese fila"<<endl;
		cin>>fil;
		cout<<"Ingrese columna"<<endl;
		cin>>col;

		cosecho(fil,col,terreno,unJugador,tiempoCosecha,cultivos,tiempoRecu);
		do
		{
			cout<<"Seguir cosechando?S/N"<<endl;
			cin>>opcion;
			if(opcion!="S" && opcion!="N")
			{
				cout<<"opcion ingresada incorrecta"<<endl;
			}
		}
		while(opcion!="S"&& opcion!="N");
	}
}

void arrojarDado(Jugador *unJugador)
{

	unsigned short resultadoDado;
	string opcionDado;
	bool arrojo=false;
	while(!arrojo){
	cout << "Arroje el dado para obtener unidades de riego" << endl
		 << "1.Arrojar  dado de seis caras."<<endl
		 << "2.Paso. No quiero arrojar el dado"<<endl;
	cin>>opcionDado;
		if(opcionDado=="1"){
			cout<<"Arrojando el dado..."
			    << "El numero del dado es: "<<(resultadoDado = tirarDado())<<endl;
			calcularAguaTanque(unJugador,resultadoDado);
			arrojo=true;
		}
		else
		if(opcionDado=="2"){
			cout<<"No obtuvo unidades de riego..."<<endl;
			arrojo=true;
		}else{
			cout<<"Se ingreso una opcion incorrecta"<<endl;
		}
	}
}

void calcularAguaTanque(Jugador *unJugador,char resultadoDado)
{
	unsigned short potenciador;
	cout << "Potenciador!: " <<(potenciador = INCREM_AGUA * resultadoDado)<<endl;
		if(potenciador+unJugador->tanqueAgua>25)
		{
			unJugador->tanqueAgua=MAX_AGUA;
		}else
		{
			unJugador->tanqueAgua+=potenciador;
		}
		cout<<"Tanque de agua: "<< unJugador->tanqueAgua<<endl<<endl;
}

void tiendaSemillas(Jugador *unJugador,Cultivo cultivos[])
{
	if(unJugador->monedas>0)
	{
		cout<<"Bienvenido a la tienda de semillas!"<<endl<<"Precio por semilla:"<<endl;
		for(int i=0;i<3;i++)
		{
			cout<<(cultivos[i].nombre)<<": "<<(cultivos[i].precioSemilla)<<endl;
		}
		cout<<"Cantidad de monedas disponibles: "<<unJugador->monedas<<endl;
		comprar(unJugador,cultivos);
	}
	else{
		cout<<"Disculpe, no tiene mas monedas, vuelva mas tarde."<<endl;
	}
}

void comprar(Jugador *unJugador,Cultivo cultivos[])
{
	string cantSemi,opcionCultivo;
	bool ingresoOk=false,cantidadOk=false;
	while(!ingresoOk)
	{
		opcionCultivo=pedirCultivo();
		if(validarCultivo(opcionCultivo,cultivos)){
			compro(opcionCultivo,cantSemi,cultivos,unJugador,&cantidadOk,&ingresoOk);
		}
		else
		{
			cout<<"El cultivo ingresado no es valido"<<endl;
		}
	}
}

void compro(string opcionCultivo,string cantSemi,Cultivo cultivos[],
		    Jugador *unJugador,bool *cantidadOk,bool *ingresoOk)
{

	unsigned tipoCultivo=buscarTipoCultivo(opcionCultivo,cultivos);
	while(!*cantidadOk){
		*ingresoOk=true;
		cout<<"Ingrese la cantidad de semillas a comprar"<<endl;
		cin>>cantSemi;
		if(validarCant(cantSemi,unJugador,cultivos,tipoCultivo))
		{
			*cantidadOk=true;
			unsigned cant=atoi(cantSemi.c_str());
			if(unJugador->semillas[tipoCultivo].unidadesSemilla+(cant)>MAX_SEMILLAS)
			{
				unJugador->semillas[tipoCultivo].unidadesSemilla=MAX_SEMILLAS;
			}
			else
			{
				unJugador->semillas[tipoCultivo].unidadesSemilla+=cant;
			}
			cout<<"Muy bien! Ha comprado "<<cantSemi<< " semillas de: "
			    <<cultivos[tipoCultivo].nombre<<endl<<endl;
			unJugador->monedas-=cultivos[tipoCultivo].precioSemilla*cant;
		 }
		else
		{
			cout<<"Se ingreso una cantidad no valida"<<endl;
		}
	}
}


unsigned buscarTipoCultivo(string cultivo, Cultivo cultivos[])
{
	char posicionCultivo;
	for(int i=0;i<3;i++)
	{
		if((cultivos[i].nombre)==cultivo[0])
		{
			posicionCultivo=i;
		}
	}
	return posicionCultivo;
}

char tirarDado()
{
	srand(time(NULL));
	return ( 1 + rand() % 6 );
}

void salir(bool *finJuego)
{
	*finJuego=true;
}





