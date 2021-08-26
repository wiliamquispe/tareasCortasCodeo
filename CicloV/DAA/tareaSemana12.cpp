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
/*						 Metodos de Ordenamiento					*/	
/*------------------------------------------------------------------*/
	/*--------------- MERGESORT---------------*/
void entradaMS(int a[], int num);
void merge_sort(int a[], int izquierda,int derecha);
void merge(int v[], int izquierda,int medio,int derecha);
void mostrarMS(int a[], int num);
void pruebaMS();


	/*--------------- QUICKSORT---------------*/
void quickSort(int *vector, int inicio, int final);
void pruebaQuickSort();
void entradaVectorQS(int *vector);
void imprimirQS(int *vector, int n);


/*						 Metodos del Árbol 							*/	
/*------------------------------------------------------------------*/
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
void pruebaHuffman();


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
   printf("\t\t\t\tSUBMENU\n");
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
   	printf("\t[1] Ordenamiento Mergesort\n");
   	printf("\t[2] Ordenamiento Quicksort\n");
   	printf("\t[3] Camino Ponderado\n");
   	printf("\t[4] Algoritmo Huffman \n");
   	printf("\t \n");
}


void menu(){
	
	int opc;
	 
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
			case 1: printf("TBA Mergesort");
				
				break;	
			case 2: //printf("TBA Quicksort");
				pruebaQuickSort();
				break;
			case 3: 
				system("cls");
			//	printf("\t===================================================\n");
  			//	 printf("\t\t\tSUBMENU\n");
  				menuCPonderado();
				break;
			case 4:
				pruebaHuffman();
				break;	
			default: break;
		}
		getch();	
	}while(opc !=0);
	printf("\tUd. acaba de salir...\n");
}

void pruebaHuffman(){
	ptr node[maxsize];
	int numsymbols;
	numsymbols = leerNroSimbolos();
	crearSimbolos(numsymbols, node);
	ordenarHuffman(numsymbols, node);
	mostrartHuffman(numsymbols, node);
}


void quicksort(int *v, int inicio, int fin){
	int i = inicio, f = fin, aux;
	int x = v[(inicio+fin)/2];
	
	do{
		while(v[i] < x && f <=fin)
			i++;
		while(x < v[f] && f >inicio)
			f--;
		if(i <= f){
			aux = v[i];
			v[f] = aux;
			i++;
			f--;
		}
	}while(i <= f);
	
	if(inicio < f)
		quicksort(v, inicio, f);
	if(i < fin)
		quicksort(v, i, fin);
	
}

/*-----------------METODOS MERGESORT-----------------------*/
void pruebaMS(){
	int num;
	int a[50];
	int dx = maxsize -100;
	entradaMS(a,num);
	
}

void merge_sort(int a[], int izquierda,int derecha){
    int medio;
    if(izquierda<derecha){
    	/*  RECURSIVIDAD   */
        medio=(izquierda+derecha)/2;
        merge_sort(a,izquierda,medio);
        merge_sort(a,medio+1,derecha);
        merge(a,izquierda,medio,derecha);
    }
}

void merge(int v[], int izquierda,int medio,int derecha){
	int b[50]; //arreglo auxiliar
    int x, y, z;
    x=z=izquierda;
    y=medio +1;
    
    //Bucle encargada de hacer la mezcla
    while(x<=medio && y<=derecha){
        if(v[x]<v[y]){
            b[z++]=v[x++];
        }
        else{
            b[z++]=v[y++];
        }
    }
    //Bucle para mover los elementos no mezclados
    while(x <= medio){
        b[z++] = v[x++];
    }
    while(y <= derecha){
        b[z++] = v[y++];
    }
    //Ahors se copia lo de 'aux' al vector original
    for(z=izquierda; z<=derecha ; z++){
        v[z]=b[z];
    }
    
	/*
	int h,i,j,k;
    h=izquierda;
    i=izquierda;
    j=medio+1;
    
    while((h<=medio)&&(j<=derecha)){
        if(a[h]<=a[j]){
            b[i]=a[h];
            h++;
        }
        else
            {
                b[i]=a[j];
                j++;
            }
        i++;
    }
    if(h>medio){
        for(k=j;k<=derecha;k++){
            b[i]=a[k];
            i++;
        }
    }
    else
        {
            for(k=h;k<=medio;k++){
                b[i]=a[k];
                i++;
            }
        }
    for(k=izquierda;k<=derecha;k++){
        a[k]=b[k];
        }*/
}

void entradaMS(int a[], int num){
	cout<<"  *******************************"<<endl;
	cout<<"   PROGRAMA MERGE SORT         "<<endl;
    cout<<"  ******************************  "<<endl;
	cout<<"\tINGRESE LA CANTIDAD DE ELEMENTOS"<<endl;
    cin>>num;
    cout<<endl;
    cout<<"\tLOS ELEMENTOS SON:"<<endl;
    for(int i=1;i<=num;i++){
    	cout<<"\t";
        cin>>a[i];
	}
	mostrarMS(a,num);
	
}
void mostrarMS(int a[], int num){

   	cout<<"\n\tEL NUEVO ORDEN DE ELEMENTOS ES:"<<endl;
    for(int i=1;i<=num;i++){
        cout<<a[i]<<"   ";
        
    }
    cout<<endl;
}



	/*--------------- QUICKSORT---------------*/
void quickSort(int *vector, int inicio, int final){
	int i = inicio, f = final, tmp;
  int x = vector[(inicio + final) / 2];
  do {
    while(vector[i] < x && f <= final) {
      i++;
    }
    while(x < vector[f] && f > inicio) {
      f--;
    }
    if(i <= f) {
      tmp = vector[i];
      vector[i] = vector[f];
      vector[f] = tmp;
      i++; f--;
    }
  } while(i <= f);

  if(inicio < f) {
    quickSort(vector,inicio,f);
  }

  if(i < final){
    quickSort(vector,i,final);
  }
}

void pruebaQuickSort(){
	int vector[] ={-90,5,71,99,0,-105,12,33,26,3};
	//entradaVectorQS(vector);
	int nv = sizeof(vector)/sizeof(int);
	cout<<"\tVector original:"<<endl;
	imprimirQS(vector, nv);
	quickSort(vector,0, nv-1);
	cout<<"\tOrdenamiento QuickSort:"<<endl;
	imprimirQS(vector, nv);
}

/*
void entradaVectorQS(int *vector){
	int num;
	cout<<"\tIngrese tamanio del vector: ";
	scanf("%d", &num);
		cin>>vector[i];
	}
}*/

void imprimirQS(int *vector, int n){
	cout<<"\t";
	for(int i=0; i< n; i++){
		cout<<vector[i]<<" ";
	}
	cout<<endl;
}




