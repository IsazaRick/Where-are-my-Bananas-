#include "DxLib.h"
#include "player.h"
#include<math.h>

float prop = 0;
float speed = 4;

int jetflag = FALSE;

void player::rotate(float& a, float b) {
	a += b;
	if (a >= 6.283) a = 0;
}

void player::update(int& a, int b, int c, int& framecount, int spdx, int spdy, int flag, int& jetind) {
	framecount++;
	int asd = (8 - ((abs(spdx) + abs(spdy)) / 2));
	if (asd == 0) asd = 8;

	if (flag) jetflag = TRUE;

	if (framecount >= asd) {
		a++;
		if (jetflag) jetind++;
		framecount = 0;
	}
	if (jetpackindex >= 4) {
		jetpackindex = 0;
		jetflag = FALSE;
	} 
	if (a >= 4) a = 0;
	DrawRotaGraph(x - b, y - c, 1, angle, jetpack[jetind], true);
	DrawRotaGraph(x - b, y - c, 1, angle, image[a], true);
}

int player::move(int& a, int& b, int& c, int& d, int flag, float e, int sound, int monkey) {
	if (flag) {
		PlaySoundMem(sound, DX_PLAYTYPE_BACK);

		// Top Right Quarter (TOP)
		if (e >= 0 && e < 1.57) {
			prop = e / 1.57;
			c += round(prop * speed);
			d += -(speed - c);
		}

		// Bottom Right Quarter (RIGHT)
		else if (e >= 1.57 && e < 3.1415) {
			prop = (e - 1.57) / 1.57;
			d += round(prop * speed);
			c += (speed - c);
		}
		
		// Bottom Left Quarter (DOWN)
		else if (e >= 3.1415 && e < 4.712) {
			prop = (e - 3.1415) / 1.57;
			c += -round(prop * speed);
			d += (speed + c);
		}
		
		// Top Left Quarter (LEFT)
		else if (e >= 4.712 && e < 6.283) {
			prop = (e - 4.712) / 1.57;
			d += -round(prop * speed);
			c += -(speed + c);
		}
	}

	if (d > 6) {
		if (!CheckSoundMem(monkey)) PlaySoundMem(monkey, DX_PLAYTYPE_BACK);
		d = 6;
	} 
	else if (d < -6) {
		if (!CheckSoundMem(monkey)) PlaySoundMem(monkey, DX_PLAYTYPE_BACK);
		d = -6;
	} 
	if (c > 6) {
		if (!CheckSoundMem(monkey)) PlaySoundMem(monkey, DX_PLAYTYPE_BACK);
		c = 6;
	}
	else if (c < -6) {
		if (!CheckSoundMem(monkey)) PlaySoundMem(monkey, DX_PLAYTYPE_BACK);
			c = -6;
	} 

	if (a >= 3200 || a <= -3200) c = -c;
	if (b >= 1800 || b <= -1800) d = -d;


	a += c;
	b += d;

	return 0;
}