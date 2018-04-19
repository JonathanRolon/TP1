#include <string>

#ifndef GRANJEROS_H_
#define GRANJEROS_H_

const char TOPE_MATRIZ = 5;
const char VACIO='#';
const char PODRIDO = 'P';
const char RECUPERACION = 'R';
const char INCREM_AGUA = 5;
const unsigned MAX_SEMILLAS=50;
const unsigned MAX_AGUA=25;
const unsigned MAX_MONEDAS=600;

/*Struct que contiene los atributos del cultivo*/
struct Cultivo
{
	char nombre;
	unsigned short precioSemilla,
	tiempoCosecha,
	tiempoRecuperacion,
	rentabilidad;
};

/*Struct que contiene atributos del cultivo que tiene el jugador*/
struct CultivoJugador
{
	char nombre;
	int  unidadesSemilla;
};

/*Struct que contiene atributos del jugador*/
struct Jugador
{
	unsigned monedas;
	unsigned tanqueAgua;
	unsigned short turnosJuego;
	CultivoJugador semillas[3];
};
/* post: Muestra bienvenida al juego*/
void mostrarInicio();

/* pre: Recibe un vector de cultivos.
 post: Devuelve vector inicializado segun valores de archivo leido*/
void inicializarSemillas(Cultivo semillas[]);

/* pre: Recibe una matriz cuadrada de tamaño TOPE_MATRIZ.
 post: Devuelve matriz inicializa en #*/
void inicializarParcelas(char terreno[][TOPE_MATRIZ]);

/* pre: Recibe la matriz cuadrada de tamaño TOPE_MATRIZ.
 post: Muestra el contenido de cada parcela de la matriz actual*/
void mostrarTerreno(char terreno[][TOPE_MATRIZ]);

/* pre: Recibe struct del jugador,booleano de juego nuevo,
        booleano de quitar juego, vector de cultivos,
        matriz de tiempo de recuperacion de parcelas.
 post: Muestra el menu de opciones del juego y accede a cada opcion*/
void menuOpciones(Jugador *unJugador,bool *juegoNuevo,bool *finJuego,
		          Cultivo cultivos[],char tiempoRecu[][TOPE_MATRIZ],
				  char terreno[][TOPE_MATRIZ],char tiempoCosecha[][TOPE_MATRIZ],
				  bool terrenoRiego[][TOPE_MATRIZ]);

/* pre: Recibe struct del jugador y resultado de tirar el dado.
 post: Modifica el agua del tanque del jugador*/
void calcularAguaTanque(Jugador *unJugador,char resultadoDado);

/* pre: Recibe struct del jugador.
 post: Pregunta si quiere arrojar el dado,
       si es si arroja y llama calcularAguaTanque, sino sale.*/
void arrojarDado(Jugador *unJugador);

/* pre: Recibe struct del jugador y vector de cultivos.
 post: muestra bienvenida a tienda y llama a comprar() */
void tiendaSemillas(Jugador *unJugador,Cultivo cultivos[]);

/* pre: Recibe cultivo y vector de cultivos.
 post: Devuelve posicion de cultivo en el vector*/
unsigned buscarTipoCultivo(std::string cultivo, Cultivo cultivos[]);

/* pre: Recibe struct del jugador y vector de cultivos.
 post: Pide ingreso de nombre de cultivo, si se ingreso bien llama a compro()*/
void comprar(Jugador *unJugador,Cultivo cultivos[]);

/* pre: Recibe struct del jugador, vector de cultivos,cantidad de semillas ingresada,
        nombre del cultivo,booleano de cantidad valida
        y booleano de ingreso de cultivo existente.
 post: Si se ingresa una cantidad valida de semillas
       modifica las semillas y monedas del jugador.*/
void compro(std::string opcionCultivo,std::string cantSemi,Cultivo cultivos[],
		    Jugador *unJugador,bool *cantidadOk,bool *ingresoOk);

/* pre: Pide ingresar un cultivo
 post: Devuelve el string*/
std::string pedirCultivo();

/* pre:Recibe struct del jugador,terreno actual,vector de cultivos,matriz de tiempo recuperacion,
       matriz de tiempo de cosecha.
 post:Pide ingresar el cultivo a sembrar si se ingreso bien llama a plantar()*/
void sembrar(Jugador *unJugador,char terreno[][TOPE_MATRIZ],Cultivo cultivos[],
		     char tiempoRecu[][TOPE_MATRIZ],char tiempoCosecha[][TOPE_MATRIZ]);

