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

void inicializar_areas(Area_datos *datos[], Area_indices *indices[], int OMAX, int cant_bloques) {
	for (int i = 0; i < OMAX; i++) {
		datos[i] = new Area_datos{0, "", 0};
	}
	
	for (int i = 0; i < cant_bloques; i++) {
		indices[i] = new Area_indices{0, 0};
	}
}



string consulta(Area_datos* datos[], Area_indices* indices[], int OMAX, int OVER, int cant_bloques, int clave, int n) {
	
	if (indices[0]->clave <= clave) {   // Si la primer clave del índice es mayor que la clave que buscamos no realizamos la busqueda en el area principal
		
		for (int i = 0; i < cant_bloques; i++) {  
			if (indices[i]->clave <= clave) {
				// Buscamos en el bloque
				int dir_bloque = indices[i]->dir;
				for (int j = dir_bloque; j < dir_bloque + n; j++) {
					if (datos[j]->clave == clave) {
						return datos[j]->dato;
					}
				}
			}
		}
	}
	// Si no lo encontramos en el área principal, buscamos en el Overflow
	for (int i = OVER; i < OMAX; i++) {
		if (datos[i]->clave == clave) {
			return datos[i]->dato;
		}
	}
	
	// Si no se encuentra la clave
	cout<<"Dato no encontrado"<<endl;
	return "------";
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
bool alta_registro(Area_datos* datos[], Area_indices* indices[], int OMAX, int cant_bloques, int n, int clave, string nombre, int MAX, int OVER){
	bool check = false;
	/*Si es false retornamos esta variable, y con if en el main decimos que se agreago el dato correctamente o que 
	no se pudo tambien si el dato fue ingresado correctamente y retorna true despues reorganizamos el vector*/ 
	
	
	for(int i = 0; i<n; i++){
		//CASO 1
		//CASO 1
		if (indices[i]->clave == 0) {
			datos[indices[i]->dir]->clave = clave;
			datos[indices[i]->dir]->dato = nombre;
			return true;
			//MENSAJE DE SE GENERO UN NUEVO BLOQUE QSYO
		}
		
		// CASO 2
		if (indices[i]->clave != 0) {
			int contador = 0;
			int condicion = n / 2;
			for (int j = indices[i]->dir; j < n; j++) {
				if (datos[j]->clave != 0) {
					contador++;
				}
			}
			
			if (contador == condicion) {
				if (datos[indices[i]->dir]->clave < clave && clave < datos[indices[i]->dir + 1]->clave) {
					for (int j = indices[i]->dir; j < n; j++) {
						if (datos[j]->clave == 0) {
							datos[j]->clave = clave;
							datos[j]->dato = nombre;
							return true;
						}
					}
				}
			}
		}
		
		///CASO 3
		if(indices[i]->clave < clave) { //miro la clave en el area de indices, la clave q voy a meter tiene que ser mayor
			for (int i = indices[i]->dir; i<n; i++){ //recorro el bloque
				if(datos[i]->clave == 0) { //puede pasar que el bloque sea todo feo y queden espacios vacios, trato de encontrar ese ultimo registro
					if(datos[--i]->dir == 0) { // si la dir es cero
						if(OVER < OMAX){ //debe llegar hasta 19
							datos[OVER]->clave = clave; //pongo la clave en el overflow
							datos[OVER]->dato = nombre; //el dato q se ingresa :v
							datos[--i]->dir = OVER; //le pongo a ese anterior registro la direccion del overflow, el i deberia ser el vacio por lo que bajo una posicion para estar en el ultimo registro
							OVER++; //aumento la pos del over
							return true;
						}
					} else { //en este caso ya existe una direccion
						if(OVER < MAX){ //debe llegar hasta 19
							datos[OVER]->clave = clave; //pongo la clave en el overflow
							datos[OVER]->dato = nombre; //el dato q se ingresa :v
							datos[--OVER]->dir = OVER; //le pongo al registro anterior la direccion con el nro del over actual
							OVER++; //aumento la pos del over
							return true;
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
		int PMAX = 11;
		int OVER = PMAX + 1;
		const int OMAX = 20;
		int cant_bloques = PMAX / n;
		
		Area_datos* datos[OMAX];
		Area_indices* indices[OMAX];
		// Inicializar áreas antes de usarlas
		inicializar_areas(datos, indices, OMAX, cant_bloques);
		
		return 0;
	}
	
