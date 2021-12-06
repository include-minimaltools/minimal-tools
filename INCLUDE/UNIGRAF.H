/* unigraf.h -- archivo encabezador para la biblioteca UNIGRAF
      Incluya esta en su programa si se va a usar una funcion de UNIGRAF.

   Aqui se definen:
      los prototipos de todas las funciones de UNIGRAF
      las constantes macros para usar en aquellas funciones
      los tipos de datos que se usan en aquellas funciones
*/

#ifndef _UNIGRAF		/* evitar recompilacion		*/
#define _UNIGRAF		/* indica que ya esta incluido */
/*********** equivalencias para compatibilidad con version anterior ****/
#if 0
   #define grEntrar(adap,modo)  graf_entrar (adap, modo)
   #define grSalir graf_salir
   #define vent_parafo vent_parrafo
#endif
/***************************** constantes utiles *************************/
#define FALSO 0
#define VERDAD 1

/******************************* tipos de datos *************************/
/****** primitivos y figuras geometricas *********/
typedef struct {
   int x, y;			/* coordenadas (x,y) de un punto fisico */
} PuntoCF;

typedef struct {
   double x, y;			/* las coordenadas (x,y) de un punto 2D	*/
} Punto2D;

typedef struct {
   double x, y, z;		/* las coordenadas (x,y,z) del punto 3D	*/
} Punto3D;

typedef struct {	/* arista se define con indices de 2 vertices */
   unsigned i_p1, i_p2;
} Arista;

/* figura 3D:
   * se compone de un conjunto de vertices, que tienen aristas
     que conectan los puntos
   * la idea es evitar la redefinicion de vertices para facilitar la
     transformacion de la figura
*/
typedef struct {
   int n_vrt;   		 /* # de vertices total 		*/
   Punto3D *vrt;		 /* coordenadas de los vertices		*/
   int n_arst;			 /* # de aristas total			*/
   Arista *arst;		 /* indices de los puntos en cada arista */
} t_figura3D;

enum Plano {PLANO_XY, PLANO_XZ, PLANO_YZ};
enum Ejes {EJE_X, EJE_Y, EJE_Z};

/* color */
typedef struct {
   char r, v, a;		/* valores r, v, a para definir un color */
} RVA;
/********* transformaciones ***********/
/* matrices de transformacion 2D y 3D
   el orden de las subindices es [fila][columna]
*/
#define ALT_MAT 3
#define ANCH_MAT 3
#define ALT_MAT3D 4
#define ANCH_MAT3D 4
typedef double MatXfrm[ALT_MAT][ANCH_MAT];       	/* matriz 2D */
typedef double MatXfrm3D[ALT_MAT3D][ANCH_MAT3D]; 	/* matriz 3D */
typedef struct {    /* estructura para guardar un pedazo del fondo */
   int x1, y1;
   void *buf;
} t_fondo;

/* ventana para la definicion de la transformacion de vision */
typedef struct {
   double x1, y1, x2, y2;
} t_ventana;

typedef t_ventana t_lineaCM;	/* linea de (x1,y1) a (x2,y2) */

   /* etiquetas para las clases de transformaciones en el tipo DefXfrm3D */
enum Transformaciones {
   ETIQ_TRASL2D = 1, ETIQ_TRASL3D,
   ETIQ_ESCAL2D, ETIQ_ESCAL3D,
   ETIQ_ROTAC2D, ETIQ_ROTAC3D_X, ETIQ_ROTAC3D_Y, ETIQ_ROTAC3D_Z,
   ETIQ_CORTE2D_X, ETIQ_CORTE2D_Y,
   ETIQ_CORTE3D_X, ETIQ_CORTE3D_Y, ETIQ_CORTE3D_Z,
   ETIQ_MATRIZ2D, ETIQ_MATRIZ3D, 	/* matriz de transformacion */
   ETIQ_PARALELA,			/* proyeccion en paralela 	*/
   ETIQ_PERSPECTIVA			/* proyeccion en perspectiva	*/
};
	/* proyecciones */
typedef struct {   		/* proyecccion en perspectiva 		*/
   double distz;
} PrycnPerspectiva;

typedef struct {		/* proyeccion paralela			*/
   double lon;			/* longitud de la proyeccion		*/
   double ang;			/* angulo en grados de la proyeccion	*/
} PrycnParalela;

	/* las transformaciones basicas */
