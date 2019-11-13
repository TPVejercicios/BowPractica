#pragma once
#include <vector>
#include "Texture.h"

using namespace std;

class Background {
private:
	int h = 0, w = 0;
	Texture* texture;
public:
	Background(int _h, int _w, Texture* _texture);
	~Background();
	void render() const;
	void changeBackground(Texture* _texture);
};