/* pre:Recibe struct del jugador,terreno actual,vector de cultivos,matriz de tiempo cosecha,
       posicion del cultivo en el vector de cultivos,booleano de posicion valida: fila y columna.
 post:Si se ingreso una posicion valida se planta el cultivo en el lugar, modificando tiempo
      de cosecha y unidades de semilla del cultivo plantado*/
void plantar(char terreno[][TOPE_MATRIZ],Jugador *unJugador,unsigned short tipoCultivo,
			char tiempoCosecha[][TOPE_MATRIZ],Cultivo cultivos[], bool *posicionOk);

/* pre: Recibe el terreno,el jugador,la matriz de estado de riego de parcelas.
 post:Sino hay agua en balde sale, sino si se ingresa posicion valida llama a riego()*/
void regar(char terreno[][TOPE_MATRIZ], Jugador *unJugador,
		   bool matrizRegado[][TOPE_MATRIZ]);

/* pre:Recibe si se ingreso una posicion valida, el terreno, jugador, matriz de estado riego,
       fila y columna ingresadas.
 post:modifica el estado de riego en matriz de riego y decrementa unidades de riego*/
void riego(bool *posValida,char terreno[][TOPE_MATRIZ],Jugador *unJugador,
		    bool matrizRegado[][TOPE_MATRIZ],std::string fil,std::string col);

/* pre:Recibe fila y columna ingresadas, terreno, jugador, tiempo de cosechado,
       vector de cultivos, tiempo de recuperacion de parcela;
 post:Si hay un cultivo cosechable en la posicion llama a aumentarGanancia()
      y llama a modificarTiempoRecu()*/
void cosecho(std::string fil, std::string col,char terreno[][TOPE_MATRIZ],
		     Jugador *unJugador,char tiempoCosecha[][TOPE_MATRIZ],
			 Cultivo cultivos[],char tiempoRecu[][TOPE_MATRIZ]);

/* pre:Recibe terreno,tiempo de recuperacion, jugador, vector de cultivos, tiempo de cosechado
 post:Pide ingresar posicion de cosechado y llama a cosecho()*/
void cosechar(char terreno[][TOPE_MATRIZ],char tiempoRecu[][TOPE_MATRIZ],
		      Jugador *unJugador,Cultivo cultivos[],char tiempoCosecha[][TOPE_MATRIZ]);

/* post:simula tirar un dado devolviendo un numero "aleatorio" entre 1 y 6*/
char tirarDado();

/* pre:Recibe fila, columna ingresadas, el terreno e indicadores si la funcion es
       llamada cuando se cosecha o riega.
 post:Devuelve true o false dependiendo del valor de cosechando, regando
      o posicion ingresada.*/
bool posicionValida(std::string fila, std::string columna,
				    char terreno[][TOPE_MATRIZ],bool cosechando,bool regando);

/* pre:Recibe el cultivo ingresado y el vector de cultivos.
 post:Devuelve true si es un cultivo existente*/
bool validarCultivo(std::string cultivo,Cultivo cultivos[]);

/* pre:Recibe el jugador,la posicion del cultivo en vector,vector de cultivos.
 post:Aumenta las monedas del jugador dependiendo del tipo de cultivo cosechado.*/
void aumentarGanancia(Jugador *unJugador,unsigned short tipoCultivo,Cultivo cultivos[]);

/* pre:Recibe el terreno, el tiempo de recuperacion, fila,columna ingresadas,
       posicion del cultivo en vector.
 post:Modifica la parcela en matriz tiempoRecu de acuerdo a posicion en vec cultivos*/
void modificarTiempoRecu(char terreno[][TOPE_MATRIZ],char tiempoRecu[][TOPE_MATRIZ],
		                 unsigned short fila, unsigned short columna,Cultivo cultivos[],
						 unsigned short tipoCultivo);

/* pre:Recibe matriz de cosecha , fila,columna validadas
 post:Devuelve true si tiempo de cosecha de cultivo es 0*/
bool cosechable(char tiempoCosecha[][TOPE_MATRIZ],unsigned short fila,
		        unsigned short columna);

/* pre:Recibe tiempo de cosechado, fila, columna validadas, vector de cultivos.
 post:Modifica el tiempo de cosechado segun tipo de cultivo en vector de cultivos*/
