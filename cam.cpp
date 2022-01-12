#include "cam.h"
#include<math.h>


void movecam(int& a, int& b, int c, int d, int f, int g) {

	if (abs(a - c) <= (WIN_WIDTH / 2) - camdev) a -= abs(f);
	else if (abs(a - c) >= (WIN_WIDTH / 2) + camdev) a += abs(f);
	if (abs(b - d) <= (WIN_HEIGHT / 2) - camdev) b -= abs(g);
	if (abs(b - d) >= (WIN_HEIGHT / 2) + camdev) b += abs(g);

	if (a >= 3200 - 1280) a = 3200 - 1280;
	else if (a <= -3200) a = -3200;
	if (b >= 1800 - 720) b = 1800 - 720;
	else if (b <= -1800) b = -1800;

}