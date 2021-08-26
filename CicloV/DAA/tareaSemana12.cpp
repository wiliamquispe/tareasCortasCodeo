/*
 * nomPrograma: codigoHuffman.cpp !!!!!CAMBIAR!!!!!!!!!
 * descripcion: Implementación en código de los algoritmos 
 *				a.Mergesort
 * 				b.Quicksort
 *       		c.Camino Ponderado
 *				d.Huffman
 *			
 * @autores: Grupo 3:
 *        Curay Chacón, Piero Yahir		   19200206
 *        Mejia Benito, Elphy Xavier	   19200032
 *        Quispe Ñaupa, Wiliam Luis		   19200205
 *        Valle Romero, Javier Eduardo     19200063
 *        Yalle Muñoz, Edgar Saul Junior   19200052
 * @fecha: 25/08/2021
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>

using namespace std;

const int maxsize = 100;
const int null = 0;

/*--------------- Registro de Nodo de Huffman ---------------*/
struct huff_node {
   char symbol;
   int freq;
   huff_node *parent;
   char childtype;
};


/*--------------- Registro de nodo de árbol ---------------*/
struct NODO{
	int val;
	struct NODO *izq;
	struct NODO *der;
};


typedef huff_node *ptr;

	/*--------------- PROTOTIPOS ---------------*/
/*--------------- Metodos delÁrbol ---------------*/
void crearArbol(NODO **raiz);
NODO* nuevoNodo(int dato);
void nuevoArbol(NODO **raiz, NODO* ramaIzq, int x, NODO* ramaDer);

/*                            Metodos de Camino Ponderado
-------------------------------------------------------------------------------*/
void comprobarArbolExtendido(NODO *raiz,bool &validado);
void calcularLCP(NODO *raiz, int &cont, int &caminoPon);
bool tieneAmbosHijos(NODO *raiz);
bool esHoja(NODO *raiz);
void opcionesMenuCPonderado();
void menuCPonderado();



	/*--------------- Metodos de Algoritmo de Huffman ---------------*/
/*--------------- Metodos básicos ---------------*/
void create(int k, ptr node[]);
void print(int k, ptr node[]);
void twosmall(ptr &p, ptr &q, int numnode, ptr node[]);


int leerNroSimbolos();
void crearSimbolos(int numsymbols, ptr node[]);
void ordenarHuffman(int numsymbols, ptr node[]);
void mostrartHuffman(int numsymbols, ptr node[]);


/*--------------- Menú ---------------*/
void menu();
void opcionesMenu();


int main() {
	/*
	ptr node[maxsize];
	int numsymbols;
	numsymbols = leerNroSimbolos();
	crearSimbolos(numsymbols, node);
	ordenarHuffman(numsymbols, node);
	mostrartHuffman(numsymbols, node);*/
	menu();
	system("pause");
	return(0);
}

/*--------------- DESARROLLO DE METODOS ---------------*/
void crearArbol(NODO **raiz)  //Inicializa la raiz con valor NULL
{
   *raiz=NULL;
}

NODO* nuevoNodo(int dato)     // Crea y retorna un nodo con un dato de tipo int y apuntadores izq y der NULL
{
   NODO *neo;
   neo=(NODO*)malloc(sizeof(NODO));
   neo->val = dato;
   neo->izq = NULL;
   neo->der = NULL;

   return neo;
}

void nuevoArbol(NODO **raiz, NODO* ramaIzq, int x, NODO* ramaDer)
{
    *raiz = nuevoNodo(x);
    (*raiz) -> izq = ramaIzq;
    (*raiz) -> der = ramaDer;
}

void comprobarArbolExtendido(NODO *raiz,bool &validado)
{
    if(raiz!=NULL){
        if(tieneAmbosHijos(raiz)){
            comprobarArbolExtendido(raiz->izq,validado);
            comprobarArbolExtendido(raiz->der,validado);
        }
        else if(!esHoja(raiz)){
            printf("\n\tEl arbol no es una arbol extendido");
            validado = false;
            return;
        }
    }
}
void calcularLCP(NODO *raiz, int &cont, int &caminoPon){
    if(raiz!=NULL){
        if(esHoja(raiz)){
            caminoPon += cont*raiz->val;
            cont--;
        }
        else{
            cont++;
            calcularLCP(raiz->izq,cont,caminoPon);//
            cont++;
            calcularLCP(raiz->der,cont,caminoPon);
            cont--;
        }    
    }
}

bool tieneAmbosHijos(NODO *raiz){
    if(raiz->izq!=NULL && raiz->der!=NULL)
        return true;
    else
        return false;
}
bool esHoja(NODO *raiz)    // Retorna true si el nodo es hoja
{
   if(raiz->izq==NULL && raiz->der==NULL ){
      return true;
   }
   else{
      return false;
   }
}

void opcionesMenuCPonderado()
{
   printf("\t===================================================\n");
   printf("\t\t\tLONGITUD DE CAMINO PONDERADO\n");
   printf("\t===================================================\n");
   printf("\t[0] Salir\n");
   printf("\t[1] Crear arbol \n");
   printf("\t[2] Insertar nodos del arbol\n");
   printf("\t[3] Comprobar arbol extendido\n");
   printf("\t[4] Calcular camino ponderado\n");
   
   printf("\t---------------------------------------------------\n");
}

