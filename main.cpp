#include "DxLib.h"
#include<time.h>
#include "player.h"
#include "cam.h"
#include "world.h"
#include "ajikugames.h"
#include "object.h"

const char TITLE[] = "Where are my Bananas?!";


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	ChangeWindowMode(TRUE);
	SetWindowSizeChangeEnableFlag(TRUE, TRUE);
	SetMainWindowText(TITLE);
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);
	SetWindowSizeExtendRate(1.0);
	SetBackgroundColor(0x00, 0x00, 0x00);
	if (DxLib_Init() == -1) { return -1; }
	SetDrawScreen(DX_SCREEN_BACK);
	char keys[256] = {0}, prevkeys[256] = {0};
	int frame = 0;
	srand(time(NULL));

	// Scenestate
	int scenestate = 0;
	int gamestate = 0;
	enum states {
		ajkgames,
		oikawastudios,
		mainmenu,
		gameplay,
	};
	enum gamestates {
		load,
		game,
		finish,
		fail,
	};

	// IMAGES & SOUNDS
	ajikugames ajikugames;
	ajikugames.framecount = 0, ajikugames.index = 0;
	ajikugames.logosound = LoadSoundMem("Resource\\AjikuGames\\ajikugamessound.wav");
	LoadDivGraph("Resource\\AjikuGames\\ajikugameslogo.png", 4, 2, 2, 640, 256, ajikugames.logo, true);
	int bgimg = LoadGraph("Resource\\stage.png", true);
	player player;
	player.jetpackindex = 0;
	LoadDivGraph("Resource\\chimpanzee.png", 4, 4, 1, 64, 64, player.image, true);
	LoadDivGraph("Resource\\jetpack.png", 4, 4, 1, 64, 64, player.jetpack, true);
	player.index = 0, player.framecount = 0;
	int mainmenuscreen[2], mainmenuindex = 0, mainmenuframecount = 0;
	LoadDivGraph("Resource\\mainmenu.png", 2, 2, 1, 1280, 720, mainmenuscreen, true);
	int tank = LoadGraph("Resource\\tank.png", true);
	int ship = LoadGraph("Resource\\ship.png", true);
	int satimg = LoadGraph("Resource\\satelite.png", true);
	int metimg = LoadGraph("Resource\\meteorite.png", true);
	int bananaimg = LoadGraph("Resource\\banana.png", true);
	int warubananaimg = LoadGraph("Resource\\warubanana.png", true);
	int failimg = LoadGraph("Resource\\fail.png", true);
	int finishimg = LoadGraph("Resource\\clear.png", true);
	int bananexp = LoadSoundMem("Resource\\bananaexplosion.wav");
	int monkeysound = LoadSoundMem("Resource\\saru.wav");
	int get = LoadSoundMem("Resource\\get.wav");
	int song = LoadSoundMem("Resource\\song.wav");
	int oikawa = LoadGraph("Resource\\ikas2.png", true);
	
	object satelite[201];
	object banana[201];
	int takenbananas = 0;
	int neededbananas = 5;
	for (int a = 0; a < 200; a++) {
		satelite[a].x = 0;
		satelite[a].y = 0;
		satelite[a].speedX = 0;
		satelite[a].speedY = 0;
		satelite[a].rot = 0;

		banana[a].x = 0;
		banana[a].y = 0;
		banana[a].rot = 0;
		banana[a].existsflag = FALSE;
	}
	
	int levelnum = 1;
	int oxygenammount = 0, o2fc = 0;

	int cameraX = -(WIN_WIDTH / 2);
	int cameraY = -(WIN_HEIGHT / 2);

	// One Button Flag
	int spaceflag = FALSE, spaceheldflag = FALSE;


	while (true) {
		GetHitKeyStateAll(keys);
		ClearDrawScreen();
		srand(time(NULL));
		//---------  ここからプログラムを記述  ----------//

		if (keys[KEY_INPUT_SPACE] && !prevkeys[KEY_INPUT_SPACE]) spaceflag = TRUE;
		else if (keys[KEY_INPUT_SPACE] == prevkeys[KEY_INPUT_SPACE]) spaceflag = FALSE;

		switch (scenestate) {
		case ajkgames:
			ajikugames.DrawLogo(ajikugames.index, ajikugames.framecount, scenestate, frame, 110);
			break;
		case oikawastudios:
			DrawGraph(0, 0, oikawa, true);
			if (frame >= 320) scenestate = mainmenu;
			break;
		case mainmenu:
			mainmenuframecount++;
			if (mainmenuframecount >= 10) {
				mainmenuindex++;
				mainmenuframecount = 0;
			} 
			if (mainmenuindex >= 2) mainmenuindex = 0;
			DrawGraph(0, 0, mainmenuscreen[mainmenuindex], true);
			if (spaceflag) {
				scenestate = gameplay;
				gamestate = load;
			}
			break;
		case gameplay:
			if (!CheckSoundMem(song)) PlaySoundMem(song, DX_PLAYTYPE_BACK);
			switch (gamestate) {
			
			case load:
				player.x = 0;
				player.y = 0;
				player.speedX = 0;
				player.speedY = 0;
				oxygenammount = 210;
				takenbananas = 0;
				neededbananas = 7;
				cameraX = -(WIN_WIDTH / 2);
				cameraY = -(WIN_HEIGHT / 2);
				for (int a = 0; a < 200; a++) {
					satelite[a].x = 0;
					satelite[a].y = 0;
					satelite[a].speedX = 0;
					satelite[a].speedY = 0;
					satelite[a].rot = 0;

					banana[a].x = 0;
					banana[a].y = 0;
					banana[a].rot = 0;
					banana[a].existsflag = FALSE;
				}
				for (int a = 0; a <= levelnum * 40; a++) {
					RandomizeSpawns(satelite[a].x, satelite[a].y); // Randomize Locations
					RandomizeSpawns(banana[a].x, banana[a].y);
					banana[a].existsflag = TRUE;
				}
				gamestate = game;
				break;
			
			case game:
				DrawBG(bgimg, -3200, -1800, cameraX, cameraY); // Draw BG
				DrawRotaGraph(0 - cameraX, 0 - cameraY, 2, 0, ship, true); // Draw the Ship.
				player.rotate(player.angle, player.rotspeed); // Spin the player
				player.move(player.x, player.y, player.speedX, player.speedY, spaceflag, player.angle, bananexp, monkeysound); // Player movement
				movecam(cameraX, cameraY, player.x, player.y, player.speedX, player.speedY); // Moves the camera


				for (int a = 0; a <= levelnum * 40; a++) {
					if (checkHit(player.x, player.y, satelite[a].x, satelite[a].y, 32, 64)) {
						satelite[a].speedX = player.speedX / 2;
						satelite[a].speedY = player.speedY / 2;
						player.speedX = -player.speedX/2;
						player.speedY = -player.speedY/2;
					}

					if (checkHit(player.x, player.y, banana[a].x, banana[a].y, 32, 32) && banana[a].existsflag) {
						takenbananas++;
						banana[a].existsflag = FALSE;
						PlaySoundMem(get, DX_PLAYTYPE_BACK);
						player.speedX = player.speedX / 2;
						player.speedY = player.speedY / 2;
					}

					if (a % 2 == 0) satelite[a].UpdateSatelites(satelite[a].x, satelite[a].y, satelite[a].speedX, satelite[a].speedY, satimg, satelite[a].rot, cameraX, cameraY); // Draw and Move Satelites
					if (a % 2 == 1) satelite[a].UpdateSatelites(satelite[a].x, satelite[a].y, satelite[a].speedX, satelite[a].speedY, metimg, satelite[a].rot, cameraX, cameraY);
					if (a != 5 && a != 10) banana[a].UpdateBananas(banana[a].x, banana[a].y, bananaimg, banana[a].rot, cameraX, cameraY, banana[a].existsflag);
					if (a == 5 || a == 10) banana[a].UpdateBananas(banana[a].x, banana[a].y, warubananaimg, banana[a].rot, cameraX, cameraY, banana[a].existsflag);
				} // Checkhits for bananas and objects

				if (checkHit(player.x, player.y, 0, 0, 32, 128)) {
					oxygenammount = 210;
					if (takenbananas >= neededbananas) {
						//levelnum++;
						gamestate = finish;
					} 
					
				}

				if (oxygenammount <= 0) gamestate = fail;


				player.update(player.index, cameraX, cameraY, player.framecount, player.speedX, player.speedY, spaceflag, player.jetpackindex); // Draw the player
				
				

				// O2 Tank
				Oxygen(oxygenammount, o2fc);
				DrawGraph(0, 175, tank, true);
				SetFontSize(25);
				DrawFormatString(20, 20, GetColor(255, 255, 255), "必要なバナナ：%d/%d！\n", takenbananas, neededbananas);
				DrawFormatString(1000, 20, GetColor(255, 255, 255), "LEVEL %d", levelnum);
				DrawFormatString(1000, 65, GetColor(255, 255, 255), "宇宙船まで：%dm", checkDist(player.x, player.y, 0, 0)/10);

				if (oxygenammount < 75) DrawString(20, 65, "そろそろ宇宙船に戻らないと！！", GetColor(255, 100, 100));
				break;
			
			case finish:
				DrawGraph(0, 0, finishimg, true);
				if (spaceflag) scenestate = mainmenu;
				break;
			case fail:
				DrawGraph(0, 0, failimg, true);
				levelnum = 1;
				if (spaceflag) gamestate = load;
				break;
			}
			break;
		}

		
		
		//---------  ここまでにプログラムを記述  ---------//
		frame++;
		GetHitKeyStateAll(prevkeys);
		ScreenFlip();
		WaitTimer(20);
		if (ProcessMessage() == -1) {
			break;
		}
	}

	DxLib_End();
	return 0;
}