typedef struct {		/* definicion de xfrm de traslacion 2D 	*/
   double Tx, Ty;
} Trasl2D;

typedef struct {		/* definicion de xfrm de traslacion 3D 	*/
   double Tx, Ty, Tz;
} Trasl3D;

typedef struct {		/* definicion de xfrm de escalacion 2D	*/
   double Ex, Ey;
} Escal2D;

typedef struct {		/* definicion de xfrm de escalacion 3D	*/
   double Ex, Ey, Ez;
} Escal3D;

typedef struct {		/* definicion de xfrm de rotatcion 	*/
   double grados;		/* sirve para 2D o 3D x, y o z		*/
} Rotac;

typedef struct {		/* definicion de xfrm de corte 2D 	*/
   double a;			/* puede ser en direccion x o y		*/
} Corte2D;

typedef struct {		/* definicion de xfrm de corte 3D 	*/
   double a, b;			/* puede ser en direccion x, y o z	*/
} Corte3D;

   /* Estructura de una Transformacion 3D General:
      Se guardan solamente las parametros de la transformacion, pero
      no se guarda la matriz excepto en el caso de la matriz arbitraria.
   */
typedef struct {
   char etiq;		/* etiqueta = tipo de xfrm en la union "xf" */
   union {
      Trasl3D trasl;		/* traslacion */
      Escal3D escal;		/* escalacion */
      Rotac rotac;		/* rotacion */
      Corte3D corte;		/* corte */
      MatXfrm3D *matriz;	/* matriz arbitraria */
      PrycnParalela paralela;	/* proyeccion paralela */
      PrycnPerspectiva perspectiva; /* proyeccion perspectiva */
   } xf;
} DefXfrm3D;

   /* plano de proyeccion (usando angulo para definir direccion y) */
typedef struct {
   Punto3D prv;			/* punto de referencia de vision (origen) */
   Punto3D N;			/* vector normal del plano */
   double ang;			/* angulo con eje Y */
} PlanoPrycnAng;

   /* plano de proyeccion (usando vector para definir direccion y) */
typedef struct {
   Punto3D prv;			/* punto de referencia de vision (origen) */
   Punto3D N;			/* vector normal del plano */
   Punto3D V;			/* vector de la direccion Y */
} PlanoPrycnVec;

/****************************  funciones de control ************************/
void graf_entrar (int adaptador, int modo);
   #define MODO_DEFECTO -1  /* para seleccionar adaptador/modo por defecto */
void graf_salir (int detenerse);
   #define DETENERSE VERDAD
   #define NO_DETENERSE FALSO
void probarErr (char *nombreFn);
void pop_cntxgraf (void);
void push_cntxgraf (int banderas_atrib);
   /* banderas de bits para salvar el contexto grafico (push/pop_cntxgraf) */
   #define CNTX_COLOR       0x01
   #define CNTX_POSICION    0x02
   #define CNTX_LINEA       0x04
   #define CNTX_TEXTO       0x08
   #define CNTX_RELLENO     0x10
   #define CNTX_PUERTO      0x20
   #define CNTX_CURSOR      0x40
   #define CNTX_VENTTEXT    0x80
   #define CNTX_TV         0x100
   #define CNTX_TODO       0x1FF

void *obt_mem_asegurada (unsigned nbytes, char *nombre);

/***************************** funciones del BIOS **************************/
void bios_fij_modo (int modo);
   /* modos de video para el BIOS */
#define MODO_40x25_COLOR         0x00
#define MODO_80x25_COLOR         0x02
#define MODO_320x200x2           0x04
#define MODO_640x200x1           0x06
#define MODO_80x25_MONO          0x07
#define MODO_320x200x4           0x0D
#define MODO_640x200x4           0x0E
#define MODO_640x350x1           0x0F
#define MODO_640x350x4           0x10
#define MODO_640x480x1           0x11
#define MODO_640x480x4           0x12
#define MODO_320x200x8           0x13

int bios_leer_modo (void);
void bios_pixel (int x, int y, int color);
void bios_escr_pixel (int x, int y, int color);
int bios_leer_pixel (int x, int y);
void bios_line (int x0, int y0, int x1, int y1, int color);
int far *dir_mem_video (void);

/**************** funciones de E/S y ventanas de texto *********************/
int leerCar (void);
   /* ventanas de texto */