void menuCPonderado()
{
   NODO *a;
   bool validado = true;
   int cont = 0, caminoPon = 0;
   char opc;
   // Nodos para crear el arbol
   NODO *aizq, *ader;

   do {
      opcionesMenuCPonderado();
      printf("\tElija una opcion => ");
      scanf("%s",&opc);
      switch(opc) {
         case '0':
            printf("\n\tRETORNANDO AL MENU PRINCIPAL...");
            break;

         case '1':
            crearArbol(&a);
            printf("\n\tArbol creado con exito");
            break;

         case '2':
            
            ader = nuevoNodo(7);
            aizq = nuevoNodo(2);
            nuevoArbol(&a,aizq,1,ader);
            
            aizq->izq = nuevoNodo(6);
            aizq->der = nuevoNodo(4);

            aizq->izq->izq = nuevoNodo(3);
            aizq->izq->der = nuevoNodo(5);
            
            if(a!=NULL){
                printf("\n\tNodos insertados\n");
            }
            break;
         case '3':
            comprobarArbolExtendido(a, validado);
            if(validado){
                printf("\n\tEs un arbol extendido\n");
            }
            break;

         case '4':
            if(validado){
                calcularLCP(a,cont,caminoPon);
                printf("\n\tLa longitud del camino ponderado es: %d\n",caminoPon);
            }
            else
                printf("\n\tEl arbol no es extendido, no se puede calcular la longitud ponderada\n");
            break;

         default:
            printf("\n\tOpcion no valida.\n");
            break;
      }
      printf("\n\n");
      //system("pause");
      getch();
      system("cls");
   } while(opc!='0');
}





void crearSimbolos(int numsymbols, ptr node[]) {
	for (int i = 0; i < numsymbols; i++) {
    	create(i, node);
	}
}

int leerNroSimbolos() {
	int numsymbols;
	cout << "\n\tINGRESE EL NUMERO DE SIMBOLOS : ";
	cin >> numsymbols;
   	return numsymbols;
}

void ordenarHuffman(int numsymbols, ptr node[]) {
	ptr p, q, r;
	for (int j = numsymbols; j < 2*numsymbols - 1; j++) {
      r = new huff_node;
      node[j] = r;
      //r->parent = null;
      r->parent = NULL;
      twosmall(p, q, j, node);
      p->parent = r;
      q->parent = r;
      p->childtype = 'L';
      q->childtype = 'R';
      r->symbol = ' ';
      r->freq = p->freq + q->freq;
   }
}

void mostrartHuffman(int numsymbols, ptr node[]) {
	printf("\n\t\t\tCODIGO DE HUFFMAN\n\n");
	//cout <<"simbolo *-------* codigo: " << endl;
	printf("\t\t===============================\n");
	printf("\t\t No  SIMBOLO\tCODIGO HUFFMAN\n");
	printf("\t\t-------------------------------\n");

	for (int k = 0; k < numsymbols; k++) {
		printf("\t\t");
		print(k, node);
	}
	printf("\t\t------------------------------\n");
}

void create(int k, ptr node[]) {
   ptr t = new huff_node;
   cout << "\t\tSimbolo numero " << k+1 << ": ";
   cin >> t->symbol;
   cout << "\t\tSu  frecuencia  : ";
   cin >> t->freq;
   t->parent = NULL;
   node[k] = t;
}

void print(int k, ptr node[]) {
   ptr t = node[k];
   char code[10], cad[]="     ";
   int size = 0;
   printf("%3d %5c %", k+1, t->symbol);
   while (t->parent != NULL) {
      if (t->childtype == 'L')
      { code[size] = '0'; }
      else
      { code[size] = '1'; }
      t = t->parent;
      size++;
   }
   printf("%10s", cad);
   for (int j = size-1;j>=0; j--){
      printf("%c", code[j]);
   }
   cout << endl;
}

void twosmall(ptr &p, ptr &q, int numnodes, ptr node[]) {
   int min1 = 9999;
   int min2 = 9999;
   p = NULL;
   q = NULL;

   for (int i = 0; i < numnodes; i++) {
      if (node[i]->parent == NULL) {
         if (node[i]->freq < min1) {
            min2 = min1;
            min1 = node[i]->freq;
            q = p;
            p = node[i];
         }
         else{
            if (node[i]->freq < min2) {
               min2 = node[i]->freq;
               q = node[i];
            }
         }
      }
   }

}


void opcionesMenu(){
	printf("\t===================================================\n");
   	printf("\t\t  MENU ALGORITMOS DE GRAFOS \n");
   	printf("\t===================================================\n");
   	printf("\t[0] Salir \n");
   	printf("\t[1] Crear Grafo\n");
   	printf("\t[2] Ordenamiento Mergesort\n");
   	printf("\t[3] Ordenamiento Quicksort\n");
   	printf("\t[4] Camino Ponderado\n");
   	printf("\t[5] Algoritmo Huffman \n");
   	printf("\t \n");
}


void menu(){
	
	int opc;
	ptr node[maxsize];
	int numsymbols;
	 
	do{
		system("cls");
		opcionesMenu();
		do{
			printf("\tIngrese una opcion -> ");
			scanf("%d", &opc);
			if(opc<0 || opc>5)
				printf("\n\tOpcion no valido....\n");
		}while(opc<0 || opc>5);
		
		switch(opc){
			case 0: break;
			case 1: printf("\n\t...\n");
				
				break;
			case 2: printf("TBA Mergesort");
				break;	
			case 3: printf("TBA Quicksort");
				break;
			case 4: 
				system("cls");
				printf("\t===================================================\n");
  				 printf("\t\t\tSUBMENU\n");
  				menuCPonderado();
				break;
			case 5:
				numsymbols = leerNroSimbolos();
				crearSimbolos(numsymbols, node);
				ordenarHuffman(numsymbols, node);
				mostrartHuffman(numsymbols, node);
				break;	
			default: break;
		}
		getch();	
	}while(opc !=0);
	printf("\tUd. acaba de salir...\n");
}