void modificarTiempoCose(char tiempoCosecha[][TOPE_MATRIZ],unsigned short fila,
						 unsigned short columna,unsigned short tipoCultivo,
						 Cultivo cultivos[]);

/* pre:Recibe matriz de terreno regado, fila y columa validadas.
 post:Modifica la parcela en matrizRegado a true en la posicion fila y columna.*/
void modificarTerrenoRegado(bool matrizRegado[][TOPE_MATRIZ],unsigned short fila,
		                    unsigned short columna);

/* pre:Recibe matriz estado de riego del terreno.
 post:Inicializa en false*/
void inicializarParcelasRiego(bool terrenoRegado[][TOPE_MATRIZ]);

/* pre:Recibe terreno, estado de riego de terreno,tiempo de recup,tiempo cosechado,
       vector de cultivos.
 post:Define cultivos secos y podridos en matriz terreno, si es podrido modifica
      tiempo de recuperacion de parcela*/
void definirSecadosPodridos(char terreno[][TOPE_MATRIZ],bool terrenoRegado[][TOPE_MATRIZ],
				    		char tiempoRecuperacion[][TOPE_MATRIZ], Cultivo cultivos[],
							char tiempoCosecha[][TOPE_MATRIZ]);

/* pre:Recibe todas las matrices, el jugador, y vector de cultivos.
 post:Llama a funciones inicializar dependiendo la estructura.*/
void inicializar(char terreno[][TOPE_MATRIZ],char tiempoRecu[][TOPE_MATRIZ],
				 char tiempoCose[][TOPE_MATRIZ],bool terrenoRiego[][TOPE_MATRIZ],
				 Cultivo cultivos[],Jugador *unJugador);

/* pre:Recibe jugador,variable indicadora de juego nuevo, terreno, tiempo de recup,
       tiempo de cosecha, terreno regado.
 post:Decrementa los turnos llamando a inicializar terreno de riego, mostrar estado
      del juego y arrojar el dado.Si turnos es 0 llama a mostrar ganancia. */
void definirTurno(Jugador *unJugador,bool *juegoNuevo,char terreno[][TOPE_MATRIZ],
        	      char tiempoRecu[][TOPE_MATRIZ],char tiempoCose[][TOPE_MATRIZ],
				  bool terrenoRiego[][TOPE_MATRIZ]);

/* pre: Recibe jugador y vector de cultivos;
 post:inicializa datos del jugador*/
void inicializarJugador(Jugador *unJugador,Cultivo cultivos[]);

/* pre:Recibe jugador.
 post:Muestra si se gano o no monedas*/
void mostrarGananciaTotal(Jugador unJugador);

/* pre:recibe opcion ingresada;
 post: devuelve true si es una opcion valida*/
bool validarOpcion(std::string opMenu);

/* pre:Recibe terreno, tiempo de recuperacion, tiempo hasta cosechar.
 post:decrementa el tiempo de recuperacion y de cosechado*/
void actualizarEstadoParcelas(char terreno[][TOPE_MATRIZ],char tiempoRecu[][TOPE_MATRIZ],
		                      char tiempoCosechado[][TOPE_MATRIZ]);

/*post: contiene el estructurado de una partida y sus funciones*/
void jugarPartida();

/* pre:Recibe el terreno de juego y el jugador.
 post:Muestra atributos del jugador y llama a mostrarTerreno() */
void mostrarEstadoJuego(char terreno[][TOPE_MATRIZ],Jugador *unJugador);

/* pre:Recibe una cantidad de semillas ingresada, el jugador, el vector de
       cultivos,y posicion en vector del cultivo.
 post:Devuelve true si la cantidad ingresada esta en el rango estimado
      y ademas las monedas del jugador son suficientes*/
bool validarCant(std::string cantidad,Jugador *unJugador,Cultivo cultivos[],
		         unsigned tipoCultivo);

/* pre:Recibe indicadora de fin de Juego
 post:La modifica con true*/
void salir(bool *finJuego);

/* pre:Recibe vector de cultivos
 post:Muestra los tres cultivos por pantalla*/
void mostrarCultivos(Cultivo cultivos[]);

/* pre:Recibe el terreno, fila y columna.
 post:Muestra una leyenda: si la parcela elegida esta en recuperacion,
      vacia o esta podrido el cultivo */
void verPosicionElegida(char terreno[][TOPE_MATRIZ],std::string fil, std::string col);

#endif
