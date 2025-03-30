#include <iostream>
#include <vector>
using namespace std;

struct Area_datos {
	int clave;
	string dato;
	int dir;
};

struct Area_indices {
	int clave;
	int dir;
};

void inicializar_areas(vector<Area_datos*>& datos, vector<Area_indices*>& indices, int OMAX, int cant_bloques) {
	for (int i = 0; i < OMAX; i++) {
		datos[i] = new Area_datos;  // Asignar memoria
		datos[i]->clave = 0;
		datos[i]->dir = 0;
	}
	
	for (int i = 0; i < cant_bloques; i++) {
		indices[i] = new Area_indices;  // Asignar memoria
		indices[i]->dir = 0;
		indices[i]->clave = 0;
	}
}
/*
Caso 1:
1-consultar si hay un indice que no este ocupado
2-ingresar a la direccion de ese indices
3-insertar nuevo registro

Caso 2:
1-consultar si hay un indice ocupado
2-ingresar a la direccion de ese indice;
3-recorrer el bloque (van a haber varios casos en esta situacion):
	#Caso 1: Si el bloque ya cumple con la condicion del n/2 y el numero de la clave 
			 esta por encima de la clave del ultimo registro del bloque se debera iniciar un nuevo bloque.
	#Caso 2: Si el bloque ya cumple con la condicio n/2 pero el numero de la clave del registro a ingresar 
			 esta en el rango de claves de un bloque debera ser ingresado en ese bloque, solo si hay espacio
			 de lo contrario sera enviado al overflow.

Caso 3:
Si el area principal de datos ya esta llena (si los bloques estan llenos) el proximo dato ingresado
debera ir al overflow, donde si el valor de la clave esta entre los valores de las claves de un bloque 
el ultimo registro de ese bloque debera llevar la direccion del registro ingresado en el overflow
ejemplo:
	bloque 2[3,5,7,8 direccion (0)]
	bloque 3[10,17,23,45 direccion (1)]
	overflow[9,50]

En caso de que se ingrese nuevamente otro dato que cumpla con la condicion aterior pero el ultimo registro del bloque ya tenga un direccion 
al overflow se le debera dar la direccion del dato ingresado al anterior dato ingresado al overflow.

Ejemplo: 
se ingresa el 30
Overflow[10,20(2),30].

Caso 4: Si el archivo se llena, se devuelve un mensaje de error.
*/
bool alta_registro(vector<Area_datos*>& datos, vector<Area_indices*>& indices, string nombre, int clave, int n){
	bool check = false;
	/*Si es false retornamos esta variable, y con if en el main decimos que se agreago el dato correctamente o que 
	no se pudo tambien si el dato fue ingresado correctamente y retorna true despues reorganizamos el vector*/ 
	

	for(const auto& p: indices){
		//CASO 1
		if(p->clave == 0){
			datos[p->dir]->clave = clave;
			datos[p->dir]->dato = nombre;
			return true;
			//MENSAJE DE SE GENERO UN NUEVO BLOQUE QSYO
		}
		
		//CASO 2
		if(p->clave != 0){
			int contador = 0;
			//condicion n/2
			int condicion = n/2;
			for(int i = p->dir; i < n; i++){
				if(datos[i]->clave != 0){
					contador++;
				}
			}
			
			//caso si la clave a ingresar esta entre los valores de un bloque y ya se cumple la condicion n/2
			if(contador == condicion){
				if(datos[p->clave]->clave<clave && clave<datos[p->clave++]->clave){
					for(int i = p->dir; i<n; i++){
						if(datos[i]->clave == 0){
							datos[i]->clave = clave;
							datos[i]->dato = nombre;
							return true;
						}
					}
				}
			}
		}

		//CASO 3
		if(p->clave < clave) { //miro la clave en el area de indices, la clave q voy a meter tiene que ser mayor
			for (int i = p->dir; i<n; i++){ //recorro el bloque
				if(datos[i]->clave == 0) { //puede pasar que el bloque sea todo feo y queden espacios vacios, trato de encontrar ese ultimo registro
					if(datos[--i]->dir == 0) { // si la dir es cero
						if(OVER<OMAX){ //debe llegar hasta 19
							datos[OVER]->clave = clave; //pongo la clave en el overflow
							datos[OVER]->dato = nombre; //el dato q se ingresa :v
							datos[--i]->dir = OVER; //le pongo a ese anterior registro la direccion del overflow, el i deberia ser el vacio por lo que bajo una posicion para estar en el ultimo registro
							OVER++; //aumento la pos del over
						}
					} else { //en este caso ya existe una direccion
						if(OVER<MAX){ //debe llegar hasta 19
							datos[OVER]->clave = clave; //pongo la clave en el overflow
							datos[OVER]->dato = nombre; //el dato q se ingresa :v
							datos[--OVER]->dir = OVER; //le pongo al registro anterior la direccion con el nro del over actual
							OVER++; //aumento la pos del over
						}
					}
				}
			}
		}
	}
	return check;
	
}

int main() {
	int n = 4;
	int PMAX = 11; //11 xq arrancamos desde el cero
	int OVER = PMAX+1; //corregido del pdf, over es igual a pmax+1 por ende arrancaria en 11+1=12 como el ej del pdf
	int OMAX = 20;
	int cant_bloques = PMAX / n;
	
	vector<Area_datos*> datos(OMAX);
	vector<Area_indices*> indices(cant_bloques);
	
	// Inicializar �reas antes de usarlas
	inicializar_areas(datos, indices, OMAX, cant_bloques);
	
	for (const auto& p : datos) {
		cout << p->clave << endl;
	}
	
	for (auto& p : datos) delete p;
	for (auto& p : indices) delete p;
	
	return 0;
}

