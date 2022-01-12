#pragma once
class object
{
public:
	int x, y, speedX, speedY;
	int sateliteimg;
	float rot;
	int size;
	int existsflag;
	void UpdateSatelites(int& x, int& y, int& speedX, int& speedY, int img, float& rot, int camX, int camY);
	void UpdateBananas(int& x, int& y, int img, float& rot, int camX, int camY, int exists);
};

int checkHit(int playerX, int playerY, int objX, int objY, int playerSize, int objSize);
int checkDist(int playerX, int playerY, int objX, int objY);

