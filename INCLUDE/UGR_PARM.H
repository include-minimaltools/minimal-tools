/* ugr_parm.h -- variables y parametros para ser incluida en las funciones
      de la biblioteca unigraf
*/
#include "unigraf.h"	/* este arch. require defns de unigraf.h */

/* variables globales definidas en var_glob.c */
extern int _xMax, _yMax, _maxColor; /* coords y color maximos		*/
extern int _crsIzq, _crsDer, _crsSup, _crsInf; /* rango del cursor	*/
extern int _crsLimAct;		/* V = rango del cursor activo		*/
extern int _fuenteVent, _tamTextoVent; /* fuente de texto para ventana	*/
extern int _colTextoVent, _colFondoVent; /* color de texto/fondo de vent. */
extern int _justHorizVent, _justVertVent; /* justificacion de ventanas	*/
extern int _tamCrs;		/* tamano de un braso del cursor de cruz */
extern int _XORval;		/* valor que se usa para XOR cursor, etc. */
extern int _pasoCrs;		/* # pixeles que el cursor avanza cada paso */
extern int _pasoCrsAcel; 	/* # de pixeles del cursor acelerado 	*/
extern t_ventana _vnt, _prt; 	/* ventana y puerto de vision 		*/
extern MatXfrm _Tv;		/* matriz de la transformacion de vision */
extern int _inicVent, _inicPuerto; /* banderas de inic. de vnt/prto 	*/
extern int _memDinReservada;	/* # bytes reservada en memoria dinamica */

/* tipo para el codigo de region en el recorte */
typedef union {
   int conjunto;
   struct {
      unsigned arriba: 1;	/* 1 = punto esta arriba de la ventana */
      unsigned abajo: 1;	/* 1 = esta abajo de la ventana */
      unsigned izquierda: 1;	/* 1 = esta a la izquierda de la ventana */
      unsigned derecha : 1; 	/* 1 = esta a la derecha de la ventana */
   } bit;
} CodRegion;

/* parametros de interaccion */
#define LONG_GUION 4    /* longitud del guion para rectangulo quebrado */
#define XORVAL_DEF (0X008) /* valor por defecto de _XORval */
#define PASOCRS_DEF 4   /* paso del cursor por defecto */
#define MAX_PASOCRS 50  /* maximo paso del cursor */
#define TAMCRS_DEF 5    /* tamano del cursor por defecto */
#define MAX_TAMCRS 100  /* maximo tamano del cursor */

/* parameters de configuracion */
#define CAMINO_TC "c:\\utl\\tc20"	/* camino de Turbo C por defecto */
#define GR_ADAPTADOR VGA		/* adaptador grafico por defecto */
#define GR_MODO VGAHI		        /* modo grafico por defecto */
   /* bytes de memoria dinamica "intocables" por la fn. obt_mem_asegurada */
#define MEM_DIN_RESERVADA 1024

/* parametros de graficas matematicas (funcion graf_fnmat) */
#define MIN_RANGO (1.0E-100)  /* minimo rango absoluto para graficar */
#define MIN_TAM_CUADRO 80    /* tamano minimo para el cuadro entero */
#define MIN_TAM_GRAF 40	      /* tamano minimo para el cuadro de la grafica */

/* parametros de ventanas de texto */
#define FUENTEVENT_DEF SMALL_FONT  	/* fuente de texto por defecto	*/
#define TAMTEXTVENT_DEF 4	   	/* tamano de texto por defecto	*/
#define COLTEXTVENT_DEF 0		/* color de texto por defecto	*/
#define COLFONDOVENT_DEF 15		/* color del fondo por defecto 	*/
#define JUSTHORIZVENT_DEF LEFT_TEXT	/* just. horiz por defecto	*/
#define JUSTVERTVENT_DEF TOP_TEXT	/* just. vert. por defecto	*/
#define SALVAR_FONDO 1			/* parametro a vent_text	*/
#define NO_SALVAR_FONDO 0		/* paremetro a vent_text	*/
#define FCT_MARGEN_VRT 1		/* margen vert. de vent. en cars */
#define FCT_MARGEN_HOR 2	  	/* margen horiz. de vent. en cars */

/* parametros de transformacion */
#define PERSP_MIN_DIST 0.00001 	/* min dist del centro de proyeccion */

/************************* funciones macros *****************************/
   /* hacer la operacion XOR en un pixel (x,y) usando el patron _XORval */
#define XORpixel(X,Y,PATRON) putpixel (X, Y, getpixel (X, Y) ^ PATRON)
   /* fn booleana: si coord esta dentro del rango del cursor */
#define en_rango_crs(X,Y) (!_crsLimAct || (X>=_crsIzq && X<=_crsDer && \
					  Y<=_crsInf && Y>=_crsSup ))
#define redondear(X) ((int) (X < 0.0 ? (X - 0.5) : (X + 0.5)))

   /* marcros para intercambiar dos variables de un tipo determinado */
#define SWAP_I(a,b) {int tmp = a; a = b; b = tmp;}
#define SWAP_F(a,b) {float tmp = a; a = b; b = tmp;}
#define SWAP_D(a,b) {double tmp = a; a = b; b = tmp;}

   /* macro para copiar un arreglo de cualquier tipo ("FD = Fuente,Dest) */
#define COPIAR_ARREGLO_FD(N,FUENTE,DEST) {\
      int i;  for (i = 0; i < N; i++)  DEST[i] = FUENTE[i]; }

/* funciones internas */
int _pasoAcel (int direccion);
t_fondo *vent_text (int x1, int y1, char *texto[], int salvFondo);
void esperar_tecla_texto (int x, int y, char *texto);

/* parametros matematicos */
   /* para comparar con cero, tomando en cuenta la imprecision
      En un sentido este es completamente arbitrario, pero es
      aproximadamente el tamanos de los errores que se introducen cuando
      se trabaja con numeros en el rango [1,32767].
   */
#define CERO_REAL_APROX  (1.0E-8)
#define ES_APROX_CERO(x) (fabs(x) < CERO_REAL_APROX)
