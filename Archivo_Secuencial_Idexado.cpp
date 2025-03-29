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

int main() {
	int n = 4;
	int PMAX = 12;
	int OVER = 12;
	int OMAX = 20;
	int cant_bloques = PMAX / n;
	
	vector<Area_datos*> datos(OMAX);
	vector<Area_indices*> indices(cant_bloques);
	
	// Inicializar áreas antes de usarlas
	inicializar_areas(datos, indices, OMAX, cant_bloques);
	
	for (const auto& p : datos) {
		cout << p->clave << endl;
	}
	
	for (auto& p : datos) delete p;
	for (auto& p : indices) delete p;
	
	return 0;
}

