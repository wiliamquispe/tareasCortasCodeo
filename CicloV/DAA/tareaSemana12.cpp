/*
 * nomPrograma: codigoHuffman.cpp
 * descripcion: operaciones basica del codigo de Huffman
 *
 *       Datos de prueba ejemplo
 *    char arr[] = {'j', 'u', 'a', 'n', 'i', 't'};
 *    int freq[] = { 1,   2,   4,   1,   2,   3};
 *    1. Con los datos debe analiar y construir el arbol y luego
 *       codigo Huffman el cual debe chequear con la salida del prog.
 *    2. Analice el codigo y haga las mejoras.
 *    3. Module el programa, sobre todo el programa principal.
 *       3.1 Elimine variables globales
 *       3.2 En el programa principal solo debe haber llamdas a subprogramas
 *       3.3 Los encabezados deben ser modulos/subprogramas.                                                           )
 *
 *
 * @Autores: http://codigofuentecpp.blogspot.com/2013/10/codificacion-de-huffman.html
 *		
 * @fecha: Adaptado por GASA 25/08/2021
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

using namespace std;

const int maxsize = 100;
const int null = 0;

struct huff_node {
   char symbol;
   int freq;
   huff_node *parent;
   char childtype;
};

typedef huff_node *ptr;

void create(int k, ptr node[]);
void print(int k, ptr node[]);
void twosmall(ptr &p, ptr &q, int numnode, ptr node[]);

int leerNroSimbolos();
void crearSimbolos(int numsymbols, ptr node[]);
void ordenarHuffman(int numsymbols, ptr node[]);
void mostrartHuffman(int numsymbols, ptr node[]);

int main() {
	ptr node[maxsize];
	int numsymbols;
	numsymbols = leerNroSimbolos();
	crearSimbolos(numsymbols, node);
	ordenarHuffman(numsymbols, node);
	mostrartHuffman(numsymbols, node);
	system("pause");
	return(0);
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
	printf("\n\tCODIGO DE HUFFMAN\n\n");
	//cout <<"simbolo *-------* codigo: " << endl;
	printf("===============================\n");
	printf(" No  SIMBOLO\tCODIGO HUFFMAN\n");
	printf("-------------------------------\n");

	for (int k = 0; k < numsymbols; k++) {
		print(k, node);
	}
	printf("------------------------------\n");
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

void 