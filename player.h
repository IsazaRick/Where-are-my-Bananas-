#pragma once

class player
{
public:
	int x = 0, y = 0;
	int image[4], index, framecount;
	int jetpack[4], jetpackindex;
	int speedX = 0, speedY = 0, acc = 2;
	int size = 32;
	float angle = 0;
	float rotspeed = 0.05;
	void rotate(float& a, float b);
	void update(int& a, int b, int c, int& framerate, int spdx, int spdy, int flag, int& jetind);
	int move(int& a, int& b, int& c, int& d, int flag, float e, int sound, int monkey);
};





