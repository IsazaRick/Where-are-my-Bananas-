#include "object.h"
#include "DxLib.h"
#include<math.h>
#include<time.h>

void object::UpdateSatelites(int& x, int& y, int& speedX, int& speedY, int img, float& rot, int camX, int camY) {
	if (x == 0 && y == 0) {	}
	else {
		x += speedX;
		y += speedY;

		if (x >= 3200 || x <= -3200) speedX = -speedX;
		if (y >= 1800 || y <= -1800) speedY = -speedY;

		rot += 0.01;
		if (rot >= 6.3) rot = 0;

		DrawRotaGraph(x - camX, y - camY, 1, -(rot), img, true);
	}
}

void object::UpdateBananas(int& x, int& y, int img, float& rot, int camX, int camY, int exists) {
	if (exists) {

		rot += 0.02;
		if (rot >= 6.3) rot = 0;

		DrawRotaGraph(x - camX, y - camY, 1, -(rot), img, true);

	}
}


int checkHit(int playerX, int playerY, int objX, int objY, int playerSize, int objSize) {
	int flag = FALSE;
	float a = pow(playerX - objX, 2);
	if (a < 0) a = -a;
	float b = pow(playerY - objY, 2);
	if (b < 0) b = -b;
	float c = sqrt(a + b);
	if (c <= playerSize + objSize) flag = TRUE;
	else flag = FALSE;

	return flag;
}

int checkDist(int playerX, int playerY, int objX, int objY) {
	float a = pow(playerX - objX, 2);
	if (a < 0) a = -a;
	float b = pow(playerY - objY, 2);
	if (b < 0) b = -b;
	float c = sqrt(a + b);
	round(c);

	return c;
}