void vent_frase (int x, int y, char *frase);
void vent_parrafo (int x, int y, char *parrafo[]);
int vent_frase_tmp (int x, int y, char *frase, int anadir_peticion);
#define CON_PETICION 1		/* valores para vent_frase_tmp */
#define SIN_PETICION 0
int vent_msj_err (char *nombre, char *mensaje, int tipoErr);
   enum TipoDeError {ERR_AVISO, ERR_NORMAL, ERR_FATAL};
int vent_parrafo_tmp (int x, int y, char *parrafo[]);
t_fondo * vent_frase_ret (int x, int y, char *frase);
t_fondo * vent_parrafo_ret (int x, int y, char *parrafo[]);
void restaurar_fondo (t_fondo *fondo);
void esperar_tecla (int x, int y);
void fij_estilo_vent (int fuente, int tamano, int colTexto, int colFondo);
void obt_estilo_vent (int *fuente, int *tamano, int *colTexto, int *colFondo);
void fij_just_vent (int justHoriz, int justVert);
void obt_just_vent (int *justHoriz, int *justVert);
void tam_vent_frase (char *frase, int anadir_peticion, int *anch, int *alt);
void tam_vent_parrafo (char *parrafo[], int *anch, int *alt);

/***************************** menues **********************************/
int menu_barras (int x1, int y1, int opc, char *descr[], unsigned opciones);
	/* para el parametro "opciones" */
#define MNU_DIB 1		/* V => dibujar el menu 		*/
#define MNU_RST 2		/* V => restaurar el fondo		*/
#define MNU_SEL 4		/* V => seleccionar interactivamente 	*/

int manejar_barras (int opc, int ncol, int nfil, int barIzq, int barSup,
   int anchBar, int altBar, int brchx, int brchy);
int selec_patron ( int pat, int x1, int y1, int x2, int y2,
   int ncol, int opciones);

/************************** funciones de interaccion **********************/
void xor_cursor (int x, int y);
#define poner_cursor(X,Y)  xor_cursor (X,Y)
#define borrar_cursor(X,Y) xor_cursor (X,Y)
int ubicar_punto (int *x, int *y);
int estirar_rect (int x1, int y1, int *x2, int *y2);
int arrastrar_rect (int *x1, int *y1, int *x2, int *y2);
int selec_area (int *x1, int *y1, int *x2, int *y2, int *modo);
   #define MOD_ESTIRAR 1   	/* modos para selec_area */
   #define MOD_ARRASTRAR 2
void xor_rect (int x1, int y1, int x2, int y2);
void xor_rect_quebrado (int x1, int y1, int x2, int y2);
void fij_rango_crs (int izq, int sup, int der, int inf);
void obt_rango_crs (int *izq, int *sup, int *der, int *inf);
void fij_atr_crs (int tamCrs, int XORval);
void obt_atr_crs (int *tamCrs, int *XORval);
void fij_veloc_crs (int velocNorm, int velocAcel);
void obt_veloc_crs (int *velocNorm, int *velocAcel);
int potenciometro (int x1, int y1, int x2, int y2,
   int minval, int maxval, int incr, int *val, int opciones);

/******************* funciones de graficas matematicas *********************/
void intervalo_graf1 (double max, double *intervalo, int *nintrv);
void intervalo_graf2 (double min, double max, double *inic,
      double *intervalo, int *nintrv);
int grfnmat (int xizq_f, int ysup_f, int xder_f, int yinf_f,
   int npts, double xmin_m, double xmax_m, double (*f)(double x));
int ejes (int *xizq_f, int *ysup_f, int *xder_f, int *yinf_f,
   double xmin_m, double xmax_m, double ymin_m, double ymax_m,
   double *xorg_m, double *yorg_m, double *escalaX, double *escalaY);


/************************ transformaciones basicas **********************/
MatXfrm * hacer_trasl (double Tx, double Ty, MatXfrm *mat);
MatXfrm * hacer_escal (double Sx, double Sy, MatXfrm *mat);
MatXfrm * hacer_rotac (double grados, MatXfrm *mat);
MatXfrm * hacer_corte_x (double fact_y, MatXfrm *mat);
MatXfrm * hacer_corte_y (double fact_x, MatXfrm *mat);
MatXfrm * hacer_ident (MatXfrm *mat);
MatXfrm * hacer_escal_rel (double Sx, double Sy, int cx, int cy,
      MatXfrm *mat);
