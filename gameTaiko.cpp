#include <graphics.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <vector>
#include <Math.h>
#include "MusicGame.h"
using namespace std;

gameResult MusicGame::TKgame(int i){
	int cur_page = 0;
	
	cleardevice;
	
	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	
	setvisualpage(0);
	setactivepage(0);
	
	void *BG =malloc(imagesize(0, 0, 1440, 900));     //Check if PV image is PNG
	if(songs[i].backGround.substr(songs[i].backGround.size()-4) != ".png"){
		readimagefile( (songs[i].dir + songs[i].backGround).c_str(), 0, 0, 1440, 900);
	}
	else{
		readimagefile( ".\\resources\\bg.jpg", 0, 0, 1440, 900);
	}
	getimage(0, 0, 1440, 900, BG);
	
	setvisualpage(0);
	setactivepage(1);
	
	void *N[10];
	for(int j = 0; j < 10; j++){
		N[j] = malloc(imagesize(0, 0, 47 ,64));
		sprintf(tmp, ".\\resources\\%d.jpg", j);
		readimagefile(tmp, 0, 0, 47, 64);
		getimage(0, 0, 47, 64, N[j]);
	}
	
	
	
	/*
	Bit 0 (1): normal.
	Bit 1 (2): whistle.
	Bit 2 (4): finish.  BIG
	Bit 3 (8): clap.	
	*/
	
	
	char re[20];
	string mciCommand = "open \"" + songs[i].dir + songs[i].AudioFilename + "\" type mpegvideo alias mp3";
	cout << "open mp3 " << songs[i].AudioFilename << endl;
	mciSendString(mciCommand.c_str(), re, 20, NULL);
	cout << "MCI return " << re << endl;
	
	mciSendString("status mp3 length", re, 20, 0);
	int length = atoi(re);
	gameResult result = {0};
	int position = 0;  //music position
	
	int keySig[4] = {0};
	int lasrkeySig[4] = {0};  //KDDK
	
	mciSendString("play mp3", NULL, 0, NULL);
	
	while(songs[i].hitobjects.back().time - offset > position){
		cur_page = -cur_page+1;
		setactivepage(cur_page);
		
		cleardevice();
		putimage(0, 0, BG, COPY_PUT);
		
		int t = 100000;
		
		for(int j = 6; j > 0; j--){
			if(result.combo % t != result.combo){
				int t2 = j;
				t*=10;
				for(; j >0; j--){
					putimage( 190 + (300-(t2*47))/2 + 47*(t2-j), 280, N[(result.combo % t )/(t/10)], COPY_PUT);
					t/=10;
				}
				break;
			}
			t/=10;
		}
		
		t = 10;
		for(int j = 0; j < 10; j++){
			putimage(340-47*j, 0, N[result.score%t / (t/10)], COPY_PUT);
			t*=10;
		}
		
		
		
		
	}
	
	
	
	
	
	
	
}

/*
 todo list
 
 unstable rate
 taiko
 */
