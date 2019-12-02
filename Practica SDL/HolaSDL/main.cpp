#include "checkML.h"
#include <iostream>
#include <string>
#include "Game.h"
#include <stdexcept>

using namespace std;

using uint = unsigned int;

int Menu() {
	int op = 0;
	cout << "1. Jugar" << endl;
	cout << "2. Cargar Partida" << endl;
	cout << "Su opcion: ";
	cin >> op;
	while (op < 1 || op > 2) {
		cout << "Opcion no valida, su opcion: ";
		cin >> op;
	}
	return op;

}

int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	try {
		int op = Menu();	
		int partida;
		if (op == 2) {
			cout << "Indique el numero de la partida a cargar: ";
			cin >> partida;
			Game gameL(partida);
			gameL.run();
		}
		else {
			Game game;
			game.run();
		}
	}
	catch (exception e) {
		cout << "Error " << e.what() << endl;
	}
	system("pause");
	return 0;
}