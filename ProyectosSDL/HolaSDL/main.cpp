#include "checkML.h"
#include <iostream>
#include "Game.h"
#include <stdexcept>

using namespace std;

using uint = unsigned int;

int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	Game game;
	game.run();
	cout << "FIN DEL JUEGO" << endl;
	system("pause");
	return 0;
}