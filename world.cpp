#include "DxLib.h"
#include "player.h"
#include<math.h>
#include <time.h>
#include "world.h"
#include "object.h"

int DrawBG(int a, int worldx, int worldy, int camx, int camy)
{
	DrawGraph(worldx - camx, worldy - camy, a, true);
	return 0;
}

void RandomizeSpawns(int& x, int& y) {
	x = rand() % 6000 - 3000;
	if (x == 0) x = rand() % 6000 - 3000;
	y = rand() % 3300 - 1500;
	if (y == 0) y = rand() % 3300 - 1500;

	if (abs(x) <= 128) x = rand() % 128 + 128;
	if (abs(y) <= 128) y = rand() % 128 + 128;
}

int tick = 15; // 1 tick every X frames
void Oxygen(int& ammount, int& o2fr) {
	o2fr++;
	if (o2fr >= tick) {
		o2fr = 0;
		ammount--;
	}
	if (ammount <= 0) ammount = 0;
	DrawBox(40, 210, 40 + 45, 210 + ammount, GetColor(190, 220, 220), true);
}