MatXfrm * hacer_rotac_rel (double grados, int cx, int cy, MatXfrm *mat);
MatXfrm *invertir_xfrm (MatXfrm *mat);
MatXfrm * copiar_mat (MatXfrm *matdst, MatXfrm *matfnt);
int *poli2D_a_CF (int npts, double *poli2D, int *poliCF);
void impr_mat (MatXfrm *mat);
MatXfrm * componer_xfrm (MatXfrm *m1, MatXfrm *m2, MatXfrm *m3);
void transformar_poli (int npts, double poli[], MatXfrm *xfrm);
#define Transformar_pto2D(x ,y ,xfrm) { \
      double _tmpx = x; \
      x = x * (*xfrm)[0][0] + y * (*xfrm)[1][0] + (*xfrm)[2][0]; \
      y = _tmpx * (*xfrm)[0][1] + y * (*xfrm)[1][1] + (*xfrm)[2][1]; \
   }

/*************************** transformaciones 3D **************************/
MatXfrm3D * hacer_ident3D (MatXfrm3D *mat);
MatXfrm3D * hacer_trasl3D (double dx, double dy, double dz, MatXfrm3D *mat);
MatXfrm3D * hacer_escal3D (double ex, double ey, double ez, MatXfrm3D *mat);
MatXfrm3D * hacer_rotac3Dx (double teta, MatXfrm3D *mat);
MatXfrm3D * hacer_rotac3Dy (double teta, MatXfrm3D *mat);
MatXfrm3D * hacer_rotac3Dz (double teta, MatXfrm3D *mat);
MatXfrm3D * hacer_corte3Dx (double x_y, double x_z, MatXfrm3D *mat);
MatXfrm3D * hacer_corte3Dy (double y_x, double y_z, MatXfrm3D *mat);
MatXfrm3D * hacer_corte3Dz (double z_x, double z_y, MatXfrm3D *mat);
MatXfrm3D * invertir_xfrm3D (MatXfrm3D *mat);
MatXfrm3D * copiar_mat3D (MatXfrm3D *matdst, MatXfrm3D *matfnt);
MatXfrm3D * componer_xfrm3D (MatXfrm3D *m1, MatXfrm3D *m2, MatXfrm3D *m3);
MatXfrm3D * mat2D_a_3D (MatXfrm *m2D, MatXfrm3D *m3D);
void impr_mat3D (MatXfrm3D *mat);
int * poli3D_a_CF (int npts, double *fig3D, int *poliCF);
double * poli3D_a_2D (int npts, double *poli3D, double *poli2D);
double * transformar_poli3D (int npts, double poli[], MatXfrm3D *xfrm);
#define Transformar_pto3D(x ,y ,z ,xfrm) { \
      double _tmpx = x; \
      double _tmpy = y; \
      x = x * (*xfrm)[0][0] + y * (*xfrm)[1][0] + z * (*xfrm)[2][0] + (*xfrm)[3][0]; \
      y = _tmpx * (*xfrm)[0][1] + y * (*xfrm)[1][1] + z * (*xfrm)[2][1] +(*xfrm)[3][1]; \
      z = _tmpx * (*xfrm)[0][2] + _tmpy * (*xfrm)[1][2] + z * (*xfrm)[2][2] +(*xfrm)[3][2]; \
   }

/*********************** operacion de visualizacion *********************/
int recortar_cm (double *x1, double *y1, double *x2, double *y2);
int recortar_cf (int *x1, int *y1, int *x2, int *y2);
void def_ventana (double vx1, double vy1, double vx2, double vy2);
int obt_ventana (double *x1, double *y1, double *x2, double *y2);
void def_puerto_cf (double px1, double py1, double px2, double py2);
int obt_puerto_cf (double *x1, double *y1, double *x2, double *y2);
void def_puerto_cn (double px1, double py1, double px2, double py2);
int obt_puerto_cn (double *x1, double *y1, double *x2, double *y2);
MatXfrm * hacer_Tv (MatXfrm *Tv);
MatXfrm * hacer_Tv_inversa (MatXfrm *Tvi);
#define Tv_xy(x, y)  {  \
      extern MatXfrm _Tv; \
      Transformar_pto2D (x, y, &_Tv); \
   }
