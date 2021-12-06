/* term.h - definiciones del teclado y la pantalla
 */

/* codigos de caracteres ASCII */
#define ESCAPE 27
#define ENTER 13
#define PITO  7

/********** DEFINICION DE LAS TECLAS ESPECIALES DE LA PC ***************
    La PC usa un byte para trasmitir caracteres, pero el teclado y la
pantalla usan mas que 256 caracteres distintos. Entonces, hay un problema
de como represetar mas que 256 caracteres con 8 bits. Este se resuelve
usando dos bytes para algunos caracteres, llamados los "caracteres
extendidos". El primer de los dos bytes tiene valor 0 y el segundo byte se
llama el "codigo extendido". Entonces, si se recibe el valor 0 del
teclado, indica que el proximo byte representa un caracter extendido y no
un caracter ASCII normal. Por ejemplo, la flecha arriba envia la
combinacion 0,72. Por si mismo, el valor 72 significa "G", entonces, no
hay que confundirse.
    Para representar los caracteres en UNIGRAF, se usa un "int" en lugar
de un "char", lo que permite superar el problema de tener dos
representaciones distintas. Los valores 1-255 son caracteres normales. Los
caracteres extendidos se representan sumando 256 (bit 8) al codigo
extendido para dar un valor en el rango 257-511.
*/
/* Define bit 8 que se sum al codigo extendido para representar un
   caracter extendido. 
*/
#define BIT_COD_EXT 0x100
/* Se define este funcion macro para sacar el codigo extendido del teclado
   desde la representacion del caracter extendido.
*/
#define COD_EXT(COD_CAR) (COD_CAR & !BIT_COD_EXT)  /* para sacar el codigo

/* Teclas Varias Extendidas */
#define INICIO (71 | BIT_COD_EXT)
#define ARRIBA (72 | BIT_COD_EXT)
#define PG_ARRIBA (73 | BIT_COD_EXT)
#define IZQUIERDA (75 | BIT_COD_EXT)
#define DERECHA (77 | BIT_COD_EXT)
#define FIN (79 | BIT_COD_EXT)
#define ABAJO (80 | BIT_COD_EXT)
#define PG_ABAJO (81 | BIT_COD_EXT)
#define INSERTAR (82 | BIT_COD_EXT)
#define SUPRIMIR (83 | BIT_COD_EXT)

/* Las Teclas de Funcion F1-F10 */
#define CAR_F1 (59 | BIT_COD_EXT)
#define CAR_F2 (60 | BIT_COD_EXT)
#define CAR_F3 (61 | BIT_COD_EXT)
#define CAR_F4 (62 | BIT_COD_EXT)
#define CAR_F5 (63 | BIT_COD_EXT)
#define CAR_F6 (64 | BIT_COD_EXT)
#define CAR_F7 (65 | BIT_COD_EXT)
#define CAR_F8 (66 | BIT_COD_EXT)
#define CAR_F9 (67 | BIT_COD_EXT)
#define CAR_F10 (68 | BIT_COD_EXT)
#define CAR_ALTF1 (104 | BIT_COD_EXT)
#define CAR_ALTF2 (105 | BIT_COD_EXT)
#define CAR_ALTF3 (106 | BIT_COD_EXT)
#define CAR_ALTF4 (107 | BIT_COD_EXT)
#define CAR_ALTF5 (108 | BIT_COD_EXT)
#define CAR_ALTF6 (109 | BIT_COD_EXT)
#define CAR_ALTF7 (110 | BIT_COD_EXT)
#define CAR_ALTF8 (111 | BIT_COD_EXT)
#define CAR_ALTF9 (112 | BIT_COD_EXT)
#define CAR_ALTF10 (113 | BIT_COD_EXT)
#define CAR_MAYF1 (84 | BIT_COD_EXT)
#define CAR_MAYF2 (85 | BIT_COD_EXT)
#define CAR_MAYF3 (86 | BIT_COD_EXT)
#define CAR_MAYF4 (87 | BIT_COD_EXT)
#define CAR_MAYF5 (88 | BIT_COD_EXT)
#define CAR_MAYF6 (89 | BIT_COD_EXT)
#define CAR_MAYF7 (90 | BIT_COD_EXT)
#define CAR_MAYF8 (91 | BIT_COD_EXT)
#define CAR_MAYF9 (92 | BIT_COD_EXT)
#define CAR_MAYF10 (93 | BIT_COD_EXT)
#define CAR_CTLF1 (94 | BIT_COD_EXT)
#define CAR_CTLF2 (95 | BIT_COD_EXT)
#define CAR_CTLF3 (96 | BIT_COD_EXT)
#define CAR_CTLF4 (97 | BIT_COD_EXT)
#define CAR_CTLF5 (98 | BIT_COD_EXT)
#define CAR_CTLF6 (99 | BIT_COD_EXT)
#define CAR_CTLF7 (100 | BIT_COD_EXT)
#define CAR_CTLF8 (101 | BIT_COD_EXT)
#define CAR_CTLF9 (102 | BIT_COD_EXT)
#define CAR_CTLF10 (103 | BIT_COD_EXT)

/* atributos de caracteres en la memoria de video */
#define ATR_SUBR 0x01    /* atributo de subrayo                  */
#define ATR_NORM 0x07    /* atributo de texto normal             */
#define ATR_NEGR 0x0F    /* atributo de negrilla                 */
#define ATR_INVERS 0x70  /* atributo de video inverso            */
#define ATR_INTER 0x87   /* atributo de intermitencia            */
