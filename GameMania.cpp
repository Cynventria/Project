#include <graphics.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <vector>
#include "MusicGame.h"
using namespace std;


#define Z_KEY 0x5A
#define X_KEY 0x58
#define N_KEY 0x4E
#define M_KEY 0x4D

gameResult MusicGame::game(int i){
	cout << "gamestart" << endl;
	gameResult result = {0};
	int cur_page = 0;
	
	

	cleardevice();

	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	
	void *BG =malloc(imagesize(0, 0, 1440, 900));     //Check if PV image is PNG
	if(songs[i].backGround.substr(songs[i].backGround.size()-4) != ".png"){
		readimagefile( (songs[i].dir + songs[i].backGround).c_str(), 0, 0, 1440, 900);
	}
	else{
		readimagefile( ".\\resources\\bg.jpg", 0, 0, 1440, 900);
	}
	getimage(0, 0, 1440, 900, BG);
	
	void *zero = malloc(imagesize(0, 0, 47 ,64));
	readimagefile(".\\resources\\0.jpg", 0, 0, 47, 64);
	getimage(0, 0, 47, 64, zero);
	void *one = malloc(imagesize(0, 0, 47 ,64));
	readimagefile(".\\resources\\1.jpg", 0, 0, 47, 64);
	getimage(0, 0, 47, 64, one);
	void *two = malloc(imagesize(0, 0, 47 ,64));
	readimagefile(".\\resources\\2.jpg", 0, 0, 47, 64);
	getimage(0, 0, 47, 64, two);
	void *three = malloc(imagesize(0, 0, 47 ,64));
	readimagefile(".\\resources\\3.jpg", 0, 0, 47, 64);
	getimage(0, 0, 47, 64, three);
	void *four = malloc(imagesize(0, 0, 47 ,64));
	readimagefile(".\\resources\\4.jpg", 0, 0, 47, 64);
	getimage(0, 0, 47, 64, four);
	void *five = malloc(imagesize(0, 0, 47 ,64));
	readimagefile(".\\resources\\5.jpg", 0, 0, 47, 64);
	getimage(0, 0, 47, 64, five);
	void *six = malloc(imagesize(0, 0, 47 ,64));
	readimagefile(".\\resources\\6.jpg", 0, 0, 47, 64);
	getimage(0, 0, 47, 64, six);
	void *seven = malloc(imagesize(0, 0, 47 ,64));
	readimagefile(".\\resources\\7.jpg", 0, 0, 47, 64);
	getimage(0, 0, 47, 64, seven);
	void *eight = malloc(imagesize(0, 0, 47 ,64));
	readimagefile(".\\resources\\8.jpg", 0, 0, 47, 64);
	getimage(0, 0, 47, 64, eight);
	void *nine = malloc(imagesize(0, 0, 47 ,64));
	readimagefile(".\\resources\\9.jpg", 0, 0, 47, 64);
	getimage(0, 0, 47, 64, nine);
	
	void *perfect = malloc(imagesize(0, 0, 256, 72));
	readimagefile(".\\resources\\perfect.jpg", 0, 0, 256, 72);
	getimage(0, 0, 256, 72, perfect);
	void *great = malloc(imagesize(0, 0, 256, 72));
	readimagefile(".\\resources\\great.jpg", 0, 0, 256, 72);
	getimage(0, 0, 256, 72, great);
	void *good = malloc(imagesize(0, 0, 256, 72));
	readimagefile(".\\resources\\good.jpg", 0, 0, 256, 72);
	getimage(0, 0, 256, 72, good);
	void *bad = malloc(imagesize(0, 0, 256, 72));
	readimagefile(".\\resources\\bad.jpg", 0, 0, 256, 72);
	getimage(0, 0, 256, 72, bad);
	void *miss = malloc(imagesize(0, 0, 256, 72));
	readimagefile(".\\resources\\miss.jpg", 0, 0, 256, 72);
	getimage(0, 0, 256, 72, miss);
	
	
	
	
	
	

	//load resources;
	//convert beatmap
	
//start music
	char re[20];
	string mciCommand = "open \"" + songs[i].dir + songs[i].AudioFilename + "\" type mpegvideo alias mp3";
	cout << "open mp3 " << songs[i].AudioFilename << endl;
	mciSendString(mciCommand.c_str(), re, 20, NULL);
	cout << "MCI return " << re << endl;
	
	mciSendString("status mp3 length", re, 20, 0);
	int length = atoi(re);
	int position = 0;
	int old = 0;
	int keySig[4] = {0};
	int lastkeySig[4] = {0};
	int last = 0;
	settextstyle(GOTHIC_FONT, HORIZ_DIR, 5);
	mciSendString("play mp3", NULL, 0, NULL);
	while(position+offset < length){
		
		cur_page = -cur_page+1;
		setactivepage(cur_page);
		
		cleardevice();
		putimage(0, 0, BG, COPY_PUT);

		setfillstyle(1, BLACK);
		bar(columnPosition, 0, columnPosition+columnWidth*gameMode, 900);
		
		//settextstyle(GOTHIC_FONT, HORIZ_DIR, 5);
		sprintf(tmp, "%dx", result.combo);
		outtextxy(columnPosition+150, 200, tmp);
		
		if(last == 0)	putimage(columnPosition+(columnWidth*gameMode-256)/2, 600, miss, COPY_PUT);
		else if(last == 1)	putimage(columnPosition+(columnWidth*gameMode-256)/2, 600, perfect, COPY_PUT);
		else if(last == 2)	putimage(columnPosition+(columnWidth*gameMode-256)/2, 600, great, COPY_PUT);
		else if(last == 3)	putimage(columnPosition+(columnWidth*gameMode-256)/2, 600, bad, COPY_PUT);
		
		//outtextxy(columnPosition+120, 600, tmp);
		
		setcolor(WHITE);
		for(int j = 0; j <= gameMode; j++){
			line(columnPosition+columnWidth*j, 0, columnPosition+columnWidth*j, 900);
		}
		line(columnPosition, 800, columnPosition+gameMode*columnWidth, 800);
		
				setfillstyle(1, WHITE);
		for(int j = 0; j < 4; j++){
			if(keySig[j]==1){
				bar(columnPosition+columnWidth*j, 800, columnPosition+columnWidth*(j+1), 900);
			}
		}
		
		
		mciSendString("status mp3 position", re,20, 0);
		position = atoi(re);
		
		
		
		position += offset;
		//cout << position << endl;
		

		
		
		setfillstyle(1, WHITE);
		for(int j = 0; j < songs[i].hitobjects.size(); j++){
			
			if(songs[i].hitobjects[j].type == 1) continue;
			int ato = songs[i].hitobjects[j].time - position;
			

			int x = (songs[i].hitobjects[j].x+songs[i].hitobjects[j].time)%gameMode;
			int y = 800-speed*ato;
			
			
			if(keySig[(songs[i].hitobjects[j].x+songs[i].hitobjects[j].time)%gameMode] == 1 && lastkeySig[(songs[i].hitobjects[j].x+songs[i].hitobjects[j].time)%gameMode] == 0){
				if(ato < 128 && ato > -128){
					songs[i].hitobjects[j].type = 1;
					cout << ato << " key" << (songs[i].hitobjects[j].x)%gameMode << endl;
					/*sprintf(tmp, "%d", ato);
					outtextxy(300, 300, tmp);*/
					
					if(ato > 84 || ato < -84){
						result.bad++;
						last = 3;
					}
					else if(ato > 38 || ato < -38){
						result.great++;
						last = 2;
					}
					else {
						result.perfect++;
						last = 1;
					}
					result.combo++;
					lastkeySig[(songs[i].hitobjects[j].x+songs[i].hitobjects[j].time)%gameMode] = 1;
					cout << last << endl;
				}
			}
			if(ato < -128){
				songs[i].hitobjects[j].type = 1;
				last = 0;
				result.combo=0;
			}
			
			
			
			
			bar(columnPosition+x*columnWidth , y-20, columnPosition+(x+1)*columnWidth, y);
		}
		
		
		
		setvisualpage(cur_page);
		
		
		lastkeySig[0] = keySig[0];
		lastkeySig[1] = keySig[1];
		lastkeySig[2] = keySig[2];
		lastkeySig[3] = keySig[3];
		
		if(GetAsyncKeyState(Z_KEY)==0) keySig[0]=0;
        if(GetAsyncKeyState(X_KEY)==0) keySig[1]=0;
        if(GetAsyncKeyState(N_KEY)==0) keySig[2]=0;
        if(GetAsyncKeyState(M_KEY)==0) keySig[3]=0;
        
        if(GetAsyncKeyState(Z_KEY)!=0) keySig[0]=1;
        if(GetAsyncKeyState(X_KEY)!=0) keySig[1]=1;
        if(GetAsyncKeyState(N_KEY)!=0) keySig[2]=1;
        if(GetAsyncKeyState(M_KEY)!=0) keySig[3]=1;
		
		
		
		
		
		
		
		
		Sleep(1);
		
		

		
	}
	
	songs[i].timingpoints.clear();
	songs[i].hitobjects.clear();
	free(BG);
	mciSendString("stop mp3", NULL, 0, NULL);
	mciSendString("close mp3", NULL, 0, NULL);
	//return result;
	
}