#define Tv_poli(n, poli) { \
      extern MatXfrm _Tv; \
      transformar_poli (n, poli, &_Tv); \
   }
MatXfrm3D * hacer_proy_paralela (double L, double theta_grad, MatXfrm3D *mat);
int perspectiva_poli (double distz, int npts, double poli[]);
int perspectiva_pto (double distz, double *x, double *y, double *z);
MatXfrm3D * norm_coords_yAng (double Px, double Py, double Pz,
      double Nx, double Ny, double Nz, double angV, MatXfrm3D *mat);
MatXfrm3D * norm_coords_yVec (double Px, double Py, double Pz,
      double Nx, double Ny, double Nz, double Vx, double Vy, double Vz,
      MatXfrm3D *mat);
MatXfrm3D * norm_vol_persp (double centro, double planoLejano, double vx1,
      double vy1, double vx2, double vy2, MatXfrm3D *mat);

/*********************** funciones de manejo de color ******************/
void escala_color_VGA (int vpInic, int nvp, int r0, int v0, int a0,
      int r1, int v1, int a1);
void escala_gris_VGA (int inicDAC);
void mapear_paleta_DAC (int inicPal, int inicDAC, int nColores);
void bios_leer_DAC (int indiceDAC, int *rojo, int *azul, int *verde);
void bios_escr_DAC (int dacreg, int r, int v, int a);
void bios_cargar_DAC (int nEntradas, unsigned char *DACbuf);
void bios_fij_modo_DAC (int modoDAC);
   #define DAC_MODO_4x64 0		/* modos para bios_fij_modo_DAC */
   #define DAC_MODO_16x16 1
void bios_fij_pagina_DAC (int paginaDAC);
int bios_obt_pagina_DAC (void);
int bios_obt_modo_DAC (void);
int convertir_TIS_RVA (double t, double i, double s, int *r, int *v, int *a,
      int maxValPal);
int correccionGama (int intervalos, int j, double Imin, double gama);
int DAC_ajustar_val (int valorDeDAC);

/**************************** planos de bits *******************************/
void visualizarPlanoDeBits (int pb, RVA *colFondo, RVA *colImagen);
void priorizarPlanoDeBits (int pb, RVA *rva);
void ocultarPlanoDeBits (int pb);
void jerarquizarPlanosDeBits (int pri0, int pri1, int pri2, int pri3,
   RVA *col0, RVA *col1, RVA *col2, RVA *col3, RVA *colFondo);
#define Fijar_pixel_pb(x,y,plano) \
        (putpixel (x, y, getpixel (x, y) | posnBit[plano]))
#define Borrar_pixel_pb(x,y,plano) \
        (putpixel (x, y, getpixel (x, y) & ~posnBit[plano]))
#define Pixel_pb(x,y,plano,nuval) \
   putpixel (x, y, (nuval ? getpixel (x, y) | posnBit[plano] : \
                            getpixel (x, y) & ~posnBit[plano]));

/*********************** funciones matematicas auxiliares ******************/
double atan360 (double dx, double dy);

/***************************** funciones varias *************************/
/* redirigir llamadas a Drawpoly para evitar error en Turbo C drawpoly
   Vease la funcion Drawpoly.c para mas informacion.
*/
#define drawpoly(N,POLI) Drawpoly (N,POLI)
void Drawpoly (int npuntos, int poli[]);

/***************************** macros utiles *****************************/
#define signo(X) (X < 0 ? -1 : 1)
/*  probar signo de un real: regresa 0 si es cerca a cero, de otro modo
    regresa -1 o 1 segun el signo
*/
#define SIGNO_REAL(X) \
	((X) < -CERO_REAL_APROX ? -1 : ((X) < CERO_REAL_APROX ? 0 : 1))

/*********************** Codigos de Error Regresados **********************/
   /* codigos de retorno  de menu_barras, manejar_barras, selec_patron */
#define MNU_NO_SELEC -1		/* valor retornado si teclee ESCAPE */
#define ERR_MENU -2		/* codigo de error en menu_barras */
   /* errores que se regresan de grfnmat */
#define ERR_RNG_CERO -3	      /* rango en x o y es menor que el minimo */
#define ERR_NO_ESP -4	      /* no hay espacio para realizar la grafica */

#endif 		/* ifndf _UNIGRAF	